#include "pch.hpp"

#include "Game/misc/misc.hpp"

#include "ccUI.hpp"


__int64 __fastcall ccUiGetMessage(__int64 MessageToDecode) {
	return globals::hookManager->getOriginal<decltype(&ccUiGetMessage)>(ccUiGetMessage)(MessageToDecode);
}