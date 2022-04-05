// Copyright © 2022 Daylon Wilkins & Maxwell Chow
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "gui/sprite.h"
#include "raylib.h"

Sprite::Sprite(Context& ctx, SpriteName spriteName, const Component::Options& options) {
	this->name = spriteName;
	this->options = options;
}

Sprite::~Sprite() {
	unload();
}

int Sprite::Height(Context& ctx) {
	return (int)((float)parent->Height(ctx) * options.HeightScale);
}

int Sprite::Width(Context& ctx) {
	return (int)((float)parent->Width(ctx) * options.WidthScale);
}

void Sprite::Draw(Context& ctx) {
	load(ctx);
	if (ctx.Screen.HasResized()) {
		unload();
		load(ctx);
	}
	int halfWidth = Width(ctx) / 2;
	int halfHeight = Height(ctx) / 2;
	if (colorTex != nullptr) {
		DrawTexture(*colorTex, X() + halfWidth - (colorTex->width / 2), Y() + halfHeight - (colorTex->height / 2), WHITE);
	}
	if (grayTex != nullptr) {
		DrawTexture(*grayTex, X() + halfWidth - (grayTex->width / 2), Y() + halfHeight - (grayTex->height / 2), options.DefaultColor);
	}
	for (auto child: *children) {
		child->DrawComponent(ctx, X() + ((Width(ctx) / 2) - (child->Width(ctx) / 2)), Y() + ((Height(ctx) / 2) - (child->Height(ctx) / 2)));
	}
}

void Sprite::load(Context& ctx) {
	if (colorTex != nullptr) {
		return;
	}

	Image tempColorImg;
	Image tempGrayImg;
	bool hasGray = false;

	switch (name) {
		case SpearGoblin:
			hasGray = true;
			tempColorImg = LoadImage("../assets/enemies/speargoblin/color.png");
			tempGrayImg = LoadImage("../assets/enemies/speargoblin/gray.png");
			break;
		case BearBaby:
			hasGray = true;
			tempColorImg = LoadImage("../assets/enemies/babybearbaby/color.png");
			tempGrayImg = LoadImage("../assets/enemies/babybearbaby/gray.png");
			break;
		case Golem:
			hasGray = true;
			tempColorImg = LoadImage("../assets/enemies/golem/color.png");
			tempGrayImg = LoadImage("../assets/enemies/golem/gray.png");
			break;
		case Dragon:
			hasGray = true;
			tempColorImg = LoadImage("../assets/enemies/dragon/color.png");
			tempGrayImg = LoadImage("../assets/enemies/dragon/gray.png");
			break;
		case Bird:
			hasGray = true;
			tempColorImg = LoadImage("../assets/enemies/bird/color.png");
			tempGrayImg = LoadImage("../assets/enemies/bird/gray.png");
			break;
		case Snake:
			hasGray = true;
			tempColorImg = LoadImage("../assets/enemies/snake/color.png");
			tempGrayImg = LoadImage("../assets/enemies/snake/gray.png");
			break;
		case NoneRune:
			tempColorImg = LoadImage("../assets/runes/none.png");
			break;
		case FireRune:
			tempColorImg = LoadImage("../assets/runes/fire.png");
			break;
		case ElectricRune:
			tempColorImg = LoadImage("../assets/runes/electric.png");
			break;
		case WaterRune:
			tempColorImg = LoadImage("../assets/runes/water.png");
			break;
		case WindRune:
			tempColorImg = LoadImage("../assets/runes/wind.png");
			break;
		case PureRune:
			tempColorImg = LoadImage("../assets/runes/pure.png");
			break;
		case OmniRune:
			tempColorImg = LoadImage("../assets/runes/omni.png");
			break;
		case Backpack:
			tempColorImg = LoadImage("../assets/icons/backpack.png");
			break;
		case Back:
			tempColorImg = LoadImage("../assets/icons/back.png");
			break;
		case Home:
			tempColorImg = LoadImage("../assets/icons/home.png");
			break;
		case SingleEnemy:
			tempColorImg = LoadImage("../assets/targets/singleenemy.png");
			break;
		case AllEnemies:
			tempColorImg = LoadImage("../assets/targets/allenemies.png");
			break;
		case Self:
			tempColorImg = LoadImage("../assets/targets/self.png");
			break;
		case SelfAndSingleEnemy:
			tempColorImg = LoadImage("../assets/targets/selfandsingleenemy.png");
			break;
		case SelfAndAllEnemies:
			tempColorImg = LoadImage("../assets/targets/selfandallenemies.png");
			break;
		case Physical:
			tempColorImg = LoadImage("../assets/attacktypes/physical.png");
			break;
		case Special:
			tempColorImg = LoadImage("../assets/attacktypes/special.png");
			break;
		case Health:
			tempColorImg = LoadImage("../assets/stats/health.png");
			break;
		case PhysicalAttack:
			tempColorImg = LoadImage("../assets/attacktypes/physical.png");
			break;
		case SpecialAttack:
			tempColorImg = LoadImage("../assets/attacktypes/special.png");
			break;
		case PhysicalArmor:
			tempColorImg = LoadImage("../assets/stats/physicalarmor.png");
			break;
		case SpecialArmor:
			tempColorImg = LoadImage("../assets/stats/specialarmor.png");
			break;
		case Speed:
			tempColorImg = LoadImage("../assets/stats/speed.png");
			break;
		case Evasion:
			tempColorImg = LoadImage("../assets/stats/evasion.png");
			break;
		case FireResistance:
			tempColorImg = LoadImage("../assets/stats/fireresistance.png");
			break;
		case WaterResistance:
			tempColorImg = LoadImage("../assets/stats/waterresistance.png");
			break;
		case ElectricResistance:
			tempColorImg = LoadImage("../assets/stats/electricresistance.png");
			break;
		case WindResistance:
			tempColorImg = LoadImage("../assets/stats/windresistance.png");
			break;
		case Lifesteal:
			tempColorImg = LoadImage("../assets/buffdebuff/lifesteal.png");
			break;
		case Lucky:
			tempColorImg = LoadImage("../assets/buffdebuff/lucky.png");
			break;
		case Adrenaline:
			tempColorImg = LoadImage("../assets/buffdebuff/adrenaline.png");
			break;
		case ElementalShield:
			hasGray = true;
			tempColorImg = LoadImage("../assets/buffdebuff/shieldcolor.png");
			tempGrayImg = LoadImage("../assets/buffdebuff/shieldgray.png");
			break;
		case Poison:
			tempColorImg = LoadImage("../assets/buffdebuff/poison.png");
			break;
		case Bleed:
			tempColorImg = LoadImage("../assets/buffdebuff/bleed.png");
			break;
		case Sleep:
			tempColorImg = LoadImage("../assets/buffdebuff/sleep.png");
			break;
		case Sick:
			tempColorImg = LoadImage("../assets/buffdebuff/sick.png");
			break;
	}

	// Scale the image based on the width/height. Use the smallest scaling factor, so that no dimension is larger than our bounds.
	float widthRatio = (float)Width(ctx) / (float)tempColorImg.width;
	float heightRatio = (float)Height(ctx) / (float)tempColorImg.height;
	float ratio = widthRatio;
	if (heightRatio < widthRatio) {
		ratio = heightRatio;
	}
	if (ratio != 1) {
		ImageResizeNN(&tempColorImg, (int)((float)tempColorImg.width * ratio), (int)((float)tempColorImg.height * ratio));
	}
	Texture2D tempColorTex = LoadTextureFromImage(tempColorImg);
	colorTex = new Texture2D{tempColorTex.id, tempColorTex.width, tempColorTex.height, tempColorTex.mipmaps, tempColorTex.format};
	UnloadImage(tempColorImg);

	if (hasGray) {
		if (ratio != 1) {
			// Assume the color and gray images are the same size
			ImageResizeNN(&tempGrayImg, (int)((float)tempGrayImg.width * ratio), (int)((float)tempGrayImg.height * ratio));
		}
		Texture2D tempGrayTex = LoadTextureFromImage(tempGrayImg);
		grayTex = new Texture2D{tempGrayTex.id, tempGrayTex.width, tempGrayTex.height, tempGrayTex.mipmaps, tempGrayTex.format};
		UnloadImage(tempGrayImg);
	}
}

void Sprite::unload() {
	if (colorTex != nullptr) {
		UnloadTexture(*colorTex);
		delete (colorTex);
		colorTex = nullptr;
	}
	if (grayTex != nullptr) {
		UnloadTexture(*grayTex);
		delete (grayTex);
		grayTex = nullptr;
	}
}
