#include "npc.h"

using namespace std;

#define DEBUG if (0)
#define endl " >"<<__FUNCTION__<<"<"<<endl

extern vector <NPC> npc;
extern it stworzbron(int podtyp, double dmg, double ap, double as,int tekstura, int t, int maxt, int wym, int value,int bcrch=0,int bcrdmg=0, int bspd=0, int bds=0);
extern int ZASx;
extern int ZASy;
extern int tmpx[];
extern int tmpy[];

int stworzNPC(NPC);
xy zwroc_pkt_fav(vector <vector <int> > m1[]);

xy wygeneruj_pkt_spawnu(vector <vector <int> > m1[]){
    vector <vector <bool> > e;
    e.resize(m1[0].size());
    for (int i=0; i<m1[0].size();i++){
        e[i].resize(m1[0][0].size(),0);
    }
    queue<xy> q;
    q.push(zwroc_pkt_fav(m1));
    vector <xy> pkty;
    while(!q.empty()){
        xy tmpp = q.front();
        q.pop();
        if (abs(tmpp.x-npc[0].x)>ZASx && abs(tmpp.y-npc[0].y)>ZASy){
            pkty.push_back(tmpp);
        }
        e[tmpp.x][tmpp.y]=1;
        for (int i=0; i<4;i++){
            if (tmpp.x+tmpx[i] >=0 && tmpp.x+tmpx[i] <m1[0].size() && tmpp.y+tmpy[i]>=0 && tmpp.y+tmpy[i]<m1[0].size()){
                if (!e[tmpp.x+tmpx[i]][tmpp.y+tmpy[i]]&&(m1[2][tmpp.x+tmpx[i]][tmpp.y+tmpy[i]]==-1)&&(m1[4][tmpp.x+tmpx[i]][tmpp.y+tmpy[i]]==-1)){
                    e[tmpp.x+tmpx[i]][tmpp.y+tmpy[i]]=1;
                    xy tmp;
                    tmp.x=tmpp.x+tmpx[i];
                    tmp.y=tmpp.y+tmpy[i];
                    q.push(tmp);
                }
            }
        }
    }
    return pkty[rand()%(pkty.size()-1)+1];
}

void generuj_przeciwnika(przeciwnicy ktory, vector <int> &npceID, vector<vector <int> > m1[]){
    if (ktory==wilk){
        xy tmp=wygeneruj_pkt_spawnu(m1);
        int x=tmp.x, y=tmp.y;
        NPC npctmp(x+2,y+1,x+rand()%3,y+rand()%3,x-rand()%3,y-rand()%3,500,500,1,-1,10,1,{10},{},{},5,1,5,1,1000,1);
        int numer = stworzNPC(npctmp);
        npc[numer].ekw[0].push_back(stworzbron(1,1.50,0.50,0.30,5,-1,-1,52,1,1,1));
        npc[numer].ID=numer;
        m1[4][x][y]=numer;
        npceID.push_back(numer);
    }
}
