#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "Object.hpp"
#include "Vec.hpp"
#include "Color.hpp"
#include "rt.hpp"

using namespace std;

class Sphere : public Object {
    private:
        Vec center;
        double radius;

    public:
        Sphere::Sphere(Vec center, double radius, Color color) {
            this->center = center;
            this->radius = radius;
            this->color = color;
            this->checker = false;
            this->color2 = Color(0.0, 0.0, 0.0);
        }
        bool Sphere::intersect(RAY_T ray, double *t, Vec *intersection_point, Vec *normal);
};


#endif // SCENE_HPP