// Copyright © 2022 Daylon Wilkins & Maxwell Chow
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "gui/verticalpanel.h"

VerticalPanel::VerticalPanel(Context& ctx, const Component::Options& options) {
	this->options = options;
}

int VerticalPanel::Height(Context& ctx) {
	if (parent == nullptr) {
		return ctx.Screen.Height();
	}
	return (int)((float)parent->Height(ctx) * options.HeightScale);
}

int VerticalPanel::Width(Context& ctx) {
	if (parent == nullptr) {
		return ctx.Screen.Width();
	}
	return (int)((float)parent->Width(ctx) * options.WidthScale);
}

void VerticalPanel::Draw(Context& ctx) {
	int height = Height(ctx);
	if (options.HoverColor.a > 0 && IsMouseOver(ctx)) {
		DrawRectangle(X(), Y(), Width(ctx), height, options.HoverColor);
	} else if (options.DefaultColor.a > 0) {
		DrawRectangle(X(), Y(), Width(ctx), height, options.DefaultColor);
	}

	int halfWidth = Width(ctx) / 2;
	int totalChildHeight = 0;
	for (auto& child: *children) {
		totalChildHeight += child->Height(ctx);
	}
	int childSpacing = (height - totalChildHeight) / (children->size() + 1);
	int nextChildY = Y();
	for (auto& child: *children) {
		nextChildY += childSpacing;
		child->DrawComponent(ctx, X() + (halfWidth - (child->Width(ctx) / 2)), nextChildY);
		nextChildY += child->Height(ctx);
	}
}
