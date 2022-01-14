#pragma once
#include "../Math/Vector3.h"
#include <cassert>

class Ray3D
{
public:
	Ray3D(const Vector3 new_origin, const Vector3 new_dir, const float max_length = 400);
	//Ray3D(const Vector3 newOrigin, Vector3 newDirection) : m_origin(newOrigin), m_direction(newDirection) {}
	
private:
	Vector3 m_origin = Vector3(0, 0, 0);
	Vector3 m_direction = Vector3(0, 0, 0);
	
	Vector3 m_inv_dir = Vector3(0,0,0);
	
	float m_max_length = 100.0f;
public:
	Vector3 get_point_on_time(float time) const { return m_origin + m_direction * time; }
	
	void set_origin(const Vector3 new_origin) { m_origin = new_origin; }
	Vector3 get_origin() const { return m_origin; };

	void set_direction(const Vector3 new_dir);
	Vector3 get_direction() const { return m_direction; }
	Vector3 get_inv_direction() const { return m_inv_dir; }

	float get_max_length() const { return m_max_length; }
	void set_max_length(const float new_max) { m_max_length = new_max; }
	
	bool m_inv_sign[3];
};
