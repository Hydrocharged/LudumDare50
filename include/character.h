// Copyright © 2022 Daylon Wilkins & Maxwell Chow
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef CHARACTER_H
#define CHARACTER_H
#include "context.h"
#include "rune.h"

class Character;

class StatusEffectInstance;

struct CharacterInstance {
	explicit CharacterInstance(Character& parent) : Parent(parent) {}

	Character& Parent;
	int MaxHealth = 0;
	int PhysicalAttack = 0;
	int SpecialAttack = 0;
	int PhysicalArmor = 0;
	int SpecialArmor = 0;
	int Speed = 0;
	int Evasion = 0;
	double CritChance = 0;
	double CritMultiplier = 0;
	double DebuffResistance = 0;
	double FireResistance = 0;
	double WaterResistance = 0;
	double ElectricResistance = 0;
	double WindResistance = 0;
};

class Character {
public:
	Character() : instance(*this) {}
	virtual int Level(Context& ctx) = 0;
	virtual double FireResistance(Context& ctx) = 0;
	virtual double WaterResistance(Context& ctx) = 0;
	virtual double ElectricResistance(Context& ctx) = 0;
	virtual double WindResistance(Context& ctx) = 0;
	virtual CharacterInstance& Instance(Context& ctx) = 0;

public:
	int Health = 0;
	int CurrentHealth = 0;
	int PhysicalAttack = 0;
	int SpecialAttack = 0;
	int PhysicalArmor = 0;
	int SpecialArmor = 0;
	int Speed = 0;

protected:
	CharacterInstance instance;
};

#endif //CHARACTER_H
