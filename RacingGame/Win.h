#pragma once
#include "Module.h"
#include "Globals.h"

class Win : public Module
{
public:
	Win(Application* app, bool start_enabled = true);
	~Win();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

public:
	SDL_Texture* Win1;
	SDL_Texture* Win2;
	SDL_Texture* Win3;

	int WinIndex = 1;

	float wintimer = 0.0f;



};

