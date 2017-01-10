// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "AircraftController.hpp"
#include "../GameSubsystem.hpp"
#include "../CollisionDetection/CollisionsAggregator.hpp"
#include "../CollisionDetection/TerrainCollider.hpp"

void AircraftController::Kill() {
	GetSubsystem<GameSubsystem>()->RequestReloadGameLevel();
}

void AircraftController::Start() {
	GetComponent<CollisionsAggregator>()
			->GetSignal(TerrainCollider::GetTypeInfoStatic())
			->Connect(this, &AircraftController::OnTerrainCollision);

	GetNode()->CreateComponent<AircraftMovingController>();
	GetNode()->CreateComponent<AircraftMouseController>();
	GetNode()->CreateComponent<AircraftBombsController>();
}

void AircraftController::OnTerrainCollision(Node* terrainNode) {
	Kill();
}
