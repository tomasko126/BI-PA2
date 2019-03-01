class CWindow {
public:
    CWindow(const string & title, const CRect &absPos, const string & classType = "Window") : absPositions(absPos), origPositions(absPos), title(title), classType(classType) {}
    CWindow(const CWindow & other) {
        this->title = other.title;
        this->absPositions = other.absPositions;
        this->origPositions = other.origPositions;
        this->classType = other.classType;

        for (unsigned int i = 0; i<other.zoznamPrvkov.size(); i++) {
            shared_ptr<CWindow> kopia = other.zoznamPrvkov[i].get()->makeDuplicate();
            this->zoznamPrvkov.push_back(kopia);
        }
    }

    // Add method
    CWindow & Add(const CWindow & prvok) {
        shared_ptr<CWindow> edited = prvok.makeDuplicate();
        edited->recalculate(origPositions.m_X, origPositions.m_Y, origPositions.m_W, origPositions.m_H);
        zoznamPrvkov.push_back(edited);

        return *this;
    }

    // Search
    shared_ptr<CWindow> Search(const int & id) const {
        for (auto & prvok : zoznamPrvkov) {
            if (prvok->GetID() == id) {
                return prvok;
            }
        }

        return NULL;
    }

    // SetPosition
    void SetPosition(const CRect & newAbsPos) {
        this->absPositions = newAbsPos;
        this->origPositions = newAbsPos;

        for (auto & prvok: zoznamPrvkov) {
            prvok->recalculate(absPositions.m_X, absPositions.m_Y, absPositions.m_W, absPositions.m_H);
        }
    }


    // GetID
    virtual int GetID() const {
        return 0;
    };

    virtual unsigned int GetSelected() const {
        return 0;
    };

    // GetValue
    string GetValue() const {
        return title;
    }

    // SetValue
    void SetValue(const string & newValue) {
        this->title = newValue;
    }

    virtual shared_ptr<CWindow> makeDuplicate() const {
        return shared_ptr<CWindow>( new CWindow(*this));
    };

    string getClassType() const {
        return classType;
    }

    virtual ostream& Print (ostream& os) const {
        os << "Window " << "\"" << title << "\"" << " (" << absPositions.m_X << "," << absPositions.m_Y << "," << absPositions.m_W << "," << absPositions.m_H<< ")" << endl;
        bool shouldOutputDelimeter = true;
        for (unsigned int i = 0; i < zoznamPrvkov.size(); i++) {
            if (i == zoznamPrvkov.size() - 1) {
                shouldOutputDelimeter = false;
            }
            os << "+- [" << zoznamPrvkov[i].get()->GetID() << "] " << zoznamPrvkov[i].get()->getClassType() << (zoznamPrvkov[i].get()->GetValue() != "" ? (" \"" + zoznamPrvkov[i].get()->GetValue()) + "\"" : "") << " (" << zoznamPrvkov[i].get()->getPosition().m_X << "," << zoznamPrvkov[i].get()->getPosition().m_Y << "," << zoznamPrvkov[i].get()->getPosition().m_W << "," << zoznamPrvkov[i].get()->getPosition().m_H << ")" << endl;
            for (unsigned int j = 0; j<zoznamPrvkov[i].get()->getZoznamMoznosti().size(); j++) {

                if (j == zoznamPrvkov[i].get()->GetSelected()) {
                    if (shouldOutputDelimeter) {
                        os << "|  +->" << zoznamPrvkov[i].get()->getZoznamMoznosti()[j] << "<" << endl;
                    } else {
                        os << "   +->" << zoznamPrvkov[i].get()->getZoznamMoznosti()[j] << "<" << endl;
                    }
                } else {
                    if (shouldOutputDelimeter) {
                        os << "|  +- " << zoznamPrvkov[i].get()->getZoznamMoznosti()[j] << endl;
                    } else {
                        os << "   +- " << zoznamPrvkov[i].get()->getZoznamMoznosti()[j] << endl;
                    }
                }
            }

        }

        return os;
    }

    friend ostream& operator << (ostream& os, const CWindow & okno) {
        return okno.Print(os);
    }

    virtual vector<string> getZoznamMoznosti() const {
        vector<string> empty;
        return empty;
    }

    // Dojdu mi velkosti windowu
    void recalculate(double & x, double & y, double & w, double & h) {
        absPositions.m_W = origPositions.m_W * w;
        absPositions.m_H = origPositions.m_H * h;
        absPositions.m_X = (origPositions.m_X * w) + x;
        absPositions.m_Y = (origPositions.m_Y * h) + y;
    }

    CRect getPosition() const {
        return absPositions;
    }

protected:
    CRect absPositions = CRect(0, 0, 0, 0);
    CRect origPositions = CRect(0, 0, 0, 0);
    string title;
    string classType;

private:
    vector<shared_ptr<CWindow>> zoznamPrvkov;
};

class CButton : public CWindow {
public:
    CButton(const int id, const CRect &relPos, const string &name) : CWindow(name, relPos, "Button"), id(id) {};

    virtual shared_ptr<CWindow> makeDuplicate() const override {
        return shared_ptr<CWindow>( new CButton(*this));
    }

    virtual int GetID() const override {
        return id;
    }

    ostream& Print (ostream& os) const override {
        os << "[" << id << "] " << "Button " << "\"" << this->GetValue() << "\" " << "(" << absPositions.m_X << "," << absPositions.m_Y << "," << absPositions.m_W << "," << absPositions.m_H<< ")" << endl;
        return os;
    }
private:
    int id = 0;
};

class CInput : public CWindow {
public:
    CInput(const int id, const CRect &relPos, const string &value) : CWindow(value, relPos, "Input"), id(id) {};

    virtual shared_ptr<CWindow> makeDuplicate() const override {
        return shared_ptr<CWindow>( new CInput(*this));
    }

    virtual int GetID() const override {
        return id;
    }

    ostream& Print (ostream& os) const override {
        os << "[" << id << "] " << "Input " << "\"" << this->GetValue() << "\" " << "(" << absPositions.m_X << "," << absPositions.m_Y << "," << absPositions.m_W << "," << absPositions.m_H<< ")" << endl;
        return os;
    }

private:
    int id = 0;
};

class CLabel : public CWindow {
public:
    CLabel(const int id, const CRect &relPos, const string &label) : CWindow(label, relPos, "Label"), id(id) {};

    virtual shared_ptr<CWindow> makeDuplicate() const override {
        return shared_ptr<CWindow>( new CLabel(*this));
    }

    virtual int GetID() const override {
        return id;
    }

    ostream& Print (ostream& os) const override {
        os << "[" << id << "] " << "Label " << "\"" << this->GetValue() << "\" " << "(" << absPositions.m_X << "," << absPositions.m_Y << "," << absPositions.m_W << "," << absPositions.m_H<< ")" << endl;
        return os;
    }

private:
    int id = 0;
};

class CComboBox : public CWindow {
public:
    CComboBox(const int id, const CRect &relPos) : CWindow("", relPos, "ComboBox"), id(id) {};

    // Add
    CComboBox & Add(const string & moznost) {
        zoznamMoznosti.push_back(moznost);

        return *this;
    }

    virtual int GetID() const override {
        return id;
    }

    // SetSelected
    void SetSelected(const int & number) {
        this->selected = number;
    }

    // GetSelected
    virtual unsigned int GetSelected() const override {
        return this->selected;
    }

    virtual shared_ptr<CWindow> makeDuplicate() const override {
        return shared_ptr<CWindow>( new CComboBox(*this));
    }

    virtual vector<string> getZoznamMoznosti() const override {
        return zoznamMoznosti;
    }

    ostream& Print (ostream& os) const override {
        os << "[" << id << "] " << "ComboBox " << "(" << absPositions.m_X << "," << absPositions.m_Y << "," << absPositions.m_W << "," << absPositions.m_H<< ")" << endl;
        for (unsigned int i = 0; i<zoznamMoznosti.size(); i++) {
            if (i == selected) {
                os << "+->" << zoznamMoznosti[i] << "<" << endl;
            } else {
                os << "+- " << zoznamMoznosti[i] << endl;
            }
        }
        return os;
    }

    vector<string> zoznamMoznosti;
private:
    unsigned int selected = 0;
    int id = 0;
};
