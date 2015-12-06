/*
 * Copyright (c) 2012 Bartlomiej Siwek All rights reserved.
 */

#include "Elg/Performance/ScopeProfiler.h"

#include <cstdio>

#include "Elg/Utilities/Macros.h"
#include "Elg/Utilities/Asserts.h"
#include "Elg/Utilities/Types.h"

namespace Elg {
namespace Performance {
namespace Scope {

// Consts
const elg_uint32 ELG_SCOPE_PROFILER_HASH_TABLE_SIZE = 2048;  // Should be the power of two for fast divide/modulo
const elg_uint32 ELG_SCOPE_PROFILER_FNV_PRIME = 16777619;
const elg_uint32 ELG_SCOPE_PROFILER_FNV_OFFSET = 2166136261;
const elg_uint32 ELG_SCOPE_PROFILER_EMPTY_MARKER = 0xFFFFFFFF;

// Structs
struct HashTableEntry {
  HashTableEntry()
      : Hash(ELG_SCOPE_PROFILER_FNV_PRIME) , Empty(true) {
  }

  elg_uint32 Hash;
  bool Empty;
};

struct ScopeStatistics {
  ScopeStatistics()
      : Max(0), Accumulator(0), SquaresAccumulator(0), HitCount(0), ParentIndex(ELG_SCOPE_PROFILER_EMPTY_MARKER) {
  }

  elg_uint64 Max;
  elg_uint64 Accumulator;
  elg_uint64 SquaresAccumulator;
  elg_uint32 HitCount;
  elg_uint32 ParentIndex;
};

struct ScopeHierarchyNode {
  ScopeHierarchyNode()
    : LeftChild(ELG_SCOPE_PROFILER_EMPTY_MARKER), RightSibling(ELG_SCOPE_PROFILER_EMPTY_MARKER) {
  }

  elg_uint32 LeftChild;
  elg_uint32 RightSibling;
};

// Globals
elg_uint32 g_hash_table_entry_count_ = 0;
elg_uint32 g_current_scope_index_ = ELG_SCOPE_PROFILER_HASH_TABLE_SIZE;  // A fake root index to all calls
HashTableEntry g_hash_table_[ELG_SCOPE_PROFILER_HASH_TABLE_SIZE+1];  // The final one is used for going up over roots
ScopeStatistics g_scope_statistics_[ELG_SCOPE_PROFILER_HASH_TABLE_SIZE+1];  // Indexed via hash table
ScopeHierarchyNode g_scope_hierarchy_[ELG_SCOPE_PROFILER_HASH_TABLE_SIZE+1];  // Indexed via hash table
const char* g_scope_names_[ELG_SCOPE_PROFILER_HASH_TABLE_SIZE+1];  // Indexed via hash table

// Hash table
static ELG_FORCEINLINE elg_uint32 HashCombine(elg_uint32 seed, elg_uint32 value) {
  elg_uint32 combined = seed;

  combined *= ELG_SCOPE_PROFILER_FNV_PRIME;
  combined ^= ((value >> 24) & 0xFF);
  combined *= ELG_SCOPE_PROFILER_FNV_PRIME;
  combined ^= ((value >> 16) & 0xFF);
  combined *= ELG_SCOPE_PROFILER_FNV_PRIME;
  combined ^= ((value >> 8) & 0xFF);
  combined *= ELG_SCOPE_PROFILER_FNV_PRIME;
  combined ^= ((value) & 0xFF);

  return combined;
}

void EnterScope(elg_uint32 scope_id_hash, const char* scope_id) {
  // Get the global state
  elg_uint32 parent_index = g_current_scope_index_;
  elg_uint32 parent_hash = g_hash_table_[parent_index].Hash;

  // Hash a pair of the
  elg_uint32 comined_hash = HashCombine(parent_hash, scope_id_hash);

  // Initial guess
  elg_uint32 index = comined_hash & (ELG_SCOPE_PROFILER_HASH_TABLE_SIZE-1);  // We have power of two as the size

  // Search until we either find the key, or find an empty slot (linear probing)
  while (!g_hash_table_[index].Empty && (g_hash_table_[index].Hash != comined_hash)) {
    index = (index+1) & (ELG_SCOPE_PROFILER_HASH_TABLE_SIZE-1);  // We have power of two as the size
  }

  // Create a new entry if we need it
  if (g_hash_table_[index].Empty) {
    // Mark the hash table as not empty
    g_hash_table_[index].Empty = false;
    g_hash_table_[index].Hash = comined_hash;

    // Set the parent in the statistics
    g_scope_statistics_[index].ParentIndex = parent_index;

    // Set the scope name
    g_scope_names_[index] = scope_id;

    // Do the count tracking
    ASSERT((++g_hash_table_entry_count_) <= ELG_SCOPE_PROFILER_HASH_TABLE_SIZE, "Scope profiler table full");
  }

  // Update the global state
  g_current_scope_index_ = index;
}

void LeaveScope(elg_uint64 time) {
  // Get the index
  elg_uint32 index = g_current_scope_index_;
  elg_uint32 parent_index = g_scope_statistics_[index].ParentIndex;

  g_scope_statistics_[index].Max = (time < g_scope_statistics_[index].Max ? g_scope_statistics_[index].Max : time);
  g_scope_statistics_[index].Accumulator += time;
  g_scope_statistics_[index].SquaresAccumulator += (time * time);
  g_scope_statistics_[index].HitCount += 1;

  g_current_scope_index_ = parent_index;
}

static void ClearCallHierarchy() {
  for (elg_uint32 node_index = 0;node_index <= ELG_SCOPE_PROFILER_HASH_TABLE_SIZE;++node_index) {
    g_scope_hierarchy_[node_index].LeftChild = ELG_SCOPE_PROFILER_EMPTY_MARKER;
    g_scope_hierarchy_[node_index].RightSibling = ELG_SCOPE_PROFILER_EMPTY_MARKER;
  }
}

static void BuildCallHierarchy() {
  for (elg_uint32 table_index = 0;table_index < ELG_SCOPE_PROFILER_HASH_TABLE_SIZE;++table_index) {
    elg_uint32 parent_index = g_scope_statistics_[table_index].ParentIndex;
    if (parent_index != ELG_SCOPE_PROFILER_EMPTY_MARKER) {
      elg_uint32 left_child = g_scope_hierarchy_[parent_index].LeftChild;
      g_scope_hierarchy_[table_index].RightSibling = left_child;
      g_scope_hierarchy_[parent_index].LeftChild = table_index;
    }
  }
}

static void DumpNode(elg_uint32 node_index, elg_uint32 parent_index, FILE* output, elg_uint32 indent) {
  // Read parent data
  elg_uint64 parent_total = g_scope_statistics_[parent_index].Accumulator;

  // Read the data to local vars
  elg_uint64 max = g_scope_statistics_[node_index].Max;
  elg_uint64 total = g_scope_statistics_[node_index].Accumulator;
  elg_uint64 total_squares = g_scope_statistics_[node_index].SquaresAccumulator;
  elg_uint32 hits = g_scope_statistics_[node_index].HitCount;
  const char* scope_id = g_scope_names_[node_index];

  // Converted data
  elg_float32 parent_total_f = static_cast<elg_float32>(parent_total);
  elg_float32 total_f = static_cast<elg_float32>(total);
  elg_float32 total_squares_f = static_cast<elg_float32>(total_squares);
  elg_float32 hits_f = static_cast<elg_float32>(hits);

  // Calculate additinal stats
  elg_float32 parent_total_percent = 100 * total_f / parent_total_f;
  elg_float32 avg = total_f / hits_f;
  elg_float32 dev = 0.0;
  if (hits > 1) {
    dev = std::sqrt((total_squares_f - hits_f * avg * avg) / (hits_f - 1));
  }

  // Print
  fprintf(output, "%*s[%s] Total: %lluns (%.2f%%) Max: %lluns Avg: %.3fns Dev: %.3fns Hits: %lu\n",
          indent, "`-", scope_id, total, parent_total_percent, max, avg, dev, hits);

  // Recurse
  elg_uint32 current_child = g_scope_hierarchy_[node_index].LeftChild;
  while (current_child != ELG_SCOPE_PROFILER_EMPTY_MARKER) {
    DumpNode(current_child, node_index, output, indent+2);
    current_child = g_scope_hierarchy_[current_child].RightSibling;
  }
}

static void DumpRoot(elg_uint32 root_index, FILE* output) {
  // Read the data to local vars
  elg_uint64 max = g_scope_statistics_[root_index].Max;
  elg_uint64 total = g_scope_statistics_[root_index].Accumulator;
  elg_uint64 total_squares = g_scope_statistics_[root_index].SquaresAccumulator;
  elg_uint32 hits = g_scope_statistics_[root_index].HitCount;
  const char* scope_id = g_scope_names_[root_index];

  // Converted data
  elg_float32 total_f = static_cast<elg_float32>(total);
  elg_float32 total_squares_f = static_cast<elg_float32>(total_squares);
  elg_float32 hits_f = static_cast<elg_float32>(hits);

  // Calculate additinal stats
  elg_float32 avg = total_f / hits_f;
  elg_float32 dev = 0.0;
  if (hits > 1) {
    dev = std::sqrt((total_squares_f - hits_f * avg * avg) / (hits_f - 1));
  }

  // Print
  fprintf(output, "[%s] Total: %lluns (100%%) Max: %lluns Avg: %.3fns Dev: %.3fns Hits: %lu\n",
          scope_id, total, max, avg, dev, hits);

  // Recurse
  elg_uint32 current_child = g_scope_hierarchy_[root_index].LeftChild;
  while (current_child != ELG_SCOPE_PROFILER_EMPTY_MARKER) {
    DumpNode(current_child, root_index, output, 2);
    current_child = g_scope_hierarchy_[current_child].RightSibling;
  }
}

static void DumpCallHierarchy(FILE* output) {
  elg_uint32 current_root = g_scope_hierarchy_[ELG_SCOPE_PROFILER_HASH_TABLE_SIZE].LeftChild;
  while (current_root != ELG_SCOPE_PROFILER_EMPTY_MARKER) {
    DumpRoot(current_root, output);
    current_root = g_scope_hierarchy_[current_root].RightSibling;
  }
}

void DumpStatistics(FILE* output) {
  ClearCallHierarchy();
  BuildCallHierarchy();
  DumpCallHierarchy(output);
}

}  // namespace Scope
}  // namespace Performance
}  // namespace Elg
