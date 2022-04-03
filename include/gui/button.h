// Copyright © 2022 Daylon Wilkins & Maxwell Chow
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef BUTTON_H
#define BUTTON_H
#include "context.h"
#include "component.h"
#include "label.h"

class Button : public Component {
public:
	Button(Context& ctx, const Component::Options& options);
	int Width(Context& ctx) override;
	int Height(Context& ctx) override;

protected:
	void Draw(Context& ctx) override;
};

#endif //BUTTON_H
