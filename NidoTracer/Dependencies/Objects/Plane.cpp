#include "Plane.h"

Plane::Plane(const Vector3 newOrigin, const Vector3 newNormal, Material new_mat) :
	m_normal(newNormal)

{
	m_origin = newOrigin;
	set_material(new_mat);

	m_surface_type = SurfaceType::SurfacePlane;
}

bool Plane::hit(const Ray3D& ray_to_check, HitRecord& r_rec)
{
	const float dot_on_ray = ray_to_check.get_direction().Dot(m_normal);
	
	if (dot_on_ray == 0.0f)
		return false;
	
	const Vector3 plane_ray_difference = m_origin - ray_to_check.get_origin();

	float t = plane_ray_difference.Dot(m_normal) / dot_on_ray;

	if(t < 0.0f)
		return false;

	r_rec.m_time = t;
	r_rec.m_intersection_point = ray_to_check.get_point_on_time(t);
	r_rec.m_hit_normal = m_normal;
	r_rec.m_material = &m_material;

	if (m_material.m_checkerboard)
	{
		Color check(m_material.m_checker_col_odd);

		int u = static_cast<int>(r_rec.m_intersection_point.x * m_material.m_checker_x_multiplier);
		int v = static_cast<int>(r_rec.m_intersection_point.z * m_material.m_checker_y_multiplier);

		if (r_rec.m_intersection_point.x < 0) u--;
		if (r_rec.m_intersection_point.z < 0) v--;

		const int uv = u + v;

		if (uv % 2 == 0)
		{
			check = m_material.m_checker_col_even;
		}

		r_rec.m_material->m_dif_col = check;
	}
	
	return true;
}

BoundingBox Plane::bounding_box()
{
	return BoundingBox(
		Vector3(-INFINITY, m_origin.y, -INFINITY), 
		Vector3(INFINITY, m_origin.y, INFINITY));
}