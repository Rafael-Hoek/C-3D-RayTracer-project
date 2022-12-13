#include "renderers/edge-renderer.h"
#include "renderers/renderer-base.h"
#include "easylogging++.h"

using namespace imaging;
using namespace math;
using namespace raytracer;
using namespace raytracer::renderers;


namespace
{
    class EdgeRenderer : public raytracer::renderers::_private_::RendererBaseImplementation
    {
    public:
        EdgeRenderer(unsigned horizontal_size, unsigned vertical_size, raytracer::Sampler sampler, RayTracer ray_tracer, tasks::TaskScheduler scheduler, double brush_thickness, Color brush_color, Color background_color)
            : RendererBaseImplementation(horizontal_size, vertical_size, sampler, ray_tracer, scheduler), 
            brush_thickness(brush_thickness), brush_color(brush_color), 
            background_color(background_color)
        {
            
        }

        std::shared_ptr<imaging::Bitmap> render(const Scene& scene) const override
        {
            TIMED_FUNC(timer);

            // Create a [0,1] x [0,1] window.
            Rectangle2D window(Point2D(0, 1), Vector2D(1, 0), Vector2D(0, -1));

            // Divide this window in small rectangles (which represent pixels)
            Rasterizer window_rasterizer(window, m_horizontal_size, m_vertical_size);

            // Create a bitmap of the same size
            auto result = std::make_shared<Bitmap>(m_horizontal_size, m_vertical_size);
            Bitmap& bitmap = *result;
            data::Grid<unsigned> grid = data::Grid<unsigned>(window_rasterizer.horizontal_subdivisions(), window_rasterizer.vertical_subdivisions());
            // Repeat for each pixel
            for_each_pixel([&](Position2D pixel_coordinates) {
                math::Rectangle2D pixel_rectangle = window_rasterizer[pixel_coordinates];
                auto center = pixel_rectangle.center();
                auto rays = scene.camera->enumerate_rays(center);
                grid[pixel_coordinates] = m_ray_tracer->trace(scene, rays[0]).group_id;
                });
            for_each_pixel([&](Position2D pixel_coordinates) {
                // Determine the color of the pixel
                Color c = background_color;
                grid.around(pixel_coordinates, (int)round(brush_thickness), [&](Position2D p) {
                    if (grid[pixel_coordinates] != grid[p]) c = brush_color;
                    });

                // Assign color to bitmap
                bitmap[pixel_coordinates] = c;
                });

            return result;
        }

    private:    
        double brush_thickness;
        Color brush_color;
        Color background_color;
    };
}

Renderer raytracer::renderers::edge(unsigned width, unsigned height, raytracer::Sampler sampler, RayTracer ray_tracer, tasks::TaskScheduler scheduler, double stroke_thickness, Color stroke_color, Color background_color) {
    return Renderer(std::make_shared<EdgeRenderer>(width, height, sampler, ray_tracer, scheduler, stroke_thickness, stroke_color, background_color));
}
