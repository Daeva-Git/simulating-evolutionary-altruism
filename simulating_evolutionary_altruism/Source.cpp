#include <iostream>

int startTime;
int main()
{
	startTime = time(NULL);

	std::cout << "Hello, World!" << std::endl;
	return 0;
}

void simulate(int numofSteps, int maxTime) {
	int* time = new int[numofSteps + 1];
	int* observables = new int[numofSteps + 1];



	delete[] time;
}