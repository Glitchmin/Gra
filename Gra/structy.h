#ifndef STRUCTY_H
#define STRUCTY_H

#include <SDL.h>
#include <time.h>
#include <windows.h>
#include <sstream>
#include <iostream>
#include <vector>
#include <winuser.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#define endl " >"<<__FUNCTION__<<"<"<<endl

#include "it.h"

using namespace std;



struct xy{
int x,y;
xy() {
    this->x = -1;
    this->y = -1;
}
xy(int x, int y) {
    this->x = x;
    this->y = y;
}
};

struct xyd{
double x,y;
xyd() {
    this->x = -1;
    this->y = -1;
}
xyd(double x, double y) {
    this->x = x;
    this->y = y;
}
};

struct cz{
    Uint32 mss;
    int dni;
};

struct efekt{
    efekt();
    efekt(int czest, int ID, int ile, double obr, int zwobr, bool czystun);
    int ID;
    double obr;
    int czest;//obrazenia (leczenie jest ujemne), czestotliowsc
    int zwobr;//zwiekszenie obrazen
    int tef;//czas w ms jaki zostal do kolejnej czestotliwosci
    Uint32 t;//czas w ms od ostatnich obliczen
    int ile;//czas w ms jaki zostal do konca efektu
    bool czystun;
};



struct efestrz{
    efekt ef;
    string nazwa;
    int fade; //ilosc przed zejsciem efektu, -1 oznacza ze nie schodzi
    int tekstura;
};

struct wierzch{  //wierzcholek grafu w grafie rozmowy;
    int ID;
    string tekst;
    vector <pair<int,double> > wymief; //jaki to wymog, typ wymogu (jesli to ekw to 1,2,3 (miecz, zbroja, jedzenie)
    bool czyj; //0 jesli gracza
    vector <it> itemydodania;
};

struct hitbox{
    double x_lewy;
    double x_prawy;
    double y_gora;
    double y_dol;
};



#endif
