#include "Matrix.h"

#include <vector>
#include <iostream>
#include <assert.h>
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <boost/format.hpp>

using namespace std;

/*Matrix::Matrix(initializer_list<initializer_list<double>> values )
{
    int len;
    double zero
    for(auto iter = values.begin(); iter != values.end(); ++iter)
        if(iter->size() != 0)
        {
            len = iter->size();
            break;
        }

    assert(len > 0);

    for(auto iter = values.begin(); iter != values.end(); ++iter)
    {
        if(iter->size() != 0)
            assert(iter->size() == len);

        if(iter->size() == 0)
            for(int i = 0; i < len; ++i)
                values.push_back(0.0);
        else
            for(auto iterj = iter->begin(); iterj != iter->end(); ++iterj)
                values.push_back(*iterj);
    }

    rows = values.size();
    cols = len;
} */


Matrix Matrix::operator+(const Matrix& mx) const
{
    assert(rows == mx.rows && cols == mx.cols);

    Matrix add(rows, cols);

    for(int i = 0; i < rows; ++i)
        for(int j = 0; j < cols; ++j)
            add.at(i, j)= at(i, j) + mx.at(i, j);

    return add;
}

Matrix Matrix::operator-(const Matrix& mx) const
{
    assert(rows == mx.rows && cols == mx.cols);

    Matrix sub(rows, cols);

    for(int i = 0; i < rows; ++i)
        for(int j = 0; j < cols; ++j)
            sub.at(i, j) = at(i, j) - mx.at(i, j);

    return sub;
}

Matrix Matrix::operator*(const Matrix& mx) const
{
    assert(cols == mx.rows);

    Matrix mult(rows, mx.cols);

    for(int i = 0; i < rows; ++i)
        for (int j = 0; j < mx.cols; ++j)
            for(int x = 0; x < cols; ++x)
                mult.at(i,j) += at(i, x) * mx.at(x, j);

    return mult;
}

Matrix& Matrix::operator*=(const Matrix& mx)
{
    assert(cols == mx.rows);

    return *this = (*this * mx);
}

Matrix& Matrix::operator-=(const Matrix& mx)
{
    assert(rows == mx.rows && cols == mx.cols);

    transform(values.begin(), values.end(), mx.values.begin(), values.end(), minus<double>{});

    return *this;
}

Matrix& Matrix::operator+=(const Matrix& mx)
{
    assert(rows == mx.rows && cols == mx.cols);

    transform(values.begin(), values.end(), mx.values.begin(), values.end(), plus<double>{});

    return *this;
}

Matrix operator*(const Matrix& mx, double n)
{
    Matrix mult(mx.rows, mx.cols);

    for(int i = 0; i < mx.rows; ++i)
        for(int j = 0; j < mx.cols; ++j)
            mult.at(i, j) = mx.at(i, j) * n;

    return mult;
}

Matrix operator*(double n, const Matrix& mx)
{
    Matrix mult(mx.rows, mx.cols);

    for(int i = 0; i < mx.rows; ++i)
        for(int j = 0; j < mx.cols; ++j)
            mult.at(i, j) = mx.at(i, j) * n;

    return mult;
}

Matrix& Matrix::operator*=(double n)
{
    return *this = *this * n;
}

Matrix operator/(const Matrix& mx, double n)
{
    Matrix div(mx.rows, mx.cols);

    for(int i = 0; i < mx.rows; ++i)
        for(int j = 0; j < mx.cols; ++j)
            div.at(i, j) = mx.at(i, j) / n;

    return div;
}

Matrix Matrix::Identity(int n)
{
    assert(n > 0);

    Matrix mx(n,n);

    for(int i = 0; i < n; ++i)
        mx.at(i, i) = 1;

    return mx;
}

Matrix Matrix::Constant(int r, int c, long long int n)
{
    Matrix mx(r,c, n);

    return mx;
}

bool Matrix::is_identity() const
{
    if(! is_square())
        return false;

    return *this == Identity(cols);
}

bool Matrix::is_symmetric() const
{
    if(! is_square())
        return false;

    for(int i = 0; i < rows; ++i)
        for(int j = 0; j < cols; ++j)
            if(at(i,j) != at(j,i))
                return false;

    return true;
}

bool Matrix::is_skewSymmetric() const
{
    if(! is_square())
        return false;

    for(int i = 0; i < rows; ++i)
        for(int j = i+1; j < cols; ++j)
            if(at(i,j) != -at(j,i))
                return false;

    return true;
}

bool Matrix::is_diagonal() const
{
    if(! is_square())
        return false;

    for(int i = 0; i < rows; ++i)
        for(int j = 0; j < cols; ++j)
            if(i != j)
                if( at(i, j) != 0 )
                    return false;

    return true;
}

bool Matrix::is_zero() const
{
    return all_of( values.begin(), values.end(), [ ] (const auto& x)
    {
        return x == 0;
    } );
}

bool Matrix::is_constant() const
{
    return adjacent_find( values.begin(), values.end(), not_equal_to<double>{} ) == values.end();
}

bool Matrix::is_orthogonal() const
{
    if(! is_square())
        return false;

    return (*this * transpose() == Identity(cols));
}

bool Matrix::is_invertible() const
{
    return this->determinant() != 0;
}

bool Matrix::is_linearly_dependent() const
{
    return this->determinant() == 0;
}

bool Matrix::is_linearly_independent() const
{
    return ! this->is_linearly_dependent();
}

bool Matrix::is_lowerTriangular() const
{
    if(! is_square())
        return false;

    for(int i = 0; i < rows; ++i)
        for(int j = i + 1; j < cols; ++j)
            if( at(i,j) )
                return false;

    return true;
}

bool Matrix::is_upperTriangular() const
{
    if(! is_square())
        return false;

    for(int i = 0; i < rows; ++i)
        for(int j = 0; j < i; ++j)
            if( at(i,j) )
                return false;

    return true;
}

Matrix Matrix::transpose() const
{
    Matrix trans(cols, rows);

    for(int i = 0; i < rows; ++i)
        for(int j = 0; j < cols; ++j)
            trans.at(j, i) = at(i, j);

    return trans;
}

double Matrix::determinant() const
{
    assert(is_square());

    if(is_zero())
        return {0};

    if(rows == 1)
        return at(0,0);

    if(is_identity())
        return {1};

    if(is_constant())
        return {0};

    if(cols == 2)
        return at(0,0) * at(1,1) - at(0,1) * at(1,0);

    bool alternative_pivot_1_found;

    bool pivot_not_zero_found;

    bool number_not_zero_found;

    int row_with_alternative_pivot;

    int row_with_pivot_not_zero;

    int pivot_row = 0;
    int pivot_col = 0;

    Matrix mx = *this;
    vector<double> row_mults;
    int sign = 1;

    while (pivot_row < (rows - 1))
    {
        alternative_pivot_1_found = mx.pivotEqualTo_one_Found ( pivot_row, pivot_col, row_with_alternative_pivot);

        pivot_not_zero_found = mx.pivotNot_zero_Found(pivot_row, pivot_col, row_with_pivot_not_zero);

        if (mx.at(pivot_row, pivot_col) != 1 && alternative_pivot_1_found )
        {
            mx.swapRows(pivot_row, row_with_alternative_pivot);

            sign *= (-1);
        }
        else if (mx.at(pivot_row, pivot_col) == 0 && pivot_not_zero_found )
        {
            mx.swapRows(pivot_row, row_with_pivot_not_zero);

            sign *= (-1);
        }

        int col_dif_zero;

        number_not_zero_found = mx.firstNumberNot_zero(pivot_row, col_dif_zero);

        if(number_not_zero_found)
        {
            if (mx.at(pivot_row, col_dif_zero) != 1)
            {
                row_mults.push_back(mx.at(pivot_row, col_dif_zero));

                mx.changePivotTo_one(pivot_row, mx.at(pivot_row, col_dif_zero));
            }
        }

        for (int i = pivot_row + 1; i < rows; ++i)
            mx.zeroOutTheColumn(i, pivot_row, mx.at(i, col_dif_zero));

        ++pivot_row;
        ++pivot_col;
    }

    double det(sign);

    for(int i = 0; i < rows; ++i)
        det  *= mx.at(i,i);

    return accumulate(row_mults.begin(), row_mults.end(), det, multiplies<double>());
}

Matrix Matrix::inverse() const
{
    assert(is_square());

    if( ! is_invertible())
    {
        cerr << "\aNOT INVERTIBLE\n";
        return *this;
    }

    Matrix mx = *this;
    Matrix inverse = Matrix::Identity(rows);
	
    bool alternative_pivot_1_found;

    bool pivot_not_zero_found;

    bool number_not_zero_found;

    int row_with_alternative_pivot;

    int row_with_pivot_not_zero;

    int pivot_row = 0;
    int pivot_col = 0;

    //Gauss Elimination
    while (pivot_row < (rows - 1))
    {
        alternative_pivot_1_found = mx.pivotEqualTo_one_Found (pivot_row, pivot_col, row_with_alternative_pivot);

        pivot_not_zero_found = mx.pivotNot_zero_Found(pivot_row, pivot_col, row_with_pivot_not_zero);

        if (mx.at(pivot_row, pivot_col) != 1 && alternative_pivot_1_found )
        {
            inverse.swapRows(pivot_row, row_with_alternative_pivot);
            mx.swapRows(pivot_row, row_with_alternative_pivot);
        }
        else if (mx.at(pivot_row, pivot_col) == 0 && pivot_not_zero_found )
        {
            inverse.swapRows(pivot_row, row_with_pivot_not_zero);
            mx.swapRows(pivot_row, row_with_pivot_not_zero );
        }

        int col_dif_zero;

        number_not_zero_found = mx.firstNumberNot_zero(pivot_row, col_dif_zero);

        if(number_not_zero_found)
        {
            if ( mx.at(pivot_row, col_dif_zero) != 1)
            {
                inverse.changePivotTo_one(pivot_row, mx.at(pivot_row, col_dif_zero));
                mx.changePivotTo_one(pivot_row, mx.at(pivot_row, col_dif_zero));
            }
        }

        if(number_not_zero_found)
        {
            for (int i = pivot_row + 1; i < cols; ++i)
            {
                inverse.zeroOutTheColumn(i, pivot_row, mx.at(i, col_dif_zero));
                mx.zeroOutTheColumn(i, pivot_row, mx.at(i, col_dif_zero));
            }
        }

        ++pivot_row;
        ++pivot_col;
    }

    //Jordan Elimination
    while(pivot_row > 0)
    {
        int col_dif_zero;

        number_not_zero_found = mx.firstNumberNot_zero(pivot_row, col_dif_zero);

        if(number_not_zero_found)
        {
            if ( mx.at(pivot_row, col_dif_zero) != 1)
            {
                inverse.changePivotTo_one(pivot_row, mx.at(pivot_row, col_dif_zero));
                mx.changePivotTo_one(pivot_row, mx.at(pivot_row, col_dif_zero));
            }
        }

        if(number_not_zero_found)
        {
            for (int i = pivot_row - 1; i >= 0; --i)
            {
                inverse.zeroOutTheColumn(i, pivot_row, mx.at(i, col_dif_zero));
                mx.zeroOutTheColumn(i, pivot_row, mx.at(i, col_dif_zero));
            }
        }

        --pivot_row;
    }

    return inverse;
}

Matrix Matrix::adjoint()
{
    assert(is_square());
    assert(cols > 1);

    if(is_zero())
        return Matrix(rows, cols);

    if(is_constant())
        return Matrix(rows, cols);

    if(is_identity())
        return *this;

    Matrix cofact(rows, cols);

    int r = 0, c = 0;

    Matrix temp(rows - 1, cols - 1);

    for(int i = 0; i < rows; ++i)
    {
        for(int j = 0; j < cols; ++j)
        {
            for(int k = 0; k < rows; ++k)
            {
                for(int h = 0; h < cols; ++h)
                {
                    if (k != i && h != j)
                    {
                        temp(r, c++) = at(k, h);

                        if(c == cols - 1)
                        {
                            c = 0;
                            ++r;
                        }
                    }
                }
            }

            c = 0;
            r = 0;

            int sign;

            sign = ( ( i + j ) % 2 == 0 ) ? 1 : -1;

            cofact.at(i, j) = sign * temp.determinant();
        }
    }

    return cofact.transpose();
}

Matrix Matrix::gaussJordanElimination() const
{
    Matrix mx = *this;

    bool alternative_pivot_1_found;

    bool pivot_not_zero_found;

    bool number_not_zero_found;

    int row_with_alternative_pivot;

    int row_with_pivot_not_zero;

    int pivot_row = 0;
    int pivot_col = 0;

    ///Gauss Elimination
    while (pivot_row < (rows - 1))
    {
        alternative_pivot_1_found = mx.pivotEqualTo_one_Found ( pivot_row, pivot_col,
                                    row_with_alternative_pivot);

        pivot_not_zero_found = mx.pivotNot_zero_Found(
                                   pivot_row, pivot_col, row_with_pivot_not_zero);

        if (mx.at( pivot_row, pivot_col) != 1 && alternative_pivot_1_found )
        {
            mx.swapRows(pivot_row, row_with_alternative_pivot);
        }
        else if (mx.at( pivot_row, pivot_col) == 0 && pivot_not_zero_found )
        {
            mx.swapRows( pivot_row, row_with_pivot_not_zero );
        }

        int col_dif_zero;

        number_not_zero_found = mx.firstNumberNot_zero(pivot_row, col_dif_zero);

        if(number_not_zero_found)
        {
            if (( mx.at(pivot_row, col_dif_zero) ) != 1)
            {
                mx.changePivotTo_one(pivot_row,
                                     mx.at(pivot_row, col_dif_zero) );
            }
        }

        if(number_not_zero_found)
        {
            for(int i = pivot_row + 1; i < rows; ++i)
            {
                mx.zeroOutTheColumn( i, pivot_row, mx.at(i, col_dif_zero));
            }
        }

        ++pivot_row;
        ++pivot_col;
    }

    //Jordan Elimination
    while(pivot_row > 0)
    {
        int col_dif_zero;

        number_not_zero_found = mx.firstNumberNot_zero(pivot_row, col_dif_zero);

        if(number_not_zero_found)
            if ( mx.at(pivot_row, col_dif_zero) != 1)
            {
                mx.changePivotTo_one(pivot_row, mx.at(pivot_row, col_dif_zero));
            }

        if(number_not_zero_found)
            for (int i = pivot_row - 1; i >= 0; --i)
                mx.zeroOutTheColumn(i, pivot_row, mx.at(i, col_dif_zero));

        --pivot_row;
    }

    return mx;
}

Matrix Matrix::gaussElimination() const
{
    Matrix mx = *this;

    bool alternative_pivot_1_found;

    bool pivot_not_zero_found;

    bool number_not_zero_found;

    int row_with_alternative_pivot;

    int row_with_pivot_not_zero;

    int pivot_row = 0;
    int pivot_col = 0;

    ///Gauss Elimination
    while (pivot_row < (rows - 1))
    {
        alternative_pivot_1_found = mx.pivotEqualTo_one_Found ( pivot_row, pivot_col,
                                    row_with_alternative_pivot);

        pivot_not_zero_found = mx.pivotNot_zero_Found(
                                   pivot_row, pivot_col, row_with_pivot_not_zero);

        if (mx.at( pivot_row, pivot_col) != 1 && alternative_pivot_1_found )
        {
            mx.swapRows(pivot_row, row_with_alternative_pivot);
        }
        else if (mx.at( pivot_row, pivot_col) == 0 && pivot_not_zero_found )
        {
            mx.swapRows( pivot_row, row_with_pivot_not_zero );
        }

        int col_dif_zero;

        number_not_zero_found = mx.firstNumberNot_zero(pivot_row, col_dif_zero);

        if(number_not_zero_found)
        {
            if (( mx.at(pivot_row, col_dif_zero) ) != 1)
            {
                mx.changePivotTo_one(pivot_row,
                                     mx.at(pivot_row, col_dif_zero) );
            }
        }

        if(number_not_zero_found)
        {
            for(int i = pivot_row + 1; i < rows; ++i)
            {
                mx.zeroOutTheColumn( i, pivot_row, mx.at(i, col_dif_zero));
            }
        }

        ++pivot_row;
        ++pivot_col;
    }

    int col_dif_zero;

    number_not_zero_found = mx.firstNumberNot_zero(pivot_row, col_dif_zero);

    if(number_not_zero_found)
        if ( mx.at(pivot_row, col_dif_zero) != 1)
        {
            mx.changePivotTo_one(pivot_row, mx.at(pivot_row, col_dif_zero));
        }

    return mx;
}

void Matrix::swapRows( int row1, int row2)
{
    for (int i = 0; i < cols; i++ )
    {
        swap( at(row1,i ), at(row2, i) );
    }
}

bool Matrix::pivotEqualTo_one_Found( int pivot_row, int pivot_col, int& alternative_pivot_row )
{
    for (int i = pivot_row + 1; i < rows; ++i)
    {
        if(at(i, pivot_col) == 1)
        {
            alternative_pivot_row = i;

            return true;
        }
    }

    return false;
}

bool Matrix::pivotNot_zero_Found(int pivot_row, int pivot_col,int& col_dif_zero )
{
    for (int i = pivot_row + 1; i < rows; ++i)
        if(at(i, pivot_col) != 0)
        {
            col_dif_zero = i;

            return true;
        }

    return false;
}

bool Matrix::firstNumberNot_zero(int row_num, int& num_coluna_num_dif_zero)
{
    for (int i = 0; i < cols; ++i)
        if (at(row_num, i) != 0)
        {
            num_coluna_num_dif_zero = i;

            return true;
        }

    return false;
}

void Matrix::changePivotTo_one( int row_num, double constant)
{
    for(int i = 0; i < cols; ++i)
        if (at(row_num, i) != 0)
            at(row_num, i) = (at(row_num, i) / constant);
}

void Matrix::zeroOutTheColumn( int row_num, int num_pivot_row, double constant)
{
    for(int i = 0; i < cols; ++i)
        at(row_num, i) = at(row_num, i) -  (constant * at(num_pivot_row, i));
}

