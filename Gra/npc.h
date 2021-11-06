#ifndef NPC_H
#define NPC_H

#include <vector>
#include <SDL.h>
#include <string>
#include <queue>
#include <algorithm>
#include <sstream>
#include <iostream>

#include "it.h"
#include "structy.h"
#include "napis.h"

#define endl " >"<<__FUNCTION__<<"<"<<endl

using namespace std;

class NPC{
public:
    NPC(int x, int y, int maxx, int minx, int maxy, int miny,int ruch1, int ruch2,int nrtekstury,int nrubr, int hp, int ileprz, vector <int> prz,vector <vector <it> >ekw, plecak pl,int rozmjedz,int strona, int zasieg, int sila, int predkat,double h);
    NPC();
    int x,y,popx,popy,maxx,minx,maxy,miny,ruch1,ruch2;
    xyd poz;
    int kierataku, popkier;
    xy xy_ataku;
    int momentruchu, czasruchu, czasodpo;
    Uint32 tmaxruch, truchu;
    bool rozmo;
    cz t;
    int hp, ileprz;
    vector <int> prz;
    vector <efekt> ef;
    vector <vector <it> > ekw;
    vector <it> pociskiwbite;
    plecak pl;
    vector <it> nasprzedaz;
    int rozmjedz;
    int rozmstrz; //ilosc strzal na slot
    int ilstrz;//rozm kolczanu
    int strona;
    int zasieg;
    int n;
    int gold;
    double wspsprzedazy;
    double wspkupna;
    vector <vector <int> > g;
    vector <int> e;
    vector <wierzch> wierz;
    int sila;
    int predkat;
    bool czymartwy;
    vector <xy> sciezka2;
    int gdzie;
    SDL_Texture* tekstura;
    double h;
    vector <napis> napisy;
    int wspheal;
    int wspcoile, wspnaile;
    int nrtekstury;
    int nrubr;
    int tmaxatak;
    int tmaxatak2;
    Uint32 tatak;
    bool czyatciezki;
    Uint32 tblok;
    bool czyatak;
    bool czy_anim_ataku;
    int tmaxblok;
    int poziomblok;
    bool czydodge;
    Uint32 tdodge;
    Uint32 tparada;
    bool czyparada;
    bool czystun;
    bool czyprzerwany_atak;
    Uint32 t_stun;
    vector <xy> sciezka1 (xy konieclg,xy koniecpd,vector<vector<int> > m1[]);

    hitbox zwr_hitbox();

    int bonus(int i);

    int dodgespd();

    int czasparady();

    int cdparady();

    double ap();

    double dmg();

    int cr_ch();

    double cr_wsp();

    int czas_stunu_ciezki();

    int czas_stunu_kryt();

    int kier();

    bool czyruch();

    void sprawdzef();

    void rend_atak(bool czyprzod);

    void updatetx();

    void dodge(vector <vector<int> > m1[]);

    pair <int,int> dl_ataku(bool czyciezki);

    void atak (bool czyciezki, Uint32 tataku);

    void anim_ataku ();

    bool czy_dlugi ();

    void zach (vector <vector <int> > m1[],vector <NPC> & npc);

    void czek (efekt &tmp);

    void zabij ();

    bool dodajdoekw (it item,int gdzie, bool czynapr);

    bool dodajdopl(it item, bool czynapr);

    bool usunzpl(int k, int k2);

    bool zapis(int ID);

    bool odczyt(int ID,bool czyorig);
};

#endif // NPC_H
