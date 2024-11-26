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
        static bool Light::shadow_test(SCENE_T scene, int obj_index, Vec int_pt);

    public:
        Light(Vec loc);
        Color Light::illuminate(RAY_T ray, SCENE_T scene, int obj_index, Vec int_pt, Vec normal);
};

#endif // LIGHT_HPP