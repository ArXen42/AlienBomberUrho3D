#pragma once

#include <Urho3D/Scene/LogicComponent.h>
#include <Urho3D/Core/Context.h>
#include <Urho3D/Scene/Node.h>
#include "ThirdParty/Signals/Signal.hpp"

using namespace Urho3D;

/// Предоставляет функционал взрывов
class ExplosiveController : public LogicComponent {
URHO3D_OBJECT(ExplosiveController, LogicComponent);
public:
	static void RegisterObject(Context* context) { context->RegisterFactory<ExplosiveController>(); }

	/// Оповещает о том, что на уровне произошло попадание и взрыв снаряда
	static Gallant::Signal2<ExplosiveController*, Node*> SomethingExploded;

public:
	ExplosiveController(Context* context) : LogicComponent(context) {}

	/// Оповещает о столкновении и взрыве снаряда.
	Gallant::Signal2<ExplosiveController*, Node*> Exploded;

	/// Вызывает события взрыва и удаляет ноду, к которой прикреплен этот компонент
	void Explode(Node* node) { Exploded.Emit(this, node), SomethingExploded.Emit(this, node), GetNode()->Remove(); }
};