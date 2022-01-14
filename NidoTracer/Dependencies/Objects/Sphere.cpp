#include "Sphere.h"

Sphere::Sphere(const Vector3 newOrigin, const float newRadius, Material new_mat) :
	m_radius(newRadius)
{
	m_origin = newOrigin;
	set_material(new_mat);
	
	m_surface_type = SurfaceType::SurfaceSphere;
}

Sphere::~Sphere()
{
	
}

bool Sphere::hit(const Ray3D& ray_to_check, HitRecord& r_rec)
{
	if (!bounding_box().hit(ray_to_check))
		return false;

	const Vector3 rayDirection = ray_to_check.get_direction();
	const Vector3 rayOrigin = ray_to_check.get_point_on_time(0.0f);

	// Quadtratic equation
	const float a = (rayDirection.Dot(rayDirection));
	const float b = rayDirection.Dot(rayOrigin - m_origin) * rayDirection.Dot(rayOrigin - m_origin);
	const float c = (rayOrigin - m_origin).Dot(rayOrigin - m_origin) - (m_radius * m_radius);

	const float discriminant = b - a * c;

	if (discriminant > 0)
	{
		float t1 = (rayDirection * -1.0f).Dot(rayOrigin - GetOrigin()) - sqrt(discriminant) / a; // square magnitude is always 1 of a unit vector
		float t2 = (rayDirection * -1.0f).Dot(rayOrigin - GetOrigin()) + sqrt(discriminant) / a; // square magnitude is always 1 of a unit vector

		if (t1 < 0 || t2 < 0)
			return false;

		if (t1 > t2)
		{
			const float temp = t2;
			t1 = t2;
			t2 = temp;
		}
		
		const Vector3 inter_point = ray_to_check.get_point_on_time(t1);
		
		r_rec.m_time = t1;
		r_rec.m_intersection_point = inter_point;
		r_rec.m_hit_normal = (inter_point - GetOrigin()).Unit();
		//r_rec.m_hit_normal = r_rec.m_hit_normal + 0.0001 * r_rec.m_hit_normal;
		r_rec.m_material = &m_material;
		
		return true;
	}
	
	return false;
}

BoundingBox Sphere::bounding_box()
{
	Vector3 min = m_origin - Vector3(m_radius);
	Vector3 max = m_origin + Vector3(m_radius);
	return BoundingBox(min, max);
}