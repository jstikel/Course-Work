/*************************
 *Josh Stikeleather
 *CPSC 2310 002
 *jstikel@clemson.edu
 *************************/

#ifndef SHAPES_H
#define SHAPES_H

#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "ppm.h"

//A struct for a circle
typedef struct Circle{
    Point center;
    int radius;
    Pixel color;
} Circle;

//A struct for a triangle
typedef struct Triangle{
    Point point1;
    Point point2;
    Point point3;
    Pixel color;
} Triangle;

//A struct for a rectangle
typedef struct Rectangle{
    Point point1;
    Point point2;
    Point point3;
    Point point4;
    Pixel color;
} Rectangle;

//Here we have our three bool functions to check if a point is inside of a certain shape
bool pointInsideCircle(int x, int y, Circle *c);
bool pointInsideTriangle(int x, int y, Triangle *t);
bool pointInsideRectangle(int x, int y, Rectangle *r);

//Iterates over all pixels, writes the correct pixel color depending on whether or not it's inside of any shape
//Gives priority to the shapes towards the end of the input file
void drawShapes(FILE *out, PPMImage *img, Circle *c, Triangle *t, Rectangle *r, ShapeOrder *order);

#endif