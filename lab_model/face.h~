#ifndef FACE_H
#define FACE_H

#include <boost/qvm/vec.hpp>
#include <boost/qvm/vec_operations.hpp>
#include <boost/qvm/vec_access.hpp>
#include <boost/qvm/quat.hpp>
#include <boost/qvm/quat_operations.hpp>

using namespace boost::qvm;

enum class ModeDraw {WIRE, SOLID, SHADED};

class Face {

    vec<float, 3> vertices[4];
    vec<float, 3> normal;

    public:
        Face();
        ~Face();
        void draw();
        void scale(float x, float y);
        void raotate(float x, float y, float z);
        void setMode(ModeDraw m);
        vec<float, 3> &getNormal();

};

#endif


