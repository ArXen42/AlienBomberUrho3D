#pragma once

#include <Urho3D/Core/Context.h>
#include "StaticColliderComponent.hpp"

class UpperBoundCollider : public StaticColliderComponent
{
URHO3D_OBJECT(UpperBoundCollider, StaticColliderComponent);
public:
	static void RegisterObject(Context* context)
	{ context->RegisterFactory<UpperBoundCollider>(); }

public:
	explicit UpperBoundCollider(Context* context) : StaticColliderComponent(context)
	{}

	void Start() override;

	float ReflectDirectionAngle(float degAngle);
};
