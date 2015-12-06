/*
 * Copyright (c) 2012 Bartlomiej Siwek All rights reserved.
 */

#include "Elg.DirectX/Game.h"

#include "Elg.DirectX/Keyboard.h"
#include "Elg.DirectX/WindowRegistry.h"

namespace Elg {
namespace DirectX {

Game::Game() : m_event_manager_() {
}

Game::~Game() {
}

bool Game::Initialize() {
  return true;
}

bool Game::HandleOSMessagesEvents() {
  MSG msg;
  bool should_continue = true;

  while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
    if (msg.message == WM_QUIT) {
      should_continue = false;
      break;
    }
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  return should_continue;
}

bool Game::Update(Elg::Clock::GameClock::TimePoint /* current_simulation_time */,
                  Elg::Clock::GameClock::Duration /* DT */) {
  return true;
}

void Game::Render(elg_float32 /* interpolation_factor */) {
}

void Game::Shutdown() {
}

Elg::DirectX::Events::EventManager* Game::GetEventManager() {
  return &m_event_manager_;
}

const Elg::DirectX::Events::EventManager* Game::GetEventManager() const {
  return &m_event_manager_;
}

void Game::RequestTermination() {
  PostQuitMessage(0);
}

LRESULT Game::WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
  switch (msg) {
    case WM_CREATE: {
      // Register RAW Input
      RAWINPUTDEVICE rid = {0x01, 6, RIDEV_NOLEGACY | RIDEV_INPUTSINK, hwnd };
      RegisterRawInputDevices(&rid, 1, sizeof(rid));

      // Return 0 to allow the window to proceed in the creation process.
      return 0;
    }
    case WM_PAINT: {
      // This message is handled by the default handler to avoid a repeated sending of the message. This results in
      // the ability to process all pending messages at once without getting stuck in an eternal loop.
      break;
    }
    case WM_CLOSE: {
      // This message is sent when a window or an application should terminate.
      Window* window = WindowRegistry::GetWindow(hwnd);
      if (window != NULL) {
        window->Shutdown();
      }
      return 0;
    }
    case WM_DESTROY: {
      // This message is sent when a window has been destroyed - check count now
      if (WindowRegistry::GetWindowCount() == 0) {
        PostQuitMessage(0);
      }
      return 0;
    }
    case WM_SIZE: {
      // EvtWindowResize* pEvent = new EvtWindowResize( hwnd, wparam, lparam );
      // EventManager::Get()->ProcessEvent( pEvent );
      break;
    }
    case WM_LBUTTONUP: {
      FireMouseEvent(hwnd, Elg::DirectX::LEFT_MOUSE_BUTTON, Elg::DirectX::MOUSE_BUTTON_UP, lparam);
      break;
    }
    case WM_LBUTTONDOWN: {
      FireMouseEvent(hwnd, Elg::DirectX::LEFT_MOUSE_BUTTON, Elg::DirectX::MOUSE_BUTTON_DOWN, lparam);
      break;
    }
    case WM_MBUTTONUP: {
      FireMouseEvent(hwnd, Elg::DirectX::MIDDLE_MOUSE_BUTTON, Elg::DirectX::MOUSE_BUTTON_UP, lparam);
      break;
    }
    case WM_MBUTTONDOWN: {
      FireMouseEvent(hwnd, Elg::DirectX::MIDDLE_MOUSE_BUTTON, Elg::DirectX::MOUSE_BUTTON_DOWN, lparam);
      break;
    }
    case WM_RBUTTONUP: {
      FireMouseEvent(hwnd, Elg::DirectX::RIGHT_MOUSE_BUTTON, Elg::DirectX::MOUSE_BUTTON_UP, lparam);
      break;
    }
    case WM_RBUTTONDOWN: {
      FireMouseEvent(hwnd, Elg::DirectX::RIGHT_MOUSE_BUTTON, Elg::DirectX::MOUSE_BUTTON_DOWN, lparam);
      break;
    }
    case WM_MOUSEMOVE: {
      FireMouseMoveEvent(hwnd, lparam);
      break;
    }
    case WM_MOUSEWHEEL: {
      FireMouseWheelEvent(hwnd, wparam, lparam);
      break;
    }
    case WM_INPUT: {
      return FireKeyboardEvent(hwnd, lparam);
      break;
    }
  }

  return DefWindowProc(hwnd, msg, wparam, lparam);
}

void Game::FireMouseEvent(HWND hwnd, Elg::DirectX::MouseButton button, Elg::DirectX::MouseButtonAction action,
                          LPARAM lparam) const {
  elg_int32 x = (0xffff & lparam);
  elg_int32 y = ((0xffff0000 & lparam) >> 16);

  Window* window = WindowRegistry::GetWindow(hwnd);
  if (window != NULL) {
    Elg::DirectX::Events::Event e;
    e.EventType = Elg::DirectX::Events::MOUSE_BUTTON_EVENT;
    e.MouseButtonEvent.Window = window;
    e.MouseButtonEvent.Button = button;
    e.MouseButtonEvent.Action = action;
    e.MouseButtonEvent.X = x;
    e.MouseButtonEvent.Y = y;

    m_event_manager_.FireEvent(&e);
  }
}

void Game::FireMouseMoveEvent(HWND hwnd, LPARAM lparam) const {
  elg_int32 x = (0xffff & lparam);
  elg_int32 y = ((0xffff0000 & lparam) >> 16);

  Window* window = WindowRegistry::GetWindow(hwnd);
  if (window != NULL) {
    Elg::DirectX::Events::Event e;
    e.EventType = Elg::DirectX::Events::MOUSE_MOVE_EVENT;
    e.MouseMoveEvent.Window = window;
    e.MouseMoveEvent.X = x;
    e.MouseMoveEvent.Y = y;

    m_event_manager_.FireEvent(&e);
  }
}

void Game::FireMouseWheelEvent(HWND hwnd, WPARAM wparam, LPARAM lparam) const {
  elg_int32 x = (0xffff & lparam);
  elg_int32 y = ((0xffff0000 & lparam) >> 16);
  elg_int32 delta = static_cast<elg_int32>((0xffff0000 & wparam) >> 16);

  Window* window = WindowRegistry::GetWindow(hwnd);
  if (window != NULL) {
    Elg::DirectX::Events::Event e;
    e.EventType = Elg::DirectX::Events::MOUSE_WHEEL_EVENT;
    e.MouseWheelEvent.Window = window;
    e.MouseWheelEvent.X = x;
    e.MouseWheelEvent.Y = y;
    e.MouseWheelEvent.Delta = delta;

    m_event_manager_.FireEvent(&e);
  }
}

LRESULT Game::FireKeyboardEvent(HWND /* hwnd */, LPARAM lparam) const {
  RAWINPUT ri;
  UINT size = sizeof(RAWINPUT);
  GetRawInputData((HRAWINPUT)lparam, RID_INPUT, &ri, &size, sizeof(RAWINPUTHEADER));
  if (ri.header.dwType == RIM_TYPEKEYBOARD) {
    VirtualKeyCode key_code = GetKeyCode(ri.data.keyboard.VKey);

    VirtualKeyState state;
    if ((ri.data.keyboard.Flags & RI_KEY_BREAK) != 0) {
      // Key is UP
      RegisterKeyUp(key_code);
      state = KEY_STATE_UP;
    } else  {
      // Key is DOWN
      RegisterKeyDown(key_code);
      state = KEY_STATE_DOWN;
    }

    VirtualKeyModifierFlags modifier_flags = GetModifierFlags();
    VirtualKeyState previous_state = GetPreviousState(key_code);

    HWND acctive_hwnd = GetActiveWindow();
    Window* window = WindowRegistry::GetWindow(acctive_hwnd);
    if (window != NULL) {
      Elg::DirectX::Events::Event e;
      e.EventType = Elg::DirectX::Events::KEYBOARD_EVENT;
      e.KeyboardEvent.Window = window;
      e.KeyboardEvent.KeyCode = key_code;
      e.KeyboardEvent.ModifierFlags = modifier_flags;
      e.KeyboardEvent.State = state;
      e.KeyboardEvent.PreviousState = previous_state;

      m_event_manager_.FireEvent(&e);
    }

    return 0;  // Return 0 to mark the event as handled
  } else {
    return 1;  // Return 1 to mark the event as NOT handled
  }
}

}  // namespace DirectX
}  // namespace Elg
