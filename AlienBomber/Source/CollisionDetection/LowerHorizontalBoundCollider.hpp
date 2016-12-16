#pragma once

#include <Urho3D/Core/Context.h>
#include "StaticColliderComponent.hpp"

class LowerHorizontalBoundCollider : public StaticColliderComponent {
URHO3D_OBJECT(StaticColliderComponent, LogicComponent);
public:
	static void RegisterObject(Context* context) { context->RegisterFactory<LowerHorizontalBoundCollider>(); }

public:
	LowerHorizontalBoundCollider(Context* context) : StaticColliderComponent(context) {}
};
