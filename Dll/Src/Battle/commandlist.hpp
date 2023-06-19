#pragma once

#include "pch.hpp"
#include <sys/types.h>
#include <sys/stat.h>
namespace commandlist {
	inline int customCLRun = 0;
	inline int combos = 0;
	inline int type = 0;
	std::string kgy = "5kgy";
	class functions {
	public:
		static __int64 __fastcall ccUiGetMessage(__int64 MessageToDecode);
		static int __fastcall sub_140654FD8(__int64 a1, int* a2, const char* a3, int a4);
		static __int64 __fastcall sub_140654848(__int64 a1);
		static __int64 __fastcall ccGetCharCode(__int64 a1, int a2);
		static __int64* __fastcall strcpy(void* Dst, char* Src, size_t Size);
		static __int64 __fastcall ccReplaceStringTag(__int64* Src, char* a2, char* a3);
	};
	class character {
	public:
		std::string name;
		std::string awaname = "";
		std::string charcode;
		std::string path;
		std::string clnames[20];
		std::string cldesc[20];
		std::string clanames[20];
		std::string cladesc[20];
		int clsize = 0;
		int clasize = 0;
		std::vector<std::string> Messages;
		std::vector<std::string> aMessages;
		int index = 0;
		int aindex = 0;
		int awake = 0;
		character() {
		};
		character(std::string charcode) {
			this->charcode = charcode;
			this->path = ".\\Perfect Storm\\character\\" + charcode;
		}
		bool isvalid() {
			std::ifstream g((path + "\\name.char").c_str());
			return g.good();
		}
		void readcombofile() {
			clsize = 0;
			std::ifstream y((path + "\\combos.char").c_str());
			if (y.good() == false)
				return;
			std::ifstream f;
			f.open(path + "\\combos.char");

			std::string actual = "";
			while (!f.eof())
			{
				char a = f.get();

				if (a != 0x00)
				{
					actual = actual + a;
				}
				else
				{
					Messages.push_back(actual);
					actual = "";
				}
			}
			f.close();
			for (int x = 0; x + 1 < Messages.size(); x = x + 2)
			{
				this->clnames[clsize] = (Messages[x]);
				this->cldesc[clsize] = (Messages[x + 1]);
				clsize++;
			}
		}
		void readacombofile() {
			clasize = 0;
			std::ifstream y((path + "\\awacombos.char").c_str());
			if (y.good() == false)
				return;
			std::ifstream e;
			e.open(path + "\\awacombos.char");

			std::string actual = "";
			while (!e.eof())
			{
				char a = e.get();

				if (a != 0x00)
				{
					actual = actual + a;
				}
				else
				{
					aMessages.push_back(actual);
					actual = "";
				}
			}
			e.close();
			for (int x = 0; x + 1 < aMessages.size(); x = x + 2)
			{
				this->clanames[clasize] = (aMessages[x]);
				this->cladesc[clasize] = (aMessages[x + 1]);
				clasize++;
			}
		}
		void readnamefile() {
			std::ifstream f;
			f.open(path + "\\name.char");

			std::vector<std::string> Messages;
			std::string actual = "";
			while (!f.eof())
			{
				char a = f.get();

				if (a != 0x00)
				{
					actual = actual + a;
				}
				else
				{
					Messages.push_back(actual);
					actual = "";
				}
			}
			f.close();
			this->name = Messages[0];
		}
		void readawakenamefile() {
			std::ifstream y((path + "\\awakening.char").c_str());
			if (y.good() == false) {
				this->awaname = this->name;
				return;
			}
			std::ifstream f;
			f.open(path + "\\awakening.char");

			std::vector<std::string> Messages;
			std::string actual = "";
			while (!f.eof())
			{
				char a = f.get();

				if (a != 0x00)
				{
					actual = actual + a;
				}
				else
				{
					Messages.push_back(actual);
					actual = "";
				}
			}
			f.close();
			this->awaname = Messages[0];
		}
	};
}