// Copyright © 2022 Daylon Wilkins & Maxwell Chow
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef FLOATINGHORIZONTALPANEL_H
#define FLOATINGHORIZONTALPANEL_H
#include "context.h"
#include "component.h"

class FloatingHorizontalPanel : public Component {
public:
	FloatingHorizontalPanel(Context& ctx, const Component::Options& options, float startX, float startY, float riseAmount);
	int Width(Context& ctx) override;
	int Height(Context& ctx) override;

protected:
	void Draw(Context& ctx) override;

private:
	unsigned char parentAlpha(Context& ctx);

private:
	double targetTime;
	float startX;
	float startY;
	float riseAmount;

	const float duration = 1;
};

#endif //FLOATINGHORIZONTALPANEL_H
