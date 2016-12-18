// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "Game.h"
#include "AircraftControl/AircraftMovingController.hpp"
#include "AircraftControl/AircraftMouseController.hpp"
#include "Terrain/TerrainController.hpp"
#include "Terrain/TerrainCollisionShapeController.hpp"
#include "Terrain/TerrainSpriteController.hpp"
#include "AircraftControl/AircraftBombsController.hpp"
#include "CameraController.hpp"
#include "CollisionDetection/CollisionsAggregator.hpp"
#include "CollisionDetection/StaticColliderComponent.hpp"
#include "CollisionDetection/TerrainCollider.hpp"
#include "CollisionDetection/UpperBoundCollider.hpp"
#include "CollisionDetection/VerticalBoundCollider.hpp"
#include "CollisionDetection/LowerHorizontalBoundCollider.hpp"
#include <Urho3D/Urho2D/PhysicsWorld2D.h>
#include <Urho3D/Input/Input.h>

void Game::Setup() {
	engineParameters_["FullScreen"] = false;
	engineParameters_["WindowWidth"] = 1280;
	engineParameters_["WindowHeight"] = 720;
	engineParameters_["WindowResizable"] = false;

}

void Game::Start() {
	GetSubsystem<Input>()->SetMouseVisible(true);
	GetSubsystem<Input>()->SetMouseGrabbed(false);

	LoadGameLevel();

	SubscribeToEvent(E_POSTRENDERUPDATE, URHO3D_HANDLER(Game, HandlePostRenderUpdate));
}

void Game::Stop() {
}

void Game::LoadGameLevel() {
	{
		// Регистрация компонентов
		TerrainController::RegisterObject(context_);
		TerrainCollisionShapeController::RegisterObject(context_);
		TerrainSpriteController::RegisterObject(context_);

		CameraController::RegisterObject(context_);

		AircraftMovingController::RegisterObject(context_);
		AircraftMouseController::RegisterObject(context_);
		AircraftBombsController::RegisterObject(context_);

		CollisionsAggregator::RegisterObject(context_);
		StaticColliderComponent::RegisterObject(context_);
		TerrainCollider::RegisterObject(context_);
		UpperBoundCollider::RegisterObject(context_);
		VerticalBoundCollider::RegisterObject(context_);
		LowerHorizontalBoundCollider::RegisterObject(context_);

		ShellController::RegisterObject(context_);
	}

	{
		// Загрузка базовой конфигурации сцены из файла
		auto resourceCache = GetSubsystem<ResourceCache>();
		auto jsonSceneFile = resourceCache->GetFile("Data/Scenes/Game.json");
		scene_ = new Scene(context_);
		scene_.Get()->LoadJSON(*jsonSceneFile);
	}

	{
		// Установка Viewport и масштабирование камеры
		auto cameraNode = scene_->GetChild("MainCamera");
		cameraNode->CreateComponent<CameraController>();
	}

	{
		// Инициализация своих компонентов на сцене
		// (к сожалению, Urho3D не может их задавать в редакторе, в отличие от AngelScript скриптов)
		auto terrainNode = scene_->GetChild("Terrain");
		terrainNode->CreateComponent<TerrainController>();
		terrainNode->CreateComponent<TerrainCollisionShapeController>();
		terrainNode->CreateComponent<TerrainCollider>();
		terrainNode->GetChild("Sprite")->CreateComponent<TerrainSpriteController>();

		auto aircraft = scene_->GetChild("Aircraft");
		aircraft->CreateComponent<AircraftMovingController>();
		aircraft->CreateComponent<AircraftMouseController>();
		aircraft->CreateComponent<AircraftBombsController>();

		auto upperBoundNode = scene_->GetChild("UpperBound");
		upperBoundNode->CreateComponent<UpperBoundCollider>();
	}
}

void Game::HandlePostRenderUpdate(StringHash eventType, VariantMap& eventData) {
	scene_->GetComponent<PhysicsWorld2D>()->DrawDebugGeometry();
}
