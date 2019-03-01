#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <ctime>
#include <climits>
#include <cmath>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <functional>
#include <memory>
using namespace std;
class InvalidDateException
{
};
#endif /* __PROGTEST__ */

// uncomment if your code implements the overloaded suffix operators
#define TEST_LITERALS

// Pole obsahuje maximálny počet dní v danom mesiaci
const unsigned int poleDni[2][12] = {{31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
                                     {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}};

// ----------------------------- Pomocné funkcie -----------------------------
bool jeRokPrestupny(int y) {
    bool prestupny = false;

    // Prestupny rok?
    if (y % 4 == 0) {
        prestupny = true;
    }
    if (y % 100 == 0) {
        prestupny = false;
    }
    if (y % 400 == 0) {
        prestupny = true;
    }
    if (y % 4000 == 0) {
        prestupny = false;
    }

    return prestupny;
}

int getMaxDay(int rok, int mesiac) {

    bool prestupnyRok = jeRokPrestupny(rok);

    if (prestupnyRok) {
        return poleDni[0][mesiac-1];
    }

    return poleDni[1][mesiac-1];

}

bool jeZadanyDatumPlatny(int y, int m, int d) {
    if (m < 1 || m > 12 || d < 1 || y < 1600) {
        return false;
    }

    int maxDayOfMonthInYear = getMaxDay(y, m);

    if (d > maxDayOfMonthInYear) {
        return false;
    }

    return true;
}

// ----------------------------- Pričítaj/odčítaj dni od dátumu -----------------------------

// ---------------------------- Den, Mesiac, Rok --------------------------------
vector <bool> zmena;

class CDate2 {
public:
    int den = 0;
    int mesiac = 0;
    int rok = 0;

    CDate2 & operator + (const CDate2 & newDate) {
        this->den += newDate.den;
        this->mesiac += newDate.mesiac;
        this->rok += newDate.rok;

        return *this;
    }

    CDate2 & operator - () {
        this->den = -this->den;
        this->mesiac = -this->mesiac;
        this->rok = -this->rok;

        if (zmena.back() == true) {
            zmena.back() = false;
        } else {
            zmena.back() = true;
        }

        return *this;
    }

    CDate2 & operator - (const CDate2 & newDate) {
        this->den = -newDate.den;
        this->mesiac = -newDate.mesiac;
        this->rok = -newDate.rok;

        if (zmena.back() == true) {
            zmena.back() = false;
        } else {
            zmena.back() = true;
        }

        return *this;
    }
};

vector <CDate2> postupnost;

CDate2 Day(int den) {
    CDate2 datum;
    datum.den = den;
    datum.mesiac = 0;
    datum.rok = 0;

    postupnost.push_back(datum);
    zmena.push_back(false);

    return datum;
}

CDate2 Month(int mesiac) {
    CDate2 datum;
    datum.den = 0;
    datum.mesiac = mesiac;
    datum.rok = 0;

    postupnost.push_back(datum);
    zmena.push_back(false);

    return datum;
}

CDate2 Year(int rok) {
    CDate2 datum;
    datum.den = 0;
    datum.mesiac = 0;
    datum.rok = rok;

    postupnost.push_back(datum);
    zmena.push_back(false);

    return datum;
}

// --------------------------- CDate -----------------------------
class CDate {
public:

    CDate(void) = default;

    // Konštruktor
    CDate(int rok, int mesiac, int den) {
        // Vymaž dáta
        postupnost.clear();
        zmena.clear();

        bool platnyDatum = jeZadanyDatumPlatny(rok, mesiac, den);
        if (!platnyDatum) {
            throw InvalidDateException();
        } else {
            this->den = den;
            this->mesiac = mesiac;
            this->rok = rok;
        }
    }

    // Pričítame CDate2 k CDate
    CDate operator + (const CDate2 & newDate) {
        // Uložíme si premenné, ktoré budeme modifikovať
        int den = this->den;
        int mesiac = this->mesiac;
        int rok = this->rok;

        pricitajRok(rok, newDate.rok);

        bool platnyDatum = jeZadanyDatumPlatny(rok, mesiac, den);
        if (!platnyDatum) {
            throw InvalidDateException();
        }

        pricitajMesiac(rok, mesiac, newDate.mesiac);

        platnyDatum = jeZadanyDatumPlatny(rok, mesiac, den);
        if (!platnyDatum) {
            throw InvalidDateException();
        }

        pricitajDen(rok, mesiac, den, newDate.den);

        // Ošetri neplatný dátum
        platnyDatum = jeZadanyDatumPlatny(rok, mesiac, den);
        if (!platnyDatum) {
            throw InvalidDateException();
        }

        // Nevyhodilo výnimku, uložíme si premenné do objektu
        CDate novyDatum;
        novyDatum.den = den;
        novyDatum.mesiac = mesiac;
        novyDatum.rok = rok;

        return novyDatum;
    }

    CDate operator - (const CDate2 & newDate) {
        // Uložíme si premenné, ktoré budeme modifikovať
        int den = this->den;
        int mesiac = this->mesiac;
        int rok = this->rok;

        odcitajRok(rok, newDate.rok);

        bool platnyDatum = jeZadanyDatumPlatny(rok, mesiac, den);
        if (!platnyDatum) {
            throw InvalidDateException();
        }

        odcitajMesiac(rok, mesiac, newDate.mesiac);

        platnyDatum = jeZadanyDatumPlatny(rok, mesiac, den);
        if (!platnyDatum) {
            throw InvalidDateException();
        }

        odcitajDen(rok, mesiac, den, newDate.den);

        // Ošetri neplatný dátum
        platnyDatum = jeZadanyDatumPlatny(rok, mesiac, den);
        if (!platnyDatum) {
            throw InvalidDateException();
        }

        // Nevyhodilo výnimku, uložíme si premenné do objektu
        CDate novyDatum;
        novyDatum.den = den;
        novyDatum.mesiac = mesiac;
        novyDatum.rok = rok;

        return novyDatum;
    }

    CDate operator += (const CDate2 & novyDatum) {
        for (unsigned int i = 0; i<postupnost.size(); i++) {

            if (zmena.at(i)) {
                postupnost[i].den = -postupnost[i].den;
                postupnost[i].mesiac = -postupnost[i].mesiac;
                postupnost[i].rok = -postupnost[i].rok;
            }

            CDate novyDate = CDate::operator+(postupnost[i]);

            this->den = novyDate.den;
            this->mesiac = novyDate.mesiac;
            this->rok = novyDate.rok;

            bool platnyDatum = jeZadanyDatumPlatny(this->rok, this->mesiac, this->den);

            if (!platnyDatum) {
                throw InvalidDateException();
            }
        }

        return *this;
    }

    bool operator == (const CDate & datum) const {
        if (this->den != datum.den || this->mesiac != datum.mesiac || this->rok != datum.rok) {
            return false;
        }
        return true;
    }

    bool operator != (const CDate & datum) const {
        return !(this->operator==(datum));
    }

    bool operator < (const CDate & datum) const {
        if (this->rok == datum.rok) {
            if (this->mesiac == datum.mesiac) {
                if (this->den < datum.den) {
                    return true;
                } else if (this->den > datum.den) {
                    return false;
                } else {
                    return false;
                }
            } else if (this->mesiac > datum.mesiac) {
                return false;
            } else {
                return true;
            }
        } else if (this->rok > datum.rok) {
            return false;
        } else {
            return true;
        }
    }

    long operator - (const CDate & datum) const {
        long pocetDni = pocetDniMedziDatumami(*this, datum);
        return pocetDni;
    }

    // operator <<
    friend ostream & operator << (ostream & os, const CDate & datum) {
        ios state(nullptr);
        state.copyfmt(os);

        os << dec << datum.rok << "-" << (datum.mesiac < 10 ? "0" : "") <<
                  datum.mesiac << "-" << (datum.den < 10 ? "0" : "") << datum.den;

        os.copyfmt(state);

        return os;
    }

    // Volá sa z + operátora
    void pricitajRok(int & staryRok, int pocetRokov) {
        if (pocetRokov >= 0) {
            staryRok += pocetRokov;
        } else {
            odcitajRok(staryRok, abs(pocetRokov));
        }
    }

    // Volá sa z - operátora
    void odcitajRok(int & staryRok, int pocetRokov) {
        if (pocetRokov >= 0) {
            staryRok -= pocetRokov;
        } else {
            pricitajRok(staryRok, abs(pocetRokov));
        }
    }

    // Volá sa z + operátora
    void pricitajMesiac(int & staryRok, int & staryMesiac, int pocetMesiacov) {
        if (pocetMesiacov >= 0) {
            while (pocetMesiacov > 0) {
                if (staryMesiac == 12) {
                    staryMesiac = 1;
                    staryRok++;
                } else {
                    staryMesiac++;
                }
                pocetMesiacov--;
            }
        } else {
            odcitajMesiac(staryRok, staryMesiac, abs(pocetMesiacov));
        }
    }

    // Volá sa z - operátoru
    void odcitajMesiac(int & staryRok, int & staryMesiac, int pocetMesiacov) {
        if (pocetMesiacov >= 0) {
            while (pocetMesiacov > 0) {
                if (staryMesiac == 1) {
                    staryMesiac = 12;
                    staryRok--;
                } else {
                    staryMesiac--;
                }
                pocetMesiacov--;
            }
        } else {
            pricitajMesiac(staryRok, staryMesiac, abs(pocetMesiacov));
        }
    }

    // Volá sa z + operátora
    void pricitajDen(int & staryRok, int & staryMesiac, int & staryDen, int pocetDni) {
        if (pocetDni >= 0) {
            while (pocetDni > 0) {
                int maxDniVMesiaci = getMaxDay(staryRok, staryMesiac);
                // Musím pričítať další mesiac
                if (maxDniVMesiaci < staryDen + 1) {
                    if (staryMesiac == 12) {
                        staryDen = 1;
                        staryMesiac = 1;
                        staryRok++;
                    } else {
                        staryDen = 1;
                        staryMesiac++;
                    }
                } else {
                    staryDen++;
                }
                pocetDni--;
            }
        } else {
            odcitajDen(staryRok, staryMesiac, staryDen, abs(pocetDni));
        }
    }

    // Volá sa z - operátora
    void odcitajDen(int & staryRok, int & staryMesiac, int & staryDen, int pocetDni) {
        if (pocetDni >= 0) {
            while (pocetDni > 0) {
                // Prepneme sa do predchádzajúceho mesiaca
                if (staryDen == 1) {
                    if (staryMesiac == 1) {
                        staryDen = 31;
                        staryMesiac = 12;
                        staryRok--;
                    } else {
                        staryMesiac--;
                        staryDen = getMaxDay(staryRok, staryMesiac);
                    }
                } else {
                    staryDen--;
                }
                pocetDni--;
            }
        } else {
            pricitajDen(staryRok, staryMesiac, staryDen, abs(pocetDni));
        }
    }

    // Zisti počet prestupných rokov zadaného dátumu
    int pocetPrestupnychRokov(const CDate & datum) const {
        int pocetRokov = datum.rok;

        // Nepočítaj ako prestupný rok s mesiacom <= februáru
        if (datum.mesiac <= 2) {
            pocetRokov--;
        }

        return pocetRokov / 4 - pocetRokov / 100 + pocetRokov / 400 - pocetRokov / 4000;
    }

    // Zisti počet dní medzi dvoma dátumami
    long pocetDniMedziDatumami(const CDate & prvyDatum, const CDate & druhyDatum) const {

        // Zisti celkový počet dní do prvého dátumu
        long pocetDni_1 = prvyDatum.rok * 365;

        // Pridaj dni v mesiaci - 1
        for (int i = 0; i<prvyDatum.mesiac - 1; i++) {
            pocetDni_1 += poleDni[1][i];
        }

        // Dopočítaj počet zostávajúcich dní
        pocetDni_1 += prvyDatum.den;

        // Pridaj dni v prestupnom roku
        pocetDni_1 += pocetPrestupnychRokov(prvyDatum);

        // Zisti celkový počet dní do druhého dátumu
        long pocetDni_2 = druhyDatum.rok * 365;

        // Pridaj dni v mesiaci - 1
        for (int i = 0; i<druhyDatum.mesiac - 1; i++) {
            pocetDni_2 += poleDni[1][i];
        }

        // Dopočítaj počet zostávajúcich dní
        pocetDni_2 += druhyDatum.den;

        // Pridaj dni v prestupných rokoch
        pocetDni_2 += pocetPrestupnychRokov(druhyDatum);

        return pocetDni_1 - pocetDni_2;
    }

    int den = 0;
    int mesiac = 0;
    int rok = 0;
};

CDate2 operator "" _year (unsigned long long rok) {
    return Year(rok);
}

CDate2 operator "" _years (unsigned long long rok) {
    return Year(rok);
}

CDate2 operator "" _month (unsigned long long mesiac) {
    return Month(mesiac);
}

CDate2 operator "" _months (unsigned long long mesiac) {
    return Month(mesiac);
}

CDate2 operator "" _day (unsigned long long den) {
    return Day(den);
}

CDate2 operator "" _days (unsigned long long den) {
    return Day(den);
}
