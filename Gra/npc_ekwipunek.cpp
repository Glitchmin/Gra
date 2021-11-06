#include "npc.h"

#define endl " >"<<__FUNCTION__<<"<"<<endl

using namespace std;

extern string bonusystr [7];
extern string bonusypoz_stopnstr [7];
extern string bonusyneg_stopnstr [7];
extern vector <int> bonusyint_critch;
extern vector <int> bonusyint_critdmg;
extern vector <int> bonusyint_procenty;

int NPC::bonus(int i){
    int bonuss=0;
    vector <int> tab = bonusyint_procenty;
    if (i==3){
        tab=bonusyint_critch;
    }
    if (i==4){
        tab=bonusyint_critdmg;
    }
    if (!ekw[0].empty()){
        if (ekw[0][0].zwrocbonus(i)>0){
            bonuss+=tab[ekw[0][0].zwrocbonus(i)-1];
        }
        if (ekw[0][0].zwrocbonus(i)<0){
            bonuss-=tab[-ekw[0][0].zwrocbonus(i)-1];
        }
    }
    if (!ekw[1].empty()){
        if (ekw[1][0].zwrocbonus(i)>0){
            bonuss+=tab[ekw[1][0].zwrocbonus(i)-1];
        }
        if (ekw[1][0].zwrocbonus(i)<0){
            bonuss-=tab[-ekw[1][0].zwrocbonus(i)-1];
        }
    }
    if (!ekw[4].empty()){
        if (ekw[4][0].zwrocbonus(i)>0){
            bonuss+=tab[ekw[4][0].zwrocbonus(i)-1];
        }
        if (ekw[4][0].zwrocbonus(i)<0){
            bonuss-=tab[-ekw[4][0].zwrocbonus(i)-1];
        }
    }
    return bonuss;
}

bool NPC::dodajdoekw (it item,int gdzie, bool czynapr){
    if (gdzie == 0){
        if (ekw[gdzie].empty() && (item.typ==0 || item.typ==1)){
            if (czynapr){
                ekw[gdzie].push_back(item);
            }
            return 1;
        }
        return 0;
    }
    if (gdzie == 1){
        if (ekw[gdzie].empty() && (item.typ==4)){
            if (czynapr){
                ekw[gdzie].push_back(item);
            }
            return 1;
        }
        return 0;
    }
    if (gdzie == 2){
        if (ekw[gdzie].empty() && (item.typ==0)){
            if (czynapr){
                ekw[gdzie].push_back(item);
            }
            return 1;
        }
        return 0;
    }
    if (gdzie == 3){
        if (ekw[gdzie].empty() && ((item.typ==0 && item.inty[0]==2)||item.typ==2)){
            if (czynapr){
                ekw[gdzie].push_back(item);
            }
            return 1;
        }
        if (!ekw[gdzie].empty() && ekw[gdzie][0].typ==2 && ekw[gdzie].size()!=rozmstrz && item.typ==2){
            if (czynapr){
                ekw[gdzie].push_back(item);
            }
            return 1;
        }
        return 0;
    }
    if (gdzie == 4){
        if (ekw[gdzie].empty() && (item.typ==3)){
            if (czynapr){
                ekw[gdzie].push_back(item);
            }
            return 1;
        }
        return 0;
    }
    if (gdzie == 5){
        if (ekw[gdzie].size()!=ilstrz && item.typ==2){
            if (czynapr){
                ekw[gdzie].push_back(item);
            }
            return 1;
        }
        return 0;
    }
    if (gdzie == 6){
        if (ekw[gdzie].size()!=rozmjedz && item.typ==5){
            if (czynapr){
                ekw[gdzie].push_back(item);
            }
            return 1;
        }
        return 0;
    }
    if (gdzie == 7){
        if (ekw[gdzie].empty() && (item.typ==0 || item.typ==1 || item.typ==4)){
            if (czynapr){
                ekw[gdzie].push_back(item);
            }
            return 1;
        }
        return 0;
    }
    if (gdzie == 8){
        if (ekw[gdzie].empty() && (item.typ==0 || item.typ==1 || item.typ==4) && pl.t.empty()){
            if (czynapr){
                ekw[gdzie].push_back(item);
            }
            return 1;
        }
        return 0;
    }
    return 0;
}

bool NPC::dodajdopl(it item, bool czynapr){
    int a=item.wym/10;
    int b=item.wym%10;
    if (pl.t.empty()){
        return 0;
    }
    bool czek=0;
    for (int j=0; j<pl.t[0].size();j++){
        for (int i=0; i<pl.t.size();i++){
            czek=0;
            if (item.typ==2){
                if (pl.t[i][j] && pl.prz[pl.t[i][j]-1][0].typ==2 && pl.prz[pl.t[i][j]-1].size()<rozmstrz){
                    if (czynapr){
                        pl.prz[pl.t[i][j]-1].push_back(item);
                    }
                    return 1;
                }
            }
            if (item.typ==5){
                if (pl.t[i][j] && pl.prz[pl.t[i][j]-1][0].typ==5 && pl.prz[pl.t[i][j]-1].size()<rozmjedz && item.wym==pl.prz[pl.t[i][j]-1][0].wym){
                    if (czynapr){
                        pl.prz[pl.t[i][j]-1].push_back(item);
                    }
                    return 1;
                }
            }
        }
    }
    for (int j=0; j<pl.t[0].size();j++){
        for (int i=0; i<pl.t.size();i++){
            czek=0;
            for (int i2=0; i2<a;i2++){
                for (int j2=0; j2<b;j2++){
                    if (i+i2>=pl.t.size() || j+j2>=pl.t[0].size()){
                        czek=1;
                        break;
                    }
                    if (pl.t[i+i2][j+j2]!=0){
                        czek=1;
                    }
                }
            }
            if (czek==0){
                if (czynapr){
                    for (int i2=0; i2<a;i2++){
                        for (int j2=0; j2<b;j2++){
                            pl.t[i+i2][j+j2]=pl.prz.size()+1;
                        }
                    }
                    vector <it> tmp;
                    tmp.push_back(item);
                    pl.prz.push_back(tmp);
                }
                return 1;
            }
        }
    }
    return 0;
}

bool NPC::usunzpl(int k, int k2){
    pl.prz[k].erase(pl.prz[k].begin()+k2);
    if (pl.prz[k].empty()){
        pl.prz.erase(pl.prz.begin()+(k));
        for (int i=0; i<pl.t.size();i++){
            for (int j=0; j<pl.t[0].size();j++){
                if (pl.t[i][j]==k+1){
                    pl.t[i][j]=0;
                }
            }
        }
        for (int i=0; i<pl.t.size();i++){
            for (int j=0; j<pl.t[0].size();j++){
                if (pl.t[i][j]>k+1){
                    pl.t[i][j]--;
                }
            }
        }
        return 0;
    }
    return 1;
}

void NPC::sprawdzef(){
    bool czystun_tmp=0;
    for (int i=0; i<ef.size();i++){
        czek(ef[i]);
        if (ef[i].ile<0){
            ef.erase(ef.begin()+i);
            i--;
        }
        czystun_tmp = max(czystun_tmp,ef[i].czystun);
    }
    czystun=czystun_tmp;
    if (czystun){
        czyprzerwany_atak=1;
        if (SDL_GetTicks()-tatak < tmaxatak2){
            tmaxatak2=0;
            tmaxatak=0;
            czy_anim_ataku=0;
            czyatak=0;
        }else{
            tatak+=SDL_GetTicks()-t_stun;
        }
    }
    t_stun=SDL_GetTicks();
}

