#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"

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
	coin.SetPos(0, 3, 30);
	coin.color = Yellow;

	platform = Cube(50, 1, 30);
	platform.SetPos(0, 1, 20);
	platform.color = White;
	
	mud=App->physics->AddBody(Cube(50, 6, 30), 0.0);
	mud->SetPos(0, 1, 30);
	//mud->collision_listeners.add(this);
	mud->SetAsSensor(true);
	

	physBody = App->physics->AddBody(platform, 0.0f);
	platform.physbody = physBody;

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

	platform.Render();

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
}

