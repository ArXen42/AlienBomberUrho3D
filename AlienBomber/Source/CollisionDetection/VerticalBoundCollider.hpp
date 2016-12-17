#pragma once

#include <Urho3D/Core/Context.h>
#include "StaticColliderComponent.hpp"

class VerticalBoundCollider : public StaticColliderComponent {
URHO3D_OBJECT(StaticColliderComponent, LogicComponent);
public:
	static void RegisterObject(Context* context) { context->RegisterFactory<VerticalBoundCollider>(); }

public:
	VerticalBoundCollider(Context* context) : StaticColliderComponent(context) {}
};