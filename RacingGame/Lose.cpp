#include "Globals.h"
#include "Application.h"
#include "Lose.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleNetwork.h"


Lose::Lose(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

Lose::~Lose()
{}

// Load assets
bool Lose::Start()
{
	LOG("Loading Lose assets");
	bool ret = true;

	Lose1 = App->textures->Load("Assets/YouLose.png");

	//load music

	return ret;
}

// Unload assets
bool Lose::CleanUp()
{
	LOG("Unloading Menu scene");

	return true;
}

// Update
update_status Lose::Update(float dt)
{


	int imageWidth = 3840;
	int imageHeight = 2160;

	int windowWidth, windowHeight;
	SDL_GetWindowSize(App->window->window, &windowWidth, &windowHeight);

	int xPos = (windowWidth - imageWidth) / 2;
	int yPos = (windowHeight - imageHeight) / 2;

	App->renderer->Blit(Lose1, xPos, yPos, NULL);

	return UPDATE_CONTINUE;
}

