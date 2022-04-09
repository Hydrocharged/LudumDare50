// Copyright © 2022 Daylon Wilkins & Maxwell Chow
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "gui/functionlabel.h"

#include <utility>

FunctionLabel::FunctionLabel(Context& ctx, const Component::Options& options, std::string textModel, std::function<std::string(Context&)> func) {
	this->options = options;
	this->textModel = textModel;
	this->modelLengthAt10 = (float)MeasureText(textModel.c_str(), 10);
	this->func = std::move(func);
}

int FunctionLabel::Height(Context& ctx) {
	return (int)((float)parent->Height(ctx) * options.HeightScale);
}

int FunctionLabel::Width(Context& ctx) {
	return (int)((float)parent->Width(ctx) * options.WidthScale);
}

void FunctionLabel::Draw(Context& ctx) {
	int fontSize = Height(ctx);
	int fontLength = MeasureText(textModel.c_str(), fontSize);
	if (fontLength > Width(ctx)) {
		fontLength = Width(ctx);
		fontSize = (int)(((float)fontLength / modelLengthAt10) * 10.0f);
	}
	auto color = options.DefaultColor;
	if (options.HoverColor.a > 0 && IsMouseOver(ctx)) {
		color = options.HoverColor;
	}
	DrawText(
		func(ctx).c_str(),
		X() + (Width(ctx) / 2) - (fontLength / 2),
		Y() + (Height(ctx) / 2) - (fontSize / 2),
		fontSize,
		color);
	for (auto child: *children) {
		child->DrawComponent(ctx, X() + ((Width(ctx) / 2) - (child->Width(ctx) / 2)), Y() + ((Height(ctx) / 2) - (child->Height(ctx) / 2)));
	}
}

