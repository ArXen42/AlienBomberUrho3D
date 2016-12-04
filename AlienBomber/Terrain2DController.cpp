#include "Terrain2DController.h"
#include <Urho3D/Urho2D/CollisionChain2D.h>
#include <Urho3D/Core/Context.h>
#include <Urho3D/IO/Log.h>
#include <Urho3D/Core/Timer.h>
#include <Urho3D/Urho2D/StaticSprite2D.h>
#include <Urho3D/Urho2D/Sprite2D.h>
#include <Urho3D/Graphics/Texture2D.h>

void Terrain2DController::RegisterObject(Context* context) {
	context->RegisterFactory<Terrain2DController>();
}

void Terrain2DController::Start() {
	GenerateHeightmap(256, Random(0.3f, 0.6f), Random(0.3f, 0.6f), 2.f);
	UpdateTerrainView();
}

void Terrain2DController::BlastDeform(uint x, uint radius) {
	//TODO: деформировать
}

void Terrain2DController::UpdateCollisionChain() {

	auto collisionChain = GetComponent<CollisionChain2D>();
	unsigned int size = heightmap_->Size();
	auto& vertices = *new PODVector<Vector2>(size);
	for (uint i = 0; i < size; i++) {
		vertices[i] = Vector2(i*terrainLength_/(size - 1), heightmap_->At(i)*terrainMaxHeight_) -
		              Vector2(terrainLength_/2, terrainMaxHeight_/2);
//		URHO3D_LOGINFO((String)i + "  " + vertices[i].ToString());
	}

	collisionChain->SetVertices(vertices);
}

void Terrain2DController::UpdateSprite() {
//	auto spriteComponent = GetSubsystem<StaticSprite2D>();
//	auto sprite = spriteComponent->GetSprite();
//	auto texture2D = sprite->GetTexture();
//	auto image = texture2D->GetData()
}

void Terrain2DController::GenerateHeightmap(uint length, float startHeight, float endHeight, float roughness) {
	SetRandomSeed(Time::GetSystemTime());
	auto vertices = new float[length];
	vertices[0] = startHeight;
	vertices[length - 1] = endHeight;

	MidpointDisplacement1D(vertices, 0, length - 1, roughness/length);
	while (!IsValid(vertices, length)) {
		MidpointDisplacement1D(vertices, 0, length - 1, roughness/(length - 1));
		URHO3D_LOGINFO("Invalid heightmap, generating another one...");
	}

	heightmap_ = new Vector<float>(vertices, length);
	delete[] vertices;
}

void Terrain2DController::MidpointDisplacement1D(float* vertices, uint l, uint r, float roughness) {
	const uint delta = r - l;
	if (delta > 1) {
		vertices[(l + r)/2] = (vertices[l] + vertices[r])/2 +
		                      (Random()*delta - delta*0.5f)*roughness;

		MidpointDisplacement1D(vertices, l, (l + r)/2, roughness);
		MidpointDisplacement1D(vertices, (l + r)/2, r, roughness);
	}
}
bool Terrain2DController::IsValid(float* vertices, uint size) {
	float* p = vertices;
	while (p < vertices + size) {
		if (*p < 0 || *p > 1) return false;
		++p;
	}
	return true;
}
