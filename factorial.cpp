#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

int factorial(int n)
{
	if(n == 0) return 1;
	return n * factorial(n-1);
}

int main()
{
	int n=5;
	pid_t pid = fork();
	if(pid == 0)
	{
		int result = factorial(n);
		exit(result);
	}
	else if(pid > 0)
	{
		int status;
		wait(&status);
		if(WIFEXITED(status))
		{
			int result = WEXITSTATUS(status);
			cout<<"Factorial("<<n<<") = "<<result<<endl;
		}
	}
	else
	{
		cerr<<"Fork failed\n";
		return 1;
	}
	return 0;
}
