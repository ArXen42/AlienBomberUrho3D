// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <Urho3D/Graphics/Texture2D.h>
#include <Urho3D/Graphics/Camera.h>
#include <Urho3D/Urho2D/StaticSprite2D.h>
#include <Urho3D/Urho2D/Sprite2D.h>
#include <Urho3D/Scene/Scene.h>
#include "SkySpriteController.hpp"

void SkySpriteController::Start() {
	auto staticSprite2D = GetComponent<StaticSprite2D>();

	int spriteWidth = staticSprite2D->GetSprite()->GetTexture()->GetWidth();
	int spriteHeight = staticSprite2D->GetSprite()->GetTexture()->GetHeight();

	auto camera = GetScene()->GetChild("MainCamera")->GetComponent<Camera>();
	float verticalScreenSize = camera->GetOrthoSize();
	float horizontalScreenSize = camera->GetAspectRatio()*verticalScreenSize;

	Vector2 scale = Vector2(horizontalScreenSize*100/spriteWidth,
	                        verticalScreenSize*100/spriteHeight);

	GetNode()->SetScale2D(scale);
	GetNode()->SetPosition2D(camera->GetNode()->GetPosition2D());
}
