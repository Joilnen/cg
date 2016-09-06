#ifndef MODELER_H
#define MODELER_H

#include <vector>
#include <string>
#include "object.h"

using namespace std;
using namespace boost::qvm;

enum class ObjectType {PLAN, CUBE};

class Modeler {

    vector<Object> objects;
    bool editing;
    void createPlan();
    void createCube();

    Modeler();
    public:
        virtual ~Modeler();
        static Modeler &getInstance() {
            static Modeler m;
            return m;
        }

        void createObject(ObjectType ot);
        bool isEditing();
        void draw();
        void selectObject(int i);
        int getObjectIndex(string &s);
        void deleteObject(string &s);
        void deleteObject(int i);
        void addObject(Object o);
        void setEditObject(string &s);
        void exitEditMode();
};

#endif


