#pragma once

#include "pch.hpp"
#include <Windows.h>
#include <string>
#include <iostream>
#include <Wininet.h>
#include <string>
#include "imgui/include/imgui.h"
#include "GGPO/ggponet.h"
#pragma comment(lib, "wininet.lib")
namespace S1API {
	inline GGPOSession *ggpo = NULL;
	inline GGPOErrorCode result;
	inline GGPOSessionCallbacks cb;
	inline GGPOPlayer host, client; //host is p1, client is p2
	inline GGPOPlayerHandle player_handles[2];
	inline std::string ipclient;
	inline std::string iphost;
	//inline unsigned short port;
	inline std::string clientport;
	inline std::string hostport;
	inline char buf[32];
	inline int framedelay = 3;
	inline int onlinemenu = 0;
	inline bool isHost = 0;
	inline bool hosting = 0;
	inline bool enableOnline = 0;
	std::string getip();
	void fillcallbacks();
	bool startsession(GGPOSession** session, GGPOSessionCallbacks* cb, int input_size, unsigned short localport);
	bool addlocalplayer(GGPOSession* session, GGPOPlayer player, GGPOPlayerHandle handle, std::string ip_address);
	bool addremoteplayer(GGPOSession* session, GGPOPlayer player, GGPOPlayerHandle handle, std::string ip_address);
	class test {
	public:

		static void getinputs(GGPOSession* session, GGPOPlayer host, GGPOPlayer client, __int64 hostinputs, __int64 clientinputs, GGPOPlayerHandle hosthandle, GGPOPlayerHandle clienthandle);
	};
	void setframedelay(GGPOSession* session, GGPOPlayerHandle host, GGPOPlayerHandle client, int frame_delay);
	static void endsession(GGPOSession* session);
}