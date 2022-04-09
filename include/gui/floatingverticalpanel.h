// Copyright © 2022 Daylon Wilkins & Maxwell Chow
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef FLOATINGVERTICALPANEL_H
#define FLOATINGVERTICALPANEL_H
#include "context.h"
#include "component.h"

class FloatingVerticalPanel : public Component {
public:
	FloatingVerticalPanel(Context& ctx, const Component::Options& options, float startX, float startY, float riseAmount);
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

#endif //FLOATINGVERTICALPANEL_H
