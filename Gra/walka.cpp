#include <iostream>
#include "poci.h"
#include "napis.h"
#include "npc.h"

#define endl " >"<<__FUNCTION__<<"<"<<endl

extern vector <NPC> npc;
extern vector <int> w[8];

int obldouble (double w);

int miecz = 0;
int pala = 1;
int sztylet = 2;

double obliczarmor(int npcIDdef, bool czyatak_ciezki){
    double armor=0;
    if (!npc[npcIDdef].ekw[1].empty()){
        armor += npc[npcIDdef].ekw[1][0].dou[0]*(0.2+(1.0-0.5*czyatak_ciezki)*0.8*max(max(0,min((255*npc[npcIDdef].poziomblok)/npc[npcIDdef].tmaxblok,255))/255,(int)npc[npcIDdef].czyparada));
    }
    if (!npc[npcIDdef].ekw[4].empty()){
        armor += npc[npcIDdef].ekw[4][0].dou[0];
    }
    return armor;
}

pair <double, double> obl_at_ciezki(it & bron, int npcIDof){
    double bonusap  = 0.0;
    double bonusdmg  = 0.0;
    if (bron.inty[0] == miecz){
        bonusap+=0.2*(npc[npcIDof].dmg()+npc[npcIDof].ap());
        bonusdmg+=0.3*(npc[npcIDof].dmg()+npc[npcIDof].ap());
    }
    if (bron.inty[0] == pala){
        bonusdmg+=0.3*(npc[npcIDof].dmg()+npc[npcIDof].ap());
    }
    if (bron.inty[0] == sztylet){
        bonusdmg+=0.5*(npc[npcIDof].dmg()+npc[npcIDof].ap());
        bonusdmg-=0.1*(npc[npcIDof].dmg()+npc[npcIDof].ap());
    }
    return make_pair(bonusap,bonusdmg);
}

void atak(int npcIDof, int npcIDdef, bool czykontratak = 0){
    cout << "pocz"<<endl;
    NPC& of_npc = npc[npcIDof];
    NPC& def_npc = npc[npcIDdef];
    double armor = obliczarmor(npcIDdef, (of_npc.czyatciezki && !of_npc.ekw[0].empty() && of_npc.ekw[0][0].typ==0 && of_npc.ekw[0][0].inty[0]==pala));
    double wspdmg=1.0 - 0.5*czykontratak + 0.3*(czykontratak && !npc[0].ekw[0].empty() && npc[0].ekw[0][0].inty[0]==miecz);
    double wspdodge = 0.0;
    double bonusap = 0.0;
    double bonusdmg = 0.0;
    string kryt_string;

    if (!czykontratak && rand()%100<of_npc.cr_ch()){
        wspdmg *= of_npc.cr_wsp();
        kryt_string="!";
    }

    if (SDL_GetTicks()-def_npc.tdodge<def_npc.dodgespd()){
        wspdodge = (SDL_GetTicks()-def_npc.tdodge);
        wspdodge/=def_npc.dodgespd();
    }
    wspdmg*=1.0-wspdodge;

    double wsp_dmg_par [3]={0.3,0.5,0.6};
    if(!def_npc.ekw[0].empty() && def_npc.czyparada && !(of_npc.czyatciezki &&!of_npc.ekw[0].empty() && of_npc.ekw[0][0].typ==0 && of_npc.ekw[0][0].inty[0]==pala)){
        wspdmg*=wsp_dmg_par[def_npc.ekw[0][0].inty[0]];
    }

    if (of_npc.czyatciezki){
        if (!of_npc.ekw[0].empty() && of_npc.ekw[0][0].typ==0){
            pair <double, double> tmp=obl_at_ciezki(of_npc.ekw[0][0],npcIDof);
            bonusap+=tmp.first;
            bonusdmg+=tmp.second;
        }else{
            bonusdmg+=0.5*(of_npc.dmg()+of_npc.ap());
        }
    }

    double dmg = -max(armor - wspdmg*(of_npc.ap()+bonusap),0.0) + wspdmg*(of_npc.dmg()+bonusdmg);
    if (of_npc.sila){
        dmg +=  rand()%of_npc.sila;
    }
    if (dmg<0.0){
        dmg = (rand()%(-(int)dmg+1)==0);
    }

    if (def_npc.czyparada){
        atak(npcIDdef,npcIDof,1);
    }
    int dmg_ost = obldouble(dmg);
    napis tmp(to_string(-dmg_ost)+kryt_string,128+64*(dmg!=0.0),128*(dmg==0.0),128*(dmg==0.0),w[4][7],w[4][8]);

    if ((of_npc.czas_stunu_ciezki() && of_npc.czyatciezki) || (!kryt_string.empty() && of_npc.czas_stunu_kryt())){
        efekt tmp (1,0,of_npc.czas_stunu_ciezki()*of_npc.czyatciezki + of_npc.czas_stunu_kryt()*(!kryt_string.empty()),0,0,1);
        def_npc.ef.push_back(tmp);
    }
    if (czykontratak && !npc[0].ekw[0].empty() && npc[0].ekw[0][0].inty[0]==pala){
        efekt tmp (1,0,of_npc.czas_stunu_ciezki(),0,0,1);
        def_npc.ef.push_back(tmp);
        dmg_ost=0;
    }
    def_npc.napisy.push_back(tmp);
    def_npc.hp-=dmg_ost;
    cout << "koniec"<<endl;
}

pair <double, double> oblicz_dmg_strzaly_gracza (int npcIDdef, string& kryt_string){ //tylko dla gracza
    double dmg = npc[0].dmg();
    double ap = npc[0].ap();
    if (rand()%100 < npc[0].cr_ch()){
        dmg*=npc[0].cr_wsp();
        ap*=npc[0].cr_wsp();
        kryt_string="!";
    }
    return make_pair(ap,dmg);
}

void oblicz_strzale(poci& strzala, int npcIDdef){
    double armor = 0.0;
    NPC& def_npc = npc[npcIDdef];
    string kryt_string;
    if (!npc[npcIDdef].ekw[4].empty()){
        armor += npc[npcIDdef].ekw[4][0].dou[0];
    }
    if (!npc[npcIDdef].ekw[1].empty()){
        armor += npc[npcIDdef].ekw[1][0].dou[0];
    }

    double dmg;
    if (npcIDdef==0){
        dmg = -max(armor - (strzala.ap),0.0) + (strzala.dmg);
    }else{
        auto ap_obr = oblicz_dmg_strzaly_gracza(npcIDdef, kryt_string);
        dmg = -max(armor - (ap_obr.first),0.0) + (ap_obr.second);
    }
    int dmg_ost=obldouble(dmg);
    def_npc.hp -= dmg_ost;
    napis tmp(to_string(-dmg_ost)+kryt_string,128+64*(dmg!=0.0),128*(dmg==0.0),128*(dmg==0.0),w[4][7],w[4][8]);
    def_npc.napisy.push_back(tmp);


}
