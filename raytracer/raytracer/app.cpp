#ifndef TEST_BUILD

#include "easylogging++.h"
#include "version.h"
#include "command-line-parser.h"
#include "logging.h"
#include "pipeline/pipelines.h"
#include "util/beep.h"
#include "scripting/scripting.h"
#include "performance/performance.h"
#include <assert.h>

using namespace raytracer;


namespace
{
    void render_script(const std::string& filename)
    {
        TIMED_SCOPE(timer, "Rendering script");

#       ifdef EXCLUDE_SCRIPTING
        LOG(ERROR) << "Cannot run script - scripting was excluded";
        abort();
#       endif

        if (filename != "-")
        {
            LOG(INFO) << "Rendering " << filename;

            raytracer::scripting::run_script(filename);
        }
        else
        {
            LOG(INFO) << "Rendering script from STDIN";

            std::string script;

            while (!std::cin.eof())
            {
                std::string line;
                std::getline(std::cin, line);
                script += line + "\n";
            }

            raytracer::scripting::run(script);
        }
    }

    void quiet()
    {
        logging::quiet();
    }

    void show_version()
    {
        LOG(INFO) << "Build " << BUILD_NUMBER << std::endl;
    }

    void emit_beep()
    {
        ::beep();
    }

    void print_statistics()
    {
        performance::print_statistics();
    }

    void enable_3dstudio_output()
    {
        logging::enable("studio");

        LOG(INFO) << "Activated 3d studio mode";
    }
}

/// <summary>
/// Processes the command line arguments.
/// The command line arguments form a series of commands to be executed in order by the ray tracer.
/// For example, using "-s a.chai -s b.chai --beep" tells
/// the ray tracer to render a.chai, then b.chai, and finally emit a beep (so that you know it's done working.)
/// </summary>
void process_command_line_arguments(int argc, char** argv)
{
    CommandLineParser parser;

    parser.register_processor("-s", render_script);
    parser.register_processor("--quiet", quiet);
    parser.register_processor("--version", show_version);
    parser.register_processor("--beep", emit_beep);
    parser.register_processor("--statistics", print_statistics);
    parser.register_processor("--studio", enable_3dstudio_output);

    parser.process(argc, argv);

    LOG(INFO) << "Terminated successfully";
}

int main(int argc, char** argv)
{
    LOG(INFO) << "Build " << BUILD_NUMBER;
    TIMED_FUNC(timer);

    logging::configure();
    
#ifdef NDEBUG
    // Release build
    // Get rendering instructions from command line
    process_command_line_arguments(argc, argv);    
#else
    // Debug build
    // Make path point to a test script
    const std::string path = R"(D:\School\fase3\3d\raytracer-jerome-rafael-stijn\scenes\pyramid.chai)";
    render_script(path);
#endif
}

#endif
