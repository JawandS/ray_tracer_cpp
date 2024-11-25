#include <math.h>
#include "Vec.hpp"

using namespace std;

void Vec::normalize() {
    // normalize a vector
    double len = this->len();
    this->x /= len;
    this->y /= len;
    this->z /= len;
}

// operator overloading
Vec Vec::add(Vec *b) {
            return Vec(this->x + b->x, 
                       this->y + b->y, 
                       this->z + b->z);
        }
Vec Vec::operator+(Vec *b) {
    return this->add(b);
}

Vec Vec::sub(Vec *b) {
    return Vec(this->x - b->x, 
                this->y - b->y, 
                this->z - b->z);
}
Vec Vec::operator-(Vec *b) {
    return this->sub(b);
}

Vec Vec::mult(Vec *s) {
    return Vec(this->x * s->x, 
                this->y * s->y, 
                this->z * s->z);
}
Vec Vec::operator*(Vec *s) {
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

double Vec::sum_floor_componenets() {
    return floor(this->x) + floor(this->y) + floor(this->z);
}