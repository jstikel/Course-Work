/*************************
 *Josh Stikeleather
 *CPSC 2310 002
 *jstikel@clemson.edu
 *************************/

#include "shapes.h"

//This function loops through every pixel, if it's inside the circle it colors it whatever color the circle is
//Otherwise color it the same as the background
void drawShapes(FILE *out, PPMImage *img, Circle *c, Triangle *t, Rectangle *r, ShapeOrder *order){
    for (int y = 0; y < img->height; y++){

        for (int x = 0; x < img->width; x++){

            //Automatically set the color of the pixel to the background, so if it's not
            //inside any shapes, it automatically stays the color of the background
            Pixel pixelColor = img->background;
            bool drawn = false;

            //Iterates over each pixel a maximum of three times and sets the
            //pixel to the color of the shape with the highest priority
            for (int i = order->count - 1; i >= 0 && !drawn; i--){
                if (order->types[i] == SHAPE_CIRCLE && pointInsideCircle(x, y, c)){
                    pixelColor = c->color;
                    drawn = true;
                }
                else if (order->types[i] == SHAPE_TRIANGLE && pointInsideTriangle(x, y, t)){
                    pixelColor = t->color;
                    drawn = true;
                }
                else if (order->types[i] == SHAPE_RECTANGLE && pointInsideRectangle(x, y, r)){
                    pixelColor = r->color;
                    drawn = true;
                }
            }
            fwrite(&pixelColor, sizeof(Pixel), 1, out);  //Write every pixel ONLY ONCE
        }
    }
}

//This function uses the distdance formula given in the doc to determind if the pixel is inside the circle
bool pointInsideCircle(int x, int y, Circle *c){
    float distdance = sqrt((x - c->center.x) * (x - c->center.x) + (y - c->center.y) * (y - c->center.y));

    float radius = sqrt(c->radius * c->radius);

    return (distdance <= radius);
}

//This function uses the formulas given in the docs to determine if the point is inside of the triangle
bool pointInsideTriangle(int x, int y, Triangle *t){

    //Since the denominator is the same in both equations putting it only once at the beginning to reduce redundancy
    float denominator = ((t->point2.y - t->point3.y) * (t->point1.x - t->point3.x) + (t->point3.x - t->point2.x) * (t->point1.y - t->point3.y));

    float a =
    ((t->point2.y - t->point3.y) * (x - t->point3.x) + (t->point3.x - t->point2.x) * (y - t->point3.y)) / denominator;

    float b = 
    ((t->point3.y - t->point1.y) * (x - t->point3.x) + (t->point1.x - t->point3.x) * (y - t->point3.y)) / denominator;

    float c = 1 - a - b;

    //Now that we have our a, b, and c values, we can easily return our bool value
    return ((a >= 0 && a <= 1) && (b >= 0 && b <= 1) && (c >= 0 && c <= 1));
}

//We use our pointInsideTriangle function by cutting the rectangle in half and checking both halfs
bool pointInsideRectangle(int x, int y, Rectangle *r){
    Triangle triangle1;
    Triangle triangle2;

    //Here we make two distinct triangles, each are half of the rectangle
    triangle1.point1.x = r->point1.x;
    triangle1.point1.y = r->point1.y;
    triangle1.point2.x = r->point2.x;
    triangle1.point2.y = r->point2.y;
    triangle1.point3.x = r->point3.x;
    triangle1.point3.y = r->point3.y;

    triangle2.point1.x = r->point1.x;
    triangle2.point1.y = r->point1.y;
    triangle2.point2.x = r->point3.x;
    triangle2.point2.y = r->point3.y;
    triangle2.point3.x = r->point4.x;
    triangle2.point3.y = r->point4.y;

    //If the point is inside the rectangle return true
    return (pointInsideTriangle(x, y, &triangle1) || pointInsideTriangle(x, y, &triangle2));
}