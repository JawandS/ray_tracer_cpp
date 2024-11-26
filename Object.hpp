#ifndef OBJECT_HPP
#define OBJECT_HPP

using namespace std;

class Object {
    public:
        Color color;
        bool checker;
        Color color2;
        virtual bool Object::intersect(RAY_T ray, double *t, Vec *int_pt, Vec *normal) {
            return false;
        }
        Object *next;
};

#endif // OBJECT_HPP