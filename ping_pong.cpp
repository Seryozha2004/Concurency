#include <iostream>
#include <unistd.h>
#include <pthread.h>
using namespace std;

int n;
int count = 0;
int pingTurn = 1;
pthread_mutex_t lock;
pthread_cond_t cond;

void* Ping(void* arg)
{
	while(true)
	{
		pthread_mutex_lock(&lock);
		while(!pingTurn && count<n)
		{
			pthread_cond_wait(&cond, &lock);
		}
		if(count >= n)
		{
			pthread_mutex_unlock(&lock);
			pthread_cond_signal(&cond);
			break;
		}
		sleep(1);
		cout<<"Ping"<<endl;
		pingTurn = 0;
		pthread_cond_signal(&cond);
		pthread_mutex_unlock(&lock);
	}
	return nullptr;
}
void* Pong(void* arg)
{
	while(true)
	{
		pthread_mutex_lock(&lock);
		while(pingTurn && count<n)
		{
			pthread_cond_wait(&cond, &lock);
		}
		if(count >= n)
		{
			pthread_mutex_unlock(&lock);
			pthread_cond_signal(&cond);
			break;
		}
		sleep(1);
		count++;
		cout<<"Pong"<<endl;
		pingTurn = 1;
		pthread_cond_signal(&cond);
		pthread_mutex_unlock(&lock);
	}
	return nullptr;
}

int main()
{
	cout<<"n="; cin>>n;
	pthread_t t1, t2;
	pthread_create(&t1, nullptr, Ping, nullptr);
	pthread_create(&t2, nullptr, Pong, nullptr);
	pthread_join(t1, nullptr);
	pthread_join(t2, nullptr);
	pthread_mutex_destroy(&lock);
	pthread_cond_destroy(&cond);
	return 0;
}
