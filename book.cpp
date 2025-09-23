#include <iostream>
#include <pthread.h>
#include <unistd.h>
using namespace std;

pthread_mutex_t lock;
pthread_cond_t cond;
bool ticketsBooked = false;

void* friendThread(void* arg)
{
	int id = *((int*)arg);
	pthread_mutex_lock(&lock);
	while(!ticketsBooked)
	{
		cout<<"Friend "<<id<<": Are the tickets booked?\n";
		pthread_cond_wait(&cond, &lock);
	}
	cout<<"Friend "<<id<<": Yay!\n";
	pthread_mutex_unlock(&lock);
	return nullptr;
}
void* bookingThread(void* arg)
{
	cout<<"Booking thread: I wiil book tickets.\n";
	sleep(3);
	pthread_mutex_lock(&lock);
	ticketsBooked = true;
	cout<<"Booking thread: Tickets are booked!\n";
	pthread_cond_broadcast(&cond);
	pthread_mutex_unlock(&lock);
	return nullptr;
}

int main()
{
	pthread_t friends[5];
	pthread_t booker;
	int ids[5];
	for(int i=0; i<5; i++)
	{
		ids[i] = i+1;
		pthread_create(&friends[i], nullptr, friendThread, &ids[i]);
	}
	pthread_create(&booker, nullptr, bookingThread, nullptr);
	for(int i=0; i<5; i++)
	{
		pthread_join(friends[i], nullptr);
	}
	pthread_join(booker, nullptr);
	pthread_mutex_destroy(&lock);
	pthread_cond_destroy(&cond);
	return 0;
}
