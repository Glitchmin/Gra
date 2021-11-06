#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <time.h>
#include <windows.h>
#include <sstream>
#include <winuser.h>
#include <SDL_ttf.h>
#include <SDL_opengl.h>
#include <conio.h>
using namespace std;

void zapisz(vector <int> a,vector <int> odsw, string s){
    cout <<" otwarto "<< s;
    SDL_RWops* plik=SDL_RWFromFile(s.c_str(),"wb+");
    cout << s<<" - wczytano pomyslnie "<<endl;
    int ilosc=a.size();
    SDL_RWwrite(plik, &ilosc,sizeof(int),1);
    for (int i=0;i<ilosc;i++){
        SDL_RWwrite(plik, &a[i],sizeof(int),1);
        SDL_RWwrite(plik, &odsw[i],sizeof(int),1);
    }
    cout << "zakonczono zapisywanie"<<endl;
    SDL_RWclose(plik);
    }
pair<vector <int>, vector <int> > odczyt (string s){
    cout <<" otwarto "<< s;
    SDL_RWops* plik=SDL_RWFromFile(s.c_str(),"r");
    if (plik!=NULL){
        cout << " - wczytano pomyslnie "<<endl;
        int ilosc;
        SDL_RWread(plik, &ilosc,sizeof(int),1);
        vector <int> odsw;
        vector <int> rozm;
        odsw.resize(ilosc);
        rozm.resize(ilosc);
        for (int i=0;i<ilosc;i++){
            SDL_RWread(plik, &rozm[i],sizeof(int),1);
            SDL_RWread(plik, &odsw[i],sizeof(int),1);
        }
        SDL_RWclose(plik);
        return make_pair(rozm,odsw);
    }
    SDL_RWclose(plik);
    return make_pair((vector <int>){-1},(vector <int>){-1});
}
bool czek_tekstura (string nazwa){
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
            SDL_FreeSurface(tmp);
            return 0;
        }else{
            SDL_FreeSurface(tmp);
            return 1;
        }

    }else{
        SDL_FreeSurface(tmp);
    }
    return 1;
}

int main(int argc, char* args[]){
    while(1){
        stringstream ss;
        string sciezka = ss.str();
        cout << "podaj typ pliku (bg/tr/w/fw) lub wpisz x aby wyjsc"<<endl;
        string sciezka2;
        string sciezka3;
        cin >> sciezka2;
        string tab[4]={"bg","tr","w","fw"};
        if (sciezka2=="x"){
            break;
        }
        if (sciezka2=="bg" || sciezka2=="tr"|| sciezka2=="w" || sciezka2=="fw"){
            vector <int> rozmiary, odsw;
            sciezka3=sciezka2;
            sciezka2="tx/terrain/fltx"+sciezka2+".bin";
            cout << "Wpisz 1 aby zaczac dorzucac tekstury, 2 aby modyfikowac konkretna teksture, 3 aby wyswietlic zawartosc, 0 aby wyczyscic"<<endl;
            int input;
            cin >> input;
            if (input==0){
                cout << "najwiekszy wykryty numer tekstury "<<sciezka3<<": "<<endl;
                int n=1;
                stringstream nn;
                nn << n;
                string tmp_nazwa="tx/terrain/tx"+sciezka3+nn.str()+"_0.bmp";
                while (czek_tekstura(tmp_nazwa)){
                    n++;
                    stringstream nn;
                    nn << n;
                    tmp_nazwa="tx/terrain/tx"+sciezka3+nn.str()+"_0.bmp";
                }
                n--;
                cout << n<<endl;
                odsw.resize(n);
                rozmiary.resize(n);
                for (int i=0; i<n;i++){
                    bool czek=1;
                    int j=0;
                    while (czek){
                        stringstream tmp;
                        tmp << "tx/terrain/tx"<<sciezka3<<i+1<<"_"<<j<<".bmp";
                        if (!czek_tekstura(tmp.str())){
                                break;
                        }
                        j++;

                    }
                    cout <<"tx"<<sciezka3<<i+1<< " wykryta ilosc tekstur "<<j<<endl;
                    rozmiary[i]=j-1;
                    cout << "Czas odswiezania? OwO"<<endl;
                    cin >> odsw[i];
                }
                zapisz(rozmiary,odsw,sciezka2);
            }
            if (input==2){
                pair <vector <int>, vector<int> > tmp=odczyt(sciezka2);
                rozmiary=tmp.first;
                odsw=tmp.second;
                cout << "podaj numer tekstury ^^ "<<endl;
                int numer;
                cin >> numer;
                bool czek=1;
                int j=0;
                while (czek){
                    stringstream tmp;
                    tmp << "tx/terrain/tx"<<sciezka3<<numer<<"_"<<j<<".bmp";
                    if (!czek_tekstura(tmp.str())){
                            break;
                    }
                    j++;

                }
                cout <<"tx"<<sciezka3<<numer<< " wykryta ilosc tekstur "<<j<<endl;
                rozmiary[numer-1]=j-1;
                cout << "podaj czas odswiezania"<<endl;
                cin >> odsw[numer-1];
                zapisz(rozmiary,odsw,sciezka2);
            }
            if (input==1){
                pair <vector <int>, vector<int> > tmp=odczyt(sciezka2);
                rozmiary=tmp.first;
                odsw=tmp.second;
                int rozm=tmp.first.size();
                cout << "przybylo nowych tekstur "<<sciezka3<<": "<<endl;
                int n=1;
                stringstream nn;
                nn << n;
                string tmp_nazwa="tx/terrain/tx"+sciezka3+nn.str()+"_0.bmp";
                while (czek_tekstura(tmp_nazwa)){
                    n++;
                    stringstream nn;
                    nn << n;
                    tmp_nazwa="tx/terrain/tx"+sciezka3+nn.str()+"_0.bmp";
                }
                n--;
                n-=rozm;
                cout << n<<endl;
                odsw.resize(n);
                rozmiary.resize(n);
                odsw.resize(n+rozm);
                rozmiary.resize(n+rozm);
                for (int i=rozm; i<n+rozm;i++){
                    bool czek=1;
                    int j=0;
                    while (czek){
                        stringstream tmp;
                        tmp << "tx/terrain/tx"<<sciezka3<<i+1<<"_"<<j<<".bmp";
                        if (!czek_tekstura(tmp.str())){
                                break;
                        }
                        j++;

                    }
                    cout <<"tx"<<sciezka3<<i+1<< " wykryta ilosc tekstur "<<j<<endl;
                    rozmiary[i]=j-1;
                    cout << "a czas odswiezania? OwO"<<endl;
                    cin >> odsw[i];
                }
                zapisz(rozmiary,odsw,sciezka2);
            }
            if (input==3){
                sciezka2=sciezka3;
                sciezka2="tx/terrain/fltx"+sciezka2+".bin";
                pair <vector <int>, vector<int> > tmp=odczyt(sciezka2);
                cout << "w folderze powinno byc:"<<endl;
                for (int i=0; i<tmp.first.size();i++){
                    int numer=tmp.first[i];
                    for (int j=0; j<=numer;j++){
                        cout << "tx"+sciezka3<<i+1<<"_"<<j<<".png (albo .bmp)"<<endl;
                    }
                    cout << "czestotliwosc odswiezania: "<<tmp.second[i]<<endl<<endl;
                }
            }

        }else if (sciezka2!="x"){
            for (int i=0; i<4;i++){
                sciezka2=tab[i];
                sciezka3=tab[i];
                sciezka2="tx/terrain/fltx"+sciezka2+".bin";
                pair <vector <int>, vector<int> > tmp=odczyt(sciezka2);
                cout << "w folderze powinno byc:"<<endl;
                for (int i=0; i<tmp.first.size();i++){
                    int numer=tmp.first[i];
                    for (int j=0; j<=numer;j++){
                        cout << "tx"+sciezka3<<i+1<<"_"<<j<<".bmp"<<endl;
                    }
                    cout << "czestotliwosc odswiezania: "<<tmp.second[i]<<endl<<endl;
                }
            }
        }
    }
    cout << "nacisnij cokolwiek by zakonczyc dzialanie programu"<<endl;
    getch();
}
