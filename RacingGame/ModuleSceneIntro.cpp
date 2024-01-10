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
	sensor_cube = App->physics->AddBody(Cube(5, 5, 5), 0.0);
	sensor_cube->SetAsSensor(true);
	sensor_cube->SetPos(0, 3, 0);

	coin = Cylinder(1.0f, 0.5f);
	coin.SetPos(5, 3, 5);
	coin.color = Blue;

	CreateCube(vec3(50, 1, 30), vec3(5, 3, 5), vec3(0,0,0), White);

	logo = App->renderer3D->LoadTexture("Assets/Bugatti_logo.png");
	logo2 = App->renderer3D->LoadTexture("Assets/logo2.png");
	road = App->renderer3D->LoadTexture("Assets/road.png");

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

	angle++;
	coin.SetRotation(angle, vec3(0, 1, 0));
	coin.Render();

	for (auto& cube : cubes)
	{
		cube.Render();
	}

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

	App->renderer3D->DrawTexture(road, { 0, 1.6f, 10.0f }, 50.0f, 90, vec3(1, 0, 0));

	const btVector3& chassisPos = App->player->vehicle[App->network->clientIndex]->vehicle->getChassisWorldTransform().getOrigin();
	btQuaternion carRotation = App->player->vehicle[App->network->clientIndex]->vehicle->getChassisWorldTransform().getRotation();
	float carAngle = carRotation.getAngle() * RADTODEG;

	btVector3 logoOffset = btVector3(0.0f, 1.0f, -2.35f);

	btVector3 rotatedOffset = App->player->vehicle[App->network->clientIndex]->vehicle->getChassisWorldTransform().getBasis() * logoOffset;

	btVector3 logoPos = chassisPos + rotatedOffset;

	if (carRotation.getAxis().y() < 0)
	{
		carAngle = -carAngle;
	}

	App->renderer3D->DrawTexture(logo, { logoPos.getX(), logoPos.getY(), logoPos.getZ() }, 0.7f, carAngle, vec3(0, 1, 0));

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
}

void ModuleSceneIntro::CreateCube(vec3 size, vec3 position, vec3 rotation, Color color) 
{
	Cube platform(size.x, size.y, size.z);
	platform.SetPos(position.x, position.y, position.z);
	platform.SetRotation(rotation.x, vec3(1, 0, 0));
	platform.SetRotation(rotation.y, vec3(0, 1, 0));
	platform.SetRotation(rotation.z, vec3(0, 0, 1));
	platform.color = color;

	auto physBody = App->physics->AddBody(platform, 0.0f);
	platform.physbody = physBody;

	cubes.push_back(platform);
}
