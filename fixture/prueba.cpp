using namespace std;

typedef struct{ //acá entran  los datos del archivo
    short indice;
 char nombre[31];
 int paramA;
 int paramB;
} Equipo; //para el array que va a tener cada partido
typedef struct{
    char equipo[31];
    int resultado;
    int paramA;
    int paramB;
    int puntos;
}tipopartido;

typedef struct{ // local y visitante tienen almacenado un array tipopartido por fecha
    tipopartido local[99];
    tipopartido visitante[99];
    }partidosfixture;
typedef struct{ // Para mostrar la tabla de posiciones uso otro array en vez de la lista, es más fácil de ordenar
    int puntos;
    char nombre[31];
}posiciones;
typedef struct{ //nodo de información de la lista
    int fecha;
    partidosfixture tabla[99];
    bool fuesimulado;
}info;

typedef struct tipofixture{ // la lista del fixture
info infofixture;
tipofixture *siguiente;
 }tipofixture;
