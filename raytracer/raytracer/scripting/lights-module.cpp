#ifndef EXCLUDE_SCRIPTING

#include "scripting/lights-module.h"
#include "scripting/scripting-util.h"
#include "lights/lights.h"

using namespace chaiscript;
using namespace raytracer;
using namespace math;
using namespace imaging;


namespace
{
    struct LightLibrary
    {
        LightSource omnidirectional(const Point3D& position, const Color& c) const
        {
            return lights::omnidirectional(position, c);
        }
        LightSource spot(const Point3D& position, const Vector3D& direction, math::Angle angle, const Color& color) const
        {
            return lights::spot(position, direction, angle, color);
        }
        //LightSource spot(const Point3D& position, const math::Point3D& target, math::Angle angle, const Color& color) const
        //{
        //    return lights::spot(position, target, angle, color);
        //}
        LightSource directional(const math::Vector3D& direction, const Color& color) const
        {
            return lights::directionalLight(direction, color);
        }
    };
}

ModulePtr raytracer::scripting::_private_::create_lights_module()
{
    auto module = std::make_shared<chaiscript::Module>();

    util::register_type<LightSource>(*module, "LightSource");

    auto lights_library = std::make_shared<LightLibrary>();
    module->add_global_const(chaiscript::const_var(lights_library), "Lights");

#   define BIND(NAME)                      BIND_AS(NAME, NAME)
#   define BIND_AS(INTERNAL, EXTERNAL)     module->add(fun(&LightLibrary::INTERNAL), #EXTERNAL)
    BIND(omnidirectional);
    BIND(spot);
    BIND(directional);
#   undef BIND_AS
#   undef BIND

    return module;
}

#endif
