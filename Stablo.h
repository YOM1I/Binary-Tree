#ifndef STABLO_H
#define STABLO_H

#include <string>
#include <iostream>
#include <vector>
using namespace std;

class Stablo {

protected:
    struct Korisnik {
        string prezime;
        string ime;
        long long brtel;
        Korisnik* sinDesni = nullptr;
        Korisnik* sinLijevi = nullptr;
        Korisnik* otac = nullptr;
        int komunikacija = 0;
        Korisnik*next = nullptr;
        Korisnik*prev = nullptr;

    };
    Korisnik*root;
    int uspjeh = 1;
    //-----------------------
    Korisnik**niz;
    int x;
    int n;
    //------------------------
    Korisnik*head = nullptr;
    Korisnik*tail = nullptr;

    ;
public:
    Stablo(string naziv_fajla);

    int pronadji_zarez(string red);
    string ime_i_prezime(string& red);
    std::vector<Korisnik*> svi_sljedbenici_i_prethodninci_isto_ime_i_prezime(Korisnik *temp, int p = 0);
    void pretraga_prezime_i_ime(string prezime, string ime = "");
    Korisnik* sledbenik(Korisnik*temp);
    Korisnik* prethodnik(Korisnik*temp);
    void izmjena_podataka(string prezime, string ime , string novo_prezime, string novo_ime, long long novo_brtel, long long brtel = 0);
    int brisanje_cvora(string prezime, string ime, long long brtel = 0);
    void dodavanje(string prezime, string ime, long long brtel);
    Korisnik* pronalazim_ako_postoji(string prezime, string ime = "", long long brtel = 0);
    void ispis_stabla() const;
    int vrati_uspjeh() const;

    //------------------------------------------------------------
    void setN(int a) {
        this->n = a;
    }
    void setX(int b) {
        this->x = b;
    }

    void tekstulne_poruke_istorija();
    void posalji_poruku(string prezime, string ime, long long brtel = 0);
    int prodnaji_u_niz(Korisnik*temp);
    void printaj_niz();
    //------------------------------------------------------------
    void slanje_sadrzaja(string prezime, string ime, long long brtel = 0);
    int pronadji_u_listi(Korisnik*temp);
    void ispis_liste();
    Korisnik*nadji(Korisnik*temp);


    Korisnik*izabrani_korisnik(Korisnik*temp,int p=0);

    ~Stablo();
};

#endif //STABLO_H
