#pragma once
#include "Misc/ScreenResolutionConsts.h"

#include "Misc/HitRecord.h"
#include "Objects/Ray3D.h"

#include <SFML/Graphics/Image.hpp>
#include "SceneManager.h"

class Renderer
{
private:
	const int m_max_recursion_depth = 1;
	int m_cur_recursion_depth = 0;

	float time_add = -0.2f;
	float time = 2;
	float time_bounds = 4;

	float total_time = 0;
	
public:
	sf::Image create_image(SceneManager& scene_manager);
	Color trace_ray_color(const Ray3D& ray, Scene& active_scene);
	
	Color lambert_shading(const HitRecord& the_hit_record, const PointLight& light_point);
	Color blinn_phong_shading(const Camera& the_camera, const HitRecord& the_hit_record, const PointLight& light_point);

	int get_pixel_width() const { return pixels_width_amount; }
	int get_pixel_height() const { return pixels_height_amount; }

	bool m_ignore_bvh = false;
};