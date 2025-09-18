#include <iostream>
#include <pthread.h>
#include <unistd.h>

using namespace std;

int counter = 0;
pthread_mutex_t lock;

void* increment(void* arg)
{
	for(int i=0; i<100000; i++)
	{
		pthread_mutex_lock(&lock);
		counter++;
		pthread_mutex_unlock(&lock);
	}
	return nullptr;
}
void* decrement(void* arg)
{
	for(int i=0; i<100000; i++)
	{
		pthread_mutex_lock(&lock);
		counter--;
		pthread_mutex_unlock(&lock);
	}
	return nullptr;
}

int main()
{
	pthread_t t1, t2, t3, t4;
	pthread_mutex_init(&lock, nullptr);
	pthread_create(&t1, nullptr, increment, nullptr);
	pthread_create(&t2, nullptr, increment, nullptr);
	pthread_create(&t3, nullptr, decrement, nullptr);
	pthread_create(&t4, nullptr, decrement, nullptr);
	pthread_join(t1, nullptr);
	pthread_join(t2, nullptr);
	pthread_join(t3, nullptr);
	pthread_join(t4, nullptr);
	pthread_mutex_destroy(&lock);
	cout<<"Counter value: "<<counter<<endl;
	return 0;
}
