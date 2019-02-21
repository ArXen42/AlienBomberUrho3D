// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <Urho3D/Graphics/Camera.h>
#include <Urho3D/Scene/Scene.h>
#include <Urho3D/Urho2D/CollisionEdge2D.h>
#include "RightBoundCollider.hpp"
#include "LeftBoundCollider.hpp"

void RightBoundCollider::DelayedStart()
{
	auto cameraNode = GetScene()->GetChild("MainCamera");
	auto camera     = cameraNode->GetComponent<Camera>();

	const float verticalSize   = camera->GetOrthoSize();
	const float horizontalSize = verticalSize * camera->GetAspectRatio();

	GetNode()->SetPosition2D(Vector2(horizontalSize / 2, 0)
	                         + cameraNode->GetPosition2D());

	GetComponent<CollisionEdge2D>()->SetVertices(
			Vector2(0, verticalSize / 2),
			Vector2(0, -verticalSize / 2)
	);

	opposite_ = GetScene()->GetChild("LeftBound")->GetDerivedComponent<LeftBoundCollider>();
}

Vector2 RightBoundCollider::GetOppositePosition(Vector2 position)
{
	return GetOppositeBound()->GetPositionOnBound(position.y_);
}

