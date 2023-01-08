#pragma once

#include "pch.hpp"

#include "Class/message.hpp"

#include "Util/Util.hpp"

#include "json/single_include/json.hpp"

#include "Core/DebugMenu/DebugMenu.hpp"
using json = nlohmann::json;
class Language
{
	public:
		static void setgLanguages(std::vector<Language> set) {
			std::string path = util::getModPath().generic_string() + "\\message\\";
			std::replace(path.begin(), path.end(), '/', '\\');
			for (auto& p : std::filesystem::recursive_directory_iterator(path)) {
				if (p.is_directory()) {
					int languageindex = 0;
					for (int x = 0; x < size(set); x++) {
						if (set[x].type == p.path().filename().string())
							languageindex = x;
					}
					set[languageindex].clearmessages();
					std::string folder = path + p.path().filename().string();
					std::ifstream f((folder + "\\language.json"));
					if (f.good()) {
						std::ifstream MyFile(folder + "\\language.json");
						json data = json::parse(f);
						for (auto it = data.begin(); it != data.end(); ++it) {
							set[languageindex].addmessage(message(it.key(), it.value()));
						}
					MyFile.close();
					}
				}
			}
		}
		Language(std::string type) {
			this->type = type;
		}
		Language() {}
		std::string gettype() {
			return this->type;
		}
		void settype(std::string type) {
			this->type = type;
		}
		void clearmessages() {
			messages.clear();
		}
		message getmessage(int index) {
			return this->messages[index];
		}
		void addmessage(message newmessage) {
			this->messages.push_back(newmessage);
		}
		int messagesSize() {
			return this->messages.size();
		}
		std::string getmessageconversion(std::string original) {
			for (int x = 0; x < this->messages.size(); x++) {
				if (this->messages[x].getoriginal() == original)
					return this->messages[x].getconverted();
			}
			return "translation not found";
		}
	private:
		std::string type;
		std::vector<message> messages;
};

inline Language Arabic = Language("Arabic");
inline Language ChineseT = Language("Chinese(Traditional)");
inline Language English = Language("English");
inline Language French = Language("French");
inline Language German = Language("German");
inline Language Italian = Language("Italian");
inline Language Japanese = Language("Japanese");
inline Language Korean = Language("Korean");
inline Language Polish = Language("Polish");
inline Language Portuguese = Language("Portuguese");
inline Language Russian = Language("Russian");
inline Language Spanish = Language("Spanish");
inline Language Thai = Language("Thai");

class LanguageSet {
public:
	LanguageSet() {}
	void setLanguages() {
		for (int x = 0; x < this->set.size(); x++)
			set[x].clearmessages();
		std::string path = util::getModPath().generic_string() + "\\message\\";
		std::replace(path.begin(), path.end(), '/', '\\');
		for (auto& p : std::filesystem::recursive_directory_iterator(path)) {
			if (p.is_directory()) {
				int languageindex = 0;
				for (int x = 0; x < size(set); x++) {
					if (set[x].gettype() == p.path().filename().string())
						languageindex = x;
				}
				std::string folder = path + p.path().filename().string();
				std::ifstream f((folder + "\\language.json"));
				if (f.good()) {
					std::ifstream MyFile(folder + "\\language.json");
					json data = json::parse(f);
					for (auto it = data.begin(); it != data.end(); ++it) {
						this->set[languageindex].addmessage(message(it.key(), std::string(it.value())));
					}
					MyFile.close();
				}
			}
		}
	}
	std::string getTranslation(std::string input) {
		std::string currentlang = c.langarr[c.lang];
		int languageindex = 0;
		for (int x = 0; x < this->set.size(); x++) {
			if (this->set[x].gettype() == currentlang)
				languageindex = x;
		}
		return this->set[languageindex].getmessageconversion(input);
	}
private:
	std::vector<Language> set = { Arabic, ChineseT, English, French, German, Italian, Japanese, Korean, Polish, Portuguese, Russian, Spanish, Thai };
};

inline LanguageSet menuSet = LanguageSet();

inline Language gArabic = Language("Arabic");
inline Language gChineseT = Language("Chinese(Traditional)");
inline Language gEnglish = Language("Englishg");
inline Language gFrench = Language("French");
inline Language gGerman = Language("German");
inline Language gItalian = Language("Italian");
inline Language gJapanese = Language("Japanese");
inline Language gKorean = Language("Korean");
inline Language gPolish = Language("Polish");
inline Language gPortuguese = Language("Portuguese");
inline Language gRussian = Language("Russian");
inline Language gSpanish = Language("Spanish");
inline Language gThai = Language("Thai");

inline std::vector<Language> languages = { Arabic, ChineseT, English, French, German, Italian, Japanese, Korean, Polish, Portuguese, Russian, Spanish, Thai };
inline std::vector<Language> glanguages = { gArabic, gChineseT, gEnglish, gFrench, gGerman, gItalian, gJapanese, gKorean, gPolish, gPortuguese, gRussian, gSpanish, gThai };