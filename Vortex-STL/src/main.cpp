#include "stack_vector.h"
#include "stack_array.h"

#include <iostream>
#include <vector>
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

void PushBackTest()
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
}

void InitializerListTest()
{
	std::cout << "TEST: vstl::stack_vector<>::stack_vector(std::initializer_list const&)\n\n";

	vstl::stack_vector<int> vector = { 10, 20, 30, 40, 50, 60, 70, 80, 90, 100 };
	for (auto it = vector.crbegin(); it != vector.crend(); it++)
	{
		std::cout << *it << '\n';
	}
}

void StructTest()
{
	struct Data
	{
		float A, B, C;
	};

	vstl::stack_vector<Data> vector(3, Data{ 1, 1, 1 });

	for (const auto& data : vector)
	{
		std::cout << data.A << ", " << data.B << ", " << data.C << '\n';
	}
}

int main()
{
	PushBackTest();
	std::cout << std::endl;
	InitializerListTest();
	std::cout << std::endl;
	StructTest();
	std::cout << std::endl;

	vstl::stack_array<int, 3> arr(1);

	std::cin.get();
	return 0;
}
