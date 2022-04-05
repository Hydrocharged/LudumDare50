// Copyright © 2022 Daylon Wilkins & Maxwell Chow
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "gui/slider.h"

Slider::Slider(Context& ctx, const Component::Options& options, Color trackColor, float* trackedValue) {
	this->options = options;
	this->trackColor = trackColor;
	this->trackedValue = trackedValue;
	AddChild(new SliderTab(ctx, options));
}

int Slider::Height(Context& ctx) {
	return (int)((float)parent->Height(ctx) * options.HeightScale);
}

int Slider::Width(Context& ctx) {
	return (int)((float)parent->Width(ctx) * options.WidthScale);
}

void Slider::Update(Context& ctx) {
	Component::Update(ctx);
	if (IsMouseDown(ctx)) {
		int height = Height(ctx);
		int width = Width(ctx);
		int tabSize = height;
		if (width < height) {
			tabSize = width;
		}
		int startX = X() + (tabSize / 2);
		int endX = X() + width - (tabSize / 2);
		int mouseX = ctx.Mouse.X();
		if (mouseX < startX) {
			*trackedValue = 0;
		} else if (mouseX > endX) {
			*trackedValue = 1;
		} else {
			*trackedValue = (float)(mouseX - startX) / (float)(endX - startX);
		}
	}
	for (auto child: *children) {
		child->Update(ctx);
	}
}

void Slider::Draw(Context& ctx) {
	int height = Height(ctx);
	int width = Width(ctx);
	int trackThickness = (int)((float)height * 0.1);
	if ((int)((float)width * 0.1) < trackThickness) {
		trackThickness = (int)((float)width * 0.1);
	}
	DrawRectangle(X(), Y() + (height / 2) - (trackThickness / 2), width, trackThickness, trackColor);

	int tabSize = height;
	if (width < height) {
		tabSize = width;
	}
	int moveableLength = width - tabSize;
	int tabX = X() + +(int)((float)moveableLength * (*trackedValue));
	int tabY = Y() + (height / 2) - (tabSize / 2);
	DrawRectangle(tabX, tabY, tabSize, tabSize, trackColor);
	for (auto child: *children) {
		child->DrawComponent(ctx, tabX + trackThickness, tabY + trackThickness);
	}
}

SliderTab::SliderTab(Context& ctx, const Component::Options& options) {
	this->options = options;
}

int SliderTab::Height(Context& ctx) {
	int parentHeight = parent->Height(ctx);
	int parentWidth = parent->Width(ctx);
	int trackThickness = (int)((float)parentHeight * 0.1);
	if ((int)((float)parentWidth * 0.1) < trackThickness) {
		trackThickness = (int)((float)parentWidth * 0.1);
	}

	int tabSize = parentHeight;
	if (parentWidth < parentHeight) {
		tabSize = parentWidth;
	}
	return tabSize - (2 * trackThickness);
}

int SliderTab::Width(Context& ctx) {
	return Height(ctx);
}

void SliderTab::Draw(Context& ctx) {
	auto color = options.DefaultColor;
	if (options.HoverColor.a > 0 && IsMouseOver(ctx)) {
		color = options.HoverColor;
	}
	int innerTabSize = Height(ctx);
	DrawRectangle(X(), Y(), innerTabSize, innerTabSize, color);
	for (auto child: *children) {
		child->DrawComponent(ctx, X() + ((Width(ctx) / 2) - (child->Width(ctx) / 2)), Y() + ((Height(ctx) / 2) - (child->Height(ctx) / 2)));
	}
}
