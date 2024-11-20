#ifndef COLOR_HPP
#define COLOR_HPP

using namespace std;

class Color {
    private:
        double r, g, b;

    public:
        // constructors
        Color();
        Color(double r, double g, double b);

        // getters 
        inline double get_r() { return r; }
        inline double get_g() { return g; }
        inline double get_b() { return b; }

        // add/operator+ method
        Color operator+(Color &c);
        Color add(Color &c);
        Color operator+(double scalar);
        Color add(double scalar);
        // mult_scalar/operator* method
        Color operator*(double scalar);
        Color mult_scalar(double scalar);

        // cap method
        void cap();
};

#endif // COLOR_HPP