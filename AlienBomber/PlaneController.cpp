#include "PlaneController.h"
#include <Urho3D/Core/Context.h>
#include <Urho3D/Scene/Node.h>
#include <Urho3D/Urho2D/StaticSprite2D.h>

void PlaneController::RegisterObject(Context* context) {
	context->RegisterFactory<PlaneController>();
}
void PlaneController::Start() {
	rigidBody2D_ = GetComponent<RigidBody2D>();
	SetTargetRotation(0);
}
void PlaneController::Update(float timeStep) {
}
void PlaneController::SetTargetRotation(float rotation) {
	targetRotation_ = rotation;
	//TODO: плавный поворот куда надо и т.д.
	GetNode()->SetRotation2D(rotation);
	rigidBody2D_->SetLinearVelocity(Vector2(Cos(rotation), Sin(rotation))*velocityMagnitude_);

	GetComponent<StaticSprite2D>()->SetFlipY(Abs(rotation) > 90);
}
