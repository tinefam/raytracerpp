#pragma once

#include <chrono>
#include <iostream>
#include <format>
#include <string>
#include <thread>

class timer
{
public:
    timer(const std::string &label) : label(label)
    {
        start = std::chrono::steady_clock::now();
    }

    ~timer()
    {
        const auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> duration = end - start;
        std::clog << std::format("{}: {:.3f}s\n", label, duration.count());
    }

private:
    std::string label;

    std::chrono::time_point<std::chrono::steady_clock> start;
};

class thread_timer
{
public:
    thread_timer()
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

struct thread_timer_info
{
    std::thread::id id;
    double time;
};




