#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define PASS 55

/*===========================FUNCTION DECLARATIONS===========================*/
float courseAvg(int length, int grades[]);
float coursePass(int length, int grades[]);
int findMin(int length, int grades[]);
int findMax(int length, int grades[]);
void gradePrint(FILE* fp, int length, int grades[]);
int courseMedian(int length, int grades[]);
int getFileLength(FILE* fp);
void swap(int* source, int* destinaton);
void bubbleSort(int length, int grades[]);
/*===========================================================================*/


//REMINDER: USE "%0.2f" WHEN PRINTING FLOAT (PASS PRECENTAGE)
//REMINDER: USE "%0.3f" WHEN PRINTING FLOAT (COURSE AVERAGE)
//ALERT: AT THE END OF THE GRADES FILE THERE SHOULD BE AN EMPTY LINE
int main(int argc, char* argv[]) {
    if (argc < 1) {
        fprintf(stderr, "Error\n");
        return 1;
    }

    char coursename[33];
    strcpy(coursename,argv[1]);
    strcat(coursename,"_stat/course_statistics.txt");
    strcat(argv[1],"_stat/grades.txt");
    
    //argv[1] name of course
    FILE* gradefile = fopen(argv[1], "r");
    int length = getFileLength(gradefile);
    fclose(gradefile);


    gradefile = fopen(argv[1], "r");
    if (gradefile == NULL) {
        printf("Could not open file %s \n", "grades.txt");
        return 1;
    }

    int* grades = (int*)malloc(length * sizeof(int));
    if (grades == NULL) {
        printf("Could not allocate memory \n");
        return 1;
    }

    for (int i = 0; i < length; i++) {
        if (fscanf(gradefile, "%d", &grades[i]) == 0) {
            printf("Could not scan grades.txt properly \n");
            return 1;
        }
    }
    fclose(gradefile);

    bubbleSort(length, grades);

    //makes a statistics file for "w"riting
    
    FILE* statfile = fopen(coursename, "w");
    if (statfile == NULL) {
        printf("Could not open file %s \n", "course_statistics.txt");
        return 1;
    }
    
    fprintf(statfile, "num of students = %d \n", length);
    fprintf(statfile, "avg = %0.3f \n", courseAvg(length, grades));
    fprintf(statfile, "the median is - %d \n", courseMedian(length, grades));
    fprintf(statfile, "max grade = %d, ", findMax(length, grades));
    fprintf(statfile, "min grade = %d \n", findMin(length, grades));
    fprintf(statfile, "pass rate = %0.2f%% \n", coursePass(length, grades));
    gradePrint(statfile, length, grades);
    fclose(statfile);
    free(grades);
    return 0;
}

//Sorts array in Ascending orders
void bubbleSort(int length, int grades[]) {
    for (int i = 0; i < length - 1; i++) {   
        for (int j = 0; j < length - i - 1; j++) {
            if (grades[j] > grades[j + 1]) {
                swap(&grades[j], &grades[j + 1]);
            }
        }
    }
}

//Switches places between two int pointers
void swap(int* first, int* second) {
    int temp = *first;
    *first = *second;
    *second = temp;
}

//Given an array of grades, returns the average with 3 decimal point accuracy
float courseAvg(int length, int grades[]) {
    float sum = 0;
    for (int i = 0; i < length; i++) {
        sum += grades[i];
    }
    float avg = sum / length;
    return (avg);
}

//Given an array of grades, calculates the Pass%
float coursePass(int length, int grades[]) {
    float pass = 0;
    for (int i = 0; i < length; i++) {
        if(grades[i]>=PASS) {
            pass++;
        }
    }

    pass = (pass / length)*100;
    return pass;
}

//Given an array, Finds the minimum 
int findMin(int length,int grades[]) {
    int min = grades[0];
    for (int i = 0; i < length; i++) {
        if (min>=grades[i]) {
            min = grades[i];
        }
    }
    return min;
}

//Given an array, Finds the maximum 
int findMax(int length, int grades[]) {
    int max = grades[0];
    for (int i = 0; i < length; i++) {
        if (max <= grades[i]) {
            max = grades[i];
        }
    }
    return max;
}

//Prints the given array as a 10 x 10 matrix into the file
void gradePrint(FILE* fp,int length, int grades[]) {
    int histogram[100] = {0};
    int count = 0;

    for (int i = 0; i < length; i++) {
        ++histogram[grades[i]-1];
    }

    for (int i = 0; i < 100; i++) {
        ++count;
        fprintf(fp,"%d ", histogram[i]);
        if (count == 10) {
            count = 0;
            fprintf(fp, "\n");
        } 
    }
}

//Given an array of grades, returns the median grade
int courseMedian(int length, int grades[]) {
    int median = 0;
    int half = length / 2;
    if (length % 2 == 0) {
        median = (grades[half] + grades[half -1]) / 2;
    }
    else {
        median = grades[half];
    }
    return median;
}

//Find amount of lines in grades.txt
int getFileLength(FILE* fp) {
    int length = 0;
    //opens grade file for "r"eading
    if (fp == NULL) {
        printf("Could not open file %s \n", "grades.txt");
        return 1;
    }


    //find amount of lines
    for (char c = getc(fp); c != EOF; c = getc(fp)) {
        if (c == '\n') {
            ++length;
        }
    
    }

    return length;
}