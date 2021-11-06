#include "npc.h"

#define endl " >"<<__FUNCTION__<<"<"<<endl

using namespace std;

extern int KRATKA;
extern vector <vector <SDL_Texture*> > txanim;
extern vector <vector <SDL_Texture*> > txit;
extern SDL_Renderer* Rend;
extern vector <vector <SDL_Texture*> > txnpc;

void NPC::rend_atak(bool czyprzod){
    if ((SDL_GetTicks()-tatak<tmaxatak || czy_anim_ataku)){
        SDL_Point tmppkt={0.5*KRATKA,0.9*KRATKA};
        SDL_Rect tmp;
        double kat=0;
        if (SDL_GetTicks()-tatak<tmaxatak2){
            kat=(120*(SDL_GetTicks()-tatak))/tmaxatak2;
        }else{
            kat=(120*(SDL_GetTicks()-tatak-tmaxatak2))/(tmaxatak-tmaxatak2);
            kat=120-kat;
        }
        if (kierataku==2 && !czyprzod){
            return;
        }
        if (kierataku!=2 && czyprzod){
            return;
        }
        if (kierataku==1){
            tmp={(int)1.3*KRATKA,2*KRATKA,KRATKA,KRATKA};
        }
        if (kierataku==3 || kierataku==-1){
            tmp={(int)0.7*KRATKA,2*KRATKA,KRATKA,KRATKA};
            kat*=(-1);
            kat+=360;
        }
        if (kierataku==0){
            tmp={(int)1.3*KRATKA,(int)2.1*KRATKA,KRATKA,KRATKA};
            tmppkt={(int)0.5*KRATKA,(int)0.9*KRATKA};
            kat+=300;
        }
        if (kierataku==2){
            tmp={(int)0.7*KRATKA,(int)2.1*KRATKA,KRATKA,KRATKA};
            kat+=300;
        }
        if (!ekw[0].empty() && ekw[0][0].typ==0){
            SDL_RenderCopyEx(Rend,txit[ekw[0][0].typ][ekw[0][0].tekstura],NULL,&tmp,kat,&tmppkt,SDL_FLIP_NONE);
        }else{
            SDL_RenderCopyEx(Rend,txanim[3][0],NULL,&tmp,kat,&tmppkt,SDL_FLIP_NONE);
        }
    }
}

void NPC::updatetx(){
    if (!czy_dlugi()){
        //cout << czy_anim_ataku<<endl;
    }
    if (tekstura==NULL){
        tekstura=SDL_CreateTexture(Rend, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,4*KRATKA, 5*KRATKA);
        SDL_SetTextureBlendMode(tekstura,SDL_BLENDMODE_BLEND);
    }
    SDL_Texture* cel=SDL_GetRenderTarget(Rend);
    SDL_SetRenderTarget(Rend,tekstura);
    SDL_SetRenderDrawColor(Rend,0,0,0,0);
    SDL_RenderClear(Rend);
    SDL_SetRenderDrawColor(Rend,255,0,0,255);
    SDL_Rect hitboxtmp={(zwr_hitbox().x_lewy+1)*KRATKA,(zwr_hitbox().y_gora+1)*KRATKA,(zwr_hitbox().x_prawy-zwr_hitbox().x_lewy)*KRATKA,(zwr_hitbox().y_dol-zwr_hitbox().y_gora)*KRATKA};
    SDL_RenderDrawRect(Rend,&hitboxtmp);
    if (czystun){
        SDL_Rect tmp = {KRATKA,1.5*KRATKA,KRATKA,KRATKA};
        SDL_RenderCopy(Rend, txanim[6][0],NULL,&tmp);
    }
    SDL_Rect tmp={KRATKA,3*KRATKA,KRATKA,KRATKA};
    SDL_Point tmppkt={KRATKA/2,KRATKA/2};
    rend_atak(0);
    if (kierataku!=-1){
        SDL_RenderCopyEx(Rend,txanim[2][0],NULL,&tmp,kierataku*90+270,&tmppkt,SDL_FLIP_NONE);
    }
    int kierunek=kier();
    tmp={KRATKA,KRATKA,2*KRATKA,3*KRATKA};
    SDL_RenderCopy(Rend,txnpc[nrtekstury][(kierunek)%4],NULL,&tmp);
    /*if (nrubr!=-1){
        SDL_SetTextureColorMod(txubr[nrubr],150,75,0);
        SDL_RenderCopy(Rend,txubr[nrubr],NULL,&tmp);
    }
    if (nrtekstury==0){
        SDL_SetTextureColorMod(txwlosy[0],236,213,167);
        SDL_RenderCopy(Rend,txwlosy[0],NULL,&tmp);
        SDL_SetTextureColorMod(txoczy[0],0,127,255);
        if ((SDL_GetTicks()-tatak<tmaxatak || czy_anim_ataku) && czyatciezki){
            SDL_SetTextureColorMod(txoczy[0],200,0,0);
        }
        SDL_RenderCopy(Rend,txoczy[0],NULL,&tmp);
    }*/
    tmp={KRATKA,2*KRATKA,KRATKA,KRATKA};
    if (poziomblok!=0 && tmaxblok!=0){
        if (!ekw[1].empty()){
            SDL_SetTextureAlphaMod(txit[ekw[1][0].typ][ekw[1][0].tekstura],max(0,min((255*poziomblok)/tmaxblok,255)));
            SDL_RenderCopy(Rend,txit[ekw[1][0].typ][ekw[1][0].tekstura],NULL,&tmp);
            SDL_SetTextureAlphaMod(txit[ekw[1][0].typ][ekw[1][0].tekstura],255);
        }else{
            SDL_SetTextureAlphaMod(txanim[4][0],max(0,min((255*poziomblok)/tmaxblok,255)));
            SDL_RenderCopy(Rend,txanim[4][0],NULL,&tmp);
        }
    }
    if (czyparada){
        int a;
        if (SDL_GetTicks()-tparada<=czasparady()/2){
            a=(512*(SDL_GetTicks()-tparada))/czasparady();
        }else{
            a=255-(512*(SDL_GetTicks()-tparada-czasparady()/2))/czasparady();
        }
        a=max(128,a);
        SDL_SetTextureAlphaMod(txanim[5][0],a);
        SDL_RenderCopy(Rend,txanim[5][0],NULL,&tmp);
    }
    tmp={KRATKA,KRATKA,2*KRATKA,3*KRATKA};
    rend_atak(1);
    SDL_SetRenderTarget(Rend,cel);
}
