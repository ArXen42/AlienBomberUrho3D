// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <Urho3D/Core/Object.h>
#include <Urho3D/Scene/Node.h>
#include <Urho3D/Urho2D/PhysicsEvents2D.h>
#include <Urho3D/IO/Log.h>
#include "CollisionsAggregator.hpp"
#include "StaticColliderComponent.hpp"

SharedPtr<Gallant::Signal1<Node*>> CollisionsAggregator::GetSignal(const TypeInfo* colliderTypeInfo) {
	assert(colliderTypeInfo->IsTypeOf(StaticColliderComponent::GetTypeStatic()));

	if (!collisionSignals_.Contains(colliderTypeInfo->GetType())){
		collisionSignals_[colliderTypeInfo->GetType()] = new Gallant::Signal1<Node*>();
	}

	return collisionSignals_[colliderTypeInfo->GetType()];
}

void CollisionsAggregator::Start() {
	SubscribeToEvent(E_PHYSICSBEGINCONTACT2D, URHO3D_HANDLER(CollisionsAggregator, OnPhysicsBeginContact2D));
}

void CollisionsAggregator::OnPhysicsBeginContact2D(StringHash eventType, VariantMap& eventData) {
	auto nodeA = dynamic_cast<Node*>(eventData[PhysicsBeginContact2D::P_NODEA].GetPtr());
	auto nodeB = dynamic_cast<Node*>(eventData[PhysicsBeginContact2D::P_NODEB].GetPtr());

	if (nodeA != node_ && nodeB != node_) return;

	auto collidedNode = nodeB == node_ ? nodeA : nodeB;
	auto staticColliderComponent = collidedNode->GetDerivedComponent<StaticColliderComponent>();
	if (staticColliderComponent == nullptr) return;

	SharedPtr<Gallant::Signal1<Node*>> signal;
	collisionSignals_.TryGetValue(staticColliderComponent->GetType(), signal);

	if (signal.NotNull())
		signal->Emit(collidedNode);
}