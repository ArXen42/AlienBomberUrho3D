// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "ShellController.hpp"
#include "CollisionDetection/CollisionsAggregator.hpp"
#include "CollisionDetection/TerrainCollider.hpp"
#include <Urho3D/Scene/Node.h>
#include <Urho3D/Scene/Scene.h>

void ShellController::Start() {
	GetComponent<CollisionsAggregator>()
			->GetSignal(TerrainCollider::GetTypeInfoStatic())
			->Connect(this, &ShellController::OnTerrainCollision);
}

void ShellController::OnTerrainCollision(Node* terrainNode) {
	Exploded.Emit(terrainNode);
	SomeShellExploded.Emit(this, terrainNode);

	GetNode()->Remove();
}

