// Copyright © 2022 Daylon Wilkins & Maxwell Chow
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef SPRITE_H
#define SPRITE_H

#include "raylib.h"
#include <string>

enum SpriteName {
	None = 0,
    SpearGoblin = 1,
    BearBaby = 2,
    Golem = 3
};

class Sprite {
public:
    Sprite();

	SpriteName name;
    Color color;

    int posX, posY;
private:

};

Sprite::Sprite() {
	name = None;
    color = WHITE;
    posX = 0;
    posY = 0;
}

// Create sprite given a name type and the color for tinting
Sprite& initializeSprite(SpriteName spriteName, Color spriteColor);

// Prints the sprite onto a given location
void printSprite(Sprite sprite);

#endif //SPRITE_H
