// Copyright © 2022 Daylon Wilkins & Maxwell Chow
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "gui/sprite.h"
#include "raylib.h"
#include "map"

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

std::map<SpriteName, Image> colors;
std::map<SpriteName, Image> grays;

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
			if (colors.count(name) <= 0) {
				colors[name] = LoadImage("../assets/enemies/speargoblin/color.png");
				grays[name] = LoadImage("../assets/enemies/speargoblin/gray.png");
			}
			tempColorImg = ImageCopy(colors[name]);
			tempGrayImg = ImageCopy(grays[name]);
			break;
		case BearBaby:
			hasGray = true;
			if (colors.count(name) <= 0) {
				colors[name] = LoadImage("../assets/enemies/babybearbaby/color.png");
				grays[name] = LoadImage("../assets/enemies/babybearbaby/gray.png");
			}
			tempColorImg = ImageCopy(colors[name]);
			tempGrayImg = ImageCopy(grays[name]);
			break;
		case Golem:
			hasGray = true;
			if (colors.count(name) <= 0) {
				colors[name] = LoadImage("../assets/enemies/golem/color.png");
				grays[name] = LoadImage("../assets/enemies/golem/gray.png");
			}
			tempColorImg = ImageCopy(colors[name]);
			tempGrayImg = ImageCopy(grays[name]);
			break;
		case Dragon:
			hasGray = true;
			if (colors.count(name) <= 0) {
				colors[name] = LoadImage("../assets/enemies/dragon/color.png");
				grays[name] = LoadImage("../assets/enemies/dragon/gray.png");
			}
			tempColorImg = ImageCopy(colors[name]);
			tempGrayImg = ImageCopy(grays[name]);
			break;
		case Bird:
			hasGray = true;
			if (colors.count(name) <= 0) {
				colors[name] = LoadImage("../assets/enemies/bird/color.png");
				grays[name] = LoadImage("../assets/enemies/bird/gray.png");
			}
			tempColorImg = ImageCopy(colors[name]);
			tempGrayImg = ImageCopy(grays[name]);
			break;
		case Snake:
			hasGray = true;
			if (colors.count(name) <= 0) {
				colors[name] = LoadImage("../assets/enemies/snake/color.png");
				grays[name] = LoadImage("../assets/enemies/snake/gray.png");
			}
			tempColorImg = ImageCopy(colors[name]);
			tempGrayImg = ImageCopy(grays[name]);
			break;
		case NoneRune:
			if (colors.count(name) <= 0) {
				colors[name] = LoadImage("../assets/runes/none.png");
			}
			tempColorImg = ImageCopy(colors[name]);
			break;
		case FireRune:
			if (colors.count(name) <= 0) {
				colors[name] = LoadImage("../assets/runes/fire.png");
			}
			tempColorImg = ImageCopy(colors[name]);
			break;
		case ElectricRune:
			if (colors.count(name) <= 0) {
				colors[name] = LoadImage("../assets/runes/electric.png");
			}
			tempColorImg = ImageCopy(colors[name]);
			break;
		case WaterRune:
			if (colors.count(name) <= 0) {
				colors[name] = LoadImage("../assets/runes/water.png");
			}
			tempColorImg = ImageCopy(colors[name]);
			break;
		case WindRune:
			if (colors.count(name) <= 0) {
				colors[name] = LoadImage("../assets/runes/wind.png");
			}
			tempColorImg = ImageCopy(colors[name]);
			break;
		case PureRune:
			if (colors.count(name) <= 0) {
				colors[name] = LoadImage("../assets/runes/pure.png");
			}
			tempColorImg = ImageCopy(colors[name]);
			break;
		case OmniRune:
			if (colors.count(name) <= 0) {
				colors[name] = LoadImage("../assets/runes/omni.png");
			}
			tempColorImg = ImageCopy(colors[name]);
			break;
		case Backpack:
			if (colors.count(name) <= 0) {
				colors[name] = LoadImage("../assets/icons/backpack.png");
			}
			tempColorImg = ImageCopy(colors[name]);
			break;
		case Back:
			if (colors.count(name) <= 0) {
				colors[name] = LoadImage("../assets/icons/back.png");
			}
			tempColorImg = ImageCopy(colors[name]);
			break;
		case Home:
			if (colors.count(name) <= 0) {
				colors[name] = LoadImage("../assets/icons/home.png");
			}
			tempColorImg = ImageCopy(colors[name]);
			break;
		case SingleEnemy:
			if (colors.count(name) <= 0) {
				colors[name] = LoadImage("../assets/targets/singleenemy.png");
			}
			tempColorImg = ImageCopy(colors[name]);
			break;
		case AllEnemies:
			if (colors.count(name) <= 0) {
				colors[name] = LoadImage("../assets/targets/allenemies.png");
			}
			tempColorImg = ImageCopy(colors[name]);
			break;
		case Self:
			if (colors.count(name) <= 0) {
				colors[name] = LoadImage("../assets/targets/self.png");
			}
			tempColorImg = ImageCopy(colors[name]);
			break;
		case SelfAndSingleEnemy:
			if (colors.count(name) <= 0) {
				colors[name] = LoadImage("../assets/targets/selfandsingleenemy.png");
			}
			tempColorImg = ImageCopy(colors[name]);
			break;
		case SelfAndAllEnemies:
			if (colors.count(name) <= 0) {
				colors[name] = LoadImage("../assets/targets/selfandallenemies.png");
			}
			tempColorImg = ImageCopy(colors[name]);
			break;
		case Physical:
			if (colors.count(name) <= 0) {
				colors[name] = LoadImage("../assets/attacktypes/physical.png");
			}
			tempColorImg = ImageCopy(colors[name]);
			break;
		case Special:
			if (colors.count(name) <= 0) {
				colors[name] = LoadImage("../assets/attacktypes/special.png");
			}
			tempColorImg = ImageCopy(colors[name]);
			break;
		case Health:
			if (colors.count(name) <= 0) {
				colors[name] = LoadImage("../assets/stats/health.png");
			}
			tempColorImg = ImageCopy(colors[name]);
			break;
		case PhysicalAttack:
			if (colors.count(name) <= 0) {
				colors[name] = LoadImage("../assets/attacktypes/physical.png");
			}
			tempColorImg = ImageCopy(colors[name]);
			break;
		case SpecialAttack:
			if (colors.count(name) <= 0) {
				colors[name] = LoadImage("../assets/attacktypes/special.png");
			}
			tempColorImg = ImageCopy(colors[name]);
			break;
		case PhysicalArmor:
			if (colors.count(name) <= 0) {
				colors[name] = LoadImage("../assets/stats/physicalarmor.png");
			}
			tempColorImg = ImageCopy(colors[name]);
			break;
		case SpecialArmor:
			if (colors.count(name) <= 0) {
				colors[name] = LoadImage("../assets/stats/specialarmor.png");
			}
			tempColorImg = ImageCopy(colors[name]);
			break;
		case Speed:
			if (colors.count(name) <= 0) {
				colors[name] = LoadImage("../assets/stats/speed.png");
			}
			tempColorImg = ImageCopy(colors[name]);
			break;
		case Evasion:
			if (colors.count(name) <= 0) {
				colors[name] = LoadImage("../assets/stats/evasion.png");
			}
			tempColorImg = ImageCopy(colors[name]);
			break;
		case FireResistance:
			if (colors.count(name) <= 0) {
				colors[name] = LoadImage("../assets/stats/fireresistance.png");
			}
			tempColorImg = ImageCopy(colors[name]);
			break;
		case WaterResistance:
			if (colors.count(name) <= 0) {
				colors[name] = LoadImage("../assets/stats/waterresistance.png");
			}
			tempColorImg = ImageCopy(colors[name]);
			break;
		case ElectricResistance:
			if (colors.count(name) <= 0) {
				colors[name] = LoadImage("../assets/stats/electricresistance.png");
			}
			tempColorImg = ImageCopy(colors[name]);
			break;
		case WindResistance:
			if (colors.count(name) <= 0) {
				colors[name] = LoadImage("../assets/stats/windresistance.png");
			}
			tempColorImg = ImageCopy(colors[name]);
			break;
		case Lifesteal:
			if (colors.count(name) <= 0) {
				colors[name] = LoadImage("../assets/buffdebuff/lifesteal.png");
			}
			tempColorImg = ImageCopy(colors[name]);
			break;
		case Lucky:
			if (colors.count(name) <= 0) {
				colors[name] = LoadImage("../assets/buffdebuff/lucky.png");
			}
			tempColorImg = ImageCopy(colors[name]);
			break;
		case Adrenaline:
			if (colors.count(name) <= 0) {
				colors[name] = LoadImage("../assets/buffdebuff/adrenaline.png");
			}
			tempColorImg = ImageCopy(colors[name]);
			break;
		case ElementalShield:
			hasGray = true;
			if (colors.count(name) <= 0) {
				colors[name] = LoadImage("../assets/buffdebuff/shieldcolor.png");
				grays[name] = LoadImage("../assets/buffdebuff/shieldgray.png");
			}
			tempColorImg = ImageCopy(colors[name]);
			tempGrayImg = ImageCopy(grays[name]);
			break;
		case Poison:
			if (colors.count(name) <= 0) {
				colors[name] = LoadImage("../assets/buffdebuff/poison.png");
			}
			tempColorImg = ImageCopy(colors[name]);
			break;
		case Bleed:
			if (colors.count(name) <= 0) {
				colors[name] = LoadImage("../assets/buffdebuff/bleed.png");
			}
			tempColorImg = ImageCopy(colors[name]);
			break;
		case Sleep:
			if (colors.count(name) <= 0) {
				colors[name] = LoadImage("../assets/buffdebuff/sleep.png");
			}
			tempColorImg = ImageCopy(colors[name]);
			break;
		case Sick:
			if (colors.count(name) <= 0) {
				colors[name] = LoadImage("../assets/buffdebuff/sick.png");
			}
			tempColorImg = ImageCopy(colors[name]);
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
