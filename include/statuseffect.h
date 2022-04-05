// Copyright © 2022 Daylon Wilkins & Maxwell Chow
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef STATUSEFFECT_H
#define STATUSEFFECT_H
#include "character.h"
#include "state.h"

class StatusEffectInstance;

class StatusEffect {
public:
	virtual ~StatusEffect() {}
	virtual StatusEffectInstance* GetInstance(Context& ctx, Character& target, Character& caster) = 0;
	virtual void PreAttack(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance) = 0;
	virtual void PostAttack(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance, int damageDealt) = 0;
	virtual void PreHit(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance) = 0;
	virtual void PostHit(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance, int damageReceived) = 0;
	virtual bool IsBuff(Context& ctx) = 0;
	virtual Sprite* GetSprite(Context& ctx, const Component::Options& options) = 0;
	virtual std::string Description(Context& ctx) = 0;
};

class StatusEffectInstance {
public:
	StatusEffectInstance(StatusEffect& status, Character& target, Character& caster) : StatusEffect(status), Target(target), Caster(caster) {};
	void PreAttack(Context& ctx, CharacterInstance& character) { StatusEffect.PreAttack(ctx, character, *this); };
	void PostAttack(Context& ctx, CharacterInstance& character, int damageDealt) { StatusEffect.PostAttack(ctx, character, *this, damageDealt); };
	void PreHit(Context& ctx, CharacterInstance& character) { StatusEffect.PreHit(ctx, character, *this); };
	void PostHit(Context& ctx, CharacterInstance& character, int damageReceived) { StatusEffect.PostHit(ctx, character, *this, damageReceived); };
	bool IsCaster(Context& ctx, Character& character) { return &Caster == &character; }
	bool IsTarget(Context& ctx, Character& character) { return &Target == &character; }
	bool IsBuff(Context& ctx) { return StatusEffect.IsBuff(ctx); }
	bool ShouldRemoveInstance(Context& ctx) { return TurnsRemaining != -1 && TurnsRemaining <= 0; }
	void TurnEnded(Context& ctx, Character& character) {
		if (TurnsRemaining > 0 && ((IsCaster(ctx, character) && IsBuff(ctx)) || (IsTarget(ctx, character) && !IsBuff(ctx)))) {
			TurnsRemaining -= 1;
		}
	}

	StatusEffect& StatusEffect;
	Character& Target;
	Character& Caster;
	int TurnsRemaining;
};

class BuffLifesteal : public StatusEffect {
public:
	BuffLifesteal(Context& ctx, double strength, int turns) : Strength(strength), Turns(turns) {}

	StatusEffectInstance* GetInstance(Context& ctx, Character& target, Character& caster) override;
	void PreAttack(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance) override;
	void PostAttack(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance, int damageDealt) override;
	void PreHit(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance) override;
	void PostHit(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance, int damageReceived) override;
	Sprite* GetSprite(Context& ctx, const Component::Options& options) override;
	std::string Description(Context& ctx) override;
	bool IsBuff(Context& ctx) override;

	double Strength;
	int Turns;
};

class BuffLucky : public StatusEffect {
public:
	BuffLucky(Context& ctx, double critChance, int turns) : CritChance(critChance), Turns(turns) {}

	StatusEffectInstance* GetInstance(Context& ctx, Character& target, Character& caster) override;
	void PreAttack(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance) override;
	void PostAttack(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance, int damageDealt) override;
	void PreHit(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance) override;
	void PostHit(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance, int damageReceived) override;
	Sprite* GetSprite(Context& ctx, const Component::Options& options) override;
	std::string Description(Context& ctx) override;
	bool IsBuff(Context& ctx) override;

	double CritChance;
	int Turns;
};

class BuffAdrenaline : public StatusEffect {
public:
	BuffAdrenaline(Context& ctx, double strength, int turns) : Strength(strength), Turns(turns) {}

	StatusEffectInstance* GetInstance(Context& ctx, Character& target, Character& caster) override;
	void PreAttack(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance) override;
	void PostAttack(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance, int damageDealt) override;
	void PreHit(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance) override;
	void PostHit(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance, int damageReceived) override;
	Sprite* GetSprite(Context& ctx, const Component::Options& options) override;
	std::string Description(Context& ctx) override;
	bool IsBuff(Context& ctx) override;

	double Strength;
	int Turns;
};

class BuffElemental : public StatusEffect {
public:
	BuffElemental(Context& ctx, RuneAttribute::Element element, double resistance, int turns) : Element(element), Resistance(resistance), Turns(turns) {}

	StatusEffectInstance* GetInstance(Context& ctx, Character& target, Character& caster) override;
	void PreAttack(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance) override;
	void PostAttack(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance, int damageDealt) override;
	void PreHit(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance) override;
	void PostHit(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance, int damageReceived) override;
	Sprite* GetSprite(Context& ctx, const Component::Options& options) override;
	std::string Description(Context& ctx) override;
	bool IsBuff(Context& ctx) override;

	RuneAttribute::Element Element;
	double Resistance;
	int Turns;
};

class DebuffPoison : public StatusEffect {
public:
	DebuffPoison(Context& ctx, double strength, int turns) : Strength(strength), Turns(turns) {}

	StatusEffectInstance* GetInstance(Context& ctx, Character& target, Character& caster) override;
	void PreAttack(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance) override;
	void PostAttack(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance, int damageDealt) override;
	void PreHit(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance) override;
	void PostHit(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance, int damageReceived) override;
	Sprite* GetSprite(Context& ctx, const Component::Options& options) override;
	std::string Description(Context& ctx) override;
	bool IsBuff(Context& ctx) override;

	double Strength;
	int Turns;
};

class DebuffBleed : public StatusEffect {
public:
	DebuffBleed(Context& ctx, double strength, int turns) : Strength(strength), Turns(turns) {}

	StatusEffectInstance* GetInstance(Context& ctx, Character& target, Character& caster) override;
	void PreAttack(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance) override;
	void PostAttack(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance, int damageDealt) override;
	void PreHit(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance) override;
	void PostHit(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance, int damageReceived) override;
	Sprite* GetSprite(Context& ctx, const Component::Options& options) override;
	std::string Description(Context& ctx) override;
	bool IsBuff(Context& ctx) override;

	double Strength;
	int Turns;
};

class DebuffSleep : public StatusEffect {
public:
	DebuffSleep(Context& ctx, int turns) : Turns(turns) {}

	StatusEffectInstance* GetInstance(Context& ctx, Character& target, Character& caster) override;
	void PreAttack(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance) override;
	void PostAttack(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance, int damageDealt) override;
	void PreHit(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance) override;
	void PostHit(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance, int damageReceived) override;
	Sprite* GetSprite(Context& ctx, const Component::Options& options) override;
	std::string Description(Context& ctx) override;
	bool IsBuff(Context& ctx) override;

	int Turns;
};

class DebuffSick : public StatusEffect {
public:
	DebuffSick(Context& ctx, double strength, int turns) : Strength(strength), Turns(turns) {}

	StatusEffectInstance* GetInstance(Context& ctx, Character& target, Character& caster) override;
	void PreAttack(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance) override;
	void PostAttack(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance, int damageDealt) override;
	void PreHit(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance) override;
	void PostHit(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance, int damageReceived) override;
	Sprite* GetSprite(Context& ctx, const Component::Options& options) override;
	std::string Description(Context& ctx) override;
	bool IsBuff(Context& ctx) override;

	double Strength;
	int Turns;
};

#endif //STATUSEFFECT_H
