#include "pch.hpp"

#include "nuccFileLoadList.hpp"

#include "Core/DebugMenu/DebugMenu.hpp"

#include "Core/ModConsole/ModConsole.hpp"

#include "Util/Memory/String.hpp"
__int64 __fastcall nuccFileLoadList::Load(__int64** a1, char* _xfbin, int a3, int a4, int a5) {
	if (c.displayloadXFBIN)
		modconsole.AddLog((util::memory::String::strFromAddr((__int64)_xfbin) + "\n").c_str());
	return globals::hookManager->callOriginal<decltype(&nuccFileLoadList::Load)>(nuccFileLoadList::Load, a1, _xfbin, a3, a4, a5);

}