#pragma once

#include "pch.hpp"

#include "Core/Language/Language.hpp"

#include "Core/DebugMenu/Message/Message.hpp"

class MenuMessage
{
	public:
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
	messageset(std::vector<MenuMessage> m) {
		this->messages = m;
	};
	MenuMessage getMessage(int index) {
		return this->messages[index];
	}
	void translateAllMessages() {
		if (!m.showMenuGameMessages) {
			for (int x = 0; x < messages.size(); x++) {
				this->messages[x].setconverted(messages[x].getoriginal());
			}
		}
		else {
			for (int x = 0; x < messages.size(); x++) {
				this->messages[x].reconvert();
			}
		}
	}
	void clearAllMessages() {
		this->messages.clear();
	}
	private:
		std::vector<MenuMessage> messages;
};

inline std::vector<MenuMessage> debugmessages = {
	MenuMessage("debugtitle0"),
	MenuMessage("debugtitle1"),
	MenuMessage("debugtitle2")
};

inline std::vector<MenuMessage> rostermessages = {
	MenuMessage("rostertitle"),
	MenuMessage("rostertitledesc"),
	MenuMessage("modifiers"),
	MenuMessage("regclick"),
	MenuMessage("ctrlclick"),
	MenuMessage("lside"),
	MenuMessage("xpos"),
	MenuMessage("ypos"),
	MenuMessage("zpos"),
	MenuMessage("rot"),
	MenuMessage("lighta"),
	MenuMessage("lightb"),
	MenuMessage("lightc"),
	MenuMessage("rside")
};

inline std::vector<MenuMessage> gamespeedmessages = {
	MenuMessage("fssliderdef"),
	MenuMessage("enablefs"),
	MenuMessage("enablefsdef"),
	MenuMessage("gsnumframes"),
	MenuMessage("gsnumframesdef"),
	MenuMessage("gsstep"),
	MenuMessage("gsframe"),
	MenuMessage("fsdef")
};

inline std::vector<MenuMessage> rendermessages = {
	MenuMessage("renderlayer"),
	MenuMessage("renderlayerdef"),
	MenuMessage("hudrenderdef"),
};

inline std::vector<MenuMessage> consolemessages = {
	MenuMessage("consoleinput"),
	MenuMessage("consoleclear")
};

inline std::vector<MenuMessage> messagemessages = {
	MenuMessage("showConvertedGameMessages"),
	MenuMessage("showConvertedGameMessagesdef"),
	MenuMessage("showMenuGameMessages"),
	MenuMessage("showMenuGameMessagesdef"),
	MenuMessage("getConvertedGameMessage"),
	MenuMessage("getConvertedGameMessagedef")
};

inline messageset debugmessageset = messageset(debugmessages);
inline messageset rostermessageset = messageset(rostermessages);
inline messageset gamespeedmessageset = messageset(gamespeedmessages);
inline messageset rendermessageset = messageset(rendermessages);
inline messageset consolemessageset = messageset(consolemessages);
inline messageset messagemessageset = messageset(messagemessages);

static void translateAllSets() {
	menuSet.setLanguages();
	debugmessageset.translateAllMessages();
	rostermessageset.translateAllMessages();
	gamespeedmessageset.translateAllMessages();
	rendermessageset.translateAllMessages();
	consolemessageset.translateAllMessages();
	messagemessageset.translateAllMessages();
}