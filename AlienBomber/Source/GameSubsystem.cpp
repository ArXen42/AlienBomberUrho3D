// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <Urho3D/Resource/ResourceCache.h>
#include "GameSubsystem.hpp"
#include "CollisionDetection/LeftBoundCollider.hpp"
#include "CollisionDetection/UpperBoundCollider.hpp"
#include "CollisionDetection/CollisionsAggregator.hpp"
#include "Terrain/TerrainSpriteController.hpp"
#include "CollisionDetection/TerrainCollider.hpp"
#include "Terrain/TerrainCollisionShapeController.hpp"
#include "CameraController.hpp"
#include "AircraftControl/AircraftController.hpp"
#include "SkySpriteController.hpp"
#include "Units/TankSpawner.hpp"

void GameSubsystem::LoadGameLevel() {
	{
		// Загрузка базовой конфигурации сцены из файла
		auto resourceCache = GetSubsystem<ResourceCache>();
		auto jsonSceneFile = resourceCache->GetFile("Data/Scenes/Game.json");
		scene_ = new Scene(context_);
		scene_->LoadJSON(*jsonSceneFile);
	}

	{
		// Установка Viewport и масштабирование камеры
		auto cameraNode = scene_->GetChild("MainCamera");
		cameraNode->CreateComponent<CameraController>();
	}

	{
		scene_->GetChild("Sky")->CreateComponent<SkySpriteController>();

		// Инициализация своих компонентов на сцене
		// (к сожалению, Urho3D не может их задавать в редакторе, в отличие от AngelScript скриптов)
		auto terrainNode = scene_->GetChild("Terrain");
		terrainNode->CreateComponent<TerrainController>();
		terrainNode->CreateComponent<TerrainCollisionShapeController>();
		terrainNode->CreateComponent<TerrainCollider>();
		terrainNode->GetChild("Sprite")->CreateComponent<TerrainSpriteController>();

		auto aircraft = scene_->GetChild("Aircraft");
		aircraft->CreateComponent<CollisionsAggregator>();
		aircraft->CreateComponent<AircraftController>();

		auto upperBoundNode = scene_->GetChild("UpperBound");
		upperBoundNode->CreateComponent<UpperBoundCollider>();

		auto rightBoundNode = scene_->GetChild("RightBound");
		rightBoundNode->CreateComponent<RightBoundCollider>();

		auto leftBoundNode = scene_->GetChild("LeftBound");
		leftBoundNode->CreateComponent<LeftBoundCollider>();

		scene_->CreateComponent<TankSpawner>();
	}
}

void GameSubsystem::UnloadGameLevel() {
	assert(!scene_.Expired());

	scene_->RemoveAllChildren();
	scene_->RemoveAllComponents();
	scene_->RemoveAllTags();
	scene_->Remove();
}

void GameSubsystem::RequestReloadGameLevel() {
	reloadRequested_ = true;
}

void GameSubsystem::HandleBeginFrame(StringHash eventType, VariantMap& eventData) {
	if (reloadRequested_) {
		ReloadGameLevel();
		reloadRequested_ = false;
	}
}

void GameSubsystem::ReloadGameLevel() {
	UnloadGameLevel();
	LoadGameLevel();
}
