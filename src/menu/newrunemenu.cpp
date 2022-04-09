// Copyright © 2022 Daylon Wilkins & Maxwell Chow
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "gui/system.h"
#include "gui/menus.h"
#include "rune.h"
#include "state.h"

int maxExpBar2 = 10;

void replacingRune0(Context& ctx, Component& component) {
	ctx.GameState->CurrentRun.ReplacingIndex = (ctx.GameState->CurrentRun.ReplacingIndex == 0) ? -1 : 0;
	ctx.Menu.ReloadNewRuneMenu(ctx);
}

void replacingRune1(Context& ctx, Component& component) {
	ctx.GameState->CurrentRun.ReplacingIndex = (ctx.GameState->CurrentRun.ReplacingIndex == 1) ? -1 : 1;
	ctx.Menu.ReloadNewRuneMenu(ctx);
}

void replacingRune2(Context& ctx, Component& component) {
	ctx.GameState->CurrentRun.ReplacingIndex = (ctx.GameState->CurrentRun.ReplacingIndex == 2) ? -1 : 2;
	ctx.Menu.ReloadNewRuneMenu(ctx);
}

void replacingRune3(Context& ctx, Component& component) {
	ctx.GameState->CurrentRun.ReplacingIndex = (ctx.GameState->CurrentRun.ReplacingIndex == 3) ? -1 : 3;
	ctx.Menu.ReloadNewRuneMenu(ctx);
}

void replacingRune4(Context& ctx, Component& component) {
	ctx.GameState->CurrentRun.ReplacingIndex = (ctx.GameState->CurrentRun.ReplacingIndex == 4) ? -1 : 4;
	ctx.Menu.ReloadNewRuneMenu(ctx);
}

void replacingRune5(Context& ctx, Component& component) {
	ctx.GameState->CurrentRun.ReplacingIndex = (ctx.GameState->CurrentRun.ReplacingIndex == 5) ? -1 : 5;
	ctx.Menu.ReloadNewRuneMenu(ctx);
}

void newRuneCancelClick(Context& ctx, Component& component) {
	ctx.GameState->CurrentRun.ReplacingIndex = -1;
	ctx.GameState->NextRoom();
}

void newRuneConfirmClick(Context& ctx, Component& component) {
	if (ctx.GameState->CurrentRun.ReplacingIndex != -1) {
		ctx.GameState->NextRoom();
	}
}

Component* Menu::CreateNewRuneMenu(Context& ctx) {
	auto panel = new Menu::NewRuneMenuComponent(ctx, {.WidthScale = 1, .HeightScale = 1});
	auto timeRow = new HorizontalPanel(ctx, {.WidthScale = 1, .HeightScale = .05});
	auto newRuneRow = new HorizontalPanel(ctx, {.WidthScale = 1, .HeightScale = .39});
	auto healthBar = new ProgressBar(ctx, {.WidthScale = .995, .HeightScale = .033, .DefaultColor = ctx.Colors.HealthBar}, &ctx.GameState->CurrentRun.PlayerCharacter.Health, &ctx.GameState->CurrentRun.PlayerCharacter.CurrentHealth);
	auto experienceBar = new ProgressBar(ctx, {.WidthScale = .995, .HeightScale = .033, .DefaultColor = ctx.Colors.ExperienceBar}, &maxExpBar2, &ctx.GameState->CurrentRun.PlayerCharacter.Experience);
	auto runeRow = new HorizontalPanel(ctx, {.WidthScale = 1, .HeightScale = .49});
	*panel += timeRow;
	*panel += newRuneRow;
	*panel += healthBar;
	*panel += new HorizontalPanel(ctx, {.WidthScale = 1, .HeightScale = .004});;
	*panel += experienceBar;
	*panel += runeRow;

	// Time Row
	*timeRow += new FunctionLabel(ctx, {.WidthScale = .2, .HeightScale = .98, .DefaultColor = WHITE}, "Progress: 00h 00m 00.00s",
		[](Context& ctx) -> std::string { return TextFormat("Progress: %s", ctx.GameState->CurrentRun.ProgressTimeString().c_str()); });
	*timeRow += new HorizontalPanel(ctx, {.WidthScale = .55, .HeightScale = 1});
	*timeRow += new FunctionLabel(ctx, {.WidthScale = .2, .HeightScale = .98, .DefaultColor = WHITE}, "Current: 00h 00m 00.00s",
		[](Context& ctx) -> std::string { return TextFormat("Current: %s", ctx.GameState->CurrentRun.ElapsedTimeString().c_str()); });

	// New Rune Row
	auto runeButtons = Component::Options{.WidthScale = .2, .HeightScale = .2, .DefaultColor = ctx.Colors.Button, .HoverColor = ctx.Colors.ButtonHover};
	*newRuneRow += (new Button(ctx, runeButtons))->AddChild(new Label(ctx, "Cancel", {.WidthScale = .8, .HeightScale = .8, .DefaultColor = WHITE, .OnClick = newRuneCancelClick}));
	*newRuneRow += ctx.GameState->CurrentRun.AddingRune->GenerateComponent(ctx, {
		.WidthScale = .5,
		.HeightScale = .7,
		.DefaultColor = ctx.Colors.Button});
	*newRuneRow += (new Button(ctx, runeButtons))->AddChild(new Label(ctx, "Confirm", {.WidthScale = .8, .HeightScale = .8, .DefaultColor = WHITE, .OnClick = newRuneConfirmClick}));

	// Health Bar
	auto innerHealthBar = new HorizontalPanel(ctx, {.WidthScale = 1, .HeightScale = 1});
	*healthBar += innerHealthBar;
	*innerHealthBar += new FunctionLabel(ctx, {.WidthScale = .2, .HeightScale = .95, .DefaultColor = WHITE}, "Health 0000/0000",
		 [](Context& ctx) -> std::string { return TextFormat("Health %i/%i", ctx.GameState->CurrentRun.PlayerCharacter.CurrentHealth, ctx.GameState->CurrentRun.PlayerCharacter.Health); });
	*innerHealthBar += new HorizontalPanel(ctx, {.WidthScale = .75, .HeightScale = 1});

	// Experience Bar
	auto innerEXPBar = new HorizontalPanel(ctx, {.WidthScale = 1, .HeightScale = 1});
	*experienceBar += innerEXPBar;
	*innerEXPBar += new FunctionLabel(ctx, {.WidthScale = .13, .HeightScale = .95, .DefaultColor = WHITE}, "Level 000",
		[](Context& ctx) -> std::string { return TextFormat("Level %i",ctx.GameState->CurrentRun.PlayerCharacter.Level(ctx)); });
	*innerEXPBar += new HorizontalPanel(ctx, {.WidthScale = .82, .HeightScale = 1});

	// Rune Row
	auto runeCol1 = new VerticalPanel(ctx, {.WidthScale = .33, .HeightScale = 1});
	auto runeCol2 = new VerticalPanel(ctx, {.WidthScale = .33, .HeightScale = 1});
	auto runeCol3 = new VerticalPanel(ctx, {.WidthScale = .33, .HeightScale = 1});
	*runeRow += runeCol1;
	*runeRow += runeCol2;
	*runeRow += runeCol3;
	auto runeOptions = Component::Options{
		.WidthScale = 1,
		.HeightScale = .48,
		.DefaultColor = ctx.Colors.Button,
		.HoverColor = ctx.Colors.ButtonHover};

	auto runeOptions0 = runeOptions.WithOnClick(replacingRune0);
	auto runeOptions1 = runeOptions.WithOnClick(replacingRune1);
	auto runeOptions2 = runeOptions.WithOnClick(replacingRune2);
	auto runeOptions3 = runeOptions.WithOnClick(replacingRune3);
	auto runeOptions4 = runeOptions.WithOnClick(replacingRune4);
	auto runeOptions5 = runeOptions.WithOnClick(replacingRune5);
	switch (ctx.GameState->CurrentRun.ReplacingIndex) {
		case 0:
			runeOptions0 = runeOptions0.WithDefaultColor(ctx.Colors.ButtonHover);
			break;
		case 1:
			runeOptions1 = runeOptions1.WithDefaultColor(ctx.Colors.ButtonHover);
			break;
		case 2:
			runeOptions2 = runeOptions2.WithDefaultColor(ctx.Colors.ButtonHover);
			break;
		case 3:
			runeOptions3 = runeOptions3.WithDefaultColor(ctx.Colors.ButtonHover);
			break;
		case 4:
			runeOptions4 = runeOptions4.WithDefaultColor(ctx.Colors.ButtonHover);
			break;
		case 5:
			runeOptions5 = runeOptions5.WithDefaultColor(ctx.Colors.ButtonHover);
			break;
	}
	*runeCol1 += ctx.GameState->CurrentRun.PlayerCharacter.Runes[0].GenerateComponent(ctx, runeOptions0);
	*runeCol1 += ctx.GameState->CurrentRun.PlayerCharacter.Runes[1].GenerateComponent(ctx, runeOptions1);
	*runeCol2 += ctx.GameState->CurrentRun.PlayerCharacter.Runes[2].GenerateComponent(ctx, runeOptions2);
	*runeCol2 += ctx.GameState->CurrentRun.PlayerCharacter.Runes[3].GenerateComponent(ctx, runeOptions3);
	*runeCol3 += ctx.GameState->CurrentRun.PlayerCharacter.Runes[4].GenerateComponent(ctx, runeOptions4);
	*runeCol3 += ctx.GameState->CurrentRun.PlayerCharacter.Runes[5].GenerateComponent(ctx, runeOptions5);

	return panel;
}
