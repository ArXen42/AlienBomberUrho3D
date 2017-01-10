#pragma once

#include <Urho3D/Core/Object.h>
#include <Urho3D/Scene/Scene.h>

using namespace Urho3D;

class GameSubsystem : public Object {
URHO3D_OBJECT(GameSubsystem, Object)

public:
	GameSubsystem(Context* context) : Object(context) {};

	/// Загружает пока игровой уровень из json и инициализирует компоненты.
	void LoadGameLevel();

	/// Перезагружает игровой уровень.
	void ReloadGameLevel() {
		UnloadGameLevel();
		LoadGameLevel();
	}

	WeakPtr<Scene> scene_;
private:

	/// Выгружает загруженный уровень
	void UnloadGameLevel();
};