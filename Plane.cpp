#include "Plane.hpp"

using namespace std;

bool Plane::intersect(RAY_T ray, double *t, Vec *int_pt, Vec *normal) {
    // assumes that the object is a plane
    *normal = this->normal;
    double dp = normal->dot(ray.dir);
    if (dp == 0) { // no intersection
        return 0;
    } else {
        *t = -(normal->dot(ray.origin) + this->D) / dp;
        if (*t < 0) { // no intersection
            return 0;
        } else { // intersection point
            *int_pt = ray.origin + ray.dir * *t;
            return 1;
        }
    }
}
