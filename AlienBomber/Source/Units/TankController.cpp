// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "TankController.hpp"

void TankController::Start()
{
	ExplosiveController::SomethingExploded.Connect(this, &TankController::OnSomethingExploded);
}

void TankController::Stop()
{
	ExplosiveController::SomethingExploded.Disconnect(this, &TankController::OnSomethingExploded);
}

void TankController::OnSomethingExploded(ExplosiveController* shell, Node* collidedNode)
{
	auto delta = shell->GetNode()->GetPosition2D() - GetNode()->GetPosition2D();

	if (delta.Length() <= shell->GetExplosionRange())
	{
		ExplosiveController::SomethingExploded.Disconnect(this, &TankController::OnSomethingExploded);
		GetNode()->Remove();
	}
}
