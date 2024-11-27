#include <stdio.h>
#include <math.h>
#include <stdlib.h>
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
static void init(SCENE_T *scene, Light *light) {
    // default values for scene 
    scene->objs = nullptr;
    // read file for object information
    FILE *file = fopen("scene1.txt", "r");
    Object *node = nullptr;
    char info_type; // what the information is 
    while (fscanf(file, "%c", &info_type) != EOF) { // iterate while file is not empty 
        if (info_type == 's') { // sphere type
            // create variables
            double x, y, z, r; // center and radius
            double r_color, g_color, b_color; // color
            // read sphere center
            fscanf(file, "%lf %lf %lf", &x, &y, &z);
            // read sphere radius
            fscanf(file, "%lf", &r);
            // read sphere color
            fscanf(file, "%lf %lf %lf", &r_color, &g_color, &b_color);
            // print input vals
            printf("x: %lf, y: %lf, z: %lf, r: %lf, r_color: %lf, g_color: %lf, b_color: %lf\n", x, y, z, r, r_color, g_color, b_color);
            // create sphere
            Color *temp_color = new Color(r_color, g_color, b_color);
            node = new Sphere(Vec(x, y, z), r, *temp_color);
            // print sphere color
            printf("sphere color A: %lf, %lf, %lf\n", node->color.get_r(), node->color.get_g(), node->color.get_b());
            printf("sphere color: %lf, %lf, %lf\n", temp_color->get_r(), temp_color->get_g(), temp_color->get_b());
            // add it to the objects linked list
            node->next = scene->objs;
            scene->objs = node;
        } else if (info_type == 'p') { // plane type
            // create variables
            double x, y, z; // normal
            double D; // distance
            double r_color, g_color, b_color; // color
            double r_color2, g_color2, b_color2; // color2
            // read plane normal
            fscanf(file, "%lf %lf %lf", &x, &y, &z);
            // read plane distance 
            fscanf(file, "%lf", &D);
            // read plane color 
            fscanf(file, "%lf %lf %lf", &r_color, &g_color, &b_color);
            // read plane color2
            fscanf(file, "%lf %lf %lf", &r_color2, &g_color2, &b_color2);
            // create plane
            node = new Plane(Vec(x, y, z), D, Color(r_color, g_color, b_color), true, Color(r_color2, g_color2, b_color2));
            // add to list 
            node->next = scene->objs;
            scene->objs = node;
        } else if (info_type == 'l') { // light type
            // set vars
            double x, y, z; // location
            // read light location
            fscanf(file, "%lf %lf %lf", &x, &y, &z);
            // create light
            light = new Light(Vec(x, y, z));
        }
    }
    // close the file
    fclose(file);
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
    Color *obj_color = new Color(0.3, 0.3, 0.3);
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
    Vec eye_pos = Vec(0, 0, 0);

    // initialize scene
    SCENE_T *scene = new SCENE_T;
    Light *light = new Light(Vec(0, 0, 0));
    init(scene, light);
    // manual initialization: 640 x 480
    const int X_LEN = 640;
    const int Y_LEN = 480;
    scene->start_x = - ((double) X_LEN / (double) Y_LEN) / 2.0;
    scene->start_y = 0.5;
    scene->pixel_size = 1.0 / (double) Y_LEN;

    // open the file 
    FILE *fimg = fopen("img.ppm", "w");
    // initialize image file header
    fprintf(fimg, "P6\n");
    fprintf(fimg, "%d %d\n", X_LEN, Y_LEN);
    fprintf(fimg, "255\n");

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
            fprintf(fimg, "%c%c%c", (unsigned char) (255 * point_color.get_r()), (unsigned char) (255 * point_color.get_g()), (unsigned char) (255 * point_color.get_b()));
        }
    }
    printf("\n");

    // close the file
    fclose(fimg);
    // exit
    return 0;
}
