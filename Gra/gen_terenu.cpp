#include <vector>
#include <stdlib.h>
#include <queue>

#include "structy.h"
#include "npc.h"

using namespace std;

#define endl " >"<<__FUNCTION__<<"<"<<endl

extern int tmpx[4];
extern int tmpy[4];
extern int u;
extern vector<vector <int> > swiat[6];
extern int pozycje[4];
extern vector <NPC> npc;

void rekur2(int x, int y, vector <vector <int> > m1[]){
    for (int i=0; i<4;i++){
        if (x+tmpx[i]>=0 && x+tmpx[i]<m1[0].size() && y+tmpy[i]>=0 && y+tmpy[i]<m1[0].size()){
            if (m1[2][x+tmpx[i]][y+tmpy[i]]==0&&rand()%100<45&&u>0){
                u--;
                m1[2][x+tmpx[i]][y+tmpy[i]]=-1;
                rekur2 (x+tmpx[i],y+tmpy[i],m1);
            }
        }
    }
}

void stworzjezioro(int x, int y,int w,int h,vector <vector <int> > m1[]){
    int wys=0;
    vector <int> wysy;
    for (int i=0; i<w;i++){
        wys=min(i+1,h/2);
        if (i>h/2){
            wys-=(rand()%3>0);
        }
        wys=min(w-i,wys);
        //cout << wys<<";"<<endl;
        for (int k=0; k<wys;k++){
            m1[0][x+i][y+h/2-k-1]=21;
            if (i==0){
                m1[0][x+i][y+h/2-k-1]=17;
            }
            if (i==w-1){
                m1[0][x+i][y+h/2-k-1]=19;
            }
        }
        wysy.push_back(wys);
    }
    for (int i=0; i<wysy.size();i++){
        bool czek=0;
        if (i+1<wysy.size()&&wysy[i+1]>wysy[i]){
            czek=1;
            m1[0][x+i][y+h/2-wysy[i]-1]=5;
        }
        if (i>0&&wysy[i-1]>wysy[i]){
            czek=1;
            m1[0][x+i][y+h/2-wysy[i]-1]=7;
        }
        if (i+1<wysy.size() && i>0&&wysy[i-1]>wysy[i] &&wysy[i+1]>wysy[i]){
            m1[0][x+i][y+h/2-wysy[i]-1]=13;
            czek=1;
        }
        if (czek==0){
            m1[0][x+i][y+h/2-wysy[i]]=13;
        }
    }
    wysy.clear();
    for (int i=0; i<w;i++){
        wys=min(i+1,h/2);
        if (i>h/2){
            wys-=(rand()%3>0);
        }
        wys=min(w-i,wys);
        for (int k=0; k<wys;k++){
            m1[0][x+i][y+h/2+k]=21;
            if (i==0){
                m1[0][x+i][y+h/2+k]=17;
            }
            if (i==w-1){
                m1[0][x+i][y+h/2+k]=19;
            }
        }
        wysy.push_back(wys);
    }
    for (int i=0; i<wysy.size();i++){
       bool czek=0;
        if (i+1<wysy.size()&&wysy[i+1]>wysy[i]){
            czek=1;
            m1[0][x+i][y+h/2+wysy[i]]=11;
        }
        if (i>0&&wysy[i-1]>wysy[i]){
            czek=1;
            m1[0][x+i][y+h/2+wysy[i]]=9;
        }
        if (i+1<wysy.size() && i>0&&wysy[i-1]>wysy[i] &&wysy[i+1]>wysy[i]){
            m1[0][x+i][y+h/2+wysy[i]]=15;
            czek=1;
        }
        if (czek==0){
            m1[0][x+i][y+h/2+wysy[i]-1]=15;
        }
    }
}

void stworzmape (vector <vector <int> > m1[],int x,int y, int biom){
for (int j=0; j<6;j++){
    m1[j].resize(64);
    for (int i=0; i<64;i++){
        m1[j][i].resize(64,(-1+(j==0)+(j==3)));
    }
}
if (biom==0){
    srand(1000*x+y+1);
    int lewwyjy=-1;
    if (x>0 && swiat[2][x-1][y]==0){
        srand(1000*(x-1)+y+1);
        lewwyjy=rand()%62+1;
    }
    int gorwyjx=-1;
    if (y>0&& swiat[2][x][y-1]==0){
        srand(1000*(x)+y);
        gorwyjx=rand()%62+1;
    }
    int prawwyjy=-1;
    if (x+1<swiat[0].size()&& swiat[2][x+1][y]==0){
        srand(1000*x+y+1);
        prawwyjy=rand()%62+1;
    }
    int dolwyjx=-1;
    if (y+1<swiat[0].size()&& swiat[2][x][y+1]==0){
        srand(1000*x+y+1);
        dolwyjx=rand()%62+1;
    }
    if (lewwyjy!=-1){
        for (int i=0; i<64;i++){
            m1[2][0][i]=0;
        }
        m1[2][0][lewwyjy]=-1;
        int wys=2;
        for (int i=5; i<59;i++){
            for (int j=0; j<wys;j++){
                m1[2][j][i]=-(i==lewwyjy);
            }
            wys+=rand()%2-rand()%2;
            wys-=(wys>(59-i));
            wys=max(1,wys);
            wys=min(5,wys);
        }
    }
    if (prawwyjy!=-1){
        for (int i=0; i<64;i++){
            m1[2][63][i]=0;
        }
        m1[2][63][prawwyjy]=-1;
        int wys=2;
        for (int i=5; i<59;i++){
            for (int j=0; j<wys;j++){
                m1[2][63-j][i]=-(i==prawwyjy);
            }
            wys+=rand()%2-rand()%2;
            wys-=(wys>(59-i));
            wys=max(1,wys);
            wys=min(5,wys);
        }
    }
    if (gorwyjx!=-1){
        for (int i=0; i<64;i++){
            m1[2][i][0]=0;
        }
        m1[2][gorwyjx][0]=-1;
        int wys=2;
        for (int i=5; i<59;i++){
            for (int j=0; j<wys;j++){
                m1[2][i][j]=-(i==gorwyjx);
            }
            wys+=rand()%2-rand()%2;
            wys-=(wys>(59-i));
            wys=max(1,wys);
            wys=min(5,wys);
        }
    }
     if (dolwyjx!=-1){
        for (int i=0; i<64;i++){
            m1[2][i][63]=0;
        }
        m1[2][dolwyjx][63]=-1;
        int wys=2;
        for (int i=5; i<59;i++){
            for (int j=0; j<wys;j++){
                m1[2][i][63-j]=-(i==dolwyjx);
            }
            wys+=rand()%2-rand()%2;
            wys-=(wys>(59-i));
            wys=max(1,wys);
            wys=min(5,wys);
        }
    }
    pozycje[0]=prawwyjy;
    pozycje[1]=dolwyjx;
    pozycje[2]=lewwyjy;
    pozycje[3]=gorwyjx;
}
if (biom==1){
    int lewwyjy=-1;
    if (x>0 && swiat[2][x-1][y]==-1){
        srand(1000*(x-1)+y+1);
        lewwyjy=rand()%62+1;
    }
    int gorwyjx=-1;
    if (y>0&& swiat[2][x][y-1]==-1){
        srand(1000*(x)+y);
        gorwyjx=rand()%62+1;
    }
    int prawwyjy=-1;
    if (x+1<swiat[0].size()&& swiat[2][x+1][y]==-1){
        srand(1000*x+y+1);
        prawwyjy=rand()%62+1;
    }
    int dolwyjx=-1;
    if (y+1<swiat[0].size()&& swiat[2][x][y+1]==-1){
        srand(1000*x+y+1);
        dolwyjx=rand()%62+1;
    }
    pozycje[0]=prawwyjy;
    pozycje[1]=dolwyjx;
    pozycje[2]=lewwyjy;
    pozycje[3]=gorwyjx;
    srand(1000*x+y+1);
    for (int j=0; j<6;j++){
        m1[j].resize(64);
        for (int i=0; i<64;i++){
            m1[j][i].resize(64,(-1+(j==0)+(j==3)));
        }
    }
    u=64*32;
    int wynik=0;
    int wynik2=0;
    int wynik3=0;
    xy fav;
    vector <vector <int> > e;
    e.resize(m1[0].size());
    for (int i=0; i<m1[0].size();i++){
        e[i].resize(m1[0][0].size(),0);
        for (int j=0; j<m1[0][0].size();j++){
            m1[2][i][j]=0;
        }
    }
    while (u>0){
        int x=rand()%(m1[0].size());
        int y=rand()%(m1[0][0].size());
        if (m1[2][x][y]==0){
            rekur2(x,y,m1);
        }
    }
    int maksi=0;
    for (int i=0; i<m1[0].size();i++){
        m1[2][0][i]=0;
        m1[2][i][0]=0;
        m1[2][i][((int)m1[0].size())-1]=0;
        m1[2][((int)m1[0].size())-1][i]=0;
    }
    for (int i=0; i<m1[0].size();i++){
        for(int j=0; j<m1[0].size();j++){
            queue<xy> q;
            xy tmpp;
            tmpp.x=i;
            tmpp.y=j;
            q.push(tmpp);
            int rozm=0;
            if (!e[i][j]&&(m1[2][i][j]==-1)){
                while(!q.empty()){
                    rozm++;
                    xy tmpp = q.front();
                    q.pop();
                    e[tmpp.x][tmpp.y]=1;
                    for (int i=0; i<4;i++){
                        if (tmpp.x+tmpx[i] >=0 && tmpp.x+tmpx[i] <m1[0].size() && tmpp.y+tmpy[i]>=0 && tmpp.y+tmpy[i]<m1[0].size()){
                            if (!e[tmpp.x+tmpx[i]][tmpp.y+tmpy[i]]&&!(m1[0][tmpp.x+tmpx[i]][tmpp.y+tmpy[i]]%2)){
                                e[tmpp.x+tmpx[i]][tmpp.y+tmpy[i]]=1;
                                xy tmp;
                                tmp.x=tmpp.x+tmpx[i];
                                tmp.y=tmpp.y+tmpy[i];
                                q.push(tmp);
                            }
                        }
                    }
                }
                if (rozm>maksi){
                    fav.x=i;
                    fav.y=j;
                }
                maksi=max(maksi,rozm);
            }
        }
    }
    queue <xy> q;
    e.clear();
    e.resize(m1[0].size());
    for (int i=0; i<m1[0].size();i++){
        e[i].resize(m1[0][0].size(),0);
    }
    q.push(fav);
    xy naprawo;
    naprawo.x=0;
    xy nalewo;
    nalewo.x=m1[0].size();
    xy dogory;
    dogory.y=m1[0].size();
    xy dodolu;
    dodolu.y=0;
    while (!q.empty()){
        xy tmpp=q.front();
        q.pop();
        e[tmpp.x][tmpp.y]=1;
        for (int i=0; i<4;i++){
            if (tmpp.x+tmpx[i] >=0 && tmpp.x+tmpx[i] <m1[0].size() && tmpp.y+tmpy[i]>=0 && tmpp.y+tmpy[i]<m1[0].size()){
                if (!e[tmpp.x+tmpx[i]][tmpp.y+tmpy[i]]&&(m1[2][tmpp.x+tmpx[i]][tmpp.y+tmpy[i]]==-1)){
                    e[tmpp.x+tmpx[i]][tmpp.y+tmpy[i]]=1;
                    xy tmp;
                    tmp.x=tmpp.x+tmpx[i];
                    tmp.y=tmpp.y+tmpy[i];
                    q.push(tmp);
                    if (tmp.x>=naprawo.x){
                        naprawo=tmp;
                    }
                    if (tmp.x<=nalewo.x){
                        nalewo=tmp;
                    }
                    if (tmp.y>=dodolu.y){
                        dodolu=tmp;
                    }
                    if (tmp.y<=dogory.y){
                        dogory=tmp;
                    }
                }
            }
        }
    }
    if (lewwyjy!=-1){
        npc[0].x=0;
        npc[0].y=lewwyjy;
        vector <vector <int> > e2;
        e2.resize(64);
        for (int i=0; i<64;i++){
            e2[i].resize(64,-1);
        }
        queue <xy> q;
        q.push({0, lewwyjy});
        xy start={-1,-1};
        for (int i=0; i<64;i++){
            e2[0][i]=1;
            e2[63][i]=1;
            e2[i][63]=1;
            e2[i][0]=1;
        }
        e2[0][lewwyjy]=-2;
        while (!q.empty()){
            xy tmpp=q.front();
            q.pop();
            if (e[tmpp.x][tmpp.y]){
                start=tmpp;
                if (rand()%7==0){
                    break;
                }
            }
            vector <int> tmpv={0,1,2,3};
            random_shuffle(tmpv.begin(),tmpv.end());
            for (int j=0; j<4;j++){
                int i=tmpv[j];
                if (tmpp.x+tmpx[i] >=0 && tmpp.x+tmpx[i] <m1[0].size() && tmpp.y+tmpy[i]>=0 && tmpp.y+tmpy[i]<m1[0].size()){
                    if (e2[tmpp.x+tmpx[i]][tmpp.y+tmpy[i]]==-1){
                        e2[tmpp.x+tmpx[i]][tmpp.y+tmpy[i]]=i;
                        xy tmp;
                        tmp.x=tmpp.x+tmpx[i];
                        tmp.y=tmpp.y+tmpy[i];
                        q.push(tmp);
                    }
                }
            }
        }
        while(e2[start.x][start.y]!=-2){
            int tmp=e2[start.x][start.y];
            m1[2][start.x][start.y]=-1;
            e[start.x][start.y]=1;
            start.x-=tmpx[(tmp)%4];
            start.y-=tmpy[(tmp)%4];
        }
        m1[2][start.x][start.y]=-1;
        e[start.x][start.y]=1;
    }
    if (gorwyjx!=-1){
        npc[0].x=gorwyjx;
        npc[0].y=0;
        vector <vector <int> > e2;
        e2.resize(64);
        for (int i=0; i<64;i++){
            e2[i].resize(64,-1);
        }
        queue <xy> q;
        q.push({gorwyjx,0});
        xy start={-1,-1};
        for (int i=0; i<64;i++){
            e2[0][i]=1;
            e2[63][i]=1;
            e2[i][63]=1;
            e2[i][0]=1;
        }
        e2[gorwyjx][0]=-2;
        while (!q.empty()){
            xy tmpp=q.front();
            q.pop();
            if (e[tmpp.x][tmpp.y]){
                start=tmpp;
                if (rand()%7==0){
                    break;
                }
            }
            vector <int> tmpv={0,1,2,3};
            random_shuffle(tmpv.begin(),tmpv.end());
            for (int j=0; j<4;j++){
                int i=tmpv[j];
                if (tmpp.x+tmpx[i] >=0 && tmpp.x+tmpx[i] <m1[0].size() && tmpp.y+tmpy[i]>=0 && tmpp.y+tmpy[i]<m1[0].size()){
                    if (e2[tmpp.x+tmpx[i]][tmpp.y+tmpy[i]]==-1){
                        e2[tmpp.x+tmpx[i]][tmpp.y+tmpy[i]]=i;
                        xy tmp;
                        tmp.x=tmpp.x+tmpx[i];
                        tmp.y=tmpp.y+tmpy[i];
                        q.push(tmp);
                    }
                }
            }
        }
        while(e2[start.x][start.y]!=-2){
            int tmp=e2[start.x][start.y];
            m1[2][start.x][start.y]=-1;
            e[start.x][start.y]=1;
            start.x-=tmpx[(tmp)%4];
            start.y-=tmpy[(tmp)%4];
        }
        m1[2][start.x][start.y]=-1;
        e[start.x][start.y]=1;
    }
    if (dolwyjx!=-1){
        npc[0].x=dolwyjx;
        npc[0].y=63;
        vector <vector <int> > e2;
        e2.resize(64);
        for (int i=0; i<64;i++){
            e2[i].resize(64,-1);
        }
        queue <xy> q;
        q.push({dolwyjx,63});
        xy start;
        for (int i=0; i<64;i++){
            e2[0][i]=1;
            e2[63][i]=1;
            e2[i][63]=1;
            e2[i][0]=1;
        }
        e2[dolwyjx][63]=-2;
        while (!q.empty()){
            xy tmpp=q.front();
            q.pop();
            if (e[tmpp.x][tmpp.y]){
                start=tmpp;
                if (rand()%7==0){
                    break;
                }
            }
            vector <int> tmpv={0,1,2,3};
            random_shuffle(tmpv.begin(),tmpv.end());
            for (int j=0; j<4;j++){
                int i=tmpv[j];
                if (tmpp.x+tmpx[i] >=0 && tmpp.x+tmpx[i] <m1[0].size() && tmpp.y+tmpy[i]>=0 && tmpp.y+tmpy[i]<m1[0].size()){
                    if (e2[tmpp.x+tmpx[i]][tmpp.y+tmpy[i]]==-1){
                        e2[tmpp.x+tmpx[i]][tmpp.y+tmpy[i]]=i;
                        xy tmp;
                        tmp.x=tmpp.x+tmpx[i];
                        tmp.y=tmpp.y+tmpy[i];
                        q.push(tmp);
                    }
                }
            }
        }
        while(e2[start.x][start.y]!=-2){
            int tmp=e2[start.x][start.y];
            m1[2][start.x][start.y]=-1;
            e[start.x][start.y]=1;
            start.x-=tmpx[(tmp)%4];
            start.y-=tmpy[(tmp)%4];
        }
        m1[2][start.x][start.y]=-1;
        e[start.x][start.y]=1;
    }
    if (prawwyjy!=-1){
        npc[0].x=63;
        npc[0].y=prawwyjy;
        vector <vector <int> > e2;
        e2.resize(64);
        for (int i=0; i<64;i++){
            e2[i].resize(64,-1);
        }
        queue <xy> q;
        q.push({63,prawwyjy});
        xy start;
        for (int i=0; i<64;i++){
            e2[0][i]=1;
            e2[63][i]=1;
            e2[i][63]=1;
            e2[i][0]=1;
        }
        e2[63][prawwyjy]=-2;
        while (!q.empty()){
            xy tmpp=q.front();
            q.pop();
            if (e[tmpp.x][tmpp.y]){
                start=tmpp;
                if (rand()%7==0){
                    break;
                }
            }
            vector <int> tmpv={0,1,2,3};
            random_shuffle(tmpv.begin(),tmpv.end());
            for (int j=0; j<4;j++){
                int i=tmpv[j];
                if (tmpp.x+tmpx[i] >=0 && tmpp.x+tmpx[i] <m1[0].size() && tmpp.y+tmpy[i]>=0 && tmpp.y+tmpy[i]<m1[0].size()){
                    if (e2[tmpp.x+tmpx[i]][tmpp.y+tmpy[i]]==-1){
                        e2[tmpp.x+tmpx[i]][tmpp.y+tmpy[i]]=i;
                        xy tmp;
                        tmp.x=tmpp.x+tmpx[i];
                        tmp.y=tmpp.y+tmpy[i];
                        q.push(tmp);
                    }
                }
            }
        }
        while(e2[start.x][start.y]!=-2){
            int tmp=e2[start.x][start.y];
            m1[2][start.x][start.y]=-1;
            e[start.x][start.y]=1;
            start.x-=tmpx[(tmp)%4];
            start.y-=tmpy[(tmp)%4];
        }
        m1[2][start.x][start.y]=-1;
        e[start.x][start.y]=1;
    }
    }
}
