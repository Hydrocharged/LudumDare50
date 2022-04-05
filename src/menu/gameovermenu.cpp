// Copyright © 2022 Daylon Wilkins & Maxwell Chow
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "gui/system.h"
#include "gui/menus.h"
#include "state.h"

void gameOverHome(Context& ctx, Component& component) {
	ctx.GameState->NextRoom();
}

Component* Menu::CreateGameOverMenu(Context& ctx) {
	auto gameOverMenu = new VerticalPanel(ctx, {.WidthScale = 1, .HeightScale = 1});
	*gameOverMenu += new Label(ctx, "Game Over", {.WidthScale = .5, .HeightScale = .2, .DefaultColor = WHITE});
	*gameOverMenu += new Label(ctx, ctx.GameState->CurrentRun.ProgressTimeString(), {.WidthScale = .95, .HeightScale = .3, .DefaultColor = WHITE});

	auto titleLevel = new HorizontalPanel(ctx, {.WidthScale = 1, .HeightScale =.15});
	*gameOverMenu += titleLevel;
	*titleLevel += new Label(ctx, "Monsters Slain:", {.WidthScale = .3, .HeightScale = 1, .DefaultColor = WHITE});
	*titleLevel += new Label(ctx, "Bosses Slain:", {.WidthScale = .3, .HeightScale = 1, .DefaultColor = WHITE});

	auto numberLevel = new HorizontalPanel(ctx, {.WidthScale = 1, .HeightScale = .15});
	*gameOverMenu += numberLevel;
	*numberLevel += new Label(ctx, TextFormat("%i", ctx.GameState->CurrentRun.EnemiesKilled), {.WidthScale = .3, .HeightScale = 1, .DefaultColor = WHITE});
	*numberLevel += new Label(ctx, TextFormat("%i", ctx.GameState->CurrentRun.BossesKilled), {.WidthScale = .3, .HeightScale = 1, .DefaultColor = WHITE});

	auto homeButtonRow = new HorizontalPanel(ctx, {.WidthScale = 1, .HeightScale = .15});
	*gameOverMenu += homeButtonRow;
	auto homeButton = new Button(ctx, Component::Options{
		.WidthScale = 0.15,
		.HeightScale = .8,
		.DefaultColor = ctx.Colors.Button,
		.HoverColor = ctx.Colors.ButtonHover});
	auto homeButtonFill = new HorizontalPanel(ctx, {.WidthScale = .8, .HeightScale = 1});
	*homeButtonRow += homeButton;
	*homeButtonRow += homeButtonFill;
	auto homeButtonContents = new HorizontalPanel(ctx, {.WidthScale = .9, .HeightScale = 1});
	*homeButton += homeButtonContents;
	auto homeButtonContentsSprite = new Sprite(ctx, SpriteName::Home, {.WidthScale = 0.4, .HeightScale = 1});
	auto homeButtonContentsLabel = new Label(ctx, "HOME", {.WidthScale = 0.4, .HeightScale = 1, .DefaultColor = WHITE, .OnClick = gameOverHome});
	*homeButtonContents += homeButtonContentsSprite;
	*homeButtonContents += homeButtonContentsLabel;

	return gameOverMenu;
}
