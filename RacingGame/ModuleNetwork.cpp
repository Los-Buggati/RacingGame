#include "Globals.h"
#include "Application.h"
#include "ModuleNetwork.h"

ModuleNetwork::ModuleNetwork(Application* app, bool start_enabled) : Module(app, start_enabled)
{

}

ModuleNetwork::~ModuleNetwork()
{}

bool ModuleNetwork::Start()
{
	LOG("Loading Network");

	SDLNet_Init();

	return true;
}

bool ModuleNetwork::CleanUp()
{
	LOG("Unloading Network");

	return true;
}

update_status ModuleNetwork::Update(float dt)
{
	
	if (App->input->GetKey(SDL_SCANCODE_V) == KEY_DOWN || optionsIndex == 1) 
	{
		optionsIndex = 0;
		multiplayer = true;
		CreateServer();
	}

	if (App->input->GetKey(SDL_SCANCODE_B) == KEY_DOWN || optionsIndex == 2) 
	{
		optionsIndex = 0;
		multiplayer = true;
		printf("Enter the host IP: ");
		char buffer[100];
		fgets(buffer, sizeof(buffer), stdin);

		size_t len = strlen(buffer);
		if (len > 0 && buffer[len - 1] == '\n') {
			buffer[len - 1] = '\0';
		}

		host = buffer;

		CreateClient();
	}

	if (App->input->GetKey(SDL_SCANCODE_N) == KEY_DOWN || optionsIndex == 3) 
	{
		optionsIndex = 0;
		if (multiplayer) StartGame();
		else
		{
			clientIndex = 0;
			clientsCount = 1;
		}
		OnGameStart();
	}

	if (App->input->GetKey(SDL_SCANCODE_M) == KEY_DOWN) {
		waitingForStart = true;
	}
	if (multiplayer)
	{
		if (serverCreated)
		{
			TCPsocket newClient = SDLNet_TCP_Accept(server);
			if (newClient != nullptr) {
				OnClientConnect(newClient);
			}
		}

		if (clientCreated)
		{
			char text[10000];
			int receivedBytes = SDLNet_TCP_Recv(client, text, sizeof(text));

			if (receivedBytes > 0)
			{
				text[receivedBytes] = '\0';
				sscanf_s(text, "%d", &clientIndex);
				printf("Client index received: %d\n", clientIndex);
			}

			clientCreated = false;
		}

		if (waitingForStart && !gameStarted)
		{
			char text[10000];
			int receivedBytes = SDLNet_TCP_Recv(client, text, sizeof(text));

			if (receivedBytes > 0)
			{
				text[receivedBytes] = '\0';
				printf("Clients: %s\n", text);

				sscanf_s(text, "%d", &clientsCount);

				if (clientsCount > 0)
				{
					OnGameStart();
					gameStarted = true;
					canSend = true;
				}
			}
		}

		if (canSend && gameStarted)
		{
			// send messages
			char text[10000];
			sprintf_s(text, "%d,%d,%d,%d,%d,%d",
				clientIndex,
				App->player->up[clientIndex],
				App->player->down[clientIndex],
				App->player->left[clientIndex],
				App->player->right[clientIndex],
				App->player->impulseActivated[clientIndex]);

			int messageLength = strlen(text) + 1;

			if (serverHost) SDLNet_TCP_Send(connectedClients[1], text, messageLength);
			else SDLNet_TCP_Send(client, text, messageLength);

			// receive messages
			int receivedBytes;
			if (serverHost) receivedBytes = SDLNet_TCP_Recv(connectedClients[1], text, sizeof(text));
			else receivedBytes = SDLNet_TCP_Recv(client, text, sizeof(text));

			if (receivedBytes > 0) {
				text[receivedBytes] = '\0';
				printf("Stats: %s\n", text);

				int newClientIndex;
				int up, down, left, right, impulse;

				sscanf_s(text, "%d,%d,%d,%d,%d,%d", &newClientIndex, &up, &down, &left, &right, &impulse);

				App->player->up[newClientIndex] = up;
				App->player->down[newClientIndex] = down;
				App->player->left[newClientIndex] = left;
				App->player->right[newClientIndex] = right;
				App->player->impulseActivated[newClientIndex] = impulse;
			}
		}
	}

	return UPDATE_CONTINUE;
}

void ModuleNetwork::CreateServer()
{
	SDLNet_ResolveHost(&ip, NULL, 1234);

	server = SDLNet_TCP_Open(&ip);

	if (server != nullptr)
	{
		host = SDLNet_ResolveIP(&ip);

		printf("Server created at %s\n", host);

		serverCreated = true;
	}
	serverHost = true;
}

void ModuleNetwork::CreateClient()
{
	SDLNet_ResolveHost(&ip, host, 1234);

	client = SDLNet_TCP_Open(&ip);

	if (SDLNet_ResolveHost(&ip, host, 0) == -1) {
		printf("SDLNet_ResolveHost: %s\n", SDLNet_GetError());
	}
	else {
		char ipString[16];
		const char* ipStringResult = SDLNet_ResolveIP(&ip);
		if (ipStringResult) {
			printf("IP: %s\n", ipStringResult);
		}

		clientCreated = true;
	}
}

void ModuleNetwork::OnClientConnect(TCPsocket newClient)
{
	if (nextClientIndex < 2)
	{
		connectedClients.push_back(newClient);
		int assignedIndex = nextClientIndex;
		nextClientIndex++;

		const char indexMsg[2] = { '0' + assignedIndex, '\0' };
		SDLNet_TCP_Send(newClient, indexMsg, sizeof(indexMsg));
		clientsCount++;
	}
}

void ModuleNetwork::StartGame()
{
	char clientCountMsg[16];
	sprintf_s(clientCountMsg, "%d", clientsCount);

	for (int i = 0; i < connectedClients.size(); ++i) {
		SDLNet_TCP_Send(connectedClients[i], clientCountMsg, strlen(clientCountMsg) + 1);
	}
}

void ModuleNetwork::OnGameStart()
{
	App->renderer3D->Enable();
	App->scene_intro->Enable();
	App->player->Enable();
	App->camera->Enable();
	App->menu->Disable();
	App->renderer->Disable();

	for (int i = 0; i < clientsCount; i++)
	{
		App->player->CreateCar(i);
	}
	gameStarted = true;
	canSend = true;
}