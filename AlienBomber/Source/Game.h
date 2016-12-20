#include <Urho3D/Core/CoreEvents.h>
#include <Urho3D/Engine/Application.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/IO/Log.h>
#include <Urho3D/Scene/Scene.h>
#include <Urho3D/Graphics/Camera.h>
#include <Urho3D/Graphics/Renderer.h>

using namespace Urho3D;

class Game : public Application {
public:
	SharedPtr<Scene> scene_;

	Game(Context* context) : Application(context) {}

	virtual void Setup();

	virtual void Start();

	virtual void Stop();

	void HandlePostRenderUpdate(StringHash eventType, VariantMap& eventData);

private:
	/// Загружает пока единственный уровень игры из json и инициализирует компоненты.
	void LoadGameLevel();
};

URHO3D_DEFINE_APPLICATION_MAIN(Game)