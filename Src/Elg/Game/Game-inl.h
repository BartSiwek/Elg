/*
 * Copyright (c) 2011 Bartlomiej Siwek All rights reserved.
 */

#ifndef ELG_GAME_GAME_INL_H_
#define ELG_GAME_GAME_INL_H_

#include "Elg/Game/Game.h"

#include "Elg/Utilities/Types.h"
#include "Elg/Clock/GameClock.h"
#include "Elg/Performance/FrameStatistics.h"
#include "Elg/Game/GameProfiling.h"

namespace Elg {
namespace Game {

template<typename GameImpl>
const Elg::Clock::GameClock::Duration Game<GameImpl>::DT =
  Elg::Clock::GameClock::Duration(Elg::Clock::Seconds(1)) / 60;

template<typename GameImpl>
Game<GameImpl>::Game(GameImpl* game_implementation)
    : m_game_implementation_(game_implementation),
      m_current_simulation_time_(Elg::Clock::GameClock::TimePoint::Epoch()),
      m_current_game_time_(Elg::Clock::GameClock::TimePoint::Epoch()),
      m_accumulator_(Elg::Clock::GameClock::Duration::Zero()) {
}

template<typename GameImpl>
Game<GameImpl>::~Game() {
}

template<typename GameImpl>
elg_int32 Game<GameImpl>::Run() {
  m_current_game_time_ = Elg::Clock::GameClock::Now();
  m_accumulator_ = DT;

  if (m_game_implementation_->Initialize()) {
    for (;;) {
      ELG_PROFILE_GAME_LOOP;

      bool quit_event_triggered = !m_game_implementation_->HandleOSMessagesEvents();
      if (quit_event_triggered) {
        m_game_implementation_->Shutdown();
        return 0;
      }

      Elg::Clock::GameClock::TimePoint new_time = Elg::Clock::GameClock::Now();
      Elg::Clock::GameClock::Duration frame_time = new_time - m_current_game_time_;

      Elg::Performance::FrameStatistics::RegisterFrameTime(frame_time);

      if (frame_time > Elg::Clock::Milliseconds(250)) {
        // Note: Clamp max frame time to avoid spiral of death...
        frame_time = Elg::Clock::Milliseconds(250);
      }

      m_current_game_time_ = new_time;
      m_accumulator_ += frame_time;

      while (m_accumulator_ >= DT) {
        // Update and check for quit condition
        bool should_quit = !m_game_implementation_->Update(m_current_simulation_time_, DT);
        if (should_quit) {
          m_game_implementation_->Shutdown();
          return 0;
        }

        m_current_simulation_time_ += DT;
        m_accumulator_ -= DT;
      }

      const elg_float32 interpolation_factor =
        static_cast<elg_float32>(Elg::Clock::DurationCast<Elg::Clock::Milliseconds>(m_accumulator_).Count()) /
        static_cast<elg_float32>(Elg::Clock::DurationCast<Elg::Clock::Milliseconds>(DT).Count());
      m_game_implementation_->Render(interpolation_factor);
    }
    // Ureachable...
  } else {
    return 1;
  }
}

}  // namespace Game
}  // namespace Elg

#endif  // ELG_GAME_GAME_INL_H_
