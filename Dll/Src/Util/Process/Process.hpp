#pragma once

#include "Module.hpp"

namespace util::process {
	class Process {
	public:
		explicit Process(const std::string_view name) noexcept : m_name(name) {
			addModule(name);
		}

		void addModule(const std::string_view name) noexcept {
			m_Modules[name] = std::make_shared<Module>(name);
		}

		Module* getModule(const std::string_view name) noexcept {
			return m_Modules[name].get();
		}

		Module* getSelf() noexcept {
			return m_Modules[m_name].get();
		}
	private:
		std::string_view m_name;
		std::unordered_map<std::string_view, std::shared_ptr<Module>> m_Modules;
	};
}
