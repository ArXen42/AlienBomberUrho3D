// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <Urho3D/Graphics/Texture2D.h>
#include <Urho3D/Graphics/Graphics.h>
#include <Urho3D/Urho2D/Sprite2D.h>
#include <Urho3D/Urho2D/StaticSprite2D.h>
#include <Urho3D/Scene/Node.h>
#include "TerrainSpriteController.hpp"


void TerrainSpriteController::Start() {
	terrainController_ = GetNode()->GetParentComponent<TerrainController>();
	terrainController_->HeightmapUpdated.Connect(this,
	                                             &TerrainSpriteController::OnHeightmapUpdated);

	terrainResolutionX_ = static_cast<unsigned int>(TerrainController::TERRAIN_LENGTH*100);
	terrainResolutionY_ = static_cast<unsigned int>(TerrainController::MAX_TERRAIN_HEIGHT*100);

	InitializeSprite();
}

void TerrainSpriteController::InitializeSprite() {
	auto texture = new Texture2D(context_);
	texture->SetFilterMode(TextureFilterMode::FILTER_NEAREST);
	texture->SetNumLevels(1);
	texture->SetSize(terrainResolutionX_, terrainResolutionY_, Graphics::GetRGBAFormat());

	auto sprite = new Sprite2D(context_);
	sprite->SetRectangle(IntRect(0, 0, terrainResolutionX_, terrainResolutionY_));
	sprite->SetTexture(texture);

	GetComponent<StaticSprite2D>()->SetSprite(sprite);
}

void TerrainSpriteController::OnHeightmapUpdated(HeightmapUpdateDiff diff) {
	auto heightmap = terrainController_->GetHeightmap();

	//TODO: при необходимости оптимизировать с использованием diff и прямого доступа к точкам изображения
	Image image(context_);
	image.SetSize(terrainResolutionX_, terrainResolutionY_, 4);

	int height = image.GetHeight();
	int width = image.GetWidth();
	unsigned int color = Color(0.1f, 0.4f, 0, 1).ToUInt();
	unsigned int heightmapSize = heightmap->Size();

	// Цвет до округленного вниз индекса - color.
	// Следующий пиксель полупрозрачный, прозрачность определяется величиной округления.
	for (unsigned int column = 0; column < width; column++) {
		auto flooredIndex = static_cast<unsigned int>(
				std::floor(static_cast<float>(column)*(heightmapSize - 1)/(width - 1)));
		auto limit = static_cast<unsigned int>(heightmap->At(flooredIndex)*height);

		for (int row = 0; row <= limit; row++)
			image.SetPixelInt(column, height - 1 - row, color);

		for (int row = limit + 1; row < height; row++) {
			float transparency = 1.f/std::pow(row - limit, 1.f);
			const Color& pixelColor = Color(0.1f, 0.4f, 0, transparency);

			image.SetPixel(column, height - 1 - row, pixelColor);
		}
	}

	GetComponent<StaticSprite2D>()->GetSprite()->GetTexture()->SetData(&image);
}

void TerrainSpriteController::Stop() {
	if (!terrainController_.Expired())
		terrainController_->HeightmapUpdated.Disconnect(this, &TerrainSpriteController::OnHeightmapUpdated);
}
