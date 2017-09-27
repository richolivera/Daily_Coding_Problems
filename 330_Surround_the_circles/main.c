/*
 * Assumptions:
 *     1) No input sanitization will be necessary.
 *     2) 4 coordinates will always be entered as input.
 *     3) only one tilt vector will be entered (but does not have
 *     to be first
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <float.h>
#include <math.h>

#define MAX_STRING_LENGTH 80
#define CIRCLE_COUNT 4

typedef struct point{
    float x;
    float y;
}point_t;

typedef struct line {
    float slope;
    float yIntercept;
}line_t;

typedef struct circle{
    point_t centerPoint;
    float radius;
    line_t firstParallelTangent;
    line_t secondParallelTangent;
    line_t firstPerpendicularTangent;
    line_t secondPerpendicularTangent;
}circle_t;

enum edges{
MAX_PARALLEL = 0,
MIN_PARALLEL,
MAX_PERPENDICULAR,
MIN_PERPENDICULAR
};

/*
 * function: calculateIntersectionPoint()
 * inputs: line_t lineA
 *         line_t lineB 
 * returns: point_t 
 */
point_t findIntersectionPoint(line_t lineA, line_t lineB)
{
   point_t outputPoint;
   outputPoint.x = (lineB.yIntercept-lineA.yIntercept)/(lineA.slope - lineB.slope);
   outputPoint.y = (lineB.slope*lineA.yIntercept - lineA.slope*lineB.yIntercept)/(lineB.slope - lineA.slope);
   return outputPoint;
}



/*
 * function: calculateTangentLines 
 * inputs: circle_t * circ - object that contains center point and radius and 
 *                           has it's line objects populated by this function
 *         float axisSlope - slope of tilt vector
 *
 */
void calculateTangentLines(circle_t * circ, float axisSlope)
{
    float a = 0; //y radial component
    float b = 0; //x radial component
    float centerX = circ->centerPoint.x;
    float centerY = circ->centerPoint.y;
   
    // get tangent point components. Each line is a combination of two formulas
    // 1) radius^2 = a^2 + b^2 (pythagoras)
    // 2) slope = a/b (slope = rise over run)
    a = sqrt(pow(circ->radius, 2)/(1+1/pow(axisSlope, 2)));
    b = sqrt(pow(circ->radius, 2)/(1+pow(axisSlope, 2)));
   
    //set tangent lines perpendicular to slope
    circ->firstPerpendicularTangent.slope = (-1/axisSlope);
    circ->firstPerpendicularTangent.yIntercept = (centerY+a)-(-1/axisSlope)*(centerX+b);

    circ->secondPerpendicularTangent.slope = (-1/axisSlope);
    circ->secondPerpendicularTangent.yIntercept = (centerY-a)-(-1/axisSlope)*(centerX-b);

    //set tangent lines parallel to slope
    circ->firstParallelTangent.slope = axisSlope;
    circ->firstParallelTangent.yIntercept = (centerY+a)-axisSlope*(centerX-b);

    circ->secondParallelTangent.slope = axisSlope;
    circ->secondParallelTangent.yIntercept = (centerY-a)-axisSlope*(centerX+b);
   
}



/*
 * function: 
 * Description: identify outermost rectagular Bounds
 *
*/
void findRectangle(const circle_t * circArr, int circArrLen, line_t * rect )
{
    int i = 0;
    //initialize rectangle_edges array to one parallel and one perpendicular line
    rect[MAX_PARALLEL].slope = circArr[0].firstParallelTangent.slope;
    rect[MAX_PARALLEL].yIntercept = circArr[0].firstParallelTangent.yIntercept;
    rect[MIN_PARALLEL].slope = circArr[0].firstParallelTangent.slope;
    rect[MIN_PARALLEL].yIntercept = circArr[0].firstParallelTangent.yIntercept;
    rect[MAX_PERPENDICULAR].slope = circArr[0].firstPerpendicularTangent.slope;
    rect[MAX_PERPENDICULAR].yIntercept = circArr[0].firstPerpendicularTangent.yIntercept;
    rect[MIN_PERPENDICULAR].slope = circArr[0].firstPerpendicularTangent.slope;
    rect[MIN_PERPENDICULAR].yIntercept = circArr[0].firstPerpendicularTangent.yIntercept;

    // for each circle, check to see if it has tangent 
    // lines greater than max or less than min 
    for(i=0; i<circArrLen; i++)
    {
        if(circArr[i].firstParallelTangent.yIntercept > rect[MAX_PARALLEL].yIntercept)
        {
            rect[MAX_PARALLEL].yIntercept = circArr[i].firstParallelTangent.yIntercept;
        }
        if(circArr[i].firstParallelTangent.yIntercept < rect[MIN_PARALLEL].yIntercept)
        {
            rect[MIN_PARALLEL].yIntercept = circArr[i].firstParallelTangent.yIntercept;
        }
        if(circArr[i].secondParallelTangent.yIntercept > rect[MAX_PARALLEL].yIntercept)
        {
            rect[MAX_PARALLEL].yIntercept = circArr[i].secondParallelTangent.yIntercept;
        }
        if(circArr[i].secondParallelTangent.yIntercept < rect[MIN_PARALLEL].yIntercept)
        {
            rect[MIN_PARALLEL].yIntercept = circArr[i].secondParallelTangent.yIntercept;
        }

        if(circArr[i].firstPerpendicularTangent.yIntercept > rect[MAX_PERPENDICULAR].yIntercept)
        {
            rect[MAX_PERPENDICULAR].yIntercept = circArr[i].firstPerpendicularTangent.yIntercept;
        }
        if(circArr[i].firstPerpendicularTangent.yIntercept < rect[MIN_PERPENDICULAR].yIntercept)
        {
            rect[MIN_PERPENDICULAR].yIntercept = circArr[i].firstPerpendicularTangent.yIntercept;
        }
        if(circArr[i].secondPerpendicularTangent.yIntercept > rect[MAX_PERPENDICULAR].yIntercept)
        {
            rect[MAX_PERPENDICULAR].yIntercept = circArr[i].secondPerpendicularTangent.yIntercept;
        }
        if(circArr[i].secondPerpendicularTangent.yIntercept < rect[MIN_PERPENDICULAR].yIntercept)
        {
            rect[MIN_PERPENDICULAR].yIntercept = circArr[i].secondPerpendicularTangent.yIntercept;
        }
    }
}

int main(int argc, char * argv[])
{
   char inputLine[MAX_STRING_LENGTH];
   char * ptr;
   int i = 0;
   int j = 0;
   float tiltX = 0;
   float tiltY = 0 ;
   circle_t circles[CIRCLE_COUNT];
   line_t rectangle_edges[4];
   point_t Point1;
   point_t Point2;
   point_t Point3;
   point_t Point4;
   float xMin = FLT_MAX;
   float xMax = -FLT_MAX;
   float yMin = FLT_MAX;
   float yMax = -FLT_MAX;

   // prompt user for input
   printf("Please enter coordinates and radii ( 1 (optional) line in format: \"x,y\" and 4 lines in format: \"x,y,rad\" )\n");

   //loop to get user input
   for(i=0; i<CIRCLE_COUNT; i++)
   {
      //readline
      fgets(&inputLine[0], MAX_STRING_LENGTH, stdin);
      //count the number of commas
      //store radius in inputStruct
      circles[i].centerPoint.x = atof(strtok(inputLine, ","));
      circles[i].centerPoint.y = atof(strtok(NULL,","));
      ptr = strtok(NULL,",");
      if(ptr != NULL)
      {
          circles[i].radius = atof(ptr);
      }
      else
      {
          //the first line is actually rectangle tilt. Decrement i and set tilt
          //values accordingly
          tiltX = circles[i].centerPoint.x;
          tiltY = circles[i].centerPoint.y;
          i--;
      }
      
   }
   
   //if slope is non-zero
   if(0 != tiltY && 0 != tiltX)
   {
       //loop to get calculate tangentLines
       for(i=0; i<CIRCLE_COUNT; i++)
       {
           calculateTangentLines(&circles[i], (tiltY/tiltX));
       }
       findRectangle(circles, CIRCLE_COUNT, rectangle_edges);

   Point1 = findIntersectionPoint(rectangle_edges[MIN_PARALLEL],
           rectangle_edges[MIN_PERPENDICULAR]);
   Point2 = findIntersectionPoint(rectangle_edges[MIN_PARALLEL], 
           rectangle_edges[MAX_PERPENDICULAR]);
   Point3 = findIntersectionPoint(rectangle_edges[MAX_PARALLEL], 
           rectangle_edges[MIN_PERPENDICULAR]);
   Point4 = findIntersectionPoint(rectangle_edges[MAX_PARALLEL], 
           rectangle_edges[MAX_PERPENDICULAR]);


   printf("(%.3f,%.3f),(%.3f,%.3f),(%.3f,%.3f),(%.3f,%.3f)\n", 
           Point1.x, Point1.y, Point2.x, Point2.y, Point3.x, Point3.y, Point4.x, Point4.y);

   }
   else
   {
       //loop to find Maxes and Mins.  Parallel = y, Perpendicular =x
       for(i=0; i<CIRCLE_COUNT; i++)
       {
           if((circles[i].centerPoint.x - circles[i].radius) < xMin) {
               (xMin = (circles[i].centerPoint.x - circles[i].radius));}   
           if((circles[i].centerPoint.x + circles[i].radius) > xMax) {
               (xMax = (circles[i].centerPoint.x + circles[i].radius));}   
           if((circles[i].centerPoint.y - circles[i].radius) < yMin) {
               (yMin = (circles[i].centerPoint.y - circles[i].radius));}   
           if((circles[i].centerPoint.y + circles[i].radius) > yMax) {
               (yMax = (circles[i].centerPoint.y + circles[i].radius));}   
       }
   printf("(%.3f,%.3f),(%.3f,%.3f),(%.3f,%.3f),(%.3f,%.3f)\n", 
           xMin, yMin, xMin, yMax, xMax, yMax, xMax, yMin);
   }
}






