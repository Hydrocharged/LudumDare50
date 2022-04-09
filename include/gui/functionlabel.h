// Copyright © 2022 Daylon Wilkins & Maxwell Chow
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef FUNCTIONLABEL_H
#define FUNCTIONLABEL_H
#include "context.h"
#include "component.h"
#include "string"

class FunctionLabel : public Component {
public:
	FunctionLabel(Context& ctx, const Component::Options& options, std::string textModel, std::function<std::string(Context&)> func);
	int Width(Context& ctx) override;
	int Height(Context& ctx) override;

protected:
	void Draw(Context& ctx) override;

private:
	std::function<std::string(Context&)> func;
	std::string textModel;
	float modelLengthAt10;
};

#endif //FUNCTIONLABEL_H
