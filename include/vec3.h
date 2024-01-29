#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

using std::sqrt;

//Clase de los vectores de 3 dimensiones
class vec3
{
    public:
        vec3() : e{0,0,0} {}
        vec3(double e0, double e1, double e2) : e{e0,e1,e2} {}

        //Entradas de los vectores
        double x() const { return e[0]; }
        double y() const { return e[1]; }
        double z() const { return e[2]; }

        //Genera un vector aleatorio con entradas entre 0 y 1
        inline static vec3 random()
        {
            return vec3(random_double(), random_double(), random_double());
        }

        //Genera un vector aleatorio con entradas entre min y max
        inline static vec3 random(double min, double max)
        {
            return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
        }

        //Negacion de un vector
        vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }

        //Arreglo de vectores
        double operator[](int i) const { return e[i]; }
        double& operator[](int i) { return e[i]; }

        //Suma de vectores
        vec3& operator+=(const vec3 &v) {
            e[0] += v.e[0];
            e[1] += v.e[1];
            e[2] += v.e[2];
            return *this;
        }

        //Producto de un vector por una constante
        vec3& operator*=(const double t) {
            e[0] *= t;
            e[1] *= t;
            e[2] *= t;
            return *this;
        }

        //Division de un vector por una constante
        vec3& operator/=(const double t) {
            return *this *= 1/t;
        }

        //Igualdad entre vectores (entrada por entrada)
        bool operator==(const vec3& v) {
            return e[0] == v.e[0] && e[1] == v.e[1] && e[2] == v.e[2];
        }

        //Norma de un vector
        double length() const {
            return sqrt(length_squared());
        }

        //Norma al cuadrado
        double length_squared() const {
            return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
        }

        //Regresa si el vector es cercano a 0
        bool near_zero() const 
        {
            const auto s = 1e-8;
            return(fabs(e[0]) < s) && (fabs(e[1]) < s) && (fabs(e[2]) < s);
        }
    
    public:
        double e[3];
};

//Funciones utiles para trabajar con vectores

//Imprimir
inline std::ostream& operator<<(std::ostream &out, const vec3 &v) {
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

//Suma
inline vec3 operator+(const vec3 &u, const vec3 &v) {
    return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

//Resta
inline vec3 operator-(const vec3 &u, const vec3 &v) {
    return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

//Producto entrada por entrada
inline vec3 operator*(const vec3 &u, const vec3 &v) {
    return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

//Producto por constante
inline vec3 operator*(double t, const vec3 &v) {
    return vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
}

//Producto por constante
inline vec3 operator*(const vec3 &v, double t) {
    return t * v;
}

//Division entre constante
inline vec3 operator/(vec3 v, double t) {
    return (1/t) * v;
}

//Producto punto
inline double dot(const vec3 &u, const vec3 &v) {
    return u.e[0] * v.e[0]
         + u.e[1] * v.e[1]
         + u.e[2] * v.e[2];
}

//Producto cruz
inline vec3 cross(const vec3 &u, const vec3 &v) {
    return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                u.e[2] * v.e[0] - u.e[0] * v.e[2],
                u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

//Regresa el vector normalizado
inline vec3 unit_vector(vec3 v) {
    return v / v.length();
}

//Regresa un vector aleatorio en la esfera unitaria
vec3 random_in_unit_sphere()
{
    while(1)
    {
        auto p = vec3::random(-1, 1);
        if(p.length_squared() >= 1) continue;
        return p;
    }
}

//Regresa el vector normalizado de la funcion anterior
vec3 random_unit_vector()
{
    return unit_vector(random_in_unit_sphere());
}

//Regresa un vector aleatorio en el hemisferio de la esfera
vec3 random_in_hemisphere(const vec3& normal)
{
    vec3 in_unit_sphere = random_in_unit_sphere();
    if(dot(in_unit_sphere, normal) > 0.0) //In the same hemisphere as the normal
        return in_unit_sphere;
    else
        return -in_unit_sphere;
}

//Refleja un vector por una normal
vec3 reflect(const vec3& v, const vec3&n)
{
    return v - 2*dot(v, n)*n;
}

//Regresa la refraccion del vector
vec3 refract(const vec3& uv, const vec3& n, double etai_over_etat) {
    auto cos_theta = fmin(dot(-uv, n), 1.0);
    vec3 r_out_perp =  etai_over_etat * (uv + cos_theta*n);
    vec3 r_out_parallel = -sqrt(fabs(1.0 - r_out_perp.length_squared())) * n;
    return r_out_perp + r_out_parallel;
}

//Regresa un vector aleatorio en el disco unitario
vec3 random_in_unit_disk()
{
    while(true)
    {
        auto p = vec3(random_double(-1,1), random_double(-1,1), 0);
        if(p.length_squared() >= 1) continue;
        return p;
    }
}

//Aliases usados 
using point3 = vec3;   //Punto 3D
using color = vec3;    //Color en RGB

#endif