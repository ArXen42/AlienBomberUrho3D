#include "Game.h"
#include "AircraftController.hpp"
#include "AircraftMouseController.hpp"
#include "TerrainController.hpp"
#include "TerrainCollisionShapeController.hpp"
#include "TerrainSpriteController.hpp"
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
		AircraftController::RegisterObject(context_);
		AircraftMouseController::RegisterObject(context_);
	}

	{
		// Загрузка базовой конфигурации сцены из файла
		auto resourceCache = GetSubsystem<ResourceCache>();
		auto jsonSceneFile = resourceCache->GetFile("Data/Scenes/Game.json");
		scene_ = new Scene(context_);
		scene_.Get()->LoadJSON(*jsonSceneFile);
	}

	{
		// Установка Viewport
		auto camera = scene_.Get()->GetChild("MainCamera")->GetComponent<Camera>();
		auto viewport = new Viewport(context_, scene_, camera);
		GetSubsystem<Renderer>()->SetViewport(0, viewport);
	}

	{
		// Инициализация своих компонентов на сцене
		// (к сожалению, Urho3D не может их задавать в редакторе, в отличие от AngelScript скриптов)
		auto terrainNode = scene_->GetChild("Terrain");
		terrainNode->CreateComponent<TerrainController>();
		terrainNode->CreateComponent<TerrainCollisionShapeController>();
		terrainNode->GetChild("Sprite")->CreateComponent<TerrainSpriteController>();

		auto plane = scene_->GetChild("Plane");
		plane->CreateComponent<AircraftController>();
		plane->CreateComponent<AircraftMouseController>();
	}
}

void Game::HandlePostRenderUpdate(StringHash eventType, VariantMap& eventData) {
//	scene_.Get()->GetComponent<PhysicsWorld2D>()->DrawDebugGeometry();
}
