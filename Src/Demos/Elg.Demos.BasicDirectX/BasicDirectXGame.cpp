/*
 * Copyright (c) 2012 Bartlomiej Siwek All rights reserved.
 */

#include "Demos/Elg.Demos.BasicDirectX/BasicDirectXGame.h"

#pragma warning(push)
#pragma warning(disable : 6540)
#include <windows.h>
#include <d3d11.h>
#include <d3dx11.h>
#include <dxerr.h>
#pragma warning(pop)

#include "Elg/Utilities/Asserts.h"

#include "Elg.DirectX/WindowsProcInterface.h"
#include "Elg.DirectX/Game.h"

#include "Demos/Elg.Demos.BasicDirectX/BasicDirectXWindow.h"
#include "Demos/Elg.Demos.BasicDirectX/Vertex.h"

BasicDirectXGame::BasicDirectXGame(HINSTANCE /* instance */, int /* window_show_cmd */) : m_window_() {
}

const elg_char* BasicDirectXGame::GetEventListenerName() const {
  return "MyGame";
}

bool BasicDirectXGame::HandleEvent(Elg::DirectX::Events::Event* e) {
  if (e->EventType == Elg::DirectX::Events::KEYBOARD_EVENT) {
    if (e->KeyboardEvent.KeyCode == Elg::DirectX::KEY_Q) {
      this->RequestTermination();
    }
  }

  return false;
}

bool BasicDirectXGame::Initialize() {
  // Setup window
  m_window_.SetCaption("Main window");
  m_window_.Initialize(this);

  // Setup event listener
  VERIFY_TRUE(this->GetEventManager()->AddEventListener(Elg::DirectX::Events::KEYBOARD_EVENT, this),
              "Cannot register BasicDirectXGame as a listener to keyboard events");

  // Initialize Direct3D 11
  bool direct3d11_init_ok = InitializeDirect3D11();
  if (direct3d11_init_ok) {
    // Initialize scene
    bool scene_init_ok = InitScene();
    if (scene_init_ok) {
      return true;
    } else {
      return false;
    }
  } else {
    return false;
  }
}

bool BasicDirectXGame::Update(Elg::Clock::GameClock::TimePoint /* current_simulation_time */,
            Elg::Clock::GameClock::Duration /* DT */) {
  return true;
}

void BasicDirectXGame::Render(elg_float32 /* interpolation_factor */) {
  // Clear our backbuffer
  float bgColor[4] = {(0.0f, 0.0f, 0.0f, 0.0f)};
  m_d3d11_device_context_->ClearRenderTargetView(m_render_target_view_, bgColor);

  // Draw the triangle
  m_d3d11_device_context_->Draw(3, 0);

  // Present the backbuffer to the window
  m_window_.GetSwapChain()->Present(0, 0);
}

void BasicDirectXGame::Shutdown() {
  // Release the COM Objects we created
  m_vertex_layout_->Release();
  m_ps_->Release();
  m_vs_->Release();
  m_ps_buffer_->Release();
  m_vs_buffer_->Release();
  m_triangle_vertex_buffer_->Release();

  m_render_target_view_->Release();
  m_d3d11_device_context_->Release();
  m_d3d11_device_->Release();
}

bool BasicDirectXGame::InitializeDirect3D11() {
  HRESULT hr = S_OK;

  UINT create_device_flags = 0;
#ifdef _DEBUG
  create_device_flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

  D3D_DRIVER_TYPE driver_types[] = {
    D3D_DRIVER_TYPE_HARDWARE,
  };
  UINT num_driver_types = 1;

  D3D_FEATURE_LEVEL feature_levels[] = {
    D3D_FEATURE_LEVEL_11_0
  };
  UINT num_feature_levels = 1;

  // Describe our SwapChain
  DXGI_SWAP_CHAIN_DESC swap_chain_desc;

  ZeroMemory(&swap_chain_desc, sizeof(swap_chain_desc));

  HWND window_handle = m_window_.GetHandle();

  swap_chain_desc.BufferCount = 1;
  swap_chain_desc.BufferDesc.Width = 800;  // Get from window
  swap_chain_desc.BufferDesc.Height = 600;  // Get from window
  swap_chain_desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
  swap_chain_desc.BufferDesc.RefreshRate.Numerator = 60;
  swap_chain_desc.BufferDesc.RefreshRate.Denominator = 1;
  swap_chain_desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
  swap_chain_desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
  swap_chain_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
  swap_chain_desc.OutputWindow = window_handle;
  swap_chain_desc.SampleDesc.Count = 1;
  swap_chain_desc.SampleDesc.Quality = 0;
  swap_chain_desc.Windowed = TRUE;
  swap_chain_desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

  IDXGISwapChain* swap_chain = NULL;
  for (UINT driver_type_index = 0; driver_type_index < num_driver_types; driver_type_index++) {
    D3D_DRIVER_TYPE driver_type = driver_types[driver_type_index];
    D3D_FEATURE_LEVEL result_feature_level;
    hr = D3D11CreateDeviceAndSwapChain(NULL, driver_type, NULL, create_device_flags, feature_levels,
                                        num_feature_levels, D3D11_SDK_VERSION, &swap_chain_desc,
                                        &swap_chain, &m_d3d11_device_, &result_feature_level,
                                        &m_d3d11_device_context_);

    if (SUCCEEDED(hr)) {
      break;
    }

    if (FAILED(hr)) {
      DXTrace(__FILE__, __LINE__, hr, DXGetErrorDescription(hr), TRUE);
    }
  }

  // Create our BackBuffer
  ID3D11Texture2D* back_buffer;
  hr = swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&back_buffer));
  if (FAILED(hr)) {
    DXTrace(__FILE__, __LINE__, hr, DXGetErrorDescription(hr), TRUE);
    return false;
  }

  // Create our Render Target
  hr = m_d3d11_device_->CreateRenderTargetView(back_buffer, NULL, &m_render_target_view_);
  if (FAILED(hr)) {
    DXTrace(__FILE__, __LINE__, hr, DXGetErrorDescription(hr), TRUE);
    return false;
  }

  back_buffer->Release();

  // Set our Render Target
  m_d3d11_device_context_->OMSetRenderTargets(1, &m_render_target_view_, NULL);

  // Set the swaphain for window
  m_window_.SetSwapChain(swap_chain);

  // Return success
  return true;
}

bool BasicDirectXGame::InitScene() {
  HRESULT hr;

  // Compile Shaders from shader file
  hr = D3DX11CompileFromFile(L"Source\\Effects.hlsl", 0, 0, "VS", "vs_4_0", 0, 0, 0, &m_vs_buffer_, 0, 0);
  if (FAILED(hr)) {
    DXTrace(__FILE__, __LINE__, hr, DXGetErrorDescription(hr), TRUE);
    return false;
  }

  hr = D3DX11CompileFromFile(L"Source\\Effects.hlsl", 0, 0, "PS", "ps_4_0", 0, 0, 0, &m_ps_buffer_, 0, 0);
  if (FAILED(hr)) {
    DXTrace(__FILE__, __LINE__, hr, DXGetErrorDescription(hr), TRUE);
    return false;
  }

  // Create the Shader Objects
  hr = m_d3d11_device_->CreateVertexShader(m_vs_buffer_->GetBufferPointer(), m_vs_buffer_->GetBufferSize(),
                                            NULL, &m_vs_);
  if (FAILED(hr)) {
    DXTrace(__FILE__, __LINE__, hr, DXGetErrorDescription(hr), TRUE);
  }

  hr = m_d3d11_device_->CreatePixelShader(m_ps_buffer_->GetBufferPointer(), m_ps_buffer_->GetBufferSize(),
                                          NULL, &m_ps_);
  if (FAILED(hr)) {
    DXTrace(__FILE__, __LINE__, hr, DXGetErrorDescription(hr), TRUE);
  }

  // Set Vertex and Pixel Shaders
  m_d3d11_device_context_->VSSetShader(m_vs_, 0, 0);
  m_d3d11_device_context_->PSSetShader(m_ps_, 0, 0);

  // Create the vertex buffer
  Vertex v[] = {
    Vertex(0.0f,  0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f),
    Vertex(0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f),
    Vertex(-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f),
  };

  D3D11_BUFFER_DESC vertexBufferDesc;
  ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));

  vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
  vertexBufferDesc.ByteWidth = sizeof(Vertex) * 3;
  vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
  vertexBufferDesc.CPUAccessFlags = 0;
  vertexBufferDesc.MiscFlags = 0;

  D3D11_SUBRESOURCE_DATA vertexBufferData;

  ZeroMemory(&vertexBufferData, sizeof(vertexBufferData));
  vertexBufferData.pSysMem = v;
  hr = m_d3d11_device_->CreateBuffer(&vertexBufferDesc, &vertexBufferData, &m_triangle_vertex_buffer_);
  if (FAILED(hr)) {
    DXTrace(__FILE__, __LINE__, hr, DXGetErrorDescription(hr), TRUE);
  }

  // Set the vertex buffer
  UINT stride = sizeof(Vertex);
  UINT offset = 0;
  m_d3d11_device_context_->IASetVertexBuffers(0, 1, &m_triangle_vertex_buffer_, &stride, &offset);

  // Layout description
  D3D11_INPUT_ELEMENT_DESC layout[] = {
    { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
  };
  UINT layout_elements_count = 2;

  // Create the Input Layout
  hr = m_d3d11_device_->CreateInputLayout(layout, layout_elements_count, m_vs_buffer_->GetBufferPointer(),
                                          m_vs_buffer_->GetBufferSize(), &m_vertex_layout_);
  if (FAILED(hr)) {
    DXTrace(__FILE__, __LINE__, hr, DXGetErrorDescription(hr), TRUE);
  }

  // Set the Input Layout
  m_d3d11_device_context_->IASetInputLayout(m_vertex_layout_);

  // Set Primitive Topology
  m_d3d11_device_context_->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

  // Create the Viewport
  D3D11_VIEWPORT viewport;
  ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

  viewport.TopLeftX = 0;
  viewport.TopLeftY = 0;
  viewport.Width = 800;
  viewport.Height = 600;

  // Set the Viewport
  m_d3d11_device_context_->RSSetViewports(1, &viewport);

  // Signal success
  return true;
}
