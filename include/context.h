// Copyright © 2022 Daylon Wilkins & Maxwell Chow
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef CONTEXT_H
#define CONTEXT_H
#include "raylib/raylib.h"
#include "vector"
#include "string"

// GetRandomDouble returns a double between 0.0 and 1.0 inclusive.
double GetRandomDouble();
std::string GetRuneName();
std::string GetEnemyName();

class Component;

class State;

class Context {
public:
	Context();
	~Context();
	void Initialize();
	void Update();
	void Draw();

	struct Menus {
		friend class Context;

	public:
		enum Index {
			None = -1,
			MainMenu = 0,
			RuneMenu = 1,
			GameOverMenu = 2,
			CombatMenu = 3,
			NewRuneMenu = 4,
			LevelUpMenu = 5,
			PauseMenu = 6
		};
		void Set(Index menuIndex) { currentMenu = menuIndex; }
		Index Current() { return currentMenu; }
		Component* operator[](Index idx) { return menus.at(idx); }

		void ReloadGameOverMenu(Context& ctx);
		void ReloadCombatMenu(Context& ctx);
		void ReloadNewRuneMenu(Context& ctx);
		void ReloadLevelUpMenu(Context& ctx);

	private:
		Index currentMenu = None;
		std::vector<Component*> menus;
		void initialize(Context& ctx);
	};

	struct {
		Color Background = Color{30, 30, 30, 255};
		Color Slider = Color{0, 136, 182, 255};
		Color SliderHover = Color{0, 190, 253, 255};
		Color Button = Color{255, 255, 255, 50};
		Color ButtonHover = Color{255, 255, 255, 100};
		Color InputStepper = Color{255, 255, 255, 100};
		Color InputStepperHover = Color{0, 190, 253, 255};
		Color EnemyBackground = Color{255, 255, 255, 15};

		Color RarityCommon = Color{255, 255, 255, 255};
		Color RarityUncommon = Color{30, 255, 0, 255};
		Color RarityRare = Color{0, 112, 221, 255};
		Color RarityEpic = Color{163, 53, 238, 255};
		Color RarityLegendary = Color{255, 128, 0, 255};

		Color ExperienceBar = Color{30, 180, 30, 255};
		Color HealthBar = Color{180, 30, 30, 255};

		Color ElementFire = Color{194, 0, 0, 255};
		Color ElementWater = Color{41, 121, 255, 255};
		Color ElementElectric = Color{255, 167, 38, 255};
		Color ElementWind = Color{135, 222, 66, 255};
	} Colors;

	struct {
		friend class Context;

	public:
		int Width() const { return width; };
		int Height() const { return height; };
		bool HasResized() const { return width != prevWidth || height != prevHeight; }

	private:
		int width = 0;
		int height = 0;
		int prevWidth = 0;
		int prevHeight = 0;
	} Screen;

	struct {
		friend class Context;

	public:
		int X() { return x; }
		int Y() { return y; }
		bool IsDown() { return down; }
		bool HasClicked() { return clicked; }

	private:
		int x = -2147483648;
		int y = -2147483648;
		bool down = false;
		bool clicked = false;
	} Mouse;

	Menus Menu;
	State* GameState;
	float Volume = 1;
};

#endif //CONTEXT_H
