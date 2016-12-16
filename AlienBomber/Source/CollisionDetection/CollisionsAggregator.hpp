#pragma once

#include <Urho3D/Core/Context.h>
#include <Urho3D/Scene/LogicComponent.h>
#include "../ThirdParty/Signals/Signal.hpp"

using namespace Urho3D;

/// Предоставляет доступ к событиям столкновения с определенной группой коллайдеров (StaticColliderComponent).
class CollisionsAggregator : public LogicComponent {
URHO3D_OBJECT(CollisionsAggregator, LogicComponent);
public:
	static void RegisterObject(Context* context) { context->RegisterFactory<CollisionsAggregator>(); }

public:
	CollisionsAggregator(Context* context) : LogicComponent(context) {}

	/// Возвращает сигнал, вызываемый при столкновении с объектом, имеющим указанный компонент коллайдера.
	/// В случае, если сигнал был запрошен первый раз, создает его.
	SharedPtr<Gallant::Signal1<Node*>> GetSignal(const TypeInfo* colliderTypeInfo);

private:
	void Start() override;
	void OnPhysicsBeginContact2D(StringHash eventType, VariantMap& eventData);

	HashMap<StringHash, SharedPtr<Gallant::Signal1<Node*>>> collisionSignals_;
};