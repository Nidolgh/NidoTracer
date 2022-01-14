#include "Renderer.h"
#include "Math/Max.h"

sf::Image Renderer::create_image(SceneManager& scene_manager)
{
	Scene& active_scene = scene_manager.get_active_scene();
	const Camera& active_camera = active_scene.get_active_camera();

	sf::Image render_image_buffer;
	render_image_buffer.create(pixels_width_amount, pixels_height_amount, sf::Color::Red);
	
	for (int pixelY = 0; pixelY < pixels_height_amount; pixelY++)
	{
		for (int pixelX = 0; pixelX < pixels_width_amount; pixelX++)
		{
			m_cur_recursion_depth = 0;
			
			Ray3D view_ray = active_camera.get_ray_at_imageplane(pixelX, pixelY, pixels_width_amount, pixels_height_amount);
			
			Color final_pixel_col = trace_ray_color(view_ray, active_scene);

			render_image_buffer.setPixel(pixelX, pixelY,
				sf::Color(final_pixel_col.get_red_0_255(),
					final_pixel_col.get_green_0_255(),
					final_pixel_col.get_blue_0_255(),
					255));
		}
	}

	// animation behaviour
	if (active_scene.is_animated())
	{
		total_time += 0.05f;
		
		if (time < -time_bounds)
		{
			time = -time_bounds;
			time_add = -time_add;
		}
		else if (time > time_bounds)
		{
			time = time_bounds;
			time_add = -time_add;
		}

		time += time_add;
		
		active_scene.the_camera.add_to_origin(Vector3(sinf(-total_time), sinf(total_time) * 0.1f, cosf(total_time) * 2) * 1.1f);
		
		const Vector3 dir_to_head_scene_object = 
			(active_scene.scene_objects.get_tail_node()->get_data()->get_origin() - 
			active_scene.the_camera.get_origin()).Unit();
		
		active_scene.the_camera.set_view_direction(dir_to_head_scene_object);

		active_scene.light_objects.get_head_node()->get_data()->AddToOrigin(Vector3( sinf(total_time) * 1.5f, 0, cosf(-total_time) * 2));
	}

	return render_image_buffer;
}

Color Renderer::trace_ray_color(const Ray3D& ray, Scene& active_scene)
{
	HitRecord the_hit_record, temp_hit_record;
	
	if (active_scene.determine_closest_hit_surface(ray, the_hit_record, m_ignore_bvh))
	{
		Color pix_col(0.0f);
		
		pix_col += active_scene.get_ambient_color() * active_scene.get_ambient_intensity(); // ambient lighting

		if (active_scene.get_visualize_bvh_state())
			pix_col += active_scene.m_the_bvh.visualize(ray);
		
		QueueNode<PointLight*>* cur_node = active_scene.light_objects.get_head_node();
		while (cur_node != nullptr)
		{
			const PointLight& the_point_light = *cur_node->get_data();
			cur_node = cur_node->next();

			Ray3D shadow_ray(the_hit_record.m_intersection_point, 
				(the_point_light.GetOrigin() - the_hit_record.m_intersection_point).Unit());
			shadow_ray.set_origin(shadow_ray.get_point_on_time(0.1f)); // TODO get machines epsilon /\ https://www.geeksforgeeks.org/cpp-program-to-find-machine-epsilon/
			shadow_ray.set_max_length((the_point_light.GetOrigin() - the_hit_record.m_intersection_point).Unit().Magnitude());
			
			if (!active_scene.get_shadow() || !active_scene.determine_closest_hit_surface(shadow_ray, temp_hit_record, m_ignore_bvh))
			{
				if (the_hit_record.m_material->m_flat_coloring)
					return pix_col = the_hit_record.m_material->m_dif_col;
				
				if (the_hit_record.m_material->m_diffuse > 0)
				{
					pix_col += lambert_shading(the_hit_record, the_point_light);
				}

				if (the_hit_record.m_material->m_specular > 0)
				{
					pix_col += blinn_phong_shading(active_scene.get_active_camera(), the_hit_record, the_point_light);
				}

				if (the_hit_record.m_material->m_specular_reflection)
				{
					if (m_cur_recursion_depth++ < active_scene.get_reflection_depth())
					{
						Vector3 d = (the_hit_record.m_intersection_point - ray.get_origin()).Unit();
						Vector3 r = (d - the_hit_record.m_material->m_reflection_modifier * d.Dot(the_hit_record.m_hit_normal) * the_hit_record.m_hit_normal).Unit();

						Ray3D reflection_ray(the_hit_record.m_intersection_point, r);
						reflection_ray.set_origin(reflection_ray.get_point_on_time(0.05f));

						pix_col += /*the_hit_record.m_material->m_spec_col * */
							trace_ray_color(reflection_ray, active_scene);
					}
				}
			}
		}

		return pix_col;
	}
	
	return active_scene.m_background_color;
}

Color Renderer::lambert_shading(const HitRecord& the_hit_record, const PointLight& light_point)
{
	const Vector3 hit_to_light_dir = (light_point.GetOrigin() - the_hit_record.m_intersection_point).Unit();
	const Vector3 hit_normal = the_hit_record.m_hit_normal;

	const Color surface_color = the_hit_record.m_material->m_dif_col;
	const Color ambient_color = Color(0.1f, 0.1f, 0.2f) * 0.05f;

	Color col_to_return = Color(0, 0, 0);

	col_to_return.r = surface_color.r * light_point.GetIntensity() * Max(0, hit_normal.Dot(hit_to_light_dir));

	col_to_return.g = surface_color.g * light_point.GetIntensity() * Max(0, hit_normal.Dot(hit_to_light_dir));

	col_to_return.b = surface_color.b * light_point.GetIntensity() * Max(0, hit_normal.Dot(hit_to_light_dir));

	return ambient_color + col_to_return;
}

Color Renderer::blinn_phong_shading(const Camera& the_camera, const HitRecord& the_hit_record, const PointLight& light_point)
{
	// blong
	// l, points towards the light
	// v, points towards the camera/eye
	// n, perpendicular to the surface at the point where reflection is taking place

	const Vector3 lightDif = (light_point.GetOrigin() - the_hit_record.m_intersection_point).Unit();
	const Vector3 viewCamDif = (the_camera.get_origin() - the_hit_record.m_intersection_point).Unit();
	const Vector3 n = the_hit_record.m_hit_normal;

	const Vector3 halfVec = (viewCamDif + lightDif).Unit();

	const Color surface_color = the_hit_record.m_material->m_dif_col;
	const Color specular_color = Color(1, 1, 1);
	const float specular_intensity = 0.6f;

	Color col_to_return = Color(0, 0, 0);

	const int POWER = static_cast<int>(100.0f * the_hit_record.m_material->m_specular);

	col_to_return = (surface_color * light_point.GetIntensity() * Max(0, n.Dot(lightDif))) +
		(specular_color * specular_intensity * pow(Max(0, n.Dot(halfVec)), POWER));

	return Color(0.1f, 0.0f, 0.2f) * 0.2f + col_to_return;
}