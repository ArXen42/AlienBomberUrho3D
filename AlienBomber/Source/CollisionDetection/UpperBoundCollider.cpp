// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <Urho3D/Urho2D/CollisionEdge2D.h>
#include <Urho3D/IO/Log.h>
#include "UpperBoundCollider.hpp"

float UpperBoundCollider::ReflectDirectionAngle(float degAngle) {
	return -degAngle;
}

void UpperBoundCollider::Start() {
//	GetComponent<CollisionEdge2D>()->SetVertices(
//			Vector2(-16, 3),
//			Vector2(16, 3)
//	);
}
