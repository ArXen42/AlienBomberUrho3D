#pragma once

#include <Urho3D/Core/Context.h>
#include <Urho3D/Scene/LogicComponent.h>
#include "ThirdParty/Signals/Signal.hpp"

using namespace Urho3D;

class ShellController : public LogicComponent {
URHO3D_OBJECT(ShellController, LogicComponent);
public:
	static void RegisterObject(Context* context) { context->RegisterFactory<ShellController>(); }

	/// Оповещает о том, что на уровне произошло попадание и взрыв снаряда
	static Gallant::Signal2<ShellController*, Node*> SomeShellExploded;

public:
	ShellController(Context* context) : LogicComponent(context) {}

	/// Оповещает о столкновении и взрыве снаряда.
	Gallant::Signal1<Node*> Exploded;

private:
	void Start() override;

	void OnTerrainCollision(Node* terrainNode);
	void OnRightBoundCollision(Node* verticalBoundNode);
	void OnLeftBoundCollision(Node* verticalBoundNode);
};
