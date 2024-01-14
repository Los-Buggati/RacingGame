#include "Globals.h"
#include "Application.h"
#include "Win.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleNetwork.h"


Win::Win(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

Win::~Win()
{}

// Load assets
bool Win::Start()
{
	LOG("Loading Win assets");
	bool ret = true;

	Win1 = App->textures->Load("Assets/Win1.png");
	Win2 = App->textures->Load("Assets/Win2.png");
	Win3 = App->textures->Load("Assets/Win3.png");
	
	//load music

	return ret;
}

// Unload assets
bool Win::CleanUp()
{
	LOG("Unloading Menu scene");

	return true;
}

// Update
update_status Win::Update(float dt)
{

	wintimer++;
	int time = 10;

	if (wintimer < 50*time) {
		WinIndex = 1;
	}
	else if (wintimer > 50*time && wintimer < 100*time) {
		WinIndex = 2;
	}
	else if (wintimer > 100*time && wintimer < 150*time) {
		WinIndex = 3;
	}
	if (wintimer == 150*time) {
		wintimer = 0;
	}
	
	/*if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		App->
	}*/

	int imageWidth = 3840;
	int imageHeight = 2160;

	int windowWidth, windowHeight;
	SDL_GetWindowSize(App->window->window, &windowWidth, &windowHeight);

	int xPos = (windowWidth - imageWidth) / 2;
	int yPos = (windowHeight - imageHeight) / 2;

	if (WinIndex == 1) App->renderer->Blit(Win1, xPos, yPos, NULL);
	else if (WinIndex == 2) App->renderer->Blit(Win2, xPos, yPos, NULL);
	else if (WinIndex == 3) App->renderer->Blit(Win3, xPos, yPos, NULL);

	return UPDATE_CONTINUE;
}

