#ifndef MESH_H
#define MESH_H

#include "hittable_list.h"
#include "vec3.h"
#include "triangle.h"

class mesh : public hittable_list
{
    public:
        mesh(
            point3 points[], 
            int index_order[], 
            int number_of_triangles, 
            shared_ptr<material> m)
        {
            for(int i = 0; i < number_of_triangles; i++)
            {
                int first_index = i*3;
                hittable_list::add(make_shared<triangle>(points[index_order[first_index]],
                                                        points[index_order[first_index+1]],
                                                        points[index_order[first_index+2]],
                                                        m));
            }
        }
};

#endif