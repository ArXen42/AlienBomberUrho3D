#include <Urho3D/Urho2D/CollisionChain2D.h>
#include "TerrainCollisionShapeController.hpp"
#include "TerrainController.hpp"

void TerrainCollisionShapeController::Start() {
	terrainController_ = GetComponent<TerrainController>();
	terrainController_->heightmapUpdated_.Connect(this, &TerrainCollisionShapeController::OnHeightmapUpdated);
}

void TerrainCollisionShapeController::OnHeightmapUpdated() {
	auto terrainController = GetComponent<TerrainController>();
	auto heightmap = terrainController->GetHeightmap();

	auto collisionChain = GetComponent<CollisionChain2D>();
	auto heightmapSize = heightmap->Size();

	float terrainLength_ = terrainController->terrainLength_;
	float terrainMaxHeight = terrainController->maxTerrainHeight_;

	//Генерация координат вершин CollisionChain из карты высот и параметров размера ландшафта
	auto& vertices = *new PODVector<Vector2>(heightmapSize);
	for (unsigned int i = 0; i < heightmapSize; i++) {
		vertices[i] = Vector2(i*terrainLength_/(heightmapSize - 1), heightmap->At(i)*terrainMaxHeight) -
		              Vector2(terrainLength_/2, terrainMaxHeight/2);
	}

	collisionChain->SetVertices(vertices);
}

void TerrainCollisionShapeController::Stop() {
	if (!terrainController_.Expired())
		terrainController_->heightmapUpdated_.Disconnect(this, &TerrainCollisionShapeController::OnHeightmapUpdated);
}
