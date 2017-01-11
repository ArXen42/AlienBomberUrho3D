// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include <Urho3D/Scene/Scene.h>
#include <Urho3D/Urho2D/RigidBody2D.h>
#include "LandUnitMovingController.hpp"
#include "../CollisionDetection/CollisionsAggregator.hpp"
#include "../CollisionDetection/RightBoundCollider.hpp"
#include "../CollisionDetection/LeftBoundCollider.hpp"

void LandUnitMovingController::Update(float timeStep) {
	auto rigidBody2D = GetComponent<RigidBody2D>();
	float y = rigidBody2D->GetLinearVelocity().y_;
	rigidBody2D->SetLinearVelocity({movingDirection_ == MovingDirection::Right ? speed_ : -speed_, y});
}

void LandUnitMovingController::DelayedStart() {
	node_->CreateComponent<CollisionsAggregator>();

	GetComponent<CollisionsAggregator>()
			->GetSignal(RightBoundCollider::GetTypeInfoStatic())
			->Connect(this, &LandUnitMovingController::OnRightBoundCollision);

	GetComponent<CollisionsAggregator>()
			->GetSignal(LeftBoundCollider::GetTypeInfoStatic())
			->Connect(this, &LandUnitMovingController::OnLeftBoundCollision);
}

void LandUnitMovingController::OnRightBoundCollision(Node* verticalBoundNode) {
	movingDirection_ = MovingDirection::Left;
}

void LandUnitMovingController::OnLeftBoundCollision(Node* verticalBoundNode) {
	movingDirection_ = MovingDirection::Right;
}
