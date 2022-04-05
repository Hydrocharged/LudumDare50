// Copyright © 2022 Daylon Wilkins & Maxwell Chow
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "context.h"
#include "gui/system.h"
#include "hideconsole.h"

int main(void) {
	HideConsole();
	Context ctx = Context();

	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(ctx.Screen.Width(), ctx.Screen.Height(), "The Fastest RPG");
	SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));

	ctx.Initialize();

	while (!WindowShouldClose()) {
		ctx.Update();
		BeginDrawing();
		ClearBackground(ctx.Colors.Background);
		ctx.Draw();
		EndDrawing();
	}

	CloseWindow();
	return 0;
}
