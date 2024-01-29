#ifndef CAMERA_H
#define CAMERA_H

#include "constants_and_utilities.h"

class camera
{
    public:
        camera() {}
        void build(
            point3 lookfrom,     //Punto de origen de la camara
            point3 lookat,       //Punto al que ve la camara
            vec3 vup,            //Vector de vista hacia arriba
            double vfov,         //FOV vertical
            double aspect_ratio, //Relación de aspecto de la pantalla
            double aperture,     //Apertura del lente (0 todo enfocado)
            double focus_dist    //La distacia focal
        ){
            auto theta = degrees_to_radians(vfov);
            auto h = tan(theta/2);
            auto viewport_height = 2.0*h;
            auto viewport_width = aspect_ratio * viewport_height;

            auto focal_length = 1.0;
            
            w = unit_vector(lookfrom - lookat);
            u = unit_vector(cross(vup, w));
            v = cross(w, u);

            origin = lookfrom;
            horizontal = focus_dist*viewport_width*u;
            vertical = focus_dist*viewport_height*v;
            lower_left_corner = origin - horizontal/2 - vertical/2 - focus_dist*w;

            lens_radius = aperture/2;
        }

        //Funcion que lanza un rayo al pixel correspondiente.
        ray get_ray(double s, double t)
        {
            vec3 rd = lens_radius*random_in_unit_disk();
            vec3 offset = u*rd.x() + v*rd.y();
            return ray(origin + offset, lower_left_corner + s*horizontal + t*vertical - origin - offset);
        }
    private:
        point3 origin;
        point3 lower_left_corner;
        vec3 horizontal;
        vec3 vertical;
        vec3 u, v, w;
        double lens_radius;
};

#endif