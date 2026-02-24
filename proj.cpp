#include <iostream>
#include <stdexcept>
#include <cmath>

using namespace std;

class Matrix{
    public:
    int matrix_rows;
    int matrix_cols;
    int** matrix_table;
    Matrix(int rows, int cols) : matrix_rows(rows), matrix_cols(cols){ //прописываем конструтор матрицы:
        if(rows < 0 || cols < 0) throw invalid_argument("Your rows or cols are less then a zero");
        matrix_table = new int*[rows]; //создаем двумерный массив
        for(int i = 0; i < rows; i++){
            matrix_table[i] = new int[cols];
            }
        }
    ~Matrix(){ //прописываем деструтор матрицы
        for(int i = 0; i < matrix_rows; i++){
            delete[] matrix_table[i];
        }
        delete[] matrix_table;
    }

    Matrix(const Matrix& other) : matrix_rows(other.matrix_rows), matrix_cols(other.matrix_cols), matrix_table(nullptr){ //рождение человека, то есть поля надо заполнить сразу
        if(matrix_cols == 0 || matrix_rows == 0){
            return;
        }
        matrix_table = new int*[matrix_rows];
        for (int i = 0; i < matrix_rows; i++) {
            matrix_table[i] = new int[matrix_cols];
            for (int j = 0; j < matrix_cols; j++) {
                matrix_table[i][j] = other.matrix_table[i][j];
            }
        }
    
    }

    Matrix& operator=(const Matrix& other){ //хорошая аналогия со сменой паспорта, ведь человек уже есть, надо просто поменять значение полей
        if(this == &other){
            return *this;
        }
        for(int i = 0; i < matrix_rows; i++){
            delete[] matrix_table[i];
        }
        delete[] matrix_table;
        matrix_cols = other.matrix_cols;
        matrix_rows = other.matrix_rows;
        matrix_table = nullptr;
        if(matrix_cols == 0 || matrix_rows == 0){
            return *this;
        }
        matrix_table = new int*[matrix_rows];
        for(int i = 0; i < matrix_rows; i++){
            matrix_table[i] = new int[matrix_cols];
            for(int j = 0; j < matrix_cols; j++){
                matrix_table[i][j] = other.matrix_table[i][j];
            }
        }
        return *this;
    }

    Matrix operator+(const Matrix& other) const{ //оператор сложения матриц
        if (matrix_cols != other.matrix_cols || matrix_rows != other.matrix_rows) throw invalid_argument("Matrix sizes dont match");
        Matrix result(matrix_rows, matrix_cols);
        for(int i = 0; i < matrix_rows; i++){
            for(int j = 0; j < matrix_cols; j++){
                result.matrix_table[i][j] = matrix_table[i][j] + other.matrix_table[i][j];
            }
        }
        return result;
    }

    Matrix operator*(const Matrix& other) const{ // опреатор умножения матриц
        if (matrix_cols != other.matrix_rows) throw invalid_argument("Matrix sizes dont match");
        Matrix result(matrix_rows, other.matrix_cols);
        for(int i = 0; i < matrix_rows; i++){
            for(int j = 0; j < other.matrix_cols; j++){
                int cur_sum = 0;
                for(int r = 0; r < matrix_cols; r++){
                    cur_sum += matrix_table[i][r] * other.matrix_table[r][j];
                }
                result.matrix_table[i][j] = cur_sum;
            }
        }
        return result;
    }
    Matrix operator*(int value) const{ //опреатор скалярного произведения
        Matrix result(matrix_rows, matrix_cols);
        for(int i = 0; i < matrix_rows; i++){
            for(int j = 0; j < matrix_cols; j++){
                result.matrix_table[i][j] = matrix_table[i][j] * value;
            }
        }
        return result;
    }

    float find_frobenius_norm() const{
        double norm = 0.0;
        for(int i = 0; i < matrix_rows; i++){
            for(int j = 0; j < matrix_cols; j++){
                norm += pow(matrix_table[i][j], 2);
            }
        }
        return sqrt(norm);
    }
};

int main(){
    return 0;
}