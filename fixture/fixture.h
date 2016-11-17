#ifndef FIXTURE_H_INCLUDED
#define FIXTURE_H_INCLUDED

#include <iostream>
//#include "torneo.h"// contendra las funciones leerEquipo, generarPartido y simularPartido

#include <cstdlib>
#include <cmath>
#include <string>
#include <time.h>
#define BUFFER_SIZE 1024
using namespace std;

class Equipo{ //acá entran  los datos del archivo
    short indice;
    char nombre[31];
    int paramA;
    int paramB;
};
 //para el array que va a tener cada partido
class tipopartido{
    char equipo[31];
    int resultado;
    int paramA;
    int paramB;
    int puntos;
};

class partidosfixture{ // local y visitante tienen almacenado un array tipopartido por fecha
    tipopartido local[99];
    tipopartido visitante[99];
};

class posiciones{ // Para mostrar la tabla de posiciones uso otro array en vez de la lista, es más fácil de ordenar
    int puntos;
    char nombre[31];
};

class info{ //nodo de información de la lista
    int fecha;
    partidosfixture tabla[99];
    bool fuesimulado;
};

class tipofixture{ // la lista del fixture
info infofixture;
tipofixture *siguiente;
};


#endif // FIXTURE_H_INCLUDED
