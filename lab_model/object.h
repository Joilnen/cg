#ifndef OBJECT_H
#define OBJECT_H

#include <boost/qvm/vec.hpp>
#include <boost/qvm/vec_operations.hpp>
#include <boost/qvm/vec_access.hpp>
#include <boost/qvm/quat.hpp>
#include <boost/qvm/quat_operations.hpp>

#include <vector>
#include <string>

using namespace std;
using namespace boost::qvm;

#include "face.h"

class Object {

    vector<Face> faces;
    string name;

    public:
        Object();
        ~Object();
        void addFace(Face f);
        void deleteFace(int index);
        void setMode(ModeDraw m);
        void rotate(int index);
        void draw();
};

#endif


