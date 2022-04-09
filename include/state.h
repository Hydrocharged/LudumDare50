// Copyright © 2022 Daylon Wilkins & Maxwell Chow
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef STATE_H
#define STATE_H
#include "context.h"
#include "player.h"
#include "enemy.h"

class StatusEffectInstance;

namespace Chances {
	const double Rune = 0.08474409185231704; // 25%
	const double Boss = 0.0038016583035531547; // 5%
	const double RarityCommon = 0.44641928058933833; // 62%
	const double RarityUncommon = 0.08474409185231704; // 25%
	const double RarityRare = 0.014745844781072659; // 10%
	const double RarityEpic = 0.0006200876164358948; // 2%
	const double RarityLegendary = 0.00015604169167720937; // 1%
}

enum CharacterSource {
	PlayerSource = -1,
	Enemy1Source = 0,
	Enemy2Source = 1,
	Enemy3Source = 2,
};

class State {
	friend class Context;

public:
	~State();

	struct {
		double ProgressTime = 0;
		double ElapsedTime = 0;
		Player PlayerCharacter;
		Rune* AddingRune = new Rune();
		int ReplacingIndex;
		int EnemiesKilled = 0;
		int BossesKilled = 0;

		std::string ProgressTimeString() {
			int hours = ProgressTime / 3600;
			int minutes = (int)(ProgressTime / 60) % 60;
			float seconds = (float)(ProgressTime - (double)((hours * 3600) + (minutes * 60)));
			return TextFormat("%02ih %02im %02.02fs", hours, minutes, seconds);
		}
		std::string ElapsedTimeString() {
			int hours = ElapsedTime / 3600;
			int minutes = (int)(ElapsedTime / 60) % 60;
			float seconds = (float)(ElapsedTime - (double)((hours * 3600) + (minutes * 60)));
			return TextFormat("%02ih %02im %02.02fs", hours, minutes, seconds);
		}
	} CurrentRun;

	struct {
		int PlayerTurnSpeed = 0;
		std::vector<Enemy*> Enemies;
		std::vector<int> EnemyTurnSpeeds;
		std::vector<StatusEffectInstance*> StatusEffects;
	} CurrentBattle;

	struct {
		double NewRune = 0;
		double FindBoss = 0;
		double NextRuneCommon = 0;
		double NextRuneUncommon = 0;
		double NextRuneRare = 0;
		double NextRuneEpic = 0;
		double NextRuneLegendary = 0;
	} ChanceProgress;

	void NewGame();
	void NextRoom();
	void NextTurn();
	void GameOver();
	void Attack(int runeIndex);
	CharacterSource GetCharacterSource(Character* character);
	void FloatDamageNumber(CharacterSource charSource, bool hasSprite, SpriteName spriteName, int damageDone);

private:
	explicit State(Context& ctx);
	Context& ctx;
};

#endif //STATE_H
