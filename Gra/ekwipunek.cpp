#include "structy.h"
#include "napis.h"
#include "npc.h"
#include <iomanip>
using namespace std;

extern int KRATKA;
extern int SZER;
extern int WYS;
extern int WYMx, WYMy;
extern const int OPWYJ;
extern int ZASx;
extern int ZASy;
extern const int PREDKOSC;
extern const int ILOSCw;
extern int dzien;
extern int tmpx[4];
extern int tmpy[4];
extern vector <int> w[8];
extern int liczzap;
extern SDL_Window* window;
extern SDL_Surface* screenSurface;
extern SDL_Texture* CzKw;
extern SDL_Texture* jezioro;
extern SDL_Texture* jezioro2;
extern SDL_Event e;
extern SDL_Renderer* Rend;
extern SDL_Rect stretchRect;
extern SDL_Surface* KRA;
extern TTF_Font* czcionka;
extern vector <vector <SDL_Texture*> > txit;
extern bool tmpekw;
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
extern int rozmtmp;
extern int relacja[5][5];
extern int u;
extern int xnasw, ynasw;
extern vector<vector <int> > swiat[6];
extern string bonusystr [7];
extern string bonusypoz_stopnstr [7];
extern string bonusyneg_stopnstr [7];
extern vector <int> bonusyint_critch;
extern vector <int> bonusyint_critdmg;
extern vector <int> bonusyint_procenty;
extern vector <napis> dowypisania;
extern vector <efestrz> efstrz;
extern vector <vector <it> > przedm;
extern vector <xy> pozprzedm;
extern Uint32 momprzedm;
extern vector <NPC> npc;
extern vector <it> podnitem;
extern vector <SDL_Texture*> podntx;
extern vector <xy> rozmtx;
extern xy podnwym;
extern bool mysza1;
extern bool ekwmyszaP;
extern bool ekwmyszaL;
extern int ekwwybr;
extern int ekwwybr2;
extern vector <it> bufer;
extern vector <string> stringi;
extern vector <xy> xyy;
extern SDL_Texture* ekwtx;
extern vector <SDL_Rect> ekwpole;
extern vector <SDL_Rect> ekwpole2;
extern bool czyzmianaekw;
extern int xpl, ypl;

xy multipodn (int x, int y, vector <it> & itemy);

xy wypisz (string txt, int x, int y, int r, int g, int b, int a);

xy wypisz2dou(int x,int y, string tekst,string tekst2, int wsp, int a, double w, bool czyczas){
    stringstream sss;
    sss <<setprecision(2)<<fixed<< w;
    stringstream ss;
    if (czyczas){
        ss<<setprecision(2)<<fixed<<" ("<<((w/(100.0-(double)wsp))*100.0)<<")";
    }else{
        ss<<setprecision(2)<<fixed<<" ("<<((w*(100+wsp))/100)<<")";
    }
    xy tmp3 =  wypisz(tekst+sss.str()+tekst2,x,y,194,178,76,a);
    if (wsp!=0){
        if (!czyczas){
            tmp3 = wypisz(ss.str(),tmp3.x,y,200*(wsp<0),200*(wsp>0),0,a);
        }else{
            tmp3 = wypisz(ss.str(),tmp3.x,y,200*(wsp>0),200*(wsp<0),0,a);
        }
    }
    return tmp3;
}

xy wypisz2int(int x,int y, string tekst,string tekst2, int wsp, int a, int w){
    stringstream sss;
    sss<<w;
    stringstream ss; ss<<" ("<<((w*(100+wsp))/100)<<")";
    xy tmp3 =  wypisz(tekst+sss.str()+tekst2,x,y,194,178,76,a);
    if (wsp!=0){
        tmp3 = wypisz(ss.str(),tmp3.x,y,200*(wsp<0),200*(wsp>0),0,a);
    }
    return tmp3;
}

void ryskr(int a, int b, int x, int y,int kwrozm){
    for (int i=0; i<=b;i++){
        SDL_RenderDrawLine(Rend,x+i*kwrozm,y,x+i*kwrozm,y+a*kwrozm);
    }
    for (int i=0; i<=a;i++){
        SDL_RenderDrawLine(Rend,x,y+i*kwrozm,x+b*kwrozm,y+i*kwrozm);
    }
}

void ekwipunek(){
    int kwrozm=WYS/15;
    SDL_SetRenderDrawColor(Rend, 150, 75, 0,255);
    int xm, ym;
    SDL_GetMouseState(&xm, &ym);
    if (czyzmianaekw){
        ekwpole.clear();
        ekwpole2.clear();
        SDL_SetRenderTarget(Rend,ekwtx);
        SDL_SetRenderDrawColor(Rend,0,0,0,0);
        SDL_RenderClear(Rend);
        SDL_Rect tmp;
        tmp.x=kwrozm;
        tmp.y=2*kwrozm;
        int konpl=0;
        int maxi = tmp.y + 5*kwrozm;
        for (int i=0; i<9;i++){
            if ((i==8 && npc[0].pl.t.empty()) || i!=8){
                if (npc[0].ekw[i].empty()){
                    tmp.h=xyy[i].x*kwrozm;
                    tmp.w=xyy[i].y*kwrozm;
                }else{
                    tmp.h=0;
                    tmp.w=0;
                    for (int j=0; j<npc[0].ekw[i].size();j++){
                        tmp.h=max(tmp.h,npc[0].ekw[i][j].wym/10*kwrozm);
                        tmp.w=max(tmp.w,npc[0].ekw[i][j].wym%10*kwrozm);
                    }
                }
                ekwpole.push_back(tmp);
                wypisz(stringi[i],-(tmp.x+tmp.w/2),tmp.y-kwrozm/2,196,196,196,255);
                if (i<6){
                    maxi=max(maxi,tmp.h+tmp.y);
                }
                if (npc[0].ekw[i].empty()){
                    SDL_SetRenderDrawColor(Rend,150,75,0,196);
                    ryskr(xyy[i].x,xyy[i].y,tmp.x,tmp.y, kwrozm);
                }else{
                    SDL_SetRenderDrawColor(Rend,150,75,0,255);
                    ryskr(tmp.h/kwrozm,tmp.w/kwrozm,tmp.x,tmp.y, kwrozm);
                    SDL_RenderCopy(Rend, txit[npc[0].ekw[i][0].typ][npc[0].ekw[i][0].tekstura],NULL,&tmp);
                }
                if (npc[0].ekw[i].size()>1){
                    xy tmp2 = wypisz("x"+to_string((int)npc[0].ekw[i].size()),0,0,-5,0,0,0);
                    wypisz("x"+to_string((int)npc[0].ekw[i].size()),tmp.x+tmp.w-tmp2.x,tmp.y+tmp.h-tmp2.y,255,255,255,255);
                }
                tmp.x+=tmp.w+kwrozm;
                konpl=max(konpl,tmp.x);
                if (i==5){
                    tmp.y=maxi+2*kwrozm;
                    tmp.x=kwrozm;
                }
            }
        }
        xpl=tmp.x;
        ypl=tmp.y;
        if (npc[0].pl.t.size()){
            SDL_SetRenderDrawColor(Rend,150,75,0,255);
            ryskr(npc[0].pl.t.size(),npc[0].pl.t[0].size(),tmp.x,tmp.y,kwrozm);
            tmp.x=xpl;
            tmp.y=ypl;
            tmp.h=npc[0].pl.t.size()*kwrozm;
            tmp.w=npc[0].pl.t[0].size()*kwrozm;
            konpl=max(konpl,xpl+tmp.w);
            ekwpole.push_back(tmp);
            ekwpole2.resize(npc[0].pl.prz.size());
            wypisz("backpack",-(tmp.x+(tmp.w)/2),tmp.y-kwrozm/2,196,196,196,255);
            for (int i=0; i<npc[0].pl.t.size();i++){
                for (int j=0; j<npc[0].pl.t[0].size();j++){
                    if (npc[0].pl.t[i][j] && !(i>0 && npc[0].pl.t[i-1][j]==npc[0].pl.t[i][j]) && !(j>0 && npc[0].pl.t[i][j-1]==npc[0].pl.t[i][j])){
                        tmp.x=xpl+j*kwrozm;
                        tmp.y=ypl+i*kwrozm;
                        tmp.h=npc[0].pl.prz[npc[0].pl.t[i][j]-1][0].wym/10*kwrozm;
                        tmp.w=npc[0].pl.prz[npc[0].pl.t[i][j]-1][0].wym%10*kwrozm;
                        ekwpole2[npc[0].pl.t[i][j]-1]=tmp;
                        SDL_RenderCopy(Rend, txit[npc[0].pl.prz[npc[0].pl.t[i][j]-1][0].typ][npc[0].pl.prz[npc[0].pl.t[i][j]-1][0].tekstura],NULL,&tmp);
                        if (npc[0].pl.prz[npc[0].pl.t[i][j]-1].size()>1){
                            xy tmp2 = wypisz("x"+to_string((int)npc[0].pl.prz[npc[0].pl.t[i][j]-1].size()),0,0,-5,0,0,0);
                            wypisz("x"+to_string((int)npc[0].pl.prz[npc[0].pl.t[i][j]-1].size()),tmp.x+tmp.w-tmp2.x,tmp.y+tmp.h-tmp2.y,255,255,255,255);
                        }

                    }
                }
            }
        }
        xy rozmiarczcionki=wypisz("damage",0,0,0,0,0,-1);
        double ilebonus=0;
        for (int i=0; i<7;i++){
            int bonus=npc[0].bonus(i);
            ilebonus+=1.0*(bonus!=0);
        }
        int licznik=0;
        for (int i=0; i<7;i++){
            int bonus=npc[0].bonus(i);
            stringstream tmp;
            tmp << bonus;
            if (bonus){
                if (bonus>0){
                    wypisz(bonusystr[i]+": +"+tmp.str()+"%",-((SZER-konpl)/2+konpl),WYS/2+rozmiarczcionki.y*licznik*1.5-ilebonus*0.75*rozmiarczcionki.y,128*(bonus<0),128*(bonus>0),16,255);
                }else{
                    wypisz(bonusystr[i]+": "+tmp.str()+"%",-((SZER-konpl)/2+konpl),WYS/2+rozmiarczcionki.y*licznik*1.5-ilebonus*0.75*rozmiarczcionki.y,128*(bonus<0),128*(bonus>0),16,255);
                }
                licznik++;
            }
        }
        SDL_SetRenderTarget(Rend,NULL);
    }
    SDL_Rect tmp;
    tmp=ekwpole[8];
    tmp.x+=tmp.w+2*kwrozm;
    tmp.y-=kwrozm;
    tmp.h=kwrozm;
    tmp.w=kwrozm;
    if (czyzmianaekw){
        SDL_SetRenderTarget(Rend,ekwtx);
        wypisz("drop slots",-(tmp.x),tmp.y+kwrozm/2,196,196,196,255);
        for (int i=0; i<max((int)bufer.size(),6);i++){
            if (i%2){
                tmp.x+=kwrozm;
            }else{
                tmp.x-=kwrozm;
            }
            if (i%2==0){
                tmp.y+=kwrozm;
            }
            if(i>=bufer.size()){
                SDL_SetTextureAlphaMod(CzKw,128);
            }
            SDL_RenderCopy(Rend, CzKw,NULL,&tmp);
            for (int j=tmp.y;j<tmp.y+tmp.h;j++){
                SDL_SetRenderDrawColor(Rend,255,255,255,(1+(i<bufer.size()))*((64*(j-tmp.y))/tmp.h));
                SDL_RenderDrawLine(Rend,tmp.x,j,tmp.x+tmp.w,j);
            }
            if (i<bufer.size()){
                tmp.h=(kwrozm*(bufer[i].wym/10))/max(bufer[i].wym/10,bufer[i].wym%10);
                tmp.w=(kwrozm*(bufer[i].wym%10))/max(bufer[i].wym/10,bufer[i].wym%10);
                tmp.x+=(kwrozm-tmp.w)/2;
                tmp.y+=(kwrozm-tmp.h)/2;
                SDL_RenderCopy(Rend, txit[bufer[i].typ][bufer[i].tekstura],NULL,&tmp);
                tmp.y-=(kwrozm-tmp.h)/2;
                tmp.x-=(kwrozm-tmp.w)/2;
                tmp.h=kwrozm;
                tmp.w=kwrozm;
            }
            SDL_SetTextureAlphaMod(CzKw,255);
            ekwpole.push_back(tmp);
        }
        czyzmianaekw=0;
        SDL_SetRenderTarget(Rend,NULL);
    }
    SDL_Rect rendekwtxrect={0,0,SZER,WYS};
    SDL_RenderCopy(Rend,ekwtx,NULL,&rendekwtxrect);
    SDL_SetRenderDrawColor(Rend,255,255,0,255);
    if (ekwwybr>0 && ekwwybr<=9){
        SDL_RenderDrawRect(Rend,&ekwpole[ekwwybr-1]);
    }
    if (ekwwybr<0){
        SDL_RenderDrawRect(Rend,&ekwpole2[-ekwwybr-1]);
    }
    if (npc[0].pl.t.size()){
        for (int i=0; i<npc[0].pl.t.size();i++){
            for (int j=0; j<npc[0].pl.t[0].size();j++){
                if (npc[0].pl.t[i][j] && !(i>0 && npc[0].pl.t[i-1][j]==npc[0].pl.t[i][j]) && !(j>0 && npc[0].pl.t[i][j-1]==npc[0].pl.t[i][j])){
                    tmp.x=xpl+j*kwrozm;
                    tmp.y=ypl+i*kwrozm;
                    tmp.h=npc[0].pl.prz[npc[0].pl.t[i][j]-1][0].wym/10*kwrozm;
                    tmp.w=npc[0].pl.prz[npc[0].pl.t[i][j]-1][0].wym%10*kwrozm;
                    if (xm>tmp.x && xm<tmp.x+tmp.w && ym>tmp.y && ym<tmp.y+tmp.h){
                        if (ekwmyszaL==0 && (GetKeyState(VK_LBUTTON) & 0x80)){
                            if (ekwwybr==-(npc[0].pl.t[i][j])){
                                ekwwybr=0;
                            }else if (!ekwwybr){
                                ekwwybr=-(npc[0].pl.t[i][j]);
                            }
                        }
                    }
                }
            }
        }
    }

    SDL_SetRenderDrawColor(Rend,255,255,0,255);
    if (ekwwybr>9){
        SDL_RenderDrawRect(Rend,&ekwpole[ekwwybr-1]);
    }
    SDL_SetRenderDrawColor(Rend,255,0,0,255);
    if ((GetKeyState(VK_RBUTTON) & 0x80)){
        ekwwybr=0;
    }
    for (int i=0; i<9;i++){
        if (xm>ekwpole[i].x && xm<ekwpole[i].x+ekwpole[i].w && ym>ekwpole[i].y && ym<ekwpole[i].y+ekwpole[i].h && ((i==8 && npc[0].pl.t.empty())||i!=8 )){
            if ((ekwmyszaL==0 && (GetKeyState(VK_LBUTTON) & 0x80))) {
                if (ekwwybr==i+1){
                ekwwybr=0;
                }else if (!ekwwybr){
                    ekwwybr=i+1;
                }
            }
            if (ekwwybr!=i+1 && ekwwybr){
                if ((ekwwybr>0 && ekwwybr<=9 && !npc[0].ekw[ekwwybr-1].empty()&& npc[0].dodajdoekw(npc[0].ekw[ekwwybr-1][0],i,0)) ||(ekwwybr<0 && !npc[0].pl.prz[-ekwwybr-1].empty()&& npc[0].dodajdoekw(npc[0].pl.prz[-ekwwybr-1][0],i,0)) || (ekwwybr>9 && npc[0].dodajdoekw(bufer[ekwwybr-10],i,0))){
                    SDL_SetRenderDrawColor(Rend,0,255,0,255);
                    if (( ekwmyszaL==0 && (GetKeyState(VK_LBUTTON) & 0x80))) {
                        if (ekwwybr>0 && ekwwybr<=9){
                            if (npc[0].dodajdoekw(npc[0].ekw[ekwwybr-1][0],i,1)){
                                npc[0].ekw[ekwwybr-1].erase(npc[0].ekw[ekwwybr-1].begin());
                                if (npc[0].ekw[ekwwybr-1].empty()){
                                    ekwwybr=0;
                                }
                                czyzmianaekw=1;
                            }
                        }else if (ekwwybr<0){
                            czyzmianaekw=1;
                            if (npc[0].dodajdoekw(npc[0].pl.prz[-ekwwybr-1][0],i,1)){
                                ekwwybr*=(int)npc[0].usunzpl(-ekwwybr-1,0);
                            }
                        }
                        if (ekwwybr>9){
                            if (npc[0].dodajdoekw(bufer[ekwwybr-10],i,1)){
                                bufer.erase(bufer.begin()+ekwwybr-10);
                                ekwwybr=0;
                            }
                            czyzmianaekw=1;
                        }
                    }
                }else if (ekwwybr<=9){
                    SDL_SetRenderDrawColor(Rend,255,0,0,255);
                    vector <it> tmp=npc[0].ekw[i];
                    npc[0].ekw[i].clear();
                    bool czek=0;
                    int ekwwybrtmp=ekwwybr;
                    if ((ekwwybr>0 && !npc[0].ekw[ekwwybr-1].empty() && npc[0].dodajdoekw(npc[0].ekw[ekwwybr-1][0],i,0)) || (ekwwybr<0 && !npc[0].pl.prz[-ekwwybr-1].empty() && npc[0].dodajdoekw(npc[0].pl.prz[-ekwwybr-1][0],i,0))){
                        SDL_SetRenderDrawColor(Rend,0,255,0,255);
                        if (ekwmyszaL==0 && ((GetKeyState(VK_LBUTTON) & 0x80))){
                            if (ekwwybr>0){
                                if (npc[0].dodajdoekw(npc[0].ekw[ekwwybr-1][0],i,1)){
                                    npc[0].ekw[ekwwybr-1].erase(npc[0].ekw[ekwwybr-1].begin());
                                    if (npc[0].ekw[ekwwybr-1].empty()){
                                        ekwwybr=0;
                                    }
                                    czek=1;
                                    czyzmianaekw=1;
                                }
                            }else{
                                if (npc[0].dodajdoekw(npc[0].pl.prz[-ekwwybr-1][0],i,1)){
                                    czyzmianaekw=1;
                                    czek=1;
                                    npc[0].usunzpl(-ekwwybr-1,0);
                                    ekwwybr=0;
                                }
                            }
                        }
                    }
                    if (!czek){
                        npc[0].ekw[i]=tmp;
                    }else{
                        for (int i=0; i<tmp.size();i++){
                            if (ekwwybrtmp>0){
                                if (npc[0].dodajdoekw(tmp[i],ekwwybrtmp-1,1)){
                                    tmp.erase(tmp.begin());
                                    i--;
                                }
                            }else{
                                if (npc[0].dodajdopl(tmp[i],1)){
                                    tmp.erase(tmp.begin());
                                    i--;
                                }
                            }
                        }
                        for (int i=0; i<tmp.size();i++){
                            bufer.push_back(tmp[i]);
                        }
                    }
                }
                SDL_RenderDrawRect(Rend,&ekwpole[i]);

            }
            multipodn(xm,ym,npc[0].ekw[i]);
        }
        if (ekwwybr!=9 && ekwwybr>0 && i==8 && (xm>ekwpole[i].x && xm<ekwpole[i].x+ekwpole[i].w && ym>ekwpole[i].y && ym<ekwpole[i].y+ekwpole[i].h) && !npc[0].pl.t.empty()){
            if ((ekwwybr<9 && !npc[0].ekw[ekwwybr-1].empty() && npc[0].dodajdopl(npc[0].ekw[ekwwybr-1][0],0)) || (ekwwybr>9 && npc[0].dodajdopl(bufer[ekwwybr-10],0))){
                SDL_SetRenderDrawColor(Rend,0,255,0,255);
            }else{
                SDL_SetRenderDrawColor(Rend,255,0,0,255);
            }
            SDL_RenderDrawRect(Rend,&ekwpole[i]);
            if (ekwwybr<9){
                if (!npc[0].ekw[ekwwybr-1].empty() && (ekwmyszaL==0 && (GetKeyState(VK_LBUTTON) & 0x80))){
                    if (npc[0].dodajdopl(npc[0].ekw[ekwwybr-1][0],1)){
                        npc[0].ekw[ekwwybr-1].erase(npc[0].ekw[ekwwybr-1].begin());
                        if (npc[0].ekw[ekwwybr-1].empty()){
                            ekwwybr=0;
                        }
                        czyzmianaekw=1;
                    }
                }
            }else if ( (ekwmyszaL==0 && (GetKeyState(VK_LBUTTON) & 0x80))){
                if (npc[0].dodajdopl(bufer[ekwwybr-10],1)){
                    czyzmianaekw=1;
                    bufer.erase(bufer.begin()+ekwwybr-10);
                    ekwwybr=0;
                }
            }
        }
    }
    for (int i=0;i<ekwpole2.size();i++){
        if (xm>ekwpole2[i].x && xm<ekwpole2[i].x+ekwpole2[i].w && ym>ekwpole2[i].y && ym<ekwpole2[i].y+ekwpole2[i].h){
            multipodn(xm,ym,npc[0].pl.prz[i]);
        }
    }
    SDL_Rect poletmp=ekwpole[8];
    ekwpole[8].x+=ekwpole[8].w+kwrozm;
    ekwpole[8].w=2*kwrozm;
    ekwpole[8].h=(max(6,(int)bufer.size())+1)/2*kwrozm;
    if (ekwwybr&&ekwwybr<=9 && (xm>ekwpole[8].x && xm<ekwpole[8].x+ekwpole[8].w && ym>ekwpole[8].y && ym<ekwpole[8].y+ekwpole[8].h)){
        SDL_SetRenderDrawColor(Rend,0,255,0,255);
        if ((ekwwybr>0 && npc[0].ekw[ekwwybr-1].empty())){
        SDL_SetRenderDrawColor(Rend,255,0,0,255);
        }
        SDL_RenderDrawRect(Rend,&ekwpole[8]);
        if (( ekwmyszaL==0 && (GetKeyState(VK_LBUTTON) & 0x80))) {
            if (ekwwybr>0 && !npc[0].ekw[ekwwybr-1].empty()){
                czyzmianaekw=1;
                bufer.push_back(npc[0].ekw[ekwwybr-1][0]);
                npc[0].ekw[ekwwybr-1].erase(npc[0].ekw[ekwwybr-1].begin());
                if (npc[0].ekw[ekwwybr-1].empty()){
                    ekwwybr=0;
                }
                ekwmyszaL=1;
            }else if (ekwwybr<0){
                ekwmyszaL=1;
                czyzmianaekw=1;
                bufer.push_back({npc[0].pl.prz[-ekwwybr-1][0]});
                npc[0].pl.prz[-ekwwybr-1].erase(npc[0].pl.prz[-ekwwybr-1].begin());
                if (npc[0].pl.prz[-ekwwybr-1].empty()){
                    npc[0].pl.prz.erase(npc[0].pl.prz.begin()+(-ekwwybr-1));
                    for (int i=0; i<npc[0].pl.t.size();i++){
                        for (int j=0; j<npc[0].pl.t[0].size();j++){
                            if (npc[0].pl.t[i][j]==-ekwwybr){
                                npc[0].pl.t[i][j]=0;
                            }
                        }
                    }
                    for (int i=0; i<npc[0].pl.t.size();i++){
                        for (int j=0; j<npc[0].pl.t[0].size();j++){
                            if (npc[0].pl.t[i][j]>-ekwwybr){
                                npc[0].pl.t[i][j]--;
                            }
                        }
                    }
                    ekwwybr=0;
                }
            }
        }
    }
    for (int i=0; i<bufer.size();i++){
        if(xm>ekwpole[i+9].x && xm<ekwpole[i+9].x+ekwpole[i+9].w && ym>ekwpole[i+9].y && ym<ekwpole[i+9].y+ekwpole[i+9].h){
            if ((ekwmyszaL==0 && (GetKeyState(VK_LBUTTON) & 0x80))){
                if (ekwwybr==i+10){
                    ekwwybr=0;
                }else{
                    ekwwybr=i+10;
                }
            }
            vector <it> tmp;
            tmp.push_back(bufer[i]);
            multipodn(xm,ym,tmp);
        }
    }
    ekwpole[8]=poletmp;
    ekwmyszaP=(GetKeyState(VK_RBUTTON) & 0x80);
    ekwmyszaL=(GetKeyState(VK_LBUTTON) & 0x80);
    SDL_RenderPresent( Rend );

}

