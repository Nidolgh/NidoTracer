#include "BoundingBox.h"

bool BoundingBox::hit(const Ray3D& ray)
{
	const Vector3* bounds = (*this).m_bounds;

	Vector3 r_ori = ray.get_origin();
	Vector3 r_dir = ray.get_direction();
	Vector3 r_inv = ray.get_inv_direction();

	float t_min = (bounds[ray.m_inv_sign[0]].x - r_ori.x) * r_inv.x;
	float t_max = (bounds[1 - ray.m_inv_sign[0]].x - r_ori.x) * r_inv.x;
	float t_y_min = (bounds[ray.m_inv_sign[1]].y - r_ori.y) * r_inv.y;
	float t_y_max = (bounds[1 - ray.m_inv_sign[1]].y - r_ori.y) * r_inv.y;

	if (t_min > t_y_max || t_y_min > t_max)
		return false;
	if (t_y_min > t_min)
		t_min = t_y_min;
	if (t_y_max < t_max)
		t_max = t_y_max;

	float t_z_min = (bounds[ray.m_inv_sign[2]].z - r_ori.z) * r_inv.z;
	float t_z_max = (bounds[1 - ray.m_inv_sign[2]].z - r_ori.z) * r_inv.z;

	if ((t_min > t_z_max) || (t_z_min > t_max))
		return false;
	if (t_z_min > t_min)
		t_min = t_z_min;
	if (t_z_max < t_max)
		t_max = t_z_max;

	if (t_min < 0 || t_max < 0)
		return false;

	return true;
}
