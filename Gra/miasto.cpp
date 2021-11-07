#include <vector>
#include <map>
#include <SDL.h>
#include <iostream>

#include "npc.h"
#include "poci.h"

using namespace std;

#define DEBUG if (0)
#define endl " >"<<__FUNCTION__<<"<"<<endl

int DOUBLECLICKms=250;

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
extern vector <SDL_Texture*> txubr;
extern vector <SDL_Texture*> txoczy;
extern vector <SDL_Texture*> txwlosy;
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
extern int rozmtmp;
extern int relacja[5][5];
extern int u;
extern int xnasw, ynasw;
extern vector<vector <int> > swiat[6];
extern string bonusystr [7];
extern string bonusypoz_stopnstr [7];
extern string bonusyneg_stopnstr [7];
extern vector <int> bonusyint_critch ;
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
extern bool przycisk[4];
extern vector <pair<string,bool> > rozmef;
extern bool czypodn;
extern vector <poci> pociski;
extern vector <tuple <xyd, double,double,double, it> > pociskiwbite;
extern int pozycje[4];
extern SDL_Texture* txmiasto;
extern SDL_Texture* txmiasto0;
extern bool czyzmianamiasto0;
extern xy pozgr;
extern map<pair<int,int>, pair<int,bool> > przezr;
przeciwnicy przeciwnik;

int stworzNPC(NPC npctmp);
it stworzjedz (double heal, double coile, double naile,int zwsily, int zwdex, int tekstura, int t, int maxt, int wym, int value, int bdmg=0,int bap=0, int bas=0, int bcrch=0, int bcrdmg=0, int bmovspd=0, int bds=0);
it stworzbron (int podtyp, double dmg, double ap, double as,int tekstura, int t, int maxt, int wym, int value,int bcrch=0,int bcrdmg=0, int bspd=0, int bds=0);
int dodnam1(it item, int numer, int x,int y,vector<vector<int> >m1[]);
void przedmczek(bool pauz, vector<vector<int> > m1[]);
void atak(int npcIDof, int npcIDdef, bool czykontratak = 0);
void mapa(vector<vector <int> > m1[]);
void close();
void interakcjaMapa(int x,int y,int typm1,int typm1R,int npcID);
bool obliczpoci (vector <poci> & p, vector<vector <int> > m1[]);
void rendmape(vector<vector <int> > m1[],int x, int y,xy zaznkr);
void wartosci();
bool rozmowaNPC (int n2,int v);
void ekwipunek();
//int podn(int npcID, int przedmID, xy pozpodno);
void sklep (int npcnumer);
void zapisz_mape(vector <vector<int> > m1[], int x, int y, bool czyswiat);
void generuj_przeciwnika(przeciwnicy ktory, vector <int> & npceID, vector <vector<int> > []);

void zachowanieNPC (vector <int> npceID, vector<vector <int> > m1[]){
    DEBUG cout << "pocz"<<endl;
    for (int i=0;i<m1[0].size();i++){
        for (int j=0;j<m1[0].size();j++){
            m1[4][i][j]=-1;
        }
    }
    int tmpx[4]={0,-1,0,1};
    int tmpy[4]={-1,0,1,0};
    npceID.push_back(0);
    for (int i=0; i<npceID.size();i++){
        int ID=npceID[i];
        if (!npc[ID].czymartwy){
            npc[ID].sprawdzef();
            m1[4][npc[ID].x][npc[ID].y]=ID;
            if (SDL_GetTicks()-npc[ID].truchu<=npc[ID].tmaxruch && npc[ID].popx<m1[0].size() && npc[ID].popx>=0 && npc[ID].popy<m1[0].size() && npc[ID].popy>=0){
                m1[4][npc[ID].popx][npc[ID].popy]=ID;
            }
            int x = tmpx[npc[ID].kier()];
            int y = tmpy[npc[ID].kier()];
            if (npc[ID].czy_dlugi() && npc[ID].x+x>=0 && npc[ID].y+y>=0 && npc[ID].x+x<m1[0].size() && npc[ID].y+y<m1[0].size() && m1[4][npc[ID].x+x][npc[ID].y+y]==-1){
                m1[4][npc[ID].x+x][npc[ID].y+y]=ID;
            }
            if (npc[ID].czy_dlugi() && npc[ID].popx+x>=0 && npc[ID].popy+y>=0 && npc[ID].popx+x<m1[0].size() && npc[ID].popy+y<m1[0].size() && m1[4][npc[ID].popx+x][npc[ID].popy+y]==-1){
                m1[4][npc[ID].popx+x][npc[ID].popy+y]=ID;
            }
            if (npc[ID].czyprzerwany_atak && SDL_GetTicks()-npc[ID].tatak>=npc[ID].tmaxatak){
                npc[ID].czyprzerwany_atak=0;
            }
        }
    }

    npceID.pop_back();
    for (int i=0; i<npceID.size();i++){
        int ID=npceID[i];
        if (npc[ID].hp<=0){
            npc[ID].zabij();
        }
        if (!npc[ID].czymartwy){
            bool gotowy= SDL_GetTicks()-npc[ID].tatak>npc[ID].tmaxatak && !npc[ID].czystun && npc[ID].sciezka2.empty() && SDL_GetTicks() - npc[ID].truchu > npc[ID].tmaxruch;
            if (gotowy){
                npc[ID].zach(m1,npc);
            }
            if (npc[ID].czyatak && npc[ID].ekw[0].empty() && gotowy){
                npc[ID].tatak=SDL_GetTicks();
                npc[ID].tmaxatak=1200;
                npc[ID].tmaxatak2=400;
            }
            if (npc[ID].czyatak && !npc[ID].ekw[0].empty() && gotowy){
                npc[ID].anim_ataku();
                npc[ID].atak(rand()%3==0, SDL_GetTicks());
            }
            if (!npc[ID].sciezka2.empty() && SDL_GetTicks() - npc[ID].truchu > npc[ID].tmaxruch){
                xy tmp=npc[ID].sciezka2.back();
                npc[ID].sciezka2.pop_back();
                if (!(m1[4][tmp.x][tmp.y]==-1 || m1[4][tmp.x][tmp.y]==m1[4][npc[ID].x][npc[ID].y]) || m1[2][tmp.x][tmp.y]!=-1){
                    npc[ID].sciezka2.clear();
                }else{
                    npc[ID].popx=npc[ID].x;
                    npc[ID].popy=npc[ID].y;
                    npc[ID].x=tmp.x;
                    npc[ID].y=tmp.y;
                    npc[ID].tmaxruch=npc[ID].ruch1-((bool)(npc[ID].czydodge))*npc[ID].ruch1/2;
                    npc[ID].czydodge=0;
                    npc[ID].truchu=SDL_GetTicks();
                }
            }

            if (npc[ID].czyatak && SDL_GetTicks()-npc[ID].tatak>npc[ID].tmaxatak2){
                npc[ID].czyatak=0;
                npc[ID].czy_anim_ataku=0;
                xy cel_ataku = npc[ID].xy_ataku;
                if (m1[4][cel_ataku.x][cel_ataku.y]!=-1 && relacja[npc[ID].strona][npc[m1[4][cel_ataku.x][cel_ataku.y]].strona]<0){
                    atak(ID,m1[4][cel_ataku.x][cel_ataku.y]);
                }
            }
        }


        /*m1[4][npc[ID].x+(npc[ID].zwr_hitbox().x_prawy>1)][npc[ID].y]=ID;
        if (SDL_GetTicks()-npc[ID].truchu>npc[ID].tmaxruch && npc[ID].tmaxruch){
            m1[4][npc[ID].popx][npc[ID].popy]=ID;
            m1[4][npc[ID].x+(npc[ID].zwr_hitbox().x_prawy>1)][npc[ID].y]=ID;
        }*/
    }
}



int miasto1(int skad, vector<vector <int> > m1[], int gdzie, bool czywiecznanoc, bool czyswiat){
    cout << "pocz"<<endl;
    npc[0].tekstura=0;
    npc[0].h=1.7;
    przezr.clear();
    czyzmianamiasto0=1;
    txmiasto=SDL_CreateTexture(Rend, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,KRATKA*(2*ZASx+3), KRATKA*(2*ZASy+3));
    txmiasto0=SDL_CreateTexture(Rend, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,KRATKA*(2*ZASx+3), KRATKA*(2*ZASy+3));
    npc[0].nrubr=0;

    WYMx=m1[0].size();
    WYMy=m1[0][0].size();
    cout << "test"<<m1[3].size()<<" "<<WYMy<<endl;
    m1[3][7][10]=dodnam1(stworzjedz(0.50,100,1000,0,0,0,-1,-1,11,-1,-1,11,1),m1[3][7][10],7,10,m1);
    m1[3][7][10]=dodnam1(stworzjedz(0.60,100,1000,0,0,0,-1,-1,11,-1,-1,11,1),m1[3][7][10],7,10,m1);
    m1[3][7][10]=dodnam1(stworzjedz(0.60,100,1000,0,0,0,-1,-1,11,-1,-1,11,1),m1[3][7][10],7,10,m1);
    m1[3][8][10]=dodnam1(stworzjedz(0.50,100,1000,0,0,0,-1,-1,11,-1,-1,11,1),m1[3][8][10],8,10,m1);
    momprzedm=SDL_GetTicks();
    npc[0].gdzie=gdzie;
    xy poczlinitmp, konlinitmp; //linia tmp, do usuniecia
    if (skad==0){
        npc[0].x=7;
        npc[0].y=10;
    }
    bool czek=1;
    int rozmowa=0;
    int rozmowa2=0;
    bool tmprozm=1;
    bool ignorujenter=1;
    bool ignorujgranice=1;
    bool ignoruj_spacje;
    Uint32 t4,t5,ttest,ttest2=SDL_GetTicks(),tluku=SDL_GetTicks();
    Uint32 t_L_myszy=SDL_GetTicks();
    bool b_L_myszy=0;
    bool b_R=0;
    bool czy_L_atak=0;
    xy interakcja;
    t4= SDL_GetTicks();
    t5= SDL_GetTicks();
    ttest=(SDL_GetTicks()-ttest2)+w[4][1];
    int dnitest=w[4][2];
    ttest-=(w[4][3]+w[4][4])*(ttest/(w[4][3]+w[4][4]));
    bool czymapa=0, czyekw=0, czypauza=0, czypodn2=0,czynoc=0;
    bool przyciskekw=0;
    int poppodn;
    int poppodnx;
    int pozycjexy[4]={WYMx-1,WYMy-1,0,0};
    if (skad==2 || skad==4){
        npc[0].y=pozycjexy[skad-1];
        if (pozycje[skad-1]!=-1){
            npc[0].x=pozycje[skad-1];
        }
        if (skad==2){
            npc[0].popy=64;
        }
        if (skad==4){
            npc[0].popy=-1;
        }

    }
    if (skad==3 || skad==1){
        npc[0].x=pozycjexy[skad-1];
        if (pozycje[skad-1]!=-1){
            npc[0].y=pozycje[skad-1];
        }
        if (skad==1){
            npc[0].popx=64;
        }
        if (skad==3){
            npc[0].popx=-1;
        }
    }
    stretchRect.x = ZASx*KRATKA;
    stretchRect.y = ZASy*KRATKA;
    SDL_Rect pozaanim;
    xy zle;
    zle.x=-1;
    zle.y=-1;
    vector <int> npceID;
    for (int i=1; i<npc.size(); i++){
        npceID.push_back(i);
    }
    xy pozpodn;
    pozpodn.x=-1;
    int podno;
    cout << "Jest tu "<<npceID.size()<<" NPC"<<endl;
    for (int i=0; i<npceID.size();i++){
        cout << npceID[i]<<" "<< npc[npceID[i]].zasieg<<" "<< npc[npceID[i]].predkat<<" "<< npc[npceID[i]].x<<" "<< npc[npceID[i]].y<<" "<< npc[npceID[i]].minx<<" "<< npc[npceID[i]].maxx<<" "<< npc[npceID[i]].miny<<" "<< npc[npceID[i]].maxy<<" "
        << npc[npceID[i]].ruch1<<" "<< npc[npceID[i]].ruch2<<" "<< npc[npceID[i]].gdzie<<" "<<endl;
    }

    ttest2=SDL_GetTicks();
    int kreator1=-1;
    int kreator2=-1;
    for (int i=0; i<npc[0].ef.size();i++){
        cout << npc[0].ef[i].obr<<" "<< npc[0].ef[i].czest<<" "<< npc[0].ef[i].zwobr<<" "<< npc[0].ef[i].tef<<" "<< npc[0].ef[i].t<<" "<< npc[0].ef[i].ile<<endl;
        npc[0].ef[i].t=SDL_GetTicks();
    }
    ttest2=SDL_GetTicks();
    xy zaznkr;
    zaznkr.x=-1;
    Uint32 tpocisk=0;
    Uint32 tpocisktmp=0;
    bool myszpocisk=(GetKeyState(VK_RBUTTON) & 0x80);


    generuj_przeciwnika(wilk, npceID, m1);

    while( czek ){
        DEBUG cout << "test1"<<endl;
        int roz=SDL_GetTicks()-ttest2;
        w[4][1]+=roz*(1-czypauza);
        ttest2=SDL_GetTicks();
        if(w[4][1]/(dzien)){
            w[4][2]+=(w[4][1]/dzien);
            w[4][1]%=(w[4][3]+w[4][4]);
        }
        if (czypauza){
            t4+=roz;
        }
        SDL_Delay(1);
        DEBUG cout << "test1.2"<<endl;
        przedmczek(czypauza,m1);

        if (npc[0].czyatak && SDL_GetTicks()-npc[0].tatak>npc[0].tmaxatak2){
            npc[0].czyatak=0;
            npc[0].czy_anim_ataku=0;
            int x = npc[0].x+tmpx[(npc[0].kierataku+1)%4];
            int y = npc[0].y-tmpy[(npc[0].kierataku+1)%4];
            if (m1[4][x][y]!=-1){
                atak(0,m1[4][x][y]);
            }
        }
        if (npc[0].x==0 && !ignorujgranice && !czyswiat){
            return 1;
        }
        if (npc[0].x==63 && !ignorujgranice && !czyswiat){
            return 3;
        }
        if (npc[0].y==0 && !ignorujgranice && !czyswiat){
            return 2;
        }
        if (npc[0].y==63 && !ignorujgranice && !czyswiat){
            return 4;
        }
        if (npc[0].x!=0 && npc[0].x!=63 && npc[0].y!=0 && npc[0].y!=63){
            ignorujgranice=0;
        }

        DEBUG cout << "test2"<<endl;
        if (!czyekw){
            ekwwybr=0;
            for (int i=0; i<bufer.size();i++){
                m1[3][npc[0].x][npc[0].y]=dodnam1(bufer[i],m1[3][npc[0].x][npc[0].y],npc[0].x,npc[0].y,m1);
            }
            bufer.clear();
            czyzmianaekw=1;
        }
        if (rozmowa2 && !(GetKeyState(VK_LBUTTON) & 0x80)&&!tmprozm){
            tmprozm=1;
        }
        if (!(GetKeyState(VK_LBUTTON) & 0x80)){
            ignorujmysz=0;
        }
        bool czyniezaj=npc[0].sciezka2.empty()&&!czymapa&&!czyekw && !rozmowa && !czysklep && tmprozm && SDL_GetTicks()-npc[0].tatak>npc[0].tmaxatak && npc[0].poziomblok<=0 && SDL_GetTicks()>t4 && SDL_GetTicks()-npc[0].truchu>=npc[0].tmaxruch && SDL_GetTicks()-npc[0].tparada>=npc[0].czasparady() && !npc[0].czystun;
        const Uint8* stan = SDL_GetKeyboardState( NULL );
        int kodyWASD[4]={SDL_SCANCODE_A,SDL_SCANCODE_S,SDL_SCANCODE_D,SDL_SCANCODE_W};
        if (czyniezaj){
            for (int i=0; i<4;i++){
                if (stan[kodyWASD[i]] && npc[0].y+tmpy[i]>=0 && npc[0].y+tmpy[i]<WYMy && npc[0].x+tmpx[i]<WYMx && npc[0].x+tmpx[i]>=0){
                    npc[0].sciezka2=npc[0].sciezka1({npc[0].x+tmpx[i],npc[0].y+tmpy[i]},{npc[0].x+tmpx[i],npc[0].y+tmpy[i]},m1);
                    break;
                }
            }
        }
        for (int i=0; i<4;i++){
            if (stan[kodyWASD[i]] && npc[0].sciezka2.size()>1){
                npc[0].sciezka2.clear();
            }
        }
        if (stan[SDL_SCANCODE_M]){
            czymapa=1;
            mapa(m1);
        }else{
            czymapa=0;
        }
        if (przyciskekw==0 && stan[SDL_SCANCODE_I]==1){
            czyekw=!czyekw;
        }
        przyciskekw=stan[SDL_SCANCODE_I];
        if (stan[SDL_SCANCODE_P]){
            czypauza=1;
        }else{
            czypauza=0;
        }
        if (npc[0].ekw[1].empty()){
            if (stan[SDL_SCANCODE_SPACE] && czyniezaj){
                npc[0].dodge(m1);
            }
            npc[0].poziomblok=0;
            npc[0].tblok=SDL_GetTicks();
        }else{
            if (stan[SDL_SCANCODE_SPACE]){
                if (!npc[0].ekw[0].empty() && npc[0].ekw[0][0].inty[0]==0 && (czyniezaj || npc[0].poziomblok>0)){
                    if (((!npc[0].ekw[1].empty() && npc[0].ekw[1][0].typ==4) )){
                        npc[0].tmaxblok=npc[0].ekw[1][0].dou[1]*1000;
                    }
                    if (npc[0].ekw[1].empty()){
                        npc[0].tmaxblok=200;
                    }
                    npc[0].poziomblok=max(0,npc[0].poziomblok);
                    npc[0].poziomblok+=SDL_GetTicks()-npc[0].tblok;
                }
            }else{
                npc[0].poziomblok=min(npc[0].tmaxblok,npc[0].poziomblok);
                npc[0].poziomblok-=SDL_GetTicks()-npc[0].tblok;
            }
           npc[0].tblok=SDL_GetTicks();
        }

        if (b_L_myszy==0 && GetKeyState(VK_LBUTTON) & 0x80 && SDL_GetTicks()-t_L_myszy<DOUBLECLICKms){
            npc[0].atak(1,t_L_myszy);
            czy_L_atak=0;
        }
        if (czy_L_atak && SDL_GetTicks()-t_L_myszy>=DOUBLECLICKms){
            npc[0].atak(0,t_L_myszy);
            czy_L_atak=0;
        }

        if (b_L_myszy==0 && GetKeyState(VK_LBUTTON) & 0x80 && czyniezaj ){
            czy_L_atak=1;
            npc[0].anim_ataku();
        }

        if (b_L_myszy==0 && GetKeyState(VK_LBUTTON) & 0x80 && czyniezaj){
            t_L_myszy=SDL_GetTicks();
        }
        b_L_myszy=GetKeyState(VK_LBUTTON) & 0x80;


        if (GetKeyState(VK_RBUTTON) & 0x80&&czyniezaj && SDL_GetTicks()-npc[0].tparada>npc[0].cdparady() && !npc[0].ekw[0].empty() && npc[0].ekw[0][0].typ==0){
            npc[0].czyparada=1;
            npc[0].tparada=SDL_GetTicks();
        }
        if (SDL_GetTicks()-npc[0].tparada>=npc[0].czasparady()){
            npc[0].czyparada=0;
        }
        npc[0].tblok=SDL_GetTicks();
        if (stan[SDL_SCANCODE_LCTRL] && stan[SDL_SCANCODE_X] && kreator1==-1){
            cout << "podaj typ:"<<endl;
            cout << "0 -terrain"<<endl;
            cout << "1 -background"<<endl;
            cout << "2 -wall"<<endl;
            cout << "5 -foreground"<<endl;
            cin >> kreator1;
            cout << "podaj numer tekstury:"<<endl;
            cin >> kreator2;
            kreator2--;
            if (kreator1 == 0){
                int tmp=0;
                cout << "podaj kierunek obrotu od 0 od 3"<<endl;
                cin >> tmp;
                kreator2=4*kreator2+tmp;

            }
        }
        if (!b_R && stan[SDL_SCANCODE_R] && kreator1==0){
            m1[kreator1][zaznkr.x][zaznkr.y]++;
            if (m1[kreator1][zaznkr.x][zaznkr.y]%4==0){
                m1[kreator1][zaznkr.x][zaznkr.y]-=4;
            }
        }
        b_R=stan[SDL_SCANCODE_R];
        if (stan[SDL_SCANCODE_LCTRL] && stan[SDL_SCANCODE_Z]){
            kreator1=-1;
            kreator2=-1;
        }
        if (stan[SDL_SCANCODE_LSHIFT]){
            cout << zaznkr.x<<" "<<zaznkr.y<<endl;
        }
        if (stan[SDL_SCANCODE_RETURN] && !ignorujenter){
            return 0;
        }
        if (stan[SDL_SCANCODE_S] && stan[SDL_SCANCODE_LCTRL]){
            zapisz_mape(m1,xnasw,ynasw,czyswiat);
        }
        if (!stan[SDL_SCANCODE_SPACE]){
            ignoruj_spacje=0;
        }
        if (ignorujenter && !stan[SDL_SCANCODE_RETURN]){
            ignorujenter=0;
        }

        if (npc[0].czyruch()){
            rozmowa2=0;
        }
        if (kreator1!=-1){
            cout << "tryb kreatora ctrl+Z aby wyjsc ";
            cout << kreator1<<" "<<kreator2<<endl;
            if ((GetKeyState(VK_LBUTTON) & 0x80)){
                m1[kreator1][zaznkr.x][zaznkr.y]=kreator2;
            }
            if ((GetKeyState(VK_RBUTTON) & 0x80)){
                m1[kreator1][zaznkr.x][zaznkr.y]=-1;
            }
        }
        SDL_PollEvent(&e);
        if( e.type == SDL_QUIT ){
            czek=0;
            close();
            return -1;
        }
        int xm,ym;
        SDL_GetMouseState(&xm, &ym);

        if (czyniezaj && !ignorujmysz && czyniezaj && !npc[0].ekw[0].empty() && npc[0].ekw[0][0].typ==1 && !npc[0].ekw[5].empty()){
            if ((GetKeyState(VK_RBUTTON) & 0x80)){
                tpocisk+=SDL_GetTicks()-tpocisktmp;
                tpocisktmp=SDL_GetTicks();
            }
            if (myszpocisk && !(GetKeyState(VK_RBUTTON) & 0x80) && tpocisk>(Uint32)npc[0].ekw[0][0].dou[2]*1000){
                poci p(xm,ym,pozgr,npc[0], 0);
                tluku=min(SDL_GetTicks(),tluku);
                pociski.push_back(p);
            }
            if (!(GetKeyState(VK_RBUTTON) & 0x80)){
                tpocisk=0;
                tpocisktmp=SDL_GetTicks();
            }
            myszpocisk=(GetKeyState(VK_RBUTTON) & 0x80);
        }else{
            tpocisk=0;
            tpocisktmp=SDL_GetTicks();
        }
        if (rozmowa2 &&!ignorujmysz&&(GetKeyState(VK_LBUTTON) & 0x80)&& ym>=3*WYS/4+WYS-maxi-wyspask){
            rozmowa2=0;
            ignorujmysz=1;
        }
        if (kreator1==-1 && e.type == SDL_MOUSEBUTTONDOWN &&(GetKeyState(VK_LBUTTON) & 0x80)&&czyniezaj && !czypodn && !czypodn2 && tmprozm && !ignorujmysz && (!rozmowa2 || (rozmowa2 && ym<3*WYS/4+WYS-maxi-wyspask))){
            npc[0].sciezka2=npc[0].sciezka1(zaznkr,zaznkr,m1);
            ignorujmysz=1;
            mysza2=(GetKeyState(VK_LBUTTON) & 0x80);
        }
        if (kreator1==-1 && e.type == SDL_MOUSEBUTTONDOWN && !npc[0].sciezka2.empty() &&(GetKeyState(VK_LBUTTON) & 0x80)&& !ignorujmysz){
            npc[0].sciezka2.clear();
            ignorujmysz=1;
        }
        DEBUG cout<<"test3"<<endl;
        if (!npc[0].sciezka2.empty()){
            interakcja.x=-1;
        }
        if (interakcja.x!=-1){
            interakcjaMapa(interakcja.x,interakcja.y,m1[0][interakcja.x][interakcja.y],m1[1][interakcja.x][interakcja.y],0);
            interakcja.x=-1;
        }
        if (czywiecznanoc){
            czynoc=1;
            SDL_SetTextureAlphaMod(CzKw, 128);
            SDL_SetTextureAlphaMod(txanim[0][0],64);
        }else{
            if (w[4][1]<=w[4][3]){
                SDL_SetTextureAlphaMod(CzKw,0);
//                SDL_SetTextureAlphaMod(txnpc[0],255);
                SDL_SetTextureAlphaMod(txanim[0][0],128);
                czynoc=0;
            }else{
                czynoc=1;
                SDL_SetTextureAlphaMod(CzKw, 128);
                SDL_SetTextureAlphaMod(txanim[0][0],64);
            }
        }
        if (czymapa || czyekw || rozmowa || czysklep){
            npc[0].sciezka2.clear();
        }
        DEBUG cout << "test3.5"<<endl;
        if (!npc[0].sciezka2.empty() && SDL_GetTicks()>t4){
            t4=SDL_GetTicks()+PREDKOSC;
            xy tmp=npc[0].sciezka2.back();
            npc[0].sciezka2.pop_back();
            if (m1[2][tmp.x][tmp.y]!=-1 || m1[4][tmp.x][tmp.y]!=-1){
                zle=tmp;
                zle=tmp;
                npc[0].sciezka2.clear();
            }else{
                npc[0].popx=npc[0].x;
                npc[0].popy=npc[0].y;
                npc[0].x=tmp.x;
                npc[0].y=tmp.y;
                npc[0].tmaxruch=PREDKOSC-((bool)(npc[0].czydodge))*PREDKOSC/2;
                npc[0].czydodge=0;
                npc[0].truchu=SDL_GetTicks();
                czyzmianamiasto0=1;
            }
        }
        zachowanieNPC(npceID,m1);
        if (npc[0].hp<=0){
            MessageBox(NULL, (LPCWSTR)"U died, lol", (LPCWSTR)"git gud",MB_ICONERROR);
            return -1;
        }
        DEBUG cout << "test4"<<npc[0].x<<" "<<npc[0].y<<endl;
        if (SDL_GetTicks()>t5){
            //obliczpoci(pociski,m1);
            t5=SDL_GetTicks()+20;
            ttest=SDL_GetTicks();
            rendmape(m1,max(0,npc[0].x-ZASx)+((int)m1[0].size()-(ZASx)-npc[0].x-1)*((int)((int)m1[0].size()-(ZASx)-npc[0].x-1)<0),
            max(0,npc[0].y-ZASy)+((int)m1[0].size()-(ZASy)-npc[0].y-1)*((int)((int)m1[0].size()-(ZASy)-npc[0].y-1)<0),zaznkr);
            DEBUG cout << "test5"<<endl;
            int x=-KRATKA;
            if (SDL_GetTicks()-npc[0].truchu<npc[0].tmaxruch && npc[0].popx>=ZASx && npc[0].x>=ZASx && (int)m1[0].size()-(ZASx)-npc[0].x-1>=0 && (int)m1[0].size()-(ZASx)-npc[0].popx-1>=0){
                x=-((npc[0].x-npc[0].popx)*((int)((KRATKA*(SDL_GetTicks()-npc[0].truchu))/npc[0].tmaxruch)-KRATKA))*(bool)(npc[0].x-npc[0].popx)-KRATKA;
            }
            int y=-KRATKA;
            if (SDL_GetTicks()-npc[0].truchu<npc[0].tmaxruch && npc[0].popy>=ZASy && npc[0].y>=ZASy && (int)m1[0].size()-(ZASy)-npc[0].y-1>=0 && (int)m1[0].size()-(ZASy)-npc[0].popy-1>=0){
                y=-((npc[0].y-npc[0].popy)*((int)((KRATKA*(SDL_GetTicks()-npc[0].truchu))/npc[0].tmaxruch)-KRATKA))*(bool)(npc[0].y-npc[0].popy)-KRATKA;
            }
            pozgr.x+=x+KRATKA/2;
            pozgr.y+=y+7*KRATKA/4;
            int xm, ym;
            SDL_GetMouseState(&xm,&ym);
            npc[0].popkier=atan((double)(ym-pozgr.y-3*KRATKA/4)/(double)(xm-pozgr.x+(xm==pozgr.x)))*180/3.14+90;
            if (xm-pozgr.x<0){
                npc[0].popkier+=180;
            }
            npc[0].popkier= ((npc[0].popkier+45)/90)%4;
            npc[0].kierataku=npc[0].popkier;
            zaznkr.x=(xm-x-KRATKA)/KRATKA + max(0,npc[0].x-ZASx)+((int)m1[0].size()-(ZASx)-npc[0].x-1)*((int)((int)m1[0].size()-(ZASx)-npc[0].x-1)<0);
            zaznkr.y=(ym-y-KRATKA)/KRATKA + max(0,npc[0].y-ZASy)+((int)m1[0].size()-(ZASy)-npc[0].y-1)*((int)((int)m1[0].size()-(ZASy)-npc[0].y-1)<0);
            SDL_Rect poz={x,y,(2*ZASx+3)*KRATKA,(2*ZASy+3)*KRATKA};
            SDL_RenderCopy(Rend,txmiasto,NULL,&poz);
            if (czymapa || czyekw || czysklep){
                SDL_SetTextureAlphaMod(CzKw,196);
                SDL_Rect tmp ={0,0,(2*ZASx+1)*KRATKA,(2*ZASy+1)*KRATKA};
                SDL_RenderCopy(Rend,CzKw,NULL,&tmp);
            }
            if (m1[3][zaznkr.x][zaznkr.y]){
                if (!czypodn){
                    pozpodn.x=(zaznkr.x-(max(0,npc[0].x-ZASx)+((int)m1[0].size()-(ZASx)-npc[0].x-1)*((int)((int)m1[0].size()-(ZASx)-npc[0].x-1)<0))+1)*KRATKA;
                    pozpodn.y=(zaznkr.y-(max(0,npc[0].y-ZASy)+((int)m1[0].size()-(ZASy)-npc[0].y-1)*((int)((int)m1[0].size()-(ZASy)-npc[0].y-1)<0))+1)*KRATKA;
                    podno=m1[3][zaznkr.x][zaznkr.y];
                }
            }else{
                if (!czypodn){
                    pozpodn.x=-1;
                }
                poppodn=podno;
            }
            poppodnx=pozpodn.x;
            if (tpocisk){
                SDL_SetRenderDrawColor(Rend,0,0,0,min((Uint32)255,(Uint32)(256*(tpocisk)/(npc[0].ekw[0][0].dou[2]*1000))));
                SDL_RenderDrawLine(Rend,pozgr.x,pozgr.y+4*KRATKA/4,xm,ym);
                if (tpocisk<(npc[0].ekw[0][0].dou[2]*1000)){
                    SDL_SetRenderDrawColor(Rend,255,0,0,128);
                }
                if (tpocisk>=(npc[0].ekw[0][0].dou[2]*1000)){
                    SDL_SetRenderDrawColor(Rend,0,255,0,255);
                }
                SDL_RenderDrawLine(Rend,pozgr.x,pozgr.y,xm,ym);

            }
            DEBUG cout << "test7"<<endl;
            wartosci();

            //cout << "ok3";
            DEBUG cout << "test8"<<endl;
            if (rozmowa){
                int tmp=rozmowaNPC(rozmowa,rozmtmp);
                if (!tmp){
                    rozmowa2=rozmowa;
                    trozm2=SDL_GetTicks();
                    tmprozm=0;
                    ignorujmysz=1;
                }
                rozmowa=rozmowa*tmp;
            }else if (rozmowa2){
                rozmowaNPC(rozmowa2,rozmtmp);
            }
            if (!rozmowa && !rozmowa2){
                rozmtmp=0;
                maxi=0;
                czyzmianarozm=1;
            }
            if (czyekw){
                ekwipunek();
            }
            if (pozpodn.x!=-1){
                //podn(0,podno, pozpodn);
            }else{
                czypodn=0;
            }
            if (czysklep){
                sklep(czysklep);
            }
            SDL_SetRenderDrawColor(Rend,128,0,0,128);
            SDL_RenderDrawLine(Rend,poczlinitmp.x,poczlinitmp.y,konlinitmp.x,konlinitmp.y);
            if (!czymapa&&!czyekw && !czysklep){
                SDL_RenderPresent( Rend );
            }
            //cout << m1[4][zaznkr.x][zaznkr.y]<<" "<<zaznkr.x<<" "<<zaznkr.y<<endl;
        }

    }
}
