#include "Sphere.hpp"

using namespace std;

// implement intersect method
bool Sphere::intersect(RAY_T ray, double *t, Vec *intersection_point, Vec *normal) {
    // get the vector from the ray origin to the sphere center
    Vec oc = diff(ray.origin, this->center);
    // check if a ray intersects the sphere
    double a = 1.0;
    double b = 2 * (ray.dir.x * oc.x +
                    ray.dir.y * oc.y +
                    ray.dir.z * oc.z);
    double c = oc.x * oc.x + 
               oc.y * oc.y +
               oc.z * oc.z -
               sphere.radius * sphere.radius;
    double discriminant = b * b - 4 * a * c;
    if (discriminant <= 0) { // sphere invalid position
        return 0; // return false 
    }
    // quadratic formula 
    double sqrt_discriminant = sqrt(discriminant);
    double pos_t = (-b + sqrt_discriminant) / (2*a);
    double neg_t = (-b - sqrt_discriminant) / (2*a);
    if (pos_t <= 0 || neg_t <= 0) { // invalid sphere pos
        return 0; 
    }
    // select smaller t
    *t = neg_t;
    if (pos_t < neg_t)
        *t = pos_t;
    
    // intersection point
    intersection_point->x = ray.origin.x + ray.dir.x * *t;
    intersection_point->y = ray.origin.y + ray.dir.y * *t;
    intersection_point->z = ray.origin.z + ray.dir.z * *t;

    // normal point
    normal->x = intersection_point->x - sphere.center.x;
    normal->y = intersection_point->y - sphere.center.y;
    normal->z = intersection_point->z - sphere.center.z;
    normalize(normal);

    // return true
    return 1;
}