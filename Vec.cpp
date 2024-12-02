#include <math.h>
#include "Vec.hpp"

using namespace std;

// constructor
Vec::Vec(double x, double y, double z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

void Vec::normalize() {
    // normalize a vector
    double len = this->len();
    this->x /= len;
    this->y /= len;
    this->z /= len;
}

// operator overloading
Vec Vec::add(const Vec &b) {
            return Vec(this->x + b.x, 
                       this->y + b.y, 
                       this->z + b.z);
        }
Vec Vec::operator+(const Vec &b) {
    return this->add(b);
}

Vec Vec::sub(const Vec &b) {
    return Vec(this->x - b.x, 
                this->y - b.y, 
                this->z - b.z);
}
Vec Vec::operator-(const Vec &b) {
    return this->sub(b);
}

Vec Vec::mult(const Vec &b) {
    return Vec(this->x * b.x, 
                this->y * b.y, 
                this->z * b.z);
}
Vec Vec::operator*(const Vec &s) {
    return this->mult(s);
}

Vec Vec::scalar_mult(double s) {
    return Vec(this->x * s, 
                this->y * s, 
                this->z * s);
}
Vec Vec::operator*(double s) {
    return this->scalar_mult(s);
}

Vec Vec::scalar_divide(double s) {
    return Vec(this->x / s, 
                this->y / s, 
                this->z / s);
}
Vec Vec::operator/(double s) {
    return this->scalar_divide(s);
}

int Vec::sum_floor_componenets() {
    return floor(this->x) + floor(this->y) + floor(this->z);
}