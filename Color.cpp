#include "Color.hpp"

using namespace std;

// implement constructors
Color::Color() {
    this->r = 0;
    this->g = 0;
    this->b = 0;
}
Color::Color(double r, double g, double b) {
    this->r = r;
    this->g = g;
    this->b = b;
}

// implement add/operator+ method
Color Color::operator+(Color &c) {
    return Color(this->r + c.r, this->g + c.g, this->b + c.b);
}
Color Color::add(Color &c) {
    return Color::operator+(c);
}
Color Color::operator+(double scalar) {
    return Color(this->r + scalar, this->g + scalar, this->b + scalar);
}
Color Color::add(double scalar) {
    return Color::operator+(scalar);
}
// implement operator* method
Color Color::operator*(double scalar) {
    return Color(this->r * scalar, this->g * scalar, this->b * scalar);
}
Color Color::mult_scalar(double scalar) {
    return Color::operator*(scalar);
}

// implement cap
void Color::cap() {
    if (this->r > 1) 
        this->r = 1;
    if (this->g > 1) 
        this->g = 1;
    if (this->b > 1) 
        this->b = 1;
}