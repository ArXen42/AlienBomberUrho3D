#pragma once

#include <Urho3D/Scene/LogicComponent.h>
#include <Urho3D/Urho2D/RigidBody2D.h>

using namespace Urho3D;

/// Контроллирует перемещение самолета и предоставляет интерфейс для управления полетом.
class PlaneController : public LogicComponent {
URHO3D_OBJECT(PlaneController, LogicComponent);
public:
	PlaneController(Context* context) : LogicComponent(context), velocityMagnitude_(3), maxAngularVelocity_(4) {}

	static void RegisterObject(Context* context);

	void Start() override;
	void Update(float timeStep) override;

	void SetTargetRotation(float rotation);

	Vector2 GetLinearVelocity() { return rigidBody2D_->GetLinearVelocity(); }

private:
	float velocityMagnitude_;
	float maxAngularVelocity_;
	float targetRotation_;
	RigidBody2D* rigidBody2D_;
};
