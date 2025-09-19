#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

using namespace std;

int buffer;
pthread_mutex_t lock;
sem_t semEmpty;
sem_t semFull;

void* producer(void* arg)
{
	for(int i=1; i<=5; i++)
	{
		sem_wait(&semEmpty);
		pthread_mutex_lock(&lock);
		buffer = i;
		cout<<"Produced: "<<buffer<<endl;
		pthread_mutex_unlock(&lock);
		sem_post(&semFull);
		sleep(1);
	}
	return nullptr;
}
void* consumer(void* arg)
{
	for(int i=1; i<=5; i++)
	{
		sem_wait(&semFull);
		pthread_mutex_lock(&lock);
		int data = buffer;
		cout<<"Consumed: "<<data<<endl;
		pthread_mutex_unlock(&lock);
		sem_post(&semEmpty);
		sleep(2);
	}
	return nullptr;
}

int main()
{
	pthread_t prodThread, consThread;
	pthread_mutex_init(&lock, nullptr);
	sem_init(&semEmpty, 0, 1);
	sem_init(&semFull, 0, 0);
	pthread_create(&prodThread, nullptr, producer, nullptr);
	pthread_create(&consThread, nullptr, consumer, nullptr);
	pthread_join(prodThread, nullptr);
	pthread_join(consThread, nullptr);
	pthread_mutex_destroy(&lock);
	sem_destroy(&semEmpty);
	sem_destroy(&semFull);
	return 0;
}
