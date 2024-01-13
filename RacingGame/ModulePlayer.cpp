#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "Primitive.h"
#include "PhysVehicle3D.h"
#include "PhysBody3D.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled)
{

}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	return true;
}

// Update: draw background
update_status ModulePlayer::Update(float dt)
{
	myCar = App->network->clientIndex;

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && carCount < 2)
	{
		CreateCar(carCount);
	}
	
	if (App->network->gameStarted)
	{
		for (int currentCar = 0; currentCar < carCount; currentCar++)
		{
			if (currentCar != myCar)
			{
				turn[currentCar] = acceleration[currentCar] = brake[currentCar] = 0.0f;

				if (up[currentCar])
				{
					acceleration[currentCar] = MAX_ACCELERATION;
				}

				if (left[currentCar])
				{
					if (turn[currentCar] < TURN_DEGREES)
						turn[currentCar] += TURN_DEGREES;
				}

				if (right[currentCar])
				{
					if (turn[currentCar] > -TURN_DEGREES)
						turn[currentCar] -= TURN_DEGREES;
				}

				if (down[currentCar])
				{
					brake[currentCar] = BRAKE_POWER;
				}

				if (impulseActivated[currentCar])
				{
					vehicle[currentCar]->ApplyEngineForce(3000.0f);
					impulseActivated[currentCar] = false;
				}
				else vehicle[currentCar]->ApplyEngineForce(acceleration[currentCar]);
				vehicle[currentCar]->Turn(turn[currentCar]);
				vehicle[currentCar]->Brake(brake[currentCar]);

				vehicle[currentCar]->Render();
			}
		}

		turn[myCar] = acceleration[myCar] = brake[myCar] = 0.0f;

		if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		{
			if (vehicle[myCar]->GetKmh() < 0.0f) brake[myCar] = BRAKE_POWER;
			else acceleration[myCar] = MAX_ACCELERATION;
			up[myCar] = true;
		}
		else up[myCar] = false;

		if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		{
			if (turn[myCar] < TURN_DEGREES)
				turn[myCar] += TURN_DEGREES;
			left[myCar] = true;
		}
		else left[myCar] = false;

		if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		{
			if (turn[myCar] > -TURN_DEGREES)
				turn[myCar] -= TURN_DEGREES;
			right[myCar] = true;
		}
		else right[myCar] = false;

		if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		{
			if (vehicle[myCar]->GetKmh() > 0.0f) brake[myCar] = BRAKE_POWER;
			else acceleration[myCar] = -MAX_ACCELERATION / 2;
			down[myCar] = true;
		}
		else down[myCar] = false;

		if (impulseActivated[myCar])
		{
			vehicle[myCar]->ApplyEngineForce(3000.0f);
			impulseActivated[myCar] = false;
		}
		else vehicle[myCar]->ApplyEngineForce(acceleration[myCar]);
		vehicle[myCar]->Turn(turn[myCar]);
		vehicle[myCar]->Brake(brake[myCar]);

		vehicle[myCar]->Render();

		char title[80];
		sprintf_s(title, "%.1f Km/h", vehicle[myCar]->GetKmh());
		App->window->SetTitle(title);
	}

	return UPDATE_CONTINUE;
}


void ModulePlayer::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
	if (body1 == App->scene_intro->sensor_cube || body2 == App->scene_intro->sensor_cube)
	{
		for (int currentCar = 0; currentCar < carCount; currentCar++)
		{
			if (currentCar != myCar)
			{
				if (body1 == vehicle[currentCar] || body2 == vehicle[currentCar]) impulseActivated[currentCar] = true;
			}
			else impulseActivated[myCar] = true;
		}
	}
}

void ModulePlayer::CreateCar(int carIndex)
{
	carCount++;

	turn[carIndex] = acceleration[carIndex] = brake[carIndex] = 0.0f;

	VehicleInfo car;

	// Car properties ----------------------------------------
	car.chassis_size.Set(2, 1.2, 4);
	car.chassis_offset.Set(0, 0.5, 0);
	car.mass = 500.0f;
	car.suspensionStiffness = 15.88f;
	car.suspensionCompression = 0.83f;
	car.suspensionDamping = 0.88f;
	car.maxSuspensionTravelCm = 1000.0f;
	car.frictionSlip = 50.5;
	car.maxSuspensionForce = 6000.0f;
	if (carIndex == 0) car.wheelColor = Black;
	else car.wheelColor = Red;


	// Wheel properties ---------------------------------------
	float connection_height = 1.2f;
	float wheel_radius = 0.55f;
	float wheel_width = 0.5f;
	float suspensionRestLength = 1.2f;

	// Don't change anything below this line ------------------

	float half_width = car.chassis_size.x * 0.5f;
	float half_length = car.chassis_size.z * 0.5f;

	vec3 direction(0, -1, 0);
	vec3 axis(-1, 0, 0);

	car.num_wheels = 4;
	car.wheels = new Wheel[4];

	// FRONT-LEFT ------------------------
	car.wheels[0].connection.Set(half_width + 0.3f * wheel_width, connection_height, half_length + 0.15f - wheel_radius);
	car.wheels[0].direction = direction;
	car.wheels[0].axis = axis;
	car.wheels[0].suspensionRestLength = suspensionRestLength;
	car.wheels[0].radius = wheel_radius;
	car.wheels[0].width = wheel_width;
	car.wheels[0].front = true;
	car.wheels[0].drive = true;
	car.wheels[0].brake = false;
	car.wheels[0].steering = true;

	// FRONT-RIGHT ------------------------
	car.wheels[1].connection.Set(-half_width - 0.3f * wheel_width, connection_height, half_length + 0.15f - wheel_radius);
	car.wheels[1].direction = direction;
	car.wheels[1].axis = axis;
	car.wheels[1].suspensionRestLength = suspensionRestLength;
	car.wheels[1].radius = wheel_radius;
	car.wheels[1].width = wheel_width;
	car.wheels[1].front = true;
	car.wheels[1].drive = true;
	car.wheels[1].brake = false;
	car.wheels[1].steering = true;

	// REAR-LEFT ------------------------
	car.wheels[2].connection.Set(half_width + 0.3f * wheel_width, connection_height, -half_length - 0.85f + wheel_radius);
	car.wheels[2].direction = direction;
	car.wheels[2].axis = axis;
	car.wheels[2].suspensionRestLength = suspensionRestLength;
	car.wheels[2].radius = wheel_radius;
	car.wheels[2].width = wheel_width;
	car.wheels[2].front = false;
	car.wheels[2].drive = false;
	car.wheels[2].brake = true;
	car.wheels[2].steering = false;

	// REAR-RIGHT ------------------------
	car.wheels[3].connection.Set(-half_width - 0.3f * wheel_width, connection_height, -half_length -0.85f + wheel_radius);
	car.wheels[3].direction = direction;
	car.wheels[3].axis = axis;
	car.wheels[3].suspensionRestLength = suspensionRestLength;
	car.wheels[3].radius = wheel_radius;
	car.wheels[3].width = wheel_width;
	car.wheels[3].front = false;
	car.wheels[3].drive = false;
	car.wheels[3].brake = true;
	car.wheels[3].steering = false;

	vehicle[carIndex] = App->physics->AddVehicle(car);
	vehicle[carIndex]->collision_listeners.add(this); // Add this module as listener to callbacks from vehicle
	vehicle[carIndex]->SetPos(carIndex * 5, 5, 50);
}

