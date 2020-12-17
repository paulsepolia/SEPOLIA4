#pragma once

#include <iostream>
#include <chrono>

namespace SEPOLIA4::UTILITIES
{
	class Clock final
	{
	public:

		Clock();

		Clock(const Clock&) = delete;

		Clock(Clock&&) = delete;

		Clock& operator=(const Clock&) = delete;

		Clock& operator=(Clock&&) = delete;

		void Start();

		double GetSecondsPassedSinceLastCall();

		[[nodiscard]] double GetSecondsPassedSinceStart() const;

		void Reset();

		void PrintTimeSinceLastCall();

		void PrintTimeTotal() const;

		~Clock();

	private:

		decltype(std::chrono::steady_clock::now()) tStart;
		decltype(std::chrono::steady_clock::now()) tPrev;
	};
}