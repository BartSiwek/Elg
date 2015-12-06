/*
 * Copyright (c) 2012 Bartlomiej Siwek All rights reserved.
 */

#include "Elg/Game/Game.h"

#include "Demos/Elg.Demos.BasicDirectX/BasicDirectXGame.h"

int WINAPI WinMain(HINSTANCE instance, HINSTANCE /* prev_instance */, LPSTR /* cmd_line */, int window_show_cmd) {
  BasicDirectXGame g(instance, window_show_cmd);
  elg_int32 result = Elg::Game::Game<BasicDirectXGame>(&g).Run();
  return result;
}
