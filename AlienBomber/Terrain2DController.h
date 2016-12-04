#pragma once

#include <Urho3D/Scene/LogicComponent.h>

using namespace Urho3D;

typedef unsigned int uint;

/// Представляет интерфейс для взаимодействия с ландшафтом и контроллирует его отображение.
class Terrain2DController : public LogicComponent {
URHO3D_OBJECT(Terrain2DController, LogicComponent);
public:
	Terrain2DController(Context* context) : LogicComponent(context), terrainLength_(4), terrainMaxHeight_(1) {}
	static void RegisterObject(Context* context);

	void Start() override;

	/// Деформирует ландшафт в указанной точке в указанном радиусе.
	void BlastDeform(uint x, uint radius);

	Vector<float>::ConstIterator GetHeightmapBegin() { return heightmap_->Begin(); }
	Vector<float>::ConstIterator GetHeightmapEnd() { return heightmap_->End(); }

private:
	void UpdateTerrainView() {
		UpdateCollisionChain();
		UpdateSprite();
	}
	void UpdateCollisionChain();
	void UpdateSprite();

	void GenerateHeightmap(uint length, float startHeight, float endHeight, float roughness);
	void MidpointDisplacement1D(float* vertices, uint l, uint r, float roughness);
	bool IsValid(float* vertices, uint size);

	float terrainLength_;
	float terrainMaxHeight_;

	Vector<float>* heightmap_;
};

