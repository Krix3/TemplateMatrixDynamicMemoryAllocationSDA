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
    // �����������
    Matrix(size_t rows, size_t cols) : rows(rows), cols(cols)
    {
        allocateMemory();
    }

    // ����������� �����������
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

    // �������� ������������
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

    // ����������
    ~Matrix()
    {
        freeMemory();
    }

    // ���������� ������� � ����������
    void fillFromInput()
    {
        cout << "���� ��������� �������:" << endl;
        for (size_t i = 0; i < rows; ++i)
        {
            for (size_t j = 0; j < cols; ++j)
            {
                cin >> data[i][j];
            }
        }
    }

    // ���������� ������� ���������� ����������
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

    // ����������� �������
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

    // �������������� ��������
    Matrix operator+(const Matrix& other) const
    {
        if (rows != other.rows || cols != other.cols)
        {
            throw invalid_argument("������� ������� ������ ��������� ��� ��������.");
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
            throw std::invalid_argument("������� ������� ������ ��������� ��� ���������.");
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
            throw invalid_argument("������� ������� ������ ��������� ��� ���������.");
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
            throw invalid_argument("������� �� ����.");
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

    // ����� ������������� ��������
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
        cout << "������� 1:" << endl;
        mat1.display();

        Matrix<int> mat2(2, 3);
        mat2.fillFromInput();
        cout << "������� 2:" << endl;
        mat2.display();

        Matrix<int> sum = mat1 + mat2;
        cout << "����� ������ 1 � 2:" << endl;
        sum.display();

        Matrix<int> diff = mat1 - mat2;
        cout << "������� ����� �������� 1 � �������� 2:" << endl;
        diff.display();

        Matrix<int> product = mat1 * mat2; // �����������, ��� ������� ����� ����������� �������
        cout << "������������ ������ 1 � 2:" << endl;
        product.display();

        Matrix<int> div = mat1 / 2;
        cout << "������� 1 ������� �� 2:" << endl;
        div.display();

        int maxElement = mat1.findMax();
        cout << "������������ ������� � ������� 1: " << maxElement << endl;

    }
    catch (const exception& e)
    {
        cerr << "������: " << e.what() << endl;
    }

    return 0;
}