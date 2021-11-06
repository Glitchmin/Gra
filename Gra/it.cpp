#include "it.h"
#include "structy.h"


extern vector <vector <it> > przedm;
extern vector <xy> pozprzedm;
extern Uint32 momprzedm;
extern vector <int> w[8];

int it::zwrocbonus(int ktorybonus){
    //ktorybonus - dmg,ap,as,crch,crdmg,movspd,ds
    int bonus=bonusy;
    int tmp=0;
    int podziel=ktorybonus;
    while(podziel--){
        bonus/=16;
    }
    bool znak=bonus%2;
    bonus/=2;
    int tmp2=1;
    for (int i=0;i<3;i++){
        tmp+=(bonus%2)*tmp2;
        bonus/=2;
        tmp2*=2;
    }
    if (!znak){
        tmp*=(-1);
    }
    return tmp;
}

bool porownajit (it it1, it it2){
    return (it1.dou==it2.dou && it1.inty==it2.inty && it1.tekstura==it2.tekstura && it1.typ==it2.typ && it1.wym==it2.wym && it1.value == it2.value && it1.bonusy==it2.bonusy);
}

it stworzbron (int podtyp, double dmg, double ap, double as,int tekstura, int t, int maxt, int wym, int value,int bcrch,int bcrdmg, int bspd, int bds){
    it tmp;
    tmp.inty={podtyp};
    tmp.dou={dmg,ap,as};
    tmp.tekstura=tekstura;
    tmp.t=t;
    tmp.maxt=maxt;
    tmp.wym=wym;
    tmp.typ=0;
    tmp.value=value;
    tmp.ustawbonusy({0,0,0,bcrch,bcrdmg,bspd,bds});
    return tmp;
}

it stworzluk (double dmg, double ap, double cd,double prd, int tekstura, int t, int maxt, int wym, int value,int bcrch,int bcrdmg, int bspd, int bds){
    it tmp;
    tmp.dou={dmg,ap, cd, prd};
    tmp.tekstura=tekstura;
    tmp.t=t;
    tmp.maxt=maxt;
    tmp.wym=wym;
    tmp.typ=1;
    tmp.value=value;
    tmp.ustawbonusy({0,0,0,bcrch,bcrdmg,bspd,bds});
    return tmp;
}

it stworzstrz (int durability, int efnum,int effade, int tekstura, int t, int maxt, int wym, int value,int bdmg, int bap, int bcrch, int bcrdmg){
    it tmp;
    tmp.inty={durability, efnum, effade};
    tmp.tekstura=tekstura;
    tmp.t=t;
    tmp.maxt=maxt;
    tmp.wym=wym;
    tmp.typ=2;
    tmp.value=value;
    tmp.ustawbonusy({bdmg,bap,0,bcrch,bcrdmg,0,0});
    return tmp;
}

it stworzzbroje (double arm, int tekstura, int t, int maxt, int wym, int value, int bdmg,int bap, int bas, int bmovspd, int bds){
    it tmp;
    tmp.dou={arm};
    tmp.tekstura=tekstura;
    tmp.t=t;
    tmp.maxt=maxt;
    tmp.wym=wym;
    tmp.typ=3;
    tmp.value=value;
    tmp.ustawbonusy({bdmg,bap,bas,0,0,bmovspd,bds});
    return tmp;
}

it stworztarcze (double arm, double bs, int tekstura, int t, int maxt, int wym, int value, int bdmg,int bap, int bas, int bmovspd, int bds){
    it tmp;
    tmp.dou={arm, bs};
    tmp.tekstura=tekstura;
    tmp.t=t;
    tmp.maxt=maxt;
    tmp.wym=wym;
    tmp.typ=4;
    tmp.value=value;
    tmp.ustawbonusy({bdmg,bap,bas,0,0,bmovspd,bds});
    return tmp;
}

it stworzjedz (double heal, double coile, double naile,int zwsily, int zwdex, int tekstura, int t, int maxt, int wym, int value, int bdmg,int bap, int bas, int bcrch, int bcrdmg, int bmovspd, int bds){
    it tmp;
    tmp.inty={zwsily, zwdex};
    tmp.dou={heal,coile, naile};
    tmp.tekstura=tekstura;
    tmp.t=t;
    tmp.maxt=maxt;
    tmp.wym=wym;
    tmp.typ=5;
    tmp.value=value;
    tmp.ustawbonusy({bdmg,bap,bas,bcrch,bcrdmg,bmovspd,bds});
    return tmp;
}

it stworzitnic (){
    it tmp;
    tmp.typ=-1;
    return tmp;
}

int dodnam1(it item, int numer, int x,int y,vector<vector<int> >m1[]){
    xy tmp;
    tmp.x=x;
    tmp.y=y;
    if (!numer){
        int rozm=przedm.size();
        for (int i=1; i<rozm;i++){
            if (przedm[i].empty()){
                m1[3][pozprzedm[i].x][pozprzedm[i].y]=0;
                przedm[i].push_back(item);
                pozprzedm[i]=tmp;
                return i;
            }
        }
        przedm.resize(rozm+1);
        pozprzedm.resize(rozm+1);
        pozprzedm[rozm]=tmp;
        przedm[rozm].push_back(item);
        return rozm;
    }else{
        pozprzedm[numer]=tmp;
        if (item.t==-1){
            przedm[numer].insert(przedm[numer].begin(),item);
            return numer;
        }
        for (int i=0; i<przedm[numer].size();i++){
            //cout << przedm[numer][i].t<<" "<<item.t<<endl;
            if (item.t>=przedm[numer][i].t && przedm[numer][i].t!=-1){
                przedm[numer].insert(przedm[numer].begin()+i,item);
                return numer;
            }
        }
        przedm[numer].push_back(item);
        return numer;
    }
}

void przedmczek(bool pauz, vector<vector<int> > m1[]){
    int roz=SDL_GetTicks()-momprzedm;
    momprzedm=SDL_GetTicks();
    if (pauz){
        return;
    }
    int rozm=przedm.size();
    for (int i=0; i<rozm;i++){
        for (int j=0; j<przedm[i].size();j++){
            przedm[i][j].t-=roz;
            if (przedm[i][j].t<=-w[4][5] && przedm[i][j].maxt!=-1){
                przedm[i].erase(przedm[i].begin()+j);
                j--;
            }
        }
        if (przedm[i].empty()){
            m1[3][pozprzedm[i].x][pozprzedm[i].y]=0;
        }
    }
}
