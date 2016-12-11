#include <Urho3D/Core/Context.h>
#include <Urho3D/Scene/LogicComponent.h>

using namespace Urho3D;

class TerrainSpriteController : public LogicComponent {
URHO3D_OBJECT(TerrainSpriteController, LogicComponent);
public:
	static void RegisterObject(Context* context) { context->RegisterFactory<TerrainSpriteController>(); }

public:
	TerrainSpriteController(Context* context) : LogicComponent(context) {}
	~TerrainSpriteController() override;

private:
	void Start() override;
	void InitializeSprite();
	void OnHeightmapUpdated();

	float Lerp(float from, float to, float factor) { return from + (to - from)*factor; }

	unsigned int terrainResolutionX_;
	unsigned int terrainResolutionY_;
};
