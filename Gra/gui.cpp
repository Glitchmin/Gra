#include <SDL.h>
#include <vector>
#include "npc.h"

using namespace std;

extern int ZASx;
extern int ZASy;
extern SDL_Renderer* Rend;
extern int KRATKA;
extern vector <NPC> npc;
extern SDL_Texture* CzKw;

void popraw(){
    SDL_Rect poz;
    SDL_SetTextureAlphaMod(CzKw,255);
    poz.x=2*ZASx+1;
    poz.x*=KRATKA;
    poz.h=KRATKA;
    poz.w=KRATKA;
    for (int i=0; i<2*ZASy+1;i++){
        poz.y=i*KRATKA;
        SDL_RenderCopy(Rend, CzKw,NULL,&poz);
        poz.x=(2*ZASx+2)*KRATKA;
        SDL_RenderCopy(Rend, CzKw,NULL,&poz);
        poz.x-=KRATKA;
    }
    poz.y=2*ZASy*KRATKA+KRATKA;
    for (int i=0; i<=2*ZASx+2;i++){
        poz.x=i*KRATKA;
        SDL_RenderCopy(Rend, CzKw,NULL,&poz);
        poz.y+=KRATKA;
        SDL_RenderCopy(Rend, CzKw,NULL,&poz);
        poz.y-=KRATKA;
    }
}

void wartosci(){
int x=(2*ZASx-1)*KRATKA,y=(2*ZASy)*KRATKA+((3*KRATKA)/4);
int grubosc=3;
int wysokosc=3;
SDL_SetRenderDrawColor(Rend,175,0,0,255);
SDL_SetRenderDrawBlendMode(Rend,SDL_BLENDMODE_BLEND);
int suma = 0;
for (int i=0; i<npc[0].ileprz+1-1;i++){
    suma+=npc[0].prz[i];
}
int tmp=0;
for (int i=npc[0].ileprz+1-2; i>=0;i--){
        if (npc[0].hp>=tmp){
            SDL_SetRenderDrawColor(Rend,175,0,0,255);
        }else{
            SDL_SetRenderDrawColor(Rend,0,0,0,255);
        }
        SDL_RenderDrawLine(Rend,x+((KRATKA*(suma-tmp))/suma),y-wysokosc,x+((KRATKA*(suma-tmp))/suma),y+grubosc+wysokosc-1);
    if (npc[0].hp>=tmp+npc[0].prz[i]){
        for (int j=0; j<grubosc;j++){
            SDL_RenderDrawLine(Rend,x+((KRATKA*(suma-tmp)))/suma,y+j,x+((suma-(tmp+npc[0].prz[i]))*KRATKA)/suma,y+j);
        }
    }else{
        if (npc[0].hp>=tmp){
            for (int j=0; j<grubosc;j++){
                SDL_SetRenderDrawColor(Rend,0,0,0,255);
                SDL_RenderDrawLine(Rend,x+((suma-(tmp+npc[0].prz[i]))*KRATKA)/suma,y+j,x+((suma-(npc[0].hp))*KRATKA)/suma,y+j);
                SDL_SetRenderDrawColor(Rend,175,0,0,255);
                SDL_RenderDrawLine(Rend,x+((suma-npc[0].hp)*KRATKA)/suma,y+j,x+((KRATKA*(suma-tmp)))/suma,y+j);
            }
        }else{
            SDL_SetRenderDrawColor(Rend,0,0,0,255);
            for (int j=0; j<grubosc;j++){
                SDL_RenderDrawLine(Rend,x+((KRATKA*(suma-tmp)))/suma,y+j,x+((suma-(tmp+npc[0].prz[i]))*KRATKA)/suma,y+j);
            }
        }
    }
    tmp+=npc[0].prz[i];
    if (tmp==suma){
        if (npc[0].hp==suma){
            SDL_SetRenderDrawColor(Rend,175,0,0,255);
        }else{
            SDL_SetRenderDrawColor(Rend,0,0,0,255);
        }
        SDL_RenderDrawLine(Rend,x+((KRATKA*(suma-tmp))/suma),y-wysokosc,x+((KRATKA*(suma-tmp))/suma),y+grubosc+wysokosc-1);
    }

}

}

void mapa(vector<vector <int> > m1[]){
    cout << "mapa nie zrobiona";
}
