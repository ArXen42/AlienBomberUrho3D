// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <Urho3D/Urho2D/CollisionChain2D.h>
#include "TerrainCollisionShapeController.hpp"

void TerrainCollisionShapeController::Start() {
	terrainController_ = GetComponent<TerrainController>();
	terrainController_->HeightmapUpdated.Connect(this, &TerrainCollisionShapeController::OnHeightmapUpdated);
	GetComponent<CollisionChain2D>()->SetVertexCount(terrainController_->GetHeightmap()->Size());
}

void TerrainCollisionShapeController::OnHeightmapUpdated(HeightmapUpdateDiff diff) {
	auto terrainController = GetComponent<TerrainController>();
	auto heightmap = terrainController->GetHeightmap();
	auto heightmapSize = heightmap->Size();
	auto collisionChain = GetComponent<CollisionChain2D>();

	const float terrainLength_ = TerrainController::TERRAIN_LENGTH;
	const float terrainMaxHeight = TerrainController::MAX_TERRAIN_HEIGHT;

	//Генерация координат вершин CollisionChain из карты высот и параметров размера ландшафта
	for (unsigned int i = diff.startIndex_; i <= diff.endIndex_; i++) {
		collisionChain->SetVertex(i, Vector2(i*terrainLength_/(heightmapSize - 1), heightmap->At(i)*terrainMaxHeight)
		                             - Vector2(terrainLength_/2, terrainMaxHeight/2));
	}

	// Ввиду особенностей реализации компонента коллизий,
	// для вызова RecreateFixture необходимо обязательно переназначить последнюю точку.
	collisionChain->SetVertex(heightmapSize - 1, Vector2(terrainLength_, (*heightmap->End())*terrainMaxHeight)
	                                             - Vector2(terrainLength_/2, terrainMaxHeight/2));
}

void TerrainCollisionShapeController::Stop() {
	if (!terrainController_.Expired())
		terrainController_->HeightmapUpdated.Disconnect(this, &TerrainCollisionShapeController::OnHeightmapUpdated);
}
