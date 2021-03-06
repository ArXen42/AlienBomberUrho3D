// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "AircraftBombsController.hpp"
#include "../ShellController.hpp"
#include "../CollisionDetection/CollisionsAggregator.hpp"
#include <Urho3D/Input/InputEvents.h>
#include <Urho3D/Scene/Scene.h>
#include <Urho3D/IO/Log.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Urho2D/RigidBody2D.h>

void AircraftBombsController::Start()
{
	SubscribeToEvent(E_KEYDOWN, URHO3D_HANDLER(AircraftBombsController, AircraftBombsController::HandleKeyDown));
}

void AircraftBombsController::DropBomb()
{
	auto resourceCache  = GetSubsystem<ResourceCache>();
	auto jsonPrefabFile = resourceCache->GetResource<JSONFile>("Data/Prefabs/Bomb.json");
	auto jsonValue      = jsonPrefabFile->GetRoot();

	auto bomb = GetScene()->CreateChild("Bomb", LOCAL);
	bomb->LoadJSON(jsonValue);
	bomb->CreateComponent<CollisionsAggregator>();
	bomb->CreateComponent<ShellController>();
	bomb->SetPosition2D(GetNode()->GetPosition2D() + Vector2::DOWN * 0.6f);
	bomb->GetComponent<RigidBody2D>()->SetLinearVelocity(
			GetComponent<RigidBody2D>()->GetLinearVelocity());
}

void AircraftBombsController::HandleKeyDown(StringHash eventType, VariantMap& eventData)
{
	if (eventData[KeyDown::P_KEY].GetInt() != KEY_SPACE) return;

	DropBomb();
}
