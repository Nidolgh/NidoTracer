#include "Box.h"

Box::Box(const BoundingBox new_box, Material new_mat) :
	m_bounding_box(new_box)
{
	m_origin = new_box.get_max() * 0.5f;
	set_material(new_mat);

	m_surface_type = SurfaceType::SurfaceBox;
}

Box::Box(const Vector3 min_pos, const float size, Material new_mat) :
	m_bounding_box(BoundingBox(min_pos, min_pos + Vector3(size)))
{
	m_origin = (min_pos + Vector3(size)) * 0.5f;
	set_material(new_mat);
}

Box::Box(const Vector3 new_min, const Vector3 new_max, Material new_mat) :
	m_bounding_box(BoundingBox(new_min, new_max))
{
	m_origin = new_max * 0.5f;
	set_material(new_mat);
}

bool Box::hit(const Ray3D& ray, HitRecord& r_rec)
{
	const BoundingBox& the_bb = bounding_box();
	const Vector3* bounds = the_bb.get_bounds();
	
	Vector3 r_ori = ray.get_origin();
	Vector3 r_dir = ray.get_direction();
	Vector3 r_inv = ray.get_inv_direction();
	
	float t_min, t_max, t_y_min, t_y_max, t_z_min, t_z_max;

	t_min = (bounds[ray.m_inv_sign[0]].x - r_ori.x) * r_inv.x;
	t_max = (bounds[1 - ray.m_inv_sign[0]].x - r_ori.x) * r_inv.x;
	t_y_min = (bounds[ray.m_inv_sign[1]].y - r_ori.y) * r_inv.y;
	t_y_max = (bounds[1 - ray.m_inv_sign[1]].y - r_ori.y) * r_inv.y;

	if (t_min > t_y_max || t_y_min > t_max)
		return false;
	if (t_y_min > t_min)
		t_min = t_y_min;
	if (t_y_max < t_max)
		t_max = t_y_max;
	
	t_z_min = (bounds[ray.m_inv_sign[2]].z - r_ori.z) * r_inv.z;
	t_z_max = (bounds[1 - ray.m_inv_sign[2]].z - r_ori.z) * r_inv.z;
	
	if ((t_min > t_z_max) || (t_z_min > t_max))
		return false;
	if (t_z_min > t_min)
		t_min = t_z_min;
	if (t_z_max < t_max)
		t_max = t_z_max;

	if (t_min < 0 || t_max < 0)
		return false;
	
	r_rec.m_intersection_point = ray.get_point_on_time(t_min);
	r_rec.m_time = t_min;

	// TODO: fix normal calculations
	Vector3 c = (the_bb.get_min() + the_bb.get_max()) * 0.5f;
	Vector3 d = (the_bb.get_min() - the_bb.get_max()) * 0.5f;
	Vector3 p = r_rec.m_intersection_point - c;

	Vector3 temp_norm(0);
	temp_norm.x = static_cast<float>(static_cast<int>(c.x / std::abs(d.x) * bias));
	temp_norm.y = static_cast<float>(static_cast<int>(c.y / std::abs(d.y) * bias));
	temp_norm.z = static_cast<float>(static_cast<int>(c.z / std::abs(d.z) * bias));

	r_rec.m_hit_normal = temp_norm.Unit() * -1;
	/*Vector3 c = (the_bb.get_min() + the_bb.get_max()) * 0.5f;
	Vector3 d = (the_bb.get_min() - the_bb.get_max()) * 0.5f;
	Vector3 p = r_rec.m_intersection_point - d;

	Vector3 temp_norm(0);
	temp_norm.x = static_cast<float>(static_cast<int>(c.x / abs(d.x) * bias));
	temp_norm.y = static_cast<float>(static_cast<int>(c.y / abs(d.y) * bias));
	temp_norm.z = static_cast<float>(static_cast<int>(c.z / abs(d.z) * bias));

	r_rec.m_hit_normal = temp_norm;*/
	
	r_rec.m_material = &get_material();

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