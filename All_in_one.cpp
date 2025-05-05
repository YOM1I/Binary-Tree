
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <stack>
#include <queue>
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


Stablo::Stablo(string naziv_fajla) {
    constexpr int MAX_L = 100;

    ifstream file(naziv_fajla);

    if(!file.is_open()) {
        cout << "Ne postoji fajl" << endl;
        this->uspjeh = 0;
        return ;
    }
    Korisnik** niz = new Korisnik*[MAX_L];
    int duz_niza= 0;
    string line;
    getline(file, line);
    while(getline(file, line)) {
        Korisnik*temp = new Korisnik;
        temp->prezime = ime_i_prezime(line);
        temp->ime = ime_i_prezime(line);
        temp->brtel = stoll(line);
        niz[duz_niza++] = temp;
    }
    file.close();

    stack<int> STEK;
    int low = 0;
    int high = duz_niza - 1;
    STEK.push(high);
    int mid = (low+high)/2;
    this->root = niz[mid];
    STEK.push(mid);

    while(low < STEK.top()) {
        mid = (low + STEK.top())/2;
        niz[STEK.top()]->sinLijevi = niz[mid];
        niz[mid]->otac = niz[STEK.top()]; //
        STEK.push(mid);
    }

    Korisnik*poslednji_desni = nullptr;

    while (true) {
        if(STEK.empty() ) {
            poslednji_desni->sinDesni = niz[low];
            niz[low]->otac = poslednji_desni;//
            delete niz;

            break;
        }
        high = STEK.top();
        int value = (high + low)/2;

        if(!(value > low)) {
            low = STEK.top();
            STEK.pop();
        }
        else {

            niz[low]->sinDesni = niz[value];
            niz[value]->otac = niz[low];//
            poslednji_desni = niz[value];
            STEK.push(value);
            mid = (low + STEK.top()) / 2;

            while (low < mid) {
                    niz[STEK.top()]->sinLijevi = niz[mid];
                    niz[mid]->otac = niz[STEK.top()];//
                    STEK.push(mid);
                    mid = (low + STEK.top()) / 2;

            }
        }
    }

}

int Stablo::pronadji_zarez(string red) {
    for(int i = 0 ; i < red.length(); i++) {
        if(red[i] == ',') {
            return i;
        }
    }
}

string Stablo::ime_i_prezime(string& red) {
        int poz = pronadji_zarez(red);
        string sub = red.substr(0, poz);
        red.erase(0, poz + 1);
        return sub;

}

std::vector<Stablo::Korisnik*> Stablo::svi_sljedbenici_i_prethodninci_isto_ime_i_prezime(Korisnik *temp, int p) {
    std::vector<Korisnik*> sljedbenici_i_prethodnici;
    sljedbenici_i_prethodnici.push_back(temp);
    Korisnik* pocetna = temp;
    // PRETHOD
    while (true) {
        Korisnik* preth = prethodnik(pocetna);
        if (preth != nullptr && ((preth->ime == pocetna->ime && preth->prezime == pocetna->prezime)|| (preth->prezime == pocetna->prezime && p==0))) {
            sljedbenici_i_prethodnici.push_back(preth);
            pocetna = preth;
            continue;
        }
        break;
    }
    //SLJED
    while (true) {
        Korisnik* sljed = sledbenik(temp);
        if (sljed != nullptr && ((sljed->ime == temp->ime && sljed->prezime == temp->prezime) || (sljed->prezime == temp->prezime && p == 0))) {
            sljedbenici_i_prethodnici.push_back(sljed);
            temp = sljed;
            continue;
        }
        break;
    }
    return sljedbenici_i_prethodnici;
}


void Stablo::pretraga_prezime_i_ime(string prezime, string ime) {
    Korisnik *temp = pronalazim_ako_postoji(prezime, ime);
    if(temp == nullptr) {
        cout << "Ne Postoji korisnik za brisanje" << endl;
    }
    else {
        int p = 1;
        if(ime == "") {
            p = 0;
        }
        vector<Korisnik*> lista= svi_sljedbenici_i_prethodninci_isto_ime_i_prezime(temp,p);
        for(int i = 0; i < lista.size();i++) {
            cout << lista[i]->brtel << " ";
        }
        cout << endl;
    }
}

Stablo::Korisnik * Stablo::sledbenik(Korisnik*temp) {
    Korisnik *prob = temp->sinDesni;
    if (prob != nullptr) {
        while (prob->sinLijevi != nullptr) {
            prob = prob->sinLijevi;
        }
    } else {
        Korisnik *parent = temp->otac;
        while (parent != nullptr && temp == parent->sinDesni) {
            temp = parent;
            parent = parent->otac;
        }
        prob = parent;
    }
    return prob;
}

Stablo::Korisnik * Stablo::prethodnik(Korisnik *temp) {
    Korisnik* prob = temp->sinLijevi;
    if (prob != nullptr) {

        while (prob->sinDesni != nullptr) {
            prob = prob->sinDesni;
        }
    } else {

        Korisnik *parent = temp->otac;
        while (parent != nullptr && temp == parent->sinLijevi) {
            temp = parent;
            parent = parent->otac;
        }
        prob = parent;
    }
    return prob;
}

void Stablo::izmjena_podataka(string prezime, string ime, string novo_prezime, string novo_ime, long long novo_brtel, long long brtel) {
    if(brisanje_cvora(prezime, ime , brtel) < 0) {
        return;
    }
    dodavanje(novo_prezime, novo_ime, novo_brtel);
}


int Stablo::brisanje_cvora(string prezime, string ime, long long brtel) {
    Korisnik* temp = pronalazim_ako_postoji(prezime, ime, brtel);

    if (temp == nullptr) {
        cout << "Ne postoji korisnik za brisanje" << endl;
        return -1;
    }

    temp = izabrani_korisnik(temp, 1);

    // NEMA DJECE
    if (temp->sinDesni == nullptr && temp->sinLijevi == nullptr) {
        cout << "NEMA SINA Obrisan je korisnik: " << temp->prezime << " " << temp->ime << endl;

        if (temp->otac != nullptr) {

            if (temp->otac->sinLijevi == temp) {
                temp->otac->sinLijevi = nullptr;
            } else {
                temp->otac->sinDesni = nullptr;
            }
        } else {
            this->root = nullptr;
        }

        delete temp;
        return 0;
    }

    // DVOJE
    if (temp->sinDesni != nullptr && temp->sinLijevi != nullptr) {
        Korisnik* sled = sledbenik(temp); // Pronađi sledbenika

        temp->ime = sled->ime;
        temp->prezime = sled->prezime;
        temp->brtel = sled->brtel;


        if (sled->otac != nullptr) {
            if (sled->otac->sinLijevi == sled) {
                sled->otac->sinLijevi = sled->sinDesni;
            } else {
                sled->otac->sinDesni = sled->sinDesni;
            }

            if (sled->sinDesni != nullptr) {
                sled->sinDesni->otac = sled->otac;
            }
        }

        cout << "Obrisan je korisnik: " << prezime << " " << ime << endl;
        delete sled;
        return 0;
    }

    // JEDNO DIJETE
    Korisnik* child = (temp->sinLijevi != nullptr) ? temp->sinLijevi : temp->sinDesni;

    if (temp->otac != nullptr) {
        if (temp->otac->sinDesni == temp) {
            temp->otac->sinDesni = child;
        } else {
            temp->otac->sinLijevi = child;
        }
    } else {
        this->root = child;
    }

    if (child != nullptr) {
        child->otac = temp->otac;
    }

    cout << "Obrisan je korisnik: " << prezime << " " << ime << endl;
    delete temp;
    return 0;
}


void Stablo::dodavanje(string prezime, string ime, long long brtel) {
    Korisnik* novi = new Korisnik;
    novi->ime = ime;
    novi->prezime = prezime;
    novi->brtel = brtel;
    novi->sinLijevi = nullptr;
    novi->sinDesni = nullptr;
    novi->otac = nullptr;
    novi->next = nullptr;
    Korisnik*prev = nullptr;

    //OVO AKO JE PRAZNOO
    if (this->root == nullptr) {
        this->root = novi;
        cout << "USPJESNO UBACIVANJE!!!" << endl;
        return;
    }

    Korisnik* temp = this->root;
    Korisnik* cale = nullptr;

    while (temp) {
        cale = temp;
        if (temp->prezime == prezime && temp->ime == ime) {
            temp = izabrani_korisnik(temp, 3);
            cout << "(Ubacen istoimeni korisnik)" << endl;
            temp->sinDesni = novi;
            novi->otac = temp;
            return;
        }

        if (temp->prezime < prezime || (temp->prezime == prezime && temp->ime < ime)) {
            temp = temp->sinDesni;
        } else {
            temp = temp->sinLijevi;
        }
    }

    novi->otac = cale;
    if (cale->prezime == prezime) {
        if (cale->ime < ime) {
            cale->sinDesni = novi;
        } else {
            cale->sinLijevi = novi;
        }
    } else if (cale->prezime < prezime) {
        cale->sinDesni = novi;
    } else {
        cale->sinLijevi = novi;
    }
    cout << "USPJESNO UBACIVANJE!!!" << endl;
}

Stablo::Korisnik* Stablo::pronalazim_ako_postoji(string prezime , string ime , long long brtel) {
    Korisnik* temp = this->root;

    while (temp) {
        if (temp->prezime == prezime) {
            if(ime == "") {
                return temp;
            }
            else {
                if (temp->ime == ime) {
                    if(brtel == 0){
                        return temp;
                    }
                    else {
                        if(temp->brtel == brtel) {
                            return temp;
                            }
                        }
                    }
                }
                if (temp->ime < ime) {
                    temp = temp->sinDesni;
                } else {
                    temp = temp->sinLijevi;
                }
            }
        else if (temp->prezime < prezime) {
            temp = temp->sinDesni;
            }
        else {
            temp = temp->sinLijevi;
            }
    }

    return nullptr;
}

void Stablo::ispis_stabla() const{
    Korisnik* temp = this->root;
    queue<Korisnik*> RED;
    RED.push(temp);
    while (!RED.empty()) {
        int br= RED.size();

        for (int i = 0; i < br; i++) {
            temp = RED.front();
            RED.pop();
            cout << temp->prezime << " " << temp->ime << " " << temp->brtel << endl;

            if (temp->sinLijevi != nullptr) {
                RED.push(temp->sinLijevi);
            }
            if (temp->sinDesni != nullptr) {
                RED.push(temp->sinDesni);
            }
        }
        cout << "---------------" << endl;
    }
}

void Stablo::tekstulne_poruke_istorija() {
    niz = new Korisnik*[this->n];
    for (int i = 0; i < this->n; i++) {
        niz[i] = nullptr;
    }
}

void Stablo::posalji_poruku(string prezime ,string ime,  long long brtel) {
    Korisnik*temp = pronalazim_ako_postoji(prezime, ime, brtel);

    if(!temp) {
        cout << "Ne postoji trazeni konkat" << endl;
        return;
    }
    temp = izabrani_korisnik(temp, 1);
    Korisnik* novi = new Korisnik;
    novi->ime = temp->ime;
    novi->prezime = temp->prezime;
    novi->brtel = temp->brtel;

    temp = novi;

    int i = prodnaji_u_niz(temp);
    int j;
    Korisnik*vrijednost = nullptr;
    if(i == -1) {
        vrijednost = temp;
        j = this->n;
    }
    else {
        delete temp;
        vrijednost = niz[i];
        j = i;
    }
    for( ; j > 0; j--) {
        niz[j] = niz[j-1];
    }
    niz[0] = vrijednost;
}

int Stablo::prodnaji_u_niz(Korisnik *temp) {
    for(int i = 0; i < this->n; i++) {
        if(niz[i] != nullptr) {
            if(temp->brtel == niz[i]->brtel && temp->ime == niz[i]->ime  && temp->prezime == niz[i]->prezime) {
                return i;
            }
        }
    }
    return -1;
}

void Stablo::printaj_niz() {
    for(int i = 0; i < this->n; i++) {
        if(niz[i] != nullptr){
            cout << niz[i]->prezime << " ";
        }
        else {
            cout << "0" << " ";
        }
    }
    cout << endl;
}

void Stablo::slanje_sadrzaja(string prezime, string ime, long long brtel) {
    Korisnik*temp = pronalazim_ako_postoji(prezime, ime, brtel);
    if(!temp) {
        cout << "Ne postoji trazeni konkat" << endl;
        return;
    }
    temp = izabrani_korisnik(temp, 1);

    Korisnik* novi = new Korisnik;
    novi->ime = temp->ime;
    novi->prezime = temp->prezime;
    novi->brtel = temp->brtel;
    novi->komunikacija = 0;

    temp = novi;

    if(!this->head) {
        head = temp;
        tail = temp;
        temp->komunikacija++;

    }
    else {
        int k = pronadji_u_listi(temp);
        if(k == 0) {
            Korisnik*pomocni = nadji(temp);
            pomocni->komunikacija++;
            delete temp;
            return;
        }
        else if(k == -1) {
            tail->next = temp;
            temp->prev = tail;
            tail = temp;
            temp->komunikacija++;
        }

        else {
            Korisnik*pomocni = nadji(temp);
            delete temp;
            temp = pomocni;

            if(temp->komunikacija >= this->x && temp != this->head) {
                Korisnik*p = temp->prev;
                Korisnik*j = head->next;


                temp->prev = this->head->prev;
                this->head->next = temp->next;
                if(temp->next != nullptr) {
                    temp->next->prev= this->head;
                }
                this->head->prev = p;
                p->next = this->head;
                temp->next = j;
                j->prev = temp;
                this->head = temp;
            }
            else if(temp->komunikacija < this->x){
                Korisnik*q = temp->prev;
                q->next = temp->next;
                if(temp->next != nullptr) {
                    temp->next->prev = q;
                }
                if(q->prev != nullptr) {
                    q->prev->next = temp;
                }
                temp->prev = q->prev;
                temp->next = q;
                q->prev = temp;
                if(temp == tail) {
                    tail = q;
                }
                if(q == head) {
                    head = temp;
                }

            }
            temp->komunikacija++;
        }
    }
}

int Stablo::pronadji_u_listi(Korisnik *temp) {
    if(this->head == temp) {
        return 0;
    }
    Korisnik*copy_head = this->head;
    while(copy_head) {
        if(copy_head->brtel == temp->brtel && temp->ime == copy_head->ime  && temp->prezime == copy_head->prezime) {
            //cout << "PRONASAO";
            return 1;
        }
        copy_head = copy_head->next;
    }
    return -1;
}

void Stablo::ispis_liste() {
    Korisnik*temp = this->head;
    for(; temp!= nullptr; temp = temp->next) {
        cout<< temp->prezime << " " << temp->brtel << " -> ";
    }
    cout <<endl;
}

Stablo::Korisnik * Stablo::nadji(Korisnik *temp) {
    Korisnik*pomocni = this->head;
    for(; pomocni!= nullptr; pomocni = pomocni->next) {
        if(pomocni->brtel == temp->brtel) return pomocni;
    }
}

Stablo::Korisnik * Stablo::izabrani_korisnik(Korisnik *temp, int p) {
    string prezime = temp->prezime;
    string ime = temp->ime;
    vector<Korisnik*> lista= svi_sljedbenici_i_prethodninci_isto_ime_i_prezime(temp, p);

    if(lista.size() > 1) {
        if(p == 3) {
            return lista[lista.size() - 1];
        }
            cout << "Ima vise osoba sa prezimenom i imenom " << prezime << " " << ime << endl;
            cout << "Izaberite redni broj osobe sa trazenim brojem (pocevsi od nule) " <<  endl;
            for(int i = 0; i < lista.size() ; i++) {
                cout << lista[i]->brtel << " " ;
            }
            cout << endl;
            int i;
            cin >> i;
            cin.ignore();

            temp = lista[i];
        }
    else {
        temp = lista[0];
    }
    return temp;
    }

int Stablo::vrati_uspjeh() const {
    return uspjeh;
}

Stablo::~Stablo() {
    Korisnik*temp = this->root;
    stack<Korisnik*> STEK;
    STEK.push(temp);
    while (!STEK.empty()) {
        temp = STEK.top();
        STEK.pop();
        if(temp->sinDesni != nullptr) {
            STEK.push(temp->sinDesni);
        }
        if(temp->sinLijevi != nullptr) {
            STEK.push(temp->sinLijevi);
        }
        delete temp;
    }
    for(int i = 0 ; i < this->n; i++) {
        if(niz[i] == nullptr) {
            cout << "obrisao 0 " << endl;
        }
        else {
            cout << "obrisao" << niz[i]->prezime<< endl;
        }
        delete niz[i];
    }
    Korisnik*q = this->head;
    while (q) {
        Korisnik*p = q->next;
        cout << "Brisem " << q->prezime << endl;
        delete q;
        q = p;
    }

}


int main() {
    cout << "---------DOBRODOSLO--------" << endl;

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
