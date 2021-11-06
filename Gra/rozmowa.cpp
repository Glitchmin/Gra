#include <SDL.h>
#include <vector>
#include "npc.h"

using namespace std;

extern bool mysza2;
extern int maxi;
extern int wysrozm;
extern bool czyzmianarozm;
extern bool czyzmianarozm2;
extern SDL_Texture* txrozm;
extern Uint32 trozm;
extern Uint32 trozm2;
extern vector <pair <int, SDL_Rect> > rozmrozm;
extern vector <pair<SDL_Rect,int> > rozmrozm2;
extern bool czek;
extern int wyspask;
extern vector <NPC> npc;
extern vector <pair<string,bool> > rozmef;
extern vector <it> bufer;
extern bool sklmyszaL;
extern int czysklep;
extern int WYS;
extern int SZER;
extern SDL_Renderer* Rend;
extern SDL_Texture* CzKw;
extern int rozmtmp;
extern vector <vector <SDL_Texture*> > txit;

xy wypisz (string txt, int x, int y, int r, int g, int b, int a);
xy multipodn (int x, int y, vector <it> & itemy);

bool wymog(int n2, vector <pair <int, double> > wymief, bool czyodw){
bool wynik=1;
for (int i=0; i<wymief.size();i++){
int wymtyp=wymief[i].first;
double wym=wymief[i].second;
bool czek=wymtyp<=0;
    if (wymtyp==1){
        czek=!czyodw;
    }
    if (wymtyp==2){
        if (!npc[0].ekw[0].empty()){
            czek= (npc[0].ekw[0][0].typ==0 && npc[0].ekw[0][0].dou[0]>=wym);
        }
    }
    wynik*=czek;
}
return wynik;
}

SDL_Rect stworzSDL_Rect (int x, int y, int w, int h) {
    SDL_Rect tmp = { x,y,w,h };
    return tmp;
}

void efekty (int n2, vector <pair <int, double> > & wymief, vector <it> & itemy){
    if (!itemy.empty()){
        rozmef.push_back(make_pair("",1));
    }
    for (int i=0; i<itemy.size();i++){
        bool czek=npc[0].dodajdopl(itemy[i],1);
        if (!czek){
            for (int k=0;k<8;k++){
                czek=npc[0].dodajdoekw(itemy[i],k,1);
                if (czek){
                    break;
               }
            }
        }
        if (!czek){
            bufer.push_back(itemy[i]);
        }
    }
    for (int i=0; i<wymief.size();i++){
        int eftyp=wymief[i].first;
        double efe=wymief[i].second;
        if (eftyp==-1){
            sklmyszaL=1;
            czysklep=n2;
        }
        if (eftyp==-2){
            rozmef.push_back(make_pair("selling prices have improved, yay!",1));
        }
    }
}

bool rozmowaNPC (int n2,int v){
    if (!npc[n2].n){
        return 0;
    }
    wyspask=WYS/15;
    int xm,ym;
    SDL_GetMouseState(&xm,&ym);
    if (czyzmianarozm){
        czek=1;
        rozmrozm.clear();
        SDL_SetRenderTarget(Rend,txrozm);
        SDL_Rect tmp;
        npc[n2].e[v]=1;
        tmp.y=3*WYS/4;
        /*if (maxi+tmp.y>WYS){
            tmp.y=WYS-maxi;
        }*/
        wysrozm=tmp.y;
        tmp.x=0;
        int x=0;
        int y=tmp.y;
        tmp.h=2*WYS-tmp.y;
        tmp.w=SZER;
        //cout << v;
        int wys=0;
        int odstep=WYS/100;
        if (rozmef.empty()&&npc[n2].wierz[v].czyj && ((!npc[n2].g[v].empty() && !npc[n2].wierz[npc[n2].g[v][0]].czyj)||npc[n2].g[v].empty())){
            czek=0;
            SDL_SetRenderDrawColor(Rend,0,0,0,0);
            SDL_RenderClear(Rend);
            SDL_SetTextureAlphaMod(CzKw,128);
            SDL_RenderCopy(Rend,CzKw,NULL,&tmp);
            for (int i=0; i<tmp.w;i++){
                SDL_SetRenderDrawColor(Rend,255,255,255,(128*i)/tmp.w);
                SDL_RenderDrawLine(Rend,i,3*WYS/4,i,2*WYS);
            }
            xy tmp2 = wypisz(npc[n2].wierz[v].tekst,x+SZER/20,y+wyspask,-255,255,255,255);
            maxi=max(tmp2.y+2*odstep,maxi);
            wys+=(tmp2.y-(y+wyspask))+2*odstep;
            for (int i=0; i<npc[n2].g[v].size();i++){
                if (wymog(n2, npc[n2].wierz[npc[n2].g[v][i]].wymief,npc[n2].e[npc[n2].g[v][i]])){
                    czek=1;
                    if (!npc[n2].e[npc[n2].g[v][i]]){
                        tmp2=wypisz(npc[n2].wierz[npc[n2].g[v][i]].tekst,x+SZER/20,y+wyspask+wys,-255,255,255,255);
                        rozmrozm.push_back(make_pair(npc[n2].g[v][i], stworzSDL_Rect(0,y+wyspask+wys,SZER,tmp2.y-(y+wyspask+wys))));
                        maxi=max(maxi,tmp2.y+2*odstep);
                    }else{
                        tmp2=wypisz(npc[n2].wierz[npc[n2].g[v][i]].tekst,x+SZER/20,y+wyspask+wys,-196,196,196,255);
                        rozmrozm.push_back(make_pair(npc[n2].g[v][i], stworzSDL_Rect(0,y+wyspask+wys,SZER,tmp2.y-(y+wyspask+wys))));
                        maxi=max(maxi,tmp2.y+2*odstep);
                    }
                }
                int tmp3=tmp2.y-(y+wyspask+wys);
                wys+=tmp3+odstep;
            }
            czyzmianarozm=0;
        }else{
            if ((!npc[n2].wierz[v].tekst.empty() && npc[n2].wierz[v].czyj) && rozmef.empty()){
                czek=1;
                if (czyzmianarozm2){
                    SDL_SetRenderDrawColor(Rend,0,0,0,0);
                    SDL_RenderClear(Rend);
                    SDL_SetTextureAlphaMod(CzKw,128);
                    SDL_RenderCopy(Rend,CzKw,NULL,&tmp);
                    for (int i=0; i<tmp.w;i++){
                        SDL_SetRenderDrawColor(Rend,255,255,255,(128*i)/tmp.w);
                        SDL_RenderDrawLine(Rend,i,3*WYS/4,i,2*WYS);
                    }
                    xy tmp2 = wypisz(npc[n2].wierz[v].tekst,x+SZER/20,y+wyspask,-255,255,255,255);
                    maxi=max(tmp2.y+2*odstep,maxi);
                    czyzmianarozm2=0;
                    wys+=(tmp2.y-(y+wyspask))+2*odstep;
                }
                //czyzmianarozm=0;
            }
            if (!rozmef.empty()&&czyzmianarozm2){
                SDL_SetRenderDrawColor(Rend,0,0,0,0);
                SDL_RenderClear(Rend);
                SDL_SetTextureAlphaMod(CzKw,128);
                SDL_RenderCopy(Rend,CzKw,NULL,&tmp);
                for (int i=0; i<tmp.w;i++){
                    SDL_SetRenderDrawColor(Rend,255,255,255,(128*i)/tmp.w);
                    SDL_RenderDrawLine(Rend,i,3*WYS/4,i,2*WYS);
                }
                xy tmp2;
                if (rozmef[0].first.size()){
                    tmp2=wypisz(rozmef[0].first,x+SZER/20,y+wyspask,-200*(!rozmef[0].second)-1,200*rozmef[0].second,0,255);
                    maxi=max(tmp2.y+2*odstep,maxi);
                }else{
                    tmp2=wypisz("I give you these items:",x+SZER/20,y+wyspask,-1,200,0,255);
                    int kwrozm=WYS/15;
                    int pozx=kwrozm;
                    int pozy=tmp2.y+2*odstep-kwrozm;
                    for (int i=0; i<npc[n2].wierz[v].itemydodania.size();i++){
                        if (i%(SZER/kwrozm-2)){
                            pozx+=kwrozm;
                        }else{
                            pozx=kwrozm;
                            pozy+=kwrozm;
                        }
                        SDL_Rect tmp ={pozx,pozy,kwrozm,kwrozm};
                        SDL_RenderCopy(Rend,txit[npc[n2].wierz[v].itemydodania[i].typ][npc[n2].wierz[v].itemydodania[i].tekstura],NULL,&tmp);
                        rozmrozm2.push_back(make_pair(tmp,v));
                    }
                    maxi=max(maxi,pozy+kwrozm+2*odstep);
                }
                czyzmianarozm2=0;
            }
            if ((((!mysza2 && GetKeyState(VK_LBUTTON) & 0x80) || npc[n2].wierz[v].tekst.empty())||!npc[n2].wierz[v].czyj) && rozmef.empty()){
                czyzmianarozm2=1;
                for (int i=0; i<npc[n2].g[v].size();i++){
                    //cout <<"TUTAJ:"<< i<<" "<<n2<<" "<<wymog(n2,  npc[n2].wierz[npc[n2].g[v][i]].wymief,npc[n2].e[npc[n2].g[v][i]])<<" "<<npc[n2].e[npc[n2].g[v][i]]<<" "<<npc[n2].wierz[npc[n2].g[v][i]].wymief.size()<<endl;
                    if (wymog(n2,  npc[n2].wierz[npc[n2].g[v][i]].wymief,npc[n2].e[npc[n2].g[v][i]])){
                        //cout <<"UDANE:"<< i<<" "<<n2<<" "<<wymog(n2,  npc[n2].wierz[npc[n2].g[v][i]].wymief,npc[n2].e[npc[n2].g[v][i]])<<endl;
                        efekty(n2,npc[n2].wierz[npc[n2].g[v][i]].wymief,  npc[n2].wierz[npc[n2].g[v][i]].itemydodania);
                        rozmtmp=npc[n2].g[v][i];
                        break;
                    }
                }
                mysza2=1;
            }
            if ((!mysza2 && GetKeyState(VK_LBUTTON) & 0x80)&&!rozmef.empty()){
                rozmef.erase(rozmef.begin());
                rozmrozm2.clear();
                czyzmianarozm2=1;
            }
        }
        //maxi-=tmp.y;
        //maxi+=2*odstep;
        SDL_SetRenderTarget(Rend,NULL);
    }

    SDL_Rect tmp={0,WYS-maxi-wyspask,SZER,2*WYS};
    if (!czysklep){
        SDL_RenderCopy(Rend,txrozm,NULL, &tmp);
        for (int i=0; i<rozmrozm.size();i++){
            if (ym>=rozmrozm[i].second.y+WYS-maxi-wyspask && ym<=rozmrozm[i].second.y+rozmrozm[i].second.h+WYS-maxi-wyspask){
                SDL_SetRenderDrawColor(Rend,150,75,0,255);
                rozmrozm[i].second.y+=WYS-maxi-wyspask;
                SDL_RenderDrawRect(Rend, &rozmrozm[i].second);
                if (!mysza2&& GetKeyState(VK_LBUTTON) & 0x80){
                    efekty(n2,npc[n2].wierz[rozmrozm[i].first].wymief,  npc[n2].wierz[rozmrozm[i].first].itemydodania);
                    rozmtmp=rozmrozm[i].first;
                    czyzmianarozm=1;
                }
                rozmrozm[i].second.y-=WYS-maxi-wyspask;
            }
        }
    }
    if (trozm>trozm2){
        tmp={0,0,SZER,(int)min((Uint32)wyspask,(Uint32)((wyspask*(SDL_GetTicks()-trozm))/500))};
        SDL_RenderCopy(Rend,CzKw,NULL,&tmp);
        tmp={0,(int)((Uint32)WYS-min((Uint32)wyspask,(wyspask*(SDL_GetTicks()-trozm))/500)),SZER,wyspask};
        SDL_RenderCopy(Rend,CzKw,NULL,&tmp);
    }else{
        tmp={0,0,SZER,(int)max((Uint32)0,wyspask-(wyspask*(SDL_GetTicks()-trozm2))/500)};
        SDL_RenderCopy(Rend,CzKw,NULL,&tmp);
        tmp={0,(int)((Uint32)WYS-max((Uint32)0,wyspask-(wyspask*(SDL_GetTicks()-trozm2))/500)),SZER,wyspask};
        SDL_RenderCopy(Rend,CzKw,NULL,&tmp);
    }
    if (!czysklep){
        for (int i=0;i<rozmrozm2.size();i++){
            if (xm>=rozmrozm2[i].first.x && xm<=rozmrozm2[i].first.x+rozmrozm2[i].first.w && ym>=rozmrozm2[i].first.y+WYS-maxi-wyspask && ym<=rozmrozm2[i].first.y+rozmrozm2[i].first.h+WYS-maxi-wyspask){
                vector <it> tmp;
                tmp.push_back(npc[n2].wierz[rozmrozm2[i].second].itemydodania[i]);
                multipodn(xm,ym,tmp);
            }
        }
    }
    mysza2=GetKeyState(VK_LBUTTON) & 0x80;
    return czek;
}
