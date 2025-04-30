#ifndef TABBPORO_H
#define TABBPORO_H

#include <iostream>
#include "tporo.h"
#include "tvectorporo.h"

using namespace std;

class TABBPoro;

class TNodoABB {
    friend class TABBPoro;
private:
    TPoro item;
    TABBPoro* iz;
    TABBPoro* de;
public:
    TNodoABB(); 
    TNodoABB(const TNodoABB &); 
    ~TNodoABB(); 
    TNodoABB& operator=(const TNodoABB &);
};

class TABBPoro {
    friend class TNodoABB;
    friend ostream& operator<<(ostream &, TABBPoro &); 
private:
    TNodoABB* nodo; 
    void InordenAux(TVectorPoro &, int &); 
    void PreordenAux(TVectorPoro &, int &); 
    void PostordenAux(TVectorPoro &, int &); 
public:
    TABBPoro(); 
    TABBPoro(const TABBPoro &); 
    ~TABBPoro(); 
    TABBPoro& operator=(const TABBPoro &); 
    //metodos
    bool operator==(TABBPoro &); 
    bool EsVacio(); 
    bool Insertar(TPoro &); 
    bool Borrar(TPoro &); 
    bool Buscar(TPoro &); 
    TPoro Raiz(); 
    int Altura(); 
    int Nodos();  
    int NodosHoja(); 
    TVectorPoro Inorden();  
    TVectorPoro Preorden(); 
    TVectorPoro Postorden(); 
    TVectorPoro Niveles(); 
    TABBPoro operator+(TABBPoro &); 
    TABBPoro operator-(TABBPoro &);
};

#endif