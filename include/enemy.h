// Copyright © 2022 Daylon Wilkins & Maxwell Chow
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef ENEMY_H
#define ENEMY_H
#include "context.h"
#include "character.h"

class Enemy : public Character {
public:
    Enemy(Context& ctx, double currentTime, bool isBoss);
    ~Enemy();
	int Level(Context& ctx) override;
	double FireResistance(Context& ctx) override;
	double WaterResistance(Context& ctx) override;
	double ElectricResistance(Context& ctx) override;
	double WindResistance(Context& ctx) override;
	CharacterInstance& Instance(Context& ctx) override;
	Component* GenerateComponent(Context& ctx, const Component::Options& options);
	Sprite* GetSprite(Context& ctx, const Component::Options& options);

	std::string Name;
	double EncounterTime;
	bool IsBoss;

private:
	SpriteName spriteName;
	double fireResistance;
	double waterResistance;
	double electricResistance;
	double windResistance;
};

#endif //ENEMY_H
