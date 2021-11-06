#include <iomanip>

#include "npc.h"
#include "structy.h"



extern int KRATKA;
extern vector <NPC> npc;
extern string bonusystr [7];
extern string bonusypoz_stopnstr [7];
extern string bonusypoz_stopnstr [7];
extern string bonusyneg_stopnstr [7];
extern vector <int> bonusyint_critch;
extern vector <int> bonusyint_critdmg;
extern vector <int> bonusyint_procenty;
extern vector <efestrz> efstrz;
extern int SZER;
extern SDL_Renderer* Rend;
extern SDL_Texture* CzKw;
extern vector <vector <SDL_Texture*> > txit;
extern vector <SDL_Texture*> podntx;
extern vector <it> podnitem;
extern vector <xy> rozmtx;
extern int SZER;
extern int WYS;
extern xy podnwym;

bool porownajit (it it1, it it2);
void ryskr(int a, int b, int x, int y,int kwrozm);
xy wypisz (string txt, int x, int y, int r, int g, int b, int a);
xy wypisz2dou(int x,int y, string tekst,string tekst2, int wsp, int a, double w, bool czyczas);
xy wypisz2int(int x,int y, string tekst,string tekst2, int wsp, int a, int w);

xy podn2(int x,int y, it item){
    xy whatever = { -1,-1 };
    if (item.typ==-1){
        return whatever;
    }
    int wys=KRATKA;
    SDL_Rect tmp;
    tmp.x=x;
    tmp.y=y;
    tmp.h=wys;
    xy tmp2 = wypisz("attack ",x,y,128,128,128,-1);
    tmp2.x-=x;
    tmp2.y-=y;
    vector <stringstream> ssinty;
    ssinty.resize(item.inty.size());
    vector <stringstream> ssdou;
    ssdou.resize(item.dou.size());
    for (int i=0;i<item.inty.size();i++){
        ssinty[i]<<item.inty[i];
    }
    for (int i=0;i<item.dou.size();i++){
        ssdou[i]<<setprecision(2)<<fixed<<item.dou[i];
    }
    int szer2=0;
    SDL_Texture* tmptx;
    xy tmpxy;
    SDL_Rect tmpost;
    for (int ltmp=0; ltmp<2;ltmp++){
        int l=0;int a=-1+256*ltmp;
        if (item.typ==0){
            szer2=max(szer2,wypisz2dou(x,y+l*tmp2.y,"damage ","", npc[0].bonus(0),a,item.dou[0],0).x);l++;
            szer2=max(szer2,wypisz2dou(x,y+l*tmp2.y,"armor piercing ","", npc[0].bonus(1),a,item.dou[1],0).x);l++;
            szer2=max(szer2,wypisz2dou(x,y+l*tmp2.y,"attack speed "," s", -npc[0].bonus(2),a,item.dou[2],1).x);l++;
        }
        if (item.typ==1){
            szer2=max(szer2,wypisz2dou(x,y+l*tmp2.y,"damage ","", npc[0].bonus(0),a,item.dou[0],0).x);l++;
            szer2=max(szer2,wypisz2dou(x,y+l*tmp2.y,"armor piercing ","", npc[0].bonus(1),a,item.dou[1],0).x);l++;
            szer2=max(szer2,wypisz2dou(x,y+l*tmp2.y,"loading speed "," s", npc[0].bonus(2),a,item.dou[2],1).x);l++;
            szer2=max(szer2,wypisz("arrow speed "+ssdou[3].str()+" m/s",x,y+l*tmp2.y,128,128,128,a).x);l++;
        }
        if (item.typ==2){
            szer2=max(szer2,wypisz2int(x,y+l*tmp2.y,"durability ","%", 0,a,item.inty[0]).x);l++;
            for (int i=0; i<7;i++){
                if (item.zwrocbonus(i)>0){
                    stringstream ss;
                    if (i==3){
                        ss<<bonusyint_critch[item.zwrocbonus(i)-1];
                    }
                    if (i==4){
                        ss<<bonusyint_critdmg[item.zwrocbonus(i)-1];
                    }
                    if (i!=3 && i!=4){
                        ss<<bonusyint_procenty[item.zwrocbonus(i)-1];
                    }
                    szer2=max(szer2,wypisz(bonusystr[i]+" +"+ss.str()+"%",x,y+l*tmp2.y,30,172,30,a).x);l++;
                }
                if (item.zwrocbonus(i)<0){
                    stringstream ss;
                    if (i==3){
                        ss<<bonusyint_critch[-item.zwrocbonus(i)-1];
                    }
                    if (i==4){
                        ss<<bonusyint_critdmg[-item.zwrocbonus(i)-1];
                    }
                    if (i!=3 && i!=4){
                        ss<<bonusyint_procenty[-item.zwrocbonus(i)-1];
                    }
                    szer2=max(szer2,wypisz(bonusystr[i]+" -"+ss.str()+"%",x,y+l*tmp2.y,172,30,30,a).x);l++;
                }
            }

            if (item.inty[2]!=0){
                szer2 = max(szer2,wypisz("additional effect on hit: "+efstrz[item.inty[2]-1].nazwa,x+4*tmp2.y,y+l*tmp2.y,128,128,128,a).x);l++;
                stringstream ss5;
                ss5 << setprecision(2)<<fixed<<efstrz[item.inty[2]-1].ef.obr;
                szer2 = max(szer2,wypisz("dealing "+ss5.str()+" dmg each "+ to_string(efstrz[item.inty[2]-1].ef.czest) + " ms for "+to_string(efstrz[item.inty[2]-1].ef.ile)+" ms",x+4*tmp2.y,y+l*tmp2.y,128,128,128,a).x);l++;
                szer2 = max(szer2,wypisz ("uses before fading "+to_string(item.inty[3]),x+4*tmp2.y,y+l*tmp2.y,128,128,128,a).x);l++;
            }
        }
        if (item.typ==3){
            int k=0;
            szer2=max(szer2,wypisz2dou(x,y+l*tmp2.y,"armor ","", 0,a,item.dou[0],0).x);l++;
        }
        if (item.typ==4){
            int k=0;
            szer2=max(szer2,wypisz2dou(x,y+l*tmp2.y,"armor ","", 0,a,item.dou[0],0).x);l++;
            szer2=max(szer2,wypisz2dou(x,y+l*tmp2.y,"block speed ","", 0,a,item.dou[1],1).x);l++;
        }
        if (item.typ==5){
            if (item.dou[0]!=0){
                szer2=max(szer2,wypisz2dou(x,y+l*tmp2.y,"healing ","", npc[0].wspheal,a,item.dou[0],0).x);l++;
                szer2=max(szer2,wypisz2dou(x,y+l*tmp2.y,"each ","s", npc[0].wspcoile,a,item.dou[1],1).x);l++;
            }
            string naz_bon[2]={"strength","dexterity"};
            for (int k=0; k<2;k++){
                if (item.inty[k]>0){
                    szer2=max(szer2,wypisz(naz_bon[k]+" +"+ssinty[k].str(),x,y+l*tmp2.y,(item.inty[k]<0)*200,(item.inty[k]>0)*200,0,a).x);l++;
                }
                if (item.inty[k]<0){
                    szer2=max(szer2,wypisz(naz_bon[k]+" "+ssinty[k].str(),x,y+l*tmp2.y,(item.inty[k]<0)*200,(item.inty[k]>0)*200,0,a).x);l++;
                }
            }
            szer2=max(szer2,wypisz2dou(x,y+l*tmp2.y,"for ","s", npc[0].wspnaile,a,item.dou[2],1).x);l++;
        }
        if (item.typ!=2){
            for (int i=0; i<7;i++){
                if (item.zwrocbonus(i)>0){
                    szer2=max(szer2,wypisz(bonusypoz_stopnstr[item.zwrocbonus(i)-1]+" improves "+bonusystr[i],x,y+l*tmp2.y,30,172,30,a).x);l++;
                }
                if (item.zwrocbonus(i)<0){
                    szer2=max(szer2,wypisz(bonusyneg_stopnstr[-item.zwrocbonus(i)-1]+" worsens "+bonusystr[i],x,y+l*tmp2.y,172,30,30,a).x);l++;
                }
            }
        }
        if ((l)*tmp2.y>=wys){
            wys=(l)*tmp2.y;
        }
        if (ltmp==0){
            szer2-=x;
            tmp.h=wys;
            tmp.w=szer2+((tmp.h*(item.wym%10))/(item.wym/10));
            if (tmp.x+tmp.w>SZER){
                tmp.x-=tmp.w;
                x-=tmp.w;
            }
            tmpost=tmp;
            Uint8 a,r,g,b;
            SDL_GetRenderDrawColor(Rend,&r,&g,&b,&a);
            tmptx = SDL_CreateTexture(Rend, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, tmp.w, tmp.h);
            SDL_SetTextureBlendMode(tmptx,SDL_BLENDMODE_BLEND);
            SDL_SetRenderDrawBlendMode(Rend,SDL_BLENDMODE_BLEND);
            SDL_SetRenderDrawColor(Rend,0,0,0,0);
            SDL_SetRenderTarget(Rend, tmptx);
            SDL_RenderClear(Rend);
            tmp.x=0;
            tmp.y=0;
            SDL_SetTextureAlphaMod(CzKw,255);
            SDL_RenderCopy(Rend,CzKw,NULL,&tmp);
            SDL_SetRenderDrawColor(Rend,255,255,255,255);
            for (int i=0; i<tmp.h;i++){
                SDL_SetRenderDrawColor(Rend,255,255,255,(64*i)/tmp.h);
                SDL_RenderDrawLine(Rend,tmp.x,tmp.y+i,tmp.x+tmp.w,tmp.y+i);
            }
            tmpxy.y=tmpost.y+tmpost.h;
            tmpxy.x=tmpost.x+tmpost.w;

            SDL_SetRenderDrawColor(Rend,64,64,64,255);
            tmp.x--;
            tmp.y--;
            tmp.h+=2;
            tmp.w+=2;
            SDL_RenderDrawRect(Rend,&tmp);
            tmp.x++;
            tmp.y++;
            tmp.h-=2;
            tmp.w-=2;
            SDL_SetRenderDrawColor (Rend,r,g,b,a);
            tmp.w=((tmp.h*(item.wym%10))/(item.wym/10));
            SDL_SetRenderDrawColor(Rend,150,75,0,64);
            ryskr(item.wym/10,item.wym%10,tmp.x,tmp.y,tmp.h/(item.wym/10));
            SDL_SetRenderDrawColor(Rend,150,75,0,255);
            SDL_RenderCopy(Rend,txit[item.typ][item.tekstura],NULL,&tmp);
            x=tmp.w;
            y=0;
        }
    }
    SDL_SetRenderTarget(Rend, NULL);
    podntx.push_back(tmptx);
    SDL_SetTextureBlendMode(podntx[(int)podntx.size()-1],SDL_BLENDMODE_BLEND);
    podnitem.push_back(item);
    rozmtx.push_back({tmpost.w,tmpost.h});
    //SDL_RenderCopy(Rend, tmptx, NULL,&tmpost);
    return tmpxy;
}

xy multipodn (int x, int y, vector <it> & itemy){
    int wys=0;
    int maxi=0;
    bool czek=0;
    for (int i=0; i<itemy.size();i++){
        if (!(podnitem.size()==itemy.size()&& porownajit(itemy[i],podnitem[i]))){
            czek=1;
        }
    }
    if (czek){
        podnitem.clear();
        rozmtx.clear();
        for (int i=0; i<podntx.size();i++){
            SDL_DestroyTexture(podntx[i]);
        }
        podntx.clear();
        for (int i=0; i<itemy.size();i++){
            podn2(0,0,itemy[i]);
        }
    }
    for (int i=0;i<itemy.size();i++){
        wys+=rozmtx[i].y;
        maxi=max(rozmtx[i].x,maxi);
    }
    if (x+maxi>SZER){
        x=SZER-maxi;
    }
    if (y+wys>WYS && wys<WYS){
        y=WYS-wys;
    }
    podnwym.x=x;
    podnwym.y=y;
    if (wys>WYS){
        wys=0;
        int szer=0;
        for (int i=0; i<(((int)itemy.size())/2)*2;i++){
            if (rozmtx[i].x+rozmtx[i+1].x<SZER){
                szer=max(szer,rozmtx[i].x+rozmtx[i+1].x);
                i++;
            }
        }
        if (szer+x>SZER){
            x=SZER-szer;
        }
        podnwym.x=x;
        for (int i=0; i<(((int)itemy.size())/2)*2;i++){
            if (rozmtx[i].x+rozmtx[i+1].x<SZER){
                SDL_Rect tmp={x,y,rozmtx[i].x,rozmtx[i].y};
                SDL_RenderCopy(Rend,podntx[i],NULL,&tmp);
                tmp={x+rozmtx[i].x,y,rozmtx[i+1].x,rozmtx[i+1].y};
                SDL_RenderCopy(Rend,podntx[i+1],NULL,&tmp);
                y+=max(rozmtx[i].y,rozmtx[i+1].y);
                i++;
            }else{
                SDL_Rect tmp={x,y,rozmtx[i].x,rozmtx[i].y};
                SDL_RenderCopy(Rend,podntx[i],NULL,&tmp);
                y+=rozmtx[i].y;
            }
        }
        int i=(int)itemy.size();
        if (i%2){
            i--;
            SDL_Rect tmp={x,y,rozmtx[i].x,rozmtx[i].y};
            SDL_RenderCopy(Rend,podntx[i],NULL,&tmp);
        }
    }else{
        for (int i=0; i<itemy.size();i++){
            SDL_Rect tmp={x,y,rozmtx[i].x,rozmtx[i].y};
            SDL_RenderCopy(Rend,podntx[i],NULL,&tmp);
            y+=rozmtx[i].y;
        }
    }
    return podnwym;
}
