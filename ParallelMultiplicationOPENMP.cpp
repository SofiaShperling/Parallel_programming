#include <iostream>
#include <cstdlib>
#include <omp.h>

using namespace std;

void randomeMatrix(int** matrix, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            matrix[i][j] = rand() % 11;
        }
    }

    return;
}

void parallelMult(int** resultMat, int** matrix11, int** matrix22, int n, int m, int l, int threadsNum)
{
    for (int i = 0; i < n; i++) {
        resultMat[i] = (int*)malloc(sizeof(int) * l);
    }

    omp_set_num_threads(threadsNum);
    int i, j, k;
#pragma omp parallel for shared(matrix11, matrix22, resultMat) private(i, j, k)
    for (i = 0; i < n; i++) {
        for (j = 0; j < l; j++) {
            resultMat[i][j] = 0;
            for (k = 0; k < m; k++) {
                resultMat[i][j] += (matrix11[i][k] * matrix22[k][j]);
            }
        }
    }

    return;
}

int main(int argc, char** argv) {
    srand(time(NULL));
    int n1 = 10;
    int m1 = 5;
    int n2 = 5;
    int m2 = 12;

    //Matrix n1 x m1
    int** matrix1;
    //Matrix n2 x m2
    int** matrix2;
    //Result matrix n1 x m2
    int** result;

    matrix1 = (int**)malloc(sizeof(int*) * n1);
    for (int i = 0; i < n1; i++) {
        matrix1[i] = (int*)malloc(sizeof(int) * m1);
    }
    matrix2 = (int**)malloc(sizeof(int*) * n2);
    for (int i = 0; i < n2; i++) {
        matrix2[i] = (int*)malloc(sizeof(int) * m2);
    }

    //Random generation of the matrixes
    randomeMatrix(matrix1, n1, m1);
    randomeMatrix(matrix2, n2, m2);

    result = (int**)malloc(sizeof(int*) * n1);;
    for (int i = 0; i < n1; i++) {
        result[i] = (int*)malloc(sizeof(int) * m2);
    }

    //Set the number of threads and do parallel multiplications
    int threadsNum = 2;

    parallelMult(result, matrix1, matrix2, n1, m1, m2, threadsNum);

    for (int i = 0; i < n1; i++) {
        for (int j = 0; j < m2; j++) {
            cout << result[i][j]<< " ";
        }
        cout << "\n";
    }

    return 0;
}