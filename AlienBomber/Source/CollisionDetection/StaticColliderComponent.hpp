#pragma once

#include <Urho3D/Scene/LogicComponent.h>

using namespace Urho3D;

/// Базовый класс для коллайдеров.
/// Предназначен для использования в паре с CollisionShape2D.
/// Это не активный физический компонент - он только идентифицирует категорию статических объектов, с которыми можно столкнуться.
class StaticColliderComponent : public LogicComponent {
URHO3D_OBJECT(StaticColliderComponent, LogicComponent);

protected:
	StaticColliderComponent(Context* context) : LogicComponent(context) {};
};
