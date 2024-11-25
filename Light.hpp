#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "Vec.hpp"
#include "Color.hpp"
#include "Object.hpp"
#include "scene.hpp"
#include "rt.hpp"

class Light {
    public:
        Light(Vec loc);
        Color illuminate(Object *obj, Vec intersection_point, Vec normal, scene *scene, rt ray);

    private:
        Vec loc;
        static bool shadow_test(Vec intersection_point, Object *curr_obj, scene *scene);
};

#endif // LIGHT_HPP