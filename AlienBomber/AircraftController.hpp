#pragma once

#include <Urho3D/Core/Context.h>
#include <Urho3D/Scene/LogicComponent.h>
#include <Urho3D/Urho2D/RigidBody2D.h>

using namespace Urho3D;

/// Контроллирует перемещение самолета и предоставляет интерфейс для управления полетом.
class AircraftController : public LogicComponent {
URHO3D_OBJECT(AircraftController, LogicComponent);
public:
	static void RegisterObject(Context* context) { context->RegisterFactory<AircraftController>(); }

public:
	AircraftController(Context* context) : LogicComponent(context) {}

	void SetTargetPosition(const Vector2& position);
	void SetTargetRotation(float rotation);

	Vector2 GetLinearVelocity() { return rigidBody2D_->GetLinearVelocity(); }

private:
	void Start() override;
	void Update(float timeStep) override;

	float velocityMagnitude_ = 3;
	RigidBody2D* rigidBody2D_;
};
