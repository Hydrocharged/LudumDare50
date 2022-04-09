// Copyright © 2022 Daylon Wilkins & Maxwell Chow
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef MENUS_H
#define MENUS_H
#include "verticalpanel.h"
#include "horizontalpanel.h"

namespace Menu {
	Component* CreateMainMenu(Context& ctx);
	Component* CreateRuneMenu(Context& ctx);
	Component* CreateGameOverMenu(Context& ctx);
	Component* CreateCombatMenu(Context& ctx);
	Component* CreateNewRuneMenu(Context& ctx);
	Component* CreateLevelUpMenu(Context& ctx);
	Component* CreatePauseMenu(Context& ctx);

	class CombatMenuComponent : public VerticalPanel {
	public:
		CombatMenuComponent(Context& ctx, const Component::Options& options) : VerticalPanel(ctx, options) {}
	};

	class NewRuneMenuComponent : public VerticalPanel {
	public:
		NewRuneMenuComponent(Context& ctx, const Component::Options& options) : VerticalPanel(ctx, options) {}
	};

	class LevelUpMenuComponent : public VerticalPanel {
	public:
		LevelUpMenuComponent(Context& ctx, const Component::Options& options) : VerticalPanel(ctx, options) {}
		void Update(Context& ctx) override;
		void RoomLoad(Context& ctx);
	};
}

#endif //MENUS_H
