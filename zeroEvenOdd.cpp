#include <iostream>
#include <unistd.h>
#include <pthread.h>
using namespace std;

pthread_mutex_t lock;
pthread_cond_t cond;
int n = 5;
int current = 1;
bool printZero = true;

void* zeroThread(void* arg)
{
	for(int i=0; i<n; i++)
	{
		pthread_mutex_lock(&lock);
		while(!printZero)
		{
			pthread_cond_wait(&cond, &lock);
		}
		cout<<0;
		printZero = false;
		pthread_cond_broadcast(&cond);
		pthread_mutex_unlock(&lock);
	}
	return nullptr;
}
void* evenThread(void* arg)
{
	while(true)
	{
		pthread_mutex_lock(&lock);
		while(printZero || current%2 != 0)
		{
			if(current > n)
			{
				pthread_mutex_unlock(&lock);
				return nullptr;
			}
			pthread_cond_wait(&cond, &lock);
		}
		if(current > n)
		{
			pthread_mutex_unlock(&lock);
			return nullptr;
		}	
		cout<<"\033[1;3;92m"<<current++<<"\033[0m";
		printZero = true;
		pthread_cond_broadcast(&cond);
		pthread_mutex_unlock(&lock);
	}
}
void* oddThread(void* arg)
{
	while(true)
	{
		pthread_mutex_lock(&lock);
		while(printZero || current%2 != 1)
		{
			if(current > n)
			{
				pthread_mutex_unlock(&lock);
				return nullptr;
			}
			pthread_cond_wait(&cond, &lock);
		}
		if(current > n)
		{
			pthread_mutex_unlock(&lock);
			return nullptr;
		}
		cout<<"\033[1;3;91m"<<current++<<"\033[0m";
		printZero = true;
		pthread_cond_broadcast(&cond);
		pthread_mutex_unlock(&lock);
	}
}

int main()
{
	pthread_t tZero, tEven, tOdd;
	pthread_create(&tZero, nullptr, zeroThread, nullptr);
	pthread_create(&tEven, nullptr, evenThread, nullptr);
	pthread_create(&tOdd, nullptr, oddThread, nullptr);
	pthread_join(tZero, nullptr);
	pthread_join(tEven, nullptr);
	pthread_join(tOdd, nullptr);
	cout<<endl;
	pthread_mutex_destroy(&lock);
	pthread_cond_destroy(&cond);
	return 0;
}
