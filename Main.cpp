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

// initialize method
static void init(SCENE_T *scene) {
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
            fscanf(file, "%lf %lf %lf", x, y, z);
            // read sphere radius
            fscanf(file, "%lf", r);
            // read sphere color
            fscanf(file, "%lf %lf %lf", r_color, g_color, b_color);
            // create sphere
            node = new Sphere(Vec(x, y, z), r, Color(r_color, g_color, b_color));
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
            fscanf(file, "%lf %lf %lf", x, y, z);
            // read plane distance 
            fscanf(file, "%lf", D);
            // read plane color 
            fscanf(file, "%lf %lf %lf", r_color, g_color, b_color);
            // read plane color2
            fscanf(file, "%lf %lf %lf", r_color2, g_color2, b_color2);
            // create plane
            node = new Plane(Vec(x, y, z), D, Color(r_color, g_color, b_color), true, Color(r_color2, g_color2, b_color2));
            // add to list 
            node->next = scene->objs;
            scene->objs = node;
        } else if (info_type == 'l') { // light type
            // read light location
            fscanf(file, "%lf %lf %lf", &scene->light.loc.x, &scene->light.loc.y, &scene->light.loc.z);
        }
    }
    // close the file
    fclose(file);
}

static Color trace(RAY_T ray, SCENE_T *scene) {
    // calculate the color of each ray if it's an intersection point
    double closest_t = 1000;
    double t;
    Vec closest_intersection_point;
    Vec intersection_point;
    Vec closest_normal;
    Vec normal;
    Object *closest_obj = nullptr;
    // baseline color
    Color *obj_color = new Color(0.3, 0.3, 0.3);
    // iterate through objects in scene
    Object *curr;
    for(curr = scene->objs; curr != NULL; curr = curr->next) {
        if (curr->intersect(ray, &t, &intersection_point, &normal)) {
            if (t < closest_t) {
                closest_t = t;
                closest_intersection_point = intersection_point;
                closest_normal = normal;
                closest_obj = curr;
            }
        }
    }
    // get object color
    if (closest_t < 1000 && closest_obj != NULL)
        obj_color = scene->light.illuminate(closest_obj, closest_intersection_point, closest_normal, scene, ray);    
    return *obj_color; 
}

// main method
int main() {
    // set eye position 
    Vec eye_pos = Vec(0, 0, 0);

    // initialize scene
    SCENE_T scene;
    init(&scene);
    // manual initialization: 640 x 480
    const int X_LEN = 640;
    const int Y_LEN = 480;
    scene.start_x = - ((double) X_LEN / (double) Y_LEN) / 2.0;
    scene.start_y = 0.5;
    scene.pixel_size = 1.0 / (double) Y_LEN;

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
            double x_val = (scene.start_x + (x * scene.pixel_size));
            double y_val = -(-scene.start_y + (y * scene.pixel_size));
            double z_val = 1;
            curr_ray.dir = Vec(x_val, y_val, z_val);
            curr_ray.dir.normalize();
            // write pixel 
            Color point_color = trace(curr_ray, &scene); // replace with scene
            fprintf(fimg, "%c%c%c", (unsigned char) (255 * point_color.get_r()), (unsigned char) (255 * point_color.get_g()), (unsigned char) (255 * point_color.get_b()));
        }
    }
    printf("\n");

    // close the file
    fclose(fimg);
    // exit
    return 0;
}
