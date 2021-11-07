#include <SDL.h>
#include <time.h>
#include <windows.h>
#include <sstream>
#include <vector>
#include <map>
#include <winuser.h>
#include <SDL_ttf.h>
#include <SDL_image.h>


#include "structy.h"
#include "it.h"
#include "napis.h"
#include "npc.h"

#include "poci.h"


using namespace std;

#define DEBUG if (0)

#define endl " >"<<__FUNCTION__<<"<"<<endl

int KRATKA;
int SZER;
int WYS;
int WYMx, WYMy;
const int OPWYJ=3000;
int ZASx = 8;
int ZASy = 7;
const int PREDKOSC=350;
const int ILOSCw=8;
int dzien;
int tmpx[4]={-1,0,1,0};
int tmpy[4]={0,1,0,-1};
vector <int> w[ILOSCw];
int liczzap=0;
SDL_Window* window = NULL;
SDL_Surface* screenSurface = NULL;
SDL_Texture* CzKw;
SDL_Texture* jezioro;
SDL_Texture* jezioro2;
SDL_Event e;
SDL_Renderer* Rend=NULL;
SDL_Rect stretchRect;
SDL_Surface* KRA;
TTF_Font* czcionka = NULL;
vector <vector <SDL_Texture*> > txit;
bool tmpekw=0;
vector <vector <SDL_Texture*> > txnpc;
vector <vector <hitbox> > hitboxnpc;
vector <SDL_Texture*> txubr;
vector <SDL_Texture*> txoczy;
vector <SDL_Texture*> txwlosy;
vector <SDL_Texture*> txef;
vector <vector <SDL_Texture*> > txanim;
vector <int> txanimt;
vector <vector <SDL_Texture*> > txtr;
vector <int> txtrt;
vector <vector <SDL_Texture*> > txbg;
vector <int> txbgt;
vector <vector <SDL_Texture*> > txw;
vector <int> txwt;
vector <vector <SDL_Texture*> > txfw;
vector <int> txfwt;
int rozmtmp=0;
int relacja[5][5];
int u=300;
int xnasw, ynasw;
vector<vector <int> > swiat[6];
string bonusystr [7]={"damage","armor piercing","attack speed" ,"critcal hit chance","critical hit damage","movement speed","dodge speed"};
string bonusypoz_stopnstr [7]={"minimally","slightly","noticeably","remarkably","evidently","exceptionally","mightily"};
string bonusyneg_stopnstr [7]={"minimally","slightly","noticeably","remarkably","evidently","painfully","insanely"};
vector <int> bonusyint_critch ={2,4,7,10,15,20,35};
vector <int> bonusyint_critdmg ={5,10,20,30,50,70,95};
vector <int> bonusyint_procenty ={5,10,20,30,50,70,95};
vector <napis> dowypisania;
vector <efestrz> efstrz;
vector <vector <it> > przedm;
vector <xy> pozprzedm;
Uint32 momprzedm;
vector <NPC> npc;
vector <it> podnitem;
vector <SDL_Texture*> podntx;
vector <xy> rozmtx;
xy podnwym;
bool mysza1=0;
bool ekwmyszaP=0;
bool ekwmyszaL=0;
int ekwwybr=0;
int ekwwybr2=0;
vector <it> bufer;
vector <string> stringi={"hand","shield","sword sheath", "belt","armor","arrows","satchel","back 1","back 2"};
vector <xy> xyy={{5,2},{4,3},{5,2},{4,1},{4,3},{2,1},{2,2},{5,2},{5,2}};
SDL_Texture* ekwtx;
vector <SDL_Rect> ekwpole;
vector <SDL_Rect> ekwpole2;
bool czyzmianaekw=1;
int xpl, ypl;
SDL_Texture* skltx;
SDL_Rect sklzamkn;
int czysklep=0;
bool ignorujmysz=0;
bool czyzmianaskl=1;
vector <SDL_Rect> sklrozm;
vector <SDL_Rect> sklrozm2;
bool sklmyszaP=0;
bool sklmyszaL=0;
vector <vector <int> > sklept;
vector <vector <int> > sklept2;
vector <it> sklprzedm;
vector <tuple<it,int,int> > sklprzedm2;
bool mysza2;
int maxi=0;
int wysrozm;
bool czyzmianarozm=1;
bool czyzmianarozm2=1;
SDL_Texture* txrozm;
Uint32 trozm;
Uint32 trozm2;
vector <pair <int, SDL_Rect> > rozmrozm;
vector <pair<SDL_Rect,int> > rozmrozm2;
bool czek=1;
int wyspask;
bool przycisk[4]={0};
vector <pair<string,bool> > rozmef;
bool czypodn=0;
vector <poci> pociski;
vector <tuple <xyd, double,double,double, it> > pociskiwbite;
int pozycje[4];
SDL_Texture* txmiasto;
SDL_Texture* txmiasto0;
bool czyzmianamiasto0=1;
xy pozgr;
map<pair<int,int>, pair<int,bool> > przezr;



void close();

SDL_Texture* txL (string nazwa);

bool wzapis();
bool wodczyt(bool czyorig);

bool wczytajtxterrain();
bool wczytajtxnpc();

void zapisz_mape(vector <vector<int> > m1[], int x, int y, bool czyswiat);
bool odczyt_mapy(vector <vector<int> > m1[], int x, int y, bool czyswiat);

//podtyp 0 miecz, typ 1 palka, typ 2 sztylet
it stworzbron (int podtyp, double dmg, double ap, double as,int tekstura, int t, int maxt, int wym, int value,int bcrch=0,int bcrdmg=0, int bspd=0, int bds=0);
it stworzluk (double dmg, double ap, double cd,double prd, int tekstura, int t, int maxt, int wym, int value,int bcrch=0,int bcrdmg=0, int bspd=0, int bds=0);
it stworzstrz (int durability, int efnum,int effade, int tekstura, int t, int maxt, int wym, int value,int bdmg=0, int bap=0, int bcrch=0, int bcrdmg=0);
it stworzzbroje (double arm, int tekstura, int t, int maxt, int wym, int value, int bdmg=0,int bap=0, int bas=0, int bmovspd=0, int bds=0);
it stworztarcze (double arm, double bs, int tekstura, int t, int maxt, int wym, int value, int bdmg=0,int bap=0, int bas=0, int bmovspd=0, int bds=0);
it stworzjedz (double heal, double coile, double naile,int zwsily, int zwdex, int tekstura, int t, int maxt, int wym, int value, int bdmg=0,int bap=0, int bas=0, int bcrch=0, int bcrdmg=0, int bmovspd=0, int bds=0);
it stworzitnic ();



int stworzNPC(NPC npctmp);

void stworzmape (vector <vector <int> > m1[],int x,int y, int biom);

int miasto1(int skad, vector<vector <int> > m1[], int gdzie, bool czywiecznanoc, bool czyswiat);







int main(int argc, char* args[]){
SDL_Init( SDL_INIT_VIDEO );
TTF_Init();
ios_base::sync_with_stdio(0);
SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS,1);
SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES,16);
SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"1");
relacja[0][2]=1;
relacja[2][0]=1;
relacja[1][0]=-1;
relacja[0][1]=-1;
relacja[0][0]=2;
relacja[1][1]=2;
relacja[2][2]=2;
czcionka=TTF_OpenFont("czcionka1.ttf",22);
srand(time(NULL)*1000);
int x = GetSystemMetrics(SM_CXSCREEN);
int y = GetSystemMetrics(SM_CYSCREEN);
wodczyt(0);
npc.resize(1);
cout << "w[1][1]"<<w[1][1]<<endl;
ZASx=w[3][1];
ZASy=w[3][2];
w[4][4]=0;
dzien=w[4][3]+w[4][4];
cout << w[4][1]<<" "<<w[4][2];
cout << "obecnie ZASx to: "<<ZASx<<" ZASy: "<<ZASy<< " wprowadz nowe, badz przepisz stare wartosci\n";
cin >> ZASx;
cin >> ZASy;
cout << ZASx <<" "<< ZASy<<endl;
SZER=x;
WYS=y;
WYS-=50;
stretchRect.x = 0;
stretchRect.y = 0;
stretchRect.w = SZER/((2*ZASx+1));
stretchRect.h = WYS/((2*ZASy+2));
stretchRect.w = min (stretchRect.w,stretchRect.h);
stretchRect.h = min (stretchRect.w,stretchRect.h);
KRATKA = stretchRect.w;
KRA=SDL_CreateRGBSurface(0,KRATKA,KRATKA,32,0,0,0,0);
SZER=KRATKA*((2*ZASx+1));
WYS=KRATKA*((2*ZASy+1));
x = GetSystemMetrics(SM_CXSCREEN);
y = GetSystemMetrics(SM_CYSCREEN);
cout << x<< " "<<y<<endl;
cout << KRATKA<<endl;
vector <vector <bool> > sw_czygenerowane;
for (int k=0; k<6;k++){
    swiat[k].resize(64);
    if (k==0){
        sw_czygenerowane.resize(64);
    }
    for (int i=0; i<64;i++){
        if (k==0){
            sw_czygenerowane[i].resize(64,1);
        }
        swiat[k][i].resize(64);
        for (int j=0; j<64;j++){
            swiat[k][i][j]=0-(k==1 || k==2 || k==4 || k==5);
        }
    }
}

//m1odczyt(m1,m2numer,0);
//m1odczyt(m3,m3numer,0);
cout << WYMx<<" "<<WYMy<<endl;
window = SDL_CreateWindow( "Jakas nazwa, kiedys wymysle",0, 25,SZER , WYS, SDL_WINDOW_SHOWN |  SDL_WINDOW_OPENGL);//tytu³ okna, pozycja x i y okna, rozmiar i pewnoœæ ¿e okno siê pojawi
//SDL_SetWindowFullscreen(window,SDL_WINDOW_FULLSCREEN_DESKTOP);
Rend=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);

ekwtx=SDL_CreateTexture(Rend, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,SZER, WYS);
skltx=SDL_CreateTexture(Rend, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,SZER, WYS);
txrozm=SDL_CreateTexture(Rend, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,SZER, 2*WYS);
SDL_SetTextureBlendMode(skltx,SDL_BLENDMODE_BLEND);
SDL_SetTextureBlendMode(ekwtx,SDL_BLENDMODE_BLEND);
SDL_SetTextureBlendMode(txrozm,SDL_BLENDMODE_BLEND);

SDL_SetRenderDrawColor( Rend, 0, 0, 0, 255 );
txanim.resize(7);
txubr.push_back(txL("tx/npc/ubr0.bmp"));
txoczy.push_back(txL("tx/npc/oczy0.bmp"));
txwlosy.push_back(txL("tx/npc/hair0.bmp"));

NPC tmp;
npc[0]=tmp;
npc[0].odczyt(0,0);
npc[0].predkat=1000;
npc[0].nrtekstury=0;

for (int i=0;i<7; i++){
stringstream ss;
ss << i;
string sciezka = ss.str();
string sciezka2="tx/txanim"+sciezka+".bmp";
txanim[i].push_back(txL(sciezka2.c_str()));
cout <<" wczytano "<< sciezka2<<endl;
}

wczytajtxterrain();
wczytajtxnpc();
CzKw = txL("tx/kwadrat1.bmp");
txit.resize(6);
for (int j=1;j<7;j++){
    w[7][1]=6;
    for (int i=0; i<w[7][j];i++){
            txit[j-1].resize(txit[j-1].size()+1);
            stringstream ss,ss2;
            ss << i;
            ss2<<j-1;
            string sciezka = ss.str();
            string sciezka3 = ss2.str();
            string sciezka2="tx/ite/ite"+sciezka3+sciezka+".bmp";
            cout <<" wczytano "<< sciezka2<<" na pozycji "<<j-1 << ","<<i<<endl;
            txit[j-1][i]=(txL(sciezka2.c_str()));
    }
}
//npc[1].wierz[0].tekst=;npc[1].wierz[0].czyj=1;npc[1].wierz[0].wtyp=0;

cout << "N"<<endl;
/*npc[1].n=15;
npc[1].e.clear();
npc[1].e.resize(npc[1].n,0);
npc[1].wierz.clear();
npc[1].wierz.resize(npc[1].n);
npc[1].g.clear();
npc[1].g.resize(npc[1].n);
npc[1].wierz[0].tekst="";npc[1].wierz[0].czyj=1;
npc[1].wierz[1].tekst = "hello stranger"; npc[1].wierz[1].czyj=1; npc[1].wierz[1].wymief.push_back(make_pair(1,0));
npc[1].wierz[2].tekst="hello friend";npc[1].wierz[2].czyj=1;
npc[1].wierz[3].tekst="I'm new here";npc[1].wierz[3].czyj=0;
npc[1].wierz[4].tekst="Hi, friend a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a ";npc[1].wierz[4].czyj=0;
npc[1].wierz[5].tekst="How are you? a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a ";npc[1].wierz[5].czyj=0;
npc[1].wierz[6].tekst="we do not carry swords in hands in our city, gtfo";npc[1].wierz[6].czyj=1; npc[1].wierz[6].wymief.push_back(make_pair(2,0));
npc[1].wierz[7].tekst="feel free to look around";npc[1].wierz[7].czyj=1;
npc[1].wierz[8].tekst="be safe";npc[1].wierz[8].czyj=1;
npc[1].wierz[9].tekst="Don't ever take that away Isn't it so easy Just to see the greed believe me It's enough to make you sick Well that's a gratifying feeling But the ceiling isn't going anywhere It's not depleting We need meaning so deceiving Half the world is what we're needing Pleading on our knees for healing Breathing out, the skin is peeling Breathing hard enough as it is Without that toxic gas you're feeding And conceding to this need That we have taken like a beating I'm disgusted with this lack of trust And now we're all retreating It's getting hard to sleep Without that fire burning deep Why would you take that away? So put us back in our place Spit in our face It makes the hurt better Don't ever take that away It's getting hard to sleep Without that fire burning deep Why would you take that away? So put us back in our place Spit in our face It makes the hurt better Don't ever take that away";npc[1].wierz[9].czyj=1;
npc[1].wierz[10].tekst="let's talk about something else";npc[1].wierz[10].czyj=0;
npc[1].wierz[11].tekst="now you have 5 seconds before the items on floor will disappear xd";npc[1].wierz[11].czyj=1;npc[1].wierz[11].wymief.push_back(make_pair(-2,0));
npc[1].wierz[12].tekst="show me your wares";npc[1].wierz[12].czyj=0;//npc[1].wierz[12].wymief.push_back(make_pair(-1,0));
npc[1].wierz[13].tekst="kajit has the wares only if you have money";npc[1].wierz[13].czyj=1;//npc[1].wierz[12].wymief.push_back(make_pair(-1,0));
npc[1].wierz[14].tekst="thank you";npc[1].wierz[14].czyj=1;npc[1].wierz[14].wymief.push_back(make_pair(-1,0));
npc[1].g[0].push_back(1);
npc[1].g[0].push_back(2);
npc[1].g[1].push_back(3);
npc[1].g[1].push_back(4);
npc[1].g[2].push_back(4);
npc[1].g[2].push_back(5);
npc[1].g[3].push_back(6);
npc[1].g[3].push_back(7);
npc[1].g[4].push_back(8);
npc[1].g[5].push_back(9);
npc[1].g[9].push_back(10);
npc[1].g[10].push_back(0);
npc[1].g[8].push_back(11);
npc[1].g[9].push_back(12);
npc[1].g[12].push_back(13);
npc[1].g[13].push_back(14);
npc[1].wspsprzedazy=3.50;
npc[1].wspkupna=0.50;*/
npc[0].predkat=1000;
//npc[0].eq.push_back(stworzbron(21.37,0,15,120,130,0.50,0.4,1,0,-1,-1,52,70));
//npc[0].eq.push_back(stworzbron(21.37,0,15,120,130,0.50,0.4,1,0,-1,-1,52,70));
//npc[0].eq.push_back(stworzitnic());
npc[0].rozmstrz=4;
npc[0].rozmjedz=3;
npc[0].ilstrz=8;
npc[0].hp=20;
//npc[0].hand=stworzbron(21.37,0,15,120,130,0.50,0.4,1,0,-1,-1,52,70);
//npc[0].hand2=stworzitnic();
cout << "POCHWA";
cout << npc[0].ekw[5].size();
cout << npc[0].dodajdoekw(stworzstrz(80,0,0,0,-1,-1,21,1,1,-1,2,5),5,1)<<endl;
npc[0].dodajdoekw(stworzstrz(80,0,0,0,-1,-1,21,1),5,1);
vector <int> ttttt;
ttttt.push_back(0);
ttttt.push_back(0);
ttttt.push_back(0);
ttttt.push_back(0);
ttttt.push_back(0);
ttttt.push_back(0);
npc[0].pl.t.push_back(ttttt);
npc[0].pl.t.push_back(ttttt);
npc[0].pl.t.push_back(ttttt);
npc[0].dodajdoekw(stworzbron(0,17.37,0.15,0.15,0,-1,-1,52,1,7,1,0),0,1);
npc[0].dodajdoekw(stworzjedz(4.20,0.25,1,0,0,0,-1,-1,11,1,0,0,3,1),6,1);
npc[0].dodajdoekw(stworzjedz(4.50,0.25,1,0,1,0,-1,-1,11,1,0,0,3,1),6,1);
npc[0].dodajdoekw(stworzluk(1.50,1.50,1,15,0,-1,-1,52,1,7,7),7,1);
npc[0].dodajdoekw(stworzzbroje(3.10,0,-1,-1,43,1,0,0,-5),4,1);
npc[0].dodajdoekw(stworztarcze(3.60,1.2,0,-1,-1,43,1,0,0,0,0,0),1,1);
npc[0].gold=450;
/*npc[1].nasprzedaz.push_back(stworzjedz(4.01,0.2,1.0,0,0,0,0,0,0,-1,-1,22,2));
npc[1].nasprzedaz.push_back(stworzjedz(0.01,0.2,1.0,0,0,0,0,0,0,-1,-1,11,0));
npc[1].nasprzedaz.push_back(stworzzbroje(3.50,1,0,0,1,1,0,-1,-1,43,1));
npc[1].nasprzedaz.push_back(stworztarcze(21.37,0.2,1.0,1,0,0,0,1,0,-1,-1,43,1));*/
efestrz efe;
efe.ef.ID=1;
efe.ef.czest=10000;
efe.ef.tef=10000;
efe.ef.obr=1.5;
efe.ef.zwobr=0;
efe.ef.ile=50000;
efe.fade=5;
efe.nazwa="poison";
efe.tekstura=0;
efstrz.push_back(efe);
txef.push_back(txL("tx/efe/efe0.bmp"));
cout << "miasto wczytane"<<endl;
cout << " wczytano wszystko"<<endl;
cout << "TEKSTURY:";
cout << ZASx <<" "<< ZASy<<";" <<SZER << " "<<WYS<<endl;
int wynik=0;
bool czyswiat=1;
xnasw=10;
xnasw=7;
sw_czygenerowane[0][0]=0;
odczyt_mapy(swiat,0,0,1);
while (wynik!=-1){
    if (wynik==0 && czyswiat){
        npc[0].x=xnasw;
        npc[0].y=ynasw;
        wynik=miasto1(-1,swiat,1,0,1);
        if (wynik==0){
            czyswiat=0;
            ynasw=npc[0].y;
            xnasw=npc[0].x;
        }
    }else if (wynik==0){
        vector <vector <int> > m1[6];
        if (sw_czygenerowane[xnasw][ynasw]){
            stworzmape(m1,xnasw,ynasw,swiat[0][xnasw][ynasw]+(swiat[2][xnasw][ynasw]==0));
        }else{
            odczyt_mapy(m1,xnasw,ynasw,0);
        }
        wynik = miasto1(-1,m1,1,0,0);
        if (wynik==0){
            czyswiat=1;
        }
    }
    if (!czyswiat && wynik>=1 && wynik<=4){
        xnasw-=(wynik==1);
        ynasw-=(wynik==2);
        xnasw+=(wynik==3);
        ynasw+=(wynik==4);
        vector <vector <int> > m1[6];
        if (sw_czygenerowane[xnasw][ynasw]){
            stworzmape(m1,xnasw,ynasw,swiat[0][xnasw][ynasw]+(swiat[2][xnasw][ynasw]==0));
        }else{
            odczyt_mapy(m1,xnasw,ynasw,0);
        }
        wynik = miasto1(wynik,m1,1,0,0);
        if (wynik==0){
            czyswiat=1;
        }
    }
}

npc[0].zapis(0);
w[3][1]=ZASx;
w[3][2]=ZASy;
cout << "OK"<<endl;
//m1zapis(m1,m1numer);
//m1zapis(m3,m3numer);
wzapis();
cout << "TEST2";
close();
return 0;
}

