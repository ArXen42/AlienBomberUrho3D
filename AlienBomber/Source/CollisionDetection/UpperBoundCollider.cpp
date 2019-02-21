// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <Urho3D/Urho2D/CollisionEdge2D.h>
#include <Urho3D/Scene/Scene.h>
#include <Urho3D/Graphics/Camera.h>
#include "UpperBoundCollider.hpp"

float UpperBoundCollider::ReflectDirectionAngle(float degAngle)
{
	return -degAngle;
}

void UpperBoundCollider::Start()
{
	auto cameraNode = GetScene()->GetChild("MainCamera");
	auto camera     = cameraNode->GetComponent<Camera>();

	const float verticalSize   = camera->GetOrthoSize();
	const float horizontalSize = verticalSize * camera->GetAspectRatio();

	GetComponent<CollisionEdge2D>()->SetVertices(
			Vector2(-horizontalSize / 2, verticalSize / 2) + cameraNode->GetPosition2D(),
			Vector2(horizontalSize / 2, verticalSize / 2) + cameraNode->GetPosition2D()
	);
}
