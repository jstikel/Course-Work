/*************************
 *Josh Stikeleather
 *CPSC 2310 002
 *jstikel@clemson.edu
 *************************/

#include "ppm.h"
#include "shapes.h"

//This reads in the entire input.txt and fills our structs with the correct info
void readPPMInput(FILE *in, PPMImage *img, struct Circle *c, struct Triangle *t, struct Rectangle *r, ShapeOrder *order){
    //First we read the header
    fscanf(in, "%s %d %d %d", img->magicNumber, &img->width, &img->height, &img->maxColor);

    int numOfShapes;
    fscanf(in, "%d", &numOfShapes);

    //This stores how many shapes we have
    order->count = numOfShapes;

    //Varible to store what kind of shape we are saving each iteration
    char shapeType[4];

    //For loop to run through the rest of the input.txt file numOfShapes times
    for (int i = 0; i < numOfShapes; i++){
        fscanf(in, "%s", shapeType);

        //IF this iteration's identifyer is "Cir", then we will update the Circle structs info
        if (strcmp(shapeType, "Cir") == 0){
            //We remember that this shape in position "i" is a circle
            order->types[i] = SHAPE_CIRCLE;

            //Then we read the circle's center and radius
            fscanf(in, "%d %d %d", &c->center.x, &c->center.y, &c->radius);

            //Then we read the color of the Circle
            fscanf(in, "%hhu %hhu %hhu", &c->color.r, &c->color.g, &c->color.b);
        }

        //IF this iteration's identifyer is "Tri", then we will update the Triangle structs info
        if (strcmp(shapeType, "Tri") == 0){
            //We remember that this shape in position "i" is a triangle
            order->types[i] = SHAPE_TRIANGLE;

            //Scan in our triangles points
            fscanf(in, "%d %d %d %d %d %d", 
                &t->point1.x, &t->point1.y,
                &t->point2.x, &t->point2.y,
                &t->point3.x, &t->point3.y
            );
            //Then we read the color of the Triangle
            fscanf(in, "%hhu %hhu %hhu", &t->color.r, &t->color.g, &t->color.b);
        }

        //IF this iteration's identifyer is "Qua", then we will update the Rectangle structs info
        if (strcmp(shapeType, "Qua") == 0){
            //We remember that this shape in position "i" is a rectangle
            order->types[i] = SHAPE_RECTANGLE;

            //Scan in our rectangles points
            fscanf(in, "%d %d %d %d %d %d %d %d", 
                &r->point1.x, &r->point1.y,
                &r->point2.x, &r->point2.y,
                &r->point3.x, &r->point3.y,
                &r->point4.x, &r->point4.y
            );
            //Then we read the color of the Rectangle
            fscanf(in, "%hhu %hhu %hhu", &r->color.r, &r->color.g, &r->color.b);
        }
    }
    fscanf(in, "%hhu %hhu %hhu", &img->background.r, &img->background.g, &img->background.b);

}

//This writes the PPM header into the ppm
void writePPMHeader(FILE *out, PPMImage *img){
    fprintf(out, "%s\n%d %d\n%d\n", img->magicNumber, img->width, img->height, img->maxColor);
}