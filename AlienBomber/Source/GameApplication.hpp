#include <Urho3D/Core/CoreEvents.h>
#include <Urho3D/Engine/Application.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/IO/Log.h>
#include <Urho3D/Scene/Scene.h>
#include <Urho3D/Graphics/Camera.h>
#include <Urho3D/Graphics/Renderer.h>
#include "GameSubsystem.hpp"

using namespace Urho3D;

class GameApplication : public Application {
public:
	GameApplication(Context* context) : Application(context) {}

	virtual void Setup();

	virtual void Start();

	void HandlePostRenderUpdate(StringHash eventType, VariantMap& eventData);

private:
	/// Регистрация компонентов
	void RegisterObjects();

	GameSubsystem* gameSubsystem_ = nullptr;
};

URHO3D_DEFINE_APPLICATION_MAIN(GameApplication)