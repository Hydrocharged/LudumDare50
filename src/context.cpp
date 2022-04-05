// Copyright © 2022 Daylon Wilkins & Maxwell Chow
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "context.h"
#include "gui/menus.h"
#include "state.h"
#include "cmath"
#include "statuseffect.h"
#include "queue"

std::queue<Component*> toDelete;

Context::Context() {
	GameState = new State(*this);
	Screen.width = 1280;
	Screen.height = 720;
}

Context::~Context() {
	for (auto menu: Menu.menus) {
		delete (menu);
	}
	delete (this->GameState);
	while (!toDelete.empty()) {
		delete (toDelete.front());
		toDelete.pop();
	}
}

void Context::Initialize() {
	this->Menu.initialize(*this);
}

void Context::Update() {
	while (!toDelete.empty()) {
		delete (toDelete.front());
		toDelete.pop();
	}

	// Screen
	Screen.prevWidth = Screen.width;
	Screen.prevHeight = Screen.height;
	Screen.width = GetScreenWidth();
	Screen.height = GetScreenHeight();

	// Mouse
	auto mousePos = GetMousePosition();
	int prevMouseX = Mouse.x;
	int prevMouseY = Mouse.y;
	Mouse.x = (int)mousePos.x;
	Mouse.y = (int)mousePos.y;
	bool prevMouseDown = Mouse.down;
	Mouse.down = IsMouseButtonDown(MOUSE_BUTTON_LEFT);
	if (prevMouseDown && !Mouse.down && (abs(Mouse.x - prevMouseX) + abs(Mouse.y - prevMouseY)) <= 4) {
		Mouse.clicked = true;
	} else {
		Mouse.clicked = false;
	}

	if (Menu.currentMenu >= 0) {
		Menu.menus.at(Menu.currentMenu)->Update(*this);
	}

	// Time
	GameState->CurrentRun.ElapsedTime += GetFrameTime();
}

void Context::Draw() {
	if (Menu.currentMenu >= 0) {
		Menu.menus.at(Menu.currentMenu)->DrawComponent(*this, 0, 0);
	}
}

void Context::Menus::initialize(Context& ctx) {
	// ENSURE that the menu order here matches the Menu::Index enumerated order
	menus.push_back(Menu::CreateMainMenu(ctx));
	menus.push_back(Menu::CreateRuneMenu(ctx));
	menus.push_back(Menu::CreateGameOverMenu(ctx));
	menus.push_back(Menu::CreateCombatMenu(ctx));
	menus.push_back(Menu::CreateNewRuneMenu(ctx));
	menus.push_back(Menu::CreateLevelUpMenu(ctx));
	menus.push_back(Menu::CreatePauseMenu(ctx));
	currentMenu = Menus::MainMenu;
}

void Context::Menus::ReloadGameOverMenu(Context& ctx) {
	Component* original = menus.at(2);
	toDelete.push(original);
	menus[2] = Menu::CreateGameOverMenu(ctx);
}

void Context::Menus::ReloadCombatMenu(Context& ctx) {
	Component* original = menus.at(3);
	toDelete.push(original);
	menus[3] = Menu::CreateCombatMenu(ctx);
}

void Context::Menus::ReloadNewRuneMenu(Context& ctx) {
	Component* original = menus.at(4);
	toDelete.push(original);
	menus[4] = Menu::CreateNewRuneMenu(ctx);
}

void Context::Menus::ReloadLevelUpMenu(Context& ctx) {
	Component* original = menus.at(5);
	toDelete.push(original);
	menus[5] = Menu::CreateLevelUpMenu(ctx);
}
