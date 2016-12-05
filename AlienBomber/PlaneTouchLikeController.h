#pragma once

#include <Urho3D/Scene/LogicComponent.h>
#include <Urho3D/Core/Context.h>

using namespace Urho3D;

class PlaneTouchLikeController : public LogicComponent {
URHO3D_OBJECT(PlaneTouchLikeController, LogicComponent);
public:
	PlaneTouchLikeController(Context* context) : LogicComponent(context) {}

	static void RegisterObject(Context* context) { context->RegisterFactory<PlaneTouchLikeController>(); }

	void Start() override;

private:
	void HandleMouseButtonDown(StringHash eventType, VariantMap &eventData);
//	void HandleTouch(); //TODO
};