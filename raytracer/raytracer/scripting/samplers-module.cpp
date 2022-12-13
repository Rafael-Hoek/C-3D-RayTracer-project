#ifndef EXCLUDE_SCRIPTING

#include "scripting/samplers-module.h"
#include "samplers/samplers.h"
#include "scripting/scripting-util.h"

using namespace chaiscript;
using namespace raytracer;
using namespace math;


namespace
{
    struct SamplerLibrary
    {
        Sampler single() const
        {
            return samplers::single();
        }

        Sampler random(int n) const
        {
            return samplers::random(n);
        }

        Sampler stratified(unsigned rows, unsigned columns) const
        {
            return samplers::stratified(rows, columns);
        }

        Sampler nrooks(unsigned sample_count) const
        {
            return samplers::nrooks(sample_count);
        }
        Sampler stratified_jittered(unsigned rows, unsigned columns) const
        {
            return samplers::stratified_jittered(rows, columns);
        }
        Sampler stratified_half_jittered(unsigned rows, unsigned columns) const
        {
            return samplers::stratified_half_jittered(rows, columns);
        }
        Sampler multi_jittered(const int& n) const
        {
            return samplers::multi_jittered(n);
        }
    };
}

ModulePtr raytracer::scripting::_private_::create_samplers_module()
{
    auto module = std::make_shared<chaiscript::Module>();

    util::register_type<Sampler>(*module, "Sampler");

    auto sampler_library = std::make_shared<SamplerLibrary>();
    module->add_global_const(chaiscript::const_var(sampler_library), "Samplers");

#   define BIND(NAME)  module->add(fun(&SamplerLibrary::NAME), #NAME)
    BIND(single);
    BIND(random);
    BIND(stratified);
    BIND(nrooks);
    BIND(stratified_jittered);
    BIND(stratified_half_jittered);
    BIND(multi_jittered);
#   undef BIND

    return module;
}

#endif
