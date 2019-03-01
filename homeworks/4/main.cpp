// Vlastný vektor
template<class T>
class Vektoris {
public:
    Vektoris() {
        alokovanaVelkost += alokovanaVelkost + 20;
        data = new T[alokovanaVelkost];
    }

    Vektoris(const Vektoris<T> &other) {
        copy(other);
    }

    ~Vektoris() {
        delete [] data;
    }

    T & operator = (const T & other) {
        if (this == &other) {
            return *this;
        }

        delete [] data;

        copy(other);

        return *this;
    }

    T & operator [] (unsigned int idx) {
        // TODO: Check mimo pola
        return data[idx];
    }

    T operator [] (unsigned int idx) const {
        // TODO: Check mimo pola
        return data[idx];
    }

    unsigned int size() const {
        return velkostDat;
    }

    void push_back(const T &objekt) {

        if (velkostDat >= alokovanaVelkost) {

            // Zvýš počet prvkov v poli o 20
            alokovanaVelkost += alokovanaVelkost + 20;

            T * novePole = new T[alokovanaVelkost];

            // Prekopíruj staré dáta do nového pola
            for (unsigned int i = 0; i < velkostDat; i++) {
                novePole[i] = data[i];
            }

            // Uvolni pamäť po starom poli
            delete [] data;

            // Dáta budú teraz v novom poli
            data = novePole;
        }

        data[velkostDat] = objekt;
        velkostDat += 1;
    }

    void insert(const T & objekt, unsigned int index) {

        if (velkostDat < alokovanaVelkost) {
            for (unsigned int i = velkostDat; i > index; --i) {
                data[i] = data[i - 1];
                data[i - 1].clear();
            }

            if (data[index].getName() && strcmp(data[index].getName(), objekt.getName()) != 0) {
                data[index].clear();
            }

            data[index] = objekt;

        } else {
            alokovanaVelkost *= 2;

            T * novePole = new T[alokovanaVelkost];

            for (unsigned int i = 0; i < index; i++) {
                novePole[i] = data[i];
            }

            unsigned int indexToAdd = index;

            for (; index < velkostDat; index++) {
                novePole[index + 1] = data[index];
            }

            delete[] data;

            data = novePole;

            novePole[indexToAdd] = objekt;
        }
        velkostDat += 1;
    }

    void clear() {
        delete[] data;
        alokovanaVelkost = 20;
        velkostDat = 0;

        data = new T[alokovanaVelkost];
    }

    T * data;

private:
    unsigned int alokovanaVelkost = 0, velkostDat = 0;

    void copy(const Vektoris<T> &other) {
        data = new T[other.size()];
        velkostDat = other.velkostDat;

        for (unsigned int i = 0; i < velkostDat; ++i) {
            data[i] = other.data[i];
        }
    }
};


// MAIL

class CMail {
public:
    CMail() = default;

    CMail(const char *from, const char *to, const char *body) {

        // Zisti velkost stringov
        size_t velkost_from = strlen(from) + 1,
                velkost_to = strlen(to) + 1,
                velkost_body = strlen(body) + 1;

        // Alokuj pamäť
        this->from = new char[velkost_from];
        this->to = new char[velkost_to];
        this->body = new char[velkost_body];

        // Ulož stringy
        strcpy(this->from, from);
        strcpy(this->to, to);
        strcpy(this->body, body);

        allocd = true;
    }

    /*
    CMail(const CMail &novyMail) {
        copy(novyMail);
    }
     */

    char *getFrom() const {
        return this->from;
    }

    char *getTo() const {
        return this->to;
    }

    char *getBody() const {
        return this->body;
    }

    ~CMail() {
        clear();
    }


    CMail &operator=(const CMail &other) {
        if (this == &other) return *this;

        clear();

        copy(other);

        return *this;
    }


    bool operator==(const CMail &x) const {
        return strcmp(this->from, x.from) == 0 &&
               strcmp(this->to, x.to) == 0 &&
               strcmp(this->body, x.body) == 0;

    }

    void clear() {
        if (allocd) {
            delete[] from;
            delete[] to;
            delete[] body;
            from = nullptr;
            to = nullptr;
            body = nullptr;
            allocd = false;
        }
    }

private:
    char *from = nullptr;
    char *to = nullptr;
    char *body = nullptr;
    bool allocd = false;

    void copy(const CMail &other) {
        size_t velkost_from = strlen(other.getFrom()) + 1,
                velkost_to = strlen(other.getTo()) + 1,
                velkost_body = strlen(other.getBody()) + 1;

        // Alokuj pamäť
        this->from = new char[velkost_from];
        this->to = new char[velkost_to];
        this->body = new char[velkost_body];

        // Ulož stringy
        strcpy(this->from, other.getFrom());
        strcpy(this->to, other.getTo());
        strcpy(this->body, other.getBody());

        allocd = true;
    }
};

struct Node {
    char * from;
    char * to;
    char * body;
    Node * next;
};

class List {
public:

    Node * head;
    Node * poslednyPridany;

    List() {
        head = NULL;
    }

    ~List() {
        while(head != NULL) {
            Node * n = head->next;
            delete [] head->from;
            delete [] head->to;
            delete [] head->body;
            delete head;
            head = n;
        }
    }

    void add(char * from, char * to, char * body) {
        Node * last = new Node;

        size_t velkost_from = strlen(from) + 1,
                velkost_to = strlen(to) + 1,
                velkost_body = strlen(body) + 1;

        // Alokuj pamäť
        last->from = new char[velkost_from];
        last->to = new char[velkost_to];
        last->body = new char[velkost_body];

        // Ulož stringy
        strcpy(last->from, from);
        strcpy(last->to, to);
        strcpy(last->body, body);

        last->next = NULL;

        // Ak je list prazdny, nastav head na last
        if (head == NULL) {
            head = last;
            poslednyPridany = head;
        } else {

            poslednyPridany->next = last;
            poslednyPridany = last;
        }
    }

    void clear() {
        Node * tmp;

        while (head != NULL) {
            tmp = head;
            head = head->next;
            delete [] tmp->from;
            delete [] tmp->to;
            delete [] tmp->body;
            delete tmp;
        }
    }
};

class Osoba {
public:
    Osoba() {
        meno = new char[2];
        strcpy(meno, "");
        allocd = true;
    };

    Osoba(const Osoba &novaOsoba) {
        copy(novaOsoba);
    }


    Osoba(const char *meno) {
        size_t velkost_mena = strlen(meno) + 1;

        this->meno = new char[velkost_mena];

        strcpy(this->meno, meno);

        allocd = true;
    }

    ~Osoba() {
        if (allocd) {
            delete[] meno;
            allocd = false;
        }
    }


    Osoba & operator = (const Osoba &other) {
        if (this == &other) {
            return *this;
        }

        delete [] meno;

        copy(other);
        return *this;
    }

    char *getName() const {
        return meno;
    }

    void push_email(char * from, char * to, char * body, const bool & inbox) {
        if (inbox) {
            in.add(from, to, body);
        } else {
            out.add(from, to, body);
        }
    }

    void clear() {
        if (allocd) {
            delete[] meno;
            meno = nullptr;

            in.clear();
            out.clear();
        }
    }

    List in;
    List out;

private:
    bool allocd = false;
    char *meno = nullptr;

    void copy(const Osoba &other) {
        size_t velkost_name = strlen(other.getName()) + 1;

        // Alokuj pamäť
        this->meno = new char[velkost_name];

        // Ulož stringy
        strcpy(this->meno, other.getName());

        Node * head = other.in.head;

        while (head) {
            push_email(head->from, head->to, head->body, true);
            head = head->next;
        }

        head = other.out.head;

        while (head) {
            push_email(head->from, head->to, head->body, false);
            head = head->next;
        }

        allocd = true;
    }

};

class CMailIterator {
public:
    CMailIterator() = default;

    void add(char * & from, char * & to, char * & body) {
        zoznam.add(from, to, body);
        if (pocetPrvkov == 0) {
            email = CMail(from, to, body);
            node = zoznam.head;
        }
        pocetPrvkov++;
    }

    operator bool(void) const {
        if (pozicia <= pocetPrvkov) {
            return true;
        }
        return false;
    }

    bool operator!(void) const {
        if (pozicia <= pocetPrvkov) {
            return false;
        }
        return true;
    }

    const CMail &operator*(void) const {
        return email;
    }

    CMailIterator &operator++(void) {
        node = node->next;
        pozicia++;

        if (node != NULL) {
            email = CMail(node->from, node->to, node->body);
        }

        return *this;
    }

private:
    List zoznam;
    Node * node;
    CMail email;
    unsigned int pozicia = 1;
    unsigned int pocetPrvkov = 0;
};

class CMailServer {
public:
    CMailServer(void) = default;

    CMailServer(const CMailServer &src) {
        copy(src);
    };

    CMailServer &operator=(const CMailServer &src) {
        if (this == &src) {
            return *this;
        }

        zoznamOsob.clear();

        copy(src);
        return *this;
    };

    ~CMailServer(void) = default;

    void SendMail(const CMail &m) {
        const char *from = m.getFrom();

        unsigned int index = lower_bound(from);

        if ((index <= zoznamOsob.size() - 1) && strcmp(zoznamOsob[index].getName(), from) == 0) {
            zoznamOsob[index].push_email(m.getFrom(), m.getTo(), m.getBody(), false);
        } else {
            Osoba novaOsoba(from);
            novaOsoba.push_email(m.getFrom(), m.getTo(), m.getBody(), false);

            zoznamOsob.insert(novaOsoba, index);
        }

        const char *to = m.getTo();

        index = lower_bound(to);

        if ((index <= zoznamOsob.size() - 1) && strcmp(zoznamOsob[index].getName(), to) == 0) {
            zoznamOsob[index].push_email(m.getFrom(), m.getTo(), m.getBody(), true);
        } else {
            Osoba novaOsoba(to);
            novaOsoba.push_email(m.getFrom(), m.getTo(), m.getBody(), true);

            zoznamOsob.insert(novaOsoba, index);
        }
    }

    CMailIterator Outbox(const char *email) const {
        unsigned int index = lower_bound(email);

        CMailIterator it;

        Node * head = zoznamOsob.data[index].out.head;

        while (head) {
            it.add(head->from, head->to, head->body);
            head = head->next;
        }

        return it;

    };

    CMailIterator Inbox(const char * email) const {
        unsigned int index = lower_bound(email);

        CMailIterator it;

        Node * head = zoznamOsob.data[index].in.head;

        while (head) {
            it.add(head->from, head->to, head->body);
            head = head->next;
        }

        return it;
    }


    unsigned int lower_bound(const char * & val) const {
        unsigned int count = zoznamOsob.size();
        unsigned int step = 0;
        unsigned int first = 0;
        unsigned int it = 0;

        while (count > 0) {
            it = first;
            step = count / 2;
            it += step;
            if (strcmp(zoznamOsob[it].getName(), val) < 0) {
                first = ++it;
                count -= step + 1;
            } else
                count = step;
        }
        return first;
    }

private:
    Vektoris<Osoba> zoznamOsob;

    void copy(const CMailServer &src) {
        for (unsigned int i = 0; i < src.zoznamOsob.size(); i++) {
            Osoba novaOsoba(src.zoznamOsob[i].getName());

            Node * head = src.zoznamOsob.data[i].out.head;

            while (head) {
                novaOsoba.push_email(head->from, head->to, head->body, false);
                head = head->next;
            }

            head = src.zoznamOsob.data[i].in.head;

            while (head) {
                novaOsoba.push_email(head->from, head->to, head->body, true);
                head = head->next;
            }

            zoznamOsob.push_back(novaOsoba);
        }
    }
};
