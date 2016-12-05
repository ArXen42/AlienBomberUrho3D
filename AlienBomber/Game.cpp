#include "Game.h"
#include "Terrain2DController.h"
#include "PlaneController.h"
#include "PlaneTouchLikeController.h"
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
		Terrain2DController::RegisterObject(context_);
		PlaneController::RegisterObject(context_);
		PlaneTouchLikeController::RegisterObject(context_);
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
		scene_->GetChild("Terrain")->CreateComponent<Terrain2DController>();
		auto plane = scene_->GetChild("Plane");
		plane->CreateComponent<PlaneController>();
		plane->CreateComponent<PlaneTouchLikeController>();
	}
}

void Game::HandlePostRenderUpdate(StringHash eventType, VariantMap &eventData) {
	scene_.Get()->GetComponent<PhysicsWorld2D>()->DrawDebugGeometry();
}
