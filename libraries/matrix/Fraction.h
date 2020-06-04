#ifndef FRACTION_H_INCLUDED
#define FRACTION_H_INCLUDED

#include <iostream>
#include <ostream>
#include <assert.h>

class Fraction
{
    long long int gcf(long long int a, long long int b);
    void simplify();

public:
    long long int num;
    long long int den;

    Fraction(long long int _num = 0, long long int _den = 1 ) : num{std::move(_num)}, den{std::move(_den)}
    {
        assert(_den != 0);

        simplify();
    }

    Fraction (Fraction n, Fraction d) : num(n.num * d.den), den(n.den * d.num)
    {
        simplify();
    }

    friend std::ostream& operator<< (std::ostream& os, const Fraction& fr);

    std::string to_string() const;

    bool is_integer()
    {
        return den == 1;
    }

    explicit operator bool() const
    {
        return num != 0;
    }

    bool operator== (const Fraction& fr) const
    {
        return num == fr.num && den == fr.den;
    }

    bool operator!= (const Fraction& fr) const
    {
        return !(*this == fr);
    }

    bool operator== (int n) const
    {
        return (n * den) == num;
    }

    bool operator!= (int n) const
    {
        return ! (*this == n);
    }

    Fraction operator-() const
    {
        return { -num, den };
    }

    Fraction operator+() const
    {
        return *this;
    }

    Fraction operator+(const Fraction& fr) const;
    Fraction operator/(const Fraction& fr) const;
    Fraction operator-(const Fraction& fr) const;
    Fraction operator*(const Fraction& fr) const;

    friend Fraction operator+(const Fraction& fr, long long int n);
    friend Fraction operator+(long long int n, const Fraction& fr);
    friend Fraction operator-(const Fraction& fr, long long int n);
    friend Fraction operator-(long long int n, const Fraction& fr);
    friend Fraction operator/(const Fraction& fr, long long int n);
    friend Fraction operator/(long long int n, const Fraction& fr);
    friend Fraction operator*(const Fraction& fr, long long int n);
    friend Fraction operator*(long long int n, const Fraction& fr);

    friend void operator+= (Fraction& f, const Fraction& fr);
    friend void operator-= (Fraction& f, const Fraction& fr);
    friend void operator/= (Fraction& f, const Fraction& fr);
    friend void operator*= (Fraction& f, const Fraction& fr);

    friend void operator+=(Fraction& fr, long long int n);
    friend void operator-=(Fraction& fr, long long int n);
    friend void operator*=(Fraction& fr, long long int n);
    friend void operator/=(Fraction& fr, long long int n);
};

#endif // FRACTION_H_INCLUDED
