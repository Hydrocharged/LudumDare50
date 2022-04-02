// Copyright © 2022 Daylon Wilkins & Maxwell Chow
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "raylib.h"

int main(void) {
	int windowWidth = 1280;
	int windowHeight = 720;
	const Color background = Color{30, 30, 30, 255};

	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(windowWidth, windowHeight, "The Fastest RPG");
	SetTargetFPS(60);

	int menu = 1;

    Image grayGoblin = LoadImage("../Art/Enemies/GoblinwithStaff/GrayLayer.png");
    ImageResize(&grayGoblin, 500, 500);
    Texture2D tempTexture = LoadTextureFromImage(grayGoblin);
    UnloadImage(grayGoblin);

    Image backGoblin = LoadImage("../Art/Enemies/GoblinwithStaff/ColorLayer.png");
    ImageResize(&backGoblin, 500, 500);
    Texture2D tempTexture2 = LoadTextureFromImage(backGoblin);
    UnloadImage(backGoblin);

	while (!WindowShouldClose()) {
		windowWidth = GetScreenWidth();
		windowHeight = GetScreenHeight();
		BeginDrawing();
		ClearBackground(background);

		if (menu == 0 || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
			int titleSpace = windowHeight / 3;
			int titleFontSize = (int)(windowHeight * 0.15);
			if ((windowWidth * 0.08) < titleFontSize) {
				titleFontSize = (int)(windowWidth * 0.08);
			}
			int titleWidth = MeasureText("The Fastest RPG", titleFontSize);
			DrawText("The Fastest RPG", (windowWidth / 2) - (titleWidth / 2), (titleSpace / 2) - (titleFontSize / 2), titleFontSize, RAYWHITE);

			int buttonSpaceDivisions = (windowHeight - titleSpace) / 4;
			int buttonWidth = (int)(windowWidth * 0.4);
			int buttonHeight = (int)(buttonSpaceDivisions * 0.6);
			int buttonFontSize = (int)(buttonHeight * 0.7);
			if ((buttonWidth * 0.08) < buttonFontSize) {
				buttonFontSize = (int)(buttonWidth * 0.08);
			}
			Rectangle playButton = {
				.x =  (float)((windowWidth / 2) - (buttonWidth / 2)),
				.y =  (float)(titleSpace + ((buttonSpaceDivisions / 2) - (buttonHeight / 2))),
				.width =  (float)buttonWidth,
				.height =  (float)buttonHeight
			};
			Rectangle leaderboardButton = {
					.x =  playButton.x,
					.y =  playButton.y + buttonSpaceDivisions,
					.width =  playButton.width,
					.height =  playButton.height
			};
			Rectangle playerButton = {
					.x =  playButton.x,
					.y =  playButton.y + (2 * buttonSpaceDivisions),
					.width =  playButton.width,
					.height =  playButton.height
			};
			Rectangle volumeSlider = {
					.x =  playButton.x,
					.y =  playButton.y + (3 * buttonSpaceDivisions),
					.width =  playButton.width,
					.height =  playButton.height
			};

			DrawRectangleRec(playButton, GRAY);
			DrawText("PLAY",
				playButton.x + (playButton.width / 2) - (MeasureText("PLAY", buttonFontSize) / 2),
				playButton.y + (playButton.height / 2) - (buttonFontSize / 2),
				buttonFontSize,
				Color{70, 70, 70, 255});
			DrawRectangleRec(leaderboardButton, GRAY);
			DrawText("LEADERBOARDS",
					 leaderboardButton.x + (leaderboardButton.width / 2) - (MeasureText("LEADERBOARDS", buttonFontSize) / 2),
					 leaderboardButton.y + (leaderboardButton.height / 2) - (buttonFontSize / 2),
					 buttonFontSize,
					 Color{70, 70, 70, 255});
			DrawRectangleRec(playerButton, GRAY);
			DrawText("PLAYER",
					 playerButton.x + (playerButton.width / 2) - (MeasureText("PLAYER", buttonFontSize) / 2),
					 playerButton.y + (playerButton.height / 2) - (buttonFontSize / 2),
					 buttonFontSize,
					 Color{70, 70, 70, 255});
			DrawRectangleRec(volumeSlider, GRAY);
			DrawText("VOL PLACEHOLDER",
					 volumeSlider.x + (volumeSlider.width / 2) - (MeasureText("VOL PLACEHOLDER", buttonFontSize) / 2),
					 volumeSlider.y + (volumeSlider.height / 2) - (buttonFontSize / 2),
					 buttonFontSize,
					 Color{70, 70, 70, 255});
		} else if (menu == 1) {
            ClearBackground(RAYWHITE);
            DrawTexture(tempTexture, windowWidth/2 - tempTexture.width/2, windowHeight/2 - tempTexture.height/2, RED);
            DrawTexture(tempTexture2, windowWidth/2 - tempTexture.width/2, windowHeight/2 - tempTexture.height/2, WHITE);
        }
		EndDrawing();
	}

	CloseWindow();
	return 0;
}
