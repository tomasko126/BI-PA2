#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cstring>
#include <cassert>
#include <cmath>
#include <cctype>

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <list>

using namespace std;

const uint16_t ENDIAN_LITTLE = 0x4949;
const uint16_t ENDIAN_BIG = 0x4d4d;

// Skontroluj interláciu
bool checkInterlace(int &zadaneCislo) {
    switch (zadaneCislo) {
        case 1:
        case 2:
        case 4:
        case 8:
        case 16:
        case 32:
        case 64:
            return true;
        default:
            return false;
    }
}

// PIXEL CLASS
class Pixel {
public:
    Pixel() = default;

    void addChannel(uint16_t & kanal);

    bool obsadene = false;
    bool transformovane = false;

    uint16_t kanaly[4];
    int kanalyLength = 0;
};

void Pixel::addChannel(uint16_t & kanal) {
    kanaly[kanalyLength] = kanal;
    kanalyLength++;
}

// IMAGE CLASS
class Image {
public:
    Image(const char *srcFileName, const char *dstFileName, int &interlace, uint16_t &byteOrder);

    ~Image();

    bool spracujHlavicku();

    bool nacitajObrazok(bool sameInterlace);

    bool processImage();

    bool rotujObrazok();

    bool ulozHlavicku();

private:
    ifstream inputFile;
    ofstream outputFile;
    uint16_t poradieBajtov;
    uint16_t sirka;
    uint16_t vyska;
    uint16_t format;
    int pocetPixelov;
    int pocetKanalov;
    int pocetBitovNaKanal;
    int prekladanie;
    int desiredInterlace;
    uint16_t desiredByteOrder;
    Pixel ** obrazok;
};

// Konštruktor
Image::Image(const char *srcFileName, const char *dstFileName, int &interlace, uint16_t &byteOrder) {
    // Otvor zdrojovy obrazok ako binarny subor
    inputFile.open(srcFileName, ios::binary | ios::in);
    outputFile.open(dstFileName, ios::binary | ios::out);

    // Ulož hodnoty, s ktorými budeme neskôr pracovať
    desiredInterlace = interlace;
    desiredByteOrder = byteOrder;
}

// Deštruktor
Image::~Image() {
    // Zatvor súbory, nakoľko s nimi už nebudeme pracovať
    inputFile.close();
    outputFile.close();
}

// Spracovanie hlavičky
bool Image::spracujHlavicku() {
    // Zisti poradie bajtov
    inputFile.read((char *) &poradieBajtov, 2);

    if (inputFile.fail()) {
        return false;
    }

    // Byteorder check
    if (poradieBajtov != ENDIAN_LITTLE && poradieBajtov != ENDIAN_BIG) {
        return false;
    }

    // Načítaj šírku a výšku obrázku
    inputFile.read((char *) &sirka, 2);

    if (inputFile.fail()) {
        return false;
    }

    inputFile.read((char *) &vyska, 2);

    if (inputFile.fail()) {
        return false;
    }

    // Kontrola šírky a výšky, ani jedno nemôže byť 0
    if (vyska == 0 || sirka == 0) {
        return false;
    }

    // Vypočítaj počet pixelov v obrázku
    pocetPixelov = vyska * sirka;

    // Načítaj formát obrázku
    inputFile.read((char *) &format, 2);

    if (inputFile.fail()) {
        return false;
    }

    // Zisti počet kanálov
    pocetKanalov = format & 0x3;
    ++pocetKanalov;

    if (pocetKanalov == 2) {
        return false;
    }

    // Uprav formát - zahoď údaje o počte kanálov
    format = format >> 2;

    // Zisti počet bitov na kanál
    pocetBitovNaKanal = format & 0x7;
    switch (pocetBitovNaKanal) {
        case 0:
            pocetBitovNaKanal = 1;
            break;
        case 3:
            pocetBitovNaKanal = 8;
            break;
        case 4:
            pocetBitovNaKanal = 16;
            break;
        default:
            return false;
    }

    format = format >> 3;

    // Zisti prekladanie obrázku z formátu
    int neformatovanePrekladanie = format & 0x7;

    switch (neformatovanePrekladanie) {
        case 0:
            prekladanie = 1;
            break;
        case 1:
            prekladanie = 2;
            break;
        case 2:
            prekladanie = 4;
            break;
        case 3:
            prekladanie = 8;
            break;
        case 4:
            prekladanie = 16;
            break;
        case 5:
            prekladanie = 32;
            break;
        case 6:
            prekladanie = 64;
            break;
        default:
            return false;
    }

    // Zisti, či zvyšné bity nie sú nuly
    // Ak sú = chybne zadané kódovanie
    if ((format & 0xFF00) != 0) {
        return false;
    }

    return true;
}

bool Image::nacitajObrazok(bool sameInterlace) {

    // Zisti velkost pixelu a urči celkové množstvo dát
    int velkostPixelu = pocetBitovNaKanal * pocetKanalov;

    int urcenaVelkostDat = pocetPixelov;
    int detekovanaVelkostDat = 0;

    // Prečítaný bajt
    char byte;

    if (!sameInterlace) {
        obrazok = new Pixel *[sirka];
        for (int i = 0; i < sirka; i++) {
            obrazok[i] = new Pixel[vyska];
        }
    }

    int lengthX = 0, lengthY = 0;
    int tempPreklad = prekladanie;

    Pixel novyPixel;
    int length = 0;

    while (inputFile.read(&byte, 1)) {
        if (inputFile.fail()) {
            return false;
        }

        uint16_t hex = byte;
        novyPixel.addChannel(hex);

        length = length + 8;

        if (length == velkostPixelu) {
            detekovanaVelkostDat++;

            if (!sameInterlace) {
                while (true) {
                    // Ak je X suradnica väčšia ako šírka matice
                    if (lengthX > sirka - 1) {
                        lengthX = 0;
                        lengthY = lengthY + tempPreklad;
                    }

                    if (lengthY > vyska - 1) {
                        lengthX = 0;
                        lengthY = 0;
                        tempPreklad = tempPreklad / 2;
                    }

                    if (!obrazok[lengthX][lengthY].obsadene) {
                        obrazok[lengthX][lengthY] = novyPixel;
                        obrazok[lengthX][lengthY].obsadene = true;
                        break;
                    }

                    lengthX = lengthX + tempPreklad;
                }
            } else {
                for (int i = 0; i < novyPixel.kanalyLength; i++) {
                    outputFile.write((const char *) &novyPixel.kanaly[i], sizeof(char));

                    if (outputFile.fail()) {
                        return false;
                    }
                }
            }

            novyPixel = Pixel();
            novyPixel.kanalyLength = 0;
            length = 0;
        }
    }

    if (!inputFile.eof() || detekovanaVelkostDat != urcenaVelkostDat) {
        inputFile.close();
        return false;
    }

    return true;
}

bool Image::ulozHlavicku() {

    // Zapíš hlavičku
    outputFile.write((const char *) &desiredByteOrder, sizeof(uint16_t));

    if (outputFile.fail()) {
        return false;
    }

    outputFile.write((const char *) &sirka, sizeof(uint16_t));

    if (outputFile.fail()) {
        return false;
    }

    outputFile.write((const char *) &vyska, sizeof(uint16_t));

    if (outputFile.fail()) {
        return false;
    }

    // Vytvor formát
    uint16_t interlace = 0;

    switch (desiredInterlace) {
        case 1:
            interlace = 0;
            break;
        case 2:
            interlace = 1;
            break;
        case 4:
            interlace = 2;
            break;
        case 8:
            interlace = 3;
            break;
        case 16:
            interlace = 4;
            break;
        case 32:
            interlace = 5;
            break;
        case 64:
            interlace = 6;
            break;
    }

    format = interlace;

    format = format << 3;

    uint16_t bityNaKanal = 0;

    switch (pocetBitovNaKanal) {
        case 1:
            bityNaKanal = 0;
            break;
        case 8:
            bityNaKanal = 3;
            break;
        case 16:
            bityNaKanal = 4;
            break;
    }

    format = format ^ bityNaKanal;

    format = format << 2;


    uint16_t kanaly = 0;

    switch (pocetKanalov) {
        case 1:
            kanaly = 0;
            break;
        case 3:
            kanaly = 2;
            break;
        case 4:
            kanaly = 3;
            break;
    }

    format = format ^ kanaly;

    outputFile.write((const char *) &format, sizeof(uint16_t));

    if (outputFile.fail()) {
        return false;
    }

    return true;
}

bool Image::rotujObrazok() {

    int lengthX = 0;
    int lengthY = 0;
    int tempPreklad = desiredInterlace;

    // Inicializované pole reprezentujuce obrazok v pamati
    int length = 0;

    if (desiredInterlace == 1) {
        for (int i = 0; i < vyska; i++) {
            for (int j = 0; j < sirka; j++) {
                for (int k = 0; k < obrazok[j][i].kanalyLength; k++) {
                    outputFile.write((const char *) &obrazok[j][i].kanaly[k], sizeof(char));

                    if (outputFile.fail()) {
                        return false;
                    }
                }
            }
        }
    } else {
        while ((length < (sirka * vyska))) {
            // Ak je X suradnica väčšia ako šírka matice
            if (lengthX > sirka - 1) {
                lengthX = 0;
                lengthY = lengthY + tempPreklad;
            }

            if (lengthY > vyska - 1) {
                lengthX = 0;
                lengthY = 0;
                tempPreklad = tempPreklad / 2;
            }

            if (!obrazok[lengthX][lengthY].transformovane) {
                for (int i = 0; i < obrazok[lengthX][lengthY].kanalyLength; i++) {
                    outputFile.write((const char *) &obrazok[lengthX][lengthY].kanaly[i], sizeof(char));

                    if (outputFile.fail()) {
                        return false;
                    }
                }

                obrazok[lengthX][lengthY].transformovane = true;
                length++;
            }
            lengthX = lengthX + tempPreklad;
        }
    }

    return true;
}

bool Image::processImage() {

    // Skontroluj, či dané súbory existujú/je možné vytvoriť
    if (!inputFile.is_open() || !outputFile.is_open()) {
        return false;
    }

    bool spracovanaHlavicka = spracujHlavicku();

    if (!spracovanaHlavicka) {
        return false;
    }

    bool ulozenaHlavicka = ulozHlavicku();

    if (!ulozenaHlavicka) {
        return false;
    }

    bool nacitanyObrazok = nacitajObrazok(desiredInterlace == prekladanie);

    if (!nacitanyObrazok) {
        return false;
    }

    if (desiredInterlace != prekladanie) {
        bool zrotovanyObrazok = rotujObrazok();

        if (!zrotovanyObrazok) {
            return false;
        }
    }


    return true;
}

bool recodeImage(const char *srcFileName, const char *dstFileName, int interlace, uint16_t byteOrder) {

    // Kontrola správnosti zadaného poradia bajtov
    if (byteOrder != ENDIAN_BIG && byteOrder != ENDIAN_LITTLE) {
        return false;
    }

    // Kontrola správnosti interlácie
    bool spravnaInterlacia = checkInterlace(interlace);
    if (!spravnaInterlacia) {
        return false;
    }

    // Zavolaj konštruktor
    Image image(srcFileName, dstFileName, interlace, byteOrder);

    return image.processImage();
}
