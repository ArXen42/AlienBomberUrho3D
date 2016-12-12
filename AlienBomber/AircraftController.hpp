#pragma once

#include <Urho3D/Scene/LogicComponent.h>
#include <Urho3D/Urho2D/RigidBody2D.h>

using namespace Urho3D;

/// Контроллирует перемещение самолета и предоставляет интерфейс для управления полетом.
class AircraftController : public LogicComponent {
URHO3D_OBJECT(AircraftController, LogicComponent);
public:
	AircraftController(Context* context) : LogicComponent(context) {}

	static void RegisterObject(Context* context);

	void Start() override;
	void Update(float timeStep) override;

	void SetTargetPosition(const Vector2& position);

	void SetTargetRotation(float rotation);

	Vector2 GetLinearVelocity() { return rigidBody2D_->GetLinearVelocity(); }

private:
	float velocityMagnitude_ = 3;
	RigidBody2D* rigidBody2D_;
};
