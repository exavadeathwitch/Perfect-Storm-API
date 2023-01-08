#pragma once

#include "pch.hpp"

#include "texture/texture.hpp"

inline std::string controllerfilenames[21] = { "Base.png", "A.png", "B.png", "X.png", "Y.png", "L1.png", "R1.png", "L2.png", "R2.png", "Up.png", "Down.png", "Left.png", "Right.png", "Start.png", "Select.png", "LS.png", "RS.png", "1.png", "2.png", "3.png", "4.png"};

class controllertexture {
	public:
		controllertexture() {}
		controllertexture(std::vector<texture> textures, float analogmovement, std::string name) {
			this->textures = textures;
			this->analogmovement = analogmovement;
			this->name = name;
		}
		std::string getname() {
			return this->name;
		}
		void setanalogmovement(float analogmovement) {
			this->analogmovement = analogmovement;
		}
		void setname(std::string name) {
			this->name = name;
		}
		void addtexture(texture newtex) {
			this->textures.push_back(newtex);
		}
		int gettexturesize() {
			return textures.size();
		}
		texture gettexture(int index) {
			return this->textures[index];
		}
		float analogmovement;
		std::vector<texture> textures;
		std::string name;
};

inline texture basec = texture(0, 0, ".\\Perfect Storm\\ui\\controllerUI\\XSX\\Base.png", true);
inline texture A = texture(0, 0, ".\\Perfect Storm\\ui\\controllerUI\\XSX\\A.png", true);
inline texture B = texture(0, 0, ".\\Perfect Storm\\ui\\controllerUI\\XSX\\B.png", true);
inline texture X = texture(0, 0, ".\\Perfect Storm\\ui\\controllerUI\\XSX\\X.png", true);
inline texture Y = texture(0, 0, ".\\Perfect Storm\\ui\\controllerUI\\XSX\\Y.png", true);
inline texture L1 = texture(0, 0, ".\\Perfect Storm\\ui\\controllerUI\\XSX\\L1.png", true);
inline texture R1 = texture(0, 0, ".\\Perfect Storm\\ui\\controllerUI\\XSX\\R1.png", true);
inline texture L2 = texture(0, 0, ".\\Perfect Storm\\ui\\controllerUI\\XSX\\L2.png", true);
inline texture R2 = texture(0, 0, ".\\Perfect Storm\\ui\\controllerUI\\XSX\\R2.png", true);
inline texture Up = texture(0, 0, ".\\Perfect Storm\\ui\\controllerUI\\XSX\\Up.png", true);
inline texture Down = texture(0, 0, ".\\Perfect Storm\\ui\\controllerUI\\XSX\\Down.png", true);
inline texture Left = texture(0, 0, ".\\Perfect Storm\\ui\\controllerUI\\XSX\\Left.png", true);
inline texture Right = texture(0, 0, ".\\Perfect Storm\\ui\\controllerUI\\XSX\\Right.png", true);
inline texture Start = texture(0, 0, ".\\Perfect Storm\\ui\\controllerUI\\XSX\\Start.png", true);
inline texture Select = texture(0, 0, ".\\Perfect Storm\\ui\\controllerUI\\XSX\\Select.png", true);
inline texture LS = texture(0, 0, ".\\Perfect Storm\\ui\\controllerUI\\XSX\\LS.png", true);
inline texture RS = texture(0, 0, ".\\Perfect Storm\\ui\\controllerUI\\XSX\\RS.png", true);
inline std::vector<texture> textures = { basec, A, B, X, Y, L1, R1, L2, R2, Up, Down, Left, Right, Start, Select, LS, RS};
//16384, 4096, 32768, 8192, AYXB
//16, 32, 64, 128 Up, Right, Down, Left
//1, 8 Select, Start
//256, 512, 1024, 2048 L2, R2, L1, R1
