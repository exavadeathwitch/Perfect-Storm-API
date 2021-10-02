#include "pch.hpp"

#include "Hooks/Hooks.hpp"

#include "Globals.hpp"

#include "Player/Mechanics/mech.hpp"

#include "Util/Memory/Memory.hpp"

#include "Util/Console/Console.hpp"

#include "Util/Memory/Modify.hpp"

#include "Util/Sound/SDL2Music.h"

#include "Util/Sound/Music.hpp"

#include <string>
extern "C" std::uintptr_t proxyFunctions[29] = {};

static constexpr const char* proxyFuncNames[29] = {
	"D3DAssemble",
	"DebugSetMute",
	"D3DCompile",
	"D3DCompile2",
	"D3DCompileFromFile",
	"D3DCompressShaders",
	"D3DCreateBlob",
	"D3DCreateFunctionLinkingGraph",
	"D3DCreateLinker",
	"D3DDecompressShaders",
	"D3DDisassemble",
	"D3DDisassemble10Effect",
	"D3DDisassemble11Trace",
	"D3DDisassembleRegion",
	"D3DGetBlobPart",
	"D3DGetDebugInfo",
	"D3DGetInputAndOutputSignatureBlob",
	"D3DGetInputSignatureBlob",
	"D3DGetOutputSignatureBlob",
	"D3DGetTraceInstructionOffsets",
	"D3DLoadModule",
	"D3DPreprocess",
	"D3DReadFileToBlob",
	"D3DReflect",
	"D3DReflectLibrary",
	"D3DReturnFailure1",
	"D3DSetBlobPart",
	"D3DStripShader",
	"D3DWriteBlobToFile"
};

DWORD __stdcall modEntry(void* const imageBase) {
	const HMODULE oD3DCompiler = LoadLibraryA("d3dcompiler_47_o.dll");

	if (!oD3DCompiler)
		return FALSE;

	for (auto i = 0u; i < sizeof(proxyFunctions) / sizeof(*proxyFunctions); ++i)
		proxyFunctions[i] = std::bit_cast<std::uintptr_t>(GetProcAddress(oD3DCompiler, proxyFuncNames[i]));

    util::console::initialize("lol");

	globals::moduleBase = (uintptr_t)GetModuleHandle(NULL);
    
	printf_s("[+] init\n");

    if (!sdk::game::initialize())
        std::abort();
	
    hooks::initialize();
	
	settings::onStartup();
	music::functions m;
	m.playMusicTrackTest();
	/*music playing test
		SDL2Music music;
		std::string filepath = "test.wav";
		std::string str_obj(filepath);
		char* filepath_arr = &str_obj[0];
		music.addMusicTrack(filepath_arr);
		music.playMusicTrack(0);
	
	//Read
	//Write
	util::memory::Modify::write_bytes<7>(globals::moduleBase + 0x7C059A + 0xC00, { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 });
	util::memory::Modify::write_bytes<5>(globals::moduleBase + 0x5741AD + 0xC00, { 0x90, 0x90, 0x90, 0x90, 0x90 });
	util::memory::Modify::write_bytes<5>(globals::moduleBase + 0x575C3E + 0xC00, { 0x90, 0x90, 0x90, 0x90, 0x90 });
	util::memory::Modify::write_bytes<5>(globals::moduleBase + 0x573F90 + 0xC00, { 0x90, 0x90, 0x90, 0x90, 0x90 });
	util::memory::Modify::write_bytes<4>(globals::moduleBase + 0x77E621 + 0xC00, { 0x90, 0x90, 0x90, 0x90 });
	util::memory::Modify::write_bytes<5>(globals::moduleBase + 0x74A837 + 0xC00, { 0x90, 0x90, 0x90, 0x90, 0x90 });
	
	
	util::memory::Modify::write_bytes<6>(globals::moduleBase + 0x732C77, { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 });
	util::memory::Modify::write_bytes<2>(globals::moduleBase + 0x732F9A, { 0x90, 0x90 });
	util::memory::Modify::write_bytes<4>(globals::moduleBase + 0x732CEF, { 0x90, 0x90, 0x90, 0x90 });

	//Write
	
	util::memory::Modify::write_bytes<7>(globals::moduleBase + 0x7C059A + 0xC00, { mechanics::FC1[0], mechanics::FC1[1], mechanics::FC1[2], mechanics::FC1[3], mechanics::FC1[4], mechanics::FC1[5], mechanics::FC1[6] });
	util::memory::Modify::write_bytes<5>(globals::moduleBase + 0x5741AD + 0xC00, { mechanics::FC2[0], mechanics::FC2[1], mechanics::FC2[2], mechanics::FC2[3], mechanics::FC2[4] });
	util::memory::Modify::write_bytes<5>(globals::moduleBase + 0x575C3E + 0xC00, { mechanics::FC3[0], mechanics::FC3[1], mechanics::FC3[2], mechanics::FC3[3], mechanics::FC3[4] });
	util::memory::Modify::write_bytes<5>(globals::moduleBase + 0x573F90 + 0xC00, { mechanics::FC4[0], mechanics::FC4[1], mechanics::FC4[2], mechanics::FC4[3], mechanics::FC4[4] });
	*/
    while (!GetAsyncKeyState(VK_END))
        Sleep(50);

    hooks::uninitialize();
    util::console::uninitialize();
	FreeLibrary(oD3DCompiler);

    FreeLibraryAndExitThread(static_cast<HMODULE>(imageBase), EXIT_SUCCESS);
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
		DisableThreadLibraryCalls(hModule);

        if (const HANDLE thread = CreateThread(nullptr, 0, modEntry, hModule, 0, nullptr))
            CloseHandle(thread);
    }
    return TRUE;
}

extern "C" void D3DAssembleThunk();
extern "C" void DebugSetMuteThunk();
extern "C" void D3DCompileThunk();
extern "C" void D3DCompile2Thunk();
extern "C" void D3DCompileFromFileThunk();
extern "C" void D3DCompressShadersThunk();
extern "C" void D3DCreateBlobThunk();
extern "C" void D3DCreateFunctionLinkingGraphThunk();
extern "C" void D3DCreateLinkerThunk();
extern "C" void D3DDecompressShadersThunk();
extern "C" void D3DDisassembleThunk();
extern "C" void D3DDisassemble10EffectThunk();
extern "C" void D3DDisassemble11TraceThunk();
extern "C" void D3DDisassembleRegionThunk();
extern "C" void D3DGetBlobPartThunk();
extern "C" void D3DGetDebugInfoThunk();
extern "C" void D3DGetInputAndOutputSignatureBlobThunk();
extern "C" void D3DGetInputSignatureBlobThunk();
extern "C" void D3DGetOutputSignatureBlobThunk();
extern "C" void D3DGetTraceInstructionOffsetsThunk();
extern "C" void D3DLoadModuleThunk();
extern "C" void D3DPreprocessThunk();
extern "C" void D3DReadFileToBlobThunk();
extern "C" void D3DReflectThunk();
extern "C" void D3DReflectLibraryThunk();
extern "C" void D3DReturnFailure1Thunk();
extern "C" void D3DSetBlobPartThunk();
extern "C" void D3DStripShaderThunk();
extern "C" void D3DWriteBlobToFileThunk();