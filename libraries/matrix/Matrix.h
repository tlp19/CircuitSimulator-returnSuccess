#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED

#include <vector>
#include <ostream>
#include <assert.h>
#include <cstddef>
#include "Fraction.h"

class Matrix
{
private:
    int rows_num;
    int cols_num;

    std::vector<Fraction> data;

    Fraction& at(std::size_t r, std::size_t c)
    {
        return data[ r * cols_num + c ];
    }

    const Fraction& at(std::size_t r, std::size_t c) const
    {
        return data[ r * cols_num + c];
    }

public:
    Matrix () = default;

    Matrix(int r, int c, long long int n = 0 ) : rows_num(r), cols_num(c), data(r * c, n)
    {
        assert(r > 0 && c > 0);
    }

    Matrix(int r, int c, std::initializer_list<Fraction> values ) : rows_num(r), cols_num(c), data(values)
    {
        assert(r > 0 && c > 0);
        assert(values.size() == size());
    }

    Matrix(std::initializer_list<std::initializer_list<Fraction>> values );

    friend std::ostream& operator<<(std::ostream& out, const Matrix& mx);
    friend std::ostream& operator<<(std::ostream& out, const std::vector<Fraction>& diag);

    explicit operator bool() const
    {
        return ! is_zero();
    }

    bool operator== (const Matrix& mx) const
    {
        return data == mx.data;
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
    Matrix& operator*=(Fraction n);

    friend Matrix operator*(const Matrix& mx, Fraction n);
    friend Matrix operator*(Fraction n, const Matrix& mx);

    friend Matrix operator/(const Matrix& mx, Fraction n);

    Fraction& operator()(std::size_t r, std::size_t c)
    {
        return at(r,c);
    }

    const Fraction& operator()(std::size_t r, std::size_t c) const
    {
        return at(r,c);
    }

    int size() const
    {
        return rows_num * cols_num;
    }

    void resize(int r, int c, long long int n = 0)
    {
        data.clear();

        data.resize( r * c, n );

        rows_num = r;
        cols_num = c;
    }

    int rows() const
    {
        return rows_num;
    }

    int cols() const
    {
        return cols_num;
    }

    static Matrix Identity(int n);
    static Matrix Constant(int r, int c, long long int n);

    bool is_square() const
    {
        return rows_num == cols_num;
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
    Fraction determinant() const;
    Matrix inverse() const;
    Matrix adjoint();
    Matrix gaussElimination() const;
    Matrix gaussJordanElimination() const;

private:
    void swapRows(int row1, int row2);
    bool pivotEqualTo_one_Found(int pivot_row, int pivot_col, int& alternative_pivot_row );
    bool pivotNot_zero_Found(int pivot_row, int pivot_col, int& col_dif_zero );
    bool firstNumberNot_zero(int row_num, int& num_coluna_num_dif_zero);
    void changePivotTo_one(int row_num, Fraction constant);
    void zeroOutTheColumn(int row_num, int num_pivot_row, Fraction constant);

};




#endif // MATRIX_H_INCLUDED
