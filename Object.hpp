#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "Color.hpp"
#include "Vec.hpp"
#include "rt.hpp"

using namespace std;

class Object {
    public:
        Color color;
        bool checker;
        Color color2;
        virtual bool intersect(RAY_T ray, double *t, Vec *int_pt, Vec *normal) {
            return false;
        }
        Object *next;
};

#endif // OBJECT_HPP