#ifndef STATSSQUADRA_H
#define STATSSQUADRA_H

struct StatsSquadra {
    int possessoPalla = 0;               // percentuale 0-100
    double territorio = 0.0;            // percentuale 0-100

    int placcaggiTotali = 0;
    int metriGuadagnatiTotali = 0;

    int turnoverVinti = 0;

    int mischieVinte = 0;
    int mischiePerse = 0;

    int toucheVinte = 0;
    int touchePerse = 0;

    int calciPiazzatiSegnati = 0;
    int calciPiazzatiTentati = 0;

    int meteSegnate = 0;
    int falliCommessi = 0;

    // Percentuale calci piazzati
    double getPercentualeCalciPiazzati() const {
        if (calciPiazzatiTentati == 0)
            return 0.0;
        return 100.0 * calciPiazzatiSegnati / calciPiazzatiTentati;
    }
};

#endif

