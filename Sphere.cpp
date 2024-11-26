#include "Sphere.hpp"

using namespace std;

// constructor
Sphere::Sphere(Vec center, double radius, Color color, bool checker, Color color2) {
    this->center = center;
    this->radius = radius;
    this->color = color;
    this->checker = checker;
    this->color2 = color2;
}

// implement intersect method
bool Sphere::intersect(RAY_T ray, double *t, Vec *int_pt, Vec *normal) {
    // get the vector from the ray origin to the sphere center
    Vec oc = ray.origin - this->center;
    // check if a ray intersects the sphere
    double a = 1.0;
    double b = 2 * (ray.dir * oc).sum_components();
    double c = (oc * oc).sum_components() - (this->radius * this->radius);   
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
    *int_pt = ray.origin + ray.dir * *t; 

    // normal point
    *normal = *int_pt - this->center;
    normal->normalize();

    // return true
    return 1;
}