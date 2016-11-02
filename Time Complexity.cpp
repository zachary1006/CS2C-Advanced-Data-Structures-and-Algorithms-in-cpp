/*
Name: Zachary Simon
Class: CS 2C
Due Date: 10/17/2016
Instructor: Dave Harden
Name of File: a3_1.cpp


This program implements a large 2-D array as an array of float pointers to another 
set of dynamically allocated arrays. The typedef is DynMat[size]. Furthermore, the 
array is initialized and used to compute the running time of a basic matrix 
multiplication algorithm. The matrix size, MAT_SIZE, should be specified before 
running. 


Before I began this project, I looked at my code and gave an estimate of what the run 
time would be. The most significant part of my code was the nested for-loop necessary 
to multiply the two matrices together. That made the function O(N^2), or quadratic. 
Computing my Theta estimate was similar. There was no "best" or "worst" scenario 
here - all of the numbers had to be read in each matrix every single time. (Or, 
at least I could not think of a shortcut to take.) That made the function Theta(N^2), 
still quadratic. (As I coded, I realized this was wrong.) 


1. What was the smalles M that gave you a non-zero time? 
    A: When I set MAT_SIZE to 50, I got either 0 or 0.001. 

2. What happened when you doubled M, tripled it, quadrupled it, etc.? Give several 
    M values and their times in a table. 
    A: The relationship between M and the runtime wasn't linear, but I expected that. 
        Every time I double M, I add many more new cells to be allocated. 

    MAT_SIZE    |   Time
    ------------|---------------
    100         |    0.006 seconds
    200         |    0.046 s
    300         |    0.157 s
    400         |    0.618 s
    500         |    0.885 s
    1000        |   11.872 s
    1500        |   40.315 s
    2000        |  114.865 s
    2500        |  225.517 s
    5000        | 1862.88  s

3. How large an M can you use before the program refuses to run (exception or runtime 
    error due to memory overload) or it takes so long you can't wait for the run? 
    A: At 5000 it was over 30 minutes. I let that be the last one I tried. 

4. How did the data agree or disagree with your original time complexity estimate? 
    A: I expected the complexity to be quadratic because of a nested for-loop. 
        However, I made a mistake in my original algorithm design and because of 
        that, I was off by quite a bit. Doubling the size of the matrix didn't 
        double the time, or even cause it to square - it was, in at least one 
        place, over a factor of 10. 

*/

#include <iostream> 
#include <time.h>
#include <cstdlib>
#include <cstdio>

using namespace std; 

const int MAT_SIZE = 100;          //The size of the matrix we are initializing
typedef float* DynMat[MAT_SIZE];

void matMultDyn(const DynMat &matA, const DynMat &matB, DynMat &matC, int size);

void matShowDyn(const DynMat &matA, int start, int size); 

int main()
{
    srand(time(0)); 
    int r, c;
    clock_t startTime, stopTime;
    float randFrac;
    int randRow, randCol, smallPercent;

    // non-sparse dynamic matrix
    DynMat matDyn, matDynAns;


    // allocate rows and initialize to 0
    for (r = 0; r < MAT_SIZE; ++r)
    {
        matDyn[r] = new float[MAT_SIZE];
        matDynAns[r] = new float[MAT_SIZE];
        
        for (c = 0; c < MAT_SIZE; ++c)
        {
            /*if (c == r) {
                matDyn[r][c] = 1; 
            } else*/
            matDyn[r][c] = 0;
            matDynAns[r][c] = 0;
        }
    }

    // generate small% non-default values bet .1 and 10
    smallPercent = MAT_SIZE / 20. * MAT_SIZE;  // div by 20. means 5%, of course
    for (r = 0; r < smallPercent; r++)
    {
        randFrac = (rand() % 10) / (10 / (10 - 0.1)); 
        randRow = rand() % MAT_SIZE; 
        randCol = rand() % MAT_SIZE; 

        matDyn[randRow][randCol] = randFrac; 
    }

    // 10x10 submatrix in lower right
    matShowDyn(matDyn, MAT_SIZE - 10, 10);

    startTime = clock();  // ------------------ start
    matMultDyn(matDyn, matDyn, matDynAns, MAT_SIZE);
    stopTime = clock();  // ---------------------- stop

    matShowDyn(matDynAns, MAT_SIZE - 10, 10);
    cout << "\nSize = " << MAT_SIZE << " Dyn Array Mult Elapsed Time: "
        << (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC
        << " seconds." << endl << endl;

    // clean up
    for (r = 0; r < MAT_SIZE; r++)
    {
        delete[] matDyn[r];
        delete[] matDynAns[r];
    }

        cout << endl;
}






/*
    matMultDyn multiplies two matrices, matA and matB, of size "size" and puts the 
    result in matC. 
    Preconditions: All matrices must be initialized. matC is assumed to have 0 
        in each of its values. 
    Postconditions: matA and matB remain unchanged. matC is filled with the values 
        resulting from the matrix multiplication. 
*/
void matMultDyn(const DynMat &matA, const DynMat &matB, DynMat &matC, int size)
{
    int solutionRow = 0; 
    int solutionColumn = 0; 
    for (int row = 0; row < MAT_SIZE; ++row)
    {
        for (solutionColumn = 0; solutionColumn < MAT_SIZE; ++solutionColumn) {
            for (int column = 0; column < MAT_SIZE; ++column)
            {
                matC[row][solutionColumn] += matA[row][column] * matB[column][solutionColumn];
            }
        }
    }
}






/*
    matShowDyn displays a subsection of the matrix matA that is passed in. 
    "start" is the location where the subsection begins. "size" is the size of the 
    subsection to display. In other words, the displayed matrix will be 
    size x size, and start at (start, start). 
    Precondition: matA is a valid DynMat. size cannot go over the bounds of the 
        array. 
    Postcondition: A submatrix is displayed to the screen. 
*/
void matShowDyn(const DynMat &matA, int start, int size)
{
    for (int row = start; row < start + size; ++row)
    {
        for (int column = start; column < start + size; ++column)
        {
            printf("%7.2f ", matA[row][column]); 
        }
        cout << endl; 
    }
    cout << endl; 
}






/* Sample Output

0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00
0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00
0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00
0.00    0.00    0.00    0.00    1.98    0.00    0.00    0.00    0.00    0.00
0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00
0.00    0.00    0.00    2.97    0.00    0.00    0.00    0.00    0.00    0.00
0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    5.94    0.00
0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00
0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    1.98    5.94
0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00

0.00    0.00   15.68    0.00   48.02    0.00    0.00   15.68    9.80    0.00
0.00   89.19    0.00   34.30    0.00   11.76    0.00   47.04    3.92    0.00
0.00    0.00   35.28    0.00    0.00    0.00    0.00   23.52   26.46    0.00
0.00   79.39    5.88    0.00    0.00    0.00   23.52    0.00    0.00    0.00
0.00    0.00    0.00    0.00    0.00   33.32    0.00    0.00    0.00    0.00
0.00    0.00    0.98    0.00   49.99    0.00    0.00    1.96    0.00    0.00
21.56    7.84    0.00   29.40    0.00    0.00    0.00   52.93   32.34   35.28
54.89   34.30   17.64    0.00    6.86   47.04   23.52    0.00    0.00    0.00
9.80   31.36    6.86    0.00    0.00    3.92    0.00    0.00   15.68   19.60
39.20    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00


Size = 300 Dyn Array Mult Elapsed Time: 0.164 seconds.


*/