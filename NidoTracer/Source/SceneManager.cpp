#include "SceneManager.h"

SceneManager::SceneManager()
{
	const float aspect_ratio = static_cast<float>(pixels_width_amount) / static_cast<float>(pixels_height_amount);

	m_active_scene = &m_scenes[4];

	Material mat_diff(1, 0, false, Color(1), Color(0));
	Material mat_spec(0, 1, false, Color(0), Color(1));
	Material mat_reflect(0, 0, true, Color(1), Color(1));
	Material mat_spec_reflect(0, 1, true, Color(1), Color(1));
	Material mat_diff_reflect(1, 0, true, Color(1), Color(1));
	Material mat_spec_diff_reflect(1.0f, 1.5f, true, Color(1), Color(1));
	Material mat_plane_checkerboard(1, 0, false, Color(1), Color(1), true, 1.0f, 1.0f, Color(1.0f), Color(0.0f));
	Material mat_box_checkerboard(1, 0, false, Color(1), Color(1), true, 3.0f, 3.0f, Color(1.0f), Color(0.0f));

	// -- scene 0 / Blender compare scene
	{
		m_scenes[0].set_animation_state(false);
		
		m_scenes[0].the_camera = Camera(Vector3(0, 2.5f, -6), Vector3(0, 0, 1), 1.0f, aspect_ratio, 30);
		// 255, 255, 255
		mat_diff.m_dif_col = Color(1.0f);
		m_scenes[0].scene_objects.push(new Plane(Vector3(0.0f, -1.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f), mat_diff));

		mat_diff.m_dif_col = Color(0, 1, 0); // 254, 165, 147
		mat_spec_diff_reflect.m_dif_col = Color(0.9f, 0.6f, 0.5f);
		m_scenes[0].scene_objects.push(new Sphere(Vector3(0.0f, 1.0f, 16), 5.0f, mat_spec_diff_reflect));
		mat_diff.m_dif_col = Color(1, 0, 0);
		m_scenes[0].scene_objects.push(new Sphere(Vector3(8.0f, 1.0f, 10.0f), 3.0f, mat_diff));
		mat_diff.m_dif_col = Color(1, 1, 0);
		m_scenes[0].scene_objects.push(new Sphere(Vector3(-4.0f, 2.0f, 8.0f), 2.0, mat_diff));
		mat_diff.m_dif_col = Color(0, 1, 1);
		m_scenes[0].scene_objects.push(new Sphere(Vector3(5.0f, 2.0f, 20.0f), 4.0, mat_diff));

		mat_diff.m_dif_col = Color(0.1f, 0, 1);
		m_scenes[0].scene_objects.push(new Box(Vector3(-4, -1, 1.0f), 2, mat_diff));
		mat_diff.m_dif_col = Color(1, 1, 0);
		mat_diff.m_flat_coloring = true;
		m_scenes[0].scene_objects.push(new Box(Vector3(4, -1, -2.0f), 2, mat_diff));


		m_scenes[0].light_objects.push(new PointLight(Vector3(2, 20, -5), 1.0f));

		m_scenes[0].test_light = PointLight(Vector3(0.0f, 10.0f, 0.0f), 1.0f);

		mat_diff.m_flat_coloring = false;
	}
		
	mat_spec_reflect.m_spec_col = Color(1);
	mat_diff.m_dif_col = Color(1);
	mat_spec.m_spec_col = Color(1);
	
	// -- scene 1 - week 3
	{
		m_scenes[1].set_animation_state(false);
		m_scenes[1].set_shadow_state(true);
		m_scenes[1].set_ambient_intensity(0);
		
		m_scenes[1].m_background_color = Color(0.0f);
		m_scenes[1].the_camera = Camera(Vector3(0, 0, 0), Vector3(0, 0, 1), 1.0f, aspect_ratio, 60);

		m_scenes[1].scene_objects.push(new Plane(Vector3(0.0f, -1.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f), mat_plane_checkerboard));
		mat_diff.m_dif_col = Color(1, 0, 0);
		m_scenes[1].scene_objects.push(new Sphere(Vector3(0.0f, 0.10f, 5.0f), 1.0f, mat_diff));
		
		m_scenes[1].light_objects.push(new PointLight(Vector3(1.4f, 2, 3.2f), 1.0f));
	}

	// -- scene 2 - week 4
	{
		m_scenes[2].set_animation_state(false);
		m_scenes[2].set_shadow_state(true);
		m_scenes[2].set_ambient_intensity(0);

		m_scenes[2].m_background_color = Color(0.0f);
		m_scenes[2].the_camera = Camera(Vector3(0, 0, 0), Vector3(0, 0, 1), 1.0f, aspect_ratio, 60);

		m_scenes[2].scene_objects.push(new Plane(Vector3(0.0f, -1.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f), mat_plane_checkerboard));
		mat_spec_reflect.m_dif_col = Color(0.2f);
		mat_spec_reflect.m_specular = 1.5f;
		mat_spec_reflect.m_reflection_modifier = 2.0f;
		m_scenes[2].scene_objects.push(new Sphere(Vector3(0.0f, 0.10f, 5.0f), 1.0, mat_spec_reflect));

		m_scenes[2].light_objects.push(new PointLight(Vector3(1.4f, 2, 3.2f), 1.0f));
	}

	// -- scene 3 - week 5
	{
		m_scenes[3].set_shadow_state(true);
		m_scenes[3].set_ambient_intensity(0);
		m_scenes[3].set_reflection_depth(2);
		
		m_scenes[3].m_background_color = Color(0.05f, 0.5f, 0.6f);

		m_scenes[3].the_camera = Camera(Vector3(0, 0, 0), Vector3(0, 0, 1), 1.0f, aspect_ratio, 60);

		mat_spec_reflect.m_dif_col = Color(0.1f);//12, 165, 211
		mat_spec_reflect.m_spec_col = Color(0.1f);
		mat_diff.m_dif_col = Color(0.1f, 0.1f, 0.4f);
		mat_box_checkerboard.m_checker_col_odd = Color(1.0f, 0.9f, 0.0f);
		mat_box_checkerboard.m_checker_col_even = Color(1.0f,0.1f,0.0f);
		m_scenes[3].scene_objects.push(new Box(Vector3(-1.0f, -0.95f, -4.0f), Vector3(5.0f, -1.0f, 18.0f), mat_box_checkerboard));
		mat_spec_reflect.m_spec_col = Color(0.1f, 0.1f, 0.1f);
		mat_spec_reflect.m_specular = 1.4f;
		mat_spec_reflect.m_reflection_modifier = -0.15f;
		m_scenes[3].scene_objects.push(new Sphere(Vector3(0.0f, 0.0f, 3.0f), 0.6f, mat_spec_reflect));
		mat_spec_reflect.m_reflection_modifier = 2.0f;
		mat_spec_diff_reflect.m_specular = 1;
		m_scenes[3].scene_objects.push(new Sphere(Vector3(1.1f, -0.2f, 5.0f), 0.5f, mat_spec_diff_reflect));

		m_scenes[3].light_objects.push(new PointLight(Vector3(-0.6f, 10, 1), 1.0f));
	}

	// -- scene 4 - week 6
	{
		m_scenes[4].set_shadow_state(true);
		m_scenes[4].m_background_color = Color(0.0f);
		m_scenes[4].set_ambient_intensity(0.05f);
		m_scenes[4].set_reflection_depth(3);

		m_scenes[4].the_camera = Camera(Vector3(-1.0f, 2.5f, -8.0f), Vector3(0.08f, 0.0f, 0.92f), 1.0f, aspect_ratio, 60);

		mat_diff.m_dif_col = Color(0.9f);
		m_scenes[4].scene_objects.push(new Plane(Vector3(0.0f, -1.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f), mat_diff));
		mat_diff.m_dif_col = Color(0.9f);
		m_scenes[4].scene_objects.push(new Plane(Vector3(0.0f, 5.5f, 0.0f), Vector3(0.0f, -1.0f, 0.0f), mat_diff));
		mat_diff.m_dif_col = Color(1.0f, 0.0f, 0.0f);
		m_scenes[4].scene_objects.push(new Plane(Vector3(-4.0f, 0.0f, 0.0f), Vector3(1.0f, 0.0f, 0.0f), mat_diff));
		mat_diff.m_dif_col = Color(0.0f, 1.0f, 0.0f);
		m_scenes[4].scene_objects.push(new Plane(Vector3(4.0f, 0.0f, 0.0f), Vector3(-1.0f, 0.0f, 0.0f), mat_diff));
		mat_diff.m_dif_col = Color(0.0f, 0.0f, 1.0f);
		m_scenes[4].scene_objects.push(new Plane(Vector3(0.0f, 0.0f, -9.0f), Vector3(0.0f, 0.0f, 1.0f), mat_diff));
		mat_diff.m_dif_col = Color(0.9f);
		m_scenes[4].scene_objects.push(new Plane(Vector3(0.0f, 0.0f, 6.0f), Vector3(0.0f, 0.0f, -1.0f), mat_diff));

		mat_spec_reflect.m_dif_col = Color(0.1f);
		mat_spec_reflect.m_spec_col = Color(0.1f);
		mat_diff.m_dif_col = Color(0.5f, 0.0f, 0.1f);
		m_scenes[4].scene_objects.push(new Box(Vector3(-3.35f, -1.0f, 2.5f), Vector3(-1.55f, 4.0f, 5.5f), mat_reflect));
		m_scenes[4].scene_objects.push(new Sphere(Vector3(-0.8f, 0.1f, 0.4f), 1.0f, mat_diff_reflect));
		m_scenes[4].scene_objects.push(new Sphere(Vector3(1.5f, 0.1f, 2.0f), 1.0f, mat_diff_reflect));
		// m_scenes[4].scene_objects.push(new Triangle(Vector3(1.5f, -1.0f, 2.0f), Vector3(2.0f, 1.0f, 0s.0f), Vector3(2.5f, -1, -1.0f)));
		// m_scenes[4].scene_objects.push(new Mesh_OBJ(Vector3(-2.0f, 0.0f, -0.5f), "3D_OBJ/Suz_tri.oobj"));

		m_scenes[4].light_objects.push(new PointLight(Vector3(0.0f, 5.0f, 2.0f), 1.0f));
	}
	
	// -- scene 5 - week 7
	{
		m_scenes[5].set_shadow_state(true);
		m_scenes[5].set_animation_state(false);
		
		m_scenes[5].m_background_color = Color(1.0f);
		
		m_scenes[5].the_camera = Camera(Vector3(0, 12.0f, -14.0f), Vector3(0, -0.75, 1), 1.0f, aspect_ratio, 60);

		mat_spec_reflect.m_dif_col = Color(0.1f);
		mat_spec_reflect.m_spec_col = Color(0.1f);

		mat_spec.m_specular = 1.0f;
		mat_diff.m_dif_col = Color(0.7f);
		m_scenes[5].scene_objects.push(new Plane(Vector3(0.0f, -1.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f), mat_diff));
		m_scenes[5].scene_objects.push(new Sphere(Vector3(0.0f, 0.1f, 0.0f), 1.0f, mat_diff_reflect));

		for (size_t i = 0; i < 200; i++)
		{
			const float placement_rad = 40;
			const float ignore_rad = 8.0f;

			Vector3 new_vec = Vector3(rand_0_1() - 0.5f, 0.1f, rand_0_1() - 0.5f) * placement_rad;
			
			if ((new_vec.x > -ignore_rad && new_vec.x < 0) && new_vec.z > -ignore_rad && new_vec.z < ignore_rad)
				new_vec.x += -ignore_rad;
			if ((new_vec.x > 0 && new_vec.x < ignore_rad) && new_vec.z > -ignore_rad && new_vec.z < ignore_rad)
				new_vec.x += ignore_rad;
			
			if ((new_vec.z > -ignore_rad && new_vec.z < 0) && new_vec.x > -ignore_rad && new_vec.x < ignore_rad)
				new_vec.z += -ignore_rad;
			if ((new_vec.z > 0 && new_vec.z < ignore_rad) && new_vec.x > -ignore_rad && new_vec.x < ignore_rad)
				new_vec.z += ignore_rad;
			
			mat_diff.m_dif_col = Color(rand_0_1(), rand_0_1(), rand_0_1());
			mat_spec.m_spec_col = Color(rand_0_1(), rand_0_1(), rand_0_1());

			m_scenes[5].scene_objects.push(new Box(Vector3(new_vec), 
				Vector3(
					new_vec.x + rand_0_1() * 2.0f, 
					new_vec.y + rand_0_1() * 2.5f, 
					new_vec.z + rand_0_1() * 2.0f), mat_diff));
		}
		//m_scenes[5].m_the_bvh.create(m_scenes[5].scene_objects, 0);
		//m_scenes[5].set_visualize_bvh_state(true);
		
		m_scenes[5].light_objects.push(new PointLight(Vector3(-4.0f, 10, 0), 1.0f));
	}
	
	// -- scene 6
	{
		m_scenes[6].set_animation_state(true);

		m_scenes[6].m_background_color = Color(0.1f);

		m_scenes[6].the_camera = Camera(Vector3(0, 20.5f, -0), Vector3(0, -1, 1), 1.0f, aspect_ratio, 60);

		mat_spec_reflect.m_dif_col = Color(0.1f);
		mat_spec_reflect.m_spec_col = Color(0.1f);

		mat_spec.m_specular = 1.0f;
		m_scenes[6].scene_objects.push(new Plane(Vector3(-2.0f, -1.0f, 4.0f), Vector3(0.0f, 1.0f, 0.0f), mat_spec));
		m_scenes[6].scene_objects.push(new Box(Vector3(2, -1, 4), 4, mat_diff));
		m_scenes[6].scene_objects.push(new Triangle(Vector3(-10.0f, -1.0f, 20.0f), Vector3(0.0f, 20.0f, 20.0f), Vector3(10.0f, -1, 20.0f)));

		for (size_t i = 0; i < 12; i++)
		{
			const float placement_rad = 250;

			const float r_rad = fmax(static_cast<float>(rand()) / RAND_MAX, 0.8f) + 1.0f;

			const Vector3 new_vec = Vector3(rand_0_1() - 0.5f, 0, rand_0_1() - 0.5f) * placement_rad;
			mat_diff.m_dif_col = Color(rand_0_1(), rand_0_1(), rand_0_1());
			mat_spec.m_spec_col = Color(rand_0_1(), rand_0_1(), rand_0_1());

			m_scenes[6].scene_objects.push(new Box(Vector3(new_vec), Vector3(new_vec.x + rand_0_1() + 10.0f, new_vec.y + rand_0_1() * 20.0f, new_vec.z + rand_0_1() + 15.0f), mat_diff));
		}

		m_scenes[6].light_objects.push(new PointLight(Vector3(-2, 24, 8), 2.0f));
	}
	
	// -- scene 7
	{
		m_scenes[7].set_animation_state(true);

		m_scenes[7].m_background_color = Color(0);

		m_scenes[7].the_camera = Camera(Vector3(2, 1, -3), Vector3(-0.5f, -0.1f, 1), 1.0f, aspect_ratio, 60);

		mat_spec_reflect.m_dif_col = Color(0.1f);
		mat_spec_reflect.m_spec_col = Color(0.1f);
		m_scenes[7].scene_objects.push(new Plane(Vector3(0.0f, -1.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f), mat_plane_checkerboard));
		m_scenes[7].scene_objects.push(new Sphere(Vector3(-1.0f, 0.0f, 4.0f), 1.0f, mat_spec_reflect));

		m_scenes[7].light_objects.push(new PointLight(Vector3(0, 5, 0), 1.0f));
	}
	
	// -- scene 8
	{
		m_scenes[8].set_animation_state(false);

		m_scenes[8].m_background_color = Color(0.2f, 0.4f, 0.4f);

		m_scenes[8].the_camera = Camera(Vector3(0, 12, -15), Vector3(0, -0.5f, 0.9f), 1.0f, aspect_ratio, 50);

		m_scenes[8].scene_objects.push(new Sphere(Vector3(0.0f, 3.0f, 15.0f), 3.0f, mat_spec_reflect));
		m_scenes[8].scene_objects.push(new Sphere(Vector3(4.0f, 3.0f, 15.0f), 4.0f, mat_spec_reflect));
		m_scenes[8].scene_objects.push(new Sphere(Vector3(-4.0f, 3.0f, 15.0f), 4.0f, mat_spec_reflect));
		for (size_t i = 0; i < 3; i++)
		{
			const float placement_rad = 60;
			
			const float r_rad = (static_cast<float>(rand()) / RAND_MAX) + 0.75f;
			
			const Vector3 new_vec = Vector3(rand_0_1() - 0.5f, 0, rand_0_1()) * placement_rad;
			mat_diff.m_dif_col = Color(rand_0_1(), rand_0_1(), rand_0_1());
			mat_spec.m_spec_col = Color(rand_0_1(), rand_0_1(), rand_0_1());

			if (rand() % 8)
				m_scenes[8].scene_objects.push(new Sphere(Vector3(new_vec), r_rad, rand() % 4 ? mat_diff : mat_spec));
			else if (rand() % 4)
				m_scenes[8].scene_objects.push(new Box(Vector3(new_vec), Vector3(new_vec.x + rand_0_1() + 0.1f, new_vec.y + rand_0_1() * 3.0f, new_vec.z + rand_0_1() + 0.1f), mat_diff));
			else
				m_scenes[8].scene_objects.push(new Box(Vector3(new_vec), r_rad + 0.2f, mat_diff));
		}
		
		mat_spec_reflect.m_dif_col = Color(0.1f);
		mat_spec_reflect.m_spec_col = Color(0.1f);
		mat_diff.m_dif_col = Color(0.1f, 0.1f, 0.4f);
		m_scenes[8].scene_objects.push(new Plane(Vector3(0.0f, -1.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f), mat_plane_checkerboard));
		mat_diff.m_dif_col = Color(0.5f, 0.1f, 0.0f);

		m_scenes[8].light_objects.push(new PointLight(Vector3(-20, 4, 40), 1.0f));
		m_scenes[8].light_objects.push(new PointLight(Vector3(0, 10, 10), 1.0f));

		// create BVH for this scenes objects
		m_scenes[8].m_the_bvh.create(m_scenes[8].scene_objects, 0);
		m_scenes[8].set_visualize_bvh_state(true);
	}

	// -- scene 9
	{
		m_scenes[9].set_animation_state(false);
		m_scenes[9].set_shadow_state(true);
		m_scenes[9].set_ambient_intensity(0);

		m_scenes[9].m_background_color = Color(0.0f, 0.0f, 0.0f);
		//m_scenes[9].m_background_color = Color(0.05f, 0.8f, 0.9f); // 28,207,232
		m_scenes[9].the_camera = Camera(Vector3(0, 0, 0), Vector3(0, 0, 1), 1.0f, aspect_ratio, 60);

		mat_diff.m_dif_col = Color(0.8f);
		m_scenes[9].scene_objects.push(new Plane(Vector3(0.0f, 0.0f, 5.0f), Vector3(0.0f, 0.0f, -1.0f), mat_diff));
		mat_diff.m_dif_col = Color(1, 0, 0);
		//m_scenes[9].scene_objects.push(new Sphere(Vector3(0.0f, 4.0f, 5.0f), 4.0f, mat_spec_reflect));
		m_scenes[9].scene_objects.push(new Mesh_OBJ(Vector3(-1.0f, -0.2f, 2.0f), "3D_OBJ/TheDion.oobj"));

		//m_scenes[9].light_objects.push(new PointLight(Vector3(-0.5f, -1.5f, 0.0f), 1.0f));
		m_scenes[9].light_objects.push(new PointLight(Vector3(-0.5f, -1.0f, 0.0f), 0.5f));
		m_scenes[9].light_objects.push(new PointLight(Vector3(0.5f, 1.1f, 0.0f), 0.5f));
	}
}