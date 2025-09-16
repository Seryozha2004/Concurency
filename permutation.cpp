#include <iostream>
#include <pthread.h>

using namespace std;

void* factorial(void* arg)
{
	int n = *((int*)arg);
	unsigned long long* result = new unsigned long long(1);
	for(int i=1; i<=n; i++)
	{
		*result *= i;
	}
	pthread_exit(result);
}

int main()
{
	int n, r;
	cout<<"n="; cin>>n;
	cout<<"r="; cin>>r;
	pthread_t t1, t2;
	pthread_create(&t1, nullptr, factorial, &n);
	int n_r = n-r;
	pthread_create(&t2, nullptr, factorial, &n_r);
	void* num_result;
	void* denom_result;
	pthread_join(t1, &num_result);
	pthread_join(t2, &denom_result);
	unsigned long long numerator = *((unsigned long long*)num_result);
	unsigned long long denominator = *((unsigned long long*)denom_result);
	unsigned long long permutation = numerator / denominator;
	cout<<"P("<<n<<", "<<r<<") = "<<permutation<<endl;
	delete (unsigned long long*)num_result;
	delete (unsigned long long*)denom_result;
	return 0;
}
