#ifndef IT_H
#define IT_H

#include <vector>

using namespace std;

class it{
    public:
    int typ;
    vector <int> inty;
    vector <double> dou;
    int value;
    int tekstura;//ktora tekstura
    int t;//czas do znikniecia
    int maxt;//czas znikania; -1 oznacza niesmiertelnosc
    int wym;//wymiary a i b przedm 10*a+b
    int bonusy;

    int zwrocbonus(int ktorybonus);

    void ustawbonusy(vector <int> b){
        int tmplicz=1;
        bonusy=0;
        for (int k=0;k<7;k++){
            int tmp=0;
            tmp+=(b[k]>0);
            if (b[k]<0){
                b[k]*=(-1);
            }
            if (b[k]>=4){
                tmp+=8;
                b[k]-=4;
            }
            if (b[k]>=2){
                tmp+=4;
                b[k]-=2;
            }
            if (b[k]>=1){
                tmp+=2;
                b[k]-=1;
            }
            bonusy+=tmp*tmplicz;
            tmplicz*=16;
        }
    }
};

struct plecak{
    vector < vector <int> > t;
    vector <vector <it> > prz;
};

#endif IT_H
