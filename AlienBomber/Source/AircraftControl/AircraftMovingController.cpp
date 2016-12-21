// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <Urho3D/Scene/Node.h>
#include <Urho3D/Urho2D/StaticSprite2D.h>
#include "AircraftMovingController.hpp"
#include "../CollisionDetection/UpperBoundCollider.hpp"
#include "../CollisionDetection/LeftBoundCollider.hpp"
#include "../CollisionDetection/CollisionsAggregator.hpp"
#include "../Helpers/CustomMath.hpp"

void AircraftMovingController::Start() {
	GetComponent<CollisionsAggregator>()
			->GetSignal(UpperBoundCollider::GetTypeInfoStatic())
			->Connect(this, &AircraftMovingController::OnUpperBoundCollision);

	GetComponent<CollisionsAggregator>()
			->GetSignal(RightBoundCollider::GetTypeInfoStatic(), CollisionType::EndContact)
			->Connect(this, &AircraftMovingController::OnRightBoundCollision);

	GetComponent<CollisionsAggregator>()
			->GetSignal(LeftBoundCollider::GetTypeInfoStatic(), CollisionType::EndContact)
			->Connect(this, &AircraftMovingController::OnLeftBoundCollision);

	rigidBody2D_ = GetComponent<RigidBody2D>();
	SetTargetRotation(0);
}

void AircraftMovingController::Update(float timeStep) {
}

void AircraftMovingController::SetTargetPosition(const Vector2& position) {
	Vector2 direction = position - GetNode()->GetWorldPosition2D();

	float angle = CustomMath::GetDirectionAngle(direction);
	SetTargetRotation(angle);
}

void AircraftMovingController::SetTargetRotation(float rotation) {
	targetRotation_ = rotation;
	GetNode()->SetRotation2D(rotation);
	rigidBody2D_->SetLinearVelocity(Vector2(Cos(rotation), Sin(rotation))*velocityMagnitude_);

	GetComponent<StaticSprite2D>()->SetFlipY(Abs(rotation) > 90); //TODO: перенести
}

void AircraftMovingController::OnUpperBoundCollision(Node* upperBoundNode) {
	float rotation = upperBoundNode->GetComponent<UpperBoundCollider>()->ReflectDirectionAngle(targetRotation_);
	if (rotation > 0)
		rotation = -rotation; //Препятствует выходу за пределы экрана в пограничных случаях

	SetTargetRotation(rotation);
}

void AircraftMovingController::OnRightBoundCollision(Node* verticalBoundNode) {
	if (targetRotation_ > 90 || targetRotation_ < -90) return;

	auto position = GetNode()->GetPosition2D();
	GetNode()->SetPosition2D(
			verticalBoundNode->GetComponent<RightBoundCollider>()->GetOppositePosition(position));
}

void AircraftMovingController::OnLeftBoundCollision(Node* verticalBoundNode) {
	if (-90 < targetRotation_ && targetRotation_ < 90) return;

	auto position = GetNode()->GetPosition2D();
	GetNode()->SetPosition2D(
			verticalBoundNode->GetComponent<LeftBoundCollider>()->GetOppositePosition(position));
}
