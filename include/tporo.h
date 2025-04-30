#ifndef TPORO_H
#define TPORO_H
#include <iostream>
using namespace std;

class TPoro{
    friend ostream& operator<<(ostream& os,const TPoro& poro);
    private:
        int x;
        int y;
        double volumen;
        char* color;
    public:
        TPoro();
        TPoro(int x, int y, double volumen);
        TPoro(int x, int y, double volumen,const char* color);
        TPoro(const TPoro &poro2);
        ~TPoro();
        TPoro& operator=(const TPoro &poro2); // si no se hace esto se hace uno por defecto
        //metodos
        bool operator==(const TPoro &poro2) const; 
        bool operator!=(const TPoro &poro2) const; 
        //extra añadir operator +
        void Posicion(int,int); 
        void Volumen(double); 
        void Color(const char *); 
        int PosicionX() const;
        int PosicionY() const; 
        double Volumen() const; 
        char * Color() const; 
        bool EsVacio() const; 
};
#endif