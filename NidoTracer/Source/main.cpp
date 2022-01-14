#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Keyboard.hpp>

#include <Misc/Color.h>

#include "DataTypes/LinkedList.h"

#include "Renderer.h"
#include "SceneManager.h"

// this project links a lib build from Dependencies, also depends on Dependencies project
int main()
{
	Renderer the_renderer;
	SceneManager the_scene_manager;
	
	sf::Texture texture;
	texture.loadFromImage(the_renderer.create_image(the_scene_manager));

	// create sfml windows context
	sf::RenderWindow my_window(sf::VideoMode(the_renderer.get_pixel_width(), the_renderer.get_pixel_height()), "NidoTracer");
	my_window.setFramerateLimit(24);

	bool display_once = false;
	while (my_window.isOpen())
	{
		if (the_scene_manager.get_active_scene().is_animated() || !display_once)
		{
			display_once = true;
			
			sf::Sprite sprite;
			sprite.setTexture(texture, true);
			sprite.setScale(1.f, -1.f);
			sprite.setPosition(0,  static_cast<float>(the_renderer.get_pixel_height()));

			my_window.draw(sprite);
			my_window.display();
			
			texture.loadFromImage(the_renderer.create_image(the_scene_manager));
		}
		
		// check triggered window events
		sf::Event event;
		while (my_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				my_window.close();

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				my_window.close();

			// BVH toggle
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))
				the_renderer.m_ignore_bvh = true, display_once = false;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
				the_renderer.m_ignore_bvh = false, display_once = false;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::U))
				the_scene_manager.get_active_scene().set_visualize_bvh_state(true), display_once = false;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::I))
				the_scene_manager.get_active_scene().set_visualize_bvh_state(false), display_once = false;
			// Animation toggle
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Period))
				the_scene_manager.get_active_scene().set_animation_state(true), display_once = false;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Comma))
				the_scene_manager.get_active_scene().set_animation_state(false), display_once = false;
			// Active view Camera state toggle
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
				the_scene_manager.get_active_scene().the_camera.set_view_state(ViewState::Orthographic), display_once = false;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
				the_scene_manager.get_active_scene().the_camera.set_view_state(ViewState::Perspective), display_once = false;
			// FOV changing, resetting
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
				the_scene_manager.get_active_scene().the_camera.add_fov(0.2f), display_once = false;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::N))
				the_scene_manager.get_active_scene().the_camera.add_fov(-0.2f), display_once = false;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
				the_scene_manager.get_active_scene().the_camera.reset_to_default(), display_once = false;
			
			switch (event.key.code)
			{
			case sf::Keyboard::Num0:
				the_scene_manager.set_active_scene(0);
				display_once = false;
				break;
			case sf::Keyboard::Num1:
				the_scene_manager.set_active_scene(1);
				display_once = false;
				break;
			case sf::Keyboard::Num2:
				the_scene_manager.set_active_scene(2);
				display_once = false;
				break;
			case sf::Keyboard::Num3:
				the_scene_manager.set_active_scene(3);
				display_once = false;
				break;
			case sf::Keyboard::Num4:
				the_scene_manager.set_active_scene(4);
				display_once = false;
				break;
			case sf::Keyboard::Num5:
				the_scene_manager.set_active_scene(5);
				display_once = false;
				break;
			case sf::Keyboard::Num6:
				the_scene_manager.set_active_scene(6);
				display_once = false;
				break;
			case sf::Keyboard::Num7:
				the_scene_manager.set_active_scene(7);
				display_once = false;
				break;
			case sf::Keyboard::Num8:
				the_scene_manager.set_active_scene(8);
				display_once = false;
				break;
			case sf::Keyboard::Num9:
				the_scene_manager.set_active_scene(9);
				display_once = false;
				break;
			default:
				break;
			}
			
			/*
			 * // todo apply faster key scene switch state
			 *if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0) ||
				sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) ||
				sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
			{
				sf::Keyboard::Key e = event.key.code;
				const int pressedcode = event.key.code;
				const int mincode = sf::Keyboard::Num0;
				printf("%i\n", pressedcode - mincode);
				the_scene_manager.set_active_scene(0);

				display_once = false;
			}*/
		}
	}

	
	return 0;
}