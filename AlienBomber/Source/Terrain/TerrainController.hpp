#pragma once

#include <Urho3D/Scene/LogicComponent.h>
#include <Urho3D/Core/Context.h>
#include "../ThirdParty/Signals/Signal.hpp"
#include "../ExplosiveController.hpp"

using namespace Urho3D;

struct HeightmapUpdateDiff {
	HeightmapUpdateDiff(const unsigned int startIndex, const unsigned int endIndex) : startIndex_(startIndex),
	                                                                                  endIndex_(endIndex) {
		assert(endIndex >= startIndex);
	}

	const unsigned int startIndex_;
	const unsigned int endIndex_;
};

/// Основной контроллер ландшафта, представляет карту высот.
class TerrainController : public LogicComponent {
URHO3D_OBJECT(TerrainController, LogicComponent);
public:
	static void RegisterObject(Context* context) { context->RegisterFactory<TerrainController>(); }

	static const float TERRAIN_LENGTH;
	static const float MAX_TERRAIN_HEIGHT;

public:
	TerrainController(Context* context) : LogicComponent(context) {}

	const Vector<float>* GetHeightmap() const { return &heightmap_; }

	/// Возвращает координаты на карте высот из нормализованной горизонтальной координаты.
	Vector2 GetPositionFromNormalized(float normalizedX);

	Gallant::Signal1<HeightmapUpdateDiff> HeightmapUpdated;

private:
	//Использование DelayedStart позволяет "дождаться" создания и подписки зависимых компонентов
	void DelayedStart() override;
	void Stop() override;

	/// Проверяет, произошло ли столкновение с ландшафтом и деформирует его.
	void OnSomethingExploded(ExplosiveController* shell, Node* collidedNode);

	void GenerateHeightmap(float startHeight, float endHeight, float roughness);
	void MidpointDisplacement1D(unsigned int l, unsigned int r, float roughness);
	bool IsHeightmapValid();

	/// Деформирует ландшафт в указанной точке.
	void BlastDeform(unsigned int index, unsigned int radius, float depth);

	Vector<float> heightmap_ = Vector<float>(1024);
};
