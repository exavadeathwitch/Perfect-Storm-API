#pragma once

#include "pch.hpp"

#include <string>

namespace Stage {
    inline std::string stageName;
    inline std::string fbStageName;
    class functions {
    public:
        static void getStageName(__int64 a1);
    };
}