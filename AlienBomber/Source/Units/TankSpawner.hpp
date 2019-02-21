#pragma once

#include <Urho3D/Core/Context.h>
#include <Urho3D/Scene/LogicComponent.h>

using namespace Urho3D;

class TankSpawner : public LogicComponent
{
URHO3D_OBJECT(TankSpawner, LogicComponent)

public:
	static void RegisterObject(Context* context)
	{ context->RegisterFactory<TankSpawner>(); }

public:
	TankSpawner(Context* context) : LogicComponent(context)
	{}

private:
	void Start() override;

	void InstantiateTank(float normalizedPos);
};