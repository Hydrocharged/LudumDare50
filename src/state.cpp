// Copyright © 2022 Daylon Wilkins & Maxwell Chow
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "state.h"
#include "statuseffect.h"
#include "gui/menus.h"

State::State(Context& ctx) : ctx(ctx) {}

State::~State() {
	for (auto enemy: CurrentBattle.Enemies) {
		delete (enemy);
	}
	CurrentBattle.Enemies.clear();
	for (auto statusEffect: CurrentBattle.StatusEffects) {
		delete (statusEffect);
	}
}

void State::NewGame() {
	this->CurrentRun.ReplacingIndex = -1;
	this->CurrentRun.EnemiesKilled = 0;
	this->CurrentRun.BossesKilled = 0;
	this->CurrentRun.PlayerCharacter.Experience = 0;
	this->CurrentRun.PlayerCharacter.Health = 200;
	this->CurrentRun.PlayerCharacter.CurrentHealth = 200;
	this->CurrentRun.PlayerCharacter.PhysicalAttack = 10;
	this->CurrentRun.PlayerCharacter.SpecialAttack = 10;
	this->CurrentRun.PlayerCharacter.PhysicalArmor = 10;
	this->CurrentRun.PlayerCharacter.SpecialArmor = 10;
	this->CurrentRun.PlayerCharacter.Speed = 10;
	this->CurrentRun.PlayerCharacter.Evasion = 10;
	CurrentRun.ElapsedTime = 0;
	CurrentRun.ProgressTime = 0;
	ChanceProgress.NewRune = 0;
	ChanceProgress.FindBoss = 0;
	ChanceProgress.NextRuneCommon = 0;
	ChanceProgress.NextRuneUncommon = 0;
	ChanceProgress.NextRuneRare = 0;
	ChanceProgress.NextRuneEpic = 0;
	ChanceProgress.NextRuneLegendary = 0;

	this->CurrentRun.PlayerCharacter.Runes[0] = Rune();
	this->CurrentRun.PlayerCharacter.Runes[1] = Rune();
	this->CurrentRun.PlayerCharacter.Runes[2] = Rune();
	this->CurrentRun.PlayerCharacter.Runes[3] = Rune();
	this->CurrentRun.PlayerCharacter.Runes[4] = Rune();
	this->CurrentRun.PlayerCharacter.Runes[5] = Rune();

	this->CurrentRun.PlayerCharacter.Runes[0].Name = "Physical Attack";
	this->CurrentRun.PlayerCharacter.Runes[0].FlatDamage = 10;
	this->CurrentRun.PlayerCharacter.Runes[0].AttackType = RuneAttribute::Physical;
	this->CurrentRun.PlayerCharacter.Runes[0].Target = RuneAttribute::SingleEnemy;

	this->CurrentRun.PlayerCharacter.Runes[1].Name = "Special Attack";
	this->CurrentRun.PlayerCharacter.Runes[1].FlatDamage = 10;
	this->CurrentRun.PlayerCharacter.Runes[1].AttackType = RuneAttribute::Special;
	this->CurrentRun.PlayerCharacter.Runes[1].Target = RuneAttribute::SingleEnemy;

	if (GetRandomValue(0, 1) == 0) {
		this->CurrentRun.PlayerCharacter.Runes[2].Name = "Fire Slash";
		this->CurrentRun.PlayerCharacter.Runes[2].AttackType = RuneAttribute::Physical;
	} else {
		this->CurrentRun.PlayerCharacter.Runes[2].Name = "Fireball";
		this->CurrentRun.PlayerCharacter.Runes[2].AttackType = RuneAttribute::Special;
	}
	this->CurrentRun.PlayerCharacter.Runes[2].FlatDamage = 10;
	this->CurrentRun.PlayerCharacter.Runes[2].Element = RuneAttribute::Fire;
	this->CurrentRun.PlayerCharacter.Runes[2].Target = RuneAttribute::SingleEnemy;

	if (GetRandomValue(0, 1) == 0) {
		this->CurrentRun.PlayerCharacter.Runes[3].Name = "Thunder Slam";
		this->CurrentRun.PlayerCharacter.Runes[3].AttackType = RuneAttribute::Physical;
	} else {
		this->CurrentRun.PlayerCharacter.Runes[3].Name = "Lightning";
		this->CurrentRun.PlayerCharacter.Runes[3].AttackType = RuneAttribute::Special;
	}
	this->CurrentRun.PlayerCharacter.Runes[3].FlatDamage = 10;
	this->CurrentRun.PlayerCharacter.Runes[3].Element = RuneAttribute::Electric;
	this->CurrentRun.PlayerCharacter.Runes[3].Target = RuneAttribute::SingleEnemy;

	if (GetRandomValue(0, 1) == 0) {
		this->CurrentRun.PlayerCharacter.Runes[4].Name = "Water Blade";
		this->CurrentRun.PlayerCharacter.Runes[4].AttackType = RuneAttribute::Physical;
	} else {
		this->CurrentRun.PlayerCharacter.Runes[4].Name = "Drench";
		this->CurrentRun.PlayerCharacter.Runes[4].AttackType = RuneAttribute::Special;
	}
	this->CurrentRun.PlayerCharacter.Runes[4].FlatDamage = 10;
	this->CurrentRun.PlayerCharacter.Runes[4].Element = RuneAttribute::Water;
	this->CurrentRun.PlayerCharacter.Runes[4].Target = RuneAttribute::SingleEnemy;

	if (GetRandomValue(0, 1) == 0) {
		this->CurrentRun.PlayerCharacter.Runes[5].Name = "Wind Slash";
		this->CurrentRun.PlayerCharacter.Runes[5].AttackType = RuneAttribute::Physical;
	} else {
		this->CurrentRun.PlayerCharacter.Runes[5].Name = "Gust";
		this->CurrentRun.PlayerCharacter.Runes[5].AttackType = RuneAttribute::Special;
	}
	this->CurrentRun.PlayerCharacter.Runes[5].FlatDamage = 10;
	this->CurrentRun.PlayerCharacter.Runes[5].Element = RuneAttribute::Wind;
	this->CurrentRun.PlayerCharacter.Runes[5].Target = RuneAttribute::SingleEnemy;
}

void spawnEnemies(Context& ctx) {
	if (!ctx.GameState->CurrentBattle.Enemies.empty()) {
		ctx.GameState->CurrentRun.ProgressTime = ctx.GameState->CurrentBattle.Enemies[0]->EncounterTime;
	}
	for (auto enemy: ctx.GameState->CurrentBattle.Enemies) {
		delete (enemy);
	}
	ctx.GameState->CurrentBattle.Enemies.clear();
	for (auto statusEffect: ctx.GameState->CurrentBattle.StatusEffects) {
		delete (statusEffect);
	}
	ctx.GameState->CurrentBattle.StatusEffects.clear();
	ctx.GameState->CurrentBattle.EnemyTurnSpeeds.clear();
	ctx.GameState->CurrentBattle.PlayerTurnSpeed = 0;

	int enemyCount = 1;
	bool isBoss = false;
	ctx.GameState->ChanceProgress.FindBoss += Chances::Boss;
	double probability = GetRandomDouble();
	if (probability < ctx.GameState->ChanceProgress.FindBoss) {
		ctx.GameState->ChanceProgress.FindBoss = 0;
		isBoss = true;
	} else {
		if (probability <= .005) {
			enemyCount = 3;
		} else if (probability <= .05) {
			enemyCount = 2;
		}
	}

	for (int i = 0; i < enemyCount; i++) {
		auto enemy = new Enemy(ctx, isBoss);
		ctx.GameState->CurrentBattle.Enemies.push_back(enemy);
		ctx.GameState->CurrentBattle.EnemyTurnSpeeds.push_back(enemy->Speed);
	}
}

void State::NextRoom() {
	if (ctx.GameState->CurrentRun.PlayerCharacter.Experience >= 10) {
		ctx.GameState->CurrentRun.PlayerCharacter.Experience = 0;
		ctx.GameState->CurrentRun.PlayerCharacter.CurrentHealth = ctx.GameState->CurrentRun.PlayerCharacter.Health;
		ctx.GameState->CurrentRun.PlayerCharacter.LevelUp(ctx);
		ctx.Menu.Set(Context::Menus::LevelUpMenu);
		ctx.Menu.ReloadLevelUpMenu(ctx);
		((Menu::LevelUpMenuComponent*)ctx.Menu[ctx.Menu.Current()])->RoomLoad(ctx);
		return;
	}
	switch (ctx.Menu.Current()) {
		case Context::Menus::MainMenu:
			NewGame();
			spawnEnemies(ctx);
			ctx.GameState->CurrentRun.PlayerCharacter.CurrentHealth = ctx.GameState->CurrentRun.PlayerCharacter.Health;
			ctx.Menu.Set(Context::Menus::CombatMenu);
			ctx.Menu.ReloadCombatMenu(ctx);
			return;
		case Context::Menus::RuneMenu:
			return;
		case Context::Menus::GameOverMenu:
			ctx.Menu.Set(Context::Menus::MainMenu);
			return;
		case Context::Menus::NewRuneMenu:
			if (ctx.GameState->CurrentRun.ReplacingIndex != -1) {
				ctx.GameState->CurrentRun.PlayerCharacter.Runes[ctx.GameState->CurrentRun.ReplacingIndex] = *ctx.GameState->CurrentRun.AddingRune;
				ctx.GameState->CurrentRun.ReplacingIndex = -1;
			}
			spawnEnemies(ctx);
			ctx.GameState->CurrentRun.PlayerCharacter.CurrentHealth = ctx.GameState->CurrentRun.PlayerCharacter.Health;
			ctx.Menu.Set(Context::Menus::CombatMenu);
			ctx.Menu.ReloadCombatMenu(ctx);
			return;
		case Context::Menus::PauseMenu:
			return;
		case Context::Menus::LevelUpMenu:
		case Context::Menus::CombatMenu:
			double probability = GetRandomDouble();
			ChanceProgress.NewRune += Chances::Rune;
			if (probability <= ChanceProgress.NewRune) {
				ChanceProgress.NewRune = 0;
				this->CurrentRun.ReplacingIndex = -1;
				ctx.GameState->CurrentRun.PlayerCharacter.CurrentHealth = ctx.GameState->CurrentRun.PlayerCharacter.Health;
				probability = GetRandomDouble();
				ChanceProgress.NextRuneLegendary += Chances::RarityLegendary;
				//delete (ctx.GameState->CurrentRun.AddingRune);
				if (probability <= ChanceProgress.NextRuneLegendary) {
					ChanceProgress.NextRuneLegendary = 0;
					ctx.GameState->CurrentRun.AddingRune = new Rune(ctx, RuneAttribute::Legendary);
					ctx.Menu.ReloadNewRuneMenu(ctx);
					ctx.Menu.Set(Context::Menus::NewRuneMenu);
					return;
				}
				ChanceProgress.NextRuneEpic += Chances::RarityEpic;
				if (probability <= ChanceProgress.NextRuneEpic) {
					ChanceProgress.NextRuneEpic = 0;
					ctx.GameState->CurrentRun.AddingRune = new Rune(ctx, RuneAttribute::Epic);
					ctx.Menu.ReloadNewRuneMenu(ctx);
					ctx.Menu.Set(Context::Menus::NewRuneMenu);
					return;
				}
				ChanceProgress.NextRuneRare += Chances::RarityRare;
				if (probability <= ChanceProgress.NextRuneRare) {
					ChanceProgress.NextRuneRare = 0;
					ctx.GameState->CurrentRun.AddingRune = new Rune(ctx, RuneAttribute::Rare);
					ctx.Menu.ReloadNewRuneMenu(ctx);
					ctx.Menu.Set(Context::Menus::NewRuneMenu);
					return;
				}
				ChanceProgress.NextRuneUncommon += Chances::RarityUncommon;
				if (probability <= ChanceProgress.NextRuneUncommon) {
					ChanceProgress.NextRuneUncommon = 0;
					ctx.GameState->CurrentRun.AddingRune = new Rune(ctx, RuneAttribute::Uncommon);
					ctx.Menu.ReloadNewRuneMenu(ctx);
					ctx.Menu.Set(Context::Menus::NewRuneMenu);
					return;
				}
				ctx.GameState->CurrentRun.AddingRune = new Rune(ctx, RuneAttribute::Common);
				ctx.Menu.ReloadNewRuneMenu(ctx);
				ctx.Menu.Set(Context::Menus::NewRuneMenu);
				return;
			} else {
				spawnEnemies(ctx);
				ctx.GameState->CurrentRun.PlayerCharacter.CurrentHealth = ctx.GameState->CurrentRun.PlayerCharacter.Health;
				ctx.Menu.ReloadCombatMenu(ctx);
				ctx.Menu.Set(Context::Menus::CombatMenu);
			}
			break;
	}
}

void calculateAttack(Context& ctx, CharacterInstance& attacker, CharacterInstance& defender, double damage, RuneAttribute::AttackType attackType, RuneAttribute::Element element) {
	for (auto statusEffects: ctx.GameState->CurrentBattle.StatusEffects) {
		statusEffects->PreAttack(ctx, attacker);
	}
	for (auto statusEffects: ctx.GameState->CurrentBattle.StatusEffects) {
		statusEffects->PreHit(ctx, defender);
	}
	if (element != RuneAttribute::Pure) {
		switch (attackType) {
			case RuneAttribute::Physical:
				damage *= attacker.PhysicalAttack;
				damage /= defender.PhysicalArmor;
				break;
			case RuneAttribute::Special:
				damage *= attacker.SpecialAttack;
				damage /= defender.SpecialArmor;
				break;
		}
		switch (element) {
			case RuneAttribute::Fire:
				damage *= 1.0 - defender.FireResistance;
				break;
			case RuneAttribute::Water:
				damage *= 1.0 - defender.WaterResistance;
				break;
			case RuneAttribute::Electric:
				damage *= 1.0 - defender.ElectricResistance;
				break;
			case RuneAttribute::Wind:
				damage *= 1.0 - defender.WindResistance;
				break;
			case RuneAttribute::Omni:
				damage *= (1.0 - defender.FireResistance) + (1.0 - defender.WaterResistance) + (1.0 - defender.ElectricResistance) + (1.0 - defender.WindResistance);
				break;
		}
	}
	if (GetRandomDouble() <= attacker.CritChance) {
		damage *= attacker.CritMultiplier;
	}
	int damageDone = damage;
	defender.Parent.CurrentHealth -= (int)damageDone;
	if (defender.Parent.CurrentHealth < 0) {
		defender.Parent.CurrentHealth = 0;
	}
	for (auto statusEffects: ctx.GameState->CurrentBattle.StatusEffects) {
		statusEffects->PostHit(ctx, defender, (int)damageDone);
	}
	for (auto statusEffects: ctx.GameState->CurrentBattle.StatusEffects) {
		statusEffects->PostAttack(ctx, attacker, (int)damageDone);
	}
}

void State::Attack(int runeIndex) {
	auto rune = &ctx.GameState->CurrentRun.PlayerCharacter.Runes[runeIndex];
	for (StatusEffect* buff: rune->Buffs) {
		bool exists = false;
		for (StatusEffectInstance* instance: ctx.GameState->CurrentBattle.StatusEffects) {
			if (&instance->StatusEffect == buff) {
				exists = true;
				break;
			}
		}
		if (!exists) {
			ctx.GameState->CurrentBattle.StatusEffects.push_back(buff->GetInstance(ctx, ctx.GameState->CurrentRun.PlayerCharacter, ctx.GameState->CurrentRun.PlayerCharacter));
			ctx.Menu.ReloadCombatMenu(ctx);
		}
	}
	std::vector<Character*> targets;
	switch (rune->Target) {
		case RuneAttribute::SingleEnemy:
			for (auto enemy: ctx.GameState->CurrentBattle.Enemies) {
				if (enemy->CurrentHealth > 0) {
					targets.push_back(enemy);
					break;
				}
			}
			break;
		case RuneAttribute::AllEnemies:
			for (auto enemy: ctx.GameState->CurrentBattle.Enemies) {
				if (enemy->CurrentHealth > 0) {
					targets.push_back(enemy);
				}
			}
			break;
		case RuneAttribute::Self:
			targets.push_back(&ctx.GameState->CurrentRun.PlayerCharacter);
			break;
		case RuneAttribute::SelfAndSingleEnemy:
			targets.push_back(&ctx.GameState->CurrentRun.PlayerCharacter);
			for (auto enemy: ctx.GameState->CurrentBattle.Enemies) {
				if (enemy->CurrentHealth > 0) {
					targets.push_back(enemy);
					break;
				}
			}
			break;
		case RuneAttribute::SelfAndAllEnemies:
			targets.push_back(&ctx.GameState->CurrentRun.PlayerCharacter);
			for (auto enemy: ctx.GameState->CurrentBattle.Enemies) {
				if (enemy->CurrentHealth > 0) {
					targets.push_back(enemy);
				}
			}
			break;
	}

	auto attacker = ctx.GameState->CurrentRun.PlayerCharacter.Instance(ctx);
	attacker.CritChance += rune->CritChance;
	attacker.CritMultiplier *= rune->CritMultiplier;
	double startingDamage = rune->FlatDamage + (rune->FlatDamage * 0.05 * rune->AdditionalLevel);

	for (auto targetChar: targets) {
		auto defender = targetChar->Instance(ctx);
		for (StatusEffect* debuff: rune->Debuffs) {
			bool exists = false;
			for (StatusEffectInstance* instance: ctx.GameState->CurrentBattle.StatusEffects) {
				if (&instance->StatusEffect == debuff && targetChar == &instance->Target) {
					exists = true;
					break;
				}
			}
			if (!exists && GetRandomDouble() >= defender.DebuffResistance) {
				ctx.GameState->CurrentBattle.StatusEffects.push_back(debuff->GetInstance(ctx, *targetChar, ctx.GameState->CurrentRun.PlayerCharacter));
				ctx.Menu.ReloadCombatMenu(ctx);
			}
		}
		calculateAttack(ctx, attacker, defender, startingDamage, rune->AttackType, rune->Element);
		if (targetChar->CurrentHealth > targetChar->Health) {
			targetChar->CurrentHealth = targetChar->Health;
		}
	}
	if (ctx.GameState->CurrentRun.PlayerCharacter.CurrentHealth > ctx.GameState->CurrentRun.PlayerCharacter.Health) {
		ctx.GameState->CurrentRun.PlayerCharacter.CurrentHealth = ctx.GameState->CurrentRun.PlayerCharacter.Health;
	}
	if (ctx.GameState->CurrentRun.PlayerCharacter.CurrentHealth <= 0) {
		ctx.GameState->GameOver();
		return;
	}
	bool survivingEnemies = false;
	int bossesKilled = 0;
	for (auto targetChar: ctx.GameState->CurrentBattle.Enemies) {
		if (targetChar->CurrentHealth > 0) {
			survivingEnemies = true;
		}
		if (targetChar->IsBoss) {
			bossesKilled += 1;
		}
	}
	if (!survivingEnemies) {
		ctx.GameState->CurrentRun.PlayerCharacter.Experience += ctx.GameState->CurrentBattle.Enemies.size();
		ctx.GameState->CurrentRun.EnemiesKilled += ctx.GameState->CurrentBattle.Enemies.size();
		ctx.GameState->CurrentRun.BossesKilled += bossesKilled;
		ctx.GameState->NextRoom();
		return;
	}
	for (int i = ctx.GameState->CurrentBattle.StatusEffects.size() - 1; i >= 0; i--) {
		StatusEffectInstance* instance = ctx.GameState->CurrentBattle.StatusEffects[i];
		instance->TurnEnded(ctx, ctx.GameState->CurrentRun.PlayerCharacter);
		if (instance->ShouldRemoveInstance(ctx)) {
			ctx.GameState->CurrentBattle.StatusEffects.erase(ctx.GameState->CurrentBattle.StatusEffects.begin() + i);
			ctx.Menu.ReloadCombatMenu(ctx);
		}
	}
	NextTurn();
}

void State::NextTurn() {
	while (true) {
		ctx.GameState->CurrentBattle.PlayerTurnSpeed += ctx.GameState->CurrentRun.PlayerCharacter.Speed;
		for (int i = 0; i < ctx.GameState->CurrentBattle.Enemies.size(); i++) {
			ctx.GameState->CurrentBattle.EnemyTurnSpeeds[i] += ctx.GameState->CurrentBattle.Enemies[i]->Speed;
		}
		int speedIndex = -1;
		int highestSpeed = ctx.GameState->CurrentBattle.PlayerTurnSpeed;
		for (int i = 0; i < ctx.GameState->CurrentBattle.Enemies.size(); i++) {
			if (ctx.GameState->CurrentBattle.EnemyTurnSpeeds[i] > highestSpeed) {
				speedIndex = i;
				highestSpeed = ctx.GameState->CurrentBattle.EnemyTurnSpeeds[i];
			}
		}
		if (speedIndex == -1) {
			ctx.GameState->CurrentBattle.PlayerTurnSpeed = 0;
			return;
		}
		ctx.GameState->CurrentBattle.EnemyTurnSpeeds[speedIndex] = 0;
		auto enemy = ctx.GameState->CurrentBattle.Enemies[speedIndex];
		auto attacker = enemy->Instance(ctx);
		auto defender = ctx.GameState->CurrentRun.PlayerCharacter.Instance(ctx);
		auto attackType = RuneAttribute::Physical;
		if (attacker.SpecialAttack / defender.SpecialArmor > attacker.PhysicalAttack / defender.PhysicalArmor) {
			attackType = RuneAttribute::Special;
		}
		auto element = RuneAttribute::Fire;
		double elementVal = attacker.FireResistance;
		if (attacker.WaterResistance > elementVal) {
			element = RuneAttribute::Water;
			elementVal = WaterResistance;
		}
		if (attacker.ElectricResistance > elementVal) {
			element = RuneAttribute::Electric;
			elementVal = ElectricResistance;
		}
		if (attacker.WindResistance > elementVal) {
			element = RuneAttribute::Wind;
			elementVal = WindResistance;
		}
		calculateAttack(ctx, attacker, defender, enemy->BaseDamage, attackType, element);

		if (ctx.GameState->CurrentRun.PlayerCharacter.CurrentHealth <= 0) {
			ctx.GameState->GameOver();
			return;
		}
		bool survivingEnemies = false;
		int bossesKilled = 0;
		for (auto targetChar: ctx.GameState->CurrentBattle.Enemies) {
			if (targetChar->CurrentHealth > 0) {
				survivingEnemies = true;
			}
			if (targetChar->IsBoss) {
				bossesKilled += 1;
			}
		}
		if (!survivingEnemies) {
			ctx.GameState->CurrentRun.PlayerCharacter.Experience += ctx.GameState->CurrentBattle.Enemies.size();
			ctx.GameState->CurrentRun.EnemiesKilled += ctx.GameState->CurrentBattle.Enemies.size();
			ctx.GameState->CurrentRun.BossesKilled += bossesKilled;
			ctx.GameState->NextRoom();
			return;
		}

		for (int i = ctx.GameState->CurrentBattle.StatusEffects.size() - 1; i >= 0; i--) {
			StatusEffectInstance* instance = ctx.GameState->CurrentBattle.StatusEffects[i];
			instance->TurnEnded(ctx, *enemy);
			if (instance->ShouldRemoveInstance(ctx)) {
				ctx.GameState->CurrentBattle.StatusEffects.erase(ctx.GameState->CurrentBattle.StatusEffects.begin() + i);
				ctx.Menu.ReloadCombatMenu(ctx);
			}
		}
	}
}

void State::GameOver() {
	for (auto enemy: CurrentBattle.Enemies) {
		delete (enemy);
	}
	CurrentBattle.Enemies.clear();
	for (auto statusEffect: CurrentBattle.StatusEffects) {
		delete (statusEffect);
	}
	CurrentBattle.StatusEffects.clear();
	ctx.Menu.ReloadGameOverMenu(ctx);
	ctx.Menu.Set(Context::Menus::GameOverMenu);
}
