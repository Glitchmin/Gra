#ifndef NAPIS_H
#define NAPIS_H
#include <string>
#include <SDL.h>

#define endl " >"<<__FUNCTION__<<"<"<<endl

using namespace std;

struct napis{
    napis(string tekst,int r,int g,int b,int ilems,int ilemszaniku);
    napis();
    string tekst;
    int x,y;
    int r,g,b,a;
    int ilems;
    int ilemsmax;
    Uint32 poprz;
    int ilemszaniku;
};

#endif
