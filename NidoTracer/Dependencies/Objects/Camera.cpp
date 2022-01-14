#include "Camera.h"

Camera::Camera()
{

}

Camera::Camera(const Vector3 new_view_pos, const Vector3 new_forward_dir, const float new_focal_length, const float new_aspect_ratio, const float new_fov_degree)
	: m_view_origin(new_view_pos), m_view_dir(new_forward_dir.Unit()), m_focal_length(new_focal_length), m_aspect_ratio(new_aspect_ratio), m_fov_degree(new_fov_degree)
{
	d_fov = new_fov_degree;
}

Camera& Camera::operator=(const Camera& t)
{
	m_view_origin = t.get_origin();
	m_view_dir = t.m_view_dir;
	m_focal_length = t.m_focal_length;
	m_aspect_ratio = t.m_aspect_ratio;
	m_fov_degree = t.m_fov_degree;
	d_fov = m_fov_degree;
	
	return *this;
}

Ray3D Camera::get_ray_at_imageplane(const int pixel_x, const int pixel_y, const int image_width, const int image_height) const
{
	Ray3D created_ray(Vector3(0), Vector3(0));
	Vector3 imageplane_pos(0, 0, 0);

	float dimension_modifier = 1.0f;
	if (m_view_state == ViewState::Orthographic)
		dimension_modifier = m_fov_degree * 0.1f;
	
	float image_plane_u = m_min_width + (m_max_width - m_min_width) * ((static_cast<float>(pixel_x) + 0.5f) / (static_cast<float>(image_width)) * dimension_modifier);
	float image_plane_v = m_min_height + (m_max_height - m_min_height) * ((static_cast<float>(pixel_y) + 0.5f) / (static_cast<float>(image_height)) * dimension_modifier);

	if (m_view_state == ViewState::Perspective)
	{
		const float fov_rad_cal = tanf((m_fov_degree / 2) * static_cast<float>((M_PI / 180)));
		image_plane_u *= fov_rad_cal;
		image_plane_v *= fov_rad_cal;
	}
	
	image_plane_u *= m_aspect_ratio;
	
	const Vector3 w = m_view_dir;
	const Vector3 u = m_top_dir.Cross(w).Unit();
	const Vector3 v = w.Cross(u);
	imageplane_pos = (image_plane_u * u) +
					 (image_plane_v * v);

	if (m_view_state == ViewState::Orthographic)
	{
		imageplane_pos.x -= 9.0f;
		imageplane_pos.y -= 5;
		created_ray.set_origin(get_origin() + imageplane_pos);
		created_ray.set_direction(w);
	}
	else
	{
		imageplane_pos += (m_focal_length * w);
		created_ray.set_origin(get_origin());
		created_ray.set_direction(imageplane_pos);
	}
	
	return created_ray;
}
