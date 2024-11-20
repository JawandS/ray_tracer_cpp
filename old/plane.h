// plane.h
#ifndef PLAHE_H
#define PLAHE_H
#include "vp.h"
#include "rt.h"

int intersects_plane(RAY_T ray, OBJ_T *obj, double *t, VP_T *intersection_point, VP_T *normal);

#endif // plane.h
