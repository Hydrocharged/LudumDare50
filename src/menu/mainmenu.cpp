// Copyright © 2022 Daylon Wilkins & Maxwell Chow
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "gui/system.h"
#include "gui/menus.h"
#include "state.h"

void mainMenuPlayPressed(Context& ctx, Component& component) {
	ctx.GameState->NextRoom();
}

Component* Menu::CreateMainMenu(Context& ctx) {
	auto mainMenu = new VerticalPanel(ctx, {.WidthScale = 1, .HeightScale = 1});
	auto titlePanel = new VerticalPanel(ctx, {.WidthScale = 1, .HeightScale = 0.4});
	auto buttonPanel = new VerticalPanel(ctx, {.WidthScale = 1, .HeightScale = 0.6});
	*mainMenu += titlePanel;
	*mainMenu += buttonPanel;

	*titlePanel += new Label(ctx, "The Fastest RPG", {.WidthScale = 0.7, .HeightScale = 0.5, .DefaultColor = WHITE});

	*buttonPanel += (new Button(ctx, {
		.WidthScale = 0.4,
		.HeightScale = 0.15,
		.DefaultColor = ctx.Colors.Button,
		.HoverColor = ctx.Colors.ButtonHover,
		.OnClick = mainMenuPlayPressed}))->AddChild(new Label(ctx, "Play", {.WidthScale = 0.7, .HeightScale = 0.7, .DefaultColor = WHITE}));
	auto volumeRow = new HorizontalPanel(ctx, {.WidthScale = 0.7, .HeightScale = 0.15});
	*buttonPanel += volumeRow;
	*volumeRow += new Label(ctx, "Volume", {.WidthScale = 0.3, .HeightScale = 1, .DefaultColor = WHITE});
	*volumeRow += new Slider(ctx, Component::Options{
		.WidthScale = 0.7,
		.HeightScale = 1,
		.DefaultColor = ctx.Colors.Slider,
		.HoverColor = ctx.Colors.SliderHover}, WHITE, &ctx.Volume);
	return mainMenu;
}
