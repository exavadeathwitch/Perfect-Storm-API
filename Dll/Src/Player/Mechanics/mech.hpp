#pragma once

//Adding Toggles for Each Individual Mechanic

namespace mechanics {
	//Chakraless Circle Attacks Function
	inline bool enableNMTilt = 1;
	inline bool enableTaunt = 1;
	inline bool enableGKunaiAirCombo = 1;

	//Grab/Counter Function
	inline bool enableNMGrab = 1;
	inline bool enableGKunai = 1;

	//Can You Shuriken Function
	inline bool enableShurikenComboTilt = 1;

	//Cancelling Out of Tilts Function
	inline bool enableTiltCancels = 1;

	//Full Combo Switch Function
	inline bool enableFullComboSwitch = 1;

	//Can You Fast Air Chakra Dash or Instant(Gens/S3) Air Chakra Dash
	inline bool enableFastACD = 1;
	inline bool enableInstantACD = 0;

	//Storm Generations Air Back Spark Function
	inline bool enableABCDSpark = 1;

	//Backdash Priority Function
	inline bool enableDashPriority = 1;
	
	//Rev Ninja Move Function
	inline bool enableRevNM = 1;
	inline bool enableRevNMK = 1;

	//Cover Fire Chakra Shuriken
	inline bool enableCFCS = 1;
	
	//Guard to Item Cancel
	inline bool enableGTI = 1;

	//Switch Priorities
	inline bool enableTiltSwitch = 1;
	inline bool enableGrabSwitch = 1;
	inline bool enableShurikenSwitch = 1;
	inline bool enableChakraShurikenSwitch = 1;

	//Six Paths Madara Awakening Crash Fix
	inline __int64 limboCloneAddr;

	class functions {
	public:
		static __int64 __fastcall canYouShuriken(__int64 a1);
		static __int64 __fastcall newPlayerState(__int64 a1, unsigned int a2, int a3, int a4);
		static __int64 __fastcall newPlayerAnim(__int64 rcx, int a1, __int64 a2, unsigned int a3, float a4, int a5, int a6);
		static void setNoChakraCirclePlayerState(__int64 a1);
		static __int64 __fastcall setMultiInputPlayerState(__int64 a1, float a2);
		static int itemState(__int64 a1, unsigned int a2);
		static __int64 areYouComboing(__int64 playerAddr, unsigned int playerState, unsigned int a3);
		static __int64 movementChain(void* rcx, int a1, __int64 a2, __int64 a3);
		static __int64 __fastcall cdashState(void* rcx, __int64 a1, int a2, float a3);
		static int backACD(__int64 a1, int a2);
		static void __fastcall setDashPriority(__int64 a1, int a2);
		static int __fastcall writeSupportState(__int64 a1, unsigned int a2);
		static int __fastcall writeSwitchByte(__int64 a1);
		static int comboGuardBreak(__int64 a1, __int64 a2, __int64 a3, __int64 a4);
	};
}