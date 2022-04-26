#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 5

typedef struct address {
    char *streetAddress;
    int zipcode;
    char city[50];
    char countryCode[4];
} address;

typedef struct student {
    double grade;
    char *name;
    address *addressData;
} student;

student *createStudent(char *name, double grade, char *streetAddress, int zipcode, char *cityName, char *countryCode) {

    // dynamically allocate the student
    student *newStudent = malloc(sizeof(student));
    
    // set the static grade
    newStudent->grade = grade;

    // dynamically allocate the student name and copy it over
    newStudent->name = malloc(sizeof(char) * (strlen(name)+1));
    strcpy(newStudent->name, name);

    // dynamically allocate the address to the student struct
    newStudent->addressData = malloc(sizeof(address));

    // set the static zipcode in the pointer to address
    newStudent->addressData->zipcode = zipcode;

    // copy over the countryCode and city into these static fields in the pointer to address
    strcpy(newStudent->addressData->countryCode, countryCode);
    strcpy(newStudent->addressData->city, cityName);
    
    // dynamically allocate the street address and copy it over
    newStudent->addressData->streetAddress = malloc(sizeof(char)*(strlen(streetAddress)+1));
    strcpy(newStudent->addressData->streetAddress, streetAddress);

    return newStudent;
};

// assume the student is non NULL and they have all DMA-able fields DMA'd
void freeStudent(student *stu) {
    free(stu->name);
    free(stu->addressData->streetAddress);
    free(stu->addressData);
    free(stu);
};

// free students in a 1d array.
void freeStudents(student *students, int n) {
    for (int x = 0; x < n; ++x) {
        free(students[x]->name);
        free(students[x]->addressData->streetAddress);
        free(students[x]->addressData);
    };

    free(students);
};

// free students in a 2d array.
void freeStudents(student **students, int n, int m) {
    for (int x = 0; x < n; ++x) {
        for (int y = 0; y < m; ++y) {
            free(students[x][y]->name);
            free(students[x][y]->addressData->streetAddress);
            free(students[x][y]->addressData);
        };

        free(students[x]);
    };

    free(students);
};

char **initializeBoard(int n, int m) {
    // initialize the array of pointers to character arrays
    char **board = malloc(sizeof(char*)*n);

    // iterate through the n pointer array
    for (int x = 0; x < n; x++) {
        // allocate each array of size m to each pointer to character arrays
        board[x] = malloc(sizeof(char)*m);
        // set initial value _ to each location on the board...
        for (int y = 0; y < m; y++)
            board[x][y] = '_';
    };

    // return pointer to 2d array...
    return board;
};

// assume the board was non NULL.
void freeBoard(char **board, int n) {
    for (int x = 0; x < n; x++)
        free(board[x]);
    free(board);
}



/*
Another key reason for DMA: We want to make functions to make code more modular and not repeat code.
This gives the following error:

.\dma.c: In function 'makeArray':
.\dma.c:10:12: warning: function returns address of local variable [-Wreturn-local-addr]
     return array;

int *makeArray(int n) {
    int array[n];
    return array;
};
*/

// With Dynamic Memory Allocation, this works just fine.
int *makeArray(int n) {
    int *array = malloc(sizeof(int)*n);
    for (int x = 0; x < n; x++)
        scanf("%d", &array[x]);
    return array;
};

// Takes in LOWERCASE word and counts the frequency of each character that appears.
int *calculateFrequencyArray(char *str) {
    int *frequencies = calloc(26, sizeof(int)), x = 0;

    while (str[x] != '\0') {
        frequencies[str[x]-'a']++;
        x++;
    };

    return frequencies;
};

int main () {

    /*===================STATIC MEMORY ALLOCATION===================*/

    // All of these declarations are forms of static memory allocation.
    int staticArray1[5];
    int staticArray2[SIZE];

    // using "magic number" 5
    for (int x = 0; x < 5; x++)
        scanf("%d", &staticArray1[x]);

    printf("Static Array 1 contains:\t");
    for (int x = 0; x < 5; x++)
        printf("%d ", staticArray1[x]);
    printf("\n");

    // using defined constant
    // alternatively, this can be done by: const int SIZE = 5; instead of a define...
    for (int x = 0; x < SIZE; x++)
        scanf("%d", &staticArray2[x]);

    printf("Static Array 2 contains:\n");
    for (int x = 0; x < SIZE; x++)
        printf("%d ", staticArray2[x]);
    printf("\n");


    /*
    
    While this works great when we KNOW the size of the data the program will handle, what if it is variable?
    
    int n;
    scanf("%d", &n);
    int arr[n];

    // while doing this and reading in n values into arr will most likely work on your computer,
    // older versions of c do not support variable length arrays like this. This is where dynamic memory allocation comes in.

    */


    /*===================DYNAMIC MEMORY ALLOCATION===================*/

    int n;
    scanf("%d", &n);

    // dynamically allocates a DMA array of n integers...
    int *dmaArray = malloc(sizeof(int)*n);

    // it works the same as a regular array in terms of usage
    for (int x = 0; x < SIZE; x++)
        scanf("%d", &dmaArray[x]);

    printf("DMA Array contains:\n");
    for (int x = 0; x < SIZE; x++)
        printf("%d ", dmaArray[x]);
    printf("\n");

    return 0;
}