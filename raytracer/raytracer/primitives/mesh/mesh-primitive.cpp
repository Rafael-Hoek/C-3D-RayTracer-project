#include "primitives\bbacc.h"
#include "mesh-primitive.h"
#include "primitives\primitive.h"
#include "primitives\triangle-primitive.h"
#include "primitives\mesh\mesh-receiver.h"
#include "primitives\mesh\mesh-text-reader.h"
#include "primitives\union-primitive.h"
#include <memory>

#include <iostream>
#include <fstream>
#include <istream>
#include <sstream>

#include "logging.h"
#include "easylogging++.h"

using namespace std;
using namespace math;

namespace raytracer
{
    namespace primitives
    {
        class MeshBuilder : public MeshReceiver {

        private:

            vector<Point3D> vertices;
            vector<Primitive> primitives;

            void vertex(double x, double y, double z) override
            {
                vertices.push_back(Point3D(x, y, z));
            }

            virtual void normal(double x, double y, double z) {
            }

            void triangle(unsigned vertex1, unsigned vertex2, unsigned vertex3) override
            {
                using namespace raytracer::primitives;

                Primitive tri = raytracer::primitives::triangle(
                    vertices[vertex1],
                    vertices[vertex2],
                    vertices[vertex3]
                );
                primitives.push_back(tri);
            }

            void box(unsigned n_children) override {
                vector<Primitive> ntriangles;

                for (unsigned i = 0; i < n_children; i++)
                {
                    ntriangles.push_back(primitives.back());
                    primitives.pop_back();
                }

                primitives.push_back(
                    bounding_box_accelerator(primitives::make_union(ntriangles))
                  );
            }

        public:

            MeshBuilder()
            {
               
            }

            Primitive CreateMesh()
            {
                return primitives::make_union(primitives);
            }

        };

        Primitive raytracer::primitives::mesh(const std::string& path)
        {
            MeshBuilder builder;

            auto stream = std::ifstream(path);

            if (stream.is_open())
            {
                LOG(INFO) << "Opening mesh file at: " + path;
                read_text_mesh(stream, builder);
            }
            else
            {
                LOG(INFO) << "Failed to load file at path: " + path;
                throw "Fail!";
            }

            return builder.CreateMesh();
        }
    }
}


