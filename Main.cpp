#include <stdio.h>
#include <math.h>
#include <stdlib.h>
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
            // allocate space for object
            node = (Object*) malloc(sizeof(Object));
            node->type = 's'; // set type to sphere
            // read sphere center
            fscanf(file, "%lf %lf %lf", &node->sphere.center.x, &node->sphere.center.y, &node->sphere.center.z);
            // read sphere radius
            fscanf(file, "%lf", &node->sphere.radius);
            // read sphere color
            fscanf(file, "%lf %lf %lf", &node->color.r, &node->color.g, &node->color.b);
            // set checker to false
            node->checker = 0;
            // set interects function
            node->intersects = intersects_sphere;
            // add it to the objects linked list
            node->next = scene->objs;
            scene->objs = node;
        } else if (info_type == 'p') { // plane type
            // allocate space for object
            node = (OBJ_T*) malloc(sizeof(OBJ_T));
            node->type = 'p'; // set type to plane
            // read plane normal
            fscanf(file, "%lf %lf %lf", &node->plane.normal.x, &node->plane.normal.y, &node->plane.normal.z);
            // read plane distance 
            fscanf(file, "%lf", &node->plane.D);
            // read plane color 
            fscanf(file, "%lf %lf %lf", &node->color.r, &node->color.g, &node->color.b);
            // set checker to true
            node->checker = 1;
            // read plane color2
            fscanf(file, "%lf %lf %lf", &node->color2.r, &node->color2.g, &node->color2.b);
            // set interects function
            node->intersects = intersects_plane;
            // add it to the objects linked list
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
    Color obj_color;
    obj_color.r = 0.3;
    obj_color.g = 0.3;
    obj_color.b = 0.5;
    // iterate through objects in scene
    Object *curr;
    for(curr = scene->objs; curr != NULL; curr = curr->next) {
        if (curr->intersects(ray, curr, &t, &intersection_point, &normal)) {
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
        obj_color = illuminate(closest_obj, closest_intersection_point, closest_normal, scene, ray);    
    return obj_color; 
}

// main method
int main() {
    // set eye position 
    Vec eye_pos;
    eye_pos.x = 0.0;
    eye_pos.y = 0.0;
    eye_pos.z = 0.0;

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
            curr_ray.dir.x = (scene.start_x + (x * scene.pixel_size));
            curr_ray.dir.y = -(-scene.start_y + (y * scene.pixel_size));
            curr_ray.dir.z = 1;
            normalize(&curr_ray.dir);
            // write pixel 
            Color point_color = trace(curr_ray, &scene); // replace with scene
            fprintf(fimg, "%c%c%c", (unsigned char) (255 * point_color.r), (unsigned char) (255 * point_color.g), (unsigned char) (255 * point_color.b));
        }
    }
    printf("\n");

    // close the file
    fclose(fimg);
    // exit
    return 0;
}
