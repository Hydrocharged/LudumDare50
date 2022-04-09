// Copyright © 2022 Daylon Wilkins & Maxwell Chow
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "context.h"
#include "gui/system.h"

#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif // PLATFORM_WEB

#ifdef _WIN32
#include "hideconsole.h"
#endif //_WIN32

Context ctx = Context();

void UpdateDrawFrame(void);

int main(void) {
#ifdef _WIN32
	HideConsole();
#endif //_WIN32

	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(ctx.Screen.Width(), ctx.Screen.Height(), "The Fastest RPG");
	SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));

	ctx.Initialize();
#if defined(PLATFORM_WEB)
	emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
#else
	SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));
	while (!WindowShouldClose()) {
		ctx.Update();
		BeginDrawing();
		ClearBackground(ctx.Colors.Background);
		ctx.Draw();
		EndDrawing();
	}
#endif

	CloseWindow();
	return 0;
}

void UpdateDrawFrame(void) {
	ctx.Update();
	BeginDrawing();
	ClearBackground(ctx.Colors.Background);
	ctx.Draw();
	EndDrawing();
}
