#include <map>

#include "npc.h"
#include "structy.h"

#define DEBUG if (0)

#define endl " >"<<__FUNCTION__<<"<"<<endl

using namespace std;


const int PREDKOSC = 350;
extern int WYMx;
extern int WYMy;
extern int tmpx[4];
extern int tmpy[4];
extern SDL_Renderer* Rend;
extern int KRATKA;
extern vector <vector <SDL_Texture*> > txnpc;
extern vector <vector <hitbox> > hitboxnpc;
extern vector <SDL_Texture*> txubr;
extern vector <SDL_Texture*> txoczy;
extern vector <SDL_Texture*> txwlosy;
extern vector <SDL_Texture*> txef;
extern vector <vector <SDL_Texture*> > txit;
extern vector <vector <SDL_Texture*> > txanim;
extern int relacja[5][5];
const int ILOSCw = 8;
extern vector <int> w[ILOSCw];
extern vector<NPC> npc;

int obldouble(double w);


vector <xy> NPC::sciezka1(xy konieclg, xy koniecpd, vector<vector<int> > m1[]) {
	vector <xy> sciezka;
	xy start;
	start.x = x;
	start.y = y;
	vector <vector <int> > bfs;
	bfs.resize(WYMx);
	for (int i = 0; i < WYMx;i++) {
		bfs[i].resize(WYMy, -1);
	}
	bfs[start.x][start.y] = -2;
	queue <xy> q;
	q.push(start);
	/*if (czy_dlugi()){
		int tmpx[4]={0,-1,0,1};
		int tmpy[4]={-1,0,1,0};
		int x = tmpx[kier()];
		int y = tmpy[kier()];
		if (start.x+x>=0 && start.x+x<m1[0].size() && start.y+y>=0 && start.y+y<m1[0].size()){
			bfs[start.x+x][start.y+y]=-2;
			q.push({start.x+x,start.y+y});
		}
	}*/

	xy koniec;
	bool czyznaleziono = 0;
	while (!q.empty()) {
		xy tmp;
		tmp = q.front();
		q.pop();
		if (tmp.x >= konieclg.x && tmp.y >= konieclg.y && tmp.x <= koniecpd.x && tmp.y <= koniecpd.y) {
			koniec.x = tmp.x;
			koniec.y = tmp.y;
			czyznaleziono = 1;
			break;
		}
		vector <int> tmpkier = { 0,1,2,3 };
		random_shuffle(tmpkier.begin(), tmpkier.end());
		for (int j = 0; j < 4;j++) {
			int i = tmpkier[j];
			if (tmp.x + tmpx[i] >= 0 && tmp.x + tmpx[i] < m1[0].size() && tmp.y + tmpy[i] >= 0 && tmp.y + tmpy[i] < m1[0].size() && bfs[tmp.x + tmpx[i]][tmp.y + tmpy[i]] == -1) {
				if (m1[2][tmp.x + tmpx[i]][tmp.y + tmpy[i]] == -1 && (m1[4][tmp.x + tmpx[i]][tmp.y + tmpy[i]] == -1 || m1[4][tmp.x + tmpx[i]][tmp.y + tmpy[i]] == m1[4][x][y])) {
					xy tmp2;
					tmp2.x = tmp.x + tmpx[i];
					tmp2.y = tmp.y + tmpy[i];
					bfs[tmp2.x][tmp2.y] = i;
					q.push(tmp2);
				}
			}
		}
	}
	if (bfs[koniec.x][koniec.y] == -1 || czyznaleziono == 0) {

	}
	else {
		sciezka.push_back(koniec);
		while (bfs[koniec.x][koniec.y] != -2) {
			int tmp = koniec.x;
			koniec.x = koniec.x - tmpx[bfs[koniec.x][koniec.y]];
			koniec.y = koniec.y - tmpy[bfs[tmp][koniec.y]];
			sciezka.push_back(koniec);
		}
	}
	if (!sciezka.empty()) {
		sciezka.pop_back();
	}
	return sciezka;
}

hitbox NPC::zwr_hitbox() {
	return hitboxnpc[nrtekstury][(kier() + 1) % 2];
}


int NPC::dodgespd() {
	return PREDKOSC / 2;
}

int NPC::czasparady() {
	return 200;
}

int NPC::cdparady() {
	return 1000;
}

double NPC::ap() {
	double ap = 1.0;
	if (!ekw[0].empty()) {
		ap = ekw[0][0].dou[1];
	}
	ap *= (100.0 + (double)bonus(1)) / 100.0;
	if (!ekw[0].empty() && ekw[0][0].typ == 0 && ekw[0][0].inty[0] == 2 && !ekw[1].empty()) {
		ap *= 0.75;
	}
	if (!ekw[0].empty() && ekw[0][0].typ == 0 && ekw[0][0].inty[0] == 0 && !ekw[1].empty()) {
		ap *= 0.9;
	}
	return ap;
}

double NPC::dmg() {
	double dmg = 1.5;
	if (!ekw[0].empty()) {
		dmg = ekw[0][0].dou[0];
	}
	dmg *= (100.0 + (double)bonus(0)) / 100.0;
	if (!ekw[0].empty() && ekw[0][0].typ == 0 && ekw[0][0].inty[0] == 2 && !ekw[1].empty()) {
		dmg *= 0.75;
	}
	if (!ekw[0].empty() && ekw[0][0].typ == 0 && ekw[0][0].inty[0] == 0 && !ekw[1].empty()) {
		dmg *= 0.9;
	}
	return dmg;
}

int NPC::cr_ch() {
	return bonus(3);
}
double NPC::cr_wsp() {
	return (150.0 + (double)bonus(4)) / 100.0;
}

int NPC::czas_stunu_ciezki() {
	double wynik = 0;
	if (!ekw[0].empty() && ekw[0][0].typ == 0 && ekw[0][0].inty[0] == 1) {
		wynik += 300;
		if (ekw[1].empty()) {
			wynik += 100;
		}
	}
	return wynik;
}

int NPC::czas_stunu_kryt() {
	double wynik = 0;
	if (!ekw[0].empty() && ekw[0][0].typ == 0 && ekw[0][0].inty[0] == 1) {
		wynik += 200;
	}
	if (!ekw[0].empty() && ekw[0][0].typ == 0 && ekw[0][0].inty[0] == 0 && cr_wsp() >= 1.5) {
		wynik += 100;
	}

	return wynik;
}


int NPC::kier() {
	int kier = abs(popkier);
	if (SDL_GetTicks() - tatak <= tmaxatak) {
		if (kierataku == 0 || kierataku == 2) {
			kier = 2 - kierataku;
		}
		else {
			kier = kierataku;
		}
	}
	if (tmaxruch && SDL_GetTicks() - truchu <= tmaxruch) {
		if (x - popx) {
			kier = -(x - popx) + 2;
		}
		if (y - popy) {
			kier = -(y - popy) + 1;
		}
	}
	popkier = kier;
	return kier;
}


bool NPC::czyruch() {
	return (tmaxruch && SDL_GetTicks() - truchu <= tmaxruch);
}

void NPC::dodge(vector <vector<int> > m1[]) {
	vector <xy> v;
	for (int x1 = -1;x1 < 2;x1++) {
		for (int y1 = -1;y1 < 2;y1++) {
			xy pkt = { x + x1,y + y1 };
			if ((x1 == 0 || y1 == 0) && m1[2][pkt.x][pkt.y] == -1 && m1[4][pkt.x][pkt.y] == -1) {
				v.push_back(pkt);
			}
		}
	}
	if (!v.empty()) {
		xy pkt = v[rand() % (v.size())];
		sciezka2 = sciezka1(pkt, pkt, m1);
		tdodge = SDL_GetTicks();
		czydodge = 1;
	}
}

pair <int, int> NPC::dl_ataku(bool czyciezki) {
	int t_calego_ataku;
	int t_do_ataku;
	if (((!ekw[0].empty() && ekw[0][0].typ == 0))) {
		t_calego_ataku = (1 + 0.5 * czyciezki) * (ekw[0][0].dou[2] * 1000 + 2 * ekw[0][0].dou[2] * 1000);
		t_do_ataku = ekw[0][0].dou[2] * 1000;
	}
	else {
		t_calego_ataku = (1 + 0.5 * czyciezki) * 1000;
		t_do_ataku = 275;
	}
	t_calego_ataku *= 1 / (1.0 + (max(-99.0, (double)bonus(2)) / 100.0));
	t_do_ataku *= 1 / (1.0 + (max(-99.0, (double)bonus(2)) / 100.0));
	if (!ekw[0].empty() && ekw[0][0].typ == 0 && ekw[0][0].inty[0] == 2 && !ekw[1].empty()) {
		t_calego_ataku *= 1.5;
		t_do_ataku *= 1.5;
	}
	if (!ekw[0].empty() && ekw[0][0].typ == 0 && ekw[0][0].inty[0] <= 1 && !ekw[1].empty()) {
		t_calego_ataku *= 1.2;
		t_do_ataku *= 1.2;
	}
	return make_pair(t_do_ataku, t_calego_ataku);
}

void NPC::atak(bool czyciezki, Uint32 tataku) {
	tatak = tataku;
	pair<int, int> tmp = dl_ataku(czyciezki);
	tmaxatak2 = tmp.first;
	tmaxatak = tmp.second;
	czyatak = 1;
	czy_anim_ataku = 1;
	czyatciezki = czyciezki;
}

void NPC::anim_ataku() {
	if (((!ekw[0].empty() && ekw[0][0].typ == 0))) {
		tmaxatak = ekw[0][0].dou[2] * 1000 + 2 * ekw[0][0].dou[2] * 1000;
		tmaxatak2 = (1) * ekw[0][0].dou[2] * 1000;
	}
	if (ekw[0].empty() || ekw[0][0].typ != 0) {
		tmaxatak = 1000;
		tmaxatak2 = (1) * 200;
	}
	tmaxatak *= 1 / (1.0 + (max(-99.0, (double)bonus(2)) / 100.0));
	tmaxatak2 *= 1 / (1.0 + (max(-99.0, (double)bonus(2)) / 100.0));
	tatak = SDL_GetTicks();
	czyatciezki = 0;
	czy_anim_ataku = 1;
}


bool NPC::czy_dlugi() {
	return hitboxnpc[nrtekstury][0].x_prawy > 1.0;
}

void NPC::zach(vector <vector <int> > m1[], vector <NPC>& npc) {
	vector <xy> dospr;
	vector <int> kier_dospr;
	queue <xy> q;
	q.push({ x,y });
	map <pair <int, int>, int> m;
	vector <xy> pkt_npca;
	m[{x, y}] = 1;
	int ID = m1[4][x][y];
	vector <xy> pozycja;
	pozycja.push_back({ x,y });
	while (!q.empty()) {
		xy tmp = q.front();
		q.pop();
		for (int i = 0; i < 4;i++) {
			if (tmp.x + tmpx[i] >= 0 && tmp.x + tmpx[i] < m1[0].size() && tmp.y + tmpy[i] >= 0 && tmp.y + tmpy[i] < m1[0].size()) {
				if (m1[4][tmp.x + tmpx[i]][tmp.y + tmpy[i]] == m1[4][x][y] && m[{tmp.x + tmpx[i], tmp.y + tmpy[i]}] == 0) {
					q.push({ tmp.x + tmpx[i],tmp.y + tmpy[i] });
					m[{tmp.x + tmpx[i], tmp.y + tmpy[i]}] = 1;
					pkt_npca.push_back({ tmp.x + tmpx[i],tmp.y + tmpy[i] });
					pozycja.push_back({ tmp.x + tmpx[i],tmp.y + tmpy[i] });
				}
				if (m1[4][tmp.x + tmpx[i]][tmp.y + tmpy[i]] != m1[4][x][y]) {
					dospr.push_back({ tmp.x + tmpx[i],tmp.y + tmpy[i] });
					kier_dospr.push_back(i);
				}
			}
		}
	}
	DEBUG cout << "sr" << kier() << " " << pozycja[0].x << " " << pozycja[0].y << " " << pozycja[1].x << " " << pozycja[1].y << endl;
	m.clear();
	for (int i = 0; i < dospr.size();i++) {
		if (m1[4][dospr[i].x][dospr[i].y] != -1 && relacja[strona][npc[m1[4][dospr[i].x][dospr[i].y]].strona] < 0) {
			xy_ataku = { dospr[i].x,dospr[i].y };
			kierataku = kier_dospr[i] + 1;
			x = dospr[i].x - tmpx[kierataku - 1];
			popx = x;
			y = dospr[i].y - tmpy[kierataku - 1];
			popy = y;
			if (kierataku % 2) {
				kierataku += 2;
			}
			kierataku %= 4;
			if (czy_dlugi() && (m1[2][x][y] != -1 || m1[2][x - tmpx[kier_dospr[i]]][y - tmpy[kier_dospr[i]]] != -1)) {
				int tmpx[4] = { 0,-1,0,1 };
				int tmpy[4] = { -1,0,1,0 };
				if (abs(xy_ataku.x - pozycja[0].x) + abs(xy_ataku.y - pozycja[0].y) != 1) {
					x = pozycja[1].x;
					y = pozycja[1].y;
					popy = pozycja[0].y;
					popx = pozycja[0].x;
				}
				else {
					x = pozycja[0].x;
					y = pozycja[0].y;
					popy = pozycja[1].y;
					popx = pozycja[1].x;
				}
				for (int i = 0; i < 4;i++) {
					if (x - popx == -tmpx[i] && y - popy == tmpy[i]) {
						kierataku = i;
					}
				}
			}
			czyatak = 1;
			return;
		}
	}
	q.push(pozycja[0]);
	q.push(pozycja[1]);
	while (!q.empty()) {
		xy tmp = q.front();
		q.pop();
		m[{pozycja[1].x, pozycja[1].y}] = 0;
		for (int i = 0; i < 4;i++) {
			if (tmp.x + tmpx[i] >= 0 && tmp.x + tmpx[i] < m1[0].size() && tmp.y + tmpy[i] >= 0 && tmp.y + tmpy[i] < m1[0].size()) {
				if (m1[2][tmp.x + tmpx[i]][tmp.y + tmpy[i]] == -1 && m1[4][tmp.x + tmpx[i]][tmp.y + tmpy[i]] == -1 && m[{tmp.x + tmpx[i], tmp.y + tmpy[i]}] == 0 && m[{tmp.x, tmp.y}] < zasieg - 1) {
					q.push({ tmp.x + tmpx[i],tmp.y + tmpy[i] });
					m[{tmp.x + tmpx[i], tmp.y + tmpy[i]}] = m[{tmp.x, tmp.y}] + 1;
				}
				else if (m1[4][tmp.x + tmpx[i]][tmp.y + tmpy[i]] != -1 && relacja[strona][npc[m1[4][tmp.x + tmpx[i]][tmp.y + tmpy[i]]].strona] < 0) {
					sciezka2 = { sciezka1(tmp,tmp,m1).back() };
				}
			}
		}
		if (!sciezka2.empty()) {
			break;
		}
	}
	if (sciezka2.empty() && !(npc[0].x <= maxx && npc[0].x >= minx && npc[0].y <= maxy && npc[0].y >= miny)) {
		vector <xy> tmp = sciezka1({ minx,miny }, { maxx,maxy }, m1);
		if (!tmp.empty()) {
			sciezka2 = { tmp.back() };
		}
	}
}

void NPC::czek(efekt& tmp) {
	Uint32 przerwa = SDL_GetTicks() - tmp.t;
	//cout << przerwa<<endl;
	tmp.t = SDL_GetTicks();
	tmp.tef -= przerwa;
	tmp.ile -= przerwa;
	if (tmp.obr != 0.0) {
		while (tmp.tef < 0) {
			tmp.tef += tmp.czest;
			int dmg = obldouble(tmp.obr);
			hp -= dmg;
			napis tmp2;
			tmp2.tekst = to_string(-dmg);
			tmp2.r = 255; tmp2.g = 0; tmp2.b = 0;
			if (tmp.obr < 0) {
				tmp2.r = 0; tmp2.g = 255;
			}
			tmp2.a = 0; tmp2.poprz = SDL_GetTicks(); tmp2.ilems = w[4][7];
			tmp2.ilemsmax = tmp2.ilems;
			tmp2.ilemszaniku = w[4][8];
			napisy.push_back(tmp2);
		}
	}
}

void NPC::zabij() {
	czymartwy = 1;
	x = -1;
	sciezka2.clear();
}


bool NPC::zapis(int ID) {
	stringstream ss;
	ss << ID;
	string sciezka = ss.str();
	string sciezka2 = "fl/flnpc" + sciezka + ".bin";
	cout << " otwarto " << sciezka2;
	SDL_RWops* plik = SDL_RWFromFile(sciezka2.c_str(), "wb+");
	if (plik == NULL) {
		cout << "NIE" << endl;
		return 0;
	}
	else if (plik != NULL) {
		cout << " - wczytano pomyslnie " << endl;
		int tmp1 = t.mss, tmp2 = t.dni;
		SDL_RWwrite(plik, &x, sizeof(int), 1);
		SDL_RWwrite(plik, &y, sizeof(int), 1);
		SDL_RWwrite(plik, &maxx, sizeof(int), 1);
		SDL_RWwrite(plik, &minx, sizeof(int), 1);
		SDL_RWwrite(plik, &maxy, sizeof(int), 1);
		SDL_RWwrite(plik, &miny, sizeof(int), 1);
		SDL_RWwrite(plik, &tmp1, sizeof(int), 1);
		SDL_RWwrite(plik, &tmp2, sizeof(int), 1);
		SDL_RWwrite(plik, &ruch1, sizeof(int), 1);
		SDL_RWwrite(plik, &ruch2, sizeof(int), 1);
		SDL_RWwrite(plik, &hp, sizeof(int), 1);
		SDL_RWwrite(plik, &ileprz, sizeof(int), 1);

		for (int i = 0; i < ileprz;i++) {
			SDL_RWwrite(plik, &prz[i], sizeof(int), 1);
		}
		SDL_RWwrite(plik, &sila, sizeof(int), 1);
		int ileef = ef.size();
		SDL_RWwrite(plik, &ileef, sizeof(int), 1);
		for (int j = 0; j < ef.size();j++) {
			SDL_RWwrite(plik, &ef[j], sizeof(int), 7);
		}
		SDL_RWwrite(plik, &zasieg, sizeof(int), 1);
		SDL_RWwrite(plik, &strona, sizeof(int), 1);
		SDL_RWwrite(plik, &rozmjedz, sizeof(int), 1);
		SDL_RWwrite(plik, &n, sizeof(int), 1);
		for (int i = 0; i < n;i++) {
			int tmp = g[i].size();
			SDL_RWwrite(plik, &tmp, sizeof(int), 1);
			SDL_RWwrite(plik, &wierz[i].czyj, sizeof(bool), 1);
			SDL_RWwrite(plik, &wierz[i].ID, sizeof(int), 1);
			int tmp4 = wierz[i].wymief.size();
			SDL_RWwrite(plik, &tmp4, sizeof(int), 1);
			for (int j = 0; j < tmp4;j++) {
				int tmp = wierz[i].wymief[j].first;
				double tmp2 = wierz[i].wymief[j].second;
				SDL_RWwrite(plik, &tmp, sizeof(int), 1);
				SDL_RWwrite(plik, &tmp2, sizeof(double), 1);
			}
			int tmp2 = wierz[i].tekst.size();
			SDL_RWwrite(plik, &tmp2, sizeof(int), 1);
			for (int j = 0; j < tmp2;j++) {
				SDL_RWwrite(plik, &wierz[i].tekst[j], sizeof(char), 1);
			}
			for (int j = 0;j < tmp;j++) {
				SDL_RWwrite(plik, &g[i][j], sizeof(int), 1);
			}
		}
		SDL_RWwrite(plik, &czymartwy, sizeof(bool), 1);
		SDL_RWwrite(plik, &predkat, sizeof(bool), 1);
		SDL_RWwrite(plik, &gdzie, sizeof(bool), 1);
		SDL_RWwrite(plik, &tekstura, sizeof(bool), 1);
		SDL_RWclose(plik);
		return 1;
	}
}

bool NPC::odczyt(int ID, bool czyorig) {
	stringstream ss;
	ss << ID;
	string sciezka = ss.str();
	string tmp;
	if (czyorig == 0) {
		tmp = "fl/flnpc";
	}
	if (czyorig == 1) {
		tmp = "florig/flnpc";
	}
	string sciezka2 = tmp + sciezka + ".bin";
	cout << " czytanie z " << sciezka2;
	SDL_RWops* plik;
	plik = SDL_RWFromFile(sciezka2.c_str(), "rb");
	if (plik == NULL) {
		cout << "NIE" << endl;
		return 0;
	}
	else if (plik != NULL) {
		cout << " - wczytano pomyslnie " << endl;
		int tmp1, tmp2;
		SDL_RWread(plik, &x, sizeof(int), 1);
		SDL_RWread(plik, &y, sizeof(int), 1);
		SDL_RWread(plik, &maxx, sizeof(int), 1);
		SDL_RWread(plik, &minx, sizeof(int), 1);
		SDL_RWread(plik, &maxy, sizeof(int), 1);
		SDL_RWread(plik, &miny, sizeof(int), 1);
		SDL_RWread(plik, &tmp1, sizeof(int), 1);
		SDL_RWread(plik, &tmp2, sizeof(int), 1);
		SDL_RWread(plik, &ruch1, sizeof(int), 1);
		SDL_RWread(plik, &ruch2, sizeof(int), 1);
		SDL_RWread(plik, &hp, sizeof(int), 1);
		SDL_RWread(plik, &ileprz, sizeof(int), 1);
		prz.resize(ileprz);
		for (int i = 0;i < ileprz;i++) {
			SDL_RWread(plik, &prz[i], sizeof(int), 1);
		}
		SDL_RWread(plik, &sila, sizeof(int), 1);
		t.mss = tmp1;
		t.dni = tmp2;
		int ileef;
		SDL_RWread(plik, &ileef, sizeof(int), 1);
		ef.resize(ileef);
		for (int j = 0; j < ef.size();j++) {
			SDL_RWread(plik, &ef[j], sizeof(int), 7);
		}

		SDL_RWread(plik, &zasieg, sizeof(int), 1);
		SDL_RWread(plik, &strona, sizeof(int), 1);
		SDL_RWread(plik, &rozmjedz, sizeof(int), 1);
		SDL_RWread(plik, &n, sizeof(int), 1);
		g.resize(n);
		wierz.resize(n);
		for (int i = 0; i < n;i++) {
			int tmp;
			SDL_RWread(plik, &tmp, sizeof(int), 1);
			SDL_RWread(plik, &wierz[i].czyj, sizeof(bool), 1);
			SDL_RWread(plik, &wierz[i].ID, sizeof(int), 1);
			int tmp4;
			SDL_RWread(plik, &tmp4, sizeof(int), 1);
			for (int j = 0; j < tmp4;j++) {
				int tmp; double tmp2;
				SDL_RWread(plik, &tmp, sizeof(int), 1);
				SDL_RWread(plik, &tmp2, sizeof(double), 1);
				wierz[i].wymief.push_back(make_pair(tmp, tmp2));
			}
			int tmp2;
			SDL_RWread(plik, &tmp2, sizeof(int), 1);
			string tmp3;
			for (int j = 0; j < tmp2;j++) {
				char tmp4;
				SDL_RWread(plik, &tmp4, sizeof(char), 1);
				tmp3 += tmp4;
			}
			wierz[i].tekst = tmp3;
			g[i].resize(tmp);
			for (int j = 0;j < tmp;j++) {
				SDL_RWread(plik, &g[i][j], sizeof(int), 1);
			}
		}
		SDL_RWread(plik, &czymartwy, sizeof(bool), 1);
		SDL_RWread(plik, &predkat, sizeof(bool), 1);
		SDL_RWread(plik, &gdzie, sizeof(bool), 1);
		SDL_RWread(plik, &tekstura, sizeof(bool), 1);
		SDL_RWclose(plik);
		return 1;
	}
}

int stworzNPC(NPC npctmp) {
	for (int i = 0;i < npc.size();i++) {
		if (npc[i].czymartwy) {
			npc[i] = npctmp;
			return i;
		}
	}
	npc.resize(npc.size() + 1, npctmp);
	return npc.size() - 1;
}
