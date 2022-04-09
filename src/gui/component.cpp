// Copyright © 2022 Daylon Wilkins & Maxwell Chow
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "context.h"
#include "gui/component.h"

Component::~Component() {
	if (registeredContext != nullptr) {
		registeredContext->UnregisterComponent(registeredName);
		registeredContext = nullptr;
	}
	for (Component* child: *children) {
		delete (child);
	}
	delete (this->children);
}

bool Component::IsMouseOver(Context& ctx) {
	int right = x + Width(ctx);
	int bottom = y + Height(ctx);
	int mouseX = ctx.Mouse.X();
	int mouseY = ctx.Mouse.Y();
	if (mouseX >= x && mouseX <= right && mouseY >= y && mouseY <= bottom) {
		return true;
	}
	return false;
}

bool Component::IsMouseDown(Context& ctx) {
	if (ctx.Mouse.IsDown() && IsMouseOver(ctx)) {
		return true;
	}
	return false;
}

void Component::OnClick(Context& ctx) {
	if (options.OnClick != nullptr) {
		options.OnClick(ctx, *this);
	}
}

void Component::DrawComponent(Context& ctx, int x, int y) {
	this->x = x;
	this->y = y;
	this->Draw(ctx);
}

void Component::Update(Context& ctx) {
	if (ctx.Mouse.HasClicked() && IsMouseOver(ctx)) {
		OnClick(ctx);
	}
	for (auto child: *children) {
		child->Update(ctx);
	}
}

Component* Component::AddChild(Component* child) {
	child->parent = this;
	children->push_back(child);
	return this;
}

Component* Component::Register(Context& ctx, std::string name) {
	if (registeredContext != nullptr) {
		registeredContext->UnregisterComponent(registeredName);
	}
	registeredContext = &ctx;
	registeredName = name;
	ctx.RegisterComponent(name, this);
	return this;
}

Component* Component::Unregister(Context& ctx) {
	if (registeredContext != nullptr) {
		registeredContext->UnregisterComponent(registeredName);
		registeredContext = nullptr;
	}
	return this;
}

void Component::operator+=(Component* component) {
	AddChild(component);
}

Component::Options Component::Options::copy() {
	return Component::Options{
		.WidthScale = this->WidthScale,
		.HeightScale = this->HeightScale,
		.DefaultColor = this->DefaultColor,
		.HoverColor = this->HoverColor,
		.OnClick = this->OnClick,
	};
}

Component::Options Component::Options::WithWidthScale(float widthScale) {
	auto newOptions = copy();
	newOptions.WidthScale = widthScale;
	return newOptions;
}

Component::Options Component::Options::WithHeightScale(float heightScale) {
	auto newOptions = copy();
	newOptions.HeightScale = heightScale;
	return newOptions;
}

Component::Options Component::Options::WithDefaultColor(Color defaultColor) {
	auto newOptions = copy();
	newOptions.DefaultColor = defaultColor;
	return newOptions;
}

Component::Options Component::Options::WithHoverColor(Color hoverColor) {
	auto newOptions = copy();
	newOptions.HoverColor = hoverColor;
	return newOptions;
}

Component::Options Component::Options::WithOnClick(std::function<void(Context&, Component&)> onClick) {
	auto newOptions = copy();
	newOptions.OnClick = std::move(onClick);
	return newOptions;
}
