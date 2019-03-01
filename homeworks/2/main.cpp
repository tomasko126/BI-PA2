#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <cmath>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <functional>
#include <memory>
using namespace std;
#endif /* __PROGTEST__ */

class Osoba {
public:
    Osoba(const string & meno, const string & priezvisko,
          const string & email, unsigned int plat) :
            meno(meno), priezvisko(priezvisko), email(email), plat(plat) {}

    string meno;
    string priezvisko;
    string email;
    unsigned int plat;

    struct porovnavacMena {
        bool operator() (const Osoba & a, const Osoba & b ) {
            if (a.priezvisko == b.priezvisko) {
                return a.meno < b.meno;
            }
            return a.priezvisko < b.priezvisko;
        }
    };

    struct porovnavacEmailu {
        bool operator() (const Osoba & a, const Osoba & b ) {
                return a.email < b.email;
        }
    };
};

class CPersonalAgenda {
public:
    CPersonalAgenda  ( void );
    ~CPersonalAgenda ( void );
    bool          Add              ( const string    & name,
                                     const string    & surname,
                                     const string    & email,
                                     unsigned int      salary );
    bool          Del              ( const string    & name,
                                     const string    & surname );
    bool          Del              ( const string    & email );

    bool          ChangeName       ( const string    & email,
                                     const string    & newName,
                                     const string    & newSurname );

    bool          ChangeEmail      ( const string    & name,
                                     const string    & surname,
                                     const string    & newEmail );
    bool          SetSalary        ( const string    & name,
                                     const string    & surname,
                                     unsigned int      salary );
    bool          SetSalary        ( const string    & email,
                                     unsigned int      salary );
    unsigned int  GetSalary        ( const string    & name,
                                     const string    & surname ) const;
    unsigned int  GetSalary        ( const string    & email ) const;
    bool          GetRank          ( const string    & name,
                                     const string    & surname,
                                     int             & rankMin,
                                     int             & rankMax ) const;
    bool          GetRank          ( const string    & email,
                                     int             & rankMin,
                                     int             & rankMax ) const;
    bool          GetFirst         ( string          & outName,
                                     string          & outSurname ) const;

    bool          GetNext          ( const string    & name,
                                     const string    & surname,
                                     string          & outName,
                                     string          & outSurname ) const;
private:
    vector <Osoba> osobyPodlaMena;
    vector <Osoba> osobyPodlaEmailu;
    vector <unsigned int> platy;

};

CPersonalAgenda::CPersonalAgenda(void) {}
CPersonalAgenda::~CPersonalAgenda(void) {}

bool CPersonalAgenda::Add(const string &name, const string &surname, const string &email, unsigned int salary) {
    Osoba novaOsoba(name, surname, email, salary);

    // Vkladaj podla mena
    auto objektMena = lower_bound(osobyPodlaMena.begin(), osobyPodlaMena.end(), novaOsoba, Osoba::porovnavacMena());

    unsigned int indexMeno = distance(osobyPodlaMena.begin(), objektMena);

    // Hladaj duplikatne meno/priezvisko
    try {
        if (osobyPodlaMena.at(indexMeno).meno == novaOsoba.meno && osobyPodlaMena.at(indexMeno).priezvisko == novaOsoba.priezvisko) {
            //cout << "Duplikatne meno" << endl;
            return false;
        }
    } catch (...) {
        //cout << "Index mena sa nenachadza v poli = nenasli sme duplikat" << endl;
    }


    // Vkladaj podla emailu
    auto objektEmailu = lower_bound(osobyPodlaEmailu.begin(), osobyPodlaEmailu.end(), novaOsoba, Osoba::porovnavacEmailu());
    unsigned int indexEmail = distance(osobyPodlaEmailu.begin(), objektEmailu);

    // Hladaj duplikatny email
    try {
        if (osobyPodlaEmailu.at(indexEmail).email == novaOsoba.email) {
            //cout << "Duplikatny email" << endl;
            return false;
        }
    } catch (...) {
        //cout << "Index emailu sa nenachadza v poli = nenasli sme duplikat" << endl;
    }


    // Nenašli sme duplikátne meno a priezvisko/email
    osobyPodlaMena.insert(osobyPodlaMena.begin() + indexMeno, novaOsoba);
    osobyPodlaEmailu.insert(osobyPodlaEmailu.begin() + indexEmail, novaOsoba);

    // Vlož plat
    auto objektPlat = lower_bound(platy.begin(), platy.end(), salary);
    unsigned int indexPlat = distance(platy.begin(), objektPlat);


    platy.insert(platy.begin() + indexPlat, salary);

    //cout << " " << endl;

    return true;
}

bool CPersonalAgenda::Del(const string &email) {
    // Vkladaj podla emailu
    Osoba novaOsoba("", "", email, 0);

    auto objektEmailu = lower_bound(osobyPodlaEmailu.begin(), osobyPodlaEmailu.end(), novaOsoba, Osoba::porovnavacEmailu());
    unsigned int indexEmail = distance(osobyPodlaEmailu.begin(), objektEmailu);

    // Hladaj duplikatny email
    try {
        if (osobyPodlaEmailu.at(indexEmail).email == novaOsoba.email) {
            //cout << "Našli sme osobu na zmazanie" << endl;

            // Zmažeme ju zo zoznamu podla mena
            auto objektMena = lower_bound(osobyPodlaMena.begin(), osobyPodlaMena.end(), osobyPodlaEmailu.at(indexEmail), Osoba::porovnavacMena());
            unsigned int indexMeno = distance(osobyPodlaMena.begin(), objektMena);

            osobyPodlaMena.erase(osobyPodlaMena.begin() + indexMeno);

            // Zmažeme jej plat
            auto objektPlatu = lower_bound(platy.begin(), platy.end(), osobyPodlaEmailu.at(indexEmail).plat);
            unsigned int indexPlat = distance(platy.begin(), objektPlatu);
            platy.erase(platy.begin() + indexPlat);

            // Zmažeme ju z mailoveho zoznamu
            osobyPodlaEmailu.erase(osobyPodlaEmailu.begin() + indexEmail);

            return true;
        } else {
            return false;
        }
    } catch (...) {
        //cout << "Nenašli sme osobu na zmazanie" << endl;
        return false;
    }
}

bool CPersonalAgenda::Del(const string &name, const string &surname) {
    Osoba novaOsoba(name, surname, "", 0);

    auto objektMena = lower_bound(osobyPodlaMena.begin(), osobyPodlaMena.end(), novaOsoba, Osoba::porovnavacMena());
    unsigned int indexMeno = distance(osobyPodlaMena.begin(), objektMena);

    try {
        if (osobyPodlaMena.at(indexMeno).meno == name && osobyPodlaMena.at(indexMeno).priezvisko == surname) {
            //cout << "Našli sme osobu na zmazanie" << endl;

            // Zmazanie osoby zo zoznamu mejlov
            auto objektMejlu = lower_bound(osobyPodlaEmailu.begin(), osobyPodlaEmailu.end(), osobyPodlaMena.at(indexMeno), Osoba::porovnavacEmailu());
            unsigned int indexMejlu = distance(osobyPodlaEmailu.begin(), objektMejlu);

            osobyPodlaEmailu.erase(osobyPodlaEmailu.begin() + indexMejlu);

            // Zmazanie platu osoby
            auto objektPlatu = lower_bound(platy.begin(), platy.end(), osobyPodlaMena.at(indexMeno).plat);
            unsigned int indexPlat = distance(platy.begin(), objektPlatu);

            platy.erase(platy.begin() + indexPlat);

            // Zmazanie osoby zo zoznamu mien
            osobyPodlaMena.erase(osobyPodlaMena.begin() + indexMeno);

            return true;
        } else {
            return false;
        }
    } catch (...) {
        //cout << "Nenašli sme osobu na zmazanie" << endl;
        return false;
    }
}

bool CPersonalAgenda::ChangeName(const string &email, const string &newName, const string &newSurname) {
    // Musíme zistiť plat danej osoby,
    // aby sme pri pridávaní osoby so zmeneným menom/priezviskom vedeli plat zmazanej osoby
    Osoba novaOsoba(newName, newSurname, email, 0);

    auto objektEmailu = lower_bound(osobyPodlaEmailu.begin(), osobyPodlaEmailu.end(), novaOsoba, Osoba::porovnavacEmailu());
    unsigned int indexEmail = distance(osobyPodlaEmailu.begin(), objektEmailu);

    unsigned int plat = 0;

    // Zistenie platu danej osoby
    try {
        if (osobyPodlaEmailu.at(indexEmail).email == novaOsoba.email) {
            plat = osobyPodlaEmailu.at(indexEmail).plat;
        } else {
            //cout << "Nenašli sme osobu pre zistenie jej platu" << endl;
            return false;
        }
    } catch (...) {
        //cout << "Nenašli sme osobu pre zistenie jej platu" << endl;
        return false;
    }

    // Kontrola pridávania duplikovaného mena a priezviska
    auto objektMena = lower_bound(osobyPodlaMena.begin(), osobyPodlaMena.end(), novaOsoba, Osoba::porovnavacMena());
    unsigned int indexMena = distance(osobyPodlaMena.begin(), objektMena);

    try {
        if (osobyPodlaMena.at(indexMena).meno == novaOsoba.meno && osobyPodlaMena.at(indexMena).priezvisko == novaOsoba.priezvisko) {
            //cout << "Pridávaná osoba obsahuje duplikované meno a priezvisko" << endl;
            return false;
        }
    } catch(...) {
        //cout << "Nenašli sme osobu s daným novým menom a priezviskom => nevkladáme duplikát" << endl;
    }

    // Vymaž osobu s daným mejlom
    if (!Del(email)) {
        return false;
    }

    // Pridaj osobu s novým menom a priezviskom
    if (!Add(newName, newSurname, email, plat)) {
        return false;
    }

    return true;
}

bool CPersonalAgenda::ChangeEmail(const string &name, const string &surname, const string &newEmail) {
    // Musíme zistiť plat danej osoby,
    // aby sme pri pridávaní osoby so zmeneným menom/priezviskom vedeli plat zmazanej osoby
    Osoba novaOsoba(name, surname, newEmail, 0);

    auto objektMena = lower_bound(osobyPodlaMena.begin(), osobyPodlaMena.end(), novaOsoba, Osoba::porovnavacMena());
    unsigned int indexMeno = distance(osobyPodlaMena.begin(), objektMena);

    unsigned int plat = 0;

    // Zistenie platu danej osoby
    try {
        if (osobyPodlaMena.at(indexMeno).meno == name && osobyPodlaMena.at(indexMeno).priezvisko == surname) {
            plat = osobyPodlaMena.at(indexMeno).plat;
        } else {
            //cout << "Nenašli sme osobu pre zistenie jej platu" << endl;
            return false;
        }
    } catch(...) {
        //cout << "Nenašli sme osobu pre zistenie jej platu" << endl;
        return false;
    }

    // Kontrola pridávania duplikovaného emajlu
    auto objektMejlu = lower_bound(osobyPodlaEmailu.begin(), osobyPodlaEmailu.end(), novaOsoba, Osoba::porovnavacEmailu());
    unsigned int indexMejl = distance(osobyPodlaEmailu.begin(), objektMejlu);

    try {
        if (osobyPodlaEmailu.at(indexMejl).email == newEmail) {
            //cout << "Pridávaná osoba obsahuje duplikovaný email" << endl;
            return false;
        }
    } catch (...) {
        //cout << "Osoba na pridanie neobosahuje emailový duplikát" << endl;
    }


    if (!Del(name, surname)) {
        return false;
    }

    if (!Add(name, surname, newEmail, plat)) {
        return false;
    }

    return true;
}

bool CPersonalAgenda::SetSalary(const string &email, unsigned int salary) {
    Osoba novaOsoba("", "", email, salary);

    auto objektEmailu = lower_bound(osobyPodlaEmailu.begin(), osobyPodlaEmailu.end(), novaOsoba, Osoba::porovnavacEmailu());
    unsigned int indexEmail = distance(osobyPodlaEmailu.begin(), objektEmailu);

    unsigned int doterajsiPlat = 0;

    // Zistenie platu danej osoby
    try {
        if (osobyPodlaEmailu.at(indexEmail).email == novaOsoba.email) {
            doterajsiPlat = osobyPodlaEmailu.at(indexEmail).plat;

            novaOsoba.meno = osobyPodlaEmailu.at(indexEmail).meno;
            novaOsoba.priezvisko = osobyPodlaEmailu.at(indexEmail).priezvisko;

            osobyPodlaEmailu.at(indexEmail).plat = salary;

            // Treba zmenit plat aj pri zazname s menom
            auto objektMeno = lower_bound(osobyPodlaMena.begin(), osobyPodlaMena.end(), novaOsoba, Osoba::porovnavacMena());
            unsigned int indexMeno = distance(osobyPodlaMena.begin(), objektMeno);

            if (osobyPodlaMena.at(indexMeno).meno == novaOsoba.meno && osobyPodlaMena.at(indexMeno).priezvisko == novaOsoba.priezvisko) {
                osobyPodlaMena.at(indexMeno).plat = salary;
            }

            // Vymaž starý plat
            auto objektStaryPlat = lower_bound(platy.begin(), platy.end(), doterajsiPlat);
            unsigned int indexStaryPlat = distance(platy.begin(), objektStaryPlat);

            if (platy.at(indexStaryPlat) == doterajsiPlat) {
                platy.erase(platy.begin() + indexStaryPlat);
            }

            // Pridaj nový plat
            auto objektNovyPlat = lower_bound(platy.begin(), platy.end(), salary);
            unsigned int indexNovyPlat = distance(platy.begin(), objektNovyPlat);

            platy.insert(platy.begin() + indexNovyPlat, salary);

            return true;
        } else {
            // "Nenašli sme osobu pre zistenie jej platu" << endl;
            return false;
        }
    } catch (...) {
        //cout << "Nenašli sme osobu pre zistenie jej platu" << endl;
        return false;
    }
}

bool CPersonalAgenda::SetSalary(const string &name, const string &surname, unsigned int salary) {
    Osoba novaOsoba(name, surname, "", salary);

    auto objektMena = lower_bound(osobyPodlaMena.begin(), osobyPodlaMena.end(), novaOsoba, Osoba::porovnavacMena());
    unsigned int indexMeno = distance(osobyPodlaMena.begin(), objektMena);

    unsigned int doterajsiPlat = 0;

    try {
        if (osobyPodlaMena.at(indexMeno).meno == novaOsoba.meno && osobyPodlaMena.at(indexMeno).priezvisko == novaOsoba.priezvisko) {
            doterajsiPlat = osobyPodlaMena.at(indexMeno).plat;
            novaOsoba.email = osobyPodlaMena.at(indexMeno).email;

            osobyPodlaMena.at(indexMeno).plat = salary;

            // Treba zmenit salary aj u emailu
            auto objektEmail = lower_bound(osobyPodlaEmailu.begin(), osobyPodlaEmailu.end(), novaOsoba, Osoba::porovnavacEmailu());
            unsigned int indexEmail = distance(osobyPodlaEmailu.begin(), objektEmail);

            if (osobyPodlaEmailu.at(indexEmail).email == novaOsoba.email) {
                osobyPodlaEmailu.at(indexEmail).plat = salary;
            }

            auto objektStaryPlat = lower_bound(platy.begin(), platy.end(), doterajsiPlat);
            unsigned int indexStaryPlat = distance(platy.begin(), objektStaryPlat);

            if (platy.at(indexStaryPlat) == doterajsiPlat) {
                platy.erase(platy.begin() + indexStaryPlat);
            }

            auto objektNovyPlat = lower_bound(platy.begin(), platy.end(), salary);
            unsigned int indexNovyPlat = distance(platy.begin(), objektNovyPlat);

            platy.insert(platy.begin() + indexNovyPlat, salary);

            return true;
        } else {
            //cout << "Nenašli sme osobu pre zistenie jej platu" << endl;
            return false;
        }
    } catch (...) {
        //cout << "Nenašli sme osobu pre zistenie jej platu" << endl;
        return false;
    }
}

unsigned int CPersonalAgenda::GetSalary(const string &email) const {
    Osoba novaOsoba("", "", email, 0);

    auto objektEmailu = lower_bound(osobyPodlaEmailu.begin(), osobyPodlaEmailu.end(), novaOsoba, Osoba::porovnavacEmailu());
    unsigned int indexEmail = distance(osobyPodlaEmailu.begin(), objektEmailu);

    try {
        if (osobyPodlaEmailu.at(indexEmail).email == novaOsoba.email) {
            return osobyPodlaEmailu.at(indexEmail).plat;
        } else {
            //cout << "Nenašli sme osobu pre zistenie jej platu" << endl;
            return 0;
        }
    } catch (...) {
        //cout << "Nenašli sme osobu pre zistenie jej platu" << endl;
        return 0;
    }
}

unsigned int CPersonalAgenda::GetSalary(const string &name, const string &surname) const {
    Osoba novaOsoba(name, surname, "", 0);

    auto objektMena = lower_bound(osobyPodlaMena.begin(), osobyPodlaMena.end(), novaOsoba, Osoba::porovnavacMena());
    unsigned int indexMena = distance(osobyPodlaMena.begin(), objektMena);

    try {
        if (osobyPodlaMena.at(indexMena).meno == name && osobyPodlaMena.at(indexMena).priezvisko == surname) {
            return osobyPodlaMena.at(indexMena).plat;
        } else {
            //cout << "Nenašli sme osobu pre zistenie jej platu" << endl;
            return 0;
        }
    } catch (...) {
        //cout << "Nenašli sme osobu pre zistenie jej platu" << endl;
        return 0;
    }
}

bool CPersonalAgenda::GetFirst(string &outName, string &outSurname) const {
    if (osobyPodlaMena.size() == 0) {
        return false;
    }

    outName = osobyPodlaMena.at(0).meno;
    outSurname = osobyPodlaMena.at(0).priezvisko;

    return true;
}

bool CPersonalAgenda::GetNext(const string &name, const string &surname, string &outName, string &outSurname) const {
    Osoba novaOsoba(name, surname, "", 0);

    auto objektMena = lower_bound(osobyPodlaMena.begin(), osobyPodlaMena.end(), novaOsoba, Osoba::porovnavacMena());
    unsigned int indexMena = distance(osobyPodlaMena.begin(), objektMena);

    if (osobyPodlaMena.at(indexMena).meno == name && osobyPodlaMena.at(indexMena).priezvisko == surname) {
        try {
            outName = osobyPodlaMena.at(indexMena + 1).meno;
            outSurname = osobyPodlaMena.at(indexMena + 1).priezvisko;
            return true;
        } catch(...) {
            return false;
        }
    }

    return false;
}

bool CPersonalAgenda::GetRank(const string &email, int &rankMin, int &rankMax) const {
    Osoba novaOsoba("", "", email, 0);

    auto objektEmail = lower_bound(osobyPodlaEmailu.begin(), osobyPodlaEmailu.end(), novaOsoba, Osoba::porovnavacEmailu());
    unsigned int indexEmail = distance(osobyPodlaEmailu.begin(), objektEmail);

    try {
        if (osobyPodlaEmailu.at(indexEmail).email == email) {
            unsigned int platOsoby = osobyPodlaEmailu.at(indexEmail).plat;

            auto lowrank = lower_bound(platy.begin(), platy.end(), platOsoby);
            unsigned int pocetNizsichPlatov = distance(platy.begin(), lowrank);

            auto highrank = upper_bound(platy.begin(), platy.end(), platOsoby);
            unsigned int pocetRovnakychPlatov = distance(platy.begin(), highrank);

            //cout << "rankmin: " << pocetNizsichPlatov << " rankmax: " << pocetRovnakychPlatov << endl;

            rankMin = pocetNizsichPlatov;
            rankMax = pocetRovnakychPlatov - 1;

            return true;
        } else {
            //cout << "Hladany zamestnanec nebol najdeny" << endl;
            return false;
        }
    } catch (...) {
        //cout << "Hladany zamestnanec nebol najdeny" << endl;
        return false;
    }
}

bool CPersonalAgenda::GetRank(const string &name, const string &surname, int &rankMin, int &rankMax) const {
    Osoba novaOsoba(name, surname, "", 0);

    auto objektMeno = lower_bound(osobyPodlaMena.begin(), osobyPodlaMena.end(), novaOsoba, Osoba::porovnavacMena());
    unsigned int indexMeno = distance(osobyPodlaMena.begin(), objektMeno);

    try {
        if (osobyPodlaMena.at(indexMeno).meno == novaOsoba.meno && osobyPodlaMena.at(indexMeno).priezvisko == novaOsoba.priezvisko) {
            unsigned int platOsoby = osobyPodlaMena.at(indexMeno).plat;

            auto lowrank = lower_bound(platy.begin(), platy.end(), platOsoby);
            unsigned int pocetNizsichPlatov = distance(platy.begin(), lowrank);

            auto highrank = upper_bound(platy.begin(), platy.end(), platOsoby);
            unsigned int pocetRovnakychPlatov = distance(platy.begin(), highrank);

            //cout << "rankmin: " << pocetNizsichPlatov << " rankmax: " << pocetRovnakychPlatov << endl;

            rankMin = pocetNizsichPlatov;
            rankMax = pocetRovnakychPlatov - 1;

            return true;
        } else {
            //cout << "Hladany zamestnanec nebol najdeny" << endl;
            return false;
        }
    } catch (...) {
        //cout << "Hladany zamestnanec nebol najdeny" << endl;
        return false;
    }
}

#ifndef __PROGTEST__
int main ( void )
{

}
#endif /* __PROGTEST__ */