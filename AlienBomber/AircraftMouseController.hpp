#pragma once

#include <Urho3D/Scene/LogicComponent.h>
#include <Urho3D/Core/Context.h>

using namespace Urho3D;

class AircraftMouseController : public LogicComponent {
URHO3D_OBJECT(AircraftMouseController, LogicComponent);
public:
	static void RegisterObject(Context* context) { context->RegisterFactory<AircraftMouseController>(); }

public:
	AircraftMouseController(Context* context) : LogicComponent(context) {}

	void Start() override;

private:
	void HandleMouseButtonDown(StringHash eventType, VariantMap& eventData);
};