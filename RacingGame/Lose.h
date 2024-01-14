#pragma once
#include "Module.h"
#include "Globals.h"

class Lose : public Module
{
public:
	Lose(Application* app, bool start_enabled = true);
	~Lose();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

public:
	SDL_Texture* Lose1;
	
};



