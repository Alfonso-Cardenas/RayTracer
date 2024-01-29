#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "hittable.h"
#include "vec3.h"

//Funcion auxiliar que detecta si un punto dado pertenece al triangulo formado por los 
//3 vertices que se pasan, utilizando ideas de coordenadas baricentricas
bool point_in_triangle(const point3& p, const point3& v1, const point3& v2, const point3& v3)
{
    point3 a = v1-p;
    point3 b = v2-p;
    point3 c = v3-p;

    vec3 u = cross(b,c);
    vec3 v = cross(c,a);
    vec3 w = cross(a,b);

    if(dot(u,v) < 0 || dot(u,w) < 0) return false;
    
    return true;
}

class triangle : public hittable
{
    public:
        //El triangulo se define con 3 verices y con un material, la normal se calcula
        //con el producto cruz de dos de sus lados
        triangle(point3 v1, point3 v2, point3 v3, shared_ptr<material> m)
            : v1(v1), v2(v2), v3(v3), mat_ptr(m), normal(cross(v2-v1, v3-v1)) {};

        virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;

    public:
        point3 v1, v2, v3, normal;
        shared_ptr<material> mat_ptr;
};

bool triangle::hit(const ray& r, double t_min, double t_max, hit_record& rec) const
{
    //Primero se revisa si el rayo colisiona con el plano asociado
    //al triangulo
    auto numerator = dot(normal, v2-r.origin());
    auto denominator = dot(normal, r.direction()); 
    if(fabs(denominator) < 0.0001) return false;

    auto time = numerator/denominator;
    if(time < t_min || t_max < time)
        return false;

    //Utiliza la funcion auxiliar para saber si
    //el punto se encuentra dentro del triangulo
    auto intersection = r.at(time);
    if(!point_in_triangle(intersection, v1, v2, v3))
        return false;

    rec.t = time;
    rec.p = intersection;
    rec.set_face_normal(r, normal);
    rec.mat_ptr = mat_ptr;

    return true;
}

#endif