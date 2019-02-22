// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Resource/JSONFile.h>
#include <Urho3D/Scene/Scene.h>
#include "TankSpawner.hpp"
#include "TankController.hpp"
#include "LandUnitMovingController.hpp"

void TankSpawner::Start()
{
	InstantiateTank(0.2f);
	InstantiateTank(0.7f);
}

void TankSpawner::InstantiateTank(float normalizedPos)
{
	auto resourceCache  = GetSubsystem<ResourceCache>();
	auto jsonPrefabFile = resourceCache->GetResource<JSONFile>("Data/Prefabs/Tank.json");
	auto jsonValue      = jsonPrefabFile->GetRoot();

	auto tank = GetScene()->CreateChild("Bomb", LOCAL);
	tank->LoadJSON(jsonValue);

	tank->CreateComponent<TankController>();
	tank->CreateComponent<LandUnitMovingController>();

	auto  terrain       = GetScene()->GetChild("Terrain")->GetComponent<TerrainController>();
	float terrainHeight = terrain->GetPositionFromNormalized(normalizedPos).y_ + 5;
	tank->SetPosition2D({terrain->GetPositionFromNormalized(normalizedPos).x_, terrainHeight});

}
