

#include "napis.h"


extern int KRATKA;

napis::napis(string tekst,int r,int g,int b,int ilems,int ilemszaniku){
    this->tekst=tekst;
    this->r=r;
    this->g=g;
    this->b=b;
    this->ilems=ilems;
    this->ilemsmax=ilems;
    this->ilemszaniku=ilemszaniku;
    this->poprz=SDL_GetTicks();
}

napis::napis(){
    this->tekst="pustooo";
    this->r=128;
    this->g=128;
    this->b=128;
    this->ilems=1000;
    this->ilemsmax=1000;
    this->poprz=SDL_GetTicks();
    this->ilemszaniku=500;
    this->x=KRATKA;
    this->y=KRATKA;
}
