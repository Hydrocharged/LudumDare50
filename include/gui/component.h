// Copyright © 2022 Daylon Wilkins & Maxwell Chow
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef COMPONENT_H
#define COMPONENT_H
#include "context.h"
#include "functional"

class Component {
	friend class VerticalPanel;

	friend class HorizontalPanel;

	friend class Button;

public:
	virtual ~Component();
	virtual int Width(Context& ctx) = 0;
	virtual int Height(Context& ctx) = 0;
	virtual void Update(Context& ctx);
	virtual void OnClick(Context& ctx);
	Component* AddChild(Component* child);
	void DrawComponent(Context& ctx, int x, int y);
	bool IsMouseOver(Context& ctx);
	bool IsMouseDown(Context& ctx);
	int X() { return x; }
	int Y() { return y; }
	void operator+=(Component* component);
	Component* operator[](int i) { return children->at(i); }
	Component* Child(int i) { return children->at(i); }

	struct Options {
	public:
		float WidthScale = 0;
		float HeightScale = 0;
		Color DefaultColor = {};
		Color HoverColor = {};
		std::function<void(Context&, Component&)> OnClick = nullptr;

		Options WithWidthScale(float widthScale);
		Options WithHeightScale(float heightScale);
		Options WithDefaultColor(Color defaultColor);
		Options WithHoverColor(Color hoverColor);
		Options WithOnClick(std::function<void(Context&, Component&)> onClick);

	private:
		Options copy();
	};

	Options& GetOptions() { return options; }

protected:
	Component() { children = new std::vector<Component*>(); }
	virtual void Draw(Context& ctx) = 0;
	Component* parent = nullptr;
	std::vector<Component*>* children;
	Options options;

private:
	int x = 0;
	int y = 0;
};

#endif //COMPONENT_H
