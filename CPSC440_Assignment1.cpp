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


}

void *timer(ALLEGRO_THREAD *ptr, void *arg) {
	return(0);
}

void *playerInput(ALLEGRO_THREAD *ptr, void *arg) {
	return(0);
}