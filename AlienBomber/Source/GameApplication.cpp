// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <Urho3D/Input/Input.h>
#include <Urho3D/Urho2D/PhysicsWorld2D.h>
#include "GameApplication.h"
#include "ShellController.hpp"
#include "CameraController.hpp"
#include "AircraftControl/AircraftMovingController.hpp"
#include "AircraftControl/AircraftMouseController.hpp"
#include "AircraftControl/AircraftBombsController.hpp"
#include "Terrain/TerrainController.hpp"
#include "Terrain/TerrainCollisionShapeController.hpp"
#include "Terrain/TerrainSpriteController.hpp"
#include "CollisionDetection/CollisionsAggregator.hpp"
#include "CollisionDetection/TerrainCollider.hpp"
#include "CollisionDetection/UpperBoundCollider.hpp"
#include "CollisionDetection/RightBoundCollider.hpp"
#include "CollisionDetection/LeftBoundCollider.hpp"
#include "CollisionDetection/LowerHorizontalBoundCollider.hpp"
#include "GameSubsystem.hpp"

void GameApplication::Setup() {
	engineParameters_["FullScreen"] = false;
	engineParameters_["WindowWidth"] = 1280;
	engineParameters_["WindowHeight"] = 720;
	engineParameters_["WindowResizable"] = false;

}

void GameApplication::Start() {
	GetSubsystem<Input>()->SetMouseVisible(true);
	GetSubsystem<Input>()->SetMouseGrabbed(false);

	RegisterObjects();
	context_->RegisterSubsystem(new GameSubsystem(context_));

	GetSubsystem<GameSubsystem>()->LoadGameLevel();

	SubscribeToEvent(E_POSTRENDERUPDATE, URHO3D_HANDLER(GameApplication, HandlePostRenderUpdate));
}

void GameApplication::Stop() {
}

void GameApplication::RegisterObjects() {
	TerrainController::RegisterObject(context_);
	TerrainCollisionShapeController::RegisterObject(context_);
	TerrainSpriteController::RegisterObject(context_);

	CameraController::RegisterObject(context_);

	AircraftMovingController::RegisterObject(context_);
	AircraftMouseController::RegisterObject(context_);
	AircraftBombsController::RegisterObject(context_);

	CollisionsAggregator::RegisterObject(context_);
	TerrainCollider::RegisterObject(context_);
	UpperBoundCollider::RegisterObject(context_);
	RightBoundCollider::RegisterObject(context_);
	LeftBoundCollider::RegisterObject(context_);
	LowerHorizontalBoundCollider::RegisterObject(context_);

	ExplosiveController::RegisterObject(context_);
	ShellController::RegisterObject(context_);
}

void GameApplication::HandlePostRenderUpdate(StringHash eventType, VariantMap& eventData) {
	GetSubsystem<GameSubsystem>()->scene_->GetComponent<PhysicsWorld2D>()->DrawDebugGeometry();
}
