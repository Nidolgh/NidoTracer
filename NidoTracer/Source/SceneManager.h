#pragma once
#include "Misc/ScreenResolutionConsts.h"

#include "Scene.h"
#include "Objects/Camera.h"

#include "Objects/Lights/PointLight.h"
#include "Objects/Ray3D.h"
#include "Objects/Plane.h"
#include "Objects/Sphere.h"
#include "Objects/Box.h"
#include "Objects/Box_Rotatable.h"
#include "Objects/Triangle.h"
#include "Objects/Mesh_OBJ.h"

// pinning
class SceneManager
{
public:
	SceneManager();
	
	Scene& get_active_scene() const { return *m_active_scene; }
	void set_active_scene(const int i) { m_active_scene = &m_scenes[i]; }

	float rand_0_1() const { return (static_cast<float>(rand()) / RAND_MAX); }
	
	Scene* m_active_scene = nullptr;
	Scene m_scenes[10];
};