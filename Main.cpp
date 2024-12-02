#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "Vec.hpp"
#include "Sphere.hpp"
#include "Plane.hpp"
#include "scene.hpp"
#include "Object.hpp"
#include "Color.hpp"
#include "rt.hpp"
#include "Light.hpp"

using namespace std;

// initialize method
static void init(SCENE_T *scene, Light *&light) {
    // default values for scene 
    scene->objs = nullptr;
    // read file for object information (use iostream)
    ifstream infile("scene1.txt");
    Object *node = nullptr;
    char info_type; // what the information is 
    
    while (infile >> info_type) { // iterate while file is not empty 
        if (info_type == 's') { // sphere type
            // create variables
            double x, y, z, r; // center and radius
            double r_color, g_color, b_color; // color
            // read sphere center
            infile >> x >> y >> z;
            // read sphere radius
            infile >> r;
            // read sphere color
            infile >> r_color >> g_color >> b_color;
            // create sphere
            Color *temp_color = new Color(r_color, g_color, b_color);
            node = new Sphere(Vec(x, y, z), r, *temp_color);
            node->next = scene->objs;
            scene->objs = node;
        } else if (info_type == 'p') { // plane type
            // create variables
            double x, y, z; // normal
            double D; // distance
            double r_color, g_color, b_color; // color
            double r_color2, g_color2, b_color2; // color2
            // read plane normal
            infile >> x >> y >> z;
            // read plane distance 
            infile >> D;
            // read plane color 
            infile >> r_color >> g_color >> b_color;
            // read plane color2
            infile >> r_color2 >> g_color2 >> b_color2;
            // create plane
            node = new Plane(Vec(x, y, z), D, Color(r_color, g_color, b_color), true, Color(r_color2, g_color2, b_color2));
            // add to list 
            node->next = scene->objs;
            scene->objs = node;
        } else if (info_type == 'l') { // light type
            // set vars
            double x, y, z; // location
            // read light location
            infile >> x >> y >> z;
            // create light
            light = new Light(Vec(x, y, z));
        }
    }
    // close the file
    infile.close();
}

static Color trace(RAY_T ray, SCENE_T scene, Light light) {
    // calculate the color of each ray if it's an intersection point
    double closest_t = 1000;
    double t;
    Vec closest_int_pt;
    Vec int_pt;
    Vec closest_normal;
    Vec normal;
    Object *closest_obj = nullptr;
    // baseline color
    Color *obj_color = new Color(BACKGROUND_R, BACKGROUND_G, BACKGROUND_B);
    // iterate through objects in scene
    Object *curr;
    int obj_index = 0;
    int closest_obj_index = 0;
    for(curr = scene.objs; curr != NULL; curr = curr->next) {
        if (curr->intersect(ray, &t, &int_pt, &normal)) {
            if (t < closest_t) {
                closest_t = t;
                closest_int_pt = int_pt;
                closest_normal = normal;
                closest_obj = curr;
                closest_obj_index = obj_index;
            }
        }
        obj_index++;
    }
    // get object color
    if (closest_t < 1000 && closest_obj != NULL)
        *obj_color = light.illuminate(ray, scene, closest_obj_index, closest_int_pt, closest_normal);
    return *obj_color; 
}

// main method
int main() {
    // set eye position 
    Vec eye_pos = Vec(EYE_POS, EYE_POS, EYE_POS);

    // initialize scene
    SCENE_T *scene = new SCENE_T;
    Light *light = nullptr;
    init(scene, light);
    scene->start_x = - ((double) X_LEN / (double) Y_LEN) / 2.0;
    scene->start_y = 0.5;
    scene->pixel_size = 1.0 / (double) Y_LEN;

    // open the file 
    ofstream fimg("img.ppm");
    // initialize image file header
    fimg << "P6\n";
    fimg << X_LEN << " " << Y_LEN << "\n";
    fimg << "255\n";

    // go through image 
    for (int y = 0; y < Y_LEN; y++) {
        for (int x = 0; x < X_LEN; x++) {
            // set ray origin and direction
            RAY_T curr_ray;
            curr_ray.origin = eye_pos;
            double x_val = (scene->start_x + (x * scene->pixel_size));
            double y_val = -(-scene->start_y + (y * scene->pixel_size));
            double z_val = 1;
            curr_ray.dir = Vec(x_val, y_val, z_val);
            curr_ray.dir.normalize();
            // write pixel 
            Color point_color = trace(curr_ray, *scene, *light); // replace with scene
            fimg << (unsigned char) (255 * point_color.get_r()) << (unsigned char) (255 * point_color.get_g()) << (unsigned char) (255 * point_color.get_b());
        }
    }
    printf("\n");

    // close the file
    fimg.close();
    // exit
    return 0;
}
