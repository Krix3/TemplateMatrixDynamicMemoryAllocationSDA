#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <stdexcept>
#include <windows.h>

using namespace std;

template <typename T>
class Matrix {
private:
    size_t rows;
    size_t cols;
    T** data;

    void allocateMemory()
    {
        data = new T * [rows];
        for (size_t i = 0; i < rows; ++i)
        {
            data[i] = new T[cols];
        }
    }

    void freeMemory() {
        for (size_t i = 0; i < rows; ++i)
        {
            delete[] data[i];
        }
        delete[] data;
    }

public:
    // Конструктор
    Matrix(size_t rows, size_t cols) : rows(rows), cols(cols)
    {
        allocateMemory();
    }

    // Конструктор копирования
    Matrix(const Matrix& other) : rows(other.rows), cols(other.cols)
    {
        allocateMemory();
        for (size_t i = 0; i < rows; ++i)
        {
            for (size_t j = 0; j < cols; ++j)
            {
                data[i][j] = other.data[i][j];
            }
        }
    }

    // Оператор присваивания
    Matrix& operator=(const Matrix& other)
    {
        if (this != &other)
        {
            freeMemory();
            rows = other.rows;
            cols = other.cols;
            allocateMemory();
            for (size_t i = 0; i < rows; ++i)
            {
                for (size_t j = 0; j < cols; ++j)
                {
                    data[i][j] = other.data[i][j];
                }
            }
        }
        return *this;
    }

    // Деструктор
    ~Matrix()
    {
        freeMemory();
    }

    // Заполнение матрицы с клавиатуры
    void fillFromInput()
    {
        cout << "Ввод элементов матрицы:" << endl;
        for (size_t i = 0; i < rows; ++i)
        {
            for (size_t j = 0; j < cols; ++j)
            {
                cin >> data[i][j];
            }
        }
    }

    // Заполнение матрицы случайными значениями
    void fillRandom(T minValue = 0, T maxValue = 100)
    {
        srand(time(nullptr));
        for (size_t i = 0; i < rows; ++i)
        {
            for (size_t j = 0; j < cols; ++j)
            {
                data[i][j] = minValue + static_cast<T>(rand()) / (static_cast<T>(RAND_MAX / (maxValue - minValue)));
            }
        }
    }

    // Отображение матрицы
    void display() const
    {
        for (size_t i = 0; i < rows; ++i)
        {
            for (size_t j = 0; j < cols; ++j)
            {
                cout << setw(5) << data[i][j] << " ";
            }
            cout << endl;
        }
    }

    // Арифметические операции
    Matrix operator+(const Matrix& other) const
    {
        if (rows != other.rows || cols != other.cols)
        {
            throw invalid_argument("Размеры матрицы должны совпадать для сложения.");
        }
        Matrix result(rows, cols);
        for (size_t i = 0; i < rows; ++i)
        {
            for (size_t j = 0; j < cols; ++j)
            {
                result.data[i][j] = data[i][j] + other.data[i][j];
            }
        }
        return result;
    }

    Matrix operator-(const Matrix& other) const
    {
        if (rows != other.rows || cols != other.cols)
        {
            throw std::invalid_argument("Размеры матрицы должны совпадать для вычитания.");
        }
        Matrix result(rows, cols);
        for (size_t i = 0; i < rows; ++i)
        {
            for (size_t j = 0; j < cols; ++j)
            {
                result.data[i][j] = data[i][j] - other.data[i][j];
            }
        }
        return result;
    }

    Matrix operator*(const Matrix& other) const
    {
        if (cols != other.rows)
        {
            throw invalid_argument("Размеры матрицы должны совпадать для умножения.");
        }
        Matrix result(rows, other.cols);
        for (size_t i = 0; i < rows; ++i)
        {
            for (size_t j = 0; j < other.cols; ++j)
            {
                result.data[i][j] = 0;
                for (size_t k = 0; k < cols; ++k)
                {
                    result.data[i][j] += data[i][k] * other.data[k][j];
                }
            }
        }
        return result;
    }

    Matrix operator/(const T& scalar) const
    {
        if (scalar == 0)
        {
            throw invalid_argument("Деление на ноль.");
        }
        Matrix result(rows, cols);
        for (size_t i = 0; i < rows; ++i)
        {
            for (size_t j = 0; j < cols; ++j)
            {
                result.data[i][j] = data[i][j] / scalar;
            }
        }
        return result;
    }

    // Поиск максимального элемента
    T findMax() const
    {
        T maxElement = data[0][0];
        for (size_t i = 0; i < rows; ++i)
        {
            for (size_t j = 0; j < cols; ++j)
            {
                if (data[i][j] > maxElement)
                {
                    maxElement = data[i][j];
                }
            }
        }
        return maxElement;
    }
};

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    try
    {
        Matrix<int> mat1(2, 3);
        mat1.fillRandom(1, 10);
        cout << "Матрица 1:" << endl;
        mat1.display();

        Matrix<int> mat2(2, 3);
        mat2.fillFromInput();
        cout << "Матрица 2:" << endl;
        mat2.display();

        Matrix<int> sum = mat1 + mat2;
        cout << "Сумма матриц 1 и 2:" << endl;
        sum.display();

        Matrix<int> diff = mat1 - mat2;
        cout << "Разница между матрицей 1 и матрицей 2:" << endl;
        diff.display();

        Matrix<int> product = mat1 * mat2; // Предположим, что матрицы имеют совместимые размеры
        cout << "Произведение матриц 1 и 2:" << endl;
        product.display();

        Matrix<int> div = mat1 / 2;
        cout << "Матрица 1 делится на 2:" << endl;
        div.display();

        int maxElement = mat1.findMax();
        cout << "Максимальный элемент в матрице 1: " << maxElement << endl;

    }
    catch (const exception& e)
    {
        cerr << "Ошибка: " << e.what() << endl;
    }

    return 0;
}