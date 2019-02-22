// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <Urho3D/Scene/Node.h>
#include <Urho3D/Core/Timer.h>
#include <Urho3D/IO/Log.h>
#include "TerrainController.hpp"


Vector2 TerrainController::GetPositionFromNormalized(float normalizedX)
{
	assert(normalizedX >= 0);
	assert(normalizedX <= 1);

	const auto index = static_cast<unsigned int>((heightmap_.Size() - 1) * normalizedX);
	return Vector2(normalizedX * TerrainLength - TerrainLength / 2,
	               heightmap_[index] * MaxTerrainLength - MaxTerrainLength / 2);
}

void TerrainController::DelayedStart()
{
	ExplosiveController::SomethingExploded.Connect(this, &TerrainController::OnSomethingExploded);

	GenerateHeightmap(Random(0.3f, 0.6f), Random(0.3f, 0.6f), 1.5f);
}

void TerrainController::Stop()
{
	ExplosiveController::SomethingExploded.Disconnect(this, &TerrainController::OnSomethingExploded);
}

void TerrainController::OnSomethingExploded(ExplosiveController* shell, Node* collidedNode)
{
	if (collidedNode != GetNode()) return;

	float deltaX      = shell->GetNode()->GetPosition2D().x_ - GetNode()->GetPosition2D().x_;
	float normalizedX = deltaX / TerrainLength + 0.5f;
	assert(normalizedX >= 0 && normalizedX <= 1);

	auto index = static_cast<unsigned int>((heightmap_.Size() - 1) * normalizedX);
	BlastDeform(index, 12, 0.001f * shell->GetExplosionPower());
}

void TerrainController::GenerateHeightmap(float startHeight, float endHeight, float roughness)
{
	SetRandomSeed(Time::GetSystemTime());
	unsigned int size = heightmap_.Size();

	heightmap_[0]        = startHeight;
	heightmap_[size - 1] = endHeight;

	MidpointDisplacement1D(0, size - 1, roughness / size);
	while (!IsHeightmapValid())
	{
		MidpointDisplacement1D(0, size - 1, roughness / size);
		URHO3D_LOGINFO("Invalid heightmap, generating another one...");
	}

	HeightmapUpdated.Emit({0, size - 1});
}

void TerrainController::MidpointDisplacement1D(unsigned int l, unsigned int r, float roughness)
{
	const unsigned int delta = r - l;
	if (delta > 1)
	{
		heightmap_[(l + r) / 2] = (heightmap_[l] + heightmap_[r]) / 2 +
		                          (Random() - 0.5f) * delta * roughness;

		MidpointDisplacement1D(l, (l + r) / 2, roughness);
		MidpointDisplacement1D((l + r) / 2, r, roughness);
	}
}

bool TerrainController::IsHeightmapValid()
{
	auto p = heightmap_.Begin();
	while (p < heightmap_.End())
	{
		if (*p < 0 || *p > 1) return false;
		++p;
	}
	return true;
}

//TODO: улучшить алгоритм взрыва
void TerrainController::BlastDeform(unsigned int index, unsigned int radius, float depth)
{
	for (int i = index - radius; i <= index + radius; i++)
	{
		if (i < 0 || i > heightmap_.Size() - 1) continue;

		float delta  = Abs(static_cast<float>(i) - index);
		float factor = delta / radius;

		float value = heightmap_[i] - (1 - factor * factor * factor) * depth;
		heightmap_[i] = value > 0 ? value : 0;
	}

	int          left  = index - radius;
	unsigned int right = index + radius;

	auto startIndex = static_cast<unsigned int>(left > 0 ? left : 0);
	auto endIndex   = right < heightmap_.Size() ? right : heightmap_.Size() - 1;

	HeightmapUpdated.Emit({startIndex, endIndex});
}
