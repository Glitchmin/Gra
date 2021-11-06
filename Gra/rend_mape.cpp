#include <vector>
#include <map>

#include "poci.h"
#include "npc.h"

using namespace std;

#define DEBUG if (0)
#define endl " >"<<__FUNCTION__<<"<"<<endl

extern int KRATKA;
extern int ZASx;
extern int ZASy;
extern vector <vector <SDL_Texture*> > txit;
extern SDL_Renderer* Rend;
extern SDL_Texture* txmiasto;
extern SDL_Texture* txmiasto0;
extern bool czyzmianamiasto0;
extern xy pozgr;
extern SDL_Texture* CzKw;
extern vector <NPC> npc;
extern vector <vector <SDL_Texture*> > txanim;
extern vector <poci> pociski;
extern vector <tuple <xyd, double,double,double, it> > pociskiwbite;
extern vector <vector <it> > przedm;
extern map<pair<int,int>, pair<int,bool> > przezr;

map<int,bool> renderowani;
map<int,bool> napisani;

SDL_Texture* zwroctxtr(long long x, long long y, int txnumer);
SDL_Texture* zwroctxbg(long long x, long long y, int txnumer);
SDL_Texture* zwroctxw(long long x, long long y, int txnumer);
SDL_Texture* zwroctxfw(long long x, long long y, int txnumer);
SDL_Texture* przedmnaekr(vector <it> & vect,int ID);
xy wypisz (string txt, int x, int y, int r, int g, int b, int a);

double obliczhtx (SDL_Texture* tx);
double obliczhtxszerokie (SDL_Texture* tx);

bool cmppoci (poci &a, poci &b){
    return a.poz.y<b.poz.y;
}
bool cmppociwbite (tuple <xyd, double,double,double, it> &a, tuple <xyd, double,double,double, it> &b){
    return (get <0> (a)).y < (get <0> (b)).y;
}
bool cmpnpc (tuple<double,double,SDL_Rect,SDL_Texture*> &a, tuple<double,double,SDL_Rect,SDL_Texture*> &b){
    return get <1> (a) < get <1> (b);
}

void rendpoci(xyd tmp,double h, it strzala, double kat, double kat2,int x,int y, bool czywbita){
    SDL_Texture* target;
    target = SDL_GetRenderTarget(Rend);
    SDL_Rect poz;
    SDL_Rect pozz2;
    SDL_Texture* tx=SDL_CreateTexture(Rend, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,KRATKA, KRATKA);
    SDL_SetRenderTarget(Rend,tx);
    SDL_SetRenderDrawColor(Rend,0,0,0,0);
    SDL_SetTextureBlendMode(tx,SDL_BLENDMODE_BLEND);
    SDL_RenderClear(Rend);
    SDL_Rect recttx={0,0.25*KRATKA,KRATKA,3*KRATKA/4};
    if (czywbita){
        recttx.y=0.5*KRATKA;
        recttx.h=0.5*KRATKA;
        Uint32 f; int acc, w, htx;
        SDL_QueryTexture(txit[2][strzala.tekstura], &f, &acc, &w, &htx);
        SDL_Rect srcrecttx = {0,htx/3,w,2*htx/3};
        SDL_RenderCopy(Rend,txit[2][strzala.tekstura],&srcrecttx,&recttx);
    }else{
        SDL_RenderCopy(Rend,txit[2][strzala.tekstura],NULL,&recttx);
    }
    SDL_SetRenderTarget(Rend,target);

    poz.x=(double)KRATKA*tmp.x+((-x+1.0)*KRATKA)-KRATKA/2;
    poz.y=(double)KRATKA*(tmp.y-h)+((-y+1.0)*KRATKA)-KRATKA/2;

    if (poz.x>-KRATKA && poz.x < (2*ZASx+4)*KRATKA && poz.y>-KRATKA && poz.y < (2*ZASy+4)*KRATKA){
        poz.h=KRATKA;
        poz.w=KRATKA;
        pozz2=poz;
        pozz2.y=(double)KRATKA*(tmp.y)+((-y+1.0)*KRATKA)-KRATKA/2;
        SDL_Point poz2;
        poz2.x=KRATKA/2;
        poz2.y=KRATKA/2;
        SDL_SetTextureColorMod(tx,0,0,0);
        SDL_SetTextureAlphaMod(tx,128);
        SDL_RenderCopyEx(Rend,tx,NULL,&pozz2,kat2,&poz2,SDL_FLIP_NONE);
        SDL_SetTextureColorMod(tx,255,255,255);
        SDL_SetTextureAlphaMod(tx,255);
        SDL_RenderCopyEx(Rend,tx,NULL,&poz,kat,&poz2,SDL_FLIP_NONE);
    }
    SDL_DestroyTexture(tx);
}

void rendmape(vector<vector <int> > m1[],int x, int y,xy zaznkr){
    SDL_SetRenderTarget(Rend,txmiasto);
    DEBUG cout << "testr1"<<endl;
    for (int i2=-1; i2<(2*ZASx+2); i2++){
        for (int i=-1; i<(2*ZASy+2); i++){
            SDL_Rect poz;
            poz.x=(i2+1)*KRATKA;
            poz.y=(i+1)*KRATKA;
            poz.w=KRATKA;
            poz.h=KRATKA;
            if (i2+x<0 || i+y<0 || i2+x>=m1[0].size() || i+y>=m1[0].size()){
                SDL_RenderCopy(Rend,CzKw,NULL,&poz);
            }else{
                SDL_Point tmp={KRATKA/2,KRATKA/2};
                SDL_RenderCopyEx(Rend,zwroctxtr(i2+x,i+y,m1[0][i2+x][i+y]/4),NULL,&poz,90*(m1[0][i2+x][i+y]%4),&tmp,SDL_FLIP_NONE);
            }
        }
    }
    vector <tuple<double,double,SDL_Rect,SDL_Texture*>> npce;
    vector <tuple<double,double,SDL_Rect,SDL_Texture*,int,SDL_Rect,SDL_Rect,SDL_Rect>> w;
    vector <tuple<double,double,SDL_Rect,SDL_Texture*>> fw;
    vector <tuple<double,double,SDL_Rect,SDL_Texture*>> bg;
    vector <tuple<double,double,SDL_Rect,SDL_Texture*>> itemy;
    for (int k=0; k<5;k++){
        if (k==0){
            for (int i=0; i<npc[0].sciezka2.size();i++){
                xy tmp = npc[0].sciezka2[i];
                SDL_Rect poz;
                poz.x=(tmp.x-x+1)*KRATKA;
                poz.y=(tmp.y-y+1)*KRATKA;
                poz.h=KRATKA;
                poz.w=KRATKA;
                SDL_RenderCopy(Rend,txanim[0][0],NULL,&poz);
            }
        }
        if (k==3){
            sort(pociski.begin(),pociski.end(),cmppoci);
            sort(pociskiwbite.begin(),pociskiwbite.end(),cmppociwbite);
            sort(npce.begin(),npce.end(),cmpnpc);
            int liczp=0;
            int liczpw=0;
            int licznpc=0;
            int liczsc=0;
            int liczbg=0;
            int liczfw=0;
            int liczitemy=0;
            DEBUG cout << "testr3"<<endl;
            while(liczp<pociski.size() || liczpw<pociskiwbite.size() || licznpc<npce.size() || liczsc<w.size() || liczbg<bg.size() || liczfw < fw.size()|| liczitemy < itemy.size()){
                double pocy=10000;
                if (liczp<pociski.size()){
                    pocy=pociski[liczp].poz.y;
                }
                double pocwby=10000;
                if (liczpw<pociskiwbite.size()){
                    pocwby=get <0> (pociskiwbite[liczpw]).y;
                }
                double npcy=10000;
                if (licznpc<npce.size()){
                    npcy=get <1> (npce[licznpc]);
                }
                double scy=10000;
                if (liczsc<w.size()){
                    scy=get<1> (w[liczsc]);
                }
                double bgy=10000;
                if (liczbg<bg.size()){
                    bgy=get<1> (bg[liczbg]);
                }
                double fwy=10000;
                if (liczfw<fw.size()){
                    fwy=get<1> (fw[liczfw]);
                }
                double itemyy=10000;
                if (liczitemy<itemy.size()){
                    itemyy=get<1> (itemy[liczitemy]);
                }
                double miny=min(min(itemyy,min(pocy,pocwby)),min(min(npcy,scy),min(bgy,fwy)));
                //cout << itemyy<<" "<<pocy<<" "<<pocwby<<" "<<npcy<<endl;
                if (miny==pocy){
                    int i=liczp;
                    rendpoci(pociski[i].poz,pociski[i].h,pociski[i].strzala,pociski[i].kat,pociski[i].katcienia,x,y, 0);
                    liczp++;
                }
                if (miny==pocwby){
                    int i=liczpw;
                    rendpoci(get <0> (pociskiwbite[i]),get <3> (pociskiwbite[i]),get <4> (pociskiwbite[i]),get <1> (pociskiwbite[i]),get <2> (pociskiwbite[i]),x,y, 1);
                    liczpw++;
                }
                if (miny==npcy){
                    int i=licznpc;
                    SDL_RenderCopy(Rend,get<3> (npce[i]),NULL,&get<2> (npce[i]));
                    licznpc++;
                }
                if (miny==scy){
                    int i=liczsc;
                    SDL_SetTextureAlphaMod(get <3> (w[i]),get <4> (w[i]));
                    SDL_RenderCopy(Rend,get <3> (w[i]),&get<5> (w[i]),&get <2> (w[i]));
                    SDL_SetTextureAlphaMod(get <3> (w[i]),255);
                    SDL_RenderCopy(Rend,get <3> (w[i]),&get<6> (w[i]),&get <7> (w[i]));
                    liczsc++;
                }
                if (miny==bgy){
                    int i=liczbg;
                    SDL_RenderCopy(Rend,get <3> (bg[i]),NULL,&get <2> (bg[i]));
                    liczbg++;
                }
                if (miny==fwy){
                    int i=liczfw;
                    SDL_RenderCopy(Rend,get <3> (fw[i]),NULL,&get <2> (fw[i]));
                    liczfw++;
                }
                if (miny==itemyy){
                    int i=liczitemy;
                    SDL_RenderCopy(Rend,get <3> (itemy[i]),NULL,&get <2> (itemy[i]));
                    SDL_DestroyTexture(get<3>(itemy[i]));
                    liczitemy++;
                }
            }
            DEBUG cout << "testr4"<<endl;
        }
        DEBUG cout << "testr2>"<< k<<endl;
        for (int i=-1; i<=(2*ZASy+3); i++){
            for (int i2=-1; i2<(2*ZASx+2); i2++){
                SDL_Rect poz;
                poz.x=(i2+1)*KRATKA;
                poz.y=(i+1)*KRATKA;
                poz.w=KRATKA;
                poz.h=KRATKA;
                if (k==0){
                    if (!(i2+x<0 || i+y<0 || i2+x>=m1[0].size() || i+y>=m1[0].size())){
                        if (m1[1][i2+x][i+y]!=-1){
                            SDL_Rect poz2=poz;
                            poz2.w=1.5*KRATKA;
                            poz2.x-=0.25*KRATKA;
                            poz2.y-=KRATKA;
                            poz2.h=obliczhtxszerokie(zwroctxbg(i2+x,i+y,m1[1][i2+x][i+y]))*KRATKA+KRATKA;
                            bg.push_back(make_tuple(i2+x,(double)(i+y)+0.01,poz2,zwroctxbg(i2+x,i+y,m1[1][i2+x][i+y])));
                        }
                        if (m1[5][i2+x][i+y]!=-1){
                            SDL_Rect poz2=poz;
                            poz2.w=1.5*KRATKA;
                            poz2.x-=0.25*KRATKA;
                            poz2.y-=KRATKA;
                            poz2.h=obliczhtxszerokie(zwroctxfw(i2+x,i+y,m1[5][i2+x][i+y]))*KRATKA+KRATKA;
                            fw.push_back(make_tuple(i2+x,(double)(i+y)+0.71,poz2,zwroctxfw(i2+x,i+y,m1[5][i2+x][i+y])));
                        }
                        if (m1[3][i2+x][i+y]){
                            itemy.push_back(make_tuple(i2+x,(double)(i+y)+0.50,poz,przedmnaekr(przedm[m1[3][i2+x][i+y]],m1[3][i2+x][i+y])));
                        }
                        if (m1[4][i2+x][i+y]!=-1){
                            SDL_Rect poz2={(npc[m1[4][i2+x][i+y]].x-x+1)*KRATKA,(npc[m1[4][i2+x][i+y]].y-y+1)*KRATKA,0,0};
                            poz2.h=5*KRATKA;
                            poz2.w=4*KRATKA;
                            poz2.y-=3*KRATKA;
                            poz2.x-=KRATKA;
                            if (npc[0].x==i2+x && npc[0].y==i+y){
                                pozgr.x=poz2.x+KRATKA;
                                pozgr.y=poz2.y+KRATKA;
                            }
                            double tmp1=0;
                            double tmp2=0;
                            if (npc[m1[4][i2+x][i+y]].tmaxruch && SDL_GetTicks()-npc[m1[4][i2+x][i+y]].truchu<=npc[m1[4][i2+x][i+y]].tmaxruch){
                                tmp1=((npc[m1[4][i2+x][i+y]].x-npc[m1[4][i2+x][i+y]].popx)*((int)((KRATKA*(SDL_GetTicks()-npc[m1[4][i2+x][i+y]].truchu))/npc[m1[4][i2+x][i+y]].tmaxruch)-KRATKA))*(bool)(npc[m1[4][i2+x][i+y]].x-npc[m1[4][i2+x][i+y]].popx);
                                tmp2=((npc[m1[4][i2+x][i+y]].y-npc[m1[4][i2+x][i+y]].popy)*((int)((KRATKA*(SDL_GetTicks()-npc[m1[4][i2+x][i+y]].truchu))/npc[m1[4][i2+x][i+y]].tmaxruch)-KRATKA))*(bool)(npc[m1[4][i2+x][i+y]].y-npc[m1[4][i2+x][i+y]].popy);
                                tmp1/=KRATKA;
                                tmp2/=KRATKA;
                                poz2.x+=tmp1*KRATKA;
                                poz2.y+=tmp2*KRATKA;
                            }
                            if (renderowani[m1[4][i2+x][i+y]]==0){
                                renderowani[m1[4][i2+x][i+y]]=1;
                                npc[m1[4][i2+x][i+y]].updatetx();
                                if (npc[m1[4][i2+x][i+y]].kier()==2 && npc[m1[4][i2+x][i+y]].czy_dlugi()){
                                    poz2.y+=KRATKA;
                                    tmp2+=1.0;
                                }
                                if (npc[m1[4][i2+x][i+y]].kier()==1 && npc[m1[4][i2+x][i+y]].czy_dlugi()){
                                    poz2.x-=KRATKA;
                                    tmp1-=1.0;
                                }
                                npce.push_back(make_tuple((npc[m1[4][i2+x][i+y]].x)+tmp1,(npc[m1[4][i2+x][i+y]].y)+tmp2+0.70,poz2,npc[m1[4][i2+x][i+y]].tekstura));
                                npc[m1[4][i2+x][i+y]].poz={npc[m1[4][i2+x][i+y]].x+tmp1,npc[m1[4][i2+x][i+y]].y+tmp2};
                            }
                        }
                    }
                }
                if (k==1){
                    if (i2+x<0 || i+y<0 || i2+x>=m1[0].size() || i+y>=m1[0].size()){
                        SDL_RenderCopy(Rend,CzKw,NULL,&poz);
                    }else if (m1[2][i2+x][i+y]!=-1){
                        SDL_Texture* tmptx=zwroctxw(i2+x,i+y,m1[2][i2+x][i+y]);
                        int a=200;
                        for (int k=1; k<=(int)(obliczhtxszerokie(tmptx)+0.99);k++){
                            int tab1[3]={0,-1,1};
                            int tab2[3]={0,-1,1};
                            for (int ii=0; ii<3;ii++){
                                for (int jj=0; jj<3;jj++){
                                    if (i2+x == zaznkr.x+tab1[ii] && i+y-k==zaznkr.y+tab2[jj]){
                                        przezr[make_pair(i2+x,i+y)].second=1;
                                        if (przezr[make_pair(i2+x,i+y)].first==0){
                                            przezr[make_pair(i2+x,i+y)].first=200;
                                        }
                                        a=przezr[make_pair(i2+x,i+y)].first;
                                    }
                                }
                            }
                            if (k&& i+y-k>=0 && (m1[4][i2+x][i+y-k]!=-1 || (i2+x==npc[0].x&&i+y-k==npc[0].y))){
                                przezr[make_pair(i2+x,i+y)].second=1;
                                if (przezr[make_pair(i2+x,i+y)].first==0){
                                    przezr[make_pair(i2+x,i+y)].first=200;
                                }
                                a=przezr[make_pair(i2+x,i+y)].first;
                            }
                        }
                        if (przezr.count(make_pair(i2+x,i+y))){
                            a=przezr[make_pair(i2+x,i+y)].first;
                        }
                        SDL_Rect poz2=poz;
                        poz2.h=obliczhtxszerokie(tmptx)*KRATKA+KRATKA;
                        poz2.y-=poz2.h;
                        poz2.y+=KRATKA;
                        poz2.x-=KRATKA/4;
                        poz2.w=1.5*KRATKA;
                        Uint32 format;
                        int xx,yy,acces;
                        SDL_QueryTexture(tmptx,&format,&acces,&xx,&yy);
                        SDL_Rect tmp = {0,0,xx,yy-2*xx/3};
                        SDL_Rect tmp2 = {0,yy-2*xx/3,xx,2*xx/3};
                        if (i2+x-1>=0 && m1[2][i2+x-1][i+y]==m1[2][i2+x][i+y]){
                            poz2.x+=KRATKA/4;
                            poz2.w-=KRATKA/4;
                            tmp.x+=xx/6;
                            tmp.w-=xx/6;
                        }
                        if (i2+x+1<m1[0].size() && m1[2][i2+x+1][i+y]==m1[2][i2+x][i+y]){
                            poz2.w-=KRATKA/4;
                            tmp.w-=xx/6;
                        }
                        tmp2.x=tmp.x;
                        tmp2.w=tmp.w;
                        SDL_Rect poz3=poz2;
                        poz3.h-=KRATKA;
                        poz3.y+=poz3.h;
                        poz3.h=KRATKA;
                        poz2.h-=KRATKA;
                        if (obliczhtxszerokie(zwroctxw(i2+x,i+y,m1[2][i2+x][i+y]))<=1.75){
                            a=255;
                        }
                        w.push_back(make_tuple(i2+x,(double)(i+y)+0.02,poz2,zwroctxw(i2+x,i+y,m1[2][i2+x][i+y]),a,tmp,tmp2,poz3));
                    }
                }
                if (k==2){
                    if (przezr.count(make_pair(i2+x,i+y)) && przezr[make_pair(i2+x,i+y)].second){
                        przezr[make_pair(i2+x,i+y)].first-=7*(przezr[make_pair(i2+x,i+y)].first>52);
                        przezr[make_pair(i2+x,i+y)].first=max(przezr[make_pair(i2+x,i+y)].first,52);
                    }
                    if (przezr.count(make_pair(i2+x,i+y)) && !przezr[make_pair(i2+x,i+y)].second){
                        przezr[make_pair(i2+x,i+y)].first+=7*(przezr[make_pair(i2+x,i+y)].first<200);
                        przezr[make_pair(i2+x,i+y)].first=min(200,przezr[make_pair(i2+x,i+y)].first);
                        if (przezr[make_pair(i2+x,i+y)].first==200){
                            przezr.erase(make_pair(i2+x,i+y));
                        }
                    }
                    if (przezr.count(make_pair(i2+x,i+y))){
                        przezr[make_pair(i2+x,i+y)].second=0;
                    }
                }
                if (k==4){
                    if (!(i2+x<0 || i+y<0 || i2+x>=m1[0].size() || i+y>=m1[0].size()) && m1[4][i2+x][i+y]!=-1 && !napisani[m1[4][i2+x][i+y]]){
                        napisani[m1[4][i2+x][i+y]]=1;
                        int grubosc=0;
                        for (int k=(int)npc[m1[4][i2+x][i+y]].napisy.size()-1;k>=0;k--){
                            if (npc[m1[4][i2+x][i+y]].napisy[k].ilems <= npc[m1[4][i2+x][i+y]].napisy[k].ilemszaniku){
                                npc[m1[4][i2+x][i+y]].napisy[k].a=(255*npc[m1[4][i2+x][i+y]].napisy[k].ilems)/(npc[m1[4][i2+x][i+y]].napisy[k].ilemszaniku);
                                npc[m1[4][i2+x][i+y]].napisy[k].a+=(npc[m1[4][i2+x][i+y]].napisy[k].a==0);
                            }else{
                                npc[m1[4][i2+x][i+y]].napisy[k].a=255;
                            }
                            grubosc=grubosc-(wypisz(npc[m1[4][i2+x][i+y]].napisy[k].tekst,0,0,npc[m1[4][i2+x][i+y]].napisy[k].r,npc[m1[4][i2+x][i+y]].napisy[k].g,npc[m1[4][i2+x][i+y]].napisy[k].b,-1).y);
                            int napis_x=(npc[m1[4][i2+x][i+y]].poz.x-x+1)*KRATKA+KRATKA*(npc[m1[4][i2+x][i+y]].zwr_hitbox().x_prawy-npc[m1[4][i2+x][i+y]].zwr_hitbox().x_lewy)/2;
                            int napis_y=(npc[m1[4][i2+x][i+y]].poz.y-(double)y+2.0-npc[m1[4][i2+x][i+y]].h)*KRATKA+grubosc-0.2*KRATKA;
                            napis_x*=-1;
                            wypisz(npc[m1[4][i2+x][i+y]].napisy[k].tekst,napis_x,napis_y,npc[m1[4][i2+x][i+y]].napisy[k].r,npc[m1[4][i2+x][i+y]].napisy[k].g,npc[m1[4][i2+x][i+y]].napisy[k].b,npc[m1[4][i2+x][i+y]].napisy[k].a);
                            npc[m1[4][i2+x][i+y]].napisy[k].ilems-=(SDL_GetTicks()-npc[m1[4][i2+x][i+y]].napisy[k].poprz);
                            npc[m1[4][i2+x][i+y]].napisy[k].poprz=SDL_GetTicks();
                            if (npc[m1[4][i2+x][i+y]].napisy[k].ilems<0){
                                npc[m1[4][i2+x][i+y]].napisy.erase(npc[m1[4][i2+x][i+y]].napisy.begin()+k);
                                k--;
                            }
                        }
                    }
                }
            }
        }
    }
    DEBUG cout << "testr_koniec"<<endl;
    renderowani.clear();
    napisani.clear();
    SDL_SetRenderTarget(Rend,NULL);
}
