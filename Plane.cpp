#include "Plane.hpp"

using namespace std;

bool Plane::intersect(RAY_T ray, double *t, Vec *intersection_point, Vec *normal) {
    // assumes that the object is a plane
    *normal = this->normal;
    double dp = dot(*normal, ray.dir);
    if (dp == 0) { // no intersection
        return 0;
    } else {
        *t = -(dot(*normal, ray.origin) + this->D) / dp;
        if (*t < 0) { // no intersection
            return 0;
        } else { // intersection point
            intersection_point->x = ray.origin.x + *t * ray.dir.x;
            intersection_point->y = ray.origin.y + *t * ray.dir.y;
            intersection_point->z = ray.origin.z + *t * ray.dir.z;
            return 1;
        }
    }
}
