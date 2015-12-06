/*
 * Copyright (c) 2012 Bartlomiej Siwek All rights reserved.
 */

#ifndef ELG_DIRECTX_GAME_H_
#define ELG_DIRECTX_GAME_H_

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <Windows.h>

#include "Elg/Clock/GameClock.h"
#include "Elg/Clock/TimePoint.h"
#include "Elg/Clock/Duration.h"

#include "Elg.DirectX/MouseButton.h"
#include "Elg.DirectX/Events/EventManager.h"

#include "Elg.DirectX/WindowsProcInterface.h"

namespace Elg {
namespace DirectX {

class Game : public Elg::DirectX::WindowsProcInterface {
 public:
  // Constructors
  Game();

  // Destructor
  ~Game();

  // Game interface
  bool Initialize();
  bool HandleOSMessagesEvents();
  bool Update(Elg::Clock::GameClock::TimePoint current_simulation_time, Elg::Clock::GameClock::Duration DT);
  void Render(elg_float32 interpolation_factor);
  void Shutdown();

  // Event manager
  Elg::DirectX::Events::EventManager* GetEventManager();
  const Elg::DirectX::Events::EventManager* GetEventManager() const;

  // Termination requests
  void RequestTermination();

  // The window procedure
  LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

 private:
  void FireMouseEvent(HWND hwnd, Elg::DirectX::MouseButton button, Elg::DirectX::MouseButtonAction action,
                      LPARAM lparam) const;
  void FireMouseMoveEvent(HWND hwnd, LPARAM lparam) const;
  void FireMouseWheelEvent(HWND hwnd, WPARAM wparam, LPARAM lparam) const;
  LRESULT FireKeyboardEvent(HWND hwnd, LPARAM lparam) const;

  Elg::DirectX::Events::EventManager m_event_manager_;
};

}  // namespace DirectX
}  // namespace Elg

#endif  // ELG_DIRECTX_GAME_H_
