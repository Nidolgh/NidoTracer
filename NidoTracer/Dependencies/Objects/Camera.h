#pragma once
#include "../Math/Vector3.h"
#include "../Math/MathDefines.h"
#include "../Objects/Ray3D.h"

enum ViewState
{
	Orthographic,
	Perspective
};

class Camera
{
private:
	Vector3 m_view_origin = Vector3(0, 0, 0);
	Vector3 m_view_dir = Vector3(0, 0, 1);
	Vector3 m_top_dir = Vector3(0, 1, 0);
	
	float m_focal_length = 1.0f;
	float m_aspect_ratio = 1.0f;
	float m_fov_degree = 90.0f;
	
	// image plane
	const float m_max_width = 1;
	const float m_max_height = 1;
	const float m_min_width = -m_max_width;
	const float m_min_height = -m_max_height;

	// properties
	ViewState m_view_state = ViewState::Perspective;

	// defaults
	float d_fov = 0;
	
public:
	Camera();
	Camera(const Vector3 new_view_pos, const Vector3 new_forward_dir, const float new_focal_length, const float new_aspect_ratio, const float new_fov_degree);

	Camera& operator=(const Camera& t);

	Ray3D get_ray_at_imageplane(const int pixel_x, const int pixel_y, const int image_width, const int image_height) const;
	
	Vector3 get_origin() const { return m_view_origin; }
	void add_to_origin(const Vector3 add) { m_view_origin += add; }
	void set_origin(const Vector3 new_origin) { m_view_origin = new_origin; }
	Vector3 get_view_dir() const { return m_view_dir; }
	void set_view_direction(Vector3 new_dir) { m_view_dir = new_dir.Unit(); }
	ViewState get_view_state() const { return m_view_state; }
	void set_view_state(ViewState new_state) { m_view_state = new_state; }
	
	void set_aspect_ratio(const float new_aspect_ratio) { m_aspect_ratio = new_aspect_ratio; }
	void add_fov(const float to_add) { m_fov_degree += to_add; } // no safety check

	void reset_to_default() { m_fov_degree = d_fov; }
};