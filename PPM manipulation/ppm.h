/*************************
 *Josh Stikeleather
 *CPSC 2310 002
 *jstikel@clemson.edu
 *************************/

#ifndef PPM_H
#define PPM_H

#include <stdio.h>
#include <string.h>

//Shape type constants
#define SHAPE_NONE 0
#define SHAPE_CIRCLE 1
#define SHAPE_TRIANGLE 2
#define SHAPE_RECTANGLE 3
//This brief struct helps figure out the order we should add the shapes to the ppm
typedef struct{
    int types[3];
    int count;
} ShapeOrder;

//Simply a struct for a point
typedef struct{
    int x;
    int y;
} Point;

//Pixel struct holds the different RGB values for the each individual pixel
typedef struct{
    unsigned char r;
    unsigned char g;
    unsigned char b;
} Pixel;

//This struct holds the header info for the PPM
typedef struct{
    char magicNumber[3]; //ALWAYS P6
    int width;
    int height;
    int maxColor;
    Pixel background;
} PPMImage;


//Declaring the circle struct so our pointer is valid in the next line
struct Circle;
struct Triangle;
struct Rectangle;

//This function reads in the PPM header values and the information regarding the circle, triangle, and rectangle
void readPPMInput(FILE *in, PPMImage *img, struct Circle *c, struct Triangle *t, struct Rectangle *r, ShapeOrder *order);

//This one writes to the PPM
void writePPMHeader(FILE *out, PPMImage *img);

#endif