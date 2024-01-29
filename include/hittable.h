#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"
#include "constants_and_utilities.h"

class material;

//Estructura para guardar el punto, normal, material, tiempo
//y si se esta viendo a la cara frontal de objetos con los que se colisiona
struct hit_record
{
    point3 p;
    vec3 normal;
    shared_ptr<material> mat_ptr;
    double t;
    bool front_face;

    //Calcula la normal que tiene direccion contraria al rayo
    inline void set_face_normal(const ray& r, const vec3& outward_normal)
    {
        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

class hittable
{
    public:
        virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const = 0;
};

#endif