#pragma once

#include <Urho3D/Core/Context.h>
#include <Urho3D/Scene/LogicComponent.h>

using namespace Urho3D;

class AircraftController : public LogicComponent {
URHO3D_OBJECT(AircraftController, LogicComponent);
public:
	static void RegisterObject(Context* context) { context->RegisterFactory<AircraftController>(); }

public:
	AircraftController(Context* context) : LogicComponent(context) {}

private:
	void Start() override;

	void OnTerrainCollision(Node* terrainNode);
};