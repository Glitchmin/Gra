#include <SDL.h>
#include <vector>
#include <cstdlib>
#include <time.h>

#include "it.h"
#include "structy.h"
#include "npc.h"

using namespace std;

extern int KRATKA;
extern SDL_Renderer* Rend;
extern vector <int> w[8];
extern vector <vector <SDL_Texture*> > txit;
extern bool czypodn;
extern vector <vector <it> > przedm;
extern SDL_Texture* CzKw;
extern bool mysza1;
extern vector <NPC> npc;
extern vector <xy> pozprzedm;

xy multipodn (int x, int y, vector <it> & itemy);

int gcd(int a, int b) {
    while (b != 0) {
        int c = a % b;
        a = b;
        b = c;
    }
    return a;
}

SDL_Texture* przedmnaekr(vector <it> & vect,int ID){
    int x=0,y=0;
    SDL_Texture* ittx=SDL_CreateTexture(Rend, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,KRATKA, KRATKA);
    SDL_Texture* tmptx;
    SDL_SetTextureBlendMode(ittx,SDL_BLENDMODE_BLEND);
    tmptx=SDL_GetRenderTarget(Rend);
    SDL_SetRenderTarget(Rend,ittx);
    srand(ID);
    SDL_Rect tmp;
    tmp.x=x;
    tmp.y=y;
    tmp.h=KRATKA;
    tmp.w=KRATKA;
    for (int i=0; i<vect.size();i++){
        if (vect[i].typ==3||vect[i].typ==4){
            if (vect[i].t<0 && vect[i].maxt!=-1){
                int tmp=255+((255*vect[i].t)/(w[4][5]));
                SDL_SetTextureAlphaMod(txit[vect[i].typ][vect[i].tekstura],tmp*(tmp>0));
            }
            int a=vect[i].wym/10;
            int b=vect[i].wym%10;
            int c=gcd(a,b);
            a/=c;
            b/=c;
            int tmprozm=KRATKA/(max(a,b));
            tmp.h=a*tmprozm;
            tmp.w=b*tmprozm;
            SDL_RenderCopy(Rend, txit[vect[i].typ][vect[i].tekstura], NULL,&tmp);
            SDL_SetTextureAlphaMod(txit[vect[i].typ][vect[i].tekstura],255);
        }
    }
    for (int i=0; i<vect.size();i++){
        if (vect[i].typ==0 || vect[i].typ==1){
            if (vect[i].t<0 && vect[i].maxt!=-1){
                int tmp=255+((255*vect[i].t)/(w[4][5]));
                SDL_SetTextureAlphaMod(txit[vect[i].typ][vect[i].tekstura],tmp*(tmp>0));
            }
            int a=vect[i].wym/10;
            int b=vect[i].wym%10;
            int c=gcd(a,b);
            a/=c;
            b/=c;
            int tmprozm=KRATKA/(max(a,b));
            tmp.h=a*tmprozm;
            tmp.w=b*tmprozm;
            SDL_RenderCopy(Rend, txit[vect[i].typ][vect[i].tekstura], NULL,&tmp);
            SDL_SetTextureAlphaMod(txit[vect[i].typ][vect[i].tekstura],255);
        }
    }
    tmp.h=KRATKA/3;
    tmp.w=KRATKA/3;
    for (int i=0; i<vect.size();i++){
        if (vect[i].typ==5){
            SDL_Rect tmp2;
            tmp2=tmp;
            tmp2.x+=(KRATKA/3)*(rand()%3);
            tmp2.y+=(KRATKA/3)*(rand()%3);
            if (vect[i].t<0 && vect[i].maxt!=-1){
                int tmp=255+((255*vect[i].t)/(w[4][5]));
                SDL_SetTextureAlphaMod(txit[vect[i].typ][vect[i].tekstura],tmp*(tmp>0));
            }
            int a=vect[i].wym/10;
            int b=vect[i].wym%10;
            int c=gcd(a,b);
            a/=c;
            b/=c;
            int tmprozm=KRATKA/(3*(max(a,b)));
            tmp.h=a*tmprozm;
            tmp.w=b*tmprozm;
            SDL_RenderCopy(Rend, txit[vect[i].typ][vect[i].tekstura], NULL,&tmp2);
            SDL_SetTextureAlphaMod(txit[vect[i].typ][vect[i].tekstura],255);
        }
    }
    tmp.h=2*KRATKA/3;
    tmp.w=KRATKA/3;
    for (int i=0; i<vect.size();i++){
        if (vect[i].typ==2){
            if (vect[i].t<0 && vect[i].maxt!=-1){
                int tmp=255+((255*vect[i].t)/(w[4][5]));
                SDL_SetTextureAlphaMod(txit[vect[i].typ][vect[i].tekstura],tmp*(tmp>0));
            }
            int a=vect[i].wym/10;
            int b=vect[i].wym%10;
            int c=gcd(a,b);
            a/=c;
            b/=c;
            int tmprozm=KRATKA/(max(a,b));
            tmp.h=a*tmprozm;
            tmp.w=b*tmprozm;
            SDL_RenderCopy(Rend, txit[vect[i].typ][vect[i].tekstura], NULL,&tmp);
            SDL_SetTextureAlphaMod(txit[vect[i].typ][vect[i].tekstura],255);
        }
    }
    srand(time(NULL)+SDL_GetTicks()%683);
    SDL_SetRenderTarget(Rend,tmptx);
    return ittx;
}


void podn(int npcID, int przedmID, xy pozpodno){
    //cout << czypodn;
    int jedn=KRATKA;
    int szer=0;
    int wys=0;
    if (npcID==0){
        int rozm=0;
        int rozm2=0;
        for (int i=0; i<przedm[przedmID].size();i++){
            if (przedm[przedmID][i].typ!=2){
                rozm++;

            }else if (przedm[przedmID][i].t>0 || przedm[przedmID][i].maxt==-1){
                rozm2++;
            }
        }
        //cout << rozm<< " "<<rozm2<<endl;
        while (szer/jedn*wys/jedn<(rozm+3)/4 + (rozm2+3)/4){
            if (wys==szer){
                szer+=jedn;
            }else{
                wys+=jedn;
            }
        }
        SDL_Rect tmp;
        tmp.x=pozpodno.x;
        tmp.y=pozpodno.y;
        tmp.w=szer;
        tmp.h=wys;
        SDL_SetTextureAlphaMod(CzKw,255);
        SDL_RenderCopy(Rend,CzKw,NULL,&tmp);
        tmp.w=jedn/2;
        tmp.h=jedn/2;
        int xm,ym;
        if (czypodn){
            SDL_GetMouseState(&xm,&ym);
        }
        int ile=szer/tmp.w;
        int licznik=0;
        int dopodnxm=-1;
        int dopodnym;
        int dopodnprzedmID;
        int dopodni;
        for (int i=0; i<przedm[przedmID].size();i++){
            if (przedm[przedmID][i].typ!=2){

                tmp.x=pozpodno.x+(licznik%ile)*tmp.w;
                tmp.y=pozpodno.y+(licznik/ile)*tmp.h;
                SDL_RenderCopy(Rend,txit[przedm[przedmID][i].typ][przedm[przedmID][i].tekstura],NULL,&tmp);
                licznik++;
                if (czypodn && xm>=tmp.x && xm<tmp.x+tmp.w && ym>=tmp.y && ym <tmp.y+tmp.h){
                    dopodnxm=xm;
                    dopodnym=ym;
                    dopodnprzedmID=przedmID;
                    dopodni=i;
                }
            }
        }
        for (int i=0; i<przedm[przedmID].size();i++){
            if (przedm[przedmID][i].typ==2){
                tmp.x=pozpodno.x+(licznik%ile)*tmp.w;
                tmp.y=pozpodno.y+(licznik/ile)*tmp.h;
                SDL_RenderCopy(Rend,txit[przedm[przedmID][i].typ][przedm[przedmID][i].tekstura],NULL,&tmp);
                licznik++;
                if (czypodn && xm>=tmp.x && xm<tmp.x+tmp.w && ym>=tmp.y && ym <tmp.y+tmp.h){
                    dopodnxm=xm;
                    dopodnym=ym;
                    dopodnprzedmID=przedmID;
                    dopodni=i;
                }
            }
        }
        if (dopodnxm!=-1){
            vector <it> tmp;
            tmp.push_back(przedm[dopodnprzedmID][dopodni]);
            multipodn(dopodnxm,dopodnym,tmp);
            if (!mysza1 && GetKeyState(VK_LBUTTON) & 0x80 ){
                int k=8;
                bool czek=npc[0].dodajdopl(przedm[dopodnprzedmID][dopodni],1);
                while (!czek && k>=0){
                    czek=npc[0].dodajdoekw(przedm[dopodnprzedmID][dopodni],k,1);
                    k--;
                }
                if (czek){
                    przedm[dopodnprzedmID].erase(przedm[dopodnprzedmID].begin()+dopodni);
                    czypodn=0;
                }
            }
        }
        mysza1=GetKeyState(VK_LBUTTON) & 0x80;
        if (abs(npc[0].x - pozprzedm[przedmID].x)<2 && abs(npc[0].y-pozprzedm[przedmID].y)<2 && !((abs(npc[0].x-pozprzedm[przedmID].x)) && abs(npc[0].y-pozprzedm[przedmID].y))){
            int xm,ym;
            SDL_GetMouseState(&xm,&ym);
            if (xm>=pozpodno.x-jedn && xm<=pozpodno.x+szer && ym>=pozpodno.y-jedn && ym <=pozpodno.y+wys){
                czypodn=1;
            }else{
                czypodn=0;
            }
        }else{
            czypodn=0;
        }
    }
}
