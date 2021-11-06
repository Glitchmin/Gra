#ifndef POCI_H
#define POCI_H

#include "structy.h"
#include "npc.h"

#define endl " >"<<__FUNCTION__<<"<"<<endl

class poci{
public:
    poci(){
    }
    poci(int &xm, int &ym,xy &pozgr, NPC & npcstrz, int nrnpc);
    xyd poz;
    xyd poppoz;
    xyd s;
    double predk;
    double wyzn; //x/y
    it strzala; //item
    Uint32 t; //ilosc milisekund od poprzedniego liczenia
    int npc; //wlasiciel pocisku
    double h;
    double horyg;
    double odl2;
    double kat;
    double katcienia;
    double popodl;
    bool xdod;
    double dmg, ap; //dla strzal npcow
};


#endif // POCI_H
