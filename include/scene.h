#ifndef SCENE_H
#define SCENE_H

#include "hittable.h"
#include "material.h"
#include "hittable_list.h"
#include "shapes.h"

#include <fstream>
#include <string>
#include <iostream>
#include <vector>

//En este header se define la escena, la camara, la pantalla,
//la cantidad de rayos por pixel y la profundidad maxima

bool build_scene(   hittable_list& world,
                    int& image_width,
                    int& image_height,
                    int& samples_per_pixel,
                    int& max_depth,
                    camera& cam)
{
    //obtiene los parametros de la imagen
    std::ifstream currfile("parameters/img_parameters.txt");
    if(!currfile.is_open())
    {
        std::cout << "Ocurrio un error al intentar abrir img_parameters.txt\n";
        return false;
    }
    char trash;
    double num, denom, aspect_ratio;
    currfile >> num;
    currfile >> trash;
    currfile >> denom;
    aspect_ratio = num/denom;
    currfile >> image_width;
    image_height = static_cast<int>(image_width/aspect_ratio);
    currfile >> samples_per_pixel;
    currfile >> max_depth;
    currfile.close();
    
    //obtiene los parametros de la camara
    currfile.open("parameters/cam_parameters.txt");
    if(!currfile.is_open())
    {
        std::cout << "Ocurrio un error al intentar abrir cam_parameters.txt\n";
        return false;
    }
    double x, y, z, aux;
    currfile >> x >> y >> z;
    point3 lookfrom(x,y,z);     //Origen de la camara
    currfile >> x >> y >> z;
    point3 lookat(x,y,z);       //Punto a donde ve la camara
    currfile >> x >> y >> z;
    vec3 vup(x,y,z);            //Vector hacia arriba de la camara
    currfile >> aux;
    double vfov = aux;          //FOV vertical
    currfile >> aux;
    auto dist_to_focus = aux;   //Distancia de enfoque
    currfile >> aux;
    auto aperture = aux;        //Apertura del lente de la camara
    cam.build(lookfrom, lookat, vup, vfov, aspect_ratio, aperture, dist_to_focus);

    currfile.close();

    //Obtiene los parametros de los objetos de la escena
    currfile.open("parameters/world_objects.txt");
    if(!currfile.is_open())
    {
        std::cout << "Ocurrio un error al intentar abrir world_objects.txt\n";
        return false;
    }
    std::string mat, shape;
    std::shared_ptr<material> mat_ptr;
    while(currfile >> mat)
    {
        //Primero recibe el objeto
        if(mat == "metal")
        {
            currfile >> x >> y >> z >> aux;
            mat_ptr = make_shared<metal>(color(x, y, z), aux);
        }
        else if(mat == "lambertian")
        {
            currfile >> x >> y >> z;
            mat_ptr = make_shared<lambertian>(color(x, y, z));
        }
        else if(mat == "dielectric")
        {
            currfile >> aux;
            mat_ptr = make_shared<dielectric>(aux);
        }
        else if(mat == "light")
        {
            currfile >> x >> y >> z;
            mat_ptr = make_shared<light>(color(x, y, z));
        }

        //Luego recibe la figura
        currfile >> shape;
        if(shape == "sphere")
        {
            currfile >> x >> y >> z;
            point3 center(x, y, z);
            double radius;
            currfile >> radius;
            world.add(make_shared<sphere>(center, radius, mat_ptr));
        }
        else if(shape == "plane")
        {
            currfile >> x >> y >> z;
    	    point3 p(x, y, z);
            currfile >> x >> y >> z;
            vec3 normal(x, y, z);
            world.add(make_shared<plane>(p, normal, mat_ptr));
        }
        else if(shape == "triangle")
        {
            currfile >> x >> y >> z;
            point3 v1(x, y, z);
            currfile >> x >> y >> z;
            point3 v2(x, y, z);
            currfile >> x >> y >> z;
            point3 v3(x, y, z);
            world.add(make_shared<triangle>(v1, v2, v3, mat_ptr));
        }
        else if(shape == "cube")
        {
            point3 cube_diagonal[2];
            for(int i = 0; i < 2; i++)
            {
                currfile >> x >> y >> z;
                cube_diagonal[i] = point3(x, y, z);
            }
            world.add(make_shared<cube>(cube_diagonal, mat_ptr));
        }
        else if(shape == "mesh")
        {
            int number_of_triangles, number_of_points;
            currfile >> number_of_points >> number_of_triangles;
            point3* points = new point3[number_of_points];
            int* index_order = new int[number_of_triangles*3];
            for(int i = 0; i < number_of_points; i++)
            {
                currfile >> x >> y >> z;
                points[i] = point3(x, y, z);
            }
            for(int i = 0; i < number_of_triangles*3; i++)
            {
                currfile >> index_order[i];
            }
            world.add(make_shared<mesh>(points, 
                                        index_order, 
                                        number_of_triangles,
                                        mat_ptr));
        }
    }

    currfile.close();
    return true;
}

#endif