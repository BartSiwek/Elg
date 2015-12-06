/*
 * Copyright (c) 2012 Bartlomiej Siwek All rights reserved.
 */

#ifndef DEMOS_ELG_DEMOS_BASICDIRECTX_BASICDIRECTXWINDOW_H_
#define DEMOS_ELG_DEMOS_BASICDIRECTX_BASICDIRECTXWINDOW_H_

#include "Elg.DirectX/Window.h"

class BasicDirectXWindow : public Elg::DirectX::Window {
 public:
  BasicDirectXWindow() : m_swap_chain_() {
  }

  virtual void Initailize(Elg::DirectX::WindowsProcInterface* window_proc) {
    Elg::DirectX::Window::Initialize(window_proc);
  }

  virtual void Shutdown() {
    if (m_swap_chain_ != NULL) {
      m_swap_chain_->Release();
      m_swap_chain_ = NULL;
    }
    Elg::DirectX::Window::Shutdown();
  }

  IDXGISwapChain* GetSwapChain() {
    return m_swap_chain_;
  }

  const IDXGISwapChain* GetSwapChain() const {
    return m_swap_chain_;
  }

  void SetSwapChain(IDXGISwapChain* swap_chain) {
    m_swap_chain_ = swap_chain;
  }

 private:
  IDXGISwapChain* m_swap_chain_;
};

#endif  // DEMOS_ELG_DEMOS_BASICDIRECTX_BASICDIRECTXWINDOW_H_
