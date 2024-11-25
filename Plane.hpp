#ifndef PLANE_HPP
#define PLANE_HPP

#include "Object.hpp"
#include "Vec.hpp"
#include "Color.hpp"
#include "rt.hpp"

using namespace std;

class Plane : public Object {
    private:
        Vec normal;
        double D;

    public:
        Plane::Plane(Vec normal, double D, Color color, bool checker, Color color2 = Color(0.0, 0.0, 0.0)) {
            this->normal = normal;
            this->D = D;
            this->color = color;
            this->checker = checker;
            this->color2 = color2;
        }
        bool Plane::intersect(RAY_T ray, double *t, Vec *intersection_point, Vec *normal);
};


#endif // PLANE_HPP