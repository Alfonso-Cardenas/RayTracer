#ifndef CUBE_H
#define CUBE_H

#include "hittable_list.h"
#include "vec3.h"
#include "triangle.h"

//El cubo es una lista de triangulos formados por los vertices dados.
//Es necesario pasar primero los 4 puntos de la base en orden cw o ccw y despues los
//puntos de la cara de arriba en el orden que se definieron los puntos de la base.
class cube : public hittable_list
{
    public:
        cube(point3 diagonal[], shared_ptr<material> m)
        {
            point3 vertices[8];
            vertices[0] = diagonal[0];
            vertices[6] = diagonal[1];
            vertices[3] = point3(diagonal[0].x(), diagonal[0].y(), diagonal[1].z());
            vertices[4] = point3(diagonal[0].x(), diagonal[1].y(), diagonal[0].z());
            vertices[2] = point3(diagonal[1].x(), diagonal[0].y(), diagonal[1].z());
            vertices[5] = point3(diagonal[1].x(), diagonal[1].y(), diagonal[0].z());
            vertices[1] = point3(diagonal[1].x(), diagonal[0].y(), diagonal[0].z());
            vertices[7] = point3(diagonal[0].x(), diagonal[1].y(), diagonal[1].z());

            hittable_list::add(make_shared<triangle>(vertices[0], vertices[1], vertices[2], m));
            hittable_list::add(make_shared<triangle>(vertices[0], vertices[2], vertices[3], m));
            hittable_list::add(make_shared<triangle>(vertices[0], vertices[5], vertices[4], m));
            hittable_list::add(make_shared<triangle>(vertices[0], vertices[1], vertices[5], m));
            hittable_list::add(make_shared<triangle>(vertices[1], vertices[2], vertices[5], m));
            hittable_list::add(make_shared<triangle>(vertices[2], vertices[5], vertices[6], m));
            hittable_list::add(make_shared<triangle>(vertices[2], vertices[6], vertices[3], m));
            hittable_list::add(make_shared<triangle>(vertices[3], vertices[6], vertices[7], m));
            hittable_list::add(make_shared<triangle>(vertices[0], vertices[3], vertices[4], m));
            hittable_list::add(make_shared<triangle>(vertices[3], vertices[4], vertices[7], m));
            hittable_list::add(make_shared<triangle>(vertices[4], vertices[5], vertices[7], m));
            hittable_list::add(make_shared<triangle>(vertices[7], vertices[5], vertices[6], m));
        }
};

#endif