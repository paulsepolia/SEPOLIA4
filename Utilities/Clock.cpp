#include "Clock.h"

namespace SEPOLIA4::UTILITIES
{
	Clock::Clock() :
			tStart(std::chrono::steady_clock::now()),
			tPrev(std::chrono::steady_clock::now())
	{
		Start();
	}

	void Clock::Start()
	{
		tStart = std::chrono::steady_clock::now();
		tPrev = tStart;
	}

	double Clock::GetSecondsPassedSinceLastCall()
	{
		const auto tNow = std::chrono::steady_clock::now();
		const auto totalTime = std::chrono::duration_cast<std::chrono::duration<double>>(tNow - tPrev).count();
		tPrev = tNow;
		return totalTime;
	}

	[[nodiscard]] double Clock::GetSecondsPassedSinceStart() const
	{
		const auto tNow = std::chrono::steady_clock::now();
		const auto totalTime = std::chrono::duration_cast<std::chrono::duration<double>>(tNow - tStart).count();
		return totalTime;
	}

	void Clock::Reset()
	{
		tPrev = std::chrono::steady_clock::now();
		tStart = tPrev;
	}

	void Clock::PrintTimeSinceLastCall()
	{
		const auto tLoc = std::chrono::steady_clock::now();
		const auto totalTime = std::chrono::duration_cast<std::chrono::duration<double>>(tLoc - tPrev).count();
		tPrev = tLoc;
		std::cout << "Clock::PrintTimeSinceLastCall() --> time used (secs) = " << totalTime << std::endl;
	}

	void Clock::PrintTimeTotal() const
	{
		const auto tLoc = std::chrono::steady_clock::now();
		const auto totalTime = std::chrono::duration_cast<std::chrono::duration<double>>(tLoc - tStart).count();
		std::cout << "Clock::PrintTimeTotal() --> total time used (secs) = " << totalTime << std::endl;
	}

	Clock::~Clock()
	{
		const auto tLoc = std::chrono::steady_clock::now();
		const auto totalTime = std::chrono::duration_cast<std::chrono::duration<double>>(tLoc - tStart).count();
		std::cout << "Clock::~Clock(): total time used (secs) = " << totalTime << std::endl;
	}
}
