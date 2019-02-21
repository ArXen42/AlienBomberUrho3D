// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "AircraftMouseController.hpp"
#include "AircraftMovingController.hpp"
#include <Urho3D/Input/InputEvents.h>
#include <Urho3D/Input/Input.h>
#include <Urho3D/Graphics/Camera.h>
#include <Urho3D/Scene/Scene.h>
#include <Urho3D/IO/Log.h>

void AircraftMouseController::Start()
{
	SubscribeToEvent(E_MOUSEBUTTONDOWN, URHO3D_HANDLER(AircraftMouseController, HandleMouseButtonDown));
}

void AircraftMouseController::HandleMouseButtonDown(StringHash eventType, VariantMap& eventData)
{
	auto mousePosition           = GetSubsystem<Input>()->GetMousePosition();
	auto normalizedMousePosition = Vector3((float) mousePosition.x_ / 1280, (float) mousePosition.y_ / 720, 4);
	auto camera                  = GetScene()->GetChild("MainCamera")->GetComponent<Camera>();

	Vector3 clickPosition = camera->ScreenToWorldPoint(normalizedMousePosition);
	GetComponent<AircraftMovingController>()->SetTargetPosition({clickPosition.x_, clickPosition.y_});
}
