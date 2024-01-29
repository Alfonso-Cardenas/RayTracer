### Jorge Alfonso Cárdenas Treviño | 18/11/2022

# Compilación y uso

Para compilar el raytracer se debe de tener una carpeta de include que contiene los headers personales utilizados en el programa. Una vez compilado el programa se debe de incluir una carpeta llamada parameters donde se incluirán los archivos cam_parameters.txt, img_parameters.txt y world_objects.txt. Cuando se defina la escena y se corra el programa, se generará una imagen ppm en la misma carpeta que el ejecutable con el nombre image.ppm. Los archivos de la carpeta de parameters nos permiten especificarle al programa la escena que queremos renderizar, a continuación se explica su uso:

## img_parameters.txt

En este archivo se definen en orden específico las siguientes variables:
-Relación de aspecto en forma de división. 
-Cantidad de pixeles de ancho de la imagen. 
-Cantidad de rayos lanzados por cada pixel.
-Cantidad de rebotes permitidos por rayo.

## cam_parameters.txt

En este archivo se definen en orden específico las siguientes variables:
-Punto de origen de la cámara.
-Punto en el espacio a donde está viendo la cámara.
-Vector que le indica a la cámara qué dirección es arriba en el mundo
-FOV vertical en grados.
-La distancia de enfoque.
-La apertura de la cámara (mientras mayor, más desenfocado aparecerán los objetos alejados).

## world_objects.txt

En este archivo se definen todos los objetos que aparecerán en la imagen. Los objetos se definen uno a uno definiendo primero el material y después la figura. A continuación se muestra un listado de los materiales y de las figuras disponibles, así como los parámetros de cada uno

### Materiales:
### lambertian

El material mate. Su único parámetro para definirlo es el color. Los rayos rebotan basándose en su normal.

### metal

El material metálico que refleja. Tiene como parámetros el color del objeto y un factor de qué tan borrosa es la imagen que refleja.

### dielectric

El material transparente que refracta los rayos similar al vidrio. Tiene como único parámetro el índice de refracción.

### light

El material de los objetos que emiten luz. Tiene como parámetro el color de la luz que emite, hay que tomar en cuenta que puede tomar valores mayores que 1 para tener mayor intensidad de luz y que los materiales que deben de ser iluminados deben de estar un poco oscurecidos (si se tiene un objeto con colores completamente saturados, no se puede iluminar más).

### Figuras:
### sphere

Una esfera definida por su centro y su radio (para formar una esfera de cristal vacía se pueden hacer dos esferas concéntricas dieléctricas donde el radio de la esfera de dentro es un poco más pequeño y con signo negativo para contrarrestar la refracción).

### plane

Un plano definido por un punto de referencia y su vector normal.

### triangle

Un triángulo bidimensional definido por sus tres vértices. Esta clase se puede utilizar, pero en la práctica es más útil utilizar las siguientes figuras que la usan de base.

### cube

Un cubo definido por un punto y su otro punto diagonalmente opuesto. Está conformado por 12 triángulos (2 por cada cara).

### mesh

Una figura cualquiera definida por una colección de vértices en el espacio y un orden que nos dice de qué manera se deben de unir para generar los triángulos.

### Muestra:

Se incluyen archivos de muestra en la carpeta de parameters para generar la siguiente imagen con el raytracer

![puppet](/sample_images/Inside_puppet.png)

En esta imagen generamos 4 esferas mate, una esfera de luz y un mesh basado en la figura que utilicé para el proyecto del puppet.

Una imagen un poco más compleja es la siguiente:

![best](/sample_images/best.png)

En esta se pueden ver todos los distintos materiales, hay una luz arriba, dos esferas dieléctricas (formando una esfera de cristal hueca), algunas esferas mate, un plano mate y otra esfera de metal.

# Headers

Como se mencionó anteriormente, la carpeta de include contiene todos los headers con las funciones utilizadas en el programa. Dentro de cada header se explica qué hace cada función de manera detallada, pero a continuación veamos de manera breve qué contiene cada uno de ellos:

### camera.h

Esta cabecera define la clase camara así como las funciones que necesita para funcionar correctamente. Cada escena necesita una sola cámara para poder renderizarse.

### color.h

Esta cabecera define la función utilizada para convertir los colores definidos como números reales a enteros entre 0 y 255 para poder imprimir la imagen en RGB. También suma el color encontrado por cada rayo y lo divide entre el número de rayos por pixel para obtener difuminados en pixeles donde cambia de un color a otro.

### constants_and_utilities.h

Esta cabecera incluye constantes útiles como pi e infinito y funciones que nos resultan útiles para usarse en el programa, como pasar de grados a radianes.

### cube.h

En esta cabecera definimos la clase de la figura del cubo. Se define como una colección de triángulos.

### hittable.h

En esta cabecera definimos la clase utilizadas por los objetos que pueden ser impactados por rayos y un record para guardar información del objeto impactado.

### hittable_list.h

En esta cabecera definimos una lista de hittables. Esto se utiliza para definir al mundo como una colección de objetos individuales que puedes impactar con rayos.

### material.h

En esta cabecera definimos todos los materiales mencionados anteriormente.

### plane.h

En esta cabecera se define la clase de la figura plano, así como la función utilizada para saber si se impactó.

### ray.h

En esta cabecera definimos la clase de rayo como un punto y una dirección, así como su función para obtener algún punto en un tiempo dado.

### scene.h

En esta cabecera definimos la función de build_scene, que es la que interpreta los parámetros pasados en los archivos de texto para poder renderizar la escena deseada.

### shapes.h

En esta cabecera simplemente se incluyen las cabeceras de todas las figuras definidas. Esto se hace para que resulte más simple agregar figuras en el futuro si se desea.

### sphere.h

En esta cabecera definimos la clase de esfera, así como la función para saber si se impactó.

### triangle.h

En esta cabecera definimos la clase del triángulo, así como la función para saber si se impactó.

### vec3.h

En esta cabecera definimos a los vectores de 3 dimensiones (point3 y col se consideran como sinónimos de vec3), así como las funciones básicas para poder operar con ellos y algunas otras funciones de utilidad.

## Referencias

Para generar este raytracer utilicé como referencia las diapositivas vistas en clase, junto con el libro [Raytracing in One Weekend](https://raytracing.github.io/books/RayTracingInOneWeekend.html). 