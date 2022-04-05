// Copyright © 2022 Daylon Wilkins & Maxwell Chow
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "statuseffect.h"

StatusEffectInstance* BuffLifesteal::GetInstance(Context& ctx, Character& target, Character& caster) {
	auto instance = new StatusEffectInstance(*this, target, caster);
	instance->TurnsRemaining = Turns;
	return instance;
}
void BuffLifesteal::PreAttack(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance) {}
void BuffLifesteal::PostAttack(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance, int damageDealt) {}
void BuffLifesteal::PreHit(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance) {}
void BuffLifesteal::PostHit(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance, int damageReceived) {
	if (&character.Parent != &instance.Target) {
		return;
	}
	instance.Caster.CurrentHealth += (int)((double)damageReceived * Strength);
	if (instance.Caster.CurrentHealth > instance.Caster.Health) {
		instance.Caster.CurrentHealth = instance.Caster.Health;
	}
}
Sprite* BuffLifesteal::GetSprite(Context& ctx, const Component::Options& options) {
	return new Sprite(ctx, SpriteName::Lifesteal, options);
}
std::string BuffLifesteal::Description(Context& ctx) {
	return TextFormat("Grants a buff giving %03.00f%% life steal for %i turns.", (float)Strength * 100.0f, Turns);
}
bool BuffLifesteal::IsBuff(Context& ctx) { return true; }

StatusEffectInstance* BuffLucky::GetInstance(Context& ctx, Character& target, Character& caster) {
	auto instance = new StatusEffectInstance(*this, target, caster);
	instance->TurnsRemaining = Turns;
	return instance;
}
void BuffLucky::PreAttack(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance) {
	if (&character.Parent == &instance.Caster) {
		character.CritChance += CritChance;
	}
}
void BuffLucky::PostAttack(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance, int damageDealt) {}
void BuffLucky::PreHit(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance) {}
void BuffLucky::PostHit(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance, int damageReceived) {}
Sprite* BuffLucky::GetSprite(Context& ctx, const Component::Options& options) {
	return new Sprite(ctx, SpriteName::Lucky, options);
}
std::string BuffLucky::Description(Context& ctx) {
	return TextFormat("Grants a buff giving %03.00f%% additional Critical Chance for %i turns.", (float)CritChance * 100.0f, Turns);
}
bool BuffLucky::IsBuff(Context& ctx) { return true; }

StatusEffectInstance* BuffAdrenaline::GetInstance(Context& ctx, Character& target, Character& caster) {
	auto instance = new StatusEffectInstance(*this, target, caster);
	instance->TurnsRemaining = Turns;
	return instance;
}

void BuffAdrenaline::PreAttack(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance) {
	if (&character.Parent == &instance.Caster) {
		character.PhysicalAttack = (int)((double)character.PhysicalAttack * (Strength + 1));
		character.SpecialAttack = (int)((double)character.SpecialAttack * (Strength + 1));
	}
}
void BuffAdrenaline::PostAttack(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance, int damageDealt) {}
void BuffAdrenaline::PreHit(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance) {}
void BuffAdrenaline::PostHit(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance, int damageReceived) {}
Sprite* BuffAdrenaline::GetSprite(Context& ctx, const Component::Options& options) {
	return new Sprite(ctx, SpriteName::Adrenaline, options);
}
std::string BuffAdrenaline::Description(Context& ctx) {
	return TextFormat("Grants a buff boosting attack by %03.00f%% for %i turns", (float)Strength, Turns);
}
bool BuffAdrenaline::IsBuff(Context& ctx) { return true; }

StatusEffectInstance* BuffElemental::GetInstance(Context& ctx, Character& target, Character& caster) {
	auto instance = new StatusEffectInstance(*this, target, caster);
	instance->TurnsRemaining = Turns;
	return instance;
}
void BuffElemental::PreAttack(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance) {}
void BuffElemental::PostAttack(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance, int damageDealt) {}
void BuffElemental::PreHit(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance) {
	if (&character.Parent == &instance.Target) {
		switch (Element) {
			case RuneAttribute::Electric:
				character.ElectricResistance += Resistance / 100.0;
				break;
			case RuneAttribute::Water:
				character.WaterResistance += Resistance / 100.0;
				break;
			case RuneAttribute::Wind:
				character.WindResistance += Resistance / 100.0;
				break;
			case RuneAttribute::Fire:
				character.FireResistance += Resistance / 100.0;
				break;
		}
	}
}
void BuffElemental::PostHit(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance, int damageReceived) {}
Sprite* BuffElemental::GetSprite(Context& ctx, const Component::Options& options) {
	auto newOptions = options;
	switch (Element) {
		case RuneAttribute::Electric:
			return new Sprite(ctx, SpriteName::ElementalShield, newOptions.WithDefaultColor(ctx.Colors.ElementElectric));
		case RuneAttribute::Water:
			return new Sprite(ctx, SpriteName::ElementalShield, newOptions.WithDefaultColor(ctx.Colors.ElementWater));
		case RuneAttribute::Wind:
			return new Sprite(ctx, SpriteName::ElementalShield, newOptions.WithDefaultColor(ctx.Colors.ElementWind));
		case RuneAttribute::Fire:
			return new Sprite(ctx, SpriteName::ElementalShield, newOptions.WithDefaultColor(ctx.Colors.ElementFire));
	}
}
std::string BuffElemental::Description(Context& ctx) {
	switch (Element) {
		case RuneAttribute::Electric:
			return TextFormat("Grants a buff boosting Electric resistance by %03.00f%% for %i turns.", (float)Resistance, Turns);
		case RuneAttribute::Water:
			return TextFormat("Grants a buff boosting Water resistance by %03.00f%% for %i turns.", (float)Resistance, Turns);
		case RuneAttribute::Wind:
			return TextFormat("Grants a buff boosting Wind resistance by %03.00f%% for %i turns.", (float)Resistance, Turns);
		case RuneAttribute::Fire:
			return TextFormat("Grants a buff boosting Fire resistance by %03.00f%% for %i turns.", (float)Resistance, Turns);
	}
	return "";
}
bool BuffElemental::IsBuff(Context& ctx) { return true; }

StatusEffectInstance* DebuffPoison::GetInstance(Context& ctx, Character& target, Character& caster) {
	auto instance = new StatusEffectInstance(*this, target, caster);
	instance->TurnsRemaining = Turns;
	return instance;
}
void DebuffPoison::PreAttack(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance) {
	if (&character.Parent == &instance.Target) {
		character.Parent.CurrentHealth -= Strength;
		if (character.Parent.CurrentHealth < 0) {
			character.Parent.CurrentHealth = 0;
		}
	}
}
void DebuffPoison::PostAttack(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance, int damageDealt) {}
void DebuffPoison::PreHit(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance) {}
void DebuffPoison::PostHit(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance, int damageReceived) {}
Sprite* DebuffPoison::GetSprite(Context& ctx, const Component::Options& options) {
	return new Sprite(ctx, SpriteName::Poison, options);
}
std::string DebuffPoison::Description(Context& ctx) {
	return TextFormat("Applies a debuff applying %i poison damage for %i turns.", (int)Strength, Turns);
}
bool DebuffPoison::IsBuff(Context& ctx) { return false; }

StatusEffectInstance* DebuffBleed::GetInstance(Context& ctx, Character& target, Character& caster) {
	auto instance = new StatusEffectInstance(*this, target, caster);
	instance->TurnsRemaining = Turns;
	return instance;
}
void DebuffBleed::PreAttack(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance) {
	if (&character.Parent == &instance.Target) {
		character.Parent.CurrentHealth -= character.MaxHealth * Strength;
		if (character.Parent.CurrentHealth < 0) {
			character.Parent.CurrentHealth = 0;
		}
	}
}
void DebuffBleed::PostAttack(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance, int damageDealt) {}
void DebuffBleed::PreHit(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance) {}
void DebuffBleed::PostHit(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance, int damageReceived) {}
Sprite* DebuffBleed::GetSprite(Context& ctx, const Component::Options& options) {
	return new Sprite(ctx, SpriteName::Bleed, options);
}
std::string DebuffBleed::Description(Context& ctx) {
	return TextFormat("Applies a debuff that causes %02.00f%% of max health damage per turn for %i turns.", (float)Strength * 100.0f, Turns);
}
bool DebuffBleed::IsBuff(Context& ctx) { return false; }

StatusEffectInstance* DebuffSleep::GetInstance(Context& ctx, Character& target, Character& caster) {
	auto instance = new StatusEffectInstance(*this, target, caster);
	instance->TurnsRemaining = Turns;
	return instance;
}
void DebuffSleep::PreAttack(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance) {
	if (&character.Parent == &instance.Target) {
		character.PhysicalAttack = 0;
		character.SpecialAttack = 0;
	}
}
void DebuffSleep::PostAttack(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance, int damageDealt) {}
void DebuffSleep::PreHit(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance) {}
void DebuffSleep::PostHit(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance, int damageReceived) {}
Sprite* DebuffSleep::GetSprite(Context& ctx, const Component::Options& options) {
	return new Sprite(ctx, SpriteName::Sleep, options);
}
std::string DebuffSleep::Description(Context& ctx) {
	return TextFormat("Applies a debuff preventing damage dealing for %i turns.", Turns);
}
bool DebuffSleep::IsBuff(Context& ctx) { return false; }

StatusEffectInstance* DebuffSick::GetInstance(Context& ctx, Character& target, Character& caster) {
	auto instance = new StatusEffectInstance(*this, target, caster);
	instance->TurnsRemaining = Turns;
	return instance;
}
void DebuffSick::PreAttack(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance) {}
void DebuffSick::PostAttack(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance, int damageDealt) {
	if (&character.Parent == &instance.Target) {
		character.Parent.CurrentHealth -= (int)((double)damageDealt * Strength);
		if (character.Parent.CurrentHealth < 0) {
			character.Parent.CurrentHealth = 0;
		}
	}
}
void DebuffSick::PreHit(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance) {}
void DebuffSick::PostHit(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance, int damageReceived) {}
Sprite* DebuffSick::GetSprite(Context& ctx, const Component::Options& options) {
	return new Sprite(ctx, SpriteName::Sick, options);
}
std::string DebuffSick::Description(Context& ctx) {
	return TextFormat("Applies a debuff reflecting %03.00f%% of damage dealt for %i turns.", (float)Strength * 100.0f, Turns);
}
bool DebuffSick::IsBuff(Context& ctx) { return false; }
