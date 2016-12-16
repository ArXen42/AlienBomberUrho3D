#pragma once

#include <Urho3D/Core/Context.h>
#include "StaticColliderComponent.hpp"

class UpperBoundCollider : public StaticColliderComponent {
URHO3D_OBJECT(StaticColliderComponent, LogicComponent);
public:
	static void RegisterObject(Context* context) { context->RegisterFactory<UpperBoundCollider>(); }

public:
	UpperBoundCollider(Context* context) : StaticColliderComponent(context) {}
};
