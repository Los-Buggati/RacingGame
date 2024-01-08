#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"
#include <iostream>
#include <vector>
using namespace std;

#include "SDL2_net/include/SDL_net.h"
#pragma comment(lib, "SDL2_net/lib/x86/SDL2_net.lib")

class ModuleNetwork : public Module
{
public:
	ModuleNetwork(Application* app, bool start_enabled = true);
	virtual ~ModuleNetwork();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void CreateServer();
	void CreateClient();
	void OnClientConnect(TCPsocket newClient);
	void StartGame();
	void OnGameStart();
	void SendStats(TCPsocket client);

public:
	TCPsocket server;
	TCPsocket client;
	IPaddress ip;
	const char* host;
	int clientIndex;
	int clientsCount = 0;

	vector<TCPsocket> connectedClients;
	int nextClientIndex = 0;

	bool serverCreated = false;
	bool clientCreated = false;
	bool canSend = false;
	bool gameStarted = false;
	bool waitingForStart = false;
	bool serverHost = false;
	bool multiplayer = false;

	int optionsIndex = 0;
};