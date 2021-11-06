#include <SDL.h>
#include <vector>
#include <sstream>
#include <iostream>
#include <windows.h>
using namespace std;

void zapisz_mape(vector <vector<int> > m1[], int x, int y, bool czyswiat){
    stringstream ss;
    if (!czyswiat){
        ss << x<<"_"<<y;
    }else{
        ss << "sw";
    }
    string sciezka = ss.str();
    string sciezka2="fl/maps/map_"+sciezka+".bin";
    cout <<" otwarto "<< sciezka2<<endl;
    SDL_RWops* plik=SDL_RWFromFile(sciezka2.c_str(),"wb+");
    if (plik==NULL){
        MessageBox(NULL, (LPCWSTR)"nie udalo sie utworzyc pliku w folderze fl/maps", (LPCWSTR)"problem",MB_ICONWARNING);
        return;
    }
    int rozm1=m1[0].size();
    int rozm2=m1[0][0].size();
    SDL_RWwrite(plik,&rozm1,sizeof(int),1);
    SDL_RWwrite(plik,&rozm2,sizeof(int),1);
    for (int k=0;k<6;k++){
        if (k!=3 && k!=4){
            for (int i=0; i<rozm1;i++){
                for (int j=0; j<rozm2;j++){
                    SDL_RWwrite(plik,&m1[k][i][j],sizeof(int),1);
                }
            }
        }
    }
    SDL_RWclose(plik);
    cout << "zapis pomyslny!"<<endl;
}

bool odczyt_mapy(vector <vector<int> > m1[], int x, int y, bool czyswiat){
    stringstream ss;
    if (!czyswiat){
        ss << x<<"_"<<y;
    }else{
        ss << "sw";
    }
    string sciezka = ss.str();
    string sciezka2="fl/maps/map_"+sciezka+".bin";
    cout <<" otwarto "<< sciezka2<<endl;
    SDL_RWops* plik=SDL_RWFromFile(sciezka2.c_str(),"r");
    if (plik==NULL){
        MessageBox(NULL,(LPCWSTR)"nie udalo sie otworzyc pliku w folderze fl/maps", (LPCWSTR)"problem",MB_ICONWARNING);
        return 0;
    }
    int rozm1;
    int rozm2;
    SDL_RWread(plik,&rozm1,sizeof(int),1);
    SDL_RWread(plik,&rozm2,sizeof(int),1);
    for (int k=0;k<6;k++){
        m1[k].resize(rozm1);
        if (k!=3 && k!=4){
            for (int i=0; i<rozm1;i++){
                m1[k][i].resize(rozm2);
                for (int j=0; j<rozm2;j++){
                    SDL_RWread(plik,&m1[k][i][j],sizeof(int),1);
                }
            }
        }
    }
    for (int k=3;k<=4;k++){
        m1[k].resize(rozm1);
        for (int i=0; i<m1[0].size();i++){
            m1[k][i].resize(rozm2);
            for (int j=0; j<rozm2;j++){
                m1[k][i][j]=0-(k==4);
            }
        }
    }
    SDL_RWclose(plik);
    return 1;
}
