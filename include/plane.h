#ifndef PLANE_H
#define PLANE_H

#include "hittable.h"
#include "vec3.h"

class plane : public hittable
{
    public:
        plane(
            point3 p,               //Punto de referencia del plano
            vec3 normal,            //Normal al plano
            shared_ptr<material> m  //Material del plano
            ): p(p), normal(normal), mat_ptr(m) {};
        
        virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;

    public:
        point3 p;
        vec3 normal;
        shared_ptr<material> mat_ptr;
};

//Funcion que detecta si un rayo colisiona con el plano
bool plane::hit(const ray& r, double t_min, double t_max, hit_record& rec) const
{
    auto numerator = dot(normal, p-r.origin());
    auto denominator = dot(normal, r.direction()); 
    if(fabs(denominator) < 0.0001) return false;

    //Encuentra el tiempo en el que colisiona el rayo con
    //el plano y si esta dentro del tiempo aceptable, se 
    //detecta la colision
    auto time = numerator/denominator;
    if(time < t_min || t_max < time)
        return false;

    //Guarda el tiempo de la colision, el punto,
    //la normal y el material
    rec.t = time;
    rec.p = r.at(rec.t);
    rec.set_face_normal(r, normal);
    rec.mat_ptr = mat_ptr;

    return true;
}

#endif