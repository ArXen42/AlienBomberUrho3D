#include "Terrain2DController.h"
#include <Urho3D/Urho2D/CollisionChain2D.h>
#include <Urho3D/Core/Context.h>
#include <Urho3D/IO/Log.h>
#include <Urho3D/Core/Timer.h>
#include <Urho3D/Urho2D/StaticSprite2D.h>
#include <Urho3D/Urho2D/Sprite2D.h>
#include <Urho3D/Urho2D/SpriterData2D.h>
#include <Urho3D/Graphics/Graphics.h>
#include <Urho3D/Graphics/Texture2D.h>

void Terrain2DController::RegisterObject(Context* context) {
	context->RegisterFactory<Terrain2DController>();
}

void Terrain2DController::Start() {
	GenerateHeightmap(256, Random(0.3f, 0.6f), Random(0.3f, 0.6f), 2.f);
	InitializeSprite();
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
	}

	collisionChain->SetVertices(vertices);
}

void Terrain2DController::InitializeSprite() {
	auto texture = new Texture2D(context_);
	texture->SetFilterMode(TextureFilterMode::FILTER_NEAREST);
	texture->SetNumLevels(1);
	texture->SetSize(terrainResolutionX_, terrainResolutionY_, Graphics::GetRGBAFormat());
	auto sprite = new Sprite2D(context_);
	sprite->SetRectangle(IntRect(0, 0, terrainResolutionX_, terrainResolutionY_));
	sprite->SetTexture(texture);
	GetComponent<StaticSprite2D>()->SetSprite(sprite);
}
void Terrain2DController::UpdateSprite() {
	//TODO: сопоставить размер спрайта с картой высот, выполнять сглаживание, оптимизации
	auto image = new Image(context_);
	image->SetSize(terrainResolutionX_, terrainResolutionY_, 4);

	int height = image->GetHeight();
	int width = image->GetWidth();
	uint32_t color = Color(0.1f, 0.6f, 0, 1).ToUInt();

	for (int column = 0; column < width; column++) {
		uint heightmapIndex = (uint)((float)column*(heightmap_->Size() - 1)/(width - 1));
		uint limit = (uint)(heightmap_->At(heightmapIndex)*height);

		for (int row = 0; row < limit; row++) image->SetPixelInt(column, height - 1 - row, color);
		for (int row = limit; row < height; row++) image->SetPixelInt(column, height - 1 - row, 0x00000000);
	}

	GetComponent<StaticSprite2D>()->GetSprite()->GetTexture()->SetData(image);
}

void Terrain2DController::GenerateHeightmap(uint length, float startHeight, float endHeight, float roughness) {
	SetRandomSeed(Time::GetSystemTime());
	float* vertices = new float[length];
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
