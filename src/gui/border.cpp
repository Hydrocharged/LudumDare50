// Copyright © 2022 Daylon Wilkins & Maxwell Chow
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "gui/border.h"

Border::Border(Context& ctx, const Component::Options& options, float thicknessScale) {
	this->options = options;
	this->thicknessScale = thicknessScale;
}

int Border::Height(Context& ctx) {
	if (parent == nullptr) {
		return ctx.Screen.Height();
	}
	return (int)((float)parent->Height(ctx) * options.HeightScale);
}

int Border::Width(Context& ctx) {
	if (parent == nullptr) {
		return ctx.Screen.Width();
	}
	return (int)((float)parent->Width(ctx) * options.WidthScale);
}

void Border::Draw(Context& ctx) {
	int height = Height(ctx);
	int width = Width(ctx);
	auto color = options.DefaultColor;
	if (options.HoverColor.a > 0 && IsMouseOver(ctx)) {
		color = options.HoverColor;
	}
	int thickness = (int)(thicknessScale * (float)height);
	if ((int)(thicknessScale * (float)width) < thickness) {
		thickness = (int)(thicknessScale * (float)width);
	}

	if (color.a > 0) {
		DrawRectangle(X(), Y(), width, thickness, color); // Top
		DrawRectangle(X(), Y() + height - thickness, width, thickness, color); // Bottom
		DrawRectangle(X(), Y() + thickness, thickness, height - (thickness * 2), color); // Left
		DrawRectangle(X() + width - thickness, Y() + thickness, thickness, height - (thickness * 2), color); // Right
	}

	for (auto child: *children) {
		child->DrawComponent(ctx, X() + ((width / 2) - (child->Width(ctx) / 2)), Y() + ((height / 2) - (child->Height(ctx) / 2)));
	}
}
