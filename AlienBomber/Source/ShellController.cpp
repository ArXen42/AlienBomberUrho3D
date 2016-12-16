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
	GetComponent<CollisionsAggregator>()
			->GetSignal(TerrainCollider::GetTypeInfoStatic())
			->Disconnect(this, &ShellController::OnTerrainCollision);

	Exploded.Emit(terrainNode);
	SomeShellExploded.Emit(this, terrainNode);

	GetNode()->Remove();
}

