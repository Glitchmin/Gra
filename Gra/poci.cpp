#include <tuple>

#include "poci.h"
#include "npc.h"

extern int KRATKA;
extern vector <NPC> npc;
extern vector <vector <SDL_Texture*> > txw;
extern vector <tuple <xyd, double, double, double, it> > pociskiwbite;
extern vector <int> w[8];

double obliczhtxszerokie(SDL_Texture* tx);

void oblicz_strzale(poci& strzala, int npcIDdef);

poci::poci(int& xm, int& ym, xy& pozgr, NPC& npcstrz, int nrnpc) {
	this->predk = npcstrz.ekw[0][0].dou[3];
	this->strzala = npcstrz.ekw[5][0];
	this->h = 1;
	this->horyg = 1;
	this->t = SDL_GetTicks();
	this->wyzn = ((double)(ym - pozgr.y - 4 * KRATKA / 4 + (ym - 4 * KRATKA / 4 == pozgr.y)) / (double)(xm - pozgr.x + (xm - pozgr.x == 0)));
	this->xdod = (xm - pozgr.x + (xm - pozgr.x == 0)) > 0;
	this->kat = atan(((double)(ym - pozgr.y) / (double)(xm - pozgr.x + (xm - pozgr.x == 0)))) * 180 / 3.14 + 90 + 180 * (1 - this->xdod);
	this->katcienia = atan(this->wyzn) * 180 / 3.14 + 90 + 180 * (1 - this->xdod);
	this->s.x = (npcstrz.x * KRATKA + KRATKA / 2) / (double)KRATKA;
	this->s.y = (npcstrz.y * KRATKA + 3 * KRATKA / 4) / (double)KRATKA;
	this->poppoz = this->s;
	this->poz = this->s;
	this->popodl = 0;
	this->odl2 = (double)(ym - pozgr.y - 4 * KRATKA / 4) / KRATKA * (double)(ym - pozgr.y - 5 * KRATKA / 4) / KRATKA + (double)(xm - pozgr.x) / KRATKA * (double)(xm - pozgr.x) / KRATKA;
	this->npc = nrnpc;
}

void obliczpoci(vector <poci>& p, vector<vector <int> > m1[]) {
	for (int i = 0; i < p.size();i++) {
		double odl = p[i].predk * ((double)(SDL_GetTicks() - p[i].t)) / 1000.0;
		double x = 0;
		x = sqrt(odl * odl / (1 + p[i].wyzn * p[i].wyzn));
		if (!p[i].xdod) {
			x *= (-1);
		}
		double y = (p[i].wyzn * x);
		p[i].poppoz = p[i].poz;
		p[i].poz.x = p[i].s.x + x;
		p[i].poz.y = p[i].s.y + y;
		p[i].h = (p[i].horyg - (odl / sqrt(p[i].odl2) * p[i].horyg));
		vector <xyd> pkt;
		vector <pair<xyd, int> > pktnpc;
		for (int i2 = max((int)p[i].poppoz.x - 1, 0); i2 <= min((int)p[i].poz.x + 1, (int)m1[0].size() - 1);i2++) {
			for (int j = max((int)p[i].poppoz.y - 1, 0); j <= min((int)p[i].poz.y + 1, (int)m1[0].size() - 1);j++) {
				double y1 = p[i].wyzn * ((double)i2 - p[i].s.x) + p[i].s.y;
				double y2 = p[i].wyzn * ((double)i2 - p[i].s.x + 1.0) + p[i].s.y;
				double x1 = ((double)j - p[i].s.y) / p[i].wyzn + p[i].s.x;
				double x2 = ((double)j - p[i].s.y + 1) / p[i].wyzn + p[i].s.x;
				if (i2 == (int)x1) {
					pkt.push_back({ (double)x1,(double)j });
				}
				if (i2 == (int)x2) {
					pkt.push_back({ x2,j + 1.0 - 0.0000001 });
				}
				if (j == (int)y1) {
					pkt.push_back({ (double)i2,(double)y1 });
				}
				if (j == (int)y2) {
					pkt.push_back({ i2 + 1.0 - 0.0000001,y2 });
				}
				double odl3 = sqrt(p[i].odl2);
				pkt.push_back({ sqrt(odl3 * odl3 / (1 + p[i].wyzn * p[i].wyzn)),(p[i].wyzn * (sqrt(odl3 * odl3 / (1 + p[i].wyzn * p[i].wyzn)))) });
				if (!p[i].xdod) {
					pkt[(int)pkt.size() - 1].y *= (-1);
					pkt[(int)pkt.size() - 1].x *= (-1);
				}
				pkt[(int)pkt.size() - 1].x += p[i].s.x;
				pkt[(int)pkt.size() - 1].y += p[i].s.y;
				if (m1[4][i2][j] != p[i].npc && m1[4][i2][j] != -1) {
					double xnpc = npc[m1[4][i2][j]].poz.x;
					double ynpc = npc[m1[4][i2][j]].poz.y;
					double y1 = p[i].wyzn * (xnpc - p[i].s.x + npc[m1[4][i2][j]].zwr_hitbox().x_lewy) + p[i].s.y;
					double y2 = p[i].wyzn * (xnpc - p[i].s.x + npc[m1[4][i2][j]].zwr_hitbox().x_prawy) + p[i].s.y;
					double x1 = (ynpc - p[i].s.y + npc[m1[4][i2][j]].zwr_hitbox().y_gora - 2.0) / p[i].wyzn + p[i].s.x;
					double x2 = (ynpc - p[i].s.y + npc[m1[4][i2][j]].zwr_hitbox().y_dol - 2.0) / p[i].wyzn + p[i].s.x;
					if (y1 + 2.0 >= ynpc + npc[m1[4][i2][j]].zwr_hitbox().y_gora && y1 + 2.0 <= ynpc + npc[m1[4][i2][j]].zwr_hitbox().y_dol) {
						pktnpc.push_back(make_pair(xyd(xnpc + npc[m1[4][i2][j]].zwr_hitbox().x_lewy, y1), m1[4][i2][j]));
					}
					if (y2 + 2.0 >= ynpc + npc[m1[4][i2][j]].zwr_hitbox().y_gora && y2 + 2.0 <= ynpc + npc[m1[4][i2][j]].zwr_hitbox().y_dol) {
						pktnpc.push_back(make_pair(xyd(xnpc + npc[m1[4][i2][j]].zwr_hitbox().x_prawy, y2), m1[4][i2][j]));
					}
					if (x1 >= xnpc + npc[m1[4][i2][j]].zwr_hitbox().x_lewy && x1 <= xnpc + npc[m1[4][i2][j]].zwr_hitbox().x_prawy) {
						pktnpc.push_back(make_pair(xyd(x1, ynpc + npc[m1[4][i2][j]].zwr_hitbox().y_gora - 2.0), m1[4][i2][j]));
					}
					if (x2 >= xnpc + npc[m1[4][i2][j]].zwr_hitbox().x_lewy && x2 <= xnpc + npc[m1[4][i2][j]].zwr_hitbox().x_prawy) {
						pktnpc.push_back(make_pair(xyd ( x2, ynpc + npc[m1[4][i2][j]].zwr_hitbox().y_dol - 2.0 ), m1[4][i2][j]));
					}
				}
			}
		}
		double mini = -1;
		xyd pozmini;
		double hmini = 0;
		int cel = -1;
		for (int k = 0; k < (int)pkt.size() + (int)pktnpc.size();k++) {
			xyd punkt;
			if (k < pkt.size()) {
				punkt = pkt[k];
			}
			else {
				punkt = pktnpc[k - (int)pkt.size()].first;
			}
			double odl2 = sqrt((p[i].s.x - punkt.x) * (p[i].s.x - punkt.x) + (p[i].s.y - punkt.y) * (p[i].s.y - punkt.y));
			double h = (p[i].horyg - (odl2 / sqrt(p[i].odl2) * p[i].horyg)) - 0.0000001;
			if (((punkt.y - p[i].s.y) * (pkt[(int)pkt.size() - 1].y - p[i].s.y)) > 0 && ((punkt.x - p[i].s.x) * (pkt[(int)pkt.size() - 1].x - p[i].s.x)) > 0) {
				if (odl2 <= odl && p[i].popodl <= odl2 && (mini == -1 || odl2 <= mini) && (h <= 0 || (m1[2][(int)punkt.x][(int)punkt.y] != -1 && h <= obliczhtxszerokie(txw[m1[2][(int)punkt.x][(int)punkt.y]][0])) || (k >= (int)pkt.size() && h <= npc[pktnpc[k - (int)pkt.size()].second].h))) {
					mini = odl2;
					pozmini = punkt;
					hmini = h;
					if (k >= pkt.size()) {
						cel = pktnpc[k - (int)pkt.size()].second;
					}
				}
			}
		}
		p[i].popodl = odl;
		if (mini != -1) {
			if (cel == -1) {
				pociskiwbite.push_back(make_tuple(pozmini, p[i].kat, p[i].katcienia, hmini, p[i].strzala));
			}
			else {
				npc[cel].pociskiwbite.push_back(p[i].strzala);
				oblicz_strzale(p[i], cel);
			}
			p.erase(p.begin() + i);
			i--;
		}
		//cout << endl;
	}

}
