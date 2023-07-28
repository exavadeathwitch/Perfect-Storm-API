#pragma once

// Exlude rarely used stuff from windows headers...
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

// WINAPI stuff...
#include <Windows.h>
#include <TlHelp32.h>

// Standard library stuff...
#include <array>
#include <algorithm>
#include <format>
#include <fstream>
#include <iostream>
#include <memory>
#include <mutex>
#include <ranges>
#include <string>
#include <stdexcept>
#include <unordered_map>
#include <vector>

// Your stuff... (if you know the files rarely change, so something like logging etc)
#include "Core/SDK/Game.hpp"
#include "Core/Globals.hpp"

#define TOML_IMPLEMENTATION