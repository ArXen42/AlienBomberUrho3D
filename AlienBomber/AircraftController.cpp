#include "AircraftController.hpp"
#include <Urho3D/Scene/Node.h>
#include <Urho3D/Urho2D/StaticSprite2D.h>

void AircraftController::Start() {
	rigidBody2D_ = GetComponent<RigidBody2D>();
	SetTargetRotation(0);
}

void AircraftController::Update(float timeStep) {
}

void AircraftController::SetTargetPosition(const Vector2& position) {
	Vector2 direction = position - GetNode()->GetWorldPosition2D();

	float dirx = direction.x_;
	float diry = direction.y_;
	float angle = Acos(dirx/sqrt(dirx*dirx + diry*diry));
	SetTargetRotation(diry > 0 ? angle : -angle);
}

void AircraftController::SetTargetRotation(float rotation) {
	GetNode()->SetRotation2D(rotation);
	rigidBody2D_->SetLinearVelocity(Vector2(Cos(rotation), Sin(rotation))*velocityMagnitude_);

	GetComponent<StaticSprite2D>()->SetFlipY(Abs(rotation) > 90); //TODO: перенести
}
