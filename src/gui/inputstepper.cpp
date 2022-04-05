// Copyright © 2022 Daylon Wilkins & Maxwell Chow
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "gui/inputstepper.h"
#include "gui/label.h"

InputStepper::InputStepper(Context& ctx, const Component::Options& options, int* minValue, int* maxValue, int* currentValue) {
	this->options = options;
	this->min = minValue;
	this->max = maxValue;
	this->current = currentValue;
	AddChild(new Label(ctx, std::to_string(*currentValue), {.WidthScale = .6, .HeightScale = 1, .DefaultColor = options.DefaultColor}));
}

int InputStepper::Height(Context& ctx) {
	return (int)((float)parent->Height(ctx) * options.HeightScale);
}

int InputStepper::Width(Context& ctx) {
	return (int)((float)parent->Width(ctx) * options.WidthScale);
}

void InputStepper::OnClick(Context& ctx) {
	Component::OnClick(ctx);
	int fifthWidth = Width(ctx) / 5;
	int mouseX = ctx.Mouse.X() - X();
	if (mouseX <= fifthWidth) {
		if (*current > *min) {
			*current -= 1;
			((Label*)this->Child(0))->SetText(ctx, std::to_string(*current));
		}
	} else if (mouseX >= 4 * fifthWidth) {
		if (*current < *max) {
			*current += 1;
			((Label*)this->Child(0))->SetText(ctx, std::to_string(*current));
		}
	}
}

void InputStepper::Draw(Context& ctx) {
	int height = Height(ctx);
	int width = Width(ctx);
	int halfHeight = height / 2;
	int fifthWidth = width / 5;

	auto leftColor = options.DefaultColor;
	auto rightColor = options.DefaultColor;
	if (options.HoverColor.a > 0 && IsMouseOver(ctx)) {
		if (ctx.Mouse.X() <= X() + fifthWidth) {
			leftColor = options.HoverColor;
		} else if (ctx.Mouse.X() >= X() + width - fifthWidth) {
			rightColor = options.HoverColor;
		}
	}
	if (*current <= *min) {
		leftColor = Color{options.DefaultColor.r, options.DefaultColor.g, options.DefaultColor.b, 100};
	}
	if (*current >= *max) {
		rightColor = Color{options.DefaultColor.r, options.DefaultColor.g, options.DefaultColor.b, 100};
	}

	DrawLineEx(
		Vector2{(float)(X() + fifthWidth), (float)Y() + (0.05f * halfHeight)},
		Vector2{(float)(X() + (0.05f * halfHeight)), (float)Y() + halfHeight},
		0.05f * height,
		leftColor);
	DrawLineEx(
		Vector2{(float)(X() + (0.05f * halfHeight)), (float)Y() + halfHeight},
		Vector2{(float)(X() + fifthWidth), (float)Y() + height - (0.05f * halfHeight)},
		0.05f * height,
		leftColor);
	DrawLineEx(
		Vector2{(float)(X() + width - fifthWidth), (float)Y() + (0.05f * halfHeight)},
		Vector2{(float)(X() + width - (0.05f * halfHeight)), (float)Y() + halfHeight},
		0.05f * height,
		rightColor);
	DrawLineEx(
		Vector2{(float)(X() + width - (0.05f * halfHeight)), (float)Y() + halfHeight},
		Vector2{(float)(X() + width - fifthWidth), (float)Y() + height - (0.05f * halfHeight)},
		0.05f * height,
		rightColor);
	for (auto child: *children) {
		child->DrawComponent(ctx, X() + ((width / 2) - (child->Width(ctx) / 2)), Y() + (height / 2) - (child->Height(ctx) / 2));
	}
}
