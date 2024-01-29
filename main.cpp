#include "include/constants_and_utilities.h"

#include "include/camera.h"
#include "include/color.h"
#include "include/hittable_list.h"
#include "include/shapes.h"
#include "include/material.h"
#include "include/scene.h"

#include <iostream>
#include <fstream>

color ray_color(const ray& r, const hittable& world, int depth)
{
    hit_record rec;

    //Si se excede la profundidad maxima de rebote el rayo no aporta luz
    if(depth <= 0) return color(0,0,0);

    //Si el rayo choca con algun objeto calculamos sus rayos de 
    //rebote y el color que va a regresar el rayo
    if(world.hit(r, 0.001, infinity, rec))
    {
        color emitted = rec.mat_ptr -> emitted();
        ray scattered;
        color attenuation;
        if(rec.mat_ptr -> scatter(r, rec, attenuation, scattered))
            return emitted + attenuation*ray_color(scattered, world, depth-1);
        return emitted;   
    }
    
    //Si el rayo no choca contra algun objeto se colorea el fondo,
    //en este caso un degradado de azul a blanco
    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5*(unit_direction.y() + 1.0);
    return (1.0-t)*color(1.0, 1.0, 1.0) + t*color(0.5, 0.7, 1.0);
}

int main()
{
    hittable_list world;
    int image_width, image_height, samples_per_pixel, max_depth;
    camera cam;
    if(!build_scene(world, image_width, image_height, samples_per_pixel, max_depth, cam))
        return -1;
    
    //Archivo donde se escribe la imagen
    std::ofstream output;
    output.open("image.ppm");

    //Render

    output << "P3\n" << image_width << " " << image_height << "\n254\n";

    //Barra de progreso

    std::cout << "Progress: [____________________]";
    std::cout << "\rProgress: [";
    double imgby20 = image_height/20;
    double progress_mark = image_height-imgby20;

    for(int j = image_height-1; j >= 0; j--)
    {   
        //Cuando avanza 1/20 parte de la imagen, agrega un punto de progreso
        if(j < progress_mark)
        {
            std::cout << "#";
            progress_mark -= imgby20;
        }

        for(int i = 0; i < image_width; i++)
        {
            //El color del pixel actual inicia como negro y se actualiza
            //con los rayos aleatorios correspondientes al pixel
            color pixel_color(0, 0, 0);
            for(int s = 0; s < samples_per_pixel; s++)
            {
                auto u = double(i + random_double())/(image_width - 1);
                auto v = double(j + random_double())/(image_height - 1);
                ray r = cam.get_ray(u, v);
                pixel_color += ray_color(r, world, max_depth);
            }
            write_color(output, pixel_color, samples_per_pixel);
        }
    }

    std::cout << "\nDone.\n";
}