#pragma once

#include <Urho3D/Core/Context.h>
#include <Urho3D/Scene/LogicComponent.h>
#include <Urho3D/Urho2D/RigidBody2D.h>

using namespace Urho3D;

/// Контроллирует перемещение самолета и предоставляет интерфейс для управления полетом.
class AircraftMovingController : public LogicComponent
{
URHO3D_OBJECT(AircraftMovingController, LogicComponent);
public:
	static void RegisterObject(Context* context)
	{ context->RegisterFactory<AircraftMovingController>(); }

public:
	explicit AircraftMovingController(Context* context) : LogicComponent(context)
	{}

	void SetTargetPosition(const Vector2& position);

	void SetTargetRotation(float rotation);

	Vector2 GetLinearVelocity() const
	{ return rigidBody2D_->GetLinearVelocity(); }

private:
	void Start() override;

	void Update(float timeStep) override;

	void OnUpperBoundCollision(Node* upperBoundNode);

	void OnRightBoundCollision(Node* verticalBoundNode);

	void OnLeftBoundCollision(Node* verticalBoundNode);

	float velocityMagnitude_ = 3.5f;
	float targetRotation_    = 0;
	RigidBody2D* rigidBody2D_ = nullptr;
};
