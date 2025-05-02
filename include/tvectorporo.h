#ifndef TVECTORPORO_H
#define TVECTORPORO_H

#include <iostream>
#include "tporo.h"

using namespace std;

class TVectorPoro{
    friend ostream& operator<<(ostream& os,const TVectorPoro & tvectorporo); 
    private:
        int dimension;
        TPoro *datos;
        TPoro error;
    public:
        TVectorPoro(); 
        TVectorPoro(int dimension); 
        TVectorPoro(TVectorPoro &); 
        ~TVectorPoro(); 
        TVectorPoro & operator=(const TVectorPoro &); 
        bool operator==(const TVectorPoro &) const; 
        bool operator!=(TVectorPoro &); 
        TPoro &operator[](int); 
        TPoro operator[](int) const; 
        int Longitud() const; 
        int Cantidad(); 
        bool  Redimensionar(int); 
};

#endif
