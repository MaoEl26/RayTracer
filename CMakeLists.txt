cmake_minimum_required(VERSION 3.10)
project(Programada_3_fix_1_0_0 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(Programada_3_fix_1_0_0
        cilindro.c
        cilindro.h
        disco.c
        disco.h
        elipse.c
        elipse.h
        Esfera.c
        Esfera.h
        estructuras.c
        estructuras.h
        input.c
        input.h
        plano.c
        plano.h
        poligono.c
        poligono.h
        rayTrace.c
        rayTrace.h)
