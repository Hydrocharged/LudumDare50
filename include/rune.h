// Copyright © 2022 Daylon Wilkins & Maxwell Chow
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef RUNE_H
#define RUNE_H
#include "context.h"
#include "gui/system.h"

namespace RuneAttribute {
	enum Target {
		SingleEnemy = 0,
		AllEnemies = 1,
		Self = 2,
		SelfAndSingleEnemy = 3,
		SelfAndAllEnemies = 4
	};

	enum Rarity {
		Common = 0,
		Uncommon = 1,
		Rare = 2,
		Epic = 3,
		Legendary = 4
	};

	enum AttackType {
		Physical = 0,
		Special = 1
	};

	enum Element {
		NoElement = 0,
		Fire = 1,
		Water = 2,
		Electric = 3,
		Wind = 4,
		Omni = 5,
		Pure = 6
	};

	enum StatusEffect {
		NoEffect = 0,
		Lifesteal = 1,
		Lucky = 2,
		Adrenaline = 3,
		Elemental = 4,
		Poison = 5,
		Bleed = 6,
		Sleep = 7,
		Sick = 8,
	};
}

class StatusEffect;

class Rune {
public:
	Rune();
	Rune(Context& ctx, RuneAttribute::Rarity rarity);
	~Rune();
	Component* GenerateComponent(Context& ctx, const Component::Options& options);
	Color GetRarityColor(Context& ctx);
	std::string FormatName(Context& ctx, int additionalLevels);
	std::string FormattedName(Context& ctx);
	std::string EffectText(Context& ctx);
	Sprite* GetSprite(Context& ctx, const Component::Options& options);
	double FireResistance(Context& ctx);
	double WaterResistance(Context& ctx);
	double ElectricResistance(Context& ctx);
	double WindResistance(Context& ctx);

	std::string Name;
	int AdditionalLevel;
	RuneAttribute::Target Target;
	RuneAttribute::Rarity Rarity;
	RuneAttribute::AttackType AttackType;
	RuneAttribute::Element Element;
	double FlatDamage;
	std::vector<StatusEffect*> Buffs;
	std::vector<StatusEffect*> Debuffs;
	double CritChance;
	double CritMultiplier;
};

#endif //RUNE_H
