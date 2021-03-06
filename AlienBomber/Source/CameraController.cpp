// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <Urho3D/Scene/Scene.h>
#include <Urho3D/Graphics/Camera.h>
#include <Urho3D/Graphics/Viewport.h>
#include <Urho3D/Graphics/Renderer.h>
#include "CameraController.hpp"
#include "Terrain/TerrainController.hpp"

void CameraController::Start()
{
	auto camera   = GetComponent<Camera>();
	auto viewport = new Viewport(context_, GetScene(), camera);
	GetSubsystem<Renderer>()->SetViewport(0, viewport);

	float aspectRatio = camera->GetAspectRatio();
	float orthoSize   = TerrainController::TerrainLength / aspectRatio;
	camera->SetOrthoSize(orthoSize);
	//Хак для того, чтобы получить корректное соотношение сторон в контроллерах коллайдеров границ
	camera->SetAspectRatioInternal(aspectRatio);

	Vector2 terrainPosition = GetScene()->GetChild("Terrain")->GetPosition2D();
	float   verticalOffset  = (orthoSize - TerrainController::MaxTerrainLength) / 2;
	GetNode()->SetPosition2D(terrainPosition + Vector2(0, verticalOffset));
}
