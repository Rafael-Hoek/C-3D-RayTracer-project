#pragma once

#include "renderers/renderer.h"
#include <functional>

namespace raytracer
{
    namespace renderers
    {
        Renderer masking(Renderer renderer1, Renderer renderer2);
    }
}