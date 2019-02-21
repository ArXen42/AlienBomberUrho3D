#pragma once

#include <Urho3D/Core/Object.h>
#include <Urho3D/Scene/Scene.h>
#include <Urho3D/Core/CoreEvents.h>

using namespace Urho3D;

class GameSubsystem : public Object
{
URHO3D_OBJECT(GameSubsystem, Object)

public:
	GameSubsystem(Context* context) : Object(context)
	{
		SubscribeToEvent(E_BEGINFRAME, URHO3D_HANDLER(GameSubsystem, HandleBeginFrame));
	};

	/// Загружает пока игровой уровень из json и инициализирует компоненты.
	void LoadGameLevel();

	/// Выгружает загруженный уровень
	void UnloadGameLevel();

	/// В результате вызова игровой уровень будет перезагружен в начале следующего кадра.
	void RequestReloadGameLevel();

	WeakPtr<Scene> scene_;

private:
	void HandleBeginFrame(StringHash eventType, VariantMap& eventData);

	void ReloadGameLevel();

	bool reloadRequested_ = false;
};