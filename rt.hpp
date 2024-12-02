#ifndef RT_HPP
#define RT_HPP

using namespace std;

// define constants
#define BACKGROUND_R 0.3
#define BACKGROUND_G 0.3
#define BACKGROUND_B 0.5
#define EYE_POS 0.0
#define X_LEN 640
#define Y_LEN 480

// ray structure 
typedef struct {
    Vec origin;
    Vec dir;
} RAY_T;

#endif // RT_HPP