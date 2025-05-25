#include <allegro5/allegro.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void *timer(ALLEGRO_THREAD *ptr, void *arg);

void *guessGame(ALLEGRO_THREAD *ptr, void *arg);

std::string scramble(std::string word);

bool gameComplete = false;
bool timerComplete = false;
int level;

int main()
{

	/*
	* Read dictionary and assign words to difficulty level
	* words[0] is for words of length 4-5
	* words[1] is for length 6-7
	* words[2] is for length 8+
	*/
	std::vector<std::string> words[3];

	std::string inputLine;
	int inputLength;

	std::ifstream inputFile("dictionary.txt");

	while (getline(inputFile, inputLine)) {
		inputLength = inputLine.length();
		if (inputLength < 4) {
			//Do nothing since words must be length 4 or more
		}
		else if (inputLength < 6) {
			words[0].push_back(inputLine);
		}
		else if (inputLength < 8) {
			words[1].push_back(inputLine);
		}
		else {
			words[2].push_back(inputLine);
		}
	}

	ALLEGRO_THREAD *timerThread = NULL, *gameThread = NULL;

	timerThread = al_create_thread(timer, NULL);
	gameThread = al_create_thread(guessGame, words);

	while (!gameComplete && !timerComplete) {
		if (!gameComplete && !timerComplete) {
			al_start_thread(timerThread);

			al_start_thread(gameThread);
		}
		else {
			al_destroy_thread(timerThread);

			al_destroy_thread(gameThread);
		}
	}

	//Give game over message based on how many levels player completed.
	if (level < 2) {
		std::cout << "\nGame Over\nTry better next time.\n";
	}
	if (level == 2) {
		std::cout << "\nGame Over\nYou unscrambled 2 words.\nYou are of average intelligence.";
	}
	if (level == 3) {
		std::cout << "\nGame Over\nYou unscrambled 3 words.\nYou're pretty smart!\n";
	}
	if (level == 4) {
		std::cout << "\nGame Over\nYou unscrambled 4 words.\nYou're super smart!\n";
	}
	if (level == 5) {
		std::cout << "\neGame Over\nYou unscrambled all 5 word.\nYou're the smartest person ever!\n";
	}
}

void *timer(ALLEGRO_THREAD *ptr, void *arg) {
	time_t startTime, currentTime;
	startTime = time(NULL);
	currentTime = time(NULL);

	while (currentTime - startTime < 60 && !gameComplete) {
		currentTime = time(NULL);
	}
	gameComplete = true;

	return(NULL);
}

void *guessGame(ALLEGRO_THREAD *ptr, void *arg) {
	std::string unscrambled;
	std::string scrambled;
	std::string guess;
	std::vector<std::string> *words = static_cast<std::vector<std::string>*>(arg);
	int randIndex;
	
	level = 0;
	srand(time(0));

	while (level < 5) {
		//get a random word based on current level
		if (level < 2) {
			randIndex = rand() % words[0].size();
			unscrambled = words[0][randIndex];

			//Remove word from list of possible words for future passes
			words[0].erase(words[0].begin() + randIndex);
		}
		else if (level < 4) {
			randIndex = rand() % words[1].size();
			unscrambled = words[1][randIndex];

			//Remove word from list of possible words for future passes
			words[1].erase(words[1].begin() + randIndex);
		}
		else {
			randIndex = rand() % words[2].size();
			unscrambled = words[2][randIndex];

			//Remove word from list of possible words for future passes
			words[2].erase(words[2].begin() + randIndex);
		}

		//scramble the word and ensure that don't scramble into the same word
		scrambled = unscrambled;
		while (scrambled.compare(unscrambled) == 0) {
			scrambled = scramble(unscrambled);
		}

		std::cout << scrambled << "\n";
		//Allow player to guess word
		while (true) {
			std::cin >> guess;

			if (unscrambled.compare(guess) == 0) {
				std::cout << "Correct!\n";
				level++;
				break;
			}
			else {
				std::cout << "Incorrect, try again.\n";
			}
		}
	}

	gameComplete = true;

	return(NULL);
}

std::string scramble(std::string word) {
	int length = word.length();
	int randIndex;
	char tmpChar;

	for (int i = length - 1; i >= 1; i--) {
		randIndex = rand() % (i + 1);
		tmpChar = word[i];
		word[i] = word[randIndex];
		word[randIndex] = tmpChar;
	}

	return(word);

}