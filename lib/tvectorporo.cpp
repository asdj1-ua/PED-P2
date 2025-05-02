#include "tvectorporo.h"

TVectorPoro::TVectorPoro(){
    dimension = 0;
    datos = NULL;
}

TVectorPoro::TVectorPoro(int dim){
    if(dim > 0){
        dimension = dim;
        datos = new TPoro[dim];
    } else {
        dimension = 0;
        datos = NULL;
    }
}

TVectorPoro::TVectorPoro(TVectorPoro &TVectorPoro2) : error(TVectorPoro2.error) {
    dimension = TVectorPoro2.dimension;
    
    if (dimension > 0) {
        datos = new TPoro[dimension];
        
        for (int i = 0; i < dimension; i++) {
            datos[i] = TVectorPoro2.datos[i];
        }
    } else {
        datos = NULL;
    }
}


TVectorPoro::~TVectorPoro() {
    dimension = 0;
    if(datos){
        delete[] datos;
        datos = NULL;
    }
}

TVectorPoro & TVectorPoro::operator=(const TVectorPoro &tvectorporo2){
    if(this != &tvectorporo2){
        (*this).~TVectorPoro();
        dimension = tvectorporo2.dimension;
        if (dimension > 0) {
            datos = new TPoro[dimension];

            for (int i = 0; i < dimension; i++) {
                datos[i] = tvectorporo2.datos[i];
            }
        } else {
            datos = NULL;
        }
        error = tvectorporo2.error;

    }
    return *this;
}

bool TVectorPoro::operator==(const TVectorPoro &tvectorporo2) const{
    if (dimension != tvectorporo2.dimension) {
        return false;
    }

    for (int i = 0; i < dimension; i++) {
        if (datos[i] != tvectorporo2.datos[i]) {  // != de TPoro
            return false;
        }
    }
    if (error != tvectorporo2.error) {
        return false;
    }
    return true;
}

bool TVectorPoro::operator!=(TVectorPoro &tvectorporo2){
    if (*this == tvectorporo2){
        return false;
    }
    return false;

}

TPoro & TVectorPoro::operator[](int indice){
    if (indice >= 1 && indice <= dimension) {
        return datos[indice - 1];
    } 
    return error;
}

TPoro TVectorPoro::operator[](int indice) const {
    if (indice >= 1 && indice <= dimension) {
        return datos[indice - 1];
    } 
    return error;
}

int TVectorPoro::Longitud() const{
    return dimension;
} 

int TVectorPoro::Cantidad() {
    int contador = 0;
    for (int i = 0; i < dimension; i++) {
        if (!datos[i].EsVacio()) {  
            contador++;
        }
    }
    return contador;
}

bool TVectorPoro::Redimensionar(int nuevaDimension) {
    if (nuevaDimension <= 0 || nuevaDimension == dimension) {
        return false;
    }

    TPoro *nuevoDatos = new TPoro[nuevaDimension];

    int limite = (nuevaDimension < dimension) ? nuevaDimension : dimension;

    for (int i = 0; i < limite; i++) {
        nuevoDatos[i] = datos[i];
    }

    for (int i = limite; i < nuevaDimension; i++) {
        nuevoDatos[i] = TPoro();
    }

    delete[] datos;

    datos = nuevoDatos;
    dimension = nuevaDimension;

    return true;
}

ostream& operator<<(ostream& os,const TVectorPoro& vectorporo){
    if(vectorporo.Longitud() != 0){
        os << "[";
        for (int i = 1; i <= vectorporo.Longitud(); i++) {  
            os << i << " " << vectorporo[i];

            if (i < vectorporo.Longitud()) {
                os << " ";
            }
        }
        os << "]";
    } else {
        os << "[]";
    }
    return os;
}
