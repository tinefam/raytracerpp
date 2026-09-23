#pragma once

#include <chrono>
#include <iostream>
#include <format>
#include <string>
#include <thread>

class Timer
{
public:
    Timer(const std::string &label) : label(label)
    {
        start = std::chrono::steady_clock::now();
    }

    ~Timer()
    {
        const auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> duration = end - start;
        std::clog << std::format("{}: {:.3f}s\n", label, duration.count());
    }

private:
    std::string label;

    std::chrono::time_point<std::chrono::steady_clock> start;
};

class ThreadTimer
{
public:
    ThreadTimer()
    {
        start = std::chrono::steady_clock::now();
    }

    double elapsed()
    {
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> duration = end - start;
        return duration.count();
    }

private:
    std::chrono::time_point<std::chrono::steady_clock> start;
};

struct ThreadTimerInfo
{
    std::thread::id id;
    double time;
};




