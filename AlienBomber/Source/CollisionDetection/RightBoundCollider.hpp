#pragma once

#include <Urho3D/Core/Context.h>
#include <Urho3D/Scene/Node.h>
#include "StaticColliderComponent.hpp"

class LeftBoundCollider;

class RightBoundCollider : public StaticColliderComponent
{
URHO3D_OBJECT(RightBoundCollider, StaticColliderComponent);
public:
	static void RegisterObject(Context* context)
	{ context->RegisterFactory<RightBoundCollider>(); }

public:
	RightBoundCollider(Context* context) : StaticColliderComponent(context)
	{}

	/// Возвращает противоположную границу.
	LeftBoundCollider* GetOppositeBound()
	{ return opposite_; }

	/// Возвращает проекцию позиции на эту границу.
	Vector2 GetPositionOnBound(float y)
	{ return Vector2(GetNode()->GetPosition2D().x_, y); }

	/// Возвращает проекцию позиции на противоположную границу.
	Vector2 GetOppositePosition(Vector2 position);

private:
	void DelayedStart() override;

	LeftBoundCollider* opposite_ = nullptr;
};