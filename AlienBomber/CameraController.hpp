#pragma once

#include <Urho3D/Core/Context.h>
#include <Urho3D/Scene/LogicComponent.h>

using namespace Urho3D;

class CameraController : public LogicComponent {
URHO3D_OBJECT(CameraController, LogicComponent);
public:
	static void RegisterObject(Context* context) { context->RegisterFactory<CameraController>(); }

public:
	CameraController(Context* context) : LogicComponent(context) {}

private:
	void Start() override;
};