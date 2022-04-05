// Copyright © 2022 Daylon Wilkins & Maxwell Chow
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "gui/horizontalpanel.h"

HorizontalPanel::HorizontalPanel(Context& ctx, const Component::Options& options) {
	this->options = options;
}

int HorizontalPanel::Height(Context& ctx) {
	if (parent == nullptr) {
		return ctx.Screen.Height();
	}
	return (int)((float)parent->Height(ctx) * options.HeightScale);
}

int HorizontalPanel::Width(Context& ctx) {
	if (parent == nullptr) {
		return ctx.Screen.Width();
	}
	return (int)((float)parent->Width(ctx) * options.WidthScale);
}

void HorizontalPanel::Draw(Context& ctx) {
	int width = Width(ctx);
	if (options.HoverColor.a > 0 && IsMouseOver(ctx)) {
		DrawRectangle(X(), Y(), width, Height(ctx), options.HoverColor);
	} else if (options.DefaultColor.a > 0) {
		DrawRectangle(X(), Y(), width, Height(ctx), options.DefaultColor);
	}

	int halfHeight = Height(ctx) / 2;
	int totalChildWidth = 0;
	for (auto& child: *children) {
		totalChildWidth += child->Width(ctx);
	}
	int childSpacing = (width - totalChildWidth) / (children->size() + 1);
	int nextChildX = X();
	for (auto& child: *children) {
		nextChildX += childSpacing;
		child->DrawComponent(ctx, nextChildX, Y() + (halfHeight - (child->Height(ctx) / 2)));
		nextChildX += child->Width(ctx);
	}
}
