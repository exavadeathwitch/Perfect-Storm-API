#include "pch.hpp"

#include "nuccLayer.hpp"

#include "Core/DebugMenu/Render/Render.hpp"

#include "Core/DebugMenu/DebugMenu.hpp"

#include "Util/Memory/String.hpp"
__int64 __fastcall nuccLayer::ExecuteDrawCommand(__int64 a1) {
	for (int x = 0; x < sizeof(r.layers); x++) {
		if (util::memory::String::strFromAddr(a1 + 0x8) == r.layers[x] && r.enablelayer[x] == false)
			return 0x0;
	}
	return globals::hookManager->callOriginal<decltype(&nuccLayer::ExecuteDrawCommand)>(nuccLayer::ExecuteDrawCommand, a1);
}