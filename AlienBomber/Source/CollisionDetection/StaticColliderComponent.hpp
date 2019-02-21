#pragma once

#include <Urho3D/Scene/LogicComponent.h>
#include <Urho3D/IO/Log.h>

using namespace Urho3D;

/// Базовый класс для коллайдеров.
/// Предназначен для использования в паре с CollisionShape2D.
/// Это не активный физический компонент - он только идентифицирует категорию статических объектов, с которыми можно столкнуться.
class StaticColliderComponent : public LogicComponent
{
protected:
	explicit StaticColliderComponent(Context* context) : LogicComponent(context)
	{};
};
