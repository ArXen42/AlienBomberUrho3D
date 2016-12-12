#pragma once

#include <Urho3D/Scene/LogicComponent.h>
#include <Urho3D/Core/Context.h>
#include "Signal.hpp"

using namespace Urho3D;

/// Основной контроллер ландшафта, представляет карту высот.
class TerrainController : public LogicComponent {
URHO3D_OBJECT(TerrainController, LogicComponent);
public:
	static void RegisterObject(Context* context) { context->RegisterFactory<TerrainController>(); }

public:
	TerrainController(Context* context) : LogicComponent(context) {}

	const Vector<float>* GetHeightmap() const { return &heightmap_; }

	Gallant::Signal0<void(void)> heightmapUpdated_;

	void BlastDeform(unsigned int index, unsigned int radius, float depth);

	const float terrainLength_ = 32;
	const float maxTerrainHeight_ = 4;

private:
	//Использование DelayedStart позволяет "дождаться" создания и подписки зависимых компонентов
	void DelayedStart() override;

	void GenerateHeightmap(float startHeight, float endHeight, float roughness);
	void MidpointDisplacement1D(unsigned int l, unsigned int r, float roughness);
	bool IsHeightmapValid();

	Vector<float> heightmap_ = Vector<float>(256);
};

