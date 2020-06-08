
#include <iostream>
#include <math.h>
#include "Matrix.h"
//#include "LA_Vector.h"

using namespace std;

int main()
{
    int m = 5, n = 5;
    Matrix b(3,4,3);
    Matrix c;

    Matrix a = {{-5, 5, -6, 1, 0}, {0, -5, 10, -3, 3}, {1, 11, 6, 1, 7}, {4, 5, -9, 9, -7}, {-5, 10, 0, -4, 4}};

    cout << "The Matrix A:" << endl;
    cout << a << endl;
    cout << "The Determinant of Matrix A: " << a.determinant() << endl;

    if(a.is_invertible())
    {
        cout << "The Inverse of Matrix A:" << endl;
        cout << a.inverse() << endl;
    }
    else
        cout << "The Matrix A is not Invertible" << endl;

    cout << "The Transpose of Matrix A:" << endl;
    cout << a.transpose() << endl;

    Matrix x(5,5,4);

    cout << "\nThe Matrx X:" << endl;
    cout << x;

    x *= a;

    cout << "\nThe Matrx X After Multiplication:" << endl;
    cout << x;

    c = x * 4;

    cout << "\nThe Matrx C:" << endl;
    cout << c;


    //  cout << f.gaussJordanElimination();

    b(0,2) = 4;
    b(1,2) = 5;
    b(1,3) = 2;
    b(2,0) = -8;
    b(2,3) = 9;
    b(0,0) = 1;
    b(0,1) = 2;

    cout << endl << "The Matrix B:" << endl;
    cout << b;

    cout << endl << "The Matrix After Being Applied the Gauss-Jordan Elimination:" << endl;
    cout << b.gaussJordanElimination() << endl;

    Matrix mx(4,4,4);

    cout << mx.determinant() << endl;

    for(int i = 0; i < m; ++i)
        for(int j = 0; j < n; ++j)
        {
            int x;
            cout << "Mx[" << i + 1 << "][" << j + 1 << "]: ";
            cin >> x;

            a(i,j) = {x};
        }

    cout << "The Matrix A:" << endl;
    cout << a << endl;



    c = Matrix::Identity(m);


    //  cout << a << endl;
    //  cout << a.transpose();

    //cout << a.transpose().determinant() << endl << endl;
    //  cout << a.determinant();

    //cout << c;

}
