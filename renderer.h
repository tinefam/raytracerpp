#pragma once

#include <atomic>
#include <vector>
#include <thread>
#include <syncstream>

#include "camera.h"
#include "color.h"
#include "hittable.h"
#include "timer.h"
#include "stb_image_write.h"

inline unsigned int available_threads()
{
    const unsigned int threads = std::thread::hardware_concurrency();
    return threads < 1 ? 1 : threads;
}

class renderer
{
public:
    renderer(camera& cam, const hittable& world) : cam(cam), world(world) {};

    void render()
    {
        cam.initialize();

        timer t1("Rendering time");
        std::cout << "P3\n" << cam.image_width << ' ' << cam.image_height << "\n255\n";

        grid.resize(cam.image_width * cam.image_height);

        dispatch_thread_render();

        // PPM
        for (auto x : grid)
        {
            write_color_ppm(std::cout, x);
        }

        // PNG
        std::vector<unsigned char> pixels(cam.image_width * cam.image_height * 3);

        for (int i = 0; i < cam.image_width * cam.image_height; i++)
        {
            auto bytes = raw_color_bytes(grid[i]);
            pixels[3*i] = bytes[0];
            pixels[3*i+1] = bytes[1];
            pixels[3*i+2] = bytes[2];
        }

        stbi_write_png("output.png", cam.image_width, cam.image_height, 3, pixels.data(), cam.image_width * 3);

        std::clog << "\n";

        for (auto x : all_timers)
        {
            std::clog <<  std::format("Thread [ID: {}]: {:.3f}s\n", x.id, x.time);
        }

        std::clog << "\nDone.                     \n";
    }

private:
    camera& cam;
    const hittable& world;

    std::vector<color> grid; // Temporary vector to print threaded pixel
    std::vector<thread_timer_info> all_timers; // Temporary vector to print thread timers

    std::atomic<unsigned int> scan_remaining; // Multithread remaining scans counter

    void dispatch_thread_render()
    {
        scan_remaining = cam.image_height;

        auto num_threads = available_threads();

        all_timers.resize(num_threads);

        auto image_height_portion = int(cam.image_height / num_threads);

        auto extra_portion = cam.image_height % num_threads;

        int start = 0;

        std::vector<std::jthread> threads;

        for (int i = 0; i < num_threads - 1; i++)
        {
            threads.push_back(std::jthread(&renderer::render_scanlines, this, start, start + image_height_portion, i));
            start += image_height_portion;
        }
        threads.push_back(std::jthread(&renderer::render_scanlines, this, start, start + image_height_portion + extra_portion, num_threads - 1));
    }

    void render_scanlines(int r_start, int r_end, int n)
    {
        thread_timer time;

        for (; r_start < r_end; r_start++)
        {
            std::osyncstream(std::clog) << "\rScanlines remaining: " << scan_remaining << ' ' << std::flush;

            for (int i = 0; i < cam.image_width; i++)
            {
                color pixel_color(0,0,0);

                for (int sample = 0; sample < cam.samples_per_pixel; sample++)
                {
                    ray r = cam.get_ray(i, r_start);
                    pixel_color += ray_color(r, cam.max_depth);
                }

                grid[r_start * cam.image_width + i] = cam.pixel_samples_scale * pixel_color;
            }
            scan_remaining--;
        }
        all_timers[n] = {std::this_thread::get_id(), time.elapsed()};
    }

    color ray_color(const ray& r, int depth) const
    {
        // If we've exceeded the ray bounce limit, no more light is gathered
        if (depth <= 0)
        {
            return color(0,0,0);
        }

        hit_record rec;

        if (world.hit(r, interval(0.001, infinity), rec))
        {
            ray scattered;
            color attenuation;
            if (rec.mat->scatter(r, rec, attenuation, scattered))
            {
                return attenuation * ray_color(scattered, depth - 1);
            }
            return color(0,0,0);
        }

        vec3 unit_direction = unit_vector(r.direction());
        auto a = 0.5*(unit_direction.y() + 1.0);
        return(1.0-a) * color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
    }

};

