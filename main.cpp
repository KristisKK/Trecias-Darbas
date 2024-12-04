#include <iostream>
#include <cstring>
using namespace std;

const char ABECELE[26] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };

// Pagalbinė funkcija rakto pailginimui
string SukurtiPilnaRaktoEilute(const char tekstas[], const char raktas[]) {
    string pilnasRaktas = raktas;
    while (pilnasRaktas.length() < strlen(tekstas)) {
        pilnasRaktas += raktas;
    }
    return pilnasRaktas.substr(0, strlen(tekstas));
}

// Teksto apdorojimas naudojant abėcėlę
string ProcesuotiSuAbecEle(const char tekstas[], const char raktas[], bool uzsifruoti) {
    int tekstoIlgis = strlen(tekstas);
    string pilnasRaktas = SukurtiPilnaRaktoEilute(tekstas, raktas);
    string rezultatas = "";

    for (int i = 0; i < tekstoIlgis; i++) {
        if (isalpha(tekstas[i])) { // Tik apdorojame raides
            int indeksasTeksto = toupper(tekstas[i]) - 'A';
            int indeksasRakto = toupper(pilnasRaktas[i]) - 'A';
            int indeksasRezultato = uzsifruoti
                                    ? (indeksasTeksto + indeksasRakto) % 26
                                    : (indeksasTeksto - indeksasRakto + 26) % 26;
            rezultatas += ABECELE[indeksasRezultato];
        } else {
            rezultatas += tekstas[i]; // Ne raidės lieka nepakeistos
        }
    }
    return rezultatas;
}

// Teksto apdorojimas naudojant ASCII koduotę
string ProcesuotiSuASCII(const char tekstas[], const char raktas[], bool uzsifruoti) {
    int tekstoIlgis = strlen(tekstas);
    string pilnasRaktas = SukurtiPilnaRaktoEilute(tekstas, raktas);
    string rezultatas = "";

    const int asciiPradzia = 33, asciiPabaiga = 126, asciiIlgis = asciiPabaiga - asciiPradzia + 1;

    for (int i = 0; i < tekstoIlgis; i++) {
        if (tekstas[i] >= asciiPradzia && tekstas[i] <= asciiPabaiga) {
            // Tik apdorojame simbolius ASCII diapazone
            int indeksasTeksto = tekstas[i] - asciiPradzia;
            int indeksasRakto = pilnasRaktas[i] - asciiPradzia;
            int indeksasRezultato = uzsifruoti
                                    ? (indeksasTeksto + indeksasRakto) % asciiIlgis
                                    : (indeksasTeksto - indeksasRakto + asciiIlgis) % asciiIlgis;
            rezultatas += static_cast<char>(indeksasRezultato + asciiPradzia);
        } else {
            rezultatas += tekstas[i]; // Ne ASCII simboliai lieka nepakeisti
        }
    }
    return rezultatas;
}

int main() {
    int pasirinkimas;
    char tekstas[100];
    char raktas[100];

    while (true) {
        cout << "Pasirinkite operacija kuria norite atlikti su tekstu:" << endl;
        cout << "1. Sifravimas/Desifravimas naudojant abecele" << endl;
        cout << "2. Sifravimas/Desifravimas naudojant ASCII koduote" << endl;
        cout << "3. Iseiti" << endl;
        cout << "Jusu pasirinkimas: ";
        cin >> pasirinkimas;

        if (pasirinkimas == 3) break;

        int operacija;
        cout << "Pasirinkite operacija kuria norite atlikti:" << endl;
        cout << "1. Sifravimas" << endl;
        cout << "2. Desifravimas" << endl;
        cin >> operacija;

        cout << "Irasykite teksta: ";
        cin >> tekstas;
        cout << "Irasykite rakta: ";
        cin >> raktas;

        bool uzsifruoti = (operacija == 1);
        string rezultatas;

        if (pasirinkimas == 1) { // Abėcėlė
            rezultatas = ProcesuotiSuAbecEle(tekstas, raktas, uzsifruoti);
        } else if (pasirinkimas == 2) { // ASCII
            rezultatas = ProcesuotiSuASCII(tekstas, raktas, uzsifruoti);
        }

        cout << (uzsifruoti ? "Uzsifruotas" : "Desifruotas") << " tekstas: " << rezultatas << endl;
    }

    return 0;
}

