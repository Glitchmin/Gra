#include "npc.h"


extern SDL_Renderer* Rend;
extern int KRATKA;
using namespace std;

NPC::NPC(int x, int y, int maxx, int minx, int maxy, int miny,int ruch1, int ruch2,int nrtekstury,int nrubr, int hp, int ileprz, vector <int> prz,vector <vector <it> >ekw, plecak pl,int rozmjedz,int strona, int zasieg, int sila, int predkat,double h){
        this->x=x; this->y=y; this->maxx=maxx; this->minx=minx; this->maxy=maxy; this->miny=miny; this->ruch1=ruch1;this->ruch2=ruch2; this->popkier=0;
        this->nrtekstury=nrtekstury;
        this->popx=x; this->popy=y;
        this->hp=hp;this->ileprz=ileprz;this->prz=prz; this->ekw=ekw;
        this->pl=pl; this->rozmjedz=rozmjedz;this->strona=strona;this->zasieg=zasieg;this->sila=sila;this->predkat=predkat;
        this->h=h;
        this->rozmo=0;
        this->tmaxruch=0;
        this->tmaxatak=0;
        this->n=0;
        this->czymartwy=0;
        this->nrubr=nrubr;
        this->poziomblok=0;
        this->kierataku=-1;
        this->czyatak=0;
        this->czy_anim_ataku=0;
        this->czyatciezki=0;
        this->tdodge=0;
        this->czydodge=0;
        this->czyparada=0;
        this->ekw.resize(9);
        this->wspcoile=0;
        this->wspnaile=0;
        this->wspnaile=0;
        this->tekstura=SDL_CreateTexture(Rend, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,4*KRATKA, 5*KRATKA);
        this-> poziomblok=0;
        this-> czystun=0;
        this->czyprzerwany_atak=0;
        SDL_SetTextureBlendMode(this->tekstura,SDL_BLENDMODE_BLEND);
    }

NPC::NPC(){
        this->popkier=0;
        this->rozmo=0;
        this->tmaxruch=0;
        this->tmaxatak=0;
        this->n=0;
        this->czymartwy=0;
        this->nrubr=-1;
        this->sila=0;
        this->poziomblok=0;
        this->kierataku=-1;
        this->czyatak=0;
        this->czy_anim_ataku=0;
        this->czyatciezki=0;
        this->popx=0;
        this->popy=0;
        this->tdodge=0;
        this->czydodge=0;
        this->czyparada=0;
        this->ekw.resize(9);
        this->wspcoile=0;
        this->wspnaile=0;
        this->wspnaile=0;
        this-> czystun=0;
        this->czyprzerwany_atak=0;
        this->tekstura=SDL_CreateTexture(Rend, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,4*KRATKA, 5*KRATKA);
        SDL_SetTextureBlendMode(this->tekstura,SDL_BLENDMODE_BLEND);
    }
