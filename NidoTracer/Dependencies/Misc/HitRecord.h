#pragma once
#include "../Math/Vector3.h"
#include "../Misc/Color.h"
#include "../Misc/Material.h"

class HitRecord
{
public:
	float m_time = 0.0f;
	Vector3 m_intersection_point = Vector3(0, 0, 0);
	Vector3 m_hit_normal = Vector3(0, 0, 0);

	Material* m_material = nullptr;
};