
typedef bool(*komparator)(int);


template<typename _T, typename _E>
class CAccess {
public:
    CAccess(void) = default;
    ~CAccess(void) = default;

    CAccess & Add(const _E & details, const _T & from, const _T & to) {
        graf[from].push_back(make_pair(to, details));
        graf[to].push_back(make_pair(from, details));

        return *this;
    }

    map<_T, int> Find(const _T & city) const {
        map <_T, int> mapa = BFS(city, -1);

        return mapa;
    };

    map<_T, int> Find(const _T & city, const int & pocetPrestupov) const {
        map <_T, int> mapa = BFS(city, pocetPrestupov);

        return mapa;
    };

    template<typename funkcia = komparator>
    map<_T, int> Find(const _T & city, const int & pocetPrestupov, funkcia cmp) const {
        map <_T, int> mapa;
        set <_T> visited;

        list<pair<_T, unsigned int>> queue;
        int vzdialenost = 0;

        // Prvé mesto dáme do visited + pušbek do zoznamu
        _T p = city;

        // Nachádza sa mesto v zozname?
        if (graf.find(p) == graf.end()) {
            ostringstream oss;
            oss << "unknown " << city;
            throw invalid_argument(oss.str());
        }

        // BFS
        visited.insert(p);
        queue.push_back({p, vzdialenost});
        mapa.insert(make_pair(p, vzdialenost));

        while (!queue.empty()) {
            // Dočasne si ulož názov mesta a vzdialenosť
            p = queue.front().first;
            vzdialenost = queue.front().second;

            // Skontroluj vzdialenost
            if (pocetPrestupov == vzdialenost) {
                break;
            }

            //cout << "Z mesta: " << p << endl;
            queue.pop_front();

            for (unsigned int i=0; i<graf.at(p).size(); i++) {

                const _T mesto = graf.at(p).at(i).first;

                    if (!cmp(graf.at(p).at(i).second)) {
                        continue;
                    }

                if (visited.find(mesto) == visited.end()) {
                    //cout << "Do mesta: " << mesto << " , vzdialenost: " << vzdialenost+1 << endl;
                    visited.insert(mesto);
                    queue.push_back(make_pair(mesto, vzdialenost+1));
                    mapa.insert(make_pair(mesto, vzdialenost+1));
                }
            }
        }

        return mapa;
    }

private:
    map <_T, vector<pair<_T, _E>>> graf;

    map <_T, int> BFS(const _T & s, const int & pocetPrestupov) const {
        map <_T, int> mapa;
        set <_T> visited;
        list<pair<_T, unsigned int>> queue;

        // Prvé mesto dáme do visited + pušbek do zoznamu
        _T p = s;

        int vzdialenost = 0;

        if (graf.find(p) == graf.end()) {
            ostringstream oss;
            oss << "unknown " << s;
            throw invalid_argument(oss.str());
        }

        visited.insert(p);
        queue.push_back({p, vzdialenost});
        mapa.insert(make_pair(p, vzdialenost));

        while (!queue.empty()) {
            // Dočasne si ulož názov mesta a vzdialenosť
            p = queue.front().first;
            vzdialenost = queue.front().second;

            if (pocetPrestupov != -1 && pocetPrestupov == vzdialenost) {
                break;
            }

            //cout << "Z mesta: " << p << endl;
            queue.pop_front();

            for (unsigned int i=0; i<graf.at(p).size(); i++) {

                _T mesto = graf.at(p).at(i).first;

                if (visited.find(mesto) == visited.end()) {
                    //cout << "Do mesta: " << mesto << " , vzdialenost: " << vzdialenost+1 << endl;
                    visited.insert(mesto);
                    queue.push_back(make_pair(mesto, vzdialenost+1));
                    mapa.insert(make_pair(mesto, vzdialenost+1));
                }
            }
        }

        return mapa;
    }

};
