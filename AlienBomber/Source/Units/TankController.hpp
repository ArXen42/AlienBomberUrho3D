#pragma onc       e

#include <Urho3D/Core/Context.h>
#include <Urho3D/Scene/LogicComponent.h>
#include "../ExplosiveController.hpp"

using namespace Urho3D;

class TankController : public LogicComponent
{
URHO3D_OBJECT(TankController, LogicComponent)

public:
	static void RegisterObject(Context* context)
	{ context->RegisterFactory<TankController>(); }

public:
	explicit TankController(Context* context) : LogicComponent(context)
	{};

private:
	void Start() override;

	void Stop() override;

	void OnSomethingExploded(ExplosiveController* shell, Node* collidedNode);
};