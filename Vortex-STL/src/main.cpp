#include "Vector.h"
#include <vector>

#include <iostream>
#include <chrono>

struct Timer
{
	Timer(const std::string& name)
	{
		Start = std::chrono::high_resolution_clock::now();
		Name = name;
	}

	auto Elapsed() const { return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - Start); }

	~Timer()
	{
		std::cout << Name << ": " << Elapsed() << " microseconds\n";
	}

	std::chrono::steady_clock::time_point Start;
	std::string Name;
};

int main()
{
	std::chrono::microseconds time1;
	std::chrono::microseconds time2;

	std::cout << "TEST: vstl::stack_vector<>::PushBack\n\n";

	{
		Timer timer("vstl::stack_vector<>::PushBack");
		vstl::stack_vector<int> vector;
		for (uint32_t i = 0; i < 1'000'000; i++)
			vector.PushBack(i);
		time1 = timer.Elapsed();
	}

	{
		Timer timer("std::vector<>::push_back");
		std::vector<int> vector;
		for (uint32_t i = 0; i < 1'000'000; i++)
			vector.push_back(i);
		time2 = timer.Elapsed();
	}

	auto result1 = (double)(time2 / time1) * 100;
	auto result2 = (double)(time1 / time2) * 100;
	std::cout << std::endl << "Performance Results:\n";
	std::cout << "vstl::stack_vector<>::PushBack was " << result1 << "% " << (result1 > result2 ? "faster" : "slower") << '\n';
	std::cout << "std::vector<>::push_back was " << result2 << "% " << (result2 > result1 ? "faster" : "slower") << '\n';

	std::cin.get();
}