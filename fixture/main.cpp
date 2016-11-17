#include <iostream>

using namespace std;
void GenerarFixture(Equipo vectorequipos[], tipofixture *fixture, int &fechastotales, int &PartidosPorFecha, int &totalequipos);


int main()
{
    int totalequipos= 0;
    posiciones vectortabla[99];
    tipofixture *fixture;
    tipofixture *listanueva = NULL;
    int fechastotales=0;
    int v=0;
    int a;
    int PartidosPorFecha;
    Equipo vectorequipos[99];
    int tamanio= 0;

    while (a!= 7){
        cout<<"FIXTURE 2014"<<endl;
        cout<<"Ingrese un número"<<endl;
        cout<<"1. Generar Fixture"<<endl;
        cout<<"2. Simular Partidos"<<endl;
        cout<<"3. Ver Equipo"<<endl;
        cout<<"4. Ver Tabla de Posiciones"<<endl;
        cout<<"5. Guardar Fixture"<<endl;
        cout<<"6. Cargar Fixture"<<endl;
        if (v==0){
            cout<<"7. Salir"<<endl;
        }
        cin>>a;
        int localA, localB, visitanteA, visitanteB, golesLocal, golesVisitante;
        if(a=1){ //con el switch explotaba, no sé porqué
            GenerarFixture(vectorequipos, fixture, fechastotales, PartidosPorFecha,totalequipos);
            listanueva = fixture;
            OrdenarLista(listanueva);
            cout<<"Su fixture se ha generado con éxito"<<endl;
        }
        else if (a=2){
            menusimularpartido (fixture,listanueva, fechastotales,PartidosPorFecha,vectortabla,tamanio);
        }
        else if (a=4){cout<<"ingrese una fecha, de querer ver la tabla hasta la ultima fecha simulada ingrese 0"<<endl;
            int m;
            cin>>m;
            if(recorrerlista(listanueva,m)){
                cout<<"No se simularon partidos hasta esa fecha";
            } else if(m=0) { cout<<"No existe una fecha 0!";}
            else MostrarTabla (listanueva,m,totalequipos,vectorequipos);
        }
        else if (a=3){
            MostrarEquipo(listanueva,PartidosPorFecha,fechastotales);
        }
        else if (a=5){ //tengo que reemplazar el archivo de existir, y crearlo de no figurar
            FILE *archivo = fopen ("equipos.txt", "w");
            for(int k=1;k<=totalequipos/2;k++){
                int f=0;

                fwrite((const void*)& f,sizeof(int)*1,1,archivo);
                fwrite((const void*) & listanueva->infofixture.tabla[f].local[f].paramA,sizeof(int)*1,1,archivo);
                fwrite((const void*) & listanueva->infofixture.tabla[f].local[f].paramB,sizeof(int)*1,1,archivo);
                fwrite(listanueva->infofixture.tabla[f].local[f].equipo,sizeof(char)*31,1,archivo);
                fwrite(listanueva->infofixture.tabla[f].visitante[f].equipo,sizeof(char)*31,1,archivo);

                f++;
            }
            cout<<"Guardado con éxito"<< endl;
            fclose(archivo);
        }
        else if (a=6){
            vaciarlista(fixture);
            vaciarlista(listanueva);
            GenerarFixture(vectorequipos,fixture,fechastotales,PartidosPorFecha,totalequipos);
            cout << "Se ha cargado y generado un nuevo fixture!" << endl;
        }
        else if(a=7){
            vaciarlista(fixture);
            vaciarlista(listanueva);
        }
    return 0;
}

void GenerarFixture(Equipo vectorequipos[], tipofixture *fixture, int &fechastotales, int &PartidosPorFecha, int &totalequipos) //Genera el fixture y además me devuelve algunos parámetros necesarios para saber tamaños
{
    int i=0;
    int r=1;

    int local = 0;
    int visitante = 0;

    LlenarVector(vectorequipos, i);
    if(i!=0){
    cout<<"Generando el fixture"<<endl;

    totalequipos = i+1;
    int t= totalequipos%2;

 if (t=0)
        fechastotales=totalequipos-1;
  else fechastotales= totalequipos;

    PartidosPorFecha = totalequipos/2;

    crearlista(fixture);

    if(fechastotales!=0){

    for(int l=1;l<=fechastotales;l++){
            Aleatoriafecha(l,fechastotales,fixture); //hace aleatoria la selección de fechas. Posterior ordenamiento.

        while(r<=totalequipos/2){

                    generarPartido(totalequipos, l, r, local, visitante);
                    ponerenlista(fixture,vectorequipos,local,visitante,i);


            };
        fixture->infofixture.fuesimulado=false; // Para evitar varias simulaciones.
        fixture=fixture->siguiente;

        };



    };
    cout<<"..."<<endl;
    cout<<"Generado!"<<endl;

  } else cout<<"En el archivo no hay equipos participantes!"<<endl; //si el archivo está vacío.
 }

/*****/

void LlenarVector(Equipo vectorequipos[], int &i) { //usando la función dada "leerequipo" lleno el vector y devuelvo el tamaño.
     FILE *archivo = fopen ("equipos.txt", "r");
  char nombre[31];
  int pA, pB;


  while (leerEquipo(archivo, nombre, pA, pB))
  {

   vectorequipos[i].paramA = pA; //estos dos son parámetros usados para simular partidos, son enteros.
   vectorequipos[i].paramB = pB;
   strncpy(vectorequipos[i].nombre, nombre, 31);
   i++;
         vectorequipos[i].indice = i;
  };
  fclose (archivo);




};
void Aleatoriafecha(int l, int fechastotales, tipofixture *fixture){
    srand(time(NULL));//Para que no repita en caso de fixture nuevo
    int vec[fechastotales];
    int x= 1+(rand()%fechastotales+1); //las fechas arracan en 1
    int w=0;
    vec[w]=x;


    if (FechaEncontrada(vec,fechastotales,x)){
            Aleatoriafecha(l,fechastotales,fixture);//si la fecha ya había sido usada, genera otro número aleatorio. Evito repetición de fechas.

    } else {
         fixture->infofixture.fecha=x; //si no encontró la fecha en el array, entonces se puede meter la fecha ahí
         w++;





}
}

bool FechaEncontrada(int vec[],int fechastotales, int x){
    bool encontrada=false;
    for(int t=0; t<=fechastotales-1; t++){ //que sea tamaño fechastotales-1 (el -1 va porque fechas totales arranca de 1) hace que se estén generando todas las fechas sin excepción
        if(vec[t]=x){
            encontrada=true;
        }
    }

return encontrada;



}
void crearlista(tipofixture *fixture){ //creo listas
    fixture=NULL;

};

void ponerenlista(tipofixture *fixture, Equipo vectorequipos[], int &local, int &visitante, int i) //Para poner en lista tengo que revisar los índices.
{
    int a=0;
buscarlocal(fixture,vectorequipos,local,visitante,i,a);
buscarvisitante(fixture,vectorequipos,visitante,i,a);
};

void buscarlocal(tipofixture *fixture, Equipo vectorequipos[], int local, int visitante, int i,int &a){ //Como el vector de equipos está ordenado por índice, hago una búsqueda binaria.

    int inicio = 0;
    int fin = i;
    bool encontrado = false;
    int pos = 0;
    while (inicio<=fin && !encontrado){
        pos = (inicio+fin)/2;
        if(vectorequipos[pos].indice == local){
            encontrado=true;
            strncpy(fixture->infofixture.tabla[a].local[a].equipo, vectorequipos[pos].nombre,31);
            fixture->infofixture.tabla[a].local[a].paramA = vectorequipos[pos].paramA;
            fixture->infofixture.tabla[a].local[a].paramB = vectorequipos[pos].paramB;
        } else if (vectorequipos[pos].indice>local){
                fin=pos-1;
                }else inicio = pos+1;

    }
}
void buscarvisitante(tipofixture *fixture, Equipo vectorequipos[], int visitante, int i, int &a){ //Búsqueda binaria para el visitante
    int inicio = 0;
    int fin = i;
    bool encontrado = false;
    int pos = 0;
    while (inicio<=fin && !encontrado){
        pos = (inicio+fin)/2;
        if(vectorequipos[pos].indice == visitante){
            encontrado=true;
            strncpy(fixture->infofixture.tabla[a].visitante[a].equipo, vectorequipos[pos].nombre,31);
            fixture->infofixture.tabla[a].visitante[a].paramA = vectorequipos[pos].paramA;
            fixture->infofixture.tabla[a].visitante[a].paramB = vectorequipos[pos].paramB;
            a++; // sumo acá el a porque ya terminé esta sección
        } else if (vectorequipos[pos].indice>visitante){
                fin=pos-1;
                }else inicio = pos+1;
    }
}


/****/

void menusimularpartido(tipofixture *fixture, tipofixture *listanueva,int fechastotales, int &PartidosPorFecha, posiciones vectortabla[], int &tamanio){
    int fechasimular;
    if(fechastotales>0){
    cout<<"Hasta que fecha desea simular los partidos?"<<endl;
    cin>>fechasimular;
    if(fechastotales<fechasimular && fechasimular>0){
        comprobarsimulacion(fixture,fechasimular,fechastotales,PartidosPorFecha,vectortabla,listanueva,tamanio);
    } else cout<< "El campeonato no llega hasta esa fecha (o se ha ingresado un valor mas chico que 1)!"; //si se escribe una fecha no permitida, lo indica.
    }

}


void comprobarsimulacion(tipofixture *fixture, int fechasimular, int fechastotales, int &PartidosPorFecha, posiciones vectortabla[], tipofixture *listanueva, int &tamanio){
    int i;
    if (recorrerlista(fixture,fechasimular)){
        cout<<"Ya hay fechas simuladas, desea sobreescribir los datos?"<<endl;
        cout<<"1.Si"<<endl;
        cout<<"2.No"<<endl;

        cin>>i;
        if (i=1){
            simularfecha(fixture,listanueva,fechasimular,PartidosPorFecha,vectortabla,tamanio);
        };
    } else simularfecha(fixture,listanueva,fechasimular,PartidosPorFecha,vectortabla, tamanio);


}

bool recorrerlista(tipofixture *fixture, int fechasimular){
    tipofixture *listaux=fixture;
    int a=1;
    bool t= false;
    while (a<=fechasimular){//si yo ingreso una fecha por ejemplo 4, y ya la primera está simulada, esto va a devolver verdadero para evitar sobreescribir la simulación anterior.
    if(listaux->infofixture.fuesimulado){
            t=true;
    } else listaux=listaux->siguiente; // como la lista está ordenada por fecha, no tiene sentido seguir, lo dejo porque no molesta.
    a++;
    }
    vaciarlista(listaux);
    return t;
}

void vaciarlista (tipofixture *listaux){//libero listas
    tipofixture *aux;
        while (listaux!=NULL){
            aux=listaux;
            listaux=listaux->siguiente;
            delete(aux);
        }
}
void simularfecha(tipofixture *fixture, tipofixture *listanueva, int fechasimular, int &PartidosPorFecha, posiciones vectortabla[], int &tamanio){

    int goleslocal=0;
    int golesvisitante=0;
    int totalpartidos= fechasimular*PartidosPorFecha;
    int a=1;
    while(fechasimular>=a){
        for(int x=1;x>=PartidosPorFecha;x++){
            int w=0;
            simularPartido(fixture->infofixture.tabla[w].local[w].paramA,fixture->infofixture.tabla[w].local[w].paramB,fixture->infofixture.tabla[w].visitante[w].paramA,fixture->infofixture.tabla[w].visitante[w].paramB,goleslocal,golesvisitante);
            if(goleslocal>golesvisitante){ //va a sumar los puntos por partido dependiendo del resultado, para luego ordenar más fácilmente.
            listanueva->infofixture.tabla[w].local[w].puntos=3;
            listanueva->infofixture.tabla[w].visitante[w].puntos=0;
            }else if (goleslocal<golesvisitante) {
            listanueva->infofixture.tabla[w].local[w].puntos=0;
            listanueva->infofixture.tabla[w].visitante[w].puntos=3;
            } else if (goleslocal=golesvisitante) { listanueva->infofixture.tabla[w].local[w].puntos=1;
            listanueva->infofixture.tabla[w].visitante[w].puntos=1;
            }
            listanueva->infofixture.tabla[w].local[w].resultado=goleslocal;
            listanueva->infofixture.tabla[w].visitante[w].resultado=golesvisitante;
            w++;

        }
        listanueva=listanueva->siguiente;
        a++;

    }




}

void MostrarEquipo(tipofixture *listanueva,int PartidosPorFecha, int fechastotales){
    tipofixture *mostrar = listanueva;
    char equipo[31];
    cout<<"ingrese el nombre del equipo que quiere buscar"<<endl;
    cin>>equipo;
    while (mostrar!=NULL){
        for(int x=1; x<=PartidosPorFecha; x++){
            int t=0;
            if(mostrar->infofixture.tabla[t].local[t].equipo[31]=equipo[31]){
                cout<<mostrar->infofixture.tabla[t].local[t].equipo<<"  "<< mostrar->infofixture.tabla[t].local[t].resultado<<"-"<<mostrar->infofixture.tabla[t].visitante[t].equipo<<"   "<<mostrar->infofixture.tabla[t].visitante[t].resultado<<endl;
            } else if (mostrar->infofixture.tabla[t].visitante[t].equipo[31]=equipo[31]){
                cout<<mostrar->infofixture.tabla[t].local[t].equipo<<"  "<< mostrar->infofixture.tabla[t].local[t].resultado<<"-"<<mostrar->infofixture.tabla[t].visitante[t].equipo<<"   "<<mostrar->infofixture.tabla[t].visitante[t].resultado<<endl;
                } else cout<<"ERROR: Parece que ha ingresado mal el nombre del equipo"<<endl;
        }
        mostrar=mostrar->siguiente;
    }
    vaciarlista(mostrar);
    }


void OrdenarLista(tipofixture *listanueva){
    tipofixture *listaordenada = NULL;
    while (listanueva!=NULL){
        tipofixture *ptr=listanueva;
        listanueva=listanueva->siguiente;
        ReinsertarEnLista(listaordenada,ptr);

    }
    listanueva=listaordenada;
    vaciarlista(listaordenada);

}

void ReinsertarEnLista(tipofixture *listaordenada, tipofixture *nuevo){
    tipofixture *ptr=listaordenada;
    tipofixture *ant;
    while (ptr!=NULL&&ptr->infofixture.fecha>nuevo->infofixture.fecha){
        ant = ptr;
        ptr=ptr->siguiente;
    }
    nuevo->siguiente=ptr;
    if(ptr=listaordenada){
        listaordenada=nuevo;
    } else ant->siguiente=nuevo;

}

void MostrarTabla(tipofixture *listanueva, int m, int totalequipos, Equipo vectorequipos[]){
    posiciones vec[totalequipos-1];
    for (int x=1;x>=totalequipos;x++){
        int w=0;
        strncpy(vec[w].nombre,vectorequipos[w].nombre,31);
        w++;
    }
    while (listanueva!=NULL){
        acumularpuntaje (vec, listanueva, totalequipos);
        ordenarpuntaje(vec,totalequipos);
    }
    for (int l=1;l<=totalequipos;l++){
        int p=0;
        cout<<vec[p].nombre<<":"<< vec[p].puntos<<endl;
    }

}

void acumularpuntaje (posiciones vec[],tipofixture *listanueva,int totalequipos){
    tipofixture *ptr=listanueva;
    while (ptr!=NULL){
        for(int x=1;x<=(totalequipos/2);x++){
            int w=0;
            if(ptr->infofixture.tabla[w].local[w].equipo[31]=vec[w].nombre[31]){
                    vec[w].puntos= vec[w].puntos+ptr->infofixture.tabla[w].local[w].puntos;

            } else if (ptr->infofixture.tabla[w].visitante[w].equipo[31]=vec[w].nombre[31]){
                    vec[w].puntos= vec[w].puntos+ptr->infofixture.tabla[w].visitante[w].puntos;
        }
    }
    ptr=ptr->siguiente;
    }
}
void ordenarpuntaje(posiciones vec[], int totalequipos){
    int aux=0;
    for(int j=0; j<=totalequipos-1; j++){
        for (int i=0; i<=totalequipos-1-j; i++){
            if(vec[i].puntos<vec[i+1].puntos){
                aux=vec[i].puntos;
                vec[i].puntos=vec[i+1].puntos;
                vec[i+1].puntos=aux;

            }
        }
    }


}

