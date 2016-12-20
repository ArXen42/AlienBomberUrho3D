#pragma once

#include <Urho3D/Core/Context.h>
#include <Urho3D/Scene/LogicComponent.h>
#include "../ThirdParty/Signals/Signal.hpp"

using namespace Urho3D;

/// Позволяет выбирать между подпиской на E_PHYSICSBEGINCONTACT2D и E_PHYSICSENDCONTACT2D
enum class CollisionType {
	BeginContact, EndContact
};

/// Предоставляет доступ к событиям столкновения с определенной группой коллайдеров (StaticColliderComponent).
/// Возможна раздельная подписка на BeginContact и EndContact.
/// Не поддерживает полиморфизм - сигнал связан с конкретным типом коллайдера, столкновение с наследником регистрироваться не будет.
class CollisionsAggregator : public LogicComponent {
URHO3D_OBJECT(CollisionsAggregator, LogicComponent);
public:
	static void RegisterObject(Context* context) { context->RegisterFactory<CollisionsAggregator>(); }

public:
	CollisionsAggregator(Context* context) : LogicComponent(context) {}

	/// Возвращает сигнал, вызываемый при столкновении указанного типа с объектом, имеющим указанный компонент коллайдера.
	/// В случае, если сигнал был запрошен первый раз, создает его.
	SharedPtr<Gallant::Signal1<Node*>> GetSignal(const TypeInfo* colliderTypeInfo,
	                                             CollisionType type = CollisionType::BeginContact);

private:
	void Start() override;
	void OnContact(CollisionType type, VariantMap& eventData);

	void OnPhysicsBeginContact2D(StringHash eventType, VariantMap& eventData) {
		OnContact(CollisionType::BeginContact, eventData);
	}
	void OnPhysicsEndContact2D(StringHash eventType, VariantMap& eventData) {
		OnContact(CollisionType::EndContact, eventData);
	}

	HashMap<StringHash, SharedPtr<Gallant::Signal1<Node*>>> collisionBeginContactSignals_;
	HashMap<StringHash, SharedPtr<Gallant::Signal1<Node*>>> collisionEndContactSignals_;
};

