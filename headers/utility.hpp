/*
 * Christopher Di Bella
 * Keane Chan, Ervin Macrohon, Timothy Masters
 *
 * 2014, September 17
 *
 * utility.hpp
 * Declaration of several utility functions and types
 */
#ifndef PHOSPHORUS_UTILITY_HPP11_INCLUDED
#define PHOSPHORUS_UTILITY_HPP11_INCLUDED
#include <chrono>

// nanoseconds for consistency
inline std::chrono::nanoseconds operator"" _ns(unsigned long long int ns)
{
    return std::chrono::nanoseconds(ns);
}

// microseconds to nanoseconds
inline std::chrono::nanoseconds operator"" _us(unsigned long long int us)
{
    return std::chrono::nanoseconds(us * 1000);
}

// milliseconds to nanoseconds
inline std::chrono::nanoseconds operator"" _ms(unsigned long long int ms)
{
    return std::chrono::nanoseconds(ms * 1000000);
}

// seconds to nanoseconds
inline std::chrono::nanoseconds operator"" _sec(unsigned long long int sec)
{
    return std::chrono::nanoseconds(sec * 1000000000);
}

// nanometres to metres
inline long double operator"" _nm(long double nm)
{
    return nm * 1e10-9;
}

// micrometres to metres
inline long double operator"" _um(long double um)
{
    return um * 1e10-6;
}

// millimetres to metres
inline long double operator"" _mm(long double mm)
{
    return mm * 0.001;
}

// centimetres to metres
inline long double operator"" _cm(long double cm)
{
    return cm * 0.01;
}

// metres added for consistency
inline long double operator"" _m(long double m)
{
    return m;
}

// kilometres to metres
inline long double operator"" _km(long double km)
{
    return km * 1000;
}

// megametres to metres
inline long double operator"" _megametre(long double mega)
{
    return mega * 10e+6;
}

// gigametres to metres
inline long double operator"" _gigametre(long double giga)
{
    return giga * 10e+9;
}

// terametres to metres
inline long double operator"" _terametre(long double tera)
{
    return tera * 10e+12;
}

// astronomical units to metres
inline long double operator"" _au(long double au)
{
    return au * 149597870700;
}

// inches to metres
inline long double operator"" _in(long double in)
{
    return in * 0.0254;
}

// feet to metres
inline long double operator"" _ft(long double ft)
{
    return ft * 0.3048;
}

// yards to metres
inline long double operator"" _yd(long double yd)
{
    return yd * 0.9144;
}

// miles to metres
inline long double operator"" _mi(long double mi)
{
    return mi * 1609.34;
}

// nautical miles to metres
inline long double operator"" _nmi(long double nmi)
{
    return nmi * 1852;
}

/* degrees to radians
inline long double operator"" _deg(long double deg)
{
    return phosphorus::pi * deg / 180;
}

// radians to degrees
inline long double operator"" _rad(long double rad)
{
    return phosphorus::pi * 180 / rad;
}*/
#endif // PHOSPHORUS_UTILITY_HPP11_INCLUDED
