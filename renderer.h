#pragma once

#include <atomic>
#include <vector>
#include <thread>

#include "camera.h"
#include "color.h"
#include "hittable.h"
#include "timer.h"

class renderer
{
public:
    renderer(camera& cam, const hittable& world) : cam(cam), world(world) {};

    void render()
    {

    }

private:
    camera& cam;
    const hittable& world;

    std::vector<color> grid; // Temporary vector to print threaded pixel
    std::vector<ThreadTimerInfo> thread_timers; // Temporary vector to print thread timers

    std::atomic<unsigned int> scan_remaining; // Multithread remaining scans counter

    void division_thread()
    {

    }

    void thread_grid(int r_start, int r_end, int n)
    {

    }
};
