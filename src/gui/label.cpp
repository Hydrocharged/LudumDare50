// Copyright © 2022 Daylon Wilkins & Maxwell Chow
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "gui/label.h"

Label::Label(Context& ctx, std::string text, const Component::Options& options) {
	this->text = text;
	this->options = options;
	this->textLengthAt10 = (float)MeasureText(text.c_str(), 10);
}

int Label::Height(Context& ctx) {
	return (int)((float)parent->Height(ctx) * options.HeightScale);
}

int Label::Width(Context& ctx) {
	return (int)((float)parent->Width(ctx) * options.WidthScale);
}

void Label::SetText(Context& ctx, std::string text) {
	this->text = text;
	this->textLengthAt10 = (float)MeasureText(text.c_str(), 10);
}

void Label::Draw(Context& ctx) {
	int fontSize = Height(ctx);
	int fontLength = MeasureText(text.c_str(), fontSize);
	if (fontLength > Width(ctx)) {
		fontLength = Width(ctx);
		fontSize = (int)(((float)fontLength / textLengthAt10) * 10.0f);
	}
	auto color = options.DefaultColor;
	if (options.HoverColor.a > 0 && IsMouseOver(ctx)) {
		color = options.HoverColor;
	}
	DrawText(
		text.c_str(),
		X() + (Width(ctx) / 2) - (fontLength / 2),
		Y() + (Height(ctx) / 2) - (fontSize / 2),
		fontSize,
		color);
	for (auto child: *children) {
		child->DrawComponent(ctx, X() + ((Width(ctx) / 2) - (child->Width(ctx) / 2)), Y() + ((Height(ctx) / 2) - (child->Height(ctx) / 2)));
	}
}
