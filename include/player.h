// Copyright © 2022 Daylon Wilkins & Maxwell Chow
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef PLAYER_H
#define PLAYER_H
#include "character.h"

class Player : public Character {
public:
	Player();
	~Player();
	int Level(Context& ctx) override;
	double FireResistance(Context& ctx) override;
	double WaterResistance(Context& ctx) override;
	double ElectricResistance(Context& ctx) override;
	double WindResistance(Context& ctx) override;
	CharacterInstance& Instance(Context& ctx) override;

	int Experience;
	int Evasion;
	Rune Runes[6];

private:
	int level;
};

#endif //PLAYER_H
