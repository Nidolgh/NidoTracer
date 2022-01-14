#pragma once
#include "Surface.h"

class Sphere :
	public Surface
{
public:
	Sphere(const Vector3 newOriginPos, const float radius, Material new_mat = Material());
	virtual ~Sphere();
	
	virtual bool hit(const Ray3D& ray_to_check, HitRecord& r_rec);
	virtual BoundingBox bounding_box();

	Vector3 GetOrigin() const { return m_origin; };
	float GetRadius() const { return m_radius; }

	void SetPosition(const Vector3 new_pos) { m_origin = new_pos; }
	void AddPosition(const Vector3 add_pos) { m_origin += add_pos; }
	
private:
	float m_radius = 0.0f;
};