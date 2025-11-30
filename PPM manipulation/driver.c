/*************************
 *Josh Stikeleather
 *CPSC 2310 002
 *jstikel@clemson.edu
 *************************/

#include <stdio.h>
#include <assert.h>
#include "shapes.h"

int main(){
    FILE *inFile  = fopen("input.txt", "r");
    //The out file MUST be binary
    FILE *outFile = fopen("output.ppm", "wb");

    assert(inFile  != NULL);
    assert(outFile != NULL);

    //Structs to hold input data
    PPMImage img;
    Circle c;
    Triangle t;
    Rectangle r;
    ShapeOrder order;

    //Read the header and circle info from input file
    readPPMInput(inFile, &img, &c, &t, &r, &order);

    //Now we write the ppm header to output file
    writePPMHeader(outFile, &img);

    //Finally we draw the shapes into the PPM
    drawShapes(outFile, &img, &c, &t, &r, &order);

    fclose(inFile);
    fclose(outFile);

    return 0;
}