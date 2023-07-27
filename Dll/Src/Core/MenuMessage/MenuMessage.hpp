#pragma once

#include "pch.hpp"

#include "Core/Language/Language.hpp"

#include "Core/Settings/Settings.hpp"

#include "Core/Globals.hpp"
class MenuMessage
{
	public:
		bool convertmessages = false;
		MenuMessage(std::string original) {
			this->original = original;
			this->converted;
		}
		MenuMessage() {
			this->original = "";
			this->converted = "";
		}
		std::string getoriginal() {
			return this->original;
		}
		std::string getconverted() {
			if (!convertmessages)
				return this->original;
			if (this->converted.empty())
				this->converted = menuSet.getTranslation(this->original);
			return this->converted;
		}
		void setoriginal(std::string original) {
			this->original = original;
		}
		void setconverted(std::string converted) {
			this->converted = converted;
		}
		void loadconverted() {
			if (this->converted.empty())
				this->converted = menuSet.getTranslation(this->original);
		}
		void reconvert() {
			this->converted = "";
			this->converted = menuSet.getTranslation(this->original);
		}
	private:
		std::string original;
		std::string converted;
};

class messageset {
public:
	std::vector<MenuMessage> messages;
	unsigned int size = 0;
	bool convertmenumessages = true;
	messageset(std::vector<MenuMessage> m) {
		this->messages = m;
		size = m.size();
	};
	MenuMessage getMessage(int index) {
		return this->messages[index];
	}
	void translateAllMessages() {
		/*
		if (convertmenumessages) {
			for (int x = 0; x < messages.size(); x++) {
				this->messages[x].setconverted(messages[x].getoriginal());
			}
		}
		else {*/
			for (int x = 0; x < messages.size(); x++) {
				this->messages[x].reconvert();
			}
		//}
	}
	void clearAllMessages() {
		this->messages.clear();
	}
};

inline std::vector<MenuMessage> debugmessages = {
	MenuMessage("installedmods"),
	MenuMessage("settings"),
	MenuMessage("saveconfig"),
	MenuMessage("style"),
	MenuMessage("styledef"),
	MenuMessage("apiconsole"),
	MenuMessage("apiconsoledef"),
	MenuMessage("maxmods"),
	MenuMessage("maxmodsdef"),
	MenuMessage("mod"),
	MenuMessage("language"),
	MenuMessage("languagedef"),
	MenuMessage("convert"),
	MenuMessage("convertdef"),
	MenuMessage("1"),
	MenuMessage("2"),
	MenuMessage("3"),
	MenuMessage("4"),
	MenuMessage("5"),
	MenuMessage("6"),
	MenuMessage("7"),
	MenuMessage("8"),
	MenuMessage("9"),
	MenuMessage("10")
};

inline messageset debugmessageset = messageset(debugmessages);

static void translateAllSets() {
	menuSet.setLanguages();
	debugmessageset.translateAllMessages();
}