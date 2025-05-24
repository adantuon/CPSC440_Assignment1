#include <allegro5/allegro.h>
#include <stdio.h>
#include <stdlib.h>

void *timer(ALLEGRO_THREAD *ptr, void *arg);

void *playerInput(ALLEGRO_THREAD *ptr, void *arg);

bool gameComplete = false;
bool timerComplete = false;

int main()
{
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