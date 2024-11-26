#ifndef SCENE_HPP
#define SCENE_HPP

#include "Object.hpp"

// scene type
typedef struct {
    Object *objs; // linked list of objects
    double start_x; // default -0.5, top left of the image 
    double start_y; // default 0.5
    double pixel_size; // default 1/1000
} SCENE_T;

#endif // SCENE_HPP