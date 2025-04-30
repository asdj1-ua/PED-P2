#include "tporo.h"
#include <cstring> 
#include <cctype> 

TPoro::TPoro() {
    x = 0;
    y = 0;
    volumen = 0.0;
    color = NULL;
}

TPoro::TPoro(int x, int y, double volumen) {
    this->x = x;
    this->y = y;
    this->volumen = volumen;
    color = NULL;
}

TPoro::TPoro(int x, int y, double volumen,const char* color){
    this->x = x;
    this->y = y;
    this->volumen = volumen;

    if (color != NULL) {
        int longitud = strlen(color);
        this->color = new char[longitud + 1];
        for (int i = 0; i < longitud; ++i) {
            this->color[i] = std::tolower(color[i]);
        }
        this->color[longitud] = '\0';
    } else {
        this->color = NULL;
    }
}

TPoro::TPoro(const TPoro &poro2){
    x = poro2.x;
    y = poro2.y;
    volumen = poro2.volumen;
    if (poro2.color != NULL) {
        color = new char[strlen(poro2.color) + 1];
        strcpy(color, poro2.color);
    } else {
        color = NULL;
    }
}

TPoro::~TPoro(){
    x = 0;
    y = 0;
    volumen = 0.0;
    delete[] color;
    color = NULL;
}

TPoro& TPoro::operator=(const TPoro& poro2){ // este otro & para pasar por parametro
    if(this != &poro2){ //este & sirve para acceder al valor y no la posicon en memoria
        (*this).~TPoro();
        x = poro2.x;
        y = poro2.y;
        volumen = poro2.volumen;

        if(poro2.color != NULL){
            color = new char[strlen(poro2.color) + 1]; // Reserva memoria
            strcpy(color, poro2.color); // Copia el contenido
        } else {
            color = NULL;
        }

    }
    return *this;
}

bool TPoro::operator==(const TPoro & poro2) const{
    if (x != poro2.x || y != poro2.y || volumen != poro2.volumen) {
        return false;
    }

    if (color == NULL && poro2.color == NULL) {
        return true;
    }

    if ((color == NULL && poro2.color != NULL) || (color != NULL && poro2.color == NULL)) {
        return false;
    }

    return strcmp(color, poro2.color) == 0;
}

bool TPoro::operator!=(const TPoro & poro2) const{
    return !(*this == poro2);
}

void TPoro::Posicion(int x, int y){
    this->x = x;
    this->y = y;
}

void TPoro::Volumen(double volumen){
    this->volumen = volumen;
}

void TPoro::Color(const char * colorNuevo){
    delete[] color;
    color = NULL;

    if (colorNuevo != NULL) {
        int longitud = strlen(colorNuevo);
        color = new char[longitud + 1];

        for (int i = 0; i < longitud; ++i) {
            color[i] = std::tolower(colorNuevo[i]);
        }

        color[longitud] = '\0';
    }
}

int TPoro::PosicionX() const{
    return x;
}

int TPoro::PosicionY() const{
    return y;
}

double TPoro::Volumen() const{
    return volumen;
}

char* TPoro::Color() const{
    return color;
}

bool TPoro::EsVacio() const{
    if(x == 0 && y == 0 && volumen == 0.0 && color == NULL){
        return true;
    }
    return false;
}

ostream& operator<<(ostream& os,const TPoro& poro){
    if(!poro.EsVacio()){ 
        os.setf(ios::fixed); 
        os.precision( 2 ); 
        os<<"("<<poro.x<<", "<<poro.y<<") "<<poro.volumen<<" "; 
        if(poro.color!=NULL) 
            os<<poro.color; 
        else 
            os<<"-"; 
    } else 
        os << "()"; 
    return os; 
}