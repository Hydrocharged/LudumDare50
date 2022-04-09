// Copyright © 2022 Daylon Wilkins & Maxwell Chow
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "gui/floatinghorizontalpanel.h"
#include "state.h"

FloatingHorizontalPanel::FloatingHorizontalPanel(Context& ctx, const Component::Options& options, float startX, float startY, float riseAmount) {
	this->options = options;
	targetTime = ctx.GameState->CurrentRun.ElapsedTime + duration;
	this->startX = startX;
	this->startY = startY;
	this->riseAmount = riseAmount;
}

int FloatingHorizontalPanel::Height(Context& ctx) {
	if (parent == nullptr) {
		return (int)((float)ctx.Screen.Height() * options.HeightScale);
	}
	return (int)((float)ctx.Screen.Height() * options.HeightScale);
}

int FloatingHorizontalPanel::Width(Context& ctx) {
	if (parent == nullptr) {
		return (int)((float)ctx.Screen.Width() * options.WidthScale);
	}
	return (int)((float)ctx.Screen.Width() * options.WidthScale);
}

void FloatingHorizontalPanel::Draw(Context& ctx) {
	if (ctx.GameState->CurrentRun.ElapsedTime < targetTime) {
		float timeDelta = (float)(targetTime - ctx.GameState->CurrentRun.ElapsedTime) * (1 / duration);
		float percentage = 1 - (timeDelta * timeDelta);

		int halfHeight = Height(ctx) / 2;
		int totalChildWidth = 0;
		for (auto& child: *children) {
			totalChildWidth += child->Width(ctx);
		}
		int childSpacing = (Width(ctx) - totalChildWidth) / (children->size() + 1);
		int nextChildX = startX + X();
		int nextChildY = ((startY + Y()) - halfHeight) - (percentage * (float)Height(ctx) * riseAmount);
		for (auto& child: *children) {
			nextChildX += childSpacing;
			auto originalAlpha = child->GetOptions().DefaultColor.a;
			child->GetOptions().DefaultColor.a = 255 - ((double)255 * percentage);
			child->DrawComponent(ctx, nextChildX, nextChildY + (halfHeight - (child->Height(ctx) / 2)));
			child->GetOptions().DefaultColor.a = originalAlpha;
			nextChildX += child->Width(ctx);
		}
	} else if (parent == nullptr) {
		ctx.RemoveAnimation(this);
	}
}

unsigned char FloatingHorizontalPanel::parentAlpha(Context& ctx) {
	if (parent == nullptr) {
		return 255;
	}
	return parent->GetOptions().DefaultColor.a;
}
