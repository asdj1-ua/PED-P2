#include "tabbporo.h"
#include <queue>
//************  TNodoABB ************
TNodoABB::TNodoABB (){
    item = TPoro();
    iz = NULL;
    de = NULL;
}

TNodoABB::TNodoABB(const TNodoABB &nodo){
    item = nodo.item;
    if (nodo.iz != NULL){
        iz = new TABBPoro(*nodo.iz);
    } else {
        iz = NULL;
    }   
    if (nodo.de != NULL){
        de = new TABBPoro(*nodo.de);
    }else {
        de = NULL;
    }
}
TNodoABB::~ TNodoABB (){

}

TNodoABB& TNodoABB::operator=(const TNodoABB &otro) {
    if (this != &otro) { 
        item = otro.item;

        // Liberar memoria de los subárboles actuales
        if (iz != NULL) {
            delete iz;
            iz = NULL;
        }
        if (de != NULL) {
            delete de;
            de = NULL;
        }

        // Copiar los nuevos subárboles
        if (otro.iz != NULL)
            iz = new TABBPoro(*otro.iz);
        else
            iz = NULL;

        if (otro.de != NULL)
            de = new TABBPoro(*otro.de);
        else
            de = NULL;
    }
    return *this;
}

//************  TABBPoro ************
TABBPoro::TABBPoro() {
    nodo = NULL;
}

TABBPoro::TABBPoro(const TABBPoro &arbol) {
    if (arbol.nodo) {
        nodo = new TNodoABB(*arbol.nodo);
    } else {
        nodo = NULL;
    }
}

TABBPoro::~TABBPoro() {
    if (nodo != NULL) {
        delete nodo;
        nodo = NULL;
    }
}

TABBPoro& TABBPoro::operator=(const TABBPoro &arbol) {
    if (this != &arbol) {
        if (nodo != NULL) {
            delete nodo;
            nodo = NULL;
        }
        
        if (arbol.nodo != NULL) {
            nodo = new TNodoABB(*arbol.nodo);
        } 
    }
    return *this;
}
bool TABBPoro::operator==(TABBPoro &otro){
    return Inorden() == otro.Inorden();
}

bool TABBPoro::EsVacio(){
    return nodo == NULL;
}

bool TABBPoro::Insertar(TPoro &p){
    if (nodo == NULL) {
        nodo = new TNodoABB();
        nodo->item = p;
        nodo->iz = new TABBPoro();
        nodo->de = new TABBPoro();
        return true;
    } else if (p == nodo->item) {
        return false; // ya existe
    } else if (p.Volumen() < nodo->item.Volumen()) {
        return nodo->iz->Insertar(p);
    } else {
        return nodo->de->Insertar(p);
    }
}

bool TABBPoro::Borrar(TPoro &p){
    if (nodo == NULL)
        return false;

    if (p.Volumen() < nodo->item.Volumen())
        return nodo->iz->Borrar(p);
    else if (p.Volumen() > nodo->item.Volumen())
        return nodo->de->Borrar(p);
    else if (nodo->item == p) {
        // caso 1: hoja
        if (nodo->iz->EsVacio() && nodo->de->EsVacio()) {
            delete nodo;
            nodo = NULL;
        }
        // caso 2: solo hijo izquierdo
        else if (!nodo->iz->EsVacio() && nodo->de->EsVacio()) {
            TNodoABB *aux = nodo;
            nodo = nodo->iz->nodo;
            aux->iz->nodo = NULL; // para evitar delete recursivo
            delete aux->de;
            delete aux;
        }
        // caso 3: solo hijo derecho
        else if (nodo->iz->EsVacio() && !nodo->de->EsVacio()) {
            TNodoABB *aux = nodo;
            nodo = nodo->de->nodo;
            aux->de->nodo = NULL;
            delete aux->iz;
            delete aux;
        }
        // caso 4: dos hijos
        else {
            // sustituimos por el mayor de la izquierda
            TNodoABB *sust = nodo->iz->nodo;
            while (sust->de->nodo != NULL)
                sust = sust->de->nodo;
            nodo->item = sust->item;
            nodo->iz->Borrar(sust->item);
        }
        return true;
    }

    return false;
}

bool TABBPoro::Buscar(TPoro &poro){
    if (nodo == NULL)
        return false;

    if (nodo->item == poro)
        return true;

    if (poro.Volumen() < nodo->item.Volumen())
        return nodo->iz->Buscar(poro);
    else
        return nodo->de->Buscar(poro);
}

TPoro TABBPoro::Raiz(){
    if(nodo != NULL){
        return nodo->item;
    }
    return TPoro();
}

int TABBPoro::Altura(){
    if(nodo == NULL){
        return 0;
    }
    int izq = nodo->iz->Altura();
    int der = nodo->de->Altura();
    return 1 + max(izq, der);
}

int TABBPoro::Nodos(){
    if(nodo == NULL){
        return 0;
    }
    return 1 + nodo->iz->Nodos() + nodo->de->Nodos();
}
int TABBPoro::NodosHoja(){
    if(nodo == NULL){
        return 0;
    }
    if(nodo->iz->EsVacio() && nodo->de->EsVacio()){
        return 1;
    }
    return nodo->iz->NodosHoja() + nodo->de->NodosHoja();
}
//RECORRIDOS
void TABBPoro::InordenAux(TVectorPoro &v, int &pos) {
    if (nodo != NULL) {
        nodo->iz->InordenAux(v, pos);
        v[pos++] = nodo->item;
        nodo->de->InordenAux(v, pos);
    }
}

TVectorPoro TABBPoro::Inorden() {
    TVectorPoro v(Nodos());
    int pos = 1;
    InordenAux(v, pos);
    return v;
} 
void TABBPoro::PreordenAux(TVectorPoro &v, int &pos) {
    if (nodo != NULL) {
        v[pos++] = nodo->item;
        nodo->iz->PreordenAux(v, pos);
        nodo->de->PreordenAux(v, pos);
    }
}

TVectorPoro TABBPoro::Preorden() {
    TVectorPoro v(Nodos());
    int pos = 1;
    PreordenAux(v, pos);
    return v;
}

void TABBPoro::PostordenAux(TVectorPoro &v, int &pos) {
    if (nodo != NULL) {
        nodo->iz->PostordenAux(v, pos);
        nodo->de->PostordenAux(v, pos);
        v[pos++] = nodo->item;
    }
}

TVectorPoro TABBPoro::Postorden() {
    TVectorPoro v(Nodos());
    int pos = 1;
    PostordenAux(v, pos);
    return v;
}


TVectorPoro TABBPoro::Niveles(){
    TVectorPoro vector;
    if (nodo == nullptr) {
        return vector;
    }

    queue<TABBPoro*> cola;
    cola.push(this);

    int pos = 1; // para insertar en el TVectorPoro
    int total = this->Nodos(); // saber cuántos nodos hay en total
    vector = TVectorPoro(total); // redimensionamos el vector

    while (!cola.empty()) {
        TABBPoro* actual = cola.front();
        cola.pop();

        if (actual->nodo != nullptr) {
            vector[pos] = actual->nodo->item;
            pos++;

            if (actual->nodo->iz != nullptr && actual->nodo->iz->nodo != nullptr)
                cola.push(actual->nodo->iz);

            if (actual->nodo->de != nullptr && actual->nodo->de->nodo != nullptr)
                cola.push(actual->nodo->de);
        }
    }

    return vector;
}


TABBPoro TABBPoro::operator+(TABBPoro &arbol) {
    TABBPoro res(*this);
    TVectorPoro v = arbol.Inorden();
    for (int i = 1; i <= v.Longitud(); i++) {
        TPoro p = v[i];
        if (!p.EsVacio()) res.Insertar(p);
    }
    return res;
}

TABBPoro TABBPoro::operator-(TABBPoro &arbol) {
    TABBPoro res(*this);
    TVectorPoro v = arbol.Inorden();
    for (int i = 1; i <= v.Longitud(); i++) {
        TPoro p = v[i];
        if (!p.EsVacio()) res.Borrar(p);
    }
    return res;
}
ostream& operator<<(ostream &os, TABBPoro &abb) {
    os << abb.Niveles();
    return os;
}
