#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include "TemplatedVector.h"

TemplatedVector<int> vector;

void testVector() {
	std::vector<std::thread> threads;
	int threadsSize = 40000;

	for (int i = 0; i < threadsSize; ++i)
	{
		threads.push_back(std::thread(&TemplatedVector<int>::push, &vector, 13));
		if (i == 2000) {
			threads.push_back(std::thread(&TemplatedVector<int>::clear, &vector));

		}
	}

	for (int i = 0; i < threads.size(); ++i)
	{
		threads[i].join();
	}
}

int main() {
	std::cout << "Starting" << std::endl;

	testVector();

	int tamVector = vector.size();
	for (size_t i = 0; i < tamVector; i++)
	{
		if (vector.at(i) != 13) {
			std::cout << "FAIL " << i << std::endl;
		}
	}

	std::cout << vector[1] << std::endl;
	//std::cout << "size vector "<< tamVector << std::endl;
	std::cout << "Ended" << std::endl;
	getchar();
	return 0;
}