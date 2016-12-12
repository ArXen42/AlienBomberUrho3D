#include "ProjectileController.hpp"
#include "TerrainController.hpp"
#include <Urho3D/Urho2D/PhysicsEvents2D.h>
#include <Urho3D/IO/Log.h>
#include <Urho3D/Scene/Node.h>
#include <Urho3D/Scene/Scene.h>

void ProjectileController::Start() {
	SubscribeToEvent(E_PHYSICSBEGINCONTACT2D, URHO3D_HANDLER(ProjectileController, OnPhysicsBeginContact2D));
}

void ProjectileController::OnPhysicsBeginContact2D(StringHash eventType, VariantMap& eventData) {
	auto nodeaptr = eventData[PhysicsBeginContact2D::P_NODEA].GetPtr();
	auto nodea = dynamic_cast<Node*>(nodeaptr);

	nodea->GetComponent<TerrainController>()->BlastDeform(128, 3, 0.04f);
	GetNode()->Remove();
}
