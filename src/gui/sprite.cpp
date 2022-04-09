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
	if (colorTex.height != 0) {
		auto tint = WHITE;
		tint.a = options.DefaultColor.a;
		DrawTexture(colorTex, X() + halfWidth - (colorTex.width / 2), Y() + halfHeight - (colorTex.height / 2), tint);
	}
	if (grayTex.height != 0) {
		DrawTexture(grayTex, X() + halfWidth - (grayTex.width / 2), Y() + halfHeight - (grayTex.height / 2), options.DefaultColor);
	}
	for (auto child: *children) {
		child->DrawComponent(ctx, X() + ((Width(ctx) / 2) - (child->Width(ctx) / 2)), Y() + ((Height(ctx) / 2) - (child->Height(ctx) / 2)));
	}
}

#if defined(PLATFORM_WEB)
std::string pathPrefix = "";
#else
std::string pathPrefix = "../";
#endif // PLATFORM_WEB

std::map<SpriteName, Image> colors;
std::map<SpriteName, Image> grays;
std::map<TextureKey, Texture2D> textures;

void Sprite::load(Context& ctx) {
	if (colorTex.height != 0) {
		return;
	}

	Image tempColorImg;
	Image tempGrayImg;
	bool hasGray = false;

	switch (name) {
		case SpearGoblin:
			hasGray = true;
			if (colors.find(name) == colors.end()) {
				colors[name] = LoadImage((pathPrefix + "assets/enemies/speargoblin/color.png").c_str());
				grays[name] = LoadImage((pathPrefix + "assets/enemies/speargoblin/gray.png").c_str());
			}
			tempColorImg = colors[name];
			tempGrayImg = grays[name];
			break;
		case BearBaby:
			hasGray = true;
			if (colors.find(name) == colors.end()) {
				colors[name] = LoadImage((pathPrefix + "assets/enemies/babybearbaby/color.png").c_str());
				grays[name] = LoadImage((pathPrefix + "assets/enemies/babybearbaby/gray.png").c_str());
			}
			tempColorImg = colors[name];
			tempGrayImg = grays[name];
			break;
		case Golem:
			hasGray = true;
			if (colors.find(name) == colors.end()) {
				colors[name] = LoadImage((pathPrefix + "assets/enemies/golem/color.png").c_str());
				grays[name] = LoadImage((pathPrefix + "assets/enemies/golem/gray.png").c_str());
			}
			tempColorImg = colors[name];
			tempGrayImg = grays[name];
			break;
		case Dragon:
			hasGray = true;
			if (colors.find(name) == colors.end()) {
				colors[name] = LoadImage((pathPrefix + "assets/enemies/dragon/color.png").c_str());
				grays[name] = LoadImage((pathPrefix + "assets/enemies/dragon/gray.png").c_str());
			}
			tempColorImg = colors[name];
			tempGrayImg = grays[name];
			break;
		case Bird:
			hasGray = true;
			if (colors.find(name) == colors.end()) {
				colors[name] = LoadImage((pathPrefix + "assets/enemies/bird/color.png").c_str());
				grays[name] = LoadImage((pathPrefix + "assets/enemies/bird/gray.png").c_str());
			}
			tempColorImg = colors[name];
			tempGrayImg = grays[name];
			break;
		case Snake:
			hasGray = true;
			if (colors.find(name) == colors.end()) {
				colors[name] = LoadImage((pathPrefix + "assets/enemies/snake/color.png").c_str());
				grays[name] = LoadImage((pathPrefix + "assets/enemies/snake/gray.png").c_str());
			}
			tempColorImg = colors[name];
			tempGrayImg = grays[name];
			break;
		case NoneRune:
			if (colors.find(name) == colors.end()) {
				colors[name] = LoadImage((pathPrefix + "assets/runes/none.png").c_str());
			}
			tempColorImg = colors[name];
			break;
		case FireRune:
			if (colors.find(name) == colors.end()) {
				colors[name] = LoadImage((pathPrefix + "assets/runes/fire.png").c_str());
			}
			tempColorImg = colors[name];
			break;
		case ElectricRune:
			if (colors.find(name) == colors.end()) {
				colors[name] = LoadImage((pathPrefix + "assets/runes/electric.png").c_str());
			}
			tempColorImg = colors[name];
			break;
		case WaterRune:
			if (colors.find(name) == colors.end()) {
				colors[name] = LoadImage((pathPrefix + "assets/runes/water.png").c_str());
			}
			tempColorImg = colors[name];
			break;
		case WindRune:
			if (colors.find(name) == colors.end()) {
				colors[name] = LoadImage((pathPrefix + "assets/runes/wind.png").c_str());
			}
			tempColorImg = colors[name];
			break;
		case PureRune:
			if (colors.find(name) == colors.end()) {
				colors[name] = LoadImage((pathPrefix + "assets/runes/pure.png").c_str());
			}
			tempColorImg = colors[name];
			break;
		case OmniRune:
			if (colors.find(name) == colors.end()) {
				colors[name] = LoadImage((pathPrefix + "assets/runes/omni.png").c_str());
			}
			tempColorImg = colors[name];
			break;
		case Backpack:
			if (colors.find(name) == colors.end()) {
				colors[name] = LoadImage((pathPrefix + "assets/icons/backpack.png").c_str());
			}
			tempColorImg = colors[name];
			break;
		case Back:
			if (colors.find(name) == colors.end()) {
				colors[name] = LoadImage((pathPrefix + "assets/icons/back.png").c_str());
			}
			tempColorImg = colors[name];
			break;
		case Home:
			if (colors.find(name) == colors.end()) {
				colors[name] = LoadImage((pathPrefix + "assets/icons/home.png").c_str());
			}
			tempColorImg = colors[name];
			break;
		case SingleEnemy:
			if (colors.find(name) == colors.end()) {
				colors[name] = LoadImage((pathPrefix + "assets/targets/singleenemy.png").c_str());
			}
			tempColorImg = colors[name];
			break;
		case AllEnemies:
			if (colors.find(name) == colors.end()) {
				colors[name] = LoadImage((pathPrefix + "assets/targets/allenemies.png").c_str());
			}
			tempColorImg = colors[name];
			break;
		case Self:
			if (colors.find(name) == colors.end()) {
				colors[name] = LoadImage((pathPrefix + "assets/targets/self.png").c_str());
			}
			tempColorImg = colors[name];
			break;
		case SelfAndSingleEnemy:
			if (colors.find(name) == colors.end()) {
				colors[name] = LoadImage((pathPrefix + "assets/targets/selfandsingleenemy.png").c_str());
			}
			tempColorImg = colors[name];
			break;
		case SelfAndAllEnemies:
			if (colors.find(name) == colors.end()) {
				colors[name] = LoadImage((pathPrefix + "assets/targets/selfandallenemies.png").c_str());
			}
			tempColorImg = colors[name];
			break;
		case Physical:
			if (colors.find(name) == colors.end()) {
				colors[name] = LoadImage((pathPrefix + "assets/attacktypes/physical.png").c_str());
			}
			tempColorImg = colors[name];
			break;
		case Special:
			if (colors.find(name) == colors.end()) {
				colors[name] = LoadImage((pathPrefix + "assets/attacktypes/special.png").c_str());
			}
			tempColorImg = colors[name];
			break;
		case Health:
			if (colors.find(name) == colors.end()) {
				colors[name] = LoadImage((pathPrefix + "assets/stats/health.png").c_str());
			}
			tempColorImg = colors[name];
			break;
		case PhysicalAttack:
			if (colors.find(name) == colors.end()) {
				colors[name] = LoadImage((pathPrefix + "assets/attacktypes/physical.png").c_str());
			}
			tempColorImg = colors[name];
			break;
		case SpecialAttack:
			if (colors.find(name) == colors.end()) {
				colors[name] = LoadImage((pathPrefix + "assets/attacktypes/special.png").c_str());
			}
			tempColorImg = colors[name];
			break;
		case PhysicalArmor:
			if (colors.find(name) == colors.end()) {
				colors[name] = LoadImage((pathPrefix + "assets/stats/physicalarmor.png").c_str());
			}
			tempColorImg = colors[name];
			break;
		case SpecialArmor:
			if (colors.find(name) == colors.end()) {
				colors[name] = LoadImage((pathPrefix + "assets/stats/specialarmor.png").c_str());
			}
			tempColorImg = colors[name];
			break;
		case Speed:
			if (colors.find(name) == colors.end()) {
				colors[name] = LoadImage((pathPrefix + "assets/stats/speed.png").c_str());
			}
			tempColorImg = colors[name];
			break;
		case Evasion:
			if (colors.find(name) == colors.end()) {
				colors[name] = LoadImage((pathPrefix + "assets/stats/evasion.png").c_str());
			}
			tempColorImg = colors[name];
			break;
		case FireResistance:
			if (colors.find(name) == colors.end()) {
				colors[name] = LoadImage((pathPrefix + "assets/stats/fireresistance.png").c_str());
			}
			tempColorImg = colors[name];
			break;
		case WaterResistance:
			if (colors.find(name) == colors.end()) {
				colors[name] = LoadImage((pathPrefix + "assets/stats/waterresistance.png").c_str());
			}
			tempColorImg = colors[name];
			break;
		case ElectricResistance:
			if (colors.find(name) == colors.end()) {
				colors[name] = LoadImage((pathPrefix + "assets/stats/electricresistance.png").c_str());
			}
			tempColorImg = colors[name];
			break;
		case WindResistance:
			if (colors.find(name) == colors.end()) {
				colors[name] = LoadImage((pathPrefix + "assets/stats/windresistance.png").c_str());
			}
			tempColorImg = colors[name];
			break;
		case Lifesteal:
			if (colors.find(name) == colors.end()) {
				colors[name] = LoadImage((pathPrefix + "assets/buffdebuff/lifesteal.png").c_str());
			}
			tempColorImg = colors[name];
			break;
		case Lucky:
			if (colors.find(name) == colors.end()) {
				colors[name] = LoadImage((pathPrefix + "assets/buffdebuff/lucky.png").c_str());
			}
			tempColorImg = colors[name];
			break;
		case Adrenaline:
			if (colors.find(name) == colors.end()) {
				colors[name] = LoadImage((pathPrefix + "assets/buffdebuff/adrenaline.png").c_str());
			}
			tempColorImg = colors[name];
			break;
		case ElementalShield:
			hasGray = true;
			if (colors.find(name) == colors.end()) {
				colors[name] = LoadImage((pathPrefix + "assets/buffdebuff/shieldcolor.png").c_str());
				grays[name] = LoadImage((pathPrefix + "assets/buffdebuff/shieldgray.png").c_str());
			}
			tempColorImg = colors[name];
			tempGrayImg = grays[name];
			break;
		case Poison:
			if (colors.find(name) == colors.end()) {
				colors[name] = LoadImage((pathPrefix + "assets/buffdebuff/poison.png").c_str());
			}
			tempColorImg = colors[name];
			break;
		case Bleed:
			if (colors.find(name) == colors.end()) {
				colors[name] = LoadImage((pathPrefix + "assets/buffdebuff/bleed.png").c_str());
			}
			tempColorImg = colors[name];
			break;
		case Sleep:
			if (colors.find(name) == colors.end()) {
				colors[name] = LoadImage((pathPrefix + "assets/buffdebuff/sleep.png").c_str());
			}
			tempColorImg = colors[name];
			break;
		case Sick:
			if (colors.find(name) == colors.end()) {
				colors[name] = LoadImage((pathPrefix + "assets/buffdebuff/sick.png").c_str());
			}
			tempColorImg = colors[name];
			break;
	}

	// Scale the image based on the width/height. Use the smallest scaling factor, so that no dimension is larger than our bounds.
	float widthRatio = (float)Width(ctx) / (float)tempColorImg.width;
	float heightRatio = (float)Height(ctx) / (float)tempColorImg.height;
	float ratio = widthRatio;
	if (heightRatio < widthRatio) {
		ratio = heightRatio;
	}

	auto texColorKey = TextureKey{ratio, 0, name};
	auto texGrayKey = TextureKey{ratio, 1, name};
	if (textures.find(texColorKey) == textures.end()) {
		Image newTempColorImg = ImageCopy(tempColorImg);
		ImageResizeNN(&newTempColorImg, (int)((float)newTempColorImg.width * ratio), (int)((float)newTempColorImg.height * ratio));
		textures[texColorKey] = LoadTextureFromImage(newTempColorImg);
		UnloadImage(newTempColorImg);

		if (hasGray) {
			Image newTempGrayImg = ImageCopy(tempGrayImg);
			ImageResizeNN(&newTempGrayImg, (int)((float)newTempGrayImg.width * ratio), (int)((float)newTempGrayImg.height * ratio));
			textures[texGrayKey] = LoadTextureFromImage(newTempGrayImg);
			UnloadImage(newTempGrayImg);
		}
	}

	colorTex = textures[texColorKey];
	if (hasGray) {
		grayTex = textures[texGrayKey];
	} else {
		options.DefaultColor = WHITE;
	}
}

void Sprite::unload() {
	colorTex = {};
	grayTex = {};
}
