#include <Urho3D/Core/Timer.h>
#include <Urho3D/IO/Log.h>
#include "TerrainController.hpp"

void TerrainController::DelayedStart() {
	GenerateHeightmap(Random(0.3f, 0.6f), Random(0.3f, 0.6f), 2.f);
	heightmapUpdated_.Emit();
}

void TerrainController::GenerateHeightmap(float startHeight, float endHeight, float roughness) {
	SetRandomSeed(Time::GetSystemTime());
	unsigned int size = heightmap_.Size();

	heightmap_[0] = startHeight;
	heightmap_[size - 1] = endHeight;

	MidpointDisplacement1D(0, size - 1, roughness/size);
	while (!IsHeightmapValid()) {
		MidpointDisplacement1D(0, size - 1, roughness/size);
		URHO3D_LOGINFO("Invalid heightmap, generating another one...");
	}
}

void TerrainController::MidpointDisplacement1D(unsigned int l, unsigned int r, float roughness) {
	const unsigned int delta = r - l;
	if (delta > 1) {
		heightmap_[(l + r)/2] = (heightmap_[l] + heightmap_[r])/2 +
		                        (Random()*delta - delta*0.5f)*roughness;

		MidpointDisplacement1D(l, (l + r)/2, roughness);
		MidpointDisplacement1D((l + r)/2, r, roughness);
	}
}

bool TerrainController::IsHeightmapValid() {
	auto p = heightmap_.Begin();
	while (p < heightmap_.End()) {
		if (*p < 0 || *p > 1) return false;
		++p;
	}
	return true;
}
void TerrainController::BlastDeform(unsigned int index, unsigned int radius, float depth) {
	for (int i = index - radius; i <= index + radius; i++) {
		if (i < 0 || i > heightmap_.Size() - 1) continue;

//		heightmap_[i] -= radius*Sin(M_DEGTORAD*static_cast<float>(i - index)/(2*radius));

		float delta = Abs(static_cast<float>(i) - index);
		float factor = delta/radius;

		float value = heightmap_[i] - (1 - factor*factor*factor)*depth;
		heightmap_[i] = value > 0 ? value : 0;
	}

	URHO3D_LOGINFO("END");

	heightmapUpdated_.Emit();
}
