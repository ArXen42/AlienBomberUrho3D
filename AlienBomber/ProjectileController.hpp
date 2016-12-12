#pragma once

#include <Urho3D/Core/Context.h>
#include <Urho3D/Scene/LogicComponent.h>

using namespace Urho3D;

class ProjectileController : public LogicComponent {
URHO3D_OBJECT(ProjectileController, LogicComponent);
public:
	static void RegisterObject(Context* context) { context->RegisterFactory<ProjectileController>(); }

public:
	ProjectileController(Context* context) : LogicComponent(context) {}

private:
public:
	void Start() override;
private:
	void OnPhysicsBeginContact2D(StringHash eventType, VariantMap& eventData);
};

