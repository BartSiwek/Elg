/*
 * Copyright (c) 2012 Bartlomiej Siwek All rights reserved.
 */

#ifndef DEMOS_ELG_DEMOS_BASICDIRECTX_BASICDIRECTXGAME_H_
#define DEMOS_ELG_DEMOS_BASICDIRECTX_BASICDIRECTXGAME_H_

#pragma warning(push)
#pragma warning(disable : 6540)
#include <windows.h>
#include <d3d11.h>
#pragma warning(pop)

#include "Elg.DirectX/WindowsProcInterface.h"
#include "Elg.DirectX/Game.h"

#include "Demos/Elg.Demos.BasicDirectX/BasicDirectXWindow.h"

class BasicDirectXGame : public Elg::DirectX::Events::EventListenerInterface, public Elg::DirectX::Game {
 public:
  BasicDirectXGame(HINSTANCE instance, int window_show_cmd);

  virtual const elg_char* GetEventListenerName() const;
  virtual bool HandleEvent(Elg::DirectX::Events::Event* e);

  bool Initialize();

  bool Update(Elg::Clock::GameClock::TimePoint current_simulation_time, Elg::Clock::GameClock::Duration DT);
  void Render(elg_float32 interpolation_factor);
  void Shutdown();

  bool InitializeDirect3D11();
  bool InitScene();

 private:
  BasicDirectXWindow m_window_;

  ID3D11Device* m_d3d11_device_;
  ID3D11DeviceContext* m_d3d11_device_context_;
  ID3D11RenderTargetView* m_render_target_view_;

  ID3D11Buffer* m_triangle_vertex_buffer_;
  ID3D11VertexShader* m_vs_;
  ID3D11PixelShader* m_ps_;
  ID3D10Blob* m_vs_buffer_;
  ID3D10Blob* m_ps_buffer_;
  ID3D11InputLayout* m_vertex_layout_;
};


#endif  // DEMOS_ELG_DEMOS_BASICDIRECTX_BASICDIRECTXGAME_H_
