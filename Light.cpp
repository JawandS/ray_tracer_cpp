#include <stdio.h>
#include <math.h>
#include "Light.hpp"
#include "Object.hpp"
#include "scene.hpp"

using namespace std;

// constructor
Light::Light(Vec loc) {
    this->loc = loc;
}

// shadow test 
bool Light::shadow_test(Vec intersection_point, Object *curr_obj, SCENE_T *scene) {
    // Create the shadow ray 
    RAY_T shadow_ray;
    shadow_ray.origin = intersection_point;
    shadow_ray.dir = scene->light.loc - intersection_point;
    shadow_ray.dir.normalize();

    // Check for intersection with any object
    Object *curr;
    double t;
    Vec normal;
    Vec tmp_int_pt;
    for (curr = scene->objs; curr != NULL; curr = curr->next) {
        if (curr == curr_obj) 
            continue; // don't check the same object
        if (curr->intersect(shadow_ray, &t, &tmp_int_pt, &normal)) {
            return 1; // in shadow
        }
    }
    return 0; // Not in shadow
}