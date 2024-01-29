#ifndef CONSTANTS_AND_UTILITIES_H
#define CONSTANTS_AND_UTILITIES_H

#include <cmath>
#include <limits>
#include <memory>
#include <cstdlib>

//Usings

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

//Constantes

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

//Funciones de utilidad

//Convierte grados a radianes
inline double degrees_to_radians(double degrees)
{
    return degrees*pi/180.0;
}

//Regresa un numero aleatorio en [0,1)
inline double random_double()
{
    return rand()/(RAND_MAX + 1.0);
}

//Regresa un numero aleatorio en [min,max)
inline double random_double(double min, double max)
{
    return min + (max - min)*random_double();
}

//Forza un punto a estar dentro de un intervalo
inline double clamp(double x, double min, double max)
{
    if(x < min) return min;
    if(x > max) return max;
    return x;
}

//Headers comunes

#include "ray.h"
#include "vec3.h"

#endif