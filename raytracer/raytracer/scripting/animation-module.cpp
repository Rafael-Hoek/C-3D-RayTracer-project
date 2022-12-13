#ifndef EXCLUDE_SCRIPTING

#include "scripting/animation-module.h"
#include "scripting/scripting-util.h"
#include "raytracers/scene.h"
#include "animation/animations.h"
#include "math/angle.h"
#include "math/functions.h"


using namespace chaiscript;
using namespace raytracer;
using namespace math;
using namespace imaging;
using namespace animation;


namespace
{
    struct AnimationLibrary
    {
        Animation<Point3D> point_animation(const Point3D& from, const Point3D& to, Duration duration) const
        {
            return animation::animate(from, to, duration);
        }

        Animation<double> double_animation(double from, double to, Duration duration) const
        {
            return animation::animate(from, to, duration);
        }

        Animation<Angle> angle_animation(Angle from, Angle to, Duration duration) const
        {
            return animation::animate(from, to, duration);
        }

        Animation<Point3D> circular_animation(math::Point3D point, math::Point3D center, math::Vector3D axis, math::Interval<math::Angle> angle_interval, animation::Duration duration) const
        {
            return animation::circular(point, center, axis, angle_interval, duration);
        }

        Animation<Point3D> circular_by_map(const std::map<std::string, Boxed_Value>& argument_map) const
        {
            START_ARGUMENTS(argument_map);
            OPTIONAL_ARGUMENT(math::Point3D, position, math::Point3D(0,1,0));
            OPTIONAL_ARGUMENT(math::Point3D, around, math::Point3D(0,0,0));
            OPTIONAL_ARGUMENT(math::Vector3D, axis, math::Vector3D(1,0,0));
            OPTIONAL_ARGUMENT(math::Interval<math::Angle>, angle_interval, math::Interval<math::Angle>(Angle::degrees(0), Angle::degrees(360)));
            OPTIONAL_ARGUMENT(animation::Duration, duration, animation::Duration::from_seconds(5));
            END_ARGUMENTS();

            return animation::circular(position, around, axis, angle_interval, duration);
        }

        Animation<Point3D> lissajous_animation(double x_amplitude, double y_amplitude, double z_amplitude, double x_frequency, double y_frequency, double z_frequency, const math::Angle& x_phase, const math::Angle& y_phase, const math::Angle& z_phase, const Duration& duration) const
        {
            return animation::lissajous(x_amplitude, y_amplitude, z_amplitude, x_frequency, y_frequency, z_frequency, x_phase, y_phase, z_phase, duration);
        }

        Animation<Point3D> lissajous_by_map(const std::map<std::string, Boxed_Value>& argument_map) const {
            START_ARGUMENTS(argument_map);
            OPTIONAL_ARGUMENT(double, x_amplitude, 1);
            OPTIONAL_ARGUMENT(double, y_amplitude, 1);
            OPTIONAL_ARGUMENT(double, z_amplitude, 1);
            OPTIONAL_ARGUMENT(double, x_frequency, 1);
            OPTIONAL_ARGUMENT(double, y_frequency, 1);
            OPTIONAL_ARGUMENT(double, z_frequency, 1);
            OPTIONAL_ARGUMENT(math::Angle, x_phase, math::Angle::degrees(0));
            OPTIONAL_ARGUMENT(math::Angle, y_phase, math::Angle::degrees(0));
            OPTIONAL_ARGUMENT(math::Angle, z_phase, math::Angle::degrees(0));
            OPTIONAL_ARGUMENT(Duration, duration, Duration::from_seconds(5));
            END_ARGUMENTS();

            return animation::lissajous(x_amplitude, y_amplitude, z_amplitude, x_frequency, y_frequency, z_frequency, x_phase, y_phase, z_phase, duration);
        }

        template <class T>
        Animation<T> ease_animation(Animation<T>& anim, math::functions::EasingFunction& func) const
        {
            return animation::ease(anim, func);
        }
    };

    Duration seconds(double s)
    {
        return Duration::from_seconds(s);
    }

    TimeStamp epoch()
    {
        return TimeStamp::zero();
    }

    Animation<std::shared_ptr<Scene>> make_scene_animation(std::function<std::shared_ptr<Scene>(TimeStamp)> function, Duration duration)
    {
        return Animation<std::shared_ptr<Scene>>(from_lambda(function), duration);
    }
}

ModulePtr raytracer::scripting::_private_::create_animation_module()
{
    auto module = std::make_shared<chaiscript::Module>();

    util::register_to_string<Duration>(*module);
    util::register_to_string<TimeStamp>(*module);

    auto animation_library = std::make_shared<AnimationLibrary>();
    module->add_global_const(chaiscript::const_var(animation_library), "Animations");

#define BIND_AS(INTERNAL, EXTERNAL)                 module->add(fun(&AnimationLibrary::INTERNAL), #EXTERNAL)
#define BIND(NAME)                                  BIND_AS(NAME, NAME)
    BIND_AS(double_animation, animate);
    BIND_AS(point_animation, animate);
    BIND_AS(angle_animation, animate);
    BIND_AS(circular_animation, circular);
    BIND_AS(circular_by_map, circular);
    BIND_AS(lissajous_animation, lissajous);
    BIND_AS(lissajous_by_map, lissajous);
    BIND_AS(ease_animation<double>, ease);
    BIND_AS(ease_animation<Angle>, ease);
    BIND_AS(ease_animation<Point3D>, ease);
#undef BIND
#undef BIND_AS

    module->add(fun(&seconds), "seconds");
    module->add(fun(&epoch), "epoch");
    module->add(fun([](TimeStamp t, Duration d) { return t + d; }), "+");
    module->add(fun([](Duration d, TimeStamp t) { return t + d; }), "+");
    module->add(fun(&Animation<Point3D>::operator()), "[]");
    module->add(fun(&Animation<Angle>::operator()), "[]");
    module->add(fun(&Animation<double>::operator()), "[]");
    module->add(fun(&make_scene_animation), "scene_animation");

    return module;
}

#endif
