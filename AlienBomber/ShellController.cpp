#include "ShellController.hpp"
#include "TerrainController.hpp"
#include <Urho3D/Urho2D/PhysicsEvents2D.h>
#include <Urho3D/IO/Log.h>
#include <Urho3D/Scene/Node.h>
#include <Urho3D/Scene/Scene.h>

void ShellController::Start() {
	SubscribeToEvent(E_PHYSICSBEGINCONTACT2D, URHO3D_HANDLER(ShellController, OnPhysicsBeginContact2D));
}

void ShellController::OnPhysicsBeginContact2D(StringHash eventType, VariantMap& eventData) {
	UnsubscribeFromAllEvents();

	auto nodeA = dynamic_cast<Node*>(eventData[PhysicsBeginContact2D::P_NODEA].GetPtr());
	auto nodeB = dynamic_cast<Node*>(eventData[PhysicsBeginContact2D::P_NODEB].GetPtr());

	auto collidedNode = nodeB == GetNode() ? nodeA : nodeB;

	Exploded.Emit(collidedNode);
	SomeShellExploded.Emit(this, collidedNode);

	GetNode()->Remove();
}
