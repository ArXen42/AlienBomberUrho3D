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

	/// Выгружает загруженный уровень
	void UnloadGameLevel();

	/// В результате вызова игровой уровень будет перезагружен в начале следующего кадра.
	void RequestReloadGameLevel();

	/// Служебный метод, вызываемый из GameApplication (производит фактическую перезагрузку уровня).
	void HandleBeginFrame();

	WeakPtr<Scene> scene_;

private:
	void ReloadGameLevel();

	bool reloadRequested_ = false;
};