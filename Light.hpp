#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "Vec.hpp"
#include "Color.hpp"
#include "Object.hpp"
#include "scene.hpp"
#include "rt.hpp"

class Light {
    private:
        Vec loc;
        static bool Light::shadow_test(Vec intersection_point, Object *curr_obj, SCENE_T *scene);

    public:
        Light(Vec loc);
        Color Light::illuminate(Object *obj, Vec intersection_point, Vec normal, SCENE_T *scene, RAY_T ray);
};

#endif // LIGHT_HPP