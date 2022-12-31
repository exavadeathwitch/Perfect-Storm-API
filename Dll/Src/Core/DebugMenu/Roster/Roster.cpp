#include "pch.hpp"

#include "Roster.hpp"

#include "Class/rostercoord.hpp"
void Roster::runMenu() {
		if (rosterrunning == 1 && leftaddr != NULL)
			R1 = *reinterpret_cast<rostercoord*>(this->leftaddr + 0xB4);
		if (rosterrunning == 1 && rightaddr != NULL)
			R2 = *reinterpret_cast<rostercoord*>(this->rightaddr + 0xB4);

		ImGui::Text("Character Select Positions\n");
		ImGui::SameLine(); widget::HelpMarker("Ctrl clicking a box will increase it by the ctrl click amount,\nregular click will do the same for the regular amount.");


		ImGui::Text("\n");
		ImGui::Text("Modifiers\n");
		ImGui::InputFloat("Regular Click", &this->click);
		ImGui::InputFloat("Ctrl Click", &this->ctrlclick);
		ImGui::Text("Left Side\n");
		ImGui::InputFloat("X Position", &this->R1.x, click, ctrlclick);
		ImGui::InputFloat("Y Position", &this->R1.y, click, ctrlclick);
		ImGui::InputFloat("Z Position", &this->R1.z, click, ctrlclick);
		ImGui::InputFloat("Rotation", &this->R1.rot, click, ctrlclick);
		ImGui::InputFloat("Lighting A", &this->R1.lightinga, click, ctrlclick);
		ImGui::InputFloat("Lighting B", &this->R1.lightingb, click, ctrlclick);
		ImGui::InputFloat("Lighting C", &this->R1.lightingc, click, ctrlclick);
		ImGui::Text("Right Side\n");
		ImGui::InputFloat("X Position ", &this->R2.x, click, ctrlclick);
		ImGui::InputFloat("Y Position ", &this->R2.y, click, ctrlclick);
		ImGui::InputFloat("Z Position ", &this->R2.z, click, ctrlclick);
		ImGui::InputFloat("Rotation ", &this->R2.rot, click, ctrlclick);
		ImGui::InputFloat("Lighting A ", &this->R2.lightinga, click, ctrlclick);
		ImGui::InputFloat("Lighting B ", &this->R2.lightingb, click, ctrlclick);
		ImGui::InputFloat("Lighting C ", &this->R2.lightingc, click, ctrlclick);
		if (rosterrunning != 1)
			return;
		if (leftaddr != NULL)
			modrostercoord(this->leftaddr, this->R1);
		if (rightaddr != NULL)
			modrostercoord(this->rightaddr, this->R2);
}

void Roster::modrostercoord(__int64 old, rostercoord newcoord) {
	__int64 baseaddr = old + 0xB4;
	*(float*)(baseaddr) = newcoord.lightinga;
	*(float*)(baseaddr + 0x4) = newcoord.lightingb;
	*(float*)(baseaddr + 0x8) = newcoord.lightingc;
	*(float*)(baseaddr + 0x18) = newcoord.x;
	*(float*)(baseaddr + 0x1C) = newcoord.z;
	*(float*)(baseaddr + 0x20) = newcoord.y;
	*(float*)(baseaddr + 0x28) = newcoord.rot;
}