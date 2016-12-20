#pragma once

#include "StaticColliderComponent.hpp"
#include <Urho3D/Core/Context.h>
#include "RightBoundCollider.hpp"

class RightBoundCollider;

class LeftBoundCollider : public StaticColliderComponent {
URHO3D_OBJECT(LeftBoundCollider, StaticColliderComponent);
public:
	static void RegisterObject(Context* context) { context->RegisterFactory<LeftBoundCollider>(); }

public:
	LeftBoundCollider(Context* context) : StaticColliderComponent(context) {}

	/// Возвращает противоположную границу.
	RightBoundCollider* GetOppositeBound() { return opposite_; }

	/// Возвращает проекцию позиции на эту границу.
	Vector2 GetPositionOnBound(float y) { return Vector2(GetNode()->GetPosition2D().x_, y); }

	/// Возвращает проекцию позиции на противоположную границу.
	Vector2 GetOppositePosition(Vector2 position);;

private:
	void DelayedStart() override;

	RightBoundCollider* opposite_ = nullptr;
};
