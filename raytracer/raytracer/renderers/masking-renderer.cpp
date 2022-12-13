#include "renderers/masking-renderer.h"
#include "renderers/renderer-base.h"
#include "easylogging++.h"

using namespace imaging;
using namespace math;
using namespace raytracer;
using namespace raytracer::renderers;


namespace
{
    class MaskingRenderer : public raytracer::renderers::_private_::RendererImplementation
    {
    public:
        MaskingRenderer(Renderer renderer1, Renderer renderer2)
            : renderer1(renderer1), renderer2(renderer2)
        {
        }

        std::shared_ptr<imaging::Bitmap> render(const Scene& scene) const override
        {
            auto map1 = *renderer1->render(scene);
            auto map2 = *renderer2->render(scene);

            auto result = imaging::Bitmap(map1.width(), map1.height());

            map1.for_each_position([&](Position2D position) {
                if (map2.is_inside(position)) {
                    result[position] = map1[position] * map2[position];
                }
                });
            return std::make_shared<imaging::Bitmap>(result);
        }

    private:
        Renderer renderer1, renderer2;
    };
}

Renderer raytracer::renderers::masking(Renderer renderer1, Renderer renderer2)
{
    return Renderer(std::make_shared<MaskingRenderer>(renderer1, renderer2));
}