// Copyright © 2022 Daylon Wilkins & Maxwell Chow
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef SPRITE_H
#define SPRITE_H

#include "raylib.h"
#include "context.h"
#include "component.h"

enum SpriteName {
	// Enemies
	SpearGoblin,
	BearBaby,
	Golem,
	Dragon,
	Bird,
	Snake,

	// Runes
	NoneRune,
	FireRune,
	ElectricRune,
	WaterRune,
	WindRune,
	PureRune,
	OmniRune,

	// Icons
	Backpack,
	Back,
	Home,

	// Targets
	SingleEnemy,
	AllEnemies,
	Self,
	SelfAndSingleEnemy,
	SelfAndAllEnemies,

	// Attack Types
	Physical,
	Special,

	// Stats
	Health,
	PhysicalAttack,
	SpecialAttack,
	PhysicalArmor,
	SpecialArmor,
	Speed,
	Evasion,
	FireResistance,
	WaterResistance,
	ElectricResistance,
	WindResistance,

	// Buffs
	Lifesteal,
	Lucky,
	Adrenaline,
	ElementalShield,

	// Debuffs
	Poison,
	Bleed,
	Sleep,
	Sick,
};

class Sprite : public Component {
public:
	Sprite(Context& ctx, SpriteName spriteName, const Component::Options& options);
	~Sprite();
	int Width(Context& ctx) override;
	int Height(Context& ctx) override;

protected:
	void Draw(Context& ctx) override;

private:
	void load(Context& ctx);
	void unload();

	SpriteName name;
	Texture2D colorTex = {};
	Texture2D grayTex = {};
};

struct TextureKey {
public:
	float Ratio;
	char IsGray;
	SpriteName Name;

	bool operator<(const TextureKey& rhs) const {
		if (this->Name != rhs.Name) {
			return this->Name < rhs.Name;
		} else if (this->IsGray != rhs.IsGray) {
			return this->IsGray < rhs.IsGray;
		} else {
			return this->Ratio < rhs.Ratio;
		}
	}
};

#endif //SPRITE_H
