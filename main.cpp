#include <iostream>
#include <string>
#include <fstream>
#include "Stablo.h"
using namespace std;


int main() {
    cout << "---------DOBRODOSLI--------" << endl;

    cout << "Unesite naziv fajla Kontakata" << endl;
    string naziv_fajla;
    getline(cin, naziv_fajla);
    Stablo* stablo = new Stablo(naziv_fajla);
    if(stablo->vrati_uspjeh() == 0) {
        return -1;
    }
    int n;
    int x;

    cout << "Unesite max duzinu istorije" << endl;
    cin >> n;
    cin.ignore();
    stablo->setN(n);
    cout << "Unesite granicu x" << endl;
    cin >> x;
    cin.ignore();
    stablo->setX(x);
    stablo->tekstulne_poruke_istorija();

    bool izlaz = true;
    while (izlaz) {
        string ime;
        string prezime;
        string novo_ime;
        string novo_prezime;
        long long brtel;
        long long novo_brtel;

        cout << "---------MENI--------" << endl;
        cout << "1 - Pretraga kontakta po prezimenu" << endl;
        cout << "2 - Pretraga kontakta po prezimenu i imenu" << endl;
        cout << "3 - Izmjena kontakta" << endl;
        cout << "4 - Dodavanje novog kontakta" << endl;
        cout << "5 - Uklanjanje kontakta" << endl;
        cout << "6 - Ispis stabla" << endl;
        cout << "7 - Posalji tekstualnu poruku" << endl;
        cout << "8 - Posalji sadrzaj" << endl;
        cout << "9 - Kraj" << endl;
        cout << endl;
        cout << "Opcija: " << endl;

        int answer;
        if (!(cin >> answer)) {
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }
        cin.ignore();
        switch (answer) {
            case 1:
                cout << "Prezime konakta:" << endl;
                getline(cin, prezime);
                stablo->pretraga_prezime_i_ime(prezime);
                break;
            case 2:
                cout << "Prezime konakta:" << endl;
                getline(cin, prezime);
                cout << "Ime konakta:" << endl;
                getline(cin, ime);
                stablo->pretraga_prezime_i_ime(prezime, ime);
                break;
            case 3:
                cout << "Prezime konakta:" << endl;
                getline(cin, prezime);
                cout << "Ime konakta:" << endl;
                getline(cin, ime);
                //cout << "Telefon konakta:" << endl;
                //cin >> brtel;
                //cin.ignore();

                cout << "Novo Prezime konakta:" << endl;
                getline(cin, novo_prezime);
                cout << "Novo Ime konakta:" << endl;
                getline(cin, novo_ime);
                cout << "Novi Telefon konakta:" << endl;
                cin >> novo_brtel;
                stablo->izmjena_podataka(prezime, ime , novo_prezime, novo_ime, novo_brtel);
                break;
            case 4:
                cout << "Prezime konakta:" << endl;
                getline(cin, prezime);
                cout << "Ime konakta:" << endl;
                getline(cin, ime);
                cout << "Telefon konakta:" << endl;
                cin >> brtel;
                stablo->dodavanje(prezime, ime, brtel);
                break;
            case 5:
                cout << "Prezime konakta:" << endl;
                getline(cin, prezime);
                cout << "Ime konakta:" << endl;
                getline(cin, ime);
                stablo->brisanje_cvora(prezime, ime);
                break;
            case 6:
                stablo->ispis_stabla();
                break;
            case 7:
                cout << "Prezime konakta:" << endl;
                getline(cin, prezime);
                cout << "Ime konakta:" << endl;
                getline(cin, ime);
                //cout << "Telefon konakta:" << endl;
                //cin >> brtel;
                stablo->posalji_poruku(prezime, ime );
                stablo->printaj_niz();
                break;
            case 8:
                cout << "Prezime konakta:" << endl;
                getline(cin, prezime);
                cout << "Ime konakta:" << endl;
                getline(cin, ime);
                //cout << "Telefon konakta:" << endl;
                //cin >> brtel;
                stablo->slanje_sadrzaja(prezime, ime );
                stablo->ispis_liste();
                break;
            case 9:
                delete stablo;
                izlaz = false;
                break;
            default:
                cout << "Nepoznata opcija" << endl;
        }
    }
    
    return 0;
}
