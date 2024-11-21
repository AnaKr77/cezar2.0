#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Struktura reprezentująca krawędź
struct Krawedz {
    int u, v, w; // wierzchołek początkowy, końcowy i waga krawędzi
    bool operator<(const Krawedz& inna) const {
        return w < inna.w; // Sortowanie po wadze
    }
};

// Funkcje pomocnicze dla Union-Find
vector<int> rodzic, ranga;

void inicjalizuj_union_find(int n) {
    rodzic.resize(n);
    ranga.resize(n, 0);
    for (int i = 0; i < n; ++i) {
        rodzic[i] = i; // Każdy wierzchołek jest swoim własnym rodzicem
    }
}

int znajdz(int x) {
    if (rodzic[x] != x) {
        rodzic[x] = znajdz(rodzic[x]); // Kompresja ścieżki
    }
    return rodzic[x];
}

void unia(int x, int y) {
    int korzen_x = znajdz(x);
    int korzen_y = znajdz(y);

    if (korzen_x != korzen_y) {
        if (ranga[korzen_x] > ranga[korzen_y]) {
            rodzic[korzen_y] = korzen_x;
        } else if (ranga[korzen_x] < ranga[korzen_y]) {
            rodzic[korzen_x] = korzen_y;
        } else {
            rodzic[korzen_y] = korzen_x;
            ranga[korzen_x]++;
        }
    }
}

// Funkcja implementująca algorytm Kruskala
int algorytm_kruskala(int n, vector<Krawedz>& krawedzie) {
    // Sortowanie krawędzi według wag
    sort(krawedzie.begin(), krawedzie.end());

    // Inicjalizacja Union-Find
    inicjalizuj_union_find(n);

    int koszt_MST = 0;
    vector<Krawedz> MST;

    for (const auto& k : krawedzie) {
        if (znajdz(k.u) != znajdz(k.v)) {
            unia(k.u, k.v);       // Połącz dwa drzewa
            koszt_MST += k.w;    // Dodaj wagę krawędzi do kosztu MST
            MST.push_back(k);    // Dodaj krawędź do MST
        }
    }

    // Wypisanie wyniku (opcjonalnie)
    cout << "Krawędzie w MST:\n";
    for (const auto& k : MST) {
        cout << k.u << " -- " << k.v << " (waga: " << k.w << ")\n";
    }

    return koszt_MST;
}

int main() {
    int n, m; // liczba wierzchołków i krawędzi
    cout << "Podaj liczbę wierzchołków i krawędzi: ";
    cin >> n >> m;

    vector<Krawedz> krawedzie;

    cout << "Podaj krawędzie w formacie u v w (wierzchołki i waga):\n";
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        krawedzie.push_back({u, v, w});
    }

    int wynik = algorytm_kruskala(n, krawedzie);
    cout << "Minimalny koszt drzewa rozpinającego: " << wynik << endl;

    return 0;
}
