// Copyright © 2022 Daylon Wilkins & Maxwell Chow
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "gui/button.h"

Button::Button(Context& ctx, const Component::Options& options) {
	this->options = options;
}

int Button::Height(Context& ctx) {
	return (int)((float)parent->Height(ctx) * options.HeightScale);
}

int Button::Width(Context& ctx) {
	return (int)((float)parent->Width(ctx) * options.WidthScale);
}

void Button::Draw(Context& ctx) {
	auto color = options.DefaultColor;
	if (options.HoverColor.a > 0 && IsMouseOver(ctx)) {
		color = options.HoverColor;
	}
	DrawRectangle(X(), Y(), Width(ctx), Height(ctx), color);
	for (auto child: *children) {
		child->DrawComponent(ctx, X() + ((Width(ctx) / 2) - (child->Width(ctx) / 2)), Y() + ((Height(ctx) / 2) - (child->Height(ctx) / 2)));
	}
}
