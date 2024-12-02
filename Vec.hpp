#ifndef VEC_HPP
#define VEC_HPP

#include <math.h>

class Vec {
    private:
        double x;
        double y;
        double z;
    
    public:
        // constructors
        inline Vec() {}
        Vec(double x, double y, double z);

        // set method
        void set(double x, double y, double z) {
            this->x = x;
            this->y = y;
            this->z = z;
        }

        // normalize
        void normalize();
        // dot
        inline double dot(Vec b) {
            return this->x * b.x + 
                   this->y * b.y + 
                   this->z * b.z;
        }
        // len
        inline double len() {
            return sqrt(this->x * this->x + 
                        this->y * this->y + 
                        this->z * this->z);
        }

        // operator overloading
        Vec add(const Vec &b);
        Vec operator+(const Vec &b);

        Vec sub(const Vec &b);
        Vec operator-(const Vec &b);

        Vec mult(const Vec &s);
        Vec operator*(const Vec &s);

        Vec scalar_mult(double s);
        Vec operator*(double s);

        Vec scalar_divide(double s);
        Vec operator/(double s);

        inline double sum_components() {
            return this->x + this->y + this->z;
        }

        int sum_floor_componenets();

};

#endif // VEC_HPP