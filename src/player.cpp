// Copyright © 2022 Daylon Wilkins & Maxwell Chow
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "player.h"

Player::Player() {
	//TODO: something here
}

Player::~Player() {
	//TODO: maybe something here?
}

int Player::Level(Context& ctx) {
	return level;
}

double Player::FireResistance(Context& ctx) {
	double resistance = 0;
	for (int i = 0; i < 6; i++) {
		resistance += Runes[i].FireResistance(ctx);
	}
	return resistance;
}

double Player::WaterResistance(Context& ctx) {
	double resistance = 0;
	for (int i = 0; i < 6; i++) {
		resistance += Runes[i].WaterResistance(ctx);
	}
	return resistance;
}

double Player::ElectricResistance(Context& ctx) {
	double resistance = 0;
	for (int i = 0; i < 6; i++) {
		resistance += Runes[i].ElectricResistance(ctx);
	}
	return resistance;
}

double Player::WindResistance(Context& ctx) {
	double resistance = 0;
	for (int i = 0; i < 6; i++) {
		resistance += Runes[i].WindResistance(ctx);
	}
	return resistance;
}

CharacterInstance& Player::Instance(Context& ctx) {
	instance.MaxHealth = Health;
	instance.PhysicalAttack = PhysicalAttack;
	instance.SpecialAttack = SpecialAttack;
	instance.PhysicalArmor = PhysicalArmor;
	instance.SpecialArmor = SpecialArmor;
	instance.Speed = Speed;
	instance.Evasion = Evasion;
	instance.CritChance = 0;
	instance.CritMultiplier = 1;
	instance.DebuffResistance = 0;
	instance.FireResistance = FireResistance(ctx);
	instance.WaterResistance = WaterResistance(ctx);
	instance.ElectricResistance = ElectricResistance(ctx);
	instance.WindResistance = WindResistance(ctx);
	return instance;
}
