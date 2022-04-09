// Copyright © 2022 Daylon Wilkins & Maxwell Chow
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "enemy.h"
#include "state.h"
#include "statuseffect.h"

Enemy::Enemy(Context& ctx, bool isBoss) {
	Name = GetEnemyName();
	spriteName = (SpriteName)GetRandomValue(0, 5);
	EncounterTime = ctx.GameState->CurrentRun.ElapsedTime;
	IsBoss = isBoss;
	double points = 36 + EncounterTime * 0.7;
	if (isBoss) {
		Name = "Boss " + Name;
		points *= 1.2;
	}

	// Resistances go from -110% to 110% and give or remove 10% points at the extremes
	double resistance = GetRandomDouble();
	points *= (((resistance * 0.2) - 0.1) * -1.0) + 1.0;
	fireResistance = (2.2 * resistance) - 1.1;
	resistance = GetRandomDouble();
	points *= (((resistance * 0.2) - 0.1) * -1.0) + 1.0;
	waterResistance = (2.2 * resistance) - 1.1;
	resistance = GetRandomDouble();
	points *= (((resistance * 0.2) - 0.1) * -1.0) + 1.0;
	electricResistance = (2.2 * resistance) - 1.1;
	resistance = GetRandomDouble();
	points *= (((resistance * 0.2) - 0.1) * -1.0) + 1.0;
	windResistance = (2.2 * resistance) - 1.1;

	double pointDelta = points * GetRandomRange(0.4, 0.5);
	points -= pointDelta;
	Health = 10.0 * pointDelta + 1.0;
	CurrentHealth = Health;

	pointDelta = points * GetRandomRange(0.4, 0.5);
	points -= pointDelta;
	double* dist = GetRandomDistribution(pointDelta, 2);
	PhysicalAttack = 1 + dist[0];
	SpecialAttack = 1 + dist[1];
	delete[] dist;

	pointDelta = points * GetRandomRange(0.4, 0.5);
	points -= pointDelta;
	dist = GetRandomDistribution(pointDelta, 2);
	PhysicalArmor = 1 + dist[0];
	SpecialArmor = 1 + dist[1];
	delete[] dist;

	pointDelta = points * GetRandomRange(0.4, 0.5);
	points -= pointDelta;
	Speed = pointDelta;
	BaseDamage = points;
}

int Enemy::Level(Context& ctx) {
	return (int)(EncounterTime / 5) + 1;
}

double Enemy::FireResistance(Context& ctx) {
	return fireResistance;
}

double Enemy::WaterResistance(Context& ctx) {
	return waterResistance;
}

double Enemy::ElectricResistance(Context& ctx) {
	return electricResistance;
}

double Enemy::WindResistance(Context& ctx) {
	return windResistance;
}

CharacterInstance& Enemy::Instance(Context& ctx) {
	instance.MaxHealth = Health;
	instance.PhysicalAttack = PhysicalAttack;
	instance.SpecialAttack = SpecialAttack;
	instance.PhysicalArmor = PhysicalArmor;
	instance.SpecialArmor = SpecialArmor;
	instance.Speed = Speed;
	instance.Evasion = 0;
	instance.CritChance = 0;
	instance.CritMultiplier = 1;
	instance.DebuffResistance = (IsBoss) ? .6 : .3;
	instance.FireResistance = fireResistance;
	instance.WaterResistance = waterResistance;
	instance.ElectricResistance = electricResistance;
	instance.WindResistance = windResistance;
	return instance;
}

Sprite* Enemy::GetSprite(Context& ctx, const Component::Options& options) {
	Color color = WHITE;
	if (!(fireResistance == waterResistance && waterResistance == electricResistance && electricResistance == windResistance)) {
		RuneAttribute::Element leadingElement = RuneAttribute::Element::Fire;
		double leadingElementVal = fireResistance;
		if (waterResistance > leadingElementVal) {
			leadingElement = RuneAttribute::Element::Water;
			leadingElementVal = waterResistance;
		}
		if (electricResistance > leadingElementVal) {
			leadingElement = RuneAttribute::Element::Electric;
			leadingElementVal = electricResistance;
		}
		if (windResistance > leadingElementVal) {
			leadingElement = RuneAttribute::Element::Wind;
			leadingElementVal = windResistance;
		}
		switch (leadingElement) {
			case RuneAttribute::Fire:
				color = ctx.Colors.ElementFire;
				break;
			case RuneAttribute::Water:
				color = ctx.Colors.ElementWater;
				break;
			case RuneAttribute::Electric:
				color = ctx.Colors.ElementElectric;
				break;
			case RuneAttribute::Wind:
				color = ctx.Colors.ElementWind;
				break;
		}
	}
	Component::Options newOptions = options;
	return new Sprite(ctx, spriteName, newOptions.WithDefaultColor(color));
}

Component* Enemy::GenerateComponent(Context& ctx, const Component::Options& options) {
	auto panel = new VerticalPanel(ctx, options);
	auto topRow = new Label(ctx, TextFormat("Lv. %i %s", Level(ctx), Name.c_str()), {.WidthScale = 1, .HeightScale = .15, .DefaultColor = WHITE});
	auto healthRow = new ProgressBar(ctx, {.WidthScale = .98, .HeightScale = .13, .DefaultColor = ctx.Colors.HealthBar}, &Health, &CurrentHealth);
	auto spriteRow = new HorizontalPanel(ctx, {.WidthScale = 1, .HeightScale = .55});
	auto resistancesRow = new HorizontalPanel(ctx, {.WidthScale = 1, .HeightScale = .10});
	auto statusEffectsRow = new HorizontalPanel(ctx, {.WidthScale = 1, .HeightScale = .07});
	*panel += topRow;
	*panel += healthRow;
	*panel += spriteRow;
	*panel += resistancesRow;
	*panel += statusEffectsRow;

	// Sprite Row
	*spriteRow += GetSprite(ctx, {.WidthScale = .7, .HeightScale = 1});
	auto attackArmorColumn = new HorizontalPanel(ctx, {.WidthScale = .3, .HeightScale = .98});
	*spriteRow += attackArmorColumn;
	auto physicalColumn = new VerticalPanel(ctx, {.WidthScale = .5, .HeightScale = 1});
	auto specialColumn = new VerticalPanel(ctx, {.WidthScale = .5, .HeightScale = 1});
	*attackArmorColumn += physicalColumn;
	*attackArmorColumn += specialColumn;
	*physicalColumn += new Sprite(ctx, SpriteName::PhysicalAttack, {.WidthScale = 1, .HeightScale = .25});
	*physicalColumn += new Label(ctx, TextFormat("%i", (int)((PhysicalAttack * BaseDamage) / ctx.GameState->CurrentRun.PlayerCharacter.PhysicalArmor)), {.WidthScale = 1, .HeightScale = .25, .DefaultColor = WHITE});
	*specialColumn += new Sprite(ctx, SpriteName::SpecialAttack, {.WidthScale = 1, .HeightScale = .25});
	*specialColumn += new Label(ctx, TextFormat("%i", (int)((SpecialAttack * BaseDamage) / ctx.GameState->CurrentRun.PlayerCharacter.SpecialArmor)), {.WidthScale = 1, .HeightScale = .25, .DefaultColor = WHITE});
	*physicalColumn += new Sprite(ctx, SpriteName::PhysicalArmor, {.WidthScale = 1, .HeightScale = .25});
	*physicalColumn += new Label(ctx, TextFormat("%i", PhysicalArmor), {.WidthScale = 1, .HeightScale = .25, .DefaultColor = WHITE});
	*specialColumn += new Sprite(ctx, SpriteName::SpecialArmor, {.WidthScale = 1, .HeightScale = .25});
	*specialColumn += new Label(ctx, TextFormat("%i", SpecialArmor), {.WidthScale = 1, .HeightScale = .25, .DefaultColor = WHITE});

	// Resistances Row
	auto resistanceSpriteOption = Component::Options{.WidthScale = .1, .HeightScale = 1};
	auto resistanceLabelOption = Component::Options{.WidthScale = .15, .HeightScale = 1, .DefaultColor = WHITE};
	*resistancesRow += new Sprite(ctx, SpriteName::FireResistance, resistanceSpriteOption);
	*resistancesRow += new Label(ctx, TextFormat("%i%%", (int)(100.0 * fireResistance)), resistanceLabelOption);
	*resistancesRow += new Sprite(ctx, SpriteName::WaterResistance, resistanceSpriteOption);
	*resistancesRow += new Label(ctx, TextFormat("%i%%", (int)(100.0 * waterResistance)), resistanceLabelOption);
	*resistancesRow += new Sprite(ctx, SpriteName::ElectricResistance, resistanceSpriteOption);
	*resistancesRow += new Label(ctx, TextFormat("%i%%", (int)(100.0 * electricResistance)), resistanceLabelOption);
	*resistancesRow += new Sprite(ctx, SpriteName::WindResistance, resistanceSpriteOption);
	*resistancesRow += new Label(ctx, TextFormat("%i%%", (int)(100.0 * windResistance)), resistanceLabelOption);

	// Buff/Debuff Row
	auto statusEffectOption = Component::Options{.WidthScale = .1, .HeightScale = 1};
	for (StatusEffectInstance* statusEffect: ctx.GameState->CurrentBattle.StatusEffects) {
		if (statusEffect->IsCaster(ctx, *this) && statusEffect->IsBuff(ctx)) {
			*statusEffectsRow += statusEffect->StatusEffect.GetSprite(ctx, statusEffectOption);
		} else if (statusEffect->IsTarget(ctx, *this) && !statusEffect->IsBuff(ctx)) {
			*statusEffectsRow += statusEffect->StatusEffect.GetSprite(ctx, statusEffectOption);
		}
	}

	return panel;
}
