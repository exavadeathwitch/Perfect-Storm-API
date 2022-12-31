#pragma once

#include "pch.hpp"
#include "texture/texture.hpp"
namespace ns4 {
	class controllerUI {
	public:
		static void controllerDisplay();
	};
}
inline texture base = texture(0, 0, ".\\Perfect Storm\\ui\\controllerUI\\XSX\\Base.png", true);
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
inline std::vector<texture> textures = { base, A, B, X, Y, L1, R1, L2, R2, Up, Down, Left, Right, Start, Select, LS, RS};
//16384, 4096, 32768, 8192, AYXB
//16, 32, 64, 128 Up, Right, Down, Left
//1, 8 Select, Start
//256, 512, 1024, 2048 L2, R2, L1, R1
inline std::vector<int> inputs = { NULL, 16384, 8192, 32768, 4096, 1024, 2048, 256, 512, 16, 64, 128, 32, 8, 1 };