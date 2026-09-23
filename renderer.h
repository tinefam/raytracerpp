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
    world& world;
};
