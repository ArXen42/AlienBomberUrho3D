#pragma once

#include <Urho3D/Core/Context.h>
#include "StaticColliderComponent.hpp"

class TerrainCollider : public StaticColliderComponent {
URHO3D_OBJECT(StaticColliderComponent, LogicComponent);
public:
	static void RegisterObject(Context* context) { context->RegisterFactory<TerrainCollider>(); }

public:
	TerrainCollider(Context* context) : StaticColliderComponent(context) {}
};
