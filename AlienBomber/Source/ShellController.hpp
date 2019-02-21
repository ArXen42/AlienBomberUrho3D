#pragma once

#include "ExplosiveController.hpp"

using namespace Urho3D;

class ShellController : public LogicComponent
{
URHO3D_OBJECT(ShellController, LogicComponent);
public:
	static void RegisterObject(Context* context)
	{ context->RegisterFactory<ShellController>(); }

public:
	explicit ShellController(Context* context) : LogicComponent(context)
	{}

private:
	void Start() override;

	void OnTerrainCollision(Node* terrainNode);

	void OnRightBoundCollision(Node* verticalBoundNode);

	void OnLeftBoundCollision(Node* verticalBoundNode);

	ExplosiveController* explosiveController_ = nullptr;
};
