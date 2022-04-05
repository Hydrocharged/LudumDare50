// Copyright © 2022 Daylon Wilkins & Maxwell Chow
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "gui/system.h"
#include "gui/menus.h"
#include "state.h"
#include "rune.h"
#include "enemy.h"
#include "statuseffect.h"

int maxExperienceBar = 10;

void Menu::CombatMenuComponent::Update(Context& ctx) {
	Component::Update(ctx);
	auto ProgressLabel = (Label*)(this->Child(0)->Child(0));
	auto ElapsedLabel = (Label*)(this->Child(0)->Child(2));
	auto HealthLabel = (Label*)(this->Child(2)->Child(0)->Child(0));
	ProgressLabel->SetText(ctx, TextFormat("Progress: %s", ctx.GameState->CurrentRun.ProgressTimeString().c_str()));
	ElapsedLabel->SetText(ctx, TextFormat("Current: %s", ctx.GameState->CurrentRun.ElapsedTimeString().c_str()));
	HealthLabel->SetText(ctx, TextFormat("Health %i/%i", ctx.GameState->CurrentRun.PlayerCharacter.CurrentHealth, ctx.GameState->CurrentRun.PlayerCharacter.Health));
}

void attackingRune0(Context& ctx, Component& component) {
	ctx.GameState->Attack(0);
}

void attackingRune1(Context& ctx, Component& component) {
	ctx.GameState->Attack(1);
}

void attackingRune2(Context& ctx, Component& component) {
	ctx.GameState->Attack(2);
}

void attackingRune3(Context& ctx, Component& component) {
	ctx.GameState->Attack(3);
}

void attackingRune4(Context& ctx, Component& component) {
	ctx.GameState->Attack(4);
}

void attackingRune5(Context& ctx, Component& component) {
	ctx.GameState->Attack(5);
}

Component* Menu::CreateCombatMenu(Context& ctx) {
	auto panel = new Menu::CombatMenuComponent(ctx, {.WidthScale = 1, .HeightScale = 1});
	auto timeRow = new HorizontalPanel(ctx, {.WidthScale = 1, .HeightScale = .05});
	auto enemyRow = new HorizontalPanel(ctx, {.WidthScale = 1, .HeightScale = .39});
	auto healthBar = new ProgressBar(ctx, {.WidthScale = .995, .HeightScale = .033, .DefaultColor = ctx.Colors.HealthBar}, &ctx.GameState->CurrentRun.PlayerCharacter.Health, &ctx.GameState->CurrentRun.PlayerCharacter.CurrentHealth);
	auto experienceBar = new ProgressBar(ctx, {.WidthScale = .995, .HeightScale = .033, .DefaultColor = ctx.Colors.ExperienceBar}, &maxExperienceBar, &ctx.GameState->CurrentRun.PlayerCharacter.Experience);
	auto runeRow = new HorizontalPanel(ctx, {.WidthScale = 1, .HeightScale = .49});
	*panel += timeRow;
	*panel += enemyRow;
	*panel += healthBar;
	*panel += new HorizontalPanel(ctx, {.WidthScale = 1, .HeightScale = .004});;
	*panel += experienceBar;
	*panel += runeRow;

	// Time Row
	*timeRow += new Label(ctx, "Progress: 10m 45.32s", {.WidthScale = .2, .HeightScale = .98, .DefaultColor = WHITE});
	*timeRow += new HorizontalPanel(ctx, {.WidthScale = .55, .HeightScale = 1});
	*timeRow += new Label(ctx, "Current: 11m 17.43s", {.WidthScale = .2, .HeightScale = .98, .DefaultColor = WHITE});

	// Enemy Row
	if (ctx.GameState->CurrentBattle.Enemies.size() == 1) {
		*enemyRow += new VerticalPanel(ctx, {.WidthScale = .3, .HeightScale = 1});
		*enemyRow += ctx.GameState->CurrentBattle.Enemies.at(0)->GenerateComponent(ctx, {.WidthScale = .3, .HeightScale = .9, .DefaultColor = ctx.Colors.EnemyBackground});
		*enemyRow += new VerticalPanel(ctx, {.WidthScale = .3, .HeightScale = 1});
	} else if (ctx.GameState->CurrentBattle.Enemies.size() == 2) {
		*enemyRow += new VerticalPanel(ctx, {.WidthScale = .1, .HeightScale = 1});
		*enemyRow += ctx.GameState->CurrentBattle.Enemies.at(0)->GenerateComponent(ctx, {.WidthScale = .3, .HeightScale = .9, .DefaultColor = ctx.Colors.EnemyBackground});
		*enemyRow += new VerticalPanel(ctx, {.WidthScale = .1, .HeightScale = 1});
		*enemyRow += ctx.GameState->CurrentBattle.Enemies.at(1)->GenerateComponent(ctx, {.WidthScale = .3, .HeightScale = .9, .DefaultColor = ctx.Colors.EnemyBackground});
		*enemyRow += new VerticalPanel(ctx, {.WidthScale = .1, .HeightScale = 1});
	} else if (ctx.GameState->CurrentBattle.Enemies.size() == 3) {
		*enemyRow += ctx.GameState->CurrentBattle.Enemies.at(0)->GenerateComponent(ctx, {.WidthScale = .3, .HeightScale = .9, .DefaultColor = ctx.Colors.EnemyBackground});
		*enemyRow += ctx.GameState->CurrentBattle.Enemies.at(1)->GenerateComponent(ctx, {.WidthScale = .3, .HeightScale = .9, .DefaultColor = ctx.Colors.EnemyBackground});
		*enemyRow += ctx.GameState->CurrentBattle.Enemies.at(2)->GenerateComponent(ctx, {.WidthScale = .3, .HeightScale = .9, .DefaultColor = ctx.Colors.EnemyBackground});
	}

	auto statusEffectsColumn = new VerticalPanel(ctx, {.WidthScale = .05, .HeightScale = 1});
	*enemyRow += statusEffectsColumn;
	auto statusEffectOption = Component::Options{.WidthScale = 1, .HeightScale = .15};
	for (StatusEffectInstance* statusEffect: ctx.GameState->CurrentBattle.StatusEffects) {
		if (statusEffect->IsCaster(ctx, ctx.GameState->CurrentRun.PlayerCharacter) && statusEffect->IsBuff(ctx)) {
			*statusEffectsColumn += statusEffect->StatusEffect.GetSprite(ctx, statusEffectOption);
		} else if (statusEffect->IsTarget(ctx, ctx.GameState->CurrentRun.PlayerCharacter) && !statusEffect->IsBuff(ctx)) {
			*statusEffectsColumn += statusEffect->StatusEffect.GetSprite(ctx, statusEffectOption);
		}
	}

	// Experience Bar
	auto innerHealthBar = new HorizontalPanel(ctx, {.WidthScale = 1, .HeightScale = 1});
	*healthBar += innerHealthBar;
	*innerHealthBar += new Label(ctx, TextFormat("Health %i/%i", ctx.GameState->CurrentRun.PlayerCharacter.CurrentHealth, ctx.GameState->CurrentRun.PlayerCharacter.Health), {.WidthScale = .1, .HeightScale = .95, .DefaultColor = WHITE});
	*innerHealthBar += new HorizontalPanel(ctx, {.WidthScale = .85, .HeightScale = 1});

	// Experience Bar
	auto innerEXPBar = new HorizontalPanel(ctx, {.WidthScale = 1, .HeightScale = 1});
	*experienceBar += innerEXPBar;
	*innerEXPBar += new Label(ctx, TextFormat("Level %i", ctx.GameState->CurrentRun.PlayerCharacter.Level(ctx)), {.WidthScale = .1, .HeightScale = .95, .DefaultColor = WHITE});
	*innerEXPBar += new HorizontalPanel(ctx, {.WidthScale = .85, .HeightScale = 1});

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
	*runeCol1 += ctx.GameState->CurrentRun.PlayerCharacter.Runes[0].GenerateComponent(ctx, runeOptions.WithOnClick(attackingRune0));
	*runeCol1 += ctx.GameState->CurrentRun.PlayerCharacter.Runes[1].GenerateComponent(ctx, runeOptions.WithOnClick(attackingRune1));
	*runeCol2 += ctx.GameState->CurrentRun.PlayerCharacter.Runes[2].GenerateComponent(ctx, runeOptions.WithOnClick(attackingRune2));
	*runeCol2 += ctx.GameState->CurrentRun.PlayerCharacter.Runes[3].GenerateComponent(ctx, runeOptions.WithOnClick(attackingRune3));
	*runeCol3 += ctx.GameState->CurrentRun.PlayerCharacter.Runes[4].GenerateComponent(ctx, runeOptions.WithOnClick(attackingRune4));
	*runeCol3 += ctx.GameState->CurrentRun.PlayerCharacter.Runes[5].GenerateComponent(ctx, runeOptions.WithOnClick(attackingRune5));

	return panel;
}
