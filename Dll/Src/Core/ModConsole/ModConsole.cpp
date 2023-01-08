#include "pch.hpp"

#include "ModConsole.hpp"

#include "imgui/include/imgui.h"

namespace console {
	void Console::render() {
		showConsole(&this->m_ShouldRender);
		return;
	}
    void Console::changeRender() {
        if (m_ShouldRender == false)
            m_ShouldRender = true;
        else
            m_ShouldRender = false;
    }
}