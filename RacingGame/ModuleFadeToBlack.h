#pragma once

#include "Application.h"
#include "Module.h"
#include "SDL/include/SDL_rect.h"

class ModuleFadeToBlack : public Module {

public:
	//Constructor
	ModuleFadeToBlack(Application* app, bool start_enabled = true);

	//Destructor
	~ModuleFadeToBlack();

	// Called when the module is activated
	// Enables the blending mode for transparency
	bool Start();
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	

	bool FadeToBlack(Module* toDisable, Module* toEnable, float frames = 60);


private:
	enum Fade_Step {
		NONE,
		TO_BLACK,
		FROM_BLACK
	} currentStep = Fade_Step::NONE;

	// A frame count system to handle the fade time and ratio
	Uint32 frameCount = 0;
	Uint32 maxFadeFrames = 0;

	// The rectangle of the screen, used to render the black rectangle
	SDL_Rect screenRect;

	// The modules that should be switched after the first step
	Module* moduleToEnable = nullptr;
	Module* moduleToDisable = nullptr;
};