#include <Urho3D/Urho2D/CollisionEdge2D.h>
#include <Urho3D/IO/Log.h>
#include "UpperBoundCollider.hpp"

float UpperBoundCollider::ReflectDirectionAngle(float degAngle) {
	return -degAngle;
}

void UpperBoundCollider::Start() {
	URHO3D_LOGINFO("Why I don't see this message?");

	GetComponent<CollisionEdge2D>()->SetVertices(
			Vector2(-16, 3),
			Vector2(16, 3)
	);
}
