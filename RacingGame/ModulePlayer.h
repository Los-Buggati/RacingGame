#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"

struct PhysVehicle3D;

#define MAX_ACCELERATION 1000.0f
#define TURN_DEGREES 15.0f * DEGTORAD
#define BRAKE_POWER 1000.0f

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update(float dt);
	void OnCollision(PhysBody3D* body1, PhysBody3D* body2) override;
	bool CleanUp();

	void CreateCar(int carIndex);
	void Respawn(int carIndex);
	void DarVuelta(int carIndex);

public:

	PhysVehicle3D* vehicle[2];
	float turn[2];
	float acceleration[2];
	float brake[2];

	int carCount = 0;

	bool up[2] = { false, false };
	bool down[2] = { false, false };
	bool left[2] = { false, false };
	bool right[2] = { false, false };
	bool back[2] = { false, false };
	bool impulseActivated[2] = { false, false};
	int myCar = 0;

	btVector3 position;
	vec3 InitPos = { 0,40,5 };
};