#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"
#include "ModulePlayer.h"
#include "PhysVehicle3D.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->camera->Move(vec3(0.0f, 5.0f, -5.0f));
	App->camera->LookAt(vec3(0, 0, 15));

	// Create sensor cube (will trigger with car)
	sensor_cube = App->physics->AddBody(Cube(5, 2, 5), 0.0);
	sensor_cube->SetAsSensor(true);
	sensor_cube->SetPos(0, 1, 100);

	coin = Cylinder(1.0f, 0.5f);
	coin.SetPos(5, 3, 5);
	coin.color = Blue;

	platform = Cube(50, 1, 30);
	platform.SetPos(0, 1, 20);
	platform.color = White;
	
	mud=App->physics->AddBody(Cube(50, 6, 30), 0.0);
	mud->SetPos(0, 1, 30);
	//mud->collision_listeners.add(this);
	mud->SetAsSensor(true);

	CreateCube(vec3(2, 5, 1), vec3(0, 40, 10), vec3(0, 0, 0), Black);
	light[0] = CreateCylinder(vec2(0.5f, 0.2f), vec3(0, 40, 9), vec3(0, 90, 0), Color(0.1f, 0.1f, 0.1f));

	CreateCube(vec3(2, 5, 1), vec3(2, 40, 10), vec3(0, 0, 0), Black);
	light[1] = CreateCylinder(vec2(0.5f, 0.2f), vec3(2, 40, 9), vec3(0, 90, 0), Color(0.1f, 0.1f, 0.1f));

	CreateCube(vec3(2, 5, 1), vec3(4, 40, 10), vec3(0, 0, 0), Black);
	light[2] = CreateCylinder(vec2(0.5f, 0.2f), vec3(4, 40, 9), vec3(0, 90, 0), Color(0.1f, 0.1f, 0.1f));

	CreateCube(vec3(2, 5, 1), vec3(6, 40, 10), vec3(0, 0, 0), Black);
	light[3] = CreateCylinder(vec2(0.5f, 0.2f), vec3(6, 40, 9), vec3(0, 90, 0), Color(0.1f, 0.1f, 0.1f));

	CreateCube(vec3(2, 5, 1), vec3(8, 7, 10), vec3(0, 0, 0), Black);
	light[4] = CreateCylinder(vec2(0.5f, 0.2f), vec3(8, 7, 9), vec3(0, 90, 0), Color(0.1f, 0.1f, 0.1f));

	constraintPlatform = Cube(15, 0.5f, 30);
	constraintPlatform.SetPos(0, 3, 80);
	constraintPlatform.SetRotation(20, vec3(1, 0, 0));
	constraintPlatformBody = App->physics->AddBody(constraintPlatform, 0.1f);
	constraintPlatform.physbody = constraintPlatformBody;

	constraintCylinder = Cylinder(0.25f, 15);
	constraintCylinder.SetPos(0, 3, 80);
	constraintCylinderBody = App->physics->AddBody(constraintCylinder, 0.0f);
	constraintCylinder.physbody = constraintCylinderBody;

	btHingeConstraint* hinge = App->physics->AddConstraintHinge(*constraintPlatformBody, *constraintCylinderBody, vec3(0, 0, 0), vec3(0, 0, 0), vec3(1, 0, 0), vec3(1, 0, 0), true);

	CreateCube(vec3(50, 1, 50), vec3(5, 1, 5), vec3(0, 0, 0), White);

	CreateCube(vec3(29.30f, 1.44f, 28.84f), vec3(16.62f, 39.06f, 302.95f), vec3(-0.00f, 0.00f, 0.42f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(81.28f, 1.44f, 28.84f), vec3(-153.80f, 46.16f, -130.91f), vec3(-0.00f, 0.00f, 0.42f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(146.39f, 1.44f, 28.84f), vec3(288.94f, 35.82f, 62.69f), vec3(-0.00f, 0.00f, 0.42f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(155.00f, 1.44f, 28.84f), vec3(-454.39f, 17.45f, 3.24f), vec3(-0.00f, 0.00f, 0.22f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(64.97f, 1.94f, 29.83f), vec3(-193.50f, 1.97f, 60.28f), vec3(-0.00f, 0.00f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(64.97f, 1.94f, 29.83f), vec3(-244.06f, 1.97f, 67.22f), vec3(-0.00f, 0.21f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(64.97f, 1.94f, 29.83f), vec3(-296.08f, 1.97f, 82.35f), vec3(-0.00f, 0.35f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(41.22f, 1.94f, 29.83f), vec3(-330.44f, 1.97f, 99.37f), vec3(-0.00f, 1.08f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(64.97f, 1.94f, 29.83f), vec3(-342.11f, 1.97f, 148.87f), vec3(-0.00f, 1.51f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(64.97f, 1.94f, 29.83f), vec3(-352.82f, 1.97f, 180.08f), vec3(-0.00f, 1.03f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(64.97f, 1.94f, 29.83f), vec3(-390.34f, 1.97f, 204.48f), vec3(-0.00f, 0.03f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(64.97f, 1.94f, 29.83f), vec3(-437.82f, 1.97f, 206.75f), vec3(-0.00f, 0.00f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(95.34f, 1.94f, 31.14f), vec3(-561.46f, 1.97f, 199.24f), vec3(-0.00f, -0.12f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(91.87f, 1.94f, 31.14f), vec3(-632.01f, 1.97f, 161.41f), vec3(-0.00f, -0.78f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(57.20f, 1.94f, 31.14f), vec3(-668.34f, 1.97f, 107.51f), vec3(-0.00f, -1.23f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(57.20f, 1.94f, 31.14f), vec3(-671.52f, 1.97f, 63.18f), vec3(0.00f, 1.37f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(57.20f, 1.94f, 31.14f), vec3(-640.51f, 1.97f, 16.60f), vec3(0.00f, 0.63f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(57.20f, 1.94f, 31.14f), vec3(-616.02f, 1.97f, 5.53f), vec3(0.00f, 0.14f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(57.20f, 1.94f, 31.14f), vec3(56.41f, 33.51f, 3.57f), vec3(0.00f, -0.12f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(57.20f, 1.94f, 31.14f), vec3(95.18f, 33.51f, 11.78f), vec3(0.00f, -0.24f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(57.20f, 1.94f, 31.14f), vec3(122.54f, 33.51f, 23.79f), vec3(0.00f, -0.50f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(57.20f, 1.94f, 31.14f), vec3(147.17f, 33.51f, 47.81f), vec3(0.00f, -1.17f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(57.20f, 1.94f, 31.14f), vec3(147.02f, 33.51f, 62.25f), vec3(0.00f, -1.52f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(57.20f, 1.94f, 31.14f), vec3(137.90f, 33.51f, 89.16f), vec3(-0.00f, 1.06f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(57.20f, 1.94f, 31.14f), vec3(126.50f, 33.51f, 95.70f), vec3(-0.00f, 0.59f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(57.20f, 1.94f, 31.14f), vec3(96.24f, 33.51f, 108.47f), vec3(-0.00f, 0.30f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(57.20f, 1.94f, 31.14f), vec3(55.50f, 33.51f, 117.14f), vec3(-0.00f, 0.14f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(57.20f, 1.94f, 31.14f), vec3(21.90f, 33.51f, 119.87f), vec3(-0.00f, -0.00f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(41.74f, 1.94f, 31.14f), vec3(-5.62f, 33.51f, 122.61f), vec3(-0.00f, 0.58f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(41.74f, 1.94f, 31.14f), vec3(-26.29f, 33.51f, 141.92f), vec3(-0.00f, 0.98f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(41.74f, 1.94f, 31.14f), vec3(-41.04f, 33.51f, 164.12f), vec3(-0.00f, 0.98f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(41.74f, 1.94f, 31.14f), vec3(-53.36f, 33.51f, 176.13f), vec3(-0.00f, 0.39f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(41.74f, 1.94f, 31.14f), vec3(-53.36f, 33.51f, 176.13f), vec3(-0.00f, 0.39f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(41.74f, 1.94f, 31.14f), vec3(-228.64f, 33.83f, 181.80f), vec3(-0.00f, 0.39f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(41.74f, 1.94f, 31.14f), vec3(-241.87f, 33.83f, 192.81f), vec3(-0.00f, 1.31f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(41.74f, 1.94f, 31.14f), vec3(-243.78f, 33.83f, 216.54f), vec3(-0.00f, 1.57f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(41.74f, 1.94f, 31.14f), vec3(-235.12f, 33.83f, 237.50f), vec3(0.00f, -0.94f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(106.61f, 1.94f, 31.14f), vec3(-196.71f, 33.83f, 273.63f), vec3(0.00f, -0.69f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(41.74f, 1.94f, 31.14f), vec3(-166.79f, 33.83f, 293.06f), vec3(0.00f, -0.45f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(41.74f, 1.94f, 31.14f), vec3(-134.35f, 33.83f, 300.99f), vec3(0.00f, -0.06f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(41.74f, 1.94f, 31.14f), vec3(208.89f, 32.35f, 301.86f), vec3(0.00f, 0.03f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(41.74f, 1.94f, 31.14f), vec3(237.27f, 32.35f, 308.67f), vec3(0.00f, -0.55f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(41.74f, 1.94f, 31.14f), vec3(255.80f, 32.35f, 328.34f), vec3(0.00f, -1.04f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(41.74f, 1.94f, 31.14f), vec3(329.57f, 32.35f, 455.83f), vec3(0.00f, -0.78f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(41.74f, 1.94f, 31.14f), vec3(351.89f, 32.35f, 467.56f), vec3(0.00f, -0.03f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(41.74f, 1.94f, 31.14f), vec3(370.43f, 32.35f, 458.10f), vec3(0.00f, 0.69f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(41.74f, 1.94f, 31.14f), vec3(486.57f, 32.35f, 305.64f), vec3(0.00f, 1.14f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(85.40f, 1.94f, 31.14f), vec3(505.86f, 32.35f, 252.68f), vec3(0.00f, 1.30f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(56.60f, 1.94f, 31.14f), vec3(503.59f, 32.35f, 224.31f), vec3(-0.00f, -1.44f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(56.60f, 1.94f, 31.14f), vec3(495.51f, 32.35f, 194.08f), vec3(-0.00f, -0.95f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(56.60f, 1.94f, 31.14f), vec3(471.68f, 32.35f, 152.84f), vec3(-0.00f, -1.26f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(56.60f, 1.94f, 31.14f), vec3(466.00f, 32.33f, 111.23f), vec3(-0.00f, -1.54f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(56.60f, 1.94f, 31.14f), vec3(448.03f, 32.42f, -97.41f), vec3(-0.00f, -1.16f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(56.60f, 1.94f, 31.14f), vec3(463.28f, 32.42f, -48.93f), vec3(-0.00f, -1.42f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(56.60f, 1.94f, 31.14f), vec3(466.55f, 32.42f, -17.33f), vec3(-0.00f, -1.55f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(56.60f, 1.94f, 31.14f), vec3(420.24f, 32.42f, -136.63f), vec3(-0.00f, -0.66f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(56.60f, 1.94f, 31.14f), vec3(375.03f, 32.42f, -165.45f), vec3(-0.00f, -0.27f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(113.81f, 1.94f, 31.14f), vec3(297.67f, 32.42f, -175.80f), vec3(-0.00f, -0.09f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(83.63f, 1.94f, 31.14f), vec3(201.80f, 32.42f, -189.96f), vec3(-0.00f, -0.23f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(83.63f, 1.94f, 31.14f), vec3(136.97f, 32.42f, -212.84f), vec3(-0.00f, -0.44f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(218.41f, 1.94f, 31.14f), vec3(10.04f, 32.42f, -285.90f), vec3(-0.00f, -0.58f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(54.54f, 1.94f, 31.14f), vec3(-105.31f, 32.42f, -346.91f), vec3(-0.00f, -0.13f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(54.54f, 1.94f, 31.14f), vec3(-143.99f, 32.42f, -337.65f), vec3(-0.00f, 0.51f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(54.54f, 1.94f, 31.14f), vec3(-240.41f, 32.42f, -259.20f), vec3(-0.00f, 0.96f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(54.54f, 1.94f, 31.14f), vec3(-252.94f, 32.42f, -227.61f), vec3(-0.00f, 1.47f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(54.54f, 1.94f, 31.14f), vec3(-255.66f, 32.42f, -184.57f), vec3(0.00f, -1.52f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(54.54f, 1.94f, 31.14f), vec3(-239.86f, 32.42f, -149.16f), vec3(0.00f, -0.73f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(33.37f, 1.94f, 31.14f), vec3(-212.08f, 32.42f, -132.82f), vec3(0.00f, -0.13f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(92.92f, 1.94f, 31.14f), vec3(-68.98f, 62.94f, -132.43f), vec3(0.00f, 0.05f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(44.28f, 1.94f, 31.14f), vec3(-16.70f, 62.94f, -133.22f), vec3(0.00f, -0.08f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(44.28f, 1.94f, 31.14f), vec3(-6.20f, 62.94f, -131.11f), vec3(0.00f, -0.32f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(44.28f, 1.94f, 31.14f), vec3(17.71f, 62.94f, -112.99f), vec3(0.00f, -1.03f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(58.25f, 1.94f, 31.14f), vec3(36.24f, 62.94f, -44.97f), vec3(0.00f, -1.56f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(110.57f, 1.94f, 31.14f), vec3(17.90f, 62.94f, 26.77f), vec3(-0.00f, 1.24f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(110.57f, 1.94f, 31.14f), vec3(-10.48f, 62.94f, 125.51f), vec3(-0.00f, 1.40f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(54.03f, 1.94f, 31.14f), vec3(-13.13f, 62.94f, 180.64f), vec3(0.00f, -1.50f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(54.03f, 1.94f, 31.14f), vec3(-0.73f, 62.94f, 214.68f), vec3(0.00f, -1.05f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(54.03f, 1.94f, 31.14f), vec3(34.07f, 62.94f, 242.68f), vec3(0.00f, -0.46f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(54.03f, 1.94f, 31.14f), vec3(74.93f, 62.94f, 248.73f), vec3(0.00f, -0.00f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(54.03f, 1.94f, 31.14f), vec3(119.19f, 62.94f, 233.60f), vec3(0.00f, 0.56f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(54.03f, 1.94f, 31.14f), vec3(141.13f, 62.94f, 198.42f), vec3(0.00f, 1.19f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(54.03f, 1.94f, 31.14f), vec3(148.70f, 62.94f, 153.51f), vec3(0.00f, 1.49f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(60.65f, 1.94f, 31.14f), vec3(146.52f, 62.94f, -21.90f), vec3(0.00f, 1.49f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(54.03f, 1.94f, 31.14f), vec3(161.77f, 62.94f, -69.30f), vec3(0.00f, 1.07f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(63.95f, 1.94f, 31.14f), vec3(197.18f, 62.94f, -100.35f), vec3(0.00f, 0.52f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(54.03f, 1.94f, 31.14f), vec3(234.22f, 62.94f, -105.80f), vec3(0.00f, 0.07f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(54.03f, 1.94f, 31.14f), vec3(283.25f, 62.94f, -103.62f), vec3(0.00f, -0.28f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(54.03f, 1.94f, 31.14f), vec3(334.08f, 62.94f, -85.83f), vec3(0.00f, -0.45f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(60.41f, 1.94f, 31.14f), vec3(379.52f, 62.94f, -56.19f), vec3(0.00f, -0.73f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(54.03f, 1.94f, 31.14f), vec3(408.88f, 62.94f, -13.73f), vec3(0.00f, -1.16f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(54.03f, 1.94f, 31.14f), vec3(410.51f, 62.94f, 28.21f), vec3(-0.00f, 1.27f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(53.37f, 1.94f, 31.14f), vec3(395.10f, 62.94f, 53.46f), vec3(-0.00f, 0.54f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(32.48f, 1.94f, 31.14f), vec3(363.88f, 62.94f, 61.91f), vec3(-0.00f, 0.00f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(153.52f, 1.94f, 31.14f), vec3(-141.44f, 33.51f, 177.85f), vec3(0.00f, -0.00f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(153.52f, 1.94f, 31.14f), vec3(-46.86f, 33.51f, 302.14f), vec3(0.00f, -0.00f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(153.52f, 1.94f, 31.14f), vec3(167.51f, 32.29f, 301.84f), vec3(0.00f, -0.00f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(153.52f, 1.94f, 31.14f), vec3(282.89f, 32.29f, 379.39f), vec3(0.00f, -1.06f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(174.54f, 1.94f, 31.14f), vec3(430.75f, 32.29f, 383.49f), vec3(0.00f, 0.92f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(102.85f, 1.94f, 31.14f), vec3(-189.30f, 33.51f, -306.07f), vec3(0.00f, 0.65f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(436.20f, 1.94f, 31.14f), vec3(9.94f, 1.97f, 60.75f), vec3(-0.00f, 0.00f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(430.10f, 1.94f, 31.14f), vec3(-164.97f, 33.51f, 2.80f), vec3(0.00f, -0.00f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(57.20f, 1.94f, 31.14f), vec3(-590.43f, 1.97f, 2.74f), vec3(0.00f, 0.08f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(57.20f, 1.94f, 31.14f), vec3(-537.33f, 1.97f, 2.22f), vec3(0.00f, -0.01f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(127.14f, 1.94f, 31.14f), vec3(146.73f, 62.94f, 68.54f), vec3(0.00f, -1.55f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(116.78f, 1.94f, 31.14f), vec3(465.63f, 32.33f, 32.92f), vec3(0.00f, 1.57f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(33.37f, 1.94f, 31.14f), vec3(-198.40f, 32.42f, -131.00f), vec3(0.00f, 0.01f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(41.22f, 1.94f, 29.83f), vec3(-338.01f, 1.97f, 113.24f), vec3(-0.00f, 1.23f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(58.25f, 1.94f, 31.14f), vec3(29.18f, 62.94f, -84.86f), vec3(0.00f, -1.28f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(95.34f, 1.94f, 31.14f), vec3(-499.42f, 1.97f, 206.81f), vec3(-0.00f, -0.05f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(37.55f, 1.94f, 31.14f), vec3(-664.46f, 1.97f, 42.52f), vec3(0.00f, 1.05f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));


	logo = App->renderer3D->LoadTexture("Assets/Bugatti_logo.png");
	logo2 = App->renderer3D->LoadTexture("Assets/logo2.png");
	road = App->renderer3D->LoadTexture("Assets/pistanivelmedio.png");
	road2 = App->renderer3D->LoadTexture("Assets/arriba.png");
	road3 = App->renderer3D->LoadTexture("Assets/imagenotaa2.png");
	road4 = App->renderer3D->LoadTexture("Assets/mandanga.png");
	arrow = App->renderer3D->LoadTexture("Assets/arrow.png");

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	Plane p(0, 1, 0, 0);
	p.axis = true;
	p.Render();
	p.wire = false;

	angle++;
	coin.SetRotation(angle, vec3(0, 1, 0));
	coin.Render();

	for (int i = 0; i < 5; i++)
	{
		light[i].Render();
	}

	for (auto& cube : cubes)
	{
		cube.Render();
	}
	constraintPlatform.Render();
	constraintCylinder.Render();

	float radius = 0.3f;
	float logoAngle = angle - 90;
	float logoPosX = 5 - radius * sin(logoAngle * DEGTORAD);
	float logoPosY = 3;
	float logoPosZ = 5 - radius * cos(logoAngle * DEGTORAD);

	App->renderer3D->DrawTexture(logo2, { logoPosX, logoPosY, logoPosZ }, 1.0f, logoAngle, vec3(0, 1, 0));

	float logoAngleOtherSide = angle + 90;

	float logoPosXOtherSide = 5 - radius * sin(logoAngleOtherSide * DEGTORAD);
	float logoPosZOtherSide = 5 - radius * cos(logoAngleOtherSide * DEGTORAD);

	App->renderer3D->DrawTexture(logo2, { logoPosXOtherSide, logoPosY, logoPosZOtherSide }, 1.0f, logoAngleOtherSide, vec3(0, 1, 0));

	//App->renderer3D->DrawTexture(road, { 0, 1.6f, 10.0f }, 50.0f, 90, vec3(1, 0, 0));

	//App->renderer3D->DrawTexture(road, { -500, 2.19f, 122.0f }, 530.0f, 90, vec3(1, 0, 0));

	//suelo
	App->renderer3D->DrawTexture(road3, { -220, 3.0f, 100 }, 920.0f, 90, vec3(1, 0, 0));


	btQuaternion quat1;
	quat1.setEulerZYX(27 * DEGTORAD, 0 * DEGTORAD, 90 * DEGTORAD);

	float angle1 = quat1.getAngle() * RADTODEG;
	btVector3 axis1 = quat1.getAxis();

	App->renderer3D->DrawTexture(road4, { -156, 48, -130 }, 80.0f, angle1, vec3(axis1.getX(), axis1.getY(), axis1.getZ()));

	//central
	App->renderer3D->DrawTexture(road, { 70, 35.0f, 60.0f }, 900.0f, 90, vec3(1, 0, 0));

	//arriba
	App->renderer3D->DrawTexture(road2, { 150, 64.0f, 58.0f }, 550.0f, 90, vec3(1, 0, 0));

	App->renderer3D->DrawTexture(arrow, { 0, 0.1, 100 }, 5.0f, 90, vec3(1, 0, 0));

	/*const btVector3& chassisPos = App->player->vehicle[App->network->clientIndex]->vehicle->getChassisWorldTransform().getOrigin();
	btQuaternion carRotation = App->player->vehicle[App->network->clientIndex]->vehicle->getChassisWorldTransform().getRotation();
	float carAngle = carRotation.getAngle() * RADTODEG;

	btVector3 logoOffset = btVector3(0.0f, 1.0f, -2.35f);

	btVector3 rotatedOffset = App->player->vehicle[App->network->clientIndex]->vehicle->getChassisWorldTransform().getBasis() * logoOffset;

	btVector3 logoPos = chassisPos + rotatedOffset;

	if (carRotation.getAxis().y() < 0)
	{
		carAngle = -carAngle;
	}

	App->renderer3D->DrawTexture(logo, { logoPos.getX(), logoPos.getY(), logoPos.getZ() }, 0.7f, carAngle, vec3(0, 1, 0));*/

	if (lightIndex < 6)lightTimer++;
	if (lightTimer > 100 && lightIndex < 5)
	{
		lightTimer = 0;
		light[lightIndex].color = Red;
		lightIndex++;
	}
	else if (lightTimer > 150 && lightIndex == 5)
	{
		for (int i = 0; i < 5; i++)
		{
			light[i].color = Green;
		}
		lightIndex = 6;
	}
	
	constraintPlatformBody->GetRotation(&constraintPlatform.transform);

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
}

Cube ModuleSceneIntro::CreateCube(vec3 size, vec3 position, vec3 rotation, Color color) 
{
	Cube platform(size.x, size.y, size.z);
	platform.SetPos(position.x, position.y, position.z);


	btQuaternion quat;
	quat.setEulerZYX(rotation.z, rotation.y, rotation.x );

	float angle = quat.getAngle() * RADTODEG;
	btVector3 axis = quat.getAxis();

	platform.SetRotation(angle, vec3(axis.getX(), axis.getY(), axis.getZ()));

	platform.color = color;

	auto physBody = App->physics->AddBody(platform, 0.0f);
	platform.physbody = physBody;

	cubes.push_back(platform);

	return platform;
}

Cylinder ModuleSceneIntro::CreateCylinder(vec2 size, vec3 position, vec3 rotation, Color color)
{
	Cylinder platform(size.x, size.y);
	platform.SetPos(position.x, position.y, position.z);

	btQuaternion quat;
	quat.setEulerZYX(rotation.z * DEGTORAD, rotation.y * DEGTORAD, rotation.x * DEGTORAD);

	float angle = quat.getAngle() * RADTODEG;
	btVector3 axis = quat.getAxis();

	platform.SetRotation(angle, vec3(axis.getX(), axis.getY(), axis.getZ()));

	platform.color = color;

	auto physBody = App->physics->AddBody(platform, 0.0f);
	platform.physbody = physBody;

	return platform;
}



