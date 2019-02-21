#pragma once

#include <Urho3D/Core/Context.h>
#include "StaticColliderComponent.hpp"
#include <Urho3D/IO/Log.h>

class TerrainCollider : public StaticColliderComponent
{
URHO3D_OBJECT(TerrainCollider, StaticColliderComponent);
public:
	static void RegisterObject(Context* context)
	{ context->RegisterFactory<TerrainCollider>(); }

public:
	explicit TerrainCollider(Context* context) : StaticColliderComponent(context)
	{}
};
