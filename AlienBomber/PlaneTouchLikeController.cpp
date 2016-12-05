#include "PlaneTouchLikeController.h"
#include "PlaneController.h"
#include <Urho3D/Input/InputEvents.h>
#include <Urho3D/Input/Input.h>
#include <Urho3D/Graphics/Camera.h>
#include <Urho3D/Scene/Scene.h>
#include <Urho3D/IO/Log.h>

void PlaneTouchLikeController::Start() {
	SubscribeToEvent(E_MOUSEBUTTONDOWN, URHO3D_HANDLER(PlaneTouchLikeController, HandleMouseButtonDown));
}

void PlaneTouchLikeController::HandleMouseButtonDown(StringHash eventType, VariantMap& eventData) {
	auto mousePosition = GetSubsystem<Input>()->GetMousePosition();
	auto normalizedMousePosition = Vector3((float)mousePosition.x_/1280, (float)mousePosition.y_/720, 4);
	auto camera = GetScene()->GetChild("MainCamera")->GetComponent<Camera>();

	Vector3 clickPosition = camera->ScreenToWorldPoint(normalizedMousePosition);
	Vector3 direction = clickPosition - GetNode()->GetPosition();

	float dirx = direction.x_;
	float diry = direction.y_;
	float angle = Acos(dirx/sqrt(dirx*dirx + diry*diry));
	GetComponent<PlaneController>()->SetTargetRotation(diry > 0 ? angle : -angle);
}
