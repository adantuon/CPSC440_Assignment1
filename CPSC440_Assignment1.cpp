#include <allegro5/allegro.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void *timer(ALLEGRO_THREAD *ptr, void *arg);

void *playerInput(ALLEGRO_THREAD *ptr, void *arg);

bool gameComplete = false;
bool timerComplete = false;

int main()
{

	//Read dictionarty and assign words to difficulty level
	std::vector<std::string> words4to5;
	std::vector<std::string> words6to7;
	std::vector<std::string> words8toInf;

	std::string inputLine;
	int inputLength;

	std::ifstream inputFile("dictionary.txt");

	while (getline(inputFile, inputLine)) {
		inputLength = inputLine.length();
		if (inputLength < 4) {
			//Do nothing since words must be length 4 or more
		}
		else if (inputLength < 6) {
			words4to5.push_back(inputLine);
		}
		else if (inputLength < 8) {
			words6to7.push_back(inputLine);
		}
		else {
			words8toInf.push_back(inputLine);
		}
	}

	ALLEGRO_THREAD *thread1 = NULL, *thread2 = NULL;

	thread1 = al_create_thread(timer, NULL);
	thread2 = al_create_thread(playerInput, NULL);

	while (!gameComplete && !timerComplete) {
		if (!gameComplete && !timerComplete) {
			al_start_thread(thread1);

			al_start_thread(thread2);
		}
		else {
			al_destroy_thread(thread1);

			al_destroy_thread(thread2);
		}
	}
}

void *timer(ALLEGRO_THREAD *ptr, void *arg) {
	time_t startTime, currentTime;
	startTime = time(NULL);
	currentTime = time(NULL);

	//TO DO: Change this to 60 seconds
	while (currentTime - startTime < 5 && !gameComplete) {
		currentTime = time(NULL);
	}
	gameComplete = true;

	return(NULL);
}

void *playerInput(ALLEGRO_THREAD *ptr, void *arg) {
	return(0);
}