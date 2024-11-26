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
bool Light::shadow_test(SCENE_T scene, int obj_index, Vec int_pt) {
    // get the current object
    Object *curr_obj = scene.objs;
    for (int i = 0; i < obj_index; i++) {
        curr_obj = curr_obj->next;
    }
    // Create the shadow ray 
    RAY_T shadow_ray;
    shadow_ray.origin = int_pt;
    shadow_ray.dir = this->loc - int_pt;
    shadow_ray.dir.normalize();

    // Check for intersection with any object
    Object *curr;
    double t;
    Vec normal;
    Vec tmp_int_pt;
    for (curr = scene.objs; curr != NULL; curr = curr->next) {
        if (curr == curr_obj) 
            continue; // don't check the same object
        if (curr->intersect(shadow_ray, &t, &tmp_int_pt, &normal)) {
            return 1; // in shadow
        }
    }
    return 0; // Not in shadow
}

// illuminate
Color Light::illuminate(RAY_T ray, SCENE_T scene, int obj_index, Vec int_pt, Vec normal) {
    // get the current object
    Object *obj = scene.objs;
    for (int i = 0; i < obj_index; i++) {
        obj = obj->next;
    }
    // decide which object color to use 
    Color obj_color = obj->color;
    if (obj->checker && (int_pt.sum_floor_componenets() & 1)) {
        obj_color = obj->color2;
    }

    // calculate the color of each intersection point 
    Color color = Color(obj_color.get_r(), obj_color.get_g(), obj_color.get_b());

    // ambient light
    color = color * 0.1;

    // check for shadow
    if (!shadow_test(scene, obj_index, int_pt)) {
        // get the attentuation - TODO FIX THIS 
        double dl = (this->loc - int_pt).len();
        double atten_b = (0.002 * dl) * (0.002 * dl) + 0.02 * dl + 0.2;
        double atten = 1 / atten_b;

        // diffuse light
        Vec light_vector = this->loc - int_pt;
        light_vector.normalize();

        double dp = light_vector.dot(normal);
        if (dp > 0) {
            color = color * dp * atten;

            // specular light (only if the first dot product is positive)
            Vec r_vector = light_vector - normal * 2 * dp;
            r_vector.normalize();
            double dp2 = r_vector.dot(ray.dir);
            if (dp2 > 0) {
                color = color + pow(dp2, 200) * atten;
            }
        }
    }

    // set colors to max value
    color.cap();

    return color;
}