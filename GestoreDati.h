#ifndef GESTOREDATI_H
#define GESTOREDATI_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

template<typename T>
class GestoreDati {
private:
    vector<T> dati;

public:
    GestoreDati() = default;
    ~GestoreDati() = default;

    void inserisci(const T &obj) { dati.push_back(obj); }

    void modifica(int id, const T &obj) {
        for (auto &x : dati) {
            if (x.getId() == id) {
                x = obj;
                return;
            }
        }
    }

    void rimuovi(int id) {
        dati.erase(remove_if(dati.begin(), dati.end(),
                    [id](const T &x){ return x.getId() == id; }), dati.end());
    }

    vector<T> cerca(function<bool(const T&)> pred) const {
        vector<T> res;
        for (const auto &x : dati) if (pred(x)) res.push_back(x);
        return res;
    }

    void ordina(function<bool(const T&, const T&)> cmp) {
        sort(dati.begin(), dati.end(), cmp);
    }

    const vector<T>& getAll() const { return dati; }

    void stampaTutti() const {
        for (const auto &x : dati) {
            cout << x.toString() << "\n";
        }
    }

    void clear() { dati.clear(); }
};

#endif // GESTOREDATI_H

