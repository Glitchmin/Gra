#include <SDL.h>
#include <string>
#include <iostream>
#include <vector>
#include <sstream>

#include "structy.h"

using namespace std;

SDL_Texture* txL (string nazwa);
extern vector <vector <SDL_Texture*> > txnpc;
extern vector <vector <hitbox> > hitboxnpc;
extern vector <SDL_Texture*> txef;
extern vector <vector <SDL_Texture*> > txanim;
extern vector <int> txanimt;
extern vector <vector <SDL_Texture*> > txtr;
extern vector <int> txtrt;
extern vector <vector <SDL_Texture*> > txbg;
extern vector <int> txbgt;
extern vector <vector <SDL_Texture*> > txw;
extern vector <int> txwt;
extern vector <vector <SDL_Texture*> > txfw;
extern vector <int> txfwt;

double obliczhtx (SDL_Texture* tx){
Uint32 format;
int x,y,acces;
SDL_QueryTexture(tx,&format,&acces,&x,&y);
return (double)(y-x)/(double)x;
}

double obliczhtxszerokie (SDL_Texture* tx){
Uint32 format;
int x,y,acces;
SDL_QueryTexture(tx,&format,&acces,&x,&y);
x=x/(1.5);
return (double)(y-(x))/(double)(x);
}

bool wczytajtxterrain(){
    string sciezka2;
    string sciezka3;
    string tab[4]={"bg","tr","w","fw"};
    for (int k=0; k<4;k++){
            sciezka2=tab[k];
            sciezka3=tab[k];
            sciezka2="tx/terrain/fltx"+sciezka2+".bin";
            cout <<" otwarto "<< sciezka2;
            SDL_RWops* plik=SDL_RWFromFile(sciezka2.c_str(),"r");
            if (plik==NULL){
                cout << "NIE"<<endl;
                return 0;
            }else if (plik!=NULL){
                cout << " - wczytano pomyslnie "<<endl;
                int ilosc;
                SDL_RWread(plik, &ilosc,sizeof(int),1);
                if (k==0){
                    txbg.resize(ilosc);
                }
                if (k==1){
                    txtr.resize(ilosc);
                }
                if (k==2){
                    txw.resize(ilosc);
                }
                if (k==3){
                    txfw.resize(ilosc);
                }
                for (int i=0;i<ilosc;i++){
                    int numer;
                    SDL_RWread(plik, &numer,sizeof(int),1);
                    for (int j=0; j<=numer;j++){
                        stringstream ss;
                        ss << "tx/terrain/tx"+sciezka3<<i+1<<"_"<<j<<".bmp";
                        string ss2=ss.str();
                        cout << "wczytywanie "<<ss2<<endl;
                        if (k==0){
                            txbg[i].push_back(txL(ss2));
                        }
                        if (k==1){
                            txtr[i].push_back(txL(ss2));
                        }
                        if (k==2){
                            txw[i].push_back(txL(ss2));
                        }
                        if (k==3){
                            txfw[i].push_back(txL(ss2));
                        }

                    }
                    SDL_RWread(plik, &numer,sizeof(int),1);
                    if (k==0){
                        txbgt.push_back(numer);
                    }
                    if (k==1){
                        txtrt.push_back(numer);
                    }
                    if (k==2){
                        txwt.push_back(numer);
                    }
                    if (k==3){
                        txfwt.push_back(numer);
                    }
                }
            }
        }
}

bool wczytajtxnpc(){
    SDL_RWops* plik=SDL_RWFromFile("tx/npc/hitboxnpc.bin","r");
    if (plik == NULL) {
        return 0;
    }
    int il_n;
    SDL_RWread(plik, &il_n,sizeof(int),1);
    txnpc.resize(il_n);
    cout << "ILOSC_tx_npc:" <<il_n<<endl;
    hitboxnpc.resize(il_n);
    for (int n=0; n<il_n;n++){
        for (int i=0; i<4;i++){
            txnpc[n].push_back(txL("tx/npc/npc"+to_string(n)+"_"+to_string(i)+".bmp"));
        }
        hitboxnpc[n].resize(2);
        SDL_RWread(plik, &hitboxnpc[n][0].x_lewy,sizeof(double),1);
        SDL_RWread(plik, &hitboxnpc[n][0].x_prawy,sizeof(double),1);
        SDL_RWread(plik, &hitboxnpc[n][0].y_gora,sizeof(double),1);
        SDL_RWread(plik, &hitboxnpc[n][0].y_dol,sizeof(double),1);
        SDL_RWread(plik, &hitboxnpc[n][1].x_lewy,sizeof(double),1);
        SDL_RWread(plik, &hitboxnpc[n][1].x_prawy,sizeof(double),1);
        SDL_RWread(plik, &hitboxnpc[n][1].y_gora,sizeof(double),1);
        SDL_RWread(plik, &hitboxnpc[n][1].y_dol,sizeof(double),1);
    }
    SDL_RWclose(plik);
    return 1;
}


SDL_Texture* zwroctxtr(long long x, long long y, int txnumer){
    long long t=txtrt[txnumer];
    long long il=txtr[txnumer].size();
    if (il>1){
        if (t>0){
            long long tpocz = ((1<<24)*(x+1) + (1<<30)*(y+1))%(il*t);
            tpocz*=((1<<15)-x);
            tpocz%=il*t;
            tpocz*=((1<<15)-y);
            return txtr[txnumer][((tpocz+SDL_GetTicks())/t)%il];
        }else{
            return txtr[txnumer][(13*x+23*y)%il];
        }
    }else{
        return txtr[txnumer][0];
    }
}
SDL_Texture* zwroctxbg(long long x, long long y, int txnumer){
    long long t=txbgt[txnumer];
    long long il=txbg[txnumer].size();
    if (il>1){
        if (t>0){
            long long tpocz = ((1<<21)*(x+1) + (1<<28)*(y+1))%(il*t);
            tpocz*=((1<<16)-x);
            tpocz%=il*t;
            tpocz*=((1<<16)-y);
            return txbg[txnumer][((tpocz+SDL_GetTicks())/t)%il];
        }else{
            return txbg[txnumer][(19*x+37*y)%il];
        }
    }else{
        return txbg[txnumer][0];
    }
}
SDL_Texture* zwroctxw(long long x, long long y, int txnumer){
    long long t=txwt[txnumer];
    long long il=txw[txnumer].size();
    if (il>1){
        if (t>0){
            long long tpocz = ((1<<28)*(x+1) + (1<<21)*(y+1))%(il*t);
            tpocz*=((1<<16)-x);
            tpocz%=il*t;
            tpocz*=((1<<16)-y);
            return txw[txnumer][((tpocz+SDL_GetTicks())/t)%il];
        }else{
            return txw[txnumer][(23*x+17*y)%il];
        }
    }else{
        return txw[txnumer][0];
    }
}
SDL_Texture* zwroctxfw(long long x, long long y, int txnumer){
    long long t=txfwt[txnumer];
    long long il=txfw[txnumer].size();
    if (il>1){
        if (t>0){
            long long tpocz = ((1<<23)*(x+1) + (1<<29)*(y+1))%(il*t);
            tpocz*=((1<<19)-x);
            tpocz%=il*t;
            tpocz*=((1<<19)-y);
            return txfw[txnumer][((tpocz+SDL_GetTicks())/t)%il];
        }else{
            return txfw[txnumer][(13*x+19*y)%il];
        }
    }else{
        return txfw[txnumer][0];
    }
}
