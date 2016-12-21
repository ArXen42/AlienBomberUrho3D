// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "ShellController.hpp"
#include "CollisionDetection/CollisionsAggregator.hpp"
#include "CollisionDetection/TerrainCollider.hpp"
#include "CollisionDetection/RightBoundCollider.hpp"
#include "CollisionDetection/LeftBoundCollider.hpp"
#include "Helpers/CustomMath.hpp"
#include <Urho3D/Scene/Scene.h>
#include <Urho3D/Urho2D/RigidBody2D.h>

void ShellController::Start() {
	GetComponent<CollisionsAggregator>()
			->GetSignal(TerrainCollider::GetTypeInfoStatic())
			->Connect(this, &ShellController::OnTerrainCollision);

	GetComponent<CollisionsAggregator>()
			->GetSignal(RightBoundCollider::GetTypeInfoStatic(), CollisionType::BeginContact)
			->Connect(this, &ShellController::OnRightBoundCollision);

	GetComponent<CollisionsAggregator>()
			->GetSignal(LeftBoundCollider::GetTypeInfoStatic(), CollisionType::BeginContact)
			->Connect(this, &ShellController::OnLeftBoundCollision);
}

void ShellController::OnTerrainCollision(Node* terrainNode) {
	Exploded.Emit(terrainNode);
	SomeShellExploded.Emit(this, terrainNode);

	GetNode()->Remove();
}

void ShellController::OnRightBoundCollision(Node* verticalBoundNode) {
	auto direction = GetComponent<RigidBody2D>()->GetLinearVelocity();
	auto angle = CustomMath::GetDirectionAngle(direction);
	if (angle > 90 || angle < -90) return;

	auto position = GetNode()->GetPosition2D();
	GetNode()->SetPosition2D(
			verticalBoundNode->GetComponent<RightBoundCollider>()->GetOppositePosition(position));
}

void ShellController::OnLeftBoundCollision(Node* verticalBoundNode) {
	auto direction = GetComponent<RigidBody2D>()->GetLinearVelocity();
	auto angle = CustomMath::GetDirectionAngle(direction);
	if (-90 < angle && angle < 90) return;

	auto position = GetNode()->GetPosition2D();
	GetNode()->SetPosition2D(
			verticalBoundNode->GetComponent<LeftBoundCollider>()->GetOppositePosition(position));
}