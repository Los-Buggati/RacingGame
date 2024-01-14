#include "Globals.h"
#include "Application.h"
#include "ModuleMenu.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleNetwork.h"

ModuleMenu::ModuleMenu(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleMenu::~ModuleMenu()
{}

// Load assets
bool ModuleMenu::Start()
{
	LOG("Loading Menu assets");
	bool ret = true;

	menu1 = App->textures->Load("Assets/menu1.png");
	menu2 = App->textures->Load("Assets/menu2.png");
	menu3 = App->textures->Load("Assets/menu3.png");
	menu4 = App->textures->Load("Assets/menu4.png");

	return ret;
}

// Unload assets
bool ModuleMenu::CleanUp()
{
	LOG("Unloading Menu scene");

	return true;
}

// Update
update_status ModuleMenu::Update(float dt)
{

	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN)
	{
		if (menuIndex > 1) menuIndex--;
		else menuIndex = 4;
	}
	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN)
	{
		if (menuIndex < 4) menuIndex++;
		else menuIndex = 1;
	}

	if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
	{
		if (menuIndex == 1) App->network->optionsIndex = 3;
		else if (menuIndex == 2) App->network->optionsIndex = 1;
		else if (menuIndex == 3) App->network->optionsIndex = 2;
		else if (menuIndex == 4) return UPDATE_STOP;
	}

	int imageWidth = 3840;
	int imageHeight = 2160;

	int windowWidth, windowHeight;
	SDL_GetWindowSize(App->window->window, &windowWidth, &windowHeight);

	int xPos = (windowWidth - imageWidth) / 2;
	int yPos = (windowHeight - imageHeight) / 2;
	
	if (menuIndex == 1) App->renderer->Blit(menu1, xPos, yPos, NULL);
	else if (menuIndex == 2) App->renderer->Blit(menu2, xPos, yPos, NULL);
	else if (menuIndex == 3) App->renderer->Blit(menu3, xPos, yPos, NULL);
	else if (menuIndex == 4) App->renderer->Blit(menu4, xPos, yPos, NULL);

	return UPDATE_CONTINUE;
}

