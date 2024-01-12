#pragma once
#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"
#include "Primitive.h"
#include <vector>
#include <iostream>
#include "ModulePhysics3D.h"
using namespace std;

#define MAX_SNAKE 2

struct PhysBody3D;
struct PhysMotor3D;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void OnCollision(PhysBody3D* body1, PhysBody3D* body2);

	Cube CreateCube(vec3 size, vec3 position, vec3 rotation, Color color);

	Cylinder CreateCylinder(vec2 size, vec3 position, vec3 rotation, Color color);

public:
	/*
	PhysBody3D* pb_snake[MAX_SNAKE];
	Sphere s_snake[MAX_SNAKE];

	PhysBody3D* pb_snake2[MAX_SNAKE];
	Sphere s_snake2[MAX_SNAKE];
	*/

	PhysBody3D* pb_chassis;
	Cube p_chassis;

	PhysBody3D* pb_wheel;
	Cylinder p_wheel;

	PhysBody3D* pb_wheel2;
	Cylinder p_wheel2;

	PhysMotor3D* left_wheel;
	PhysMotor3D* right_wheel;


	PhysBody3D* sensor_cube;
	Cylinder coin;
	Cube platform;
	Cylinder cylinder;
	Sphere sphere;

	PhysBody3D* physBody;

	uint logo, logo2, road;

	vector<Cube> cubes;
	vector<Cylinder> cylinders;

	float angle = 0.0f;

	Cylinder light[5];
	int lightTimer = 0;
	int lightIndex = 0;
};
