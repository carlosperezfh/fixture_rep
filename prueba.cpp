    /* inicialización del vector v: 0 1 2 3 4 5 6 7 8 9 */
    //for (unsigned int i=0; i<10; i++)


    /* inserta 99 en la cuarta posición y escribe el vector */
    vItr = v.begin();
    vItr += 3; /* avanza tres posiciones */
    v.insert(vItr, 99);
    copy(v.begin(), v.end(), outStream);
    cout << endl;

    /* inserta 88 en la cuarta posición del vector v sin modificar el iterador */
    vItr = v.begin();
    v.insert(vItr+3, 88);
    copy(v.begin(), v.end(), outStream);
    cout << endl;

    /* acceso a los elementos mediante el operador de índice */
    vItr = v.begin();
    for (unsigned int i=0; i<5; i++)
        cout << vItr[i] << ' ';
        cout << endl;

    /* escritura del vector v en orden inverso */
    vRitr = v.rbegin();
    while (vRitr != v.rend())
        cout << *vRitr++ << ' ';
        cout << endl;

    /* muestra de comparación de iteradores */
    vector<int>::iterator itr;

    itr = v.begin() + 5;
    vItr = v.begin();
    while (vItr <= itr)
        cout << *vItr++ << ' ';
    cout << endl;


5 repo
5 readme
10 legibilidad
40 poo  herencia polimorfismo
30 stl templates
10 patrones
  ng
  ni


