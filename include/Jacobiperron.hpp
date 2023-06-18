#include <iostream>
#include <iomanip>
#include <cmath>

class Jacobiperron {
public:
    Jacobiperron(int matrixSize, double tolerance = 1e-6, int maxIterations = 100)
        : size(matrixSize), tol(tolerance), maxIter(maxIterations)
    {
        A = new double*[size];
        for (int i = 0; i < size; ++i)
            A[i] = new double[size];

        b = new double[size];
        x = new double[size];
    }

    ~Jacobiperron() {
        for (int i = 0; i < size; ++i)
            delete[] A[i];

        delete[] A;
        delete[] b;
        delete[] x;
    }

    void setMatrixCoefficient(int row, int col, double value) {
        if (row >= 0 && row < size && col >= 0 && col < size)
            A[row][col] = value;
    }

    void setVectorValue(int index, double value) {
        if (index >= 0 && index < size)
            b[index] = value;
    }

    void setInitialGuess(int index, double value) {
        if (index >= 0 && index < size)
            x[index] = value;
    }

    void solve() {
        if (!isDiagonallyDominant()) {
            std::cout << "La matriz A no es diagonalmente dominante. Modificando la matriz..." << std::endl;
            makeDiagonallyDominant();
        }

        int iter = 0;
        double* xNew = new double[size];
        double error = tol + 1;

        std::cout << "Iteracion 0:" << std::endl;
        printResult(x, size, decimals);

        while (error > tol && iter < maxIter) {
            for (int i = 0; i < size; ++i) {
                xNew[i] = b[i];

                for (int j = 0; j < size; ++j) {
                    if (j != i) {
                        xNew[i] -= A[i][j] * x[j];
                    }
                }

                xNew[i] /= A[i][i];
            }

            error = 0;

            for (int i = 0; i < size; ++i) {
                error += std::abs((xNew[i] - x[i]) / xNew[i]);
                x[i] = xNew[i];
            }

            ++iter;

            std::cout << "Iteracion " << iter << ":" << std::endl;
            printResult(x, size, decimals);
        }

        if (iter == maxIter) {
            std::cout << "El metodo de Jacobi no convergio en " << maxIter << " iteraciones." << std::endl;
        } else {
            std::cout << "Solucion encontrada en " << iter << " iteraciones:" << std::endl;
            printResult(x, size, decimals);
        }

        delete[] xNew;
    }

private:
    void printMatrix() {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                std::cout << std::setw(8) << std::fixed << std::setprecision(2) << A[i][j] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    void printResult() {
        for (int i = 0; i < size; ++i) {
            std::cout << "x[" << i << "] = " << std::fixed << std::setprecision(decimals) << x[i] << std::endl;
        }
        std::cout << std::endl;
    }

    bool isDiagonallyDominant() {
        for (int i = 0; i < size; ++i) {
            double sum = 0;

            for (int j = 0; j < size; ++j) {
                if (j != i) {
                    sum += std::abs(A[i][j]);
                }
            }

            if (std::abs(A[i][i]) <= sum) {
                return false;
            }
        }

        return true;
    }

    void makeDiagonallyDominant() {
        for (int i = 0; i < size; ++i) {
            double maxVal = std::abs(A[i][i]);
            int maxIdx = i;

            for (int j = i + 1; j < size; ++j) {
                if (std::abs(A[j][i]) > maxVal) {
                    maxVal = std::abs(A[j][i]);
                    maxIdx = j;
                }
            }

            if (maxIdx != i) {
                for (int k = 0; k < size; ++k) {
                    std::swap(A[i][k], A[maxIdx][k]);
                }
                std::swap(b[i], b[maxIdx]);
            }
        }

        std::cout << std::endl << "Matriz diagonalmente dominante A:" << std::endl;
        printMatrix();
    }

    int size;
    double tol;
    int maxIter;
    int decimals = 6;
    double** A;
    double* b;
    double* x;
};