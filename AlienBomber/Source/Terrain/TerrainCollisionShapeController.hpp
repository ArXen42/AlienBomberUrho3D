#include <Urho3D/Core/Context.h>
#include <Urho3D/Scene/LogicComponent.h>
#include "TerrainController.hpp"

using namespace Urho3D;

class TerrainCollisionShapeController : public LogicComponent {
URHO3D_OBJECT(TerrainCollisionShapeController, LogicComponent);
public:
	static void RegisterObject(Context* context) { context->RegisterFactory<TerrainCollisionShapeController>(); }

public:
	TerrainCollisionShapeController(Context* context) : LogicComponent(context) {}

private:
	void Start() override;
	void Stop() override;
	void OnHeightmapUpdated(HeightmapUpdateDiff diff);

	WeakPtr<TerrainController> terrainController_;
};