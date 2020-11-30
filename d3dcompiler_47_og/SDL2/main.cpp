#include "SDL2SoundEffects.h"
#include <iostream>
#include "SDL2Music.h"
int main()
	{
	SDL2SoundEffects se;
	se.addSoundEffect("./Laugh.wav");
	se.addSoundEffect("./JC.wav");
	se.addSoundEffect("./Level 3.wav");

	SDL2Music music;
	music.addMusicTrack("./0000_title.wav");
	
	music.volume_Music();
	music.playMusicTrack(0);
	se.volume_SoundEffects();
	int choice = 0;
	while (choice != -1)
	{
		choice = 0;
		std::cout << "Which Sound Effect To Play? (enter -1 to exit)\n"
			<< "=>: ";
		std::cin >> choice;
		if (choice == -1)
			break;
		se.playSoundEffect(choice);
		std::cin.clear();
	}
		return 0;
	}
