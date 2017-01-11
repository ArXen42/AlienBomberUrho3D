#pragma once

#include <Urho3D/Core/Context.h>
#include <Urho3D/Scene/LogicComponent.h>
#include "../ExplosiveController.hpp"
#include "../Terrain/TerrainController.hpp"

using namespace Urho3D;

class LandUnitMovingController : public LogicComponent {
URHO3D_OBJECT(LandUnitMovingController, LogicComponent);
public:
	static void RegisterObject(Context* context) { context->RegisterFactory<LandUnitMovingController>(); }

public:
	LandUnitMovingController(Context* context) : LogicComponent(context) {}

private:
	enum class MovingDirection {
		Left, Right
	};

	void Update(float timeStep) override;
	void DelayedStart() override;

	void OnRightBoundCollision(Node* verticalBoundNode);
	void OnLeftBoundCollision(Node* verticalBoundNode);

	float speed_ = 3.f;
	MovingDirection movingDirection_ = MovingDirection::Left;
};
