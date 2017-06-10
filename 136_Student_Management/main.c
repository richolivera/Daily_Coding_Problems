#include <stdio.h>
#include <stdlib.h>

#define MAX_STUDENT_NAME_LENGTH 80

int main(int argc, char * argv)
{
    char * studentNames[60] = {NULL};
    int studentGrade;
    double studentAverages[60];
    double classAverage = 0;
    int numStudents = 0;
    int numAssignments = 0;
    int i,j;
    
    //process first line of input
    scanf("%i %i", &numStudents, &numAssignments);
    //process student & grade input
    for(i = 0; i < numStudents; i++)
    {
        studentNames[i] = malloc(MAX_STUDENT_NAME_LENGTH);
        scanf("%s", studentNames[i]);
        for(j = 0; j < numAssignments; j++)
        {
            scanf("%i", &studentGrade);
            if(j > 0)
                studentAverages[i] = (studentAverages[i] * (j) / (j+1)) + ((double)studentGrade/(j+1));
            else
                studentAverages[i] = studentGrade;
        }
        if(i>0)
            classAverage = (classAverage * i / (i+1)) + (studentAverages[i]/(i+1));
        else
            classAverage = studentAverages[i];
    }
    //print output
    printf("%.2f\n",classAverage);
    for(i = 0; i < numStudents; i++)
    {
        printf("%s %.2f\n", studentNames[i], studentAverages[i]);
        free(studentNames[i]);
    }
}
