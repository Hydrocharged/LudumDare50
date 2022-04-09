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
	auto healthBar = (new ProgressBar(ctx, {.WidthScale = .995, .HeightScale = .033, .DefaultColor = ctx.Colors.HealthBar}, &ctx.GameState->CurrentRun.PlayerCharacter.Health, &ctx.GameState->CurrentRun.PlayerCharacter.CurrentHealth))->Register(ctx, "CombatHealthBar");
	auto experienceBar = new ProgressBar(ctx, {.WidthScale = .995, .HeightScale = .033, .DefaultColor = ctx.Colors.ExperienceBar}, &maxExperienceBar, &ctx.GameState->CurrentRun.PlayerCharacter.Experience);
	auto runeRow = new HorizontalPanel(ctx, {.WidthScale = 1, .HeightScale = .49});
	*panel += timeRow;
	*panel += enemyRow;
	*panel += healthBar;
	*panel += new HorizontalPanel(ctx, {.WidthScale = 1, .HeightScale = .004});
	*panel += experienceBar;
	*panel += runeRow;

	// Time Row
	*timeRow += new FunctionLabel(ctx, {.WidthScale = .2, .HeightScale = .98, .DefaultColor = WHITE}, "Progress: 00h 00m 00.00s",
		[](Context& ctx) -> std::string { return TextFormat("Progress: %s", ctx.GameState->CurrentRun.ProgressTimeString().c_str()); });
	*timeRow += new HorizontalPanel(ctx, {.WidthScale = .55, .HeightScale = 1});
	*timeRow += new FunctionLabel(ctx, {.WidthScale = .2, .HeightScale = .98, .DefaultColor = WHITE}, "Current: 00h 00m 00.00s",
		[](Context& ctx) -> std::string { return TextFormat("Current: %s", ctx.GameState->CurrentRun.ElapsedTimeString().c_str()); });

	// Enemy Row
	if (ctx.GameState->CurrentBattle.Enemies.size() == 1) {
		*enemyRow += new VerticalPanel(ctx, {.WidthScale = .3, .HeightScale = 1});
		*enemyRow += ctx.GameState->CurrentBattle.Enemies.at(0)->GenerateComponent(ctx, {.WidthScale = .3, .HeightScale = .9, .DefaultColor = ctx.Colors.EnemyBackground})->Register(ctx, "CombatEnemy1");
		*enemyRow += new VerticalPanel(ctx, {.WidthScale = .3, .HeightScale = 1});
	} else if (ctx.GameState->CurrentBattle.Enemies.size() == 2) {
		*enemyRow += new VerticalPanel(ctx, {.WidthScale = .1, .HeightScale = 1});
		*enemyRow += ctx.GameState->CurrentBattle.Enemies.at(0)->GenerateComponent(ctx, {.WidthScale = .3, .HeightScale = .9, .DefaultColor = ctx.Colors.EnemyBackground})->Register(ctx, "CombatEnemy1");
		*enemyRow += new VerticalPanel(ctx, {.WidthScale = .1, .HeightScale = 1});
		*enemyRow += ctx.GameState->CurrentBattle.Enemies.at(1)->GenerateComponent(ctx, {.WidthScale = .3, .HeightScale = .9, .DefaultColor = ctx.Colors.EnemyBackground})->Register(ctx, "CombatEnemy2");
		*enemyRow += new VerticalPanel(ctx, {.WidthScale = .1, .HeightScale = 1});
	} else if (ctx.GameState->CurrentBattle.Enemies.size() == 3) {
		*enemyRow += ctx.GameState->CurrentBattle.Enemies.at(0)->GenerateComponent(ctx, {.WidthScale = .3, .HeightScale = .9, .DefaultColor = ctx.Colors.EnemyBackground})->Register(ctx, "CombatEnemy1");
		*enemyRow += ctx.GameState->CurrentBattle.Enemies.at(1)->GenerateComponent(ctx, {.WidthScale = .3, .HeightScale = .9, .DefaultColor = ctx.Colors.EnemyBackground})->Register(ctx, "CombatEnemy2");
		*enemyRow += ctx.GameState->CurrentBattle.Enemies.at(2)->GenerateComponent(ctx, {.WidthScale = .3, .HeightScale = .9, .DefaultColor = ctx.Colors.EnemyBackground})->Register(ctx, "CombatEnemy3");
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
	*runeCol1 += ctx.GameState->CurrentRun.PlayerCharacter.Runes[0].GenerateComponent(ctx, runeOptions.WithOnClick(attackingRune0));
	*runeCol1 += ctx.GameState->CurrentRun.PlayerCharacter.Runes[1].GenerateComponent(ctx, runeOptions.WithOnClick(attackingRune1));
	*runeCol2 += ctx.GameState->CurrentRun.PlayerCharacter.Runes[2].GenerateComponent(ctx, runeOptions.WithOnClick(attackingRune2));
	*runeCol2 += ctx.GameState->CurrentRun.PlayerCharacter.Runes[3].GenerateComponent(ctx, runeOptions.WithOnClick(attackingRune3));
	*runeCol3 += ctx.GameState->CurrentRun.PlayerCharacter.Runes[4].GenerateComponent(ctx, runeOptions.WithOnClick(attackingRune4));
	*runeCol3 += ctx.GameState->CurrentRun.PlayerCharacter.Runes[5].GenerateComponent(ctx, runeOptions.WithOnClick(attackingRune5));

	return panel;
}
