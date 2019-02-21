#pragma once

#include <Urho3D/Core/Context.h>
#include <Urho3D/Scene/LogicComponent.h>

using namespace Urho3D;

class AircraftBombsController : public LogicComponent
{
URHO3D_OBJECT(AircraftBombsController, LogicComponent);
public:
	static void RegisterObject(Context* context)
	{ context->RegisterFactory<AircraftBombsController>(); }

public:
	AircraftBombsController(Context* context) : LogicComponent(context)
	{}

private:
	void Start() override;

	void DropBomb();

	void HandleKeyDown(StringHash eventType, VariantMap& eventData);
};

