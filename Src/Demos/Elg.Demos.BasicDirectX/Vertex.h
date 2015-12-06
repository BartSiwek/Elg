/*
 * Copyright (c) 2012 Bartlomiej Siwek All rights reserved.
 */

#ifndef DEMOS_ELG_DEMOS_BASICDIRECTX_VERTEX_H_
#define DEMOS_ELG_DEMOS_BASICDIRECTX_VERTEX_H_

#include <xnamath.h>

struct Vertex {
  Vertex() {
  }

  Vertex(float x, float y, float z, float r, float g, float b, float a) : position(x, y, z), color(r, g, b, a) {
  }

  XMFLOAT3 position;
  XMFLOAT4 color;
};

#endif  // DEMOS_ELG_DEMOS_BASICDIRECTX_VERTEX_H_
