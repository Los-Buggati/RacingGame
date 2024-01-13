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

	CreateCube(vec3(2, 5, 1), vec3(0, 7, 10), vec3(0, 0, 0), Black);
	light[0] = CreateCylinder(vec2(0.5f, 0.2f), vec3(0, 7, 9), vec3(0, 90, 0), Color(0.1f, 0.1f, 0.1f));

	CreateCube(vec3(2, 5, 1), vec3(2, 7, 10), vec3(0, 0, 0), Black);
	light[1] = CreateCylinder(vec2(0.5f, 0.2f), vec3(2, 7, 9), vec3(0, 90, 0), Color(0.1f, 0.1f, 0.1f));

	CreateCube(vec3(2, 5, 1), vec3(4, 7, 10), vec3(0, 0, 0), Black);
	light[2] = CreateCylinder(vec2(0.5f, 0.2f), vec3(4, 7, 9), vec3(0, 90, 0), Color(0.1f, 0.1f, 0.1f));

	CreateCube(vec3(2, 5, 1), vec3(6, 7, 10), vec3(0, 0, 0), Black);
	light[3] = CreateCylinder(vec2(0.5f, 0.2f), vec3(6, 7, 9), vec3(0, 90, 0), Color(0.1f, 0.1f, 0.1f));

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

	CreateCube(vec3(29.2993f, 1.4384f, 28.8395f), vec3(16.6206f, 38.2505f, 300.0313f), vec3(-0.0000f, 0.0000f, 0.4240f), Color(1.0000f, 1.0000f, 1.000f,0.0f));
	CreateCube(vec3(81.2752f, 1.4384f, 28.8395f), vec3(-173.0065f, 35.8515f, -130.9064f), vec3(-0.0000f, 0.0000f, 0.4240f), Color(1.0000f, 1.0000f, 1.000f,0.0f));
	CreateCube(vec3(146.3881f, 1.4384f, 28.8395f), vec3(297.0189f, 37.8682f, 62.6875f), vec3(-0.0000f, 0.0000f, 0.4240f), Color(1.0000f, 1.0000f, 1.000f,0.0f));
	CreateCube(vec3(155.0004f, 1.4384f, 28.8395f), vec3(-428.2372f, 21.6459f, -0.5410f), vec3(-0.0000f, 0.0000f, 0.2163f), Color(1.0000f, 1.0000f, 1.000f,0.0f));
	CreateCube(vec3(64.9733f, 1.9449f, 29.8250f), vec3(-193.4967f, 1.1590f, 60.2814f), vec3(-0.0000f, 0.0000f, -0.0000f), Color(1.0000f, 1.0000f, 1.000f,0.0f));
	CreateCube(vec3(64.9733f, 1.9449f, 29.8250f), vec3(-233.8489f, 1.1590f, 67.2170f), vec3(-0.0000f, 0.2054f, -0.0000f), Color(1.0000f, 1.0000f, 1.000f,0.0f));
	CreateCube(vec3(64.9733f, 1.9449f, 29.8250f), vec3(-285.8654f, 1.1590f, 82.3490f), vec3(-0.0000f, 0.3468f, -0.0000f), Color(1.0000f, 1.0000f, 1.000f,0.0f));
	CreateCube(vec3(41.2245f, 1.9449f, 29.8250f), vec3(-320.2278f, 1.1590f, 99.3726f), vec3(-0.0000f, 1.0789f, -0.0000f), Color(1.0000f, 1.0000f, 1.000f,0.0f));
	CreateCube(vec3(64.9733f, 1.9449f, 29.8250f), vec3(-331.8921f, 1.1590f, 148.8671f), vec3(-0.0000f, 1.5146f, -0.0000f), Color(1.0000f, 1.0000f, 1.000f,0.0f));
	CreateCube(vec3(64.9733f, 1.9449f, 29.8250f), vec3(-342.6106f, 1.1590f, 180.0770f), vec3(-0.0000f, 1.0284f, -0.0000f), Color(1.0000f, 1.0000f, 1.000f,0.0f));
	CreateCube(vec3(64.9733f, 1.9449f, 29.8250f), vec3(-380.1255f, 1.1590f, 209.3953f), vec3(-0.0000f, 0.0282f, -0.0000f), Color(1.0000f, 1.0000f, 1.000f,0.0f));
	CreateCube(vec3(64.9733f, 1.9449f, 29.8250f), vec3(-437.8165f, 1.1590f, 209.3953f), vec3(-0.0000f, -0.0344f, -0.0000f), Color(1.0000f, 1.0000f, 1.000f,0.0f));
	CreateCube(vec3(169.4085f, 1.9449f, 31.1421f), vec3(-542.1647f, 1.1590f, 201.5140f), vec3(-0.0000f, -0.1241f, -0.0000f), Color(1.0000f, 1.0000f, 1.000f,0.0f));
	CreateCube(vec3(91.8727f, 1.9449f, 31.1421f), vec3(-635.7944f, 1.1590f, 163.6839f), vec3(-0.0000f, -0.7813f, -0.0000f), Color(1.0000f, 1.0000f, 1.000f,0.0f));
	CreateCube(vec3(57.2029f, 1.9449f, 31.1421f), vec3(-672.9940f, 1.1590f, 109.7759f), vec3(-0.0000f, -1.2251f, -0.0000f), Color(1.0000f, 1.0000f, 1.000f,0.0f));
	CreateCube(vec3(57.2029f, 1.9449f, 31.1421f), vec3(-677.0923f, 1.1590f, 62.8034f), vec3(0.0000f, 1.3703f, 0.0000f), Color(1.0000f, 1.0000f, 1.000f,0.0f));
	CreateCube(vec3(57.2029f, 1.9449f, 31.1421f), vec3(-658.1772f, 1.1590f, 21.8208f), vec3(0.0000f, 0.7962f, 0.0000f), Color(1.0000f, 1.0000f, 1.000f,0.0f));
	CreateCube(vec3(57.2029f, 1.9449f, 31.1421f), vec3(-618.7708f, 1.1590f, 4.4819f), vec3(0.0000f, 0.2350f, 0.0000f), Color(1.0000f, 1.0000f, 1.000f,0.0f));
	CreateCube(vec3(57.2029f, 1.9449f, 31.1421f), vec3(-560.4493f, 1.1590f, -1.8231f), vec3(0.0000f, 0.0176f, 0.0000f), Color(1.0000f, 1.0000f, 1.000f,0.0f));
	CreateCube(vec3(57.2029f, 1.9449f, 31.1421f), vec3(56.4103f, 32.6951f, 3.5709f), vec3(0.0000f, -0.1214f, 0.0000f), Color(1.0000f, 1.0000f, 1.000f,0.0f));
	CreateCube(vec3(57.2029f, 1.9449f, 31.1421f), vec3(95.1782f, 32.6951f, 11.7805f), vec3(0.0000f, -0.2378f, 0.0000f), Color(1.0000f, 1.0000f, 1.000f,0.0f));
	CreateCube(vec3(57.2029f, 1.9449f, 31.1421f), vec3(122.5438f, 32.6951f, 23.7910f), vec3(0.0000f, -0.5043f, 0.0000f), Color(1.0000f, 1.0000f, 1.000f,0.0f));
	CreateCube(vec3(57.2029f, 1.9449f, 31.1421f), vec3(147.1728f, 32.6951f, 47.8119f), vec3(0.0000f, -1.1666f, 0.0000f), Color(1.0000f, 1.0000f, 1.000f,0.0f));
	CreateCube(vec3(57.2029f, 1.9449f, 31.1421f), vec3(147.0207f, 32.6951f, 62.2548f), vec3(0.0000f, -1.5197f, 0.0000f), Color(1.0000f, 1.0000f, 1.000f,0.0f));
	CreateCube(vec3(57.2029f, 1.9449f, 31.1421f), vec3(137.8989f, 32.6951f, 89.1643f), vec3(-0.0000f, 1.0612f, -0.0000f), Color(1.0000f, 1.0000f, 1.000f,0.0f));
	CreateCube(vec3(57.2029f, 1.9449f, 31.1421f), vec3(126.4966f, 32.6951f, 95.7016f), vec3(-0.0000f, 0.5883f, -0.0000f), Color(1.0000f, 1.0000f, 1.000f,0.0f));
	CreateCube(vec3(57.2029f, 1.9449f, 31.1421f), vec3(96.2424f, 32.6951f, 108.4722f), vec3(-0.0000f, 0.2953f, -0.0000f), Color(1.0000f, 1.0000f, 1.000f,0.0f));
	CreateCube(vec3(57.2029f, 1.9449f, 31.1421f), vec3(55.4981f, 32.6951f, 117.1380f), vec3(-0.0000f, 0.1392f, -0.0000f), Color(1.0000f, 1.0000f, 1.000f,0.0f));
	CreateCube(vec3(57.2029f, 1.9449f, 31.1421f), vec3(21.8993f, 32.6951f, 119.8745f), vec3(-0.0000f, -0.0043f, -0.0000f), Color(1.0000f, 1.0000f, 1.000f,0.0f));
	CreateCube(vec3(41.7430f, 1.9449f, 31.1421f), vec3(-5.6183f, 32.6951f, 122.6111f), vec3(-0.0000f, 0.5822f, -0.0000f), Color(1.0000f, 1.0000f, 1.000f,0.0f));
	CreateCube(vec3(41.7430f, 1.9449f, 31.1421f), vec3(-26.2945f, 32.6951f, 141.9190f), vec3(-0.0000f, 0.9777f, -0.0000f), Color(1.0000f, 1.0000f, 1.000f,0.0f));
	CreateCube(vec3(41.7430f, 1.9449f, 31.1421f), vec3(-41.0415f, 32.6951f, 164.1156f), vec3(-0.0000f, 0.9777f, -0.0000f), Color(1.0000f, 1.0000f, 1.000f,0.0f));
	CreateCube(vec3(41.7430f, 1.9449f, 31.1421f), vec3(-53.3560f, 32.6951f, 176.1260f), vec3(-0.0000f, 0.3941f, -0.0000f), Color(1.0000f, 1.0000f, 1.000f,0.0f));
	CreateCube(vec3(41.7430f, 1.9449f, 31.1421f), vec3(-53.3560f, 32.6951f, 176.1260f), vec3(-0.0000f, 0.3941f, -0.0000f), Color(1.0000f, 1.0000f, 1.000f,0.0f));
	CreateCube(vec3(41.7430f, 1.9449f, 31.1421f), vec3(-228.6358f, 33.0211f, 181.8005f), vec3(-0.0000f, 0.3941f, -0.0000f), Color(1.0000f, 1.0000f, 1.000f,0.0f));
	CreateCube(vec3(41.7430f, 1.9449f, 31.1421f), vec3(-239.5820f, 33.0211f, 192.8987f), vec3(-0.0000f, 1.3114f, -0.0000f), Color(1.0000f, 1.0000f, 1.000f,0.0f));
	CreateCube(vec3(41.7430f, 1.9449f, 31.1421f), vec3(-241.4064f, 33.0211f, 216.0075f), vec3(-0.0000f, 1.5666f, -0.0000f), Color(1.0000f, 1.0000f, 1.000f,0.0f));
	CreateCube(vec3(41.7430f, 1.9449f, 31.1421f), vec3(-232.7406f, 33.0211f, 234.8593f), vec3(0.0000f, -0.9353f, 0.0000f), Color(1.0000f, 1.0000f, 1.000f,0.0f));
	CreateCube(vec3(106.6117f, 1.9449f, 31.1421f), vec3(-193.9727f, 33.0211f, 270.8906f), vec3(0.0000f, -0.6902f, 0.0000f), Color(1.0000f, 1.0000f, 1.000f,0.0f));
	CreateCube(vec3(41.7430f, 1.9449f, 31.1421f), vec3(-164.7828f, 33.0211f, 288.6783f), vec3(0.0000f, -0.4525f, 0.0000f), Color(1.0000f, 1.0000f, 1.000f,0.0f));
	CreateCube(vec3(41.7430f, 1.9449f, 31.1421f), vec3(-134.1669f, 33.0211f, 298.6142f), vec3(0.0000f, -0.0570f, 0.0000f), Color(1.0000f, 1.0000f, 1.000f,0.0f));
	CreateCube(vec3(41.7430f, 1.9449f, 31.1421f), vec3(208.8950f, 31.5315f, 299.2462f), vec3(0.0000f, 0.0295f, 0.0000f), Color(1.0000f, 1.0000f, 1.000f,0.0f));
	CreateCube(vec3(41.7430f, 1.9449f, 31.1421f), vec3(237.2676f, 31.5315f, 306.0556f), vec3(0.0000f, -0.5513f, 0.0000f), Color(1.0000f, 1.0000f, 1.000f,0.0f));
	CreateCube(vec3(41.7430f, 1.9449f, 31.1421f), vec3(255.8043f, 31.5315f, 325.7273f), vec3(0.0000f, -1.0435f, 0.0000f), Color(1.0000f, 1.0000f, 1.000f,0.0f));
	CreateCube(vec3(41.7430f, 1.9449f, 31.1421f), vec3(329.5731f, 31.5315f, 453.2149f), vec3(0.0000f, -0.7811f, 0.0000f), Color(1.0000f, 1.0000f, 1.000f,0.0f));
	CreateCube(vec3(41.7430f, 1.9449f, 31.1421f), vec3(351.8929f, 31.5315f, 464.9423f), vec3(0.0000f, -0.0319f, 0.0000f), Color(1.0000f, 1.0000f, 1.000f,0.0f));
	CreateCube(vec3(41.7430f, 1.9449f, 31.1421f), vec3(370.4297f, 31.5315f, 455.4847f), vec3(0.0000f, 0.6877f, 0.0000f), Color(1.0000f, 1.0000f, 1.000f,0.0f));
	CreateCube(vec3(41.7430f, 1.9449f, 31.1421f), vec3(486.5683f, 31.5315f, 303.0292f), vec3(0.0000f, 1.1375f, 0.0000f), Color(1.0000f, 1.0000f, 1.000f,0.0f));
	CreateCube(vec3(85.4021f, 1.9449f, 31.1421f), vec3(505.8617f, 31.5315f, 250.0670f), vec3(0.0000f, 1.2988f, 0.0000f), Color(1.0000f, 1.0000f, 1.000f,0.0f));
	CreateCube(vec3(56.6010f, 1.9449f, 31.1421f), vec3(503.5919f, 31.5315f, 221.6943f), vec3(-0.0000f, -1.4408f, -0.0000f), Color(1.0000f, 1.0000f, 1.000f,0.0f));
	CreateCube(vec3(56.6010f, 1.9449f, 31.1421f), vec3(492.2429f, 31.5315f, 194.0783f), vec3(-0.0000f, -0.9451f, -0.0000f), Color(1.0000f, 1.0000f, 1.000f,0.0f));
	CreateCube(vec3(56.6010f, 1.9449f, 31.1421f), vec3(468.4099f, 31.5315f, 152.8434f), vec3(-0.0000f, -1.2585f, -0.0000f), Color(1.0000f, 1.0000f, 1.000f,0.0f));
	CreateCube(vec3(56.6009f, 1.9449f, 31.1421f), vec3(462.7354f, 31.5186f, 111.2303f), vec3(-0.0000f, -1.5426f, -0.0000f), Color(1.0000f, 1.0000f, 1.000f,0.0f));
	CreateCube(vec3(56.6010f, 1.9449f, 31.1421f), vec3(444.7584f, 31.6097f, -97.4106f), vec3(-0.0000f, -1.1551f, -0.0000f), Color(1.0000f, 1.0000f, 1.000f,0.0f));
	CreateCube(vec3(56.6010f, 1.9449f, 31.1421f), vec3(460.0116f, 31.6097f, -48.9275f), vec3(-0.0000f, -1.4187f, -0.0000f), Color(1.0000f, 1.0000f, 1.000f,0.0f));
	CreateCube(vec3(56.6010f, 1.9449f, 31.1421f), vec3(463.2801f, 31.6097f, -17.3317f), vec3(-0.0000f, -1.5470f, -0.0000f), Color(1.0000f, 1.0000f, 1.000f,0.0f));
	CreateCube(vec3(56.6010f, 1.9449f, 31.1421f), vec3(420.2445f, 31.6097f, -136.6329f), vec3(-0.0000f, -0.6632f, -0.0000f), Color(1.0000f, 1.0000f, 1.000f,0.0f));
	CreateCube(vec3(56.6010f, 1.9449f, 31.1421f), vec3(375.0299f, 31.6097f, -162.2364f), vec3(-0.0000f, -0.2663f, -0.0000f), Color(1.0000f, 1.0000f, 1.000f,0.0f));
	CreateCube(vec3(113.8129f, 1.9449f, 31.1421f), vec3(297.6748f, 31.6097f, -172.5867f), vec3(-0.0000f, -0.0881f, -0.0000f), Color(1.0000f, 1.0000f, 1.000f,0.0f));
	CreateCube(vec3(83.6342f, 1.9449f, 31.1421f), vec3(201.7980f, 31.6097f, -186.7503f), vec3(-0.0000f, -0.2252f, -0.0000f), Color(1.0000f, 1.0000f, 1.000f,0.0f));
	CreateCube(vec3(83.6342f, 1.9449f, 31.1421f), vec3(136.9723f, 31.6097f, -209.6300f), vec3(-0.0000f, -0.4434f, -0.0000f), Color(1.0000f, 1.0000f, 1.000f,0.0f));
	CreateCube(vec3(218.4142f, 1.9449f, 31.1421f), vec3(10.0445f, 31.6097f, -285.8956f), vec3(-0.0000f, -0.5759f, -0.0000f), Color(1.0000f, 1.0000f, 1.000f,0.0f));
	CreateCube(vec3(54.5436f, 1.9449f, 31.1421f), vec3(-96.7274f, 31.6097f, -346.9081f), vec3(-0.0000f, -0.1259f, -0.0000f), Color(1.0000f, 1.0000f, 1.000f,0.0f));
	CreateCube(vec3(54.5436f, 1.9449f, 31.1421f), vec3(-135.4050f, 31.6097f, -337.6473f), vec3(-0.0000f, 0.5116f, -0.0000f), Color(1.0000f, 1.0000f, 1.000f,0.0f));
	CreateCube(vec3(54.5436f, 1.9449f, 31.1421f), vec3(-231.8265f, 31.6097f, -259.2027f), vec3(-0.0000f, 0.9628f, -0.0000f), Color(1.0000f, 1.0000f, 1.000f,0.0f));
	CreateCube(vec3(54.5436f, 1.9449f, 31.1421f), vec3(-244.3558f, 31.6097f, -227.6069f), vec3(-0.0000f, 1.4708f, -0.0000f), Color(1.0000f, 1.0000f, 1.000f,0.0f));
	CreateCube(vec3(54.5436f, 1.9449f, 31.1421f), vec3(-247.0796f, 31.6097f, -184.5713f), vec3(0.0000f, -1.5207f, 0.0000f), Color(1.0000f, 1.0000f, 1.000f,0.0f));
	CreateCube(vec3(54.5436f, 1.9449f, 31.1421f), vec3(-231.2818f, 31.6097f, -149.1623f), vec3(0.0000f, -0.7335f, 0.0000f), Color(1.0000f, 1.0000f, 1.000f,0.0f));
	CreateCube(vec3(33.3688f, 1.9449f, 31.1421f), vec3(-203.4993f, 31.6097f, -132.8197f), vec3(0.0000f, -0.1330f, 0.0000f), Color(1.0000f, 1.0000f, 1.000f,0.0f));
	CreateCube(vec3(92.9217f, 1.9449f, 31.1421f), vec3(-68.9841f, 62.1234f, -132.4269f), vec3(0.0000f, 0.0512f, 0.0000f), Color(1.0000f, 1.0000f, 1.000f,0.0f));
	CreateCube(vec3(44.2841f, 1.9449f, 31.1421f), vec3(-16.7050f, 62.1234f, -133.2151f), vec3(0.0000f, -0.0824f, 0.0000f), Color(1.0000f, 1.0000f, 1.000f,0.0f));
	CreateCube(vec3(44.2841f, 1.9449f, 31.1421f), vec3(-6.1966f, 62.1234f, -131.1134f), vec3(0.0000f, -0.3225f, 0.0000f), Color(1.0000f, 1.0000f, 1.000f,0.0f));
	CreateCube(vec3(44.2841f, 1.9449f, 31.1421f), vec3(17.7100f, 62.1234f, -112.9864f), vec3(0.0000f, -1.0301f, 0.0000f), Color(1.0000f, 1.0000f, 1.000f,0.0f));
	CreateCube(vec3(122.9571f, 1.9449f, 31.1421f), vec3(32.4217f, 62.1234f, -77.7834f), vec3(0.0000f, -1.3043f, 0.0000f), Color(1.0000f, 1.0000f, 1.000f,0.0f));
	CreateCube(vec3(44.2841f, 1.9449f, 31.1421f), vec3(36.7827f, 62.1234f, -47.1515f), vec3(0.0000f, -1.4523f, 0.0000f), Color(1.0000f, 1.0000f, 1.000f,0.0f));
	CreateCube(vec3(110.5738f, 1.9449f, 31.1421f), vec3(20.0744f, 62.1234f, 26.7750f), vec3(-0.0000f, 1.2400f, -0.0000f), Color(1.0000f, 1.0000f, 1.000f,0.0f));
	CreateCube(vec3(110.5738f, 1.9449f, 31.1421f), vec3(-8.2982f, 62.1234f, 125.5117f), vec3(-0.0000f, 1.3977f, -0.0000f), Color(1.0000f, 1.0000f, 1.000f,0.0f));
	CreateCube(vec3(54.0347f, 1.9449f, 31.1421f), vec3(-10.9464f, 62.1234f, 173.5560f), vec3(0.0000f, -1.4957f, 0.0000f), Color(1.0000f, 1.0000f, 1.000f,0.0f));
	CreateCube(vec3(54.0347f, 1.9449f, 31.1421f), vec3(-0.7322f, 62.1234f, 207.6031f), vec3(0.0000f, -1.0499f, 0.0000f), Color(1.0000f, 1.0000f, 1.000f,0.0f));
	CreateCube(vec3(54.0347f, 1.9449f, 31.1421f), vec3(34.0715f, 62.1234f, 235.5975f), vec3(0.0000f, -0.4583f, 0.0000f), Color(1.0000f, 1.0000f, 1.000f,0.0f));
	CreateCube(vec3(54.0347f, 1.9449f, 31.1421f), vec3(74.9281f, 62.1234f, 241.6503f), vec3(0.0000f, -0.0022f, 0.0000f), Color(1.0000f, 1.0000f, 1.000f,0.0f));
	CreateCube(vec3(54.0347f, 1.9449f, 31.1421f), vec3(119.1894f, 62.1234f, 226.5182f), vec3(0.0000f, 0.5576f, 0.0000f), Color(1.0000f, 1.0000f, 1.000f,0.0f));
	CreateCube(vec3(54.0347f, 1.9449f, 31.1421f), vec3(141.1309f, 62.1234f, 191.3362f), vec3(0.0000f, 1.1916f, 0.0000f), Color(1.0000f, 1.0000f, 1.000f,0.0f));
	CreateCube(vec3(54.0347f, 1.9449f, 31.1421f), vec3(148.6969f, 62.1234f, 153.5060f), vec3(0.0000f, 1.4880f, 0.0000f), Color(1.0000f, 1.0000f, 1.000f,0.0f));
	CreateCube(vec3(60.6528f, 1.9449f, 31.1421f), vec3(146.5179f, 62.1234f, -21.9049f), vec3(0.0000f, 1.4880f, 0.0000f), Color(1.0000f, 1.0000f, 1.000f,0.0f));
	CreateCube(vec3(54.0347f, 1.9449f, 31.1421f), vec3(161.7710f, 62.1234f, -69.2985f), vec3(0.0000f, 1.0665f, 0.0000f), Color(1.0000f, 1.0000f, 1.000f,0.0f));
	CreateCube(vec3(63.9543f, 1.9449f, 31.1421f), vec3(197.1801f, 62.1234f, -100.3495f), vec3(0.0000f, 0.5197f, 0.0000f), Color(1.0000f, 1.0000f, 1.000f,0.0f));
	CreateCube(vec3(54.0347f, 1.9449f, 31.1421f), vec3(234.2233f, 62.1234f, -105.7970f), vec3(0.0000f, 0.0745f, 0.0000f), Color(1.0000f, 1.0000f, 1.000f,0.0f));
	CreateCube(vec3(54.0347f, 1.9449f, 31.1421f), vec3(283.2512f, 62.1234f, -103.6180f), vec3(0.0000f, -0.2790f, 0.0000f), Color(1.0000f, 1.0000f, 1.000f,0.0f));
	CreateCube(vec3(54.0347f, 1.9449f, 31.1421f), vec3(331.1896f, 62.1234f, -83.4621f), vec3(0.0000f, -0.4515f, 0.0000f), Color(1.0000f, 1.0000f, 1.000f,0.0f));
	CreateCube(vec3(60.4066f, 1.9449f, 31.1421f), vec3(375.3147f, 62.1234f, -55.1349f), vec3(0.0000f, -0.7837f, 0.0000f), Color(1.0000f, 1.0000f, 1.000f,0.0f));
	CreateCube(vec3(54.0347f, 1.9449f, 31.1421f), vec3(403.0972f, 62.1234f, -13.7336f), vec3(0.0000f, -1.1619f, 0.0000f), Color(1.0000f, 1.0000f, 1.000f,0.0f));
	CreateCube(vec3(54.0347f, 1.9449f, 31.1421f), vec3(404.7314f, 62.1234f, 28.2125f), vec3(-0.0000f, 1.2656f, -0.0000f), Color(1.0000f, 1.0000f, 1.000f,0.0f));
	CreateCube(vec3(41.4351f, 1.9449f, 31.1421f), vec3(387.7474f, 62.1234f, 50.3029f), vec3(-0.0000f, 0.5401f, -0.0000f), Color(1.0000f, 1.0000f, 1.000f,0.0f));
	CreateCube(vec3(32.4820f, 1.9449f, 31.1421f), vec3(363.8846f, 62.1234f, 61.9059f), vec3(-0.0000f, 0.0021f, -0.0000f), Color(1.0000f, 1.0000f, 1.000f,0.0f));
	CreateCube(vec3(153.5216f, 1.9449f, 31.1421f), vec3(-141.4353f, 32.6984f, 177.8539f), vec3(0.0000f, -0.0013f, 0.0000f), Color(1.0000f, 1.0000f, 1.000f,0.0f));
	CreateCube(vec3(153.5216f, 1.9449f, 31.1421f), vec3(-46.8598f, 32.6984f, 299.2258f), vec3(0.0000f, -0.0013f, 0.0000f), Color(1.0000f, 1.0000f, 1.000f,0.0f));
	CreateCube(vec3(153.5216f, 1.9449f, 31.1421f), vec3(167.5114f, 31.4725f, 299.2258f), vec3(0.0000f, -0.0013f, 0.0000f), Color(1.0000f, 1.0000f, 1.000f,0.0f));
	CreateCube(vec3(153.5216f, 1.9449f, 31.1421f), vec3(282.8935f, 31.4725f, 376.7777f), vec3(0.0000f, -1.0610f, 0.0000f), Color(1.0000f, 1.0000f, 1.000f,0.0f));
	CreateCube(vec3(174.5396f, 1.9449f, 31.1421f), vec3(430.7465f, 31.4725f, 380.8760f), vec3(0.0000f, 0.9165f, 0.0000f), Color(1.0000f, 1.0000f, 1.000f,0.0f));
	CreateCube(vec3(102.8517f, 1.9449f, 31.1421f), vec3(-180.7162f, 32.6984f, -306.0721f), vec3(0.0000f, 0.6468f, 0.0000f), Color(1.0000f, 1.0000f, 1.000f,0.0f));
	CreateCube(vec3(436.1985f, 1.9449f, 31.1421f), vec3(9.9423f, 1.1590f, 60.7493f), vec3(-0.0000f, 0.0003f, -0.0000f), Color(1.0000f, 1.0000f, 1.000f,0.0f));
	CreateCube(vec3(430.0952f, 1.9449f, 31.1421f), vec3(-164.9687f, 32.6984f, -0.9841f), vec3(0.0000f, -0.0013f, 0.0000f), Color(1.0000f, 1.0000f, 1.000f,0.0f));
	CreateCube(vec3(57.2029f, 1.9449f, 31.1421f), vec3(-593.0253f, 1.1590f, -1.5604f), vec3(0.0000f, 0.1333f, 0.0000f), Color(1.0000f, 1.0000f, 1.000f,0.0f));
	CreateCube(vec3(57.2029f, 1.9449f, 31.1421f), vec3(-537.3308f, 1.1590f, -1.5604f), vec3(0.0000f, -0.0069f, 0.0000f), Color(1.0000f, 1.0000f, 1.000f,0.0f));
	CreateCube(vec3(127.1378f, 1.9449f, 31.1421f), vec3(146.7300f, 62.1234f, 68.5396f), vec3(0.0000f, -1.5453f, 0.0000f), Color(1.0000f, 1.0000f, 1.000f,0.0f));
	CreateCube(vec3(116.7841f, 1.9449f, 31.1421f), vec3(462.3571f, 31.5186f, 32.9217f), vec3(0.0000f, 1.5667f, 0.0000f), Color(1.0000f, 1.0000f, 1.000f,0.0f));
	CreateCube(vec3(33.3688f, 1.9449f, 31.1421f), vec3(-189.8165f, 31.6097f, -130.9953f), vec3(0.0000f, 0.0069f, 0.0000f), Color(1.0000f, 1.0000f, 1.000f,0.0f));
	CreateCube(vec3(41.2245f, 1.9449f, 29.8250f), vec3(-327.7938f, 1.1590f, 113.2437f), vec3(-0.0000f, 1.2343f, -0.0000f), Color(1.0000f, 1.0000f, 1.000f,0.0f));


	logo = App->renderer3D->LoadTexture("Assets/Bugatti_logo.png");
	logo2 = App->renderer3D->LoadTexture("Assets/logo2.png");
	road = App->renderer3D->LoadTexture("Assets/road2.png");
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

	App->renderer3D->DrawTexture(road, { -500, 2.19f, 122.0f }, 530.0f, 90, vec3(1, 0, 0));

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



