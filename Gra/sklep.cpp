#include <vector>
#include <cstdlib>
#include <SDL.h>
#include <tuple>

#include "it.h"
#include "npc.h"

extern int WYS;
extern SDL_Renderer* Rend;
extern SDL_Texture* skltx;
extern SDL_Rect sklzamkn;
extern int czysklep;
extern bool ignorujmysz;
extern bool czyzmianaskl;
extern vector <SDL_Rect> sklrozm;
extern vector <SDL_Rect> sklrozm2;
extern bool sklmyszaP;
extern bool sklmyszaL;
extern vector <vector <int> > sklept;
extern vector <vector <int> > sklept2;
extern vector <it> sklprzedm;
extern vector <tuple<it,int,int> > sklprzedm2;
extern int SZER;
extern int WYS;
extern vector <NPC> npc;
extern vector <vector <SDL_Texture*> > txit;
extern SDL_Texture* CzKw;
extern xy multipodn (int x, int y, vector <it> & itemy);
extern vector <string> stringi;
extern int KRATKA;
extern int ZASy;
extern vector <it> bufer;

void wartosci2(bool czyskl, int zloto2);
void ryskr(int a, int b, int x, int y,int kwrozm);
xy wypisz (string txt, int x, int y, int r, int g, int b, int a);

void wartosci2(bool czyskl, int zloto2){
int x=KRATKA/2;
int y=(2*ZASy)*KRATKA+KRATKA;
xy tmp=wypisz("G "+to_string(npc[0].gold),x,y,0,0,0,-1);
tmp.y-=y;
y-=tmp.y;
if (czyskl){
    x=SZER/2+KRATKA/2;
}
wypisz("G "+to_string(npc[0].gold),x,y,207,181,59,255);
if (czyskl){
    xy tmp2=wypisz("G "+to_string(zloto2),x,y,0,0,0,-1);
    tmp2.x-=x;
    x=SZER/2-KRATKA/2;
    x-=tmp2.x;
    wypisz("G "+to_string(zloto2),x,y,207,181,59,255);
}
}

bool uklad (vector <it> & przedm,vector <vector <int> > & sklept){
    bool koniec=1;
    for (int k=0; k<przedm.size();k++){
        bool wynik=0;
        int a=przedm[k].wym/10;
        int b=przedm[k].wym%10;
        bool czek=0;
        for (int i=0; i<sklept.size();i++){
            for (int j=0; j<sklept[0].size();j++){
                czek=0;
                for (int i2=0; i2<a;i2++){
                    for (int j2=0; j2<b;j2++){
                        if (i+i2>=sklept.size() || j+j2>=sklept[0].size()){
                            czek=1;
                            break;
                        }
                        if (sklept[i+i2][j+j2]!=0){
                            czek=1;
                        }
                    }
                }
                if (!czek){
                    for (int i2=0; i2<a;i2++){
                        for (int j2=0; j2<b;j2++){
                            sklept[i+i2][j+j2]=k+1;
                        }
                    }
                    wynik=1;
                    break;
                }
            }
            if (wynik){
                break;
            }
        }
        koniec*=wynik;
    }
    return koniec;
}

vector <it> posortujit (vector <it> & a){
        vector <it> b;
        for (int i=0; i<a.size();i++){
            if (a[i].typ==0){
                b.push_back(a[i]);
            }
        }
        for (int i=0; i<a.size();i++){
            if (a[i].typ==1){
                b.push_back(a[i]);
            }
        }
        for (int i=0; i<a.size();i++){
            if (a[i].typ==3){
                b.push_back(a[i]);
            }
        }
        for (int i=0; i<a.size();i++){
            if (a[i].typ==4){
                b.push_back(a[i]);
            }
        }
        for (int i=0; i<a.size();i++){
            if (a[i].typ==2){
                b.push_back(a[i]);
            }
        }
        for (int i=0; i<a.size();i++){
            if (a[i].typ==5){
                b.push_back(a[i]);
            }
        }
        return b;
}

void sklep (int npcnumer){
    srand(npcnumer);
    int kwrozm=WYS/15;
    SDL_SetRenderDrawColor(Rend, 150, 75, 0,255);
    int xm, ym;
    SDL_GetMouseState(&xm, &ym);
    if (czyzmianaskl){
        SDL_SetRenderTarget(Rend,skltx);
        SDL_SetRenderDrawColor(Rend,0,0,0,0);
        SDL_RenderClear(Rend);
        sklrozm.clear();
        sklrozm2.clear();
        sklprzedm.clear();
        sklprzedm2.clear();
        SDL_SetRenderDrawColor(Rend,150,75,0,255);
        SDL_RenderDrawLine(Rend,SZER/2,0,SZER/2,WYS);
        SDL_Rect tmp;
        tmp.x=kwrozm;
        tmp.y=WYS/10+kwrozm;
        tmp.h=kwrozm;
        tmp.w=kwrozm;
        sklprzedm=posortujit(npc[npcnumer].nasprzedaz);
        npc[npcnumer].nasprzedaz=sklprzedm;

        int b=1; int e=WYS/5;
        while (b<e){
            int s=(b+e+1)/2;
            kwrozm=s;
            sklept.resize(max(4,WYS/kwrozm-3));
            for (int i=0; i<sklept.size();i++){
                sklept[i].clear();
                sklept[i].resize(max((SZER/2)/kwrozm-2,4));
            }
            bool tmp = uklad(sklprzedm,sklept);
            if (tmp){
                b=s;
            }else{
                e=s-1;
            }
        }
        kwrozm=min(b,e);
        /*cout << kwrozm<<"<"<<endl;
        for (kwrozm=WYS/5; kwrozm>0;kwrozm--){
            cout << kwrozm<<" ";
            sklept.resize(max(4,WYS/kwrozm-3));
            for (int i=0; i<sklept.size();i++){
                sklept[i].clear();
                sklept[i].resize(max((SZER/2)/kwrozm-2,4));
            }
            bool tmp=uklad(sklprzedm,sklept);
            cout << tmp<<endl;
            if (tmp){
                break;
            }
        }*/
        sklept.resize(max(4,WYS/kwrozm-3));
        for (int i=0; i<sklept.size();i++){
            sklept[i].clear();
            sklept[i].resize(max((SZER/2)/kwrozm-2,4));
        }
        if (!uklad(sklprzedm,sklept)){
            cout << "ALARM1"<<endl;
        }
        int xskl=(SZER/2-kwrozm*(int)sklept[0].size())/2;
        int yskl=3*(WYS-kwrozm*(int)sklept.size())/4;
        ryskr(sklept.size(),sklept[0].size(),xskl,yskl,kwrozm);
        xy tmp2 = wypisz("seller's items",-(SZER/4),3*(WYS-kwrozm*(int)sklept.size())/4,150,75,0,-1);
        tmp2.y-=3*(WYS-kwrozm*(int)sklept.size())/4;
        wypisz("seller's items",-(SZER/4),yskl-2*tmp2.y,150,75,0,255);
        SDL_SetRenderDrawColor(Rend,150,75,0,255);
        tmp.x=xskl;
        tmp.y=yskl;
        tmp.h=sklept.size()*kwrozm;
        tmp.w=sklept[0].size()*kwrozm;
        sklrozm.resize(sklprzedm.size());
        for (int i=0; i<sklept.size();i++){
            for (int j=0; j<sklept[0].size();j++){
                if (sklept[i][j] && !(i>0 && sklept[i-1][j]==sklept[i][j]) && !(j>0 && sklept[i][j-1]==sklept[i][j])){
                    tmp.x=xskl+j*kwrozm;
                    tmp.y=yskl+i*kwrozm;
                    tmp.h=sklprzedm[sklept[i][j]-1].wym/10*kwrozm;
                    tmp.w=sklprzedm[sklept[i][j]-1].wym%10*kwrozm;
                    sklrozm[sklept[i][j]-1]=tmp;
                    SDL_RenderCopy(Rend, txit[sklprzedm[sklept[i][j]-1].typ][sklprzedm[sklept[i][j]-1].tekstura],NULL,&tmp);
                }
            }
        }
        vector <it> sklprzedm22;
        for (int i=0; i<9;i++){
            for (int j=0; j<npc[0].ekw[i].size();j++){
                sklprzedm2.push_back(make_tuple(npc[0].ekw[i][j],i,j));
                sklprzedm22.push_back(npc[0].ekw[i][j]);
            }
        }
        for (int i=0; i<npc[0].pl.prz.size();i++){
            for (int j=0; j<npc[0].pl.prz[i].size();j++){
                sklprzedm2.push_back(make_tuple(npc[0].pl.prz[i][j],-i-1,j));
                sklprzedm22.push_back(npc[0].pl.prz[i][j]);
            }
        }
        b=1; e=WYS/5;
        while (b<e){
            int s=(b+e+1)/2;
            kwrozm=s;
            sklept2.resize(max(4,WYS/kwrozm-3));
            for (int i=0; i<sklept2.size();i++){
                sklept2[i].clear();
                sklept2[i].resize(max((SZER/2)/kwrozm-2,4));
            }
            bool tmp = uklad(sklprzedm22,sklept2);
            if (tmp){
                b=s;
            }else{
                e=s-1;
            }
        }
        kwrozm=min(b,e);
        sklept2.resize(max(4,WYS/kwrozm-3));
        for (int i=0; i<sklept2.size();i++){
            sklept2[i].clear();
            sklept2[i].resize(max((SZER/2)/kwrozm-2,4));
        }
        if (!uklad(sklprzedm22,sklept2)){
            cout << "ALARM2"<<endl;
        }
        if (SZER/2<kwrozm*(int)sklept2[0].size()){
            kwrozm=SZER/2/((int)sklept2[0].size()+2);
        }
        xskl=(SZER/2-kwrozm*(int)sklept2[0].size())/2+SZER/2;
        yskl=3*(WYS-kwrozm*(int)sklept2.size())/4;
        wypisz("your items",-(3*SZER)/4,yskl-2*tmp2.y,150,75,0,255);
        ryskr(sklept2.size(),sklept2[0].size(),xskl,yskl,kwrozm);
        tmp2.y-=3*(WYS-kwrozm*(int)sklept2.size())/4;
        SDL_SetRenderDrawColor(Rend,150,75,0,255);
        tmp.x=xskl;
        tmp.y=yskl;
        tmp.h=sklept2.size()*kwrozm;
        tmp.w=sklept2[0].size()*kwrozm;
        sklrozm2.resize(sklprzedm2.size());
        for (int i=0; i<sklept2.size();i++){
            for (int j=0; j<sklept2[0].size();j++){
                if (sklept2[i][j] && !(i>0 && sklept2[i-1][j]==sklept2[i][j]) && !(j>0 && sklept2[i][j-1]==sklept2[i][j])){
                    tmp.x=xskl+j*kwrozm;
                    tmp.y=yskl+i*kwrozm;
                    tmp.h=sklprzedm22[sklept2[i][j]-1].wym/10*kwrozm;
                    tmp.w=sklprzedm22[sklept2[i][j]-1].wym%10*kwrozm;
                    sklrozm2[sklept2[i][j]-1]=tmp;
                    SDL_RenderCopy(Rend, txit[sklprzedm22[sklept2[i][j]-1].typ][sklprzedm22[sklept2[i][j]-1].tekstura],NULL,&tmp);
                }
            }
        }
        xy tmp3=wypisz("EXIT",0,0,150,75,0,-1);
        sklzamkn.x=SZER-2*tmp3.x;
        sklzamkn.y=0;
        sklzamkn.h=2*tmp3.y;
        sklzamkn.w=2*tmp3.x;
        SDL_RenderCopy(Rend,CzKw,NULL,&sklzamkn);
        SDL_SetRenderDrawColor(Rend,200,0,0,255);
        SDL_RenderDrawRect(Rend,&sklzamkn);
        wypisz("EXIT",SZER-(3*tmp3.x)/2,tmp3.y/2,200,0,0,255);
        wartosci2(1,npc[npcnumer].gold);
        SDL_SetRenderTarget(Rend,NULL);
        czyzmianaskl=0;
    }
    SDL_Rect tmp={0,0,SZER,WYS};
    SDL_RenderCopy(Rend,skltx,NULL,&tmp);
    if (xm>=sklzamkn.x && xm<=sklzamkn.x+sklzamkn.w && ym>=sklzamkn.y && ym<=sklzamkn.y+sklzamkn.h && (GetKeyState(VK_LBUTTON) & 0x80)){
        czysklep=0;
        ignorujmysz=1;
    }
    for (int i=0; i<sklprzedm.size();i++){
        if (xm>=sklrozm[i].x && xm<=sklrozm[i].x+sklrozm[i].w && ym>=sklrozm[i].y && ym<=sklrozm[i].y+sklrozm[i].h){
            bool czek=0;
            int gdzie=-2;
            for (int k=8;k>=0 && !czek;k--){
                czek=npc[0].dodajdoekw(sklprzedm[i],k,0);
                if (czek){
                    gdzie=k;
                }
            }
            if (!czek){
                czek=npc[0].dodajdopl(sklprzedm[i],0);
                if (czek){
                    gdzie=-1;
                }
            }
            czek*=(npc[0].gold>=(int)(sklprzedm[i].value*npc[npcnumer].wspsprzedazy));
            SDL_SetRenderDrawColor(Rend,200*!czek,200*czek,0,255);
            if (czek && !sklmyszaL && (GetKeyState(VK_LBUTTON) & 0x80)){
                bool czek=0;
                for (int k=8;k>=0 && !czek;k--){
                    czek=npc[0].dodajdoekw(sklprzedm[i],k,1);
                }
                if (!czek){
                    czek=npc[0].dodajdopl(sklprzedm[i],1);
                }
                if (czek){
                    npc[0].gold-=(int)(sklprzedm[i].value*npc[npcnumer].wspsprzedazy);
                    npc[npcnumer].gold+=(int)(sklprzedm[i].value*npc[npcnumer].wspsprzedazy);
                    npc[npcnumer].nasprzedaz.erase(npc[npcnumer].nasprzedaz.begin()+i);
                }
                czyzmianaskl=czek;
            }
            SDL_RenderDrawRect(Rend,&sklrozm[i]);
            vector <it> tmp;
            tmp.push_back(sklprzedm[i]);
            xy tmp2=multipodn(xm,ym,tmp);
            stringstream ss;
            ss<<(int)(sklprzedm[i].value*npc[npcnumer].wspsprzedazy);
            xy tmp3=wypisz("G "+ss.str(),0,0,0,0,0,-1);
            SDL_Rect tmp4={tmp2.x,tmp2.y-tmp3.y,tmp3.x,tmp3.y};
            SDL_RenderCopy(Rend,CzKw,NULL,&tmp4);
            xy tmp5=wypisz("G "+ss.str(),tmp2.x,tmp2.y-tmp3.y,207,181,59,255);
            if (gdzie>=0){
                xy tmp6=wypisz("  will be added to: "+stringi[gdzie],tmp5.x,tmp2.y-tmp3.y,128,128,128,-1);
                SDL_Rect tmp7={tmp5.x,tmp2.y-tmp3.y,tmp6.x-tmp5.x,tmp6.y-tmp2.y+tmp3.y};
                SDL_RenderCopy(Rend,CzKw,NULL,&tmp7);
                wypisz("  will be added to: "+stringi[gdzie],tmp5.x,tmp2.y-tmp3.y,128,128,128,255);
            }else if (gdzie==-1){
                xy tmp6=wypisz("  will be added to: backpack",tmp5.x,tmp2.y-tmp3.y,128,128,128,-1);
                SDL_Rect tmp7={tmp5.x,tmp2.y-tmp3.y,tmp6.x-tmp5.x,tmp6.y-tmp2.y+tmp3.y};
                SDL_RenderCopy(Rend,CzKw,NULL,&tmp7);
                wypisz("  will be added to: backpack",tmp5.x,tmp2.y-tmp3.y,128,128,128,255);
            }
        }
    }
    for (int i=0; i<sklprzedm2.size();i++){
        if (xm>=sklrozm2[i].x && xm<=sklrozm2[i].x+sklrozm2[i].w && ym>=sklrozm2[i].y && ym<=sklrozm2[i].y+sklrozm2[i].h){
            SDL_SetRenderDrawColor(Rend,0,200,0,255);
            if (!sklmyszaL && (GetKeyState(VK_LBUTTON) & 0x80)){
                int cena=min((int)(get<0>(sklprzedm2[i]).value*npc[npcnumer].wspkupna),npc[npcnumer].gold);
                int k=(get<1>(sklprzedm2[i]));
                int k2=(get<2>(sklprzedm2[i]));
                if (k>=0){
                    npc[npcnumer].nasprzedaz.push_back(npc[0].ekw[k][k2]);
                    npc[0].ekw[k].erase(npc[0].ekw[k].begin()+k2);
                }else{
                    npc[npcnumer].nasprzedaz.push_back(npc[0].pl.prz[-k-1][k2]);
                    npc[0].usunzpl(-k-1,k2);
                }
                npc[0].gold+=cena;
                npc[npcnumer].gold-=cena;
                czyzmianaskl=1;
            }
            SDL_RenderDrawRect(Rend,&sklrozm2[i]);
            vector <it> tmp;
            tmp.push_back(get<0> (sklprzedm2[i]));
            xy tmp2=multipodn(xm,ym,tmp);
            stringstream ss;
            ss<<min((int)(get<0>(sklprzedm2[i]).value*npc[npcnumer].wspkupna),npc[npcnumer].gold);
            xy tmp3=wypisz("G "+ss.str(),0,0,0,0,0,-1);
            SDL_Rect tmp4={tmp2.x,tmp2.y-tmp3.y,tmp3.x,tmp3.y};
            SDL_RenderCopy(Rend,CzKw,NULL,&tmp4);
            xy tmp5 = wypisz("G "+ss.str(),tmp2.x,tmp2.y-tmp3.y,207,181,59,255);
            if (get<1>(sklprzedm2[i])>=0){
                xy tmp6=wypisz("  "+stringi[get<1>(sklprzedm2[i])],tmp5.x,tmp2.y-tmp3.y,128,128,128,-1);
                SDL_Rect tmp7={tmp5.x,tmp2.y-tmp3.y,tmp6.x-tmp5.x,tmp6.y-tmp2.y+tmp3.y};
                SDL_RenderCopy(Rend,CzKw,NULL,&tmp7);
                wypisz("  "+stringi[get<1>(sklprzedm2[i])],tmp5.x,tmp2.y-tmp3.y,128,128,128,255);
            }else{
                xy tmp6=wypisz("  backpack",tmp5.x,tmp2.y-tmp3.y,128,128,128,-1);
                SDL_Rect tmp7={tmp5.x,tmp2.y-tmp3.y,tmp6.x-tmp5.x,tmp6.y-tmp2.y+tmp3.y};
                SDL_RenderCopy(Rend,CzKw,NULL,&tmp7);
                wypisz("  backpack",tmp5.x,tmp2.y-tmp3.y,128,128,128,255);
            }
        }
    }
    srand(time(NULL)+SDL_GetTicks()%863);
    SDL_RenderPresent(Rend);
    sklmyszaP=(GetKeyState(VK_RBUTTON) & 0x80);
    sklmyszaL=(GetKeyState(VK_LBUTTON) & 0x80);
}
