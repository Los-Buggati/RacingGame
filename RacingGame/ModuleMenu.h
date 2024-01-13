#pragma once
#include "Module.h"
#include "Globals.h"

class ModuleMenu : public Module
{
public:
	ModuleMenu(Application* app, bool start_enabled = false);
	~ModuleMenu();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

public:
	SDL_Texture* menu1;
	SDL_Texture* menu2;
	SDL_Texture* menu3;
	SDL_Texture* menu4;

	int menuIndex = 1;

};
