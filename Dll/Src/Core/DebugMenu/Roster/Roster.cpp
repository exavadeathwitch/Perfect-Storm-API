#include "pch.hpp"

#include "Roster.hpp"

#include "Class/rostercoord.hpp"

#include "Core/DebugMenu/MenuMessage/MenuMessage.hpp"

void Roster::runMenu() {
		if (rosterrunning == 1 && leftaddr != NULL)
			R1 = *reinterpret_cast<rostercoord*>(this->leftaddr + 0xB4);
		if (rosterrunning == 1 && rightaddr != NULL)
			R2 = *reinterpret_cast<rostercoord*>(this->rightaddr + 0xB4);

		//ImGui::Text("Character Select Positions\n");
		//ImGui::SameLine(); widget::HelpMarker("Ctrl clicking a box will increase it by the ctrl click amount,\nregular click will do the same for the regular amount.");
		ImGui::Text((rostermessageset.getMessage(0).getconverted() + "\n").c_str());
		ImGui::SameLine(); widget::HelpMarker((rostermessageset.getMessage(1).getconverted()).c_str());

		ImGui::Text("\n");
		ImGui::Text((rostermessageset.getMessage(2).getconverted() + "\n").c_str());
		ImGui::InputFloat((rostermessageset.getMessage(3).getconverted()).c_str(), &this->click);
		ImGui::InputFloat((rostermessageset.getMessage(4).getconverted()).c_str(), &this->ctrlclick);
		ImGui::Text((rostermessageset.getMessage(5).getconverted() + "\n").c_str());
		ImGui::InputFloat((rostermessageset.getMessage(6).getconverted()).c_str(), &this->R1.x, click, ctrlclick);
		ImGui::InputFloat((rostermessageset.getMessage(7).getconverted()).c_str(), &this->R1.y, click, ctrlclick);
		ImGui::InputFloat((rostermessageset.getMessage(8).getconverted()).c_str(), &this->R1.z, click, ctrlclick);
		ImGui::InputFloat((rostermessageset.getMessage(9).getconverted()).c_str(), &this->R1.rot, click, ctrlclick);
		ImGui::InputFloat((rostermessageset.getMessage(10).getconverted()).c_str(), &this->R1.lightinga, click, ctrlclick);
		ImGui::InputFloat((rostermessageset.getMessage(11).getconverted()).c_str(), &this->R1.lightingb, click, ctrlclick);
		ImGui::InputFloat((rostermessageset.getMessage(12).getconverted()).c_str(), &this->R1.lightingc, click, ctrlclick);
		ImGui::Text((rostermessageset.getMessage(13).getconverted() + "\n").c_str());
		ImGui::InputFloat((rostermessageset.getMessage(6).getconverted() + " ").c_str(), &this->R2.x, click, ctrlclick);
		ImGui::InputFloat((rostermessageset.getMessage(7).getconverted() + " ").c_str(), &this->R2.y, click, ctrlclick);
		ImGui::InputFloat((rostermessageset.getMessage(8).getconverted() + " ").c_str(), &this->R2.z, click, ctrlclick);
		ImGui::InputFloat((rostermessageset.getMessage(9).getconverted() + " ").c_str(), &this->R2.rot, click, ctrlclick);
		ImGui::InputFloat((rostermessageset.getMessage(10).getconverted() + " ").c_str(), &this->R2.lightinga, click, ctrlclick);
		ImGui::InputFloat((rostermessageset.getMessage(11).getconverted() + " ").c_str(), &this->R2.lightingb, click, ctrlclick);
		ImGui::InputFloat((rostermessageset.getMessage(12).getconverted() + " ").c_str(), &this->R2.lightingc, click, ctrlclick);
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
	*(float*)(baseaddr + 0x1C) = newcoord.y;
	*(float*)(baseaddr + 0x20) = newcoord.z;
	*(float*)(baseaddr + 0x28) = newcoord.rot;
}