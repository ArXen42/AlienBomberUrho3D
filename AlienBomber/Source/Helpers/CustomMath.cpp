// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "CustomMath.hpp"

using namespace Urho3D;

float CustomMath::GetDirectionAngle(const Vector2& direction)
{
	const float dirX = direction.x_;
	const float dirY = direction.y_;

	float angle = Acos(dirX / std::sqrt(dirX * dirX + dirY * dirY));
	return dirY > 0 ? angle : -angle;
}
