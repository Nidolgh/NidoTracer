#pragma once
#include "../../Math/Vector3.h"

class PointLight
{
private:
	Vector3 m_origin = Vector3(0, 0, 0);
	float m_intensity = 1.0f;
	
public:
	PointLight() = default;
	PointLight(const Vector3 new_origin, const float new_intensity);
	virtual ~PointLight();

	Vector3 GetOrigin() const { return m_origin; }
	float GetIntensity() const { return m_intensity; }

	void AddToOrigin(Vector3 add) { m_origin += add; }
};