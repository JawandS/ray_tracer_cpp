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
        Sphere(Vec center, double radius, Color color, bool checker = false, Color color2 = Color(0.0, 0.0, 0.0));
        bool intersect(RAY_T ray, double *t, Vec *int_pt, Vec *normal);
};


#endif // SCENE_HPP