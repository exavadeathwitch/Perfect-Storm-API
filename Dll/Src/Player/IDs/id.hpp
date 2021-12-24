#pragma once

namespace id {
	class functions {
	public:
		static bool isPuppetMaster(__int64 baseAddr);
		static bool isPartnerCharacter(__int64 baseAddr);
		static bool isCanGKunai(__int64 baseAddr);
		static bool isInGKunai(__int64 baseAddr);
		static __int64 getHealthAddr(__int64 baseAddr);
		static int awakeningType(__int64 baseAddr);
	};
}