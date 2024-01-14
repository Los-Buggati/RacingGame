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
	lobato1= App->audio->LoadFx("Assets/IntroLobato.wav");
	App->audio->PlayFx(lobato1);
	App->audio->PlayMusic("Assets/song1.ogg");
	
	
	LOG("Loading Intro assets");
	bool ret = true;

	App->camera->Move(vec3(0.0f, 5.0f, -5.0f));
	App->camera->LookAt(vec3(0, 0, 15));

	// Create sensor cube (will trigger with car)
	sensor_cube = App->physics->AddBody(Cube(30, 5, 25), 0.0);
	sensor_cube->SetAsSensor(true);
	sensor_cube->SetPos(470, 36, 148);

	sensor_cube2 = App->physics->AddBody(Cube(30, 5, 35), 0.0);
	sensor_cube2->SetAsSensor(true);
	sensor_cube2->SetPos(-290, 36, 0);

	coin[1] = Cylinder(1.0f, 0.5f);
	coin[1].SetPos(16, 37, 302);
	coin[1].color = Blue;
	coin1Body = App->physics->AddBody(coin[1], 0.0);
	coin1Body->SetAsSensor(true);
	coin[1].physbody = coin1Body;
	
	coin[2] = Cylinder(1.0f, 0.5f);
	coin[2].SetPos(5, 37, 0);
	coin[2].color = Blue;
	coin2Body = App->physics->AddBody(coin[2], 0.0);
	coin2Body->SetAsSensor(true);
	coin[2].physbody = coin2Body;

	coin[3] = Cylinder(1.0f, 0.5f);
	coin[3].SetPos(-53.36f, 37.51f, 176.13f);
	coin[3].color = Blue;
	coin3Body = App->physics->AddBody(coin[3], 0.0);
	coin3Body->SetAsSensor(true);
	coin[3].physbody = coin3Body;
	
	coin[4] = Cylinder(1.0f, 0.5f);
	coin[4].SetPos(167.51f, 35.29f, 301.84f);
	coin[4].color = Blue;
	coin4Body = App->physics->AddBody(coin[4], 0.0);
	coin4Body->SetAsSensor(true);
	coin[4].physbody = coin4Body;

	coin[5] = Cylinder(1.0f, 0.5f);
	coin[5].SetPos(-499.42f, 4.97f, 206.81f);
	coin[5].color = Blue;
	coin5Body = App->physics->AddBody(coin[5], 0.0);
	coin5Body->SetAsSensor(true);
	coin[5].physbody = coin5Body;

	coin[6] = Cylinder(1.0f, 0.5f);
	coin[6].SetPos(-10.48f, 63.94f, 125.51f);
	coin[6].color = Blue;
	coin6Body = App->physics->AddBody(coin[6], 0.0);
	coin6Body->SetAsSensor(true);
	coin[6].physbody = coin6Body;

	coin[7] = Cylinder(1.0f, 0.5f);
	coin[7].SetPos(74.93f, 63.94f, 248.73f);
	coin[7].color = Blue;
	coin7Body = App->physics->AddBody(coin[7], 0.0);
	coin7Body->SetAsSensor(true);
	coin[7].physbody = coin7Body;

	coin[8] = Cylinder(1.0f, 0.5f);
	coin[8].SetPos(-561.46f, 2.97f, 199.24f);
	coin[8].color = Blue;
	coin8Body = App->physics->AddBody(coin[8], 0.0);
	coin8Body->SetAsSensor(true);
	coin[8].physbody = coin8Body;

	coin[9] = Cylinder(1.0f, 0.5f);
	coin[9].SetPos(137.90f, 33.51f, 89.16f);
	coin[9].color = Blue;
	coin9Body = App->physics->AddBody(coin[9], 0.0);
	coin9Body->SetAsSensor(true);
	coin[9].physbody = coin9Body;

	//platform = Cube(50, 1, 30);
	//platform.SetPos(0, 1, 20);
	//platform.color = White;
	
	mud=App->physics->AddBody(Cube(100, 6, 70), 0.0);
	mud->SetPos(-270, 5, 80);
	mud->SetAsSensor(true);

	CreateCube(vec3(2, 5, 1), vec3(15, 40, 4), vec3(0, 80, 0), Black);
	light[0] = CreateCylinder(vec2(0.5f, 0.2f), vec3(14, 40, 4), vec3(0, 10, 0), Color(0.1f, 0.1f, 0.1f));

	CreateCube(vec3(2, 5, 1), vec3(15, 40, 2), vec3(0, 80, 0), Black);
	light[1] = CreateCylinder(vec2(0.5f, 0.2f), vec3(14, 40, 2), vec3(0, 10, 0), Color(0.1f, 0.1f, 0.1f));

	CreateCube(vec3(2, 5, 1), vec3(15, 40, 0), vec3(0, 80, 0), Black);
	light[2] = CreateCylinder(vec2(0.5f, 0.2f), vec3(14, 40, 0), vec3(0, 10, 0), Color(0.1f, 0.1f, 0.1f));

	CreateCube(vec3(2, 5, 1), vec3(15, 40, -2), vec3(0, 80, 0), Black);
	light[3] = CreateCylinder(vec2(0.5f, 0.2f), vec3(14, 40, -2), vec3(0, 10, 0), Color(0.1f, 0.1f, 0.1f));

	CreateCube(vec3(2, 5, 1), vec3(15, 40, -4), vec3(0, 80, 0), Black);
	light[4] = CreateCylinder(vec2(0.5f, 0.2f), vec3(14, 40, -4), vec3(0, 10, 0), Color(0.1f, 0.1f, 0.1f));

	constraintPlatform = Cube(26, 0.5f, 40);
	constraintPlatform.SetPos(150, 68, 80);
	constraintPlatform.SetRotation(10, vec3(1, 0, 0));
	constraintPlatformBody = App->physics->AddBody(constraintPlatform, 0.1f);
	constraintPlatform.physbody = constraintPlatformBody;

	constraintCylinder = Cylinder(0.25f, 26);
	constraintCylinder.SetPos(150, 68, 80);
	constraintCylinderBody = App->physics->AddBody(constraintCylinder, 0.0f);
	constraintCylinder.physbody = constraintCylinderBody;

	btHingeConstraint* hinge = App->physics->AddConstraintHinge(*constraintPlatformBody, *constraintCylinderBody, vec3(0, 0, 0), vec3(0, 0, 0), vec3(1, 0, 0), vec3(1, 0, 0), true);

	//CreateCube(vec3(50, 1, 50), vec3(5, 1, 5), vec3(0, 0, 0), White);

	CreateCube(vec3(29.30f, 1.44f, 28.84f), vec3(17.34f, 35.83f, 299.86f), vec3(-0.00f, 0.00f, 0.22f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(81.28f, 1.44f, 25.56f), vec3(-153.80f, 46.16f, -133.28f), vec3(-0.00f, 0.00f, 0.42f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(146.39f, 1.44f, 26.31f), vec3(292.86f, 26.81f, 59.99f), vec3(-0.00f, 0.00f, 0.42f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(155.00f, 1.44f, 26.39f), vec3(-454.18f, 17.92f, -0.99f), vec3(-0.00f, 0.00f, 0.23f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(57.20f, 1.94f, 26.41f), vec3(56.62f, 33.51f, 2.83f), vec3(0.00f, -0.16f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(57.20f, 1.94f, 25.39f), vec3(91.44f, 33.51f, 9.42f), vec3(0.00f, -0.20f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(34.27f, 1.94f, 23.65f), vec3(127.10f, 33.51f, 23.03f), vec3(0.00f, -0.63f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(34.60f, 1.94f, 26.64f), vec3(148.08f, 33.51f, 58.30f), vec3(0.00f, -1.57f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(38.83f, 1.94f, 24.34f), vec3(126.50f, 33.51f, 95.70f), vec3(-0.00f, 0.59f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(30.19f, 1.94f, 25.68f), vec3(85.98f, 33.51f, 111.26f), vec3(-0.00f, 0.19f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(49.86f, 1.94f, 25.87f), vec3(64.37f, 33.51f, 114.92f), vec3(-0.00f, 0.17f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(41.87f, 1.94f, 25.91f), vec3(22.22f, 33.51f, 119.24f), vec3(-0.00f, 0.04f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(83.63f, 1.94f, 26.77f), vec3(207.75f, 33.51f, -189.45f), vec3(-0.00f, -0.26f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(49.63f, 1.94f, 27.66f), vec3(-90.52f, 62.94f, -133.45f), vec3(0.00f, 0.01f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(110.57f, 1.94f, 27.28f), vec3(19.11f, 62.94f, 30.27f), vec3(-0.00f, 1.24f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(62.55f, 1.94f, 27.36f), vec3(-9.30f, 62.94f, 133.32f), vec3(-0.00f, 1.47f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(60.65f, 1.94f, 27.61f), vec3(150.35f, 62.94f, -7.13f), vec3(0.00f, 1.56f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(26.92f, 1.94f, 27.48f), vec3(153.56f, 62.94f, -46.31f), vec3(0.00f, 1.32f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(153.52f, 1.94f, 27.23f), vec3(-141.18f, 33.51f, 178.11f), vec3(0.00f, -0.00f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(153.52f, 1.94f, 26.13f), vec3(-55.98f, 33.51f, 299.76f), vec3(0.00f, -0.00f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(123.90f, 1.94f, 26.73f), vec3(153.10f, 33.51f, 299.47f), vec3(0.00f, -0.00f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(153.52f, 1.94f, 27.36f), vec3(284.25f, 33.51f, 378.63f), vec3(0.00f, -1.06f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(113.06f, 1.94f, 27.20f), vec3(414.65f, 33.51f, 405.02f), vec3(0.00f, 0.89f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(448.08f, 1.94f, 27.47f), vec3(9.94f, 1.97f, 59.17f), vec3(-0.00f, 0.00f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(430.10f, 1.94f, 25.48f), vec3(-164.97f, 33.51f, -0.47f), vec3(0.00f, -0.00f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(127.14f, 1.94f, 29.08f), vec3(148.83f, 62.94f, 69.85f), vec3(0.00f, -1.56f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(116.78f, 1.94f, 27.44f), vec3(465.63f, 33.51f, 32.92f), vec3(0.00f, 1.57f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(34.60f, 1.94f, 26.64f), vec3(143.68f, 33.51f, 40.62f), vec3(0.00f, -1.16f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(34.60f, 1.94f, 26.64f), vec3(144.88f, 33.51f, 78.32f), vec3(-0.00f, 1.04f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(30.19f, 1.94f, 25.68f), vec3(103.60f, 33.51f, 106.42f), vec3(-0.00f, 0.33f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(41.87f, 1.94f, 25.91f), vec3(-33.03f, 33.51f, 152.58f), vec3(-0.00f, 1.01f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(15.16f, 1.94f, 25.91f), vec3(-18.41f, 33.51f, 130.90f), vec3(-0.00f, 0.94f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(15.16f, 1.94f, 25.91f), vec3(-10.34f, 33.51f, 122.99f), vec3(-0.00f, 0.70f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(15.16f, 1.94f, 25.91f), vec3(-7.82f, 33.51f, 121.29f), vec3(-0.00f, 0.47f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(15.16f, 1.94f, 25.91f), vec3(-1.92f, 33.51f, 121.13f), vec3(-0.00f, 0.36f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(15.16f, 1.94f, 25.91f), vec3(-51.74f, 33.51f, 174.05f), vec3(-0.00f, 0.47f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(15.16f, 1.94f, 25.91f), vec3(-61.60f, 33.51f, 177.48f), vec3(-0.00f, 0.20f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(15.16f, 1.94f, 25.91f), vec3(-48.05f, 33.51f, 171.15f), vec3(-0.00f, 0.64f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(15.16f, 1.94f, 25.91f), vec3(-43.47f, 33.51f, 167.54f), vec3(-0.00f, 0.86f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(15.16f, 1.94f, 25.91f), vec3(-221.33f, 33.51f, 178.84f), vec3(-0.00f, 0.20f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(15.16f, 1.94f, 25.91f), vec3(-235.67f, 33.51f, 184.83f), vec3(-0.00f, 0.59f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(15.16f, 1.94f, 25.91f), vec3(-240.42f, 33.51f, 191.25f), vec3(-0.00f, 1.13f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(15.16f, 1.94f, 25.91f), vec3(-243.33f, 33.51f, 200.13f), vec3(0.00f, -1.51f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(15.16f, 1.94f, 25.91f), vec3(-242.27f, 33.51f, 212.72f), vec3(0.00f, -1.40f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(15.16f, 1.94f, 25.91f), vec3(-239.63f, 33.51f, 223.89f), vec3(0.00f, -1.22f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(15.16f, 1.94f, 25.91f), vec3(-233.91f, 33.51f, 235.15f), vec3(0.00f, -0.97f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(15.16f, 1.94f, 25.91f), vec3(-227.84f, 33.51f, 241.40f), vec3(0.00f, -0.81f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(15.16f, 1.94f, 25.91f), vec3(-229.79f, 33.51f, 180.85f), vec3(-0.00f, 0.29f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(50.45f, 1.94f, 25.91f), vec3(-205.52f, 33.51f, 260.65f), vec3(0.00f, -0.70f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(50.02f, 1.94f, 25.91f), vec3(-170.07f, 33.51f, 285.85f), vec3(0.00f, -0.55f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(15.16f, 1.94f, 25.91f), vec3(-151.08f, 33.51f, 297.24f), vec3(0.00f, -0.33f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(15.16f, 1.94f, 25.91f), vec3(-138.71f, 33.51f, 298.88f), vec3(0.00f, -0.10f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(15.16f, 1.94f, 26.44f), vec3(219.90f, 33.51f, 299.61f), vec3(0.00f, -0.03f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(15.16f, 1.94f, 26.44f), vec3(227.75f, 33.51f, 300.49f), vec3(0.00f, -0.39f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(15.16f, 1.94f, 26.44f), vec3(234.13f, 33.51f, 303.27f), vec3(0.00f, -0.55f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(15.16f, 1.94f, 26.44f), vec3(239.99f, 33.51f, 306.86f), vec3(0.00f, -0.60f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(15.16f, 1.94f, 26.44f), vec3(244.76f, 33.51f, 311.04f), vec3(0.00f, -0.82f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(15.16f, 1.94f, 26.44f), vec3(322.73f, 33.51f, 446.79f), vec3(0.00f, -0.87f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(15.16f, 1.94f, 26.44f), vec3(331.88f, 33.51f, 456.38f), vec3(0.00f, -0.83f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(22.29f, 1.94f, 26.44f), vec3(342.44f, 33.51f, 464.21f), vec3(0.00f, -0.44f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(24.44f, 1.94f, 26.44f), vec3(355.28f, 33.51f, 466.32f), vec3(0.00f, 0.24f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(20.11f, 1.94f, 26.44f), vec3(366.63f, 33.51f, 461.48f), vec3(0.00f, 0.59f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(15.16f, 1.94f, 26.44f), vec3(376.40f, 33.51f, 452.07f), vec3(0.00f, 0.90f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(61.11f, 1.94f, 27.20f), vec3(463.78f, 33.51f, 342.76f), vec3(0.00f, 0.94f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(61.11f, 1.94f, 26.87f), vec3(492.85f, 33.51f, 297.43f), vec3(0.00f, 1.14f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(30.42f, 1.94f, 26.87f), vec3(506.38f, 33.51f, 259.11f), vec3(0.00f, 1.41f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(30.42f, 1.94f, 26.87f), vec3(507.45f, 33.51f, 232.36f), vec3(-0.00f, -1.44f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(30.42f, 1.94f, 26.87f), vec3(500.15f, 33.51f, 206.97f), vec3(-0.00f, -1.14f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(36.75f, 1.94f, 26.87f), vec3(485.05f, 33.51f, 181.37f), vec3(-0.00f, -0.99f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(30.42f, 1.94f, 26.87f), vec3(475.06f, 33.51f, 161.51f), vec3(-0.00f, -1.26f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(30.42f, 1.94f, 26.87f), vec3(468.52f, 33.51f, 135.82f), vec3(-0.00f, -1.42f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(30.42f, 1.94f, 26.87f), vec3(465.64f, 33.51f, 110.27f), vec3(-0.00f, -1.50f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(30.42f, 1.94f, 26.87f), vec3(465.03f, 33.51f, 91.27f), vec3(0.00f, 1.57f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(30.42f, 1.94f, 26.87f), vec3(464.84f, 33.51f, -34.39f), vec3(-0.00f, -1.48f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(30.42f, 1.94f, 26.87f), vec3(461.19f, 33.51f, -60.84f), vec3(-0.00f, -1.37f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(30.42f, 1.94f, 26.87f), vec3(456.08f, 33.51f, -83.46f), vec3(-0.00f, -1.26f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(30.42f, 1.94f, 26.87f), vec3(448.42f, 33.51f, -102.44f), vec3(-0.00f, -1.10f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(30.42f, 1.94f, 26.87f), vec3(434.01f, 33.51f, -124.33f), vec3(-0.00f, -0.90f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(30.42f, 1.94f, 26.87f), vec3(418.32f, 33.51f, -141.48f), vec3(-0.00f, -0.73f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(30.42f, 1.94f, 26.87f), vec3(398.95f, 33.51f, -155.36f), vec3(-0.00f, -0.48f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(45.38f, 1.94f, 26.87f), vec3(374.72f, 33.51f, -164.83f), vec3(-0.00f, -0.36f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(120.74f, 1.94f, 26.87f), vec3(304.39f, 33.51f, -174.27f), vec3(-0.00f, -0.08f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(83.63f, 1.94f, 26.77f), vec3(141.47f, 33.51f, -212.71f), vec3(-0.00f, -0.41f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(83.63f, 1.94f, 26.77f), vec3(74.12f, 33.51f, -247.53f), vec3(-0.00f, -0.55f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(83.63f, 1.94f, 26.77f), vec3(5.88f, 33.51f, -292.17f), vec3(-0.00f, -0.61f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(83.63f, 1.94f, 26.77f), vec3(-34.74f, 33.51f, -319.74f), vec3(-0.00f, -0.56f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(36.09f, 1.94f, 26.00f), vec3(-80.30f, 33.51f, -345.51f), vec3(-0.00f, -0.32f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(36.09f, 1.94f, 26.00f), vec3(-108.81f, 33.51f, -350.07f), vec3(-0.00f, 0.07f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(41.49f, 1.94f, 26.00f), vec3(-134.91f, 33.51f, -339.81f), vec3(-0.00f, 0.52f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(73.12f, 1.94f, 26.00f), vec3(-180.88f, 33.51f, -309.86f), vec3(-0.00f, 0.64f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(36.09f, 1.94f, 26.00f), vec3(-219.55f, 33.51f, -278.19f), vec3(-0.00f, 0.76f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(36.09f, 1.94f, 26.00f), vec3(-232.14f, 33.51f, -260.49f), vec3(-0.00f, 1.03f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(36.09f, 1.94f, 26.00f), vec3(-242.54f, 33.51f, -236.05f), vec3(-0.00f, 1.32f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(36.09f, 1.94f, 26.00f), vec3(-246.18f, 33.51f, -203.57f), vec3(-0.00f, 1.55f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(36.82f, 1.94f, 26.00f), vec3(-244.07f, 33.51f, -178.78f), vec3(0.00f, -1.44f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(22.93f, 1.94f, 26.00f), vec3(-237.43f, 33.51f, -159.06f), vec3(0.00f, -0.92f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(22.93f, 1.94f, 26.00f), vec3(-224.84f, 33.51f, -145.01f), vec3(0.00f, -0.66f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(27.03f, 1.94f, 26.00f), vec3(-207.99f, 33.51f, -136.38f), vec3(0.00f, -0.25f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(22.93f, 1.94f, 26.00f), vec3(-187.70f, 33.51f, -133.18f), vec3(0.00f, 0.02f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(49.63f, 1.94f, 27.66f), vec3(-44.66f, 62.94f, -134.10f), vec3(0.00f, 0.02f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(18.88f, 1.94f, 27.66f), vec3(-12.91f, 62.94f, -133.61f), vec3(0.00f, -0.14f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(18.88f, 1.94f, 27.66f), vec3(0.29f, 62.94f, -129.48f), vec3(0.00f, -0.46f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(18.88f, 1.94f, 27.66f), vec3(13.58f, 62.94f, -120.77f), vec3(0.00f, -0.71f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(18.88f, 1.94f, 27.66f), vec3(21.32f, 62.94f, -110.91f), vec3(0.00f, -1.01f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(18.88f, 1.94f, 27.66f), vec3(24.66f, 62.94f, -103.52f), vec3(0.00f, -1.19f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(50.95f, 1.94f, 26.67f), vec3(31.65f, 62.94f, -80.11f), vec3(0.00f, -1.32f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(27.52f, 1.94f, 26.67f), vec3(37.74f, 62.94f, -53.20f), vec3(0.00f, -1.41f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(32.58f, 1.94f, 26.67f), vec3(38.50f, 62.94f, -33.74f), vec3(-0.00f, 1.50f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(27.54f, 1.94f, 27.36f), vec3(-2.21f, 62.94f, 92.67f), vec3(-0.00f, 1.25f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(34.75f, 1.94f, 27.36f), vec3(-10.57f, 62.94f, 177.96f), vec3(0.00f, -1.41f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(27.54f, 1.94f, 27.36f), vec3(-4.49f, 62.94f, 200.62f), vec3(0.00f, -1.22f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(27.54f, 1.94f, 27.36f), vec3(6.76f, 62.94f, 218.86f), vec3(0.00f, -0.93f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(27.54f, 1.94f, 27.36f), vec3(22.44f, 62.94f, 231.23f), vec3(0.00f, -0.43f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(27.54f, 1.94f, 27.36f), vec3(42.94f, 62.94f, 239.38f), vec3(0.00f, -0.33f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(27.54f, 1.94f, 27.36f), vec3(67.42f, 62.94f, 244.86f), vec3(0.00f, -0.15f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(27.54f, 1.94f, 27.36f), vec3(89.77f, 62.94f, 244.25f), vec3(0.00f, 0.21f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(31.59f, 1.94f, 27.36f), vec3(113.48f, 62.94f, 235.43f), vec3(0.00f, 0.49f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(27.54f, 1.94f, 27.36f), vec3(129.60f, 62.94f, 220.68f), vec3(0.00f, 0.89f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(27.54f, 1.94f, 27.36f), vec3(140.09f, 62.94f, 203.05f), vec3(0.00f, 1.15f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(27.54f, 1.94f, 27.36f), vec3(145.87f, 62.94f, 183.44f), vec3(0.00f, 1.35f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(27.54f, 1.94f, 27.36f), vec3(149.36f, 62.94f, 163.82f), vec3(0.00f, 1.50f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(27.54f, 1.94f, 27.36f), vec3(149.36f, 62.94f, 140.77f), vec3(-0.00f, -1.57f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(26.92f, 1.94f, 27.48f), vec3(161.22f, 62.94f, -65.83f), vec3(0.00f, 1.09f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(26.92f, 1.94f, 27.48f), vec3(170.35f, 62.94f, -80.61f), vec3(0.00f, 0.94f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(26.92f, 1.94f, 27.48f), vec3(186.95f, 62.94f, -95.93f), vec3(0.00f, 0.58f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(26.92f, 1.94f, 27.48f), vec3(207.20f, 62.94f, -104.87f), vec3(0.00f, 0.34f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(26.92f, 1.94f, 27.48f), vec3(224.35f, 62.94f, -107.06f), vec3(0.00f, 0.06f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(32.03f, 1.94f, 27.48f), vec3(250.80f, 62.94f, -106.88f), vec3(0.00f, -0.06f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(26.92f, 1.94f, 27.48f), vec3(277.25f, 62.94f, -103.05f), vec3(0.00f, -0.25f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(26.92f, 1.94f, 27.48f), vec3(302.61f, 62.94f, -96.85f), vec3(0.00f, -0.25f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(26.92f, 1.94f, 27.48f), vec3(321.59f, 62.94f, -90.46f), vec3(0.00f, -0.35f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(37.15f, 1.94f, 27.48f), vec3(346.95f, 62.94f, -78.60f), vec3(0.00f, -0.51f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(26.92f, 1.94f, 27.48f), vec3(370.12f, 62.94f, -62.55f), vec3(0.00f, -0.68f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(36.56f, 1.94f, 27.48f), vec3(388.72f, 62.94f, -43.50f), vec3(0.00f, -0.85f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(26.92f, 1.94f, 27.48f), vec3(400.11f, 62.94f, -26.64f), vec3(0.00f, -1.08f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(26.92f, 1.94f, 27.48f), vec3(409.96f, 62.94f, -3.44f), vec3(0.00f, -1.27f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(26.92f, 1.94f, 27.48f), vec3(411.71f, 62.94f, 17.14f), vec3(-0.00f, 1.50f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(26.92f, 1.94f, 27.48f), vec3(406.46f, 62.94f, 33.78f), vec3(-0.00f, 1.15f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(34.61f, 1.94f, 27.48f), vec3(392.67f, 62.94f, 49.76f), vec3(-0.00f, 0.55f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(26.92f, 1.94f, 27.48f), vec3(372.31f, 62.94f, 59.17f), vec3(-0.00f, 0.29f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(26.92f, 1.94f, 27.48f), vec3(365.13f, 62.94f, 60.36f), vec3(-0.00f, 0.00f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(24.68f, 1.94f, 27.47f), vec3(-209.35f, 1.97f, 59.90f), vec3(0.00f, 0.22f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(69.29f, 1.94f, 27.47f), vec3(-246.70f, 1.97f, 69.25f), vec3(0.00f, 0.24f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(69.29f, 1.94f, 27.47f), vec3(-299.06f, 1.97f, 86.40f), vec3(0.00f, 0.39f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(18.61f, 1.94f, 27.47f), vec3(-327.72f, 1.97f, 99.18f), vec3(0.00f, 0.88f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(18.61f, 1.94f, 27.47f), vec3(-331.14f, 1.97f, 111.18f), vec3(0.00f, 1.34f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(18.61f, 1.94f, 27.47f), vec3(-331.45f, 1.97f, 123.49f), vec3(-0.00f, -1.55f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(18.61f, 1.94f, 27.47f), vec3(-331.60f, 1.97f, 138.09f), vec3(0.00f, 1.47f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(18.61f, 1.94f, 27.47f), vec3(-334.79f, 1.97f, 153.29f), vec3(0.00f, 1.31f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(18.61f, 1.94f, 27.47f), vec3(-339.50f, 1.97f, 169.26f), vec3(0.00f, 1.23f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(18.61f, 1.94f, 27.47f), vec3(-343.30f, 1.97f, 180.96f), vec3(0.00f, 1.23f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(18.61f, 1.94f, 27.47f), vec3(-349.08f, 1.97f, 192.06f), vec3(0.00f, 1.03f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(18.61f, 1.94f, 27.47f), vec3(-357.90f, 1.97f, 200.27f), vec3(0.00f, 0.65f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(18.61f, 1.94f, 27.47f), vec3(-369.15f, 1.97f, 205.74f), vec3(0.00f, 0.34f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(18.61f, 1.94f, 27.47f), vec3(-382.22f, 1.97f, 207.87f), vec3(0.00f, 0.04f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(18.61f, 1.94f, 27.47f), vec3(-396.82f, 1.97f, 208.33f), vec3(0.00f, 0.03f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(70.63f, 1.94f, 27.47f), vec3(-439.99f, 1.97f, 208.06f), vec3(0.00f, -0.00f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(70.63f, 1.94f, 27.47f), vec3(-504.94f, 1.97f, 205.33f), vec3(0.00f, -0.07f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(70.63f, 1.94f, 27.47f), vec3(-551.28f, 1.97f, 200.95f), vec3(0.00f, -0.16f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(32.86f, 1.94f, 27.47f), vec3(-597.80f, 1.97f, 190.19f), vec3(0.00f, -0.42f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(25.69f, 1.94f, 27.47f), vec3(-616.41f, 1.97f, 180.70f), vec3(0.00f, -0.58f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(46.66f, 1.94f, 27.47f), vec3(-633.56f, 1.97f, 169.02f), vec3(0.00f, -0.67f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(25.69f, 1.94f, 27.47f), vec3(-652.53f, 1.97f, 150.96f), vec3(0.00f, -0.86f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(25.69f, 1.94f, 27.47f), vec3(-665.48f, 1.97f, 132.72f), vec3(0.00f, -1.08f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(30.05f, 1.94f, 27.47f), vec3(-675.70f, 1.97f, 110.28f), vec3(0.00f, -1.22f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(25.69f, 1.94f, 27.47f), vec3(-681.17f, 1.97f, 88.38f), vec3(0.00f, -1.44f, 0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(25.69f, 1.94f, 27.47f), vec3(-681.54f, 1.97f, 69.05f), vec3(-0.00f, 1.47f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(25.69f, 1.94f, 27.47f), vec3(-676.98f, 1.97f, 47.52f), vec3(-0.00f, 1.28f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(25.69f, 1.94f, 27.47f), vec3(-670.27f, 1.97f, 32.54f), vec3(-0.00f, 1.13f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(25.69f, 1.94f, 27.47f), vec3(-657.82f, 1.97f, 17.04f), vec3(-0.00f, 0.76f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(25.69f, 1.94f, 27.47f), vec3(-642.13f, 1.97f, 7.10f), vec3(-0.00f, 0.53f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(25.69f, 1.94f, 27.47f), vec3(-630.45f, 1.97f, 2.74f), vec3(-0.00f, 0.32f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(25.69f, 1.94f, 27.47f), vec3(-616.21f, 1.97f, -0.77f), vec3(-0.00f, 0.25f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(25.69f, 1.94f, 27.47f), vec3(-600.42f, 1.97f, -1.90f), vec3(-0.00f, 0.08f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));
	CreateCube(vec3(103.22f, 1.94f, 27.47f), vec3(-566.24f, 1.97f, -1.67f), vec3(-0.00f, -0.01f, -0.00f), Color(1.00f, 1.00f, 1.00f, 0.0f));




	faryAudio = App->audio->LoadFx("Assets/TorrenteFary.wav");
	logo = App->renderer3D->LoadTexture("Assets/Bugatti_logo.png");
	logo2 = App->renderer3D->LoadTexture("Assets/logo2.png");
	road = App->renderer3D->LoadTexture("Assets/pistanivelmedio2.png");
	road2 = App->renderer3D->LoadTexture("Assets/arriba.png");
	road3 = App->renderer3D->LoadTexture("Assets/imagenotaa3.png");
	road4 = App->renderer3D->LoadTexture("Assets/mandanga.png");
	road5 = App->renderer3D->LoadTexture("Assets/rampa2.png");
	road6 = App->renderer3D->LoadTexture("Assets/rampa3.png");
	road7 = App->renderer3D->LoadTexture("Assets/rampa4.png");
	arrow = App->renderer3D->LoadTexture("Assets/arrow.png");
	win1 = App->renderer3D->LoadTexture("Assets/win1.png");
	win2 = App->renderer3D->LoadTexture("Assets/win2.png");
	win3 = App->renderer3D->LoadTexture("Assets/win3.png");
	lose1 = App->renderer3D->LoadTexture("Assets/lose1.png");

	startOne = App->audio->LoadFx("Assets/startone.wav");
	startTwo = App->audio->LoadFx("Assets/starttwo.wav");

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
	//Plane p(0, 1, 0, 0);
	//p.axis = true;
	//p.Render();
	//p.wire = false;

	if (fary)
	{
		App->audio->PlayFx(faryAudio);
		App->audio->PlayMusic("Assets/song2.ogg", 0);
		fary = false;
	}
	angle++;
	btQuaternion rotationQuaternion = btQuaternion(btVector3(0, 1, 0), angle * DEGTORAD);
	for (int i = 1; i < 10; i++)
	{
		coin[i].physbody->SetRotation(rotationQuaternion);
		coin[i].SetRotation(angle, vec3(0, 1, 0));
		coin[i].Render();
	}

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

	for (int i = 1; i < 10; i++)
	{
		float radius = 0.3f;
		float logoAngle = angle - 90;

		float logoPosX = coin[i].physbody->GetPos().getX() - radius * sin(logoAngle * DEGTORAD);
		float logoPosY = coin[i].physbody->GetPos().getY();
		float logoPosZ = coin[i].physbody->GetPos().getZ() - radius * cos(logoAngle * DEGTORAD);

		App->renderer3D->DrawTexture(logo2, { logoPosX, logoPosY, logoPosZ }, 1.0f, logoAngle, vec3(0, 1, 0));

		float logoAngleOtherSide = angle + 90;

		float logoPosXOtherSide = coin[i].physbody->GetPos().getX() - radius * sin(logoAngleOtherSide * DEGTORAD);
		float logoPosZOtherSide = coin[i].physbody->GetPos().getZ() - radius * cos(logoAngleOtherSide * DEGTORAD);

		App->renderer3D->DrawTexture(logo2, { logoPosXOtherSide, logoPosY, logoPosZOtherSide }, 1.0f, logoAngleOtherSide, vec3(0, 1, 0));
	}

	if (loseCount == 3)
	{
		lose = true;
	}

	if (win)
	{
		wintimer++;
		float time = 0.5f;

		if (wintimer < 50 * time) {
			WinIndex = 1;
		}
		else if (wintimer > 50 * time && wintimer < 100 * time) {
			WinIndex = 2;
		}
		else if (wintimer > 100 * time && wintimer < 150 * time) {
			WinIndex = 3;
		}
		if (wintimer == 150 * time) {
			wintimer = 0;
		}

		if (WinIndex == 1) App->renderer3D->DrawTexture(win1, { 0, -1000, 2 }, 300, 0, vec3(0, 0, 0));
		if (WinIndex == 2) App->renderer3D->DrawTexture(win2, { 0, -1000, 2 }, 300, 0, vec3(0, 0, 0));
		if (WinIndex == 3) App->renderer3D->DrawTexture(win3, { 0, -1000, 2 }, 300, 0, vec3(0, 0, 0));
	}

	if (lose)
	{
		loseCount = 5;
		App->renderer3D->DrawTexture(lose1, { 0, -1000, 2 }, 300, 0, vec3(0, 0, 0));
		if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
		{
			App->player->Respawn(App->network->clientIndex);
			lose = false;
			loseCount = 0;
		}
	}

	//App->renderer3D->DrawTexture(win1, { -500, 2.19f, 122.0f }, 50, 0, vec3(0, 0, 0));

	//suelo
	App->renderer3D->DrawTexture(road3, { -202, 3.1f, 104 }, 985.0f, 90, vec3(1, 0, 0));


	btQuaternion quat1;
	quat1.setEulerZYX(24 * DEGTORAD, 2 * DEGTORAD, 90 * DEGTORAD);

	float angle1 = quat1.getAngle() * RADTODEG;
	btVector3 axis1 = quat1.getAxis();

	App->renderer3D->DrawTexture(road4, { -155, 48, -131 }, 80.0f, angle1, vec3(axis1.getX(), axis1.getY(), axis1.getZ()));

	btQuaternion quat2;
	quat2.setEulerZYX(13 * DEGTORAD, 0 * DEGTORAD, 90 * DEGTORAD);

	float angle2 = quat2.getAngle() * RADTODEG;
	btVector3 axis2 = quat2.getAxis();

	App->renderer3D->DrawTexture(road5, { -448, 22, 0 }, 140.0f, angle2, vec3(axis2.getX(), axis2.getY(), axis2.getZ()));

	btQuaternion quat3;
	quat3.setEulerZYX(24 * DEGTORAD, 180 * DEGTORAD, 90 * DEGTORAD);

	float angle3 = quat3.getAngle() * RADTODEG;
	btVector3 axis3 = quat3.getAxis();

	App->renderer3D->DrawTexture(road6, { 290, 32, 60 }, 140.0f, angle3, vec3(axis3.getX(), axis3.getY(), axis3.getZ()));

	btQuaternion quat4;
	quat4.setEulerZYX(12 * DEGTORAD, 180 * DEGTORAD, 90 * DEGTORAD);

	float angle4 = quat4.getAngle() * RADTODEG;
	btVector3 axis4 = quat4.getAxis();

	App->renderer3D->DrawTexture(road7, { 20, 37.6, 298 }, 26, angle4, vec3(axis4.getX(), axis4.getY(), axis4.getZ()));

	//central
	App->renderer3D->DrawTexture(road, { 72, 34.6f, 59.0f }, 890.0f, 90, vec3(1, 0, 0));

	//arriba
	App->renderer3D->DrawTexture(road2, { 152, 64.10f, 55.0f }, 550.0f, 90, vec3(1, 0, 0));

	//App->renderer3D->DrawTexture(arrow, { 0, 0.1, 100 }, 5.0f, 90, vec3(1, 0, 0));

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

	if (lightIndex == 0)
	{
		for (int i = 0; i < 5; i++)
		{
			light[i].color = Color(0.1f, 0.1f, 0.1f);
		}
	}
	if (lightIndex < 6)lightTimer++;
	if (lightTimer > 85 && lightIndex < 5)
	{
		App->audio->PlayFx(startOne);
		lightTimer = 0;
		light[lightIndex].color = Red;
		lightIndex++;
	}
	else if (lightTimer > 85 && lightIndex == 5)
	{
		App->audio->PlayFx(startTwo);
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



