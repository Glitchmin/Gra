#include "structy.h"


extern int KRATKA;
extern int SZER;
extern int WYS;
extern int WYMx, WYMy;
extern const int OPWYJ;
extern int ZASx;
extern int ZASy;
extern const int PREDKOSC=300;
extern const int ILOSCw=8;
extern int dzien;
extern int tmpx[4];
extern int tmpy[4];
extern vector <int> w[ILOSCw];
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
extern vector <vector <SDL_Texture*> > txnpc;
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

void close(){
  SDL_DestroyWindow( window );
  SDL_Quit();
}

int obldouble (double w){
int w2=w;
int w3= (w-(double)w2)*100;
int x=rand()%100;
if (x<w3){
    w2++;
}
return w2;
}

efekt::efekt(){
}
efekt::efekt(int czest, int ID, int ile, double obr, int zwobr, bool czystun){
    this->czest = czest;
    this->ID=ID;
    this->ile=ile;
    this->obr=obr;
    this->czystun = czystun;
    this->zwobr=zwobr;
    this->tef=0;
    this->t=SDL_GetTicks();
}

bool wzapis(){
    SDL_RWops* plik=SDL_RWFromFile("fl/fl00.bin","wb+");
    if (plik == NULL) {
        cout << "nie znaleziono pliku";
        return 0;
    }
    cout << "fl/fl00.bin - wczytano pomyslnie"<<endl;
    for (int i=0; i<ILOSCw;i++){
            w[i][0]=w[i].size()-1;
            cout << "w["<<i<<"][0] - "<<w[i][0]<<endl;
            SDL_RWwrite(plik, &w[i][0],sizeof(int),1);
        for (int j=1;j<w[i].size();j++){
                cout << w[i][j]<<" ";
            SDL_RWwrite(plik, &w[i][j],sizeof(int),1);
        }
        cout << endl;
    }
    SDL_RWclose(plik);
    return 1;
}

bool wodczyt(bool czyorig){
    SDL_RWops* plik;
    if (czyorig==1){
        plik=SDL_RWFromFile("florig/fl00.bin","rb");
    }else{
        plik=SDL_RWFromFile("fl/fl00.bin","rb");
    }
    if (plik == NULL) {
        cout << "nie znaleziono pliku" << endl;
        return 0;
    }
    cout << "fl/fl00 - odczytywanie"<<endl;
    for (int i=0; i<ILOSCw;i++){
        w[i].clear();
        w[i].push_back(0);
        SDL_RWread(plik, &w[i][0],sizeof(int),1);
        cout << "w["<<i<<"][0]-"<<w[i][0]<<endl;
        if (w[i][0] > -1) {
            w[i].resize(w[i][0] + 1);
        }
        for (int j=1;j<w[i][0]+1;j++){
            SDL_RWread(plik, &w[i][j],sizeof(int),1);
            cout << w[i][j]<<" ";
        }
        cout << endl;
    }
    SDL_RWclose(plik);
    return 1;
}

SDL_Texture* txL (string nazwa){
    SDL_Surface* tmp=IMG_Load(nazwa.c_str());
    string nazwa2=nazwa;
    if (tmp==NULL){
        int a=4;
        while(a--){
            nazwa.pop_back();
        }
        nazwa+=".png";
        tmp=IMG_Load(nazwa.c_str());
        if (tmp==NULL){
            cout << "NIE ZNALEZIONO "<<nazwa<<endl;
            MessageBox(NULL,(LPCWSTR)(("nie znaleziono "+nazwa+" ani "+nazwa2+", program zadziala ale brakuje tekstury").c_str()), (LPCWSTR)"problem",MB_ICONWARNING);
        }else{
            cout << "wczytano"<<nazwa<<endl;
        }

    }else{
        cout << "wczytano "<<nazwa<<endl;
    }
    SDL_SetSurfaceBlendMode(tmp,SDL_BLENDMODE_BLEND);
    //SDL_SetColorKey( tmp, SDL_TRUE, SDL_MapRGB( tmp->format, 1, 1, 1 ) );
    SDL_Texture* TxN=SDL_CreateTextureFromSurface(Rend, tmp);
    SDL_SetTextureBlendMode(TxN,SDL_BLENDMODE_BLEND);
    SDL_FreeSurface(tmp);
    return TxN;
}

xy wypisz (string txt, int x, int y, int r, int g, int b, int a){
    bool lini=0;
    SDL_Color kolor;
    kolor.a=a;
    kolor.b=b;
    if (r<0){
        lini=1;
        r*=-1;
    }
    kolor.r=r;
    kolor.g=g;
    SDL_Rect tmp;
    SDL_Surface* text = TTF_RenderText_Solid(czcionka,txt.c_str(), kolor);
    tmp.h=text->h;
    tmp.w=text->w;
    SDL_Texture* texturka = SDL_CreateTextureFromSurface(Rend, text);
    SDL_FreeSurface(text);
    tmp.x=abs(x);
    tmp.y=y;
    if (x<0){
        x*=(-1);
        tmp.x=x-tmp.w/2;
    }
    xy tmp2;
    tmp2.x=tmp.x+tmp.w;
    tmp2.y=tmp.y+tmp.h;
        if (lini && x+text->w >SZER){
            int tmp4=0;
            int kon=0;
            int tmp3=0;
            int linie=0;
            for (int i=0; i<txt.size();i++){
                if (txt[i]==32){
                    tmp3=tmp4;
                    tmp4=i;
                    string txt2=txt;
                    if (tmp4<txt2.size()){
                        txt2.erase (txt2.begin()+tmp4,txt2.end());
                    }
                    if (kon<txt2.size()){
                        txt2.erase (txt2.begin(),txt2.begin()+kon);
                    }
                    if (wypisz(txt2,x,y,r,g,b,-1).x>SZER){
                        txt2=txt;
                        if (tmp3<txt2.size()){
                            txt2.erase (txt2.begin()+tmp3,txt2.end());
                        }
                        if (kon<txt2.size()){
                            txt2.erase (txt2.begin(),txt2.begin()+kon);
                        }
                        tmp2=wypisz(txt2,x,y+linie*tmp.h,r,g,b,a);
                        kon=tmp3;
                        linie++;
                    }
                //cout << kon << " "<<tmp4<<" "<<txt2<<endl;
                }
            }
            string txt2=txt;
            if (!txt2.empty()){
                if (tmp3 < txt2.size()){
                    txt2.erase (txt2.begin()+tmp3,txt2.end());
                }
                if (kon<txt2.size()){
                    txt2.erase (txt2.begin(),txt2.begin()+kon);
                }
            }
            tmp2=wypisz(txt2,x,y+linie*tmp.h,r,g,b,a);
        }else{
            if (a>=0){
                SDL_RenderCopy(Rend, texturka, NULL,&tmp);
            }
        }
    SDL_DestroyTexture(texturka);
    return tmp2;
}

SDL_Texture* kopiuj (SDL_Texture* t,bool czypolowa){
    Uint32 f;
    int h,w,acc;
    SDL_QueryTexture(t,&f,&acc,&w,&h);
    SDL_Texture* t2 =SDL_CreateTexture(Rend, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,w, h);
    SDL_SetTextureBlendMode(t2,SDL_BLENDMODE_BLEND);
    SDL_Texture* oldtarget=SDL_GetRenderTarget(Rend);
    SDL_SetRenderTarget(Rend,t2);
    SDL_SetRenderDrawColor(Rend,0,0,0,0);
    SDL_RenderClear(Rend);
    SDL_Rect cos={0,0,w,h};
    if (!czypolowa){
        SDL_RenderCopy(Rend,t,NULL,&cos);
    }else{
        SDL_Rect cos2={0,h/2,w,h};
        cos.y+=cos.h/2;
        cos.h/=2;
        SDL_RenderCopy(Rend,t,&cos2,&cos);
    }
    SDL_SetRenderTarget(Rend,oldtarget);
    return t2;


}
