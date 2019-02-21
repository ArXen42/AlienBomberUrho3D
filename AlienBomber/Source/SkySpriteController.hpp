#pragma once

#include <Urho3D/Scene/LogicComponent.h>
#include "Urho3D/Core/Context.h"

using namespace Urho3D;

class SkySpriteController : public LogicComponent
{
URHO3D_OBJECT(SkySpriteController, LogicComponent)

public:
	static void RegisterObject(Context* context)
	{ context->RegisterFactory<SkySpriteController>(); }

public:
	SkySpriteController(Context* context) : LogicComponent(context)
	{};

private:
public:
	void Start() override;
};