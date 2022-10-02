#include "pch.hpp"

#include "online.hpp"
#include "Core/Gamepad/gamepad.hpp"
#include "Core/Engine/engine.hpp"
#include <iostream>
#include "asio/asio.hpp"
#pragma comment (lib, "Ws2_32.lib")
using asio::ip::udp;
std::string S1API::getip() {
	try {
		asio::io_service netService;
		udp::resolver   resolver(netService);
		udp::resolver::query query(udp::v4(), "google.com", "");
		udp::resolver::iterator endpoints = resolver.resolve(query);
		udp::endpoint ep = *endpoints;
		udp::socket socket(netService);
		socket.connect(ep);
		asio::ip::address addr = socket.local_endpoint().address();
		return addr.to_string();
	}
	catch (std::exception& e) {
		return "NULL";
	}
}

void S1API::fillcallbacks() {
	
	S1API::cb.begin_game = NULL;
	S1API::cb.advance_frame = NULL;
	S1API::cb.load_game_state = NULL;
	S1API::cb.save_game_state = NULL;
	S1API::cb.free_buffer = NULL;
	S1API::cb.on_event = NULL;
}

bool S1API::startsession(GGPOSession** session, GGPOSessionCallbacks* cb, int input_size, unsigned short localport) {
	return ggpo_start_session(session, cb, "NSUNS1", 2, input_size, localport);
}

bool S1API::addlocalplayer(GGPOSession* session, GGPOPlayer player, GGPOPlayerHandle handle, std::string ip_address) {
	player.size = sizeof(player);
	player.type = GGPO_PLAYERTYPE_LOCAL;
	return ggpo_add_player(session, &player, &handle);
}

bool S1API::addremoteplayer(GGPOSession* session, GGPOPlayer player, GGPOPlayerHandle handle, std::string ip_address) {

	player.size = sizeof(player);
	player.type = GGPO_PLAYERTYPE_REMOTE;
	strcpy(player.u.remote.ip_address, &S1API::ipclient[0]);
	player.u.remote.port = std::stoi(S1API::clientport);
	return ggpo_add_player(session, &player, &handle);
}

void S1API::test::getinputs(GGPOSession* session, GGPOPlayer host, GGPOPlayer client, __int64 hostinputs, __int64 clientinputs, GGPOPlayerHandle hosthandle, GGPOPlayerHandle clienthandle) {

	S1API::pad inputs[2] = { S1API::hostpad, S1API::clientpad };
		/* notify ggpo of the local player's inputs */
		bool result = ggpo_add_local_input(S1API::ggpo,               // the session object
			hosthandle,  // handle for p1
			&inputs[0],              // p1's inputs
			sizeof(inputs[0]));      // size of p1's inputs

/* synchronize the local and remote inputs */
	if (GGPO_SUCCEEDED(result)) {
		bool result = ggpo_synchronize_input(S1API::ggpo,         // the session object
			inputs,            // array of inputs
			sizeof(inputs), NULL);   // size of all inputs
		if (GGPO_SUCCEEDED(result)) {
			/* pass both inputs to our advance function */
			engine::runEngine = 1;
			ggpo_advance_frame(S1API::ggpo);
		}
		else {
			engine::runEngine = 0;
		}
	}
}

void S1API::setframedelay(GGPOSession* session, GGPOPlayerHandle host, GGPOPlayerHandle client, int frame_delay) {
	ggpo_set_frame_delay(session, host, 10);
	ggpo_set_frame_delay(session, client, 10);
}

void S1API::endsession(GGPOSession* session) {
	ggpo_close_session(session);
}