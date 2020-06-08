#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED

#include <vector>
#include <ostream>
#include <assert.h>
#include <cstddef>

#include "../analysis_header.hpp"

using namespace std;


struct Matrix
{
    int rows;
    int cols;

    vector<double> values;

    void write(int r, int c, Component v);
    double read(int r, int c);
    void fill_with_zeros();
    void print() const;
    void write_resistor_conductance(Network input_network);
    void overwrite_w_voltage_sources(Network input_network);



    double& at(size_t r, size_t c)
    {
        return values[ r * cols + c ];
    }

    const double& at(size_t r, size_t c) const
    {
        return values[ r * cols + c];
    }

    Matrix () = default;

    Matrix(int r, int c, long long int n = 0 ) : rows(r), cols(c), values(r * c, n)
    {
        assert(r > 0 && c > 0);
    }

    Matrix(int r, int c, initializer_list<double> values ) : rows(r), cols(c), values(values)
    {
        assert(r > 0 && c > 0);
        assert(values.size() == size());
    }

    Matrix(initializer_list<initializer_list<double>> values );

    friend ostream& operator<<(ostream& out, const Matrix& mx);
    friend ostream& operator<<(ostream& out, const vector<double>& diag);

    explicit operator bool() const
    {
        return ! is_zero();
    }

    bool operator== (const Matrix& mx) const
    {
        return values == mx.values;
    }
    bool operator!= (const Matrix& mx) const
    {
        return !(*this == mx);
    }

    Matrix operator+(const Matrix& mx) const;
    Matrix operator-(const Matrix& mx) const;
    Matrix operator*(const Matrix& mx) const;

    Matrix& operator+=(const Matrix& mx);
    Matrix& operator-=(const Matrix& mx);
    Matrix& operator*=(const Matrix& mx);
    Matrix& operator*=(double n);

    friend Matrix operator*(const Matrix& mx, double n);
    friend Matrix operator*(double n, const Matrix& mx);

    friend Matrix operator/(const Matrix& mx, double n);

    double& operator()(size_t r, size_t c)
    {
        return at(r,c);
    }

    const double& operator()(size_t r, size_t c) const
    {
        return at(r,c);
    }

    int size() const
    {
        return rows * cols;
    }

    void resize(int r, int c, long long int n = 0)
    {
        values.clear();

        values.resize( r * c, n );

        rows = r;
        cols = c;
    }

/*    int rows() const
    {
        return rows;
    }

    int cols() const
    {
        return cols;
    } */

    static Matrix Identity(int n);
    static Matrix Constant(int r, int c, long long int n);

    bool is_square() const
    {
        return rows == cols;
    }

    bool is_identity() const;
    bool is_symmetric() const;
    bool is_skewSymmetric() const;
    bool is_diagonal() const;
    bool is_zero() const;
    bool is_constant() const;
    bool is_orthogonal() const;
    bool is_invertible() const;
    bool is_linearly_dependent() const;
    bool is_linearly_independent() const;
    bool is_upperTriangular() const;
    bool is_lowerTriangular() const;

    Matrix transpose() const;
    double determinant() const;
    Matrix inverse() const;
    Matrix adjoint();
    Matrix gaussElimination() const;
    Matrix gaussJordanElimination() const;

private:
    void swapRows(int row1, int row2);
    bool pivotEqualTo_one_Found(int pivot_row, int pivot_col, int& alternative_pivot_row );
    bool pivotNot_zero_Found(int pivot_row, int pivot_col, int& col_dif_zero );
    bool firstNumberNot_zero(int row_num, int& num_coluna_num_dif_zero);
    void changePivotTo_one(int row_num, double constant);
    void zeroOutTheColumn(int row_num, int num_pivot_row, double constant);

};




#endif // MATRIX_H_INCLUDED
