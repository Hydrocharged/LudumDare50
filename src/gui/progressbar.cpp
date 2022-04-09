// Copyright © 2022 Daylon Wilkins & Maxwell Chow
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "gui/progressbar.h"
#include "state.h"

ProgressBar::ProgressBar(Context& ctx, const Component::Options& options, int* maxValue, int* currentValue) {
	this->options = options;
	this->maxValue = maxValue;
	this->currentValue = currentValue;
	this->lastCurrentValue = *currentValue;
	this->fromValue = *currentValue;
	this->targetTime = -1;
}

int ProgressBar::Height(Context& ctx) {
	return (int)((float)parent->Height(ctx) * options.HeightScale);
}

int ProgressBar::Width(Context& ctx) {
	return (int)((float)parent->Width(ctx) * options.WidthScale);
}

void ProgressBar::Draw(Context& ctx) {
	if (lastCurrentValue != *currentValue) {
		targetTime = ctx.GameState->CurrentRun.ElapsedTime + duration;
		fromValue = lastCurrentValue;
		lastCurrentValue = *currentValue;
	}
	double displayValue = *currentValue;
	if (ctx.GameState->CurrentRun.ElapsedTime < targetTime) {
		double valueDelta = *currentValue - fromValue;
		double timeDelta = (targetTime - ctx.GameState->CurrentRun.ElapsedTime) * (1 / duration);
		displayValue = fromValue + ((1 - (timeDelta * timeDelta)) * valueDelta);
	} else {
		fromValue = *currentValue;
	}
	auto color = options.DefaultColor;
	if (options.HoverColor.a > 0 && IsMouseOver(ctx)) {
		color = options.HoverColor;
	}
	DrawRectangle(X(), Y(), (int)((float)Width(ctx) * ((float)displayValue / (float)*maxValue)), Height(ctx), color);
	for (auto child: *children) {
		child->DrawComponent(ctx, X() + ((Width(ctx) / 2) - (child->Width(ctx) / 2)), Y() + ((Height(ctx) / 2) - (child->Height(ctx) / 2)));
	}
}
