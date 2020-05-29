#include "Fraction.h"

#include <ostream>
#include <sstream>

using namespace std;

std::ostream& operator<< (std::ostream& os, const Fraction& fr)
{
    if(fr.den == 1)
        os << fr.num;
    else
        os << fr.num << "/" << fr.den;

    return os;
}

string Fraction::to_string() const
{
        ostringstream os;
        os << *this;
        return os.str();
}

long long int Fraction::gcf(long long int a, long long int b)
{
    if( b == 0)
        return abs(a);
    else
        return gcf(b, a%b);
}

void Fraction::simplify()
{
    if (den == 0 || num == 0)
    {
        num = 0;
        den = 1;
    }
    // Put neg. sign in numerator only.
    if (den < 0)
    {
        num *= -1;
        den *= -1;
    }

    // Factor out GCF from numerator and denominator.
    long long int n = gcf(num, den);
    num = num / n;
    den = den / n;
}

Fraction Fraction::operator- (const Fraction& fr) const
{
    Fraction sub( (num * fr.den) - (fr.num * den), den * fr.den );

    sub.simplify();

    return sub;
}

Fraction Fraction::operator+(const Fraction& fr) const
{
    Fraction add ((num * fr.den) + (fr.num * den), den * fr.den );

    add.simplify();

    return add;
}

Fraction Fraction::operator*(const Fraction& fr) const
{
    Fraction mult(num * fr.num, den * fr.den);

    mult.simplify();

    return mult;
}

Fraction Fraction::operator / (const Fraction& fr) const
{
    Fraction sub(num * fr.den, den * fr.num);

    sub.simplify();

    return sub;
}

Fraction operator+(const Fraction& fr, long long int n)
{
    return (Fraction(n) + fr);
}

Fraction operator+(long long int n, const Fraction& fr)
{
    return (Fraction(n) + fr);
}

Fraction operator-(const Fraction& fr, long long int n)
{
    return (Fraction(n) - fr);
}

Fraction operator-(long long int n, const Fraction& fr)
{
    return (Fraction(n) - fr);
}

Fraction operator/(const Fraction& fr, long long int n)
{
    return (Fraction(n) / fr);
}

Fraction operator/(long long int n, const Fraction& fr)
{
    return (Fraction(n) / fr);
}

Fraction operator*(const Fraction& fr, long long int n)
{
    return (Fraction(n) * fr);
}

Fraction operator*(long long int n, const Fraction& fr)
{
    return (Fraction(n) * fr);
}

void operator+=(Fraction& f, const Fraction& fr)
{
    f = f + fr;
}

void operator-=(Fraction& f, const Fraction& fr)
{
    f = f - fr;
}

void operator/=(Fraction& f, const Fraction& fr)
{
    f = f / fr;
}

void operator*=(Fraction& f, const Fraction& fr)
{
    f = f * fr;
}

void operator+=(Fraction& fr, long long int n)
{
    fr = fr + n;
}

void operator-=(Fraction& fr, long long int n)
{
    fr = fr - n;
}

void operator*=(Fraction& fr, long long int n)
{
    fr = fr * n;
}

void operator/=(Fraction& fr, long long int n)
{
    fr = fr / n;
}
