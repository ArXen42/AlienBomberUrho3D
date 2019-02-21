#pragma once

#include <Urho3D/Core/Context.h>
#include <Urho3D/Scene/Node.h>
#include <Urho3D/Scene/LogicComponent.h>
#include "AircraftBombsController.hpp"
#include "AircraftMouseController.hpp"
#include "AircraftMovingController.hpp"

using namespace Urho3D;

class AircraftController : public LogicComponent
{
URHO3D_OBJECT(AircraftController, LogicComponent);
public:
	static void RegisterObject(Context* context)
	{ context->RegisterFactory<AircraftController>(); }

public:
	explicit AircraftController(Context* context) : LogicComponent(context)
	{}

	void Kill();

private:
	void Start() override;

	void OnTerrainCollision(Node* terrainNode);
};