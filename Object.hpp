#ifndef OBJECT_HPP
#define OBJECT_HPP

using namespace std;

class Object {
    public:
        Color color;
        bool checker;
        Color color2;
        virtual bool intersect(RAY_T ray, Object *obj, double *t, Vec *intersection_point, Vec *normal) {
            return false;
        }
        Object *next;
};

#endif // OBJECT_HPP