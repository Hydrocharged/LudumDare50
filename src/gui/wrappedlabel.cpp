// Copyright © 2022 Daylon Wilkins & Maxwell Chow
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "gui/wrappedlabel.h"
#include "raylib/text_rectangle_bounds.c"
#include "cmath"

WrappedLabel::WrappedLabel(Context& ctx, std::string text, const Component::Options& options) {
	this->text = text;
	this->options = options;
	this->fontSize = 0;
}

int WrappedLabel::Height(Context& ctx) {
	return (int)((float)parent->Height(ctx) * options.HeightScale);
}

int WrappedLabel::Width(Context& ctx) {
	return (int)((float)parent->Width(ctx) * options.WidthScale);
}

void WrappedLabel::SetText(Context& ctx, std::string text) {
	this->text = text;
	calculateFontSize(ctx);
}

void WrappedLabel::Draw(Context& ctx) {
	if (fontSize <= 0 || ctx.Screen.HasResized()) {
		calculateFontSize(ctx);
	}
	auto color = options.DefaultColor;
	if (options.HoverColor.a > 0 && IsMouseOver(ctx)) {
		color = options.HoverColor;
	}
	DrawTextBoxed(GetFontDefault(), text.c_str(), Rectangle{(float)X(), (float)Y(), (float)Width(ctx), (float)Height(ctx)}, (float)fontSize, (float)fontSize / 10.0f, true, color);
	for (auto child: *children) {
		child->DrawComponent(ctx, X() + ((Width(ctx) / 2) - (child->Width(ctx) / 2)), Y() + ((Height(ctx) / 2) - (child->Height(ctx) / 2)));
	}
}

void WrappedLabel::calculateFontSize(Context& ctx) {
	int height = Height(ctx);
	int width = Width(ctx);
	int fontLength = MeasureText(text.c_str(), height);
	if (fontLength <= width) {
		fontSize = height;
		return;
	}
	float wrapAccumulation = .85;
	for (int lines = 2; true; lines++) {
		fontSize = height / lines;
		if (fontSize < 9) {
			fontSize = 9;
			return;
		}
		if ((MeasureText(text.c_str(), fontSize) / lines) < width * pow(wrapAccumulation, lines)) {
			return;
		}
	}
}
