#include<iostream>
#include<vector>
#include<fstream>
using namespace std;
//Andreea Maria Olaru - Mall

class Resurse {
private:
	string tip;
public:
	virtual void DescrieResursa() = 0;

	Resurse() {
		this->tip = "Tipul resursei este: ";
	}

	string getTip() {
		return this->tip;
	}

	void setTip(string tip) {
		if (tip.length() > 0) {
			this->tip = tip;
		}
	}
};

class MediiComerciale {
private:
	string tip;
public:
	virtual void DescrieMediuComercial() = 0;

	MediiComerciale() {
		this->tip = "Tipul mediului comercial: ";
	}

	string getTip() {
		return this->tip;
	}

	void setTip(string tip) {
		if (tip.length() > 0) {
			this->tip = tip;
		}
	}
};

class Magazine : public MediiComerciale {
private:
	static int nrInventar;
	const int nrTotalMagazine;
	string numeFirma;
	float suprafata;
	int nrArticole;
	string* numeArticole;
public:
	static int getNrInventar() {
		return nrInventar;
	}

	void DescrieMediuComercial() {
		cout << "Firma " << numeFirma << " are o suprafata de " << suprafata << " si un numar de " << nrArticole << " articole." << endl;
	}

	Magazine() : MediiComerciale(), nrTotalMagazine(nrInventar++) {
		this->numeFirma = "Zara";
		this->suprafata = 25;
		this->nrArticole = 4;
		this->numeArticole = new string[nrArticole];
		for (int i = 0; i < nrArticole; i++) {
			this->numeArticole[i] = numeArticole[i];
			numeArticole[0] = "tricouri";
			numeArticole[1] = "pantaloni";
			numeArticole[2] = "rochii";
			numeArticole[3] = "fuste";
		}
	}

	Magazine(string numeFirma, float suprafata) : MediiComerciale(), nrTotalMagazine(nrInventar) {
		nrInventar++;
		this->numeFirma = numeFirma;
		this->suprafata = suprafata;
		this->nrArticole = 2;
		this->numeArticole = new string[nrArticole];
		for (int i = 0; i < nrArticole; i++) {
			this->numeArticole[i] = numeArticole[i];
			numeArticole[0] = "hanorace";
			numeArticole[1] = "adidasi";
		}
	}

	Magazine(string numeFirma, float suprafata, int nrArticole, string* numeArticole) : MediiComerciale(), nrTotalMagazine(nrInventar) {
		nrInventar++;
		this->numeFirma = numeFirma;
		this->suprafata = suprafata;
		this->nrArticole = nrArticole;
		this->numeArticole = new string[nrArticole];
		for (int i = 0; i < nrArticole; i++) {
			this->numeArticole[i] = numeArticole[i];
		}
	}

	Magazine(const Magazine& m) : MediiComerciale(m), nrTotalMagazine(nrInventar++) {
		this->numeFirma = m.numeFirma;
		this->suprafata = m.suprafata;
		this->nrArticole = m.nrArticole;
		this->numeArticole = new string[m.nrArticole];
		for (int i = 0; i < m.nrArticole; i++) {
			this->numeArticole[i] = m.numeArticole[i];
		}
	}

	Magazine operator=(const Magazine& mg) {
		if (this != &mg) {
			MediiComerciale::operator=(mg);
			this->numeFirma = mg.numeFirma;
			this->suprafata = mg.suprafata;
			this->nrArticole = mg.nrArticole;
			if (this->numeArticole != NULL) {
				delete[]this->numeArticole;
			}
			this->numeArticole = new string[mg.nrArticole];
			for (int i = 0; i < mg.nrArticole; i++) {
				this->numeArticole[i] = mg.numeArticole[i];
			}
		}
		return *this;
	}

	Magazine operator+=(const Magazine& m) {
		int aux = this->nrArticole;
		this->nrArticole += m.nrArticole;
		string* vector = new string[this->nrArticole];
		for (int i = 0; i < aux; i++) {
			vector[i] = this->numeArticole[i];
		}
		for (int i = aux; i < this->nrArticole; i++) {
			vector[i] = m.numeArticole[i - aux];
		}
		if (this->numeArticole != NULL) {
			delete[]this->numeArticole;
		}
		this->numeArticole = vector;
		return *this;
	}

	bool operator!=(const Magazine& m) {
		return this->suprafata != m.suprafata && this->nrArticole != m.nrArticole;
	}

	string& operator[](int i) {
		if (i >= 0 && i < nrArticole) {
			return numeArticole[i];
		}
	}

	friend ostream& operator<<(ostream& op, const Magazine& m) {
		op << "Magazinul " << m.numeFirma << " , cu suprafata de " << m.suprafata << " m^2, are " << m.nrArticole << " tipuri de articole, si anume: ";
		if (m.nrArticole > 0) {
			for (int i = 0; i < m.nrArticole; i++) {
				op << m.numeArticole[i] << ", ";
			}
		}
		else {
			op << " inca nu are articole.";
		}
		op << endl;
		return op;
	}

	friend ofstream& operator<<(ofstream& ecran, const Magazine& m) {
		ecran << m.numeFirma << endl;
		ecran << m.suprafata << endl;
		ecran << m.nrArticole << endl;
		if (m.nrArticole > 0) {
			for (int i = 0; i < m.nrArticole; i++) {
				ecran << m.numeArticole[i] << " ";
			}
		}
		ecran << endl;
		return ecran;
	}

	friend istream& operator>>(istream& is, Magazine& m) {
		cout << "Numele firmei: ";
		is >> m.numeFirma;
		cout << "Suprafata: ";
		is >> m.suprafata;
		cout << "Numar articole: ";
		is >> m.nrArticole;
		cout << "Tipul articolelor: ";
		if (m.numeArticole != NULL) {
			delete[]m.numeArticole;
		}
		m.numeArticole = new string[m.nrArticole];
		for (int i = 0; i < m.nrArticole; i++) {
			is >> m.numeArticole[i];
		}
		return is;
	}

	friend ifstream& operator>>(ifstream& is, Magazine& m) {
		is >> m.numeFirma;
		is >> m.suprafata;
		is >> m.nrArticole;
		if (m.numeArticole != NULL) {
			delete[]m.numeArticole;
		}
		m.numeArticole = new string[m.nrArticole];
		for (int i = 0; i < m.nrArticole; i++) {
			is >> m.numeArticole[i];
		}
		return is;
	}

	void scrieInFisierBinar(fstream& f) {
		f.write((char*)&this->numeFirma, sizeof(string));
		f.write((char*)&this->suprafata, sizeof(float));
		f.write((char*)&this->nrArticole, sizeof(int));
		int lungime = strlen((char*)this->numeArticole);
		f.write((char*)&lungime, sizeof(int));
		for (int i = 0; i < lungime; i++) {
			f.write((char*)&this->numeArticole[i], sizeof(string));
		}
	}

	void citesteDinFisierBinar(fstream& f) {
		f.read((char*)&this->numeFirma, sizeof(string));
		f.read((char*)&this->suprafata, sizeof(float));
		f.read((char*)&this->nrArticole, sizeof(int));
		int lungime;
		f.read((char*)&lungime, sizeof(int));
		if (this->numeArticole != NULL) {
			delete[]this->numeArticole;
		}
		this->numeArticole = new string[lungime + 1];
		for (int i = 0; i < lungime; i++) {
			f.read((char*)&this->numeArticole[i], sizeof(string));
		}
		this->numeArticole[lungime] = '\0';
	}

	~Magazine() {
		if (this->numeArticole != NULL) {
			delete[]this->numeArticole;
		}
	}

	void afisareMagazine() {
		cout << "Magazinul " << numeFirma << " , cu suprafata de " << suprafata << " m^2, are " << nrArticole << " tipuri de articole vestimentare, si anume: ";
		if (nrArticole > 0) {
			for (int i = 0; i < nrArticole; i++) {
				cout << numeArticole[i] << ", ";
			}
		}
		else {
			cout << " inca nu are articole.";
		}
		cout << endl;
	}

	void adaugareArticol(string numeArticol) {
		string* aux = new string[this->nrArticole + 1];
		for (int i = 0; i < this->nrArticole; i++) {
			aux[i] = this->numeArticole[i];
		}
		aux[this->nrArticole] = numeArticol;
		this->nrArticole++;
		if (this->numeArticole) {
			delete[]this->numeArticole;
		}
		this->numeArticole = aux;
	}

	int getNrTotalMagazine() {
		return nrTotalMagazine;
	}

	void setArticole(int nrArticole, string* numeArticole) {
		if (nrArticole > 0) {
			this->nrArticole = nrArticole;
			if (this->numeArticole != NULL) {
				delete[]this->numeArticole;
			}
			this->numeArticole = new string[nrArticole];
			for (int i = 0; i < nrArticole; i++) {
				this->numeArticole[i] = numeArticole[i];
			}
		}
	}

	string getNumeFirma() {
		return numeFirma;
	}
	void setNumeFirma(string numeFirma) {
		if (this->numeFirma.length() > 0) {
			this->numeFirma = numeFirma;
		}
	}

	float getSuprafata() {
		return suprafata;
	}
	void setSuprafata(float suprafata) {
		if (suprafata > 0) {
			this->suprafata = suprafata;
		}
	}

	int getNrArticole() {
		return nrArticole;
	}
	void setNrArticole(int nrArticole) {
		if (nrArticole > 0) {
			this->nrArticole = nrArticole;
		}
	}

	string* getNumeArticole() {
		return numeArticole;
	}
	string getNumeArticol(int i) {
		if (i >= 0 && i < nrArticole) {
			return numeArticole[i];
		}
	}
	friend string getArticole(const Magazine& m);
};
int Magazine::nrInventar = 100;

string getArticole(const Magazine& m) {
	string aux = ", ";
	for (int i = 0; i < m.nrArticole; i++) {
		aux += m.numeArticole[i] + ", ";
	}
	return aux;
}

class Angajati : public Resurse {
private:
	static int idAngajat;
	const int nrMaximZileConcediu;
	string uniforma;
	float salariu;
	int nrAngajati;
	string* numeAngajati;
public:
	static int getIdAngajat() {
		return idAngajat;
	}

	void DescrieResursa() {
		cout << "Angajatii au ca si uniforma " << uniforma << " si un salariu de " << salariu << " lei."<<endl;
	}

	Angajati() : Resurse(), nrMaximZileConcediu(idAngajat++) {
		this->uniforma = "rochie";
		this->salariu = 2600;
		this->nrAngajati = 2;
		this->numeAngajati = new string[nrAngajati];
		for (int i = 0; i < nrAngajati; i++) {
			this->numeAngajati[i] = numeAngajati[i];
			numeAngajati[0] = "Ioana";
			numeAngajati[1] = "Alexia";
		}
	}

	Angajati(string uniforma, float salariu) : Resurse(), nrMaximZileConcediu(idAngajat) {
		idAngajat++;
		this->uniforma = uniforma;
		this->salariu = salariu;
		this->nrAngajati = 4;
		this->numeAngajati = new string[nrAngajati];
		for (int i = 0; i < nrAngajati; i++) {
			this->numeAngajati[i] = numeAngajati[i];
			numeAngajati[0] = "George";
			numeAngajati[1] = "Laura";
			numeAngajati[2] = "Razvan";
			numeAngajati[3] = "Daniel";
		}
	}

	Angajati(string uniforma, float salariu, int nrAngajati, string* numeAngajati) : Resurse(), nrMaximZileConcediu(idAngajat) {
		idAngajat++;
		this->uniforma = uniforma;
		this->salariu = salariu;
		this->nrAngajati = nrAngajati;
		this->numeAngajati = new string[nrAngajati];
		for (int i = 0; i < nrAngajati; i++) {
			this->numeAngajati[i] = numeAngajati[i];
		}
	}

	Angajati(const Angajati& a) : Resurse(a), nrMaximZileConcediu(idAngajat++) {
		this->uniforma = a.uniforma;
		this->salariu = a.salariu;
		this->nrAngajati = a.nrAngajati;
		this->numeAngajati = new string[a.nrAngajati];
		for (int i = 0; i < nrAngajati; i++) {
			this->numeAngajati[i] = numeAngajati[i];
		}
	}

	Angajati operator=(const Angajati& a) {
		if (this != &a) {
			Resurse::operator=(a);
			this->uniforma = a.uniforma;
			this->salariu = a.salariu;
			this->nrAngajati = a.nrAngajati;
			if (this->numeAngajati != NULL) {
				delete[]this->numeAngajati;
			}
			this->numeAngajati = new string[a.nrAngajati];
			for (int i = 0; i < a.nrAngajati; i++) {
				this->numeAngajati[i] = a.numeAngajati[i];
			}
		}
		return *this;
	}

	friend ostream& operator<<(ostream& opr, const Angajati& angj) {
		opr<<"Angajatii au ca si uniforma: " << angj.uniforma << ", au un salariu de " << angj.salariu << " lei, sunt in numar de " << angj.nrAngajati << " si se numesc: ";
		if (angj.nrAngajati > 0) {
			for (int i = 0; i < angj.nrAngajati; i++) {
				opr << angj.numeAngajati[i] << ", ";
			}
		}
		else {
			opr << "NA";
		}
		opr << endl;
		return opr;
	}

	friend ofstream& operator<<(ofstream& op, const Angajati& a) {
		op << a.uniforma << endl;
		op << a.salariu << endl;
		op << a.nrAngajati << endl;
		if (a.nrAngajati > 0) {
			for (int i = 0; i < a.nrAngajati; i++) {
				op << a.numeAngajati[i] << " ";
			}
		}
		op << endl;
		return op;
	}

	friend istream& operator>>(istream& is, Angajati& a) {
		cout << "Uniforma: ";
		is >> a.uniforma;
		cout << "Salariu: ";
		is >> a.salariu;
		cout << "Numar angajati: ";
		is >> a.nrAngajati;
		cout << "Nume angajati: ";
		if (a.numeAngajati != NULL) {
			delete[]a.numeAngajati;
		}
		a.numeAngajati = new string[a.nrAngajati];
		for (int i = 0; i < a.nrAngajati; i++) {
			is >> a.numeAngajati[i];
		}
		return is;
	}

	friend ifstream& operator>>(ifstream& is, Angajati& a) {;
		is >> a.uniforma;
		is >> a.salariu;
		is >> a.nrAngajati;
		if (a.numeAngajati != NULL) {
			delete[]a.numeAngajati;
		}
		a.numeAngajati = new string[a.nrAngajati];
		for (int i = 0; i < a.nrAngajati; i++) {
			is >> a.numeAngajati[i];
		}
		return is;
	}

	void scrieInFisierBinar(fstream& fis) {
		fis.write((char*)&this->uniforma, sizeof(string));
		fis.write((char*)&this->salariu, sizeof(float));
		fis.write((char*)&this->nrAngajati, sizeof(int));
		int lungime2 = strlen((char*)this->numeAngajati);
		fis.write((char*)&lungime2, sizeof(int));
		for (int i = 0; i < lungime2; i++) {
			fis.write((char*)&this->numeAngajati[i], sizeof(string));
		}
	}

	void citesteDinFisierBinar(fstream& bin) {
		bin.read((char*)&this->uniforma, sizeof(string));
		bin.read((char*)&this->salariu, sizeof(float));
		bin.read((char*)&this->nrAngajati, sizeof(int));
		int lungime3;
		bin.read((char*)&lungime3, sizeof(int));
		if (this->numeAngajati != NULL) {
			delete[]this->numeAngajati;
		}
		this->numeAngajati = new string[lungime3 + 1];
		for (int i = 0; i < lungime3; i++) {
			bin.read((char*)&this->numeAngajati[i], sizeof(string));
		}
		this->numeAngajati[lungime3] = '\0';
	}

	Angajati operator+(Angajati an) {
		Angajati aux = *this;
		aux.uniforma = this->uniforma + an.uniforma;
		aux.salariu = this->salariu + an.salariu;
		aux.nrAngajati = this->nrAngajati + an.nrAngajati;
		if (aux.numeAngajati != NULL) {
			delete[]aux.numeAngajati;
		}
		aux.numeAngajati = new string[aux.nrAngajati];
		for (int i = 0; i < this->nrAngajati; i++) {
			aux.numeAngajati[i] = this->numeAngajati[i];
		}
		for (int i = this->nrAngajati; i < aux.nrAngajati; i++) {
			aux.numeAngajati[i] = an.numeAngajati[i - this->nrAngajati];
		}
		return aux;
	}

	Angajati operator+(int salariu) const {
		Angajati aux = *this;
		aux.salariu = this->salariu + salariu;
		return aux;
	}

	bool operator>(Angajati a) {
		return this->salariu > a.salariu && this->nrAngajati > a.nrAngajati;
	}

	~Angajati() {
		if (this->numeAngajati != NULL) {
			delete[]this->numeAngajati;
		}
	}

	void afisareAngajati() {
		cout << "Angajatii au ca si uniforma: " << uniforma << ", au un salariu de " << salariu << " lei, sunt in numar de " << nrAngajati << " si se numesc: ";
		if (nrAngajati > 0) {
			for (int i = 0; i < nrAngajati; i++) {
				cout << numeAngajati[i] << ", ";
			}
		}
		else {
			cout << "nu exista angajati.";
		}
		cout << endl;
	}

	void adaugareAngajat(string numeAngajat) {
		string* aux = new string[this->nrAngajati + 1];
		for (int i = 0; i < this->nrAngajati; i++) {
			aux[i] = this->numeAngajati[i];
		}
		aux[this->nrAngajati] = numeAngajat;
		this->nrAngajati++;
		if (this->numeAngajati) {
			delete[]this->numeAngajati;
		}
		this->numeAngajati = aux;
	}

	int getNrMaximZileConcediu() {
		return nrMaximZileConcediu;
	}

	void setAngajati(int nrAngajati, string* numeAngajati) {
		if (nrAngajati > 0) {
			this->nrAngajati = nrAngajati;
			if (this->numeAngajati != NULL) {
				delete[]this->numeAngajati;
			}
			this->numeAngajati = new string[nrAngajati];
			for (int i = 0; i < nrAngajati; i++) {
				this->numeAngajati[i] = numeAngajati[i];
			}
		}
	}

	string getUniforma() {
		return uniforma;
	}
	void setUniforma(string uniforma) {
		if (this->uniforma.length() > 0) {
			this->uniforma = uniforma;
		}
	}

	float getSalariu() {
		return salariu;
	}
	void setSalariu(float salariu) {
		if (salariu > 0) {
			this->salariu = salariu;
		}
	}

	int getNrAngajati() {
		return nrAngajati;
	}
	void setNrAngajati(int nrAngajati) {
		if (nrAngajati > 0) {
			this->nrAngajati = nrAngajati;
		}
	}

	string* getNumeAngajati() {
		return numeAngajati;
	}
	string getNumeAngajat(int i) {
		if (i >= 0 && i < nrAngajati) {
			return numeAngajati[i];
		}
	}
	friend string getSirAngajati(const Angajati& an);
}; 
int Angajati::idAngajat = 200;

string getSirAngajati(const Angajati& an) {
	string aux = ", ";
	for (int i = 0; i < an.nrAngajati; i++) {
		aux += an.numeAngajati[i] + ", ";
	}
	return aux;
}

class Produse : public Resurse {
private:
	static int nrInventar;
	const int TVA;
	int pret;
	float greutate;
	int cantitate;
	string* numeProduse;
public:
	static int getNrInventar() {
		return nrInventar;
	}

	void DescrieResursa() {
		cout << "Produsele au un pret de " << pret << " lei si au o greutate de " << greutate << " kg." << endl;;
	}

	Produse() : Resurse(), TVA(nrInventar++) {
		this->pret = 160;
		this->greutate = 2;
		this->cantitate = 2;
		this->numeProduse= new string[cantitate];
		for (int i = 0; i < cantitate; i++) {
			this->numeProduse[i] = numeProduse[i];
			numeProduse[0] = "rochie";
			numeProduse[1] = "hanorac";
		}
	}

	Produse(int pret, float greutate) : Resurse(), TVA(nrInventar) {
		nrInventar++;
		this->pret = pret;
		this->greutate = greutate;
		this->cantitate = 2;
		this->numeProduse = new string[cantitate];
		for (int i = 0; i < cantitate; i++) {
			this->numeProduse[i] = numeProduse[i];
			numeProduse[0] = "fusta";
			numeProduse[1] = "tricou";
		}
	}

	Produse(int pret, float greutate, int cantitate, string* numeProduse) : Resurse(), TVA(nrInventar) {
		nrInventar++;
		this->pret = pret;
		this->greutate = greutate;
		this->cantitate = cantitate;
		this->numeProduse = new string[cantitate];
		for (int i = 0; i < cantitate; i++) {
			this->numeProduse[i] = numeProduse[i];
		}
	}

	Produse(const Produse& p) : Resurse(p), TVA(nrInventar++) {
		this->pret = p.pret;
		this->greutate = p.greutate;
		this->cantitate = p.cantitate;
		this->numeProduse = new string[p.cantitate];
		for (int i = 0; i < p.cantitate; i++) {
			this->numeProduse[i] = p.numeProduse[i];
		}
	}

	Produse operator=(const Produse& p) {
		if (this != &p) {
			Resurse::operator=(p);
			this->pret = p.pret;
			this->greutate = p.greutate;
			this->cantitate = p.cantitate;
			if (this->numeProduse != NULL) {
				delete[]this->numeProduse;
			}
			this->numeProduse = new string[p.cantitate];
			for (int i = 0; i < p.cantitate; i++) {
				this->numeProduse[i] = p.numeProduse[i];
			}
		}
		return *this;
	}

	Produse operator-(Produse p) {
		Produse aux = *this;
		aux.pret = this->pret - p.pret;
		aux.greutate = this->greutate - p.greutate;
		aux.cantitate = this->cantitate - p.cantitate;
		if (aux.numeProduse != NULL) {
			delete[]aux.numeProduse;
		}
		aux.numeProduse = new string[aux.cantitate];
		for (int i = 0; i < aux.cantitate; i++) {
			aux.numeProduse[i] = this->numeProduse[i];
		}
		return aux;
	}

	bool operator>=(Produse p) {
		return this->pret >= p.pret;
	}

	friend ostream& operator<<(ostream& op, const Produse& p) {
		op << "Produsele au un pret de " << p.pret << " lei, au o greutate de " << p.greutate << " kg, se afla intr-o cantitate de " << p.cantitate << " si au denumirile de: ";
		if (p.cantitate > 0) {
			for (int i = 0; i < p.cantitate; i++) {
				op << p.numeProduse[i] << ", ";
			}
		}
		else {
			op << "nu exista produse.";
		}
		op << endl;
		return op;
	}

	friend istream& operator>>(istream& is, Produse& p) {
		cout << "Pretul produsului: ";
		is >> p.pret;
		cout << "Greutatea produsului: ";
		is >> p.greutate;
		cout << "Cantitate: ";
		is >> p.cantitate;
		cout << "Nume produs: ";
		if (p.numeProduse != NULL) {
			delete[]p.numeProduse;
		}
		p.numeProduse = new string[p.cantitate];
		for (int i = 0; i < p.cantitate; i++) {
			is >> p.numeProduse[i];
		}
		return is;
	}

	~Produse() {
		if (this->numeProduse != NULL) {
			delete[]this->numeProduse;
		}
	}

	void afisareProdus() {
		cout << "Produsele au un pret de " << pret << " lei, au o greutate de " << greutate << " kg, se afla intr-o cantitate de " << cantitate << " si au denumirile de: ";
		if (cantitate > 0) {
			for (int i = 0; i < cantitate; i++) {
				cout << numeProduse[i] << ", ";
			}
		}
		else {
			cout << "nu exista produse.";
		}
		cout << endl;
	}

	void adaugareProdus(string numeProdus) {
		string* aux = new string[this->cantitate + 1];
		for (int i = 0; i < this->cantitate; i++) {
			aux[i] = this->numeProduse[i];
		}
		aux[this->cantitate] = numeProdus;
		this->cantitate++;
		if (this->numeProduse) {
			delete[]this->numeProduse;
		}
		this->numeProduse = aux;
	}

	int getTVA() {
		return TVA;
	}
	void setProduse(int cantitate, string* numeProduse) {
		if (cantitate > 0) {
			this->cantitate = cantitate;
			if (this->numeProduse != NULL) {
				delete[]this->numeProduse;
			}
			this->numeProduse = new string[cantitate];
			for (int i = 0; i < cantitate; i++) {
				this->numeProduse[i] = numeProduse[i];
			}
		}
	}

	int getPret() {
		return pret;
	}
	void setPret(int pret) {
		if (pret > 0) {
			this->pret = pret;
		}
	}

	float getGreutate() {
		return greutate;
	}
	void setGreutate(float greutate) {
		if (greutate > 0) {
			this->greutate = greutate;
		}
	}

	int getCantitate() {
		return cantitate;
	}
	void setCantitate(int cantitate) {
		if (cantitate > 0) {
			this->cantitate = cantitate;
		}
	}

	string* getNumeProduse() {
		return numeProduse;
	}
	string getNumeProdus(int i) {
		if (i >= 0 && i < cantitate) {
			return numeProduse[i];
		}
	}


};
int Produse::nrInventar = 300;

class Inventar {
private:
	Produse cantitate;
	string denumire;
	string dataInventariere;
public:
	Inventar() {
		this->denumire = "Tricouri";
		this->dataInventariere = "22 Noiembrie";
	}
	Inventar(string denumire, string dataInventariere, Produse& p) {
		this->denumire = denumire;
		this->dataInventariere = dataInventariere;
		this->cantitate = p;
	}
	Inventar(Produse& p) {
		this->denumire = "Pantaloni";
		this->dataInventariere = "23 Noiembrie";
		this->cantitate = p;
	}
	void afisareInventar() {
		cout << "Inventarul pentru produsele de tip: " << denumire << endl << "Data la care a fost facut inventarul: " << dataInventariere << endl;
		cantitate.afisareProdus();
	}
	string getDenumire() {
		return denumire;
	}
	void setDenumire(string denumire) {
		this->denumire = denumire;
	}
	string getDataInventariere() {
		return dataInventariere;
	}
	void setDataInventariere() {
		this->dataInventariere = dataInventariere;
	}
	int getCantitateProdus() {
		cout << "La data de: " << dataInventariere << ", produsele de tip: " << denumire << " au fost trecute in inventar intr-o cantitate de: ";
		return cantitate.getCantitate();
	}
	void setCantitateProdus(Produse& cantitate) {
		this->cantitate = cantitate;
	}
	Inventar operator=(const Inventar& in) {
		this->denumire = in.denumire;
		this->dataInventariere = in.dataInventariere;
		this->cantitate = in.cantitate;
		return *this;
	}
	friend ostream& operator<<(ostream& afis, const Inventar& inv) {
		afis << "Denumire produs: " << inv.denumire << endl;
		afis << "Data inventariere: " << inv.dataInventariere << endl;
		afis << "Cate produse se afla in inventar: " << inv.cantitate << endl;
		return afis;
	}
	friend istream& operator>>(istream& citire, Inventar& i) {
		cout << "Denumire: ";
		citire >> i.denumire;
		cout << "Data inventariere: ";
		citire >> i.dataInventariere;
		cout << "Cantitate: ";
		citire >> i.cantitate;
		return citire;
	}
};

class MagazinOnline : public Magazine, public MediiComerciale {
private:
	int vizitatoriZilnici;
	char* numeWebsite;
public:

	void DescrieMediuComercial() {
		cout << "Magazinul are un numar de " << vizitatoriZilnici << " vizitatori zilnici." << endl;
	}

	MagazinOnline() : MediiComerciale(), Magazine("Nike", 40.2) {
		this->vizitatoriZilnici = 150;
		this->numeWebsite = new char[strlen("Nike.com") + 1];
		strcpy_s(this->numeWebsite, strlen("Nike.com") + 1, "Nike.com");
	}

	MagazinOnline(int vizitatoriZilnici, const char* numeWebsite) : MediiComerciale(), Magazine() {
		this->vizitatoriZilnici = vizitatoriZilnici;
		this->numeWebsite = new char[strlen(numeWebsite) + 1];
		strcpy_s(this->numeWebsite, strlen(numeWebsite) + 1, numeWebsite);
	}

	MagazinOnline(int vizitatoriZilnici, const char* numeWebsite, string numeFirma, float suprafata, int nrArticole, string* numeArticole) : MediiComerciale(), Magazine(numeFirma, suprafata, nrArticole, numeArticole) {
		this->vizitatoriZilnici = vizitatoriZilnici;
		this->numeWebsite = new char[strlen(numeWebsite) + 1];
		strcpy_s(this->numeWebsite, strlen(numeWebsite) + 1, numeWebsite);
	}

	MagazinOnline(const MagazinOnline& mg) : MediiComerciale(), Magazine(mg) {
		this->vizitatoriZilnici = mg.vizitatoriZilnici;
		this->numeWebsite = new char[strlen(mg.numeWebsite) + 1];
		strcpy_s(this->numeWebsite, strlen(mg.numeWebsite) + 1, mg.numeWebsite);
	}

	MagazinOnline operator=(const MagazinOnline& mg) {
		if (this != &mg) {
			(Magazine)*this = (Magazine)mg;
			this->vizitatoriZilnici = mg.vizitatoriZilnici;
			if (this->numeWebsite != NULL) {
				delete[]this->numeWebsite;
			}
			this->numeWebsite = new char[strlen(mg.numeWebsite) + 1];
			strcpy_s(this->numeWebsite, strlen(mg.numeWebsite) + 1, mg.numeWebsite);
		}
		return *this;
	}

	~MagazinOnline() {
		if (this->numeWebsite != NULL) {
			delete[]this->numeWebsite;
		}
	}

	int getVizitatoriZilnici() {
		return this->vizitatoriZilnici;
	}
	void setVizitatoriZilnici(int vizitatoriZilnici) {
		if (this->vizitatoriZilnici > 0) {
			this->vizitatoriZilnici = vizitatoriZilnici;
		}
	}

	char* getNumeWebsite() {
		return numeWebsite;
	}
	void setNumeWebsite(const char* numeWebsite) {
		if (strlen(numeWebsite) > 0) {
			if (this->numeWebsite != NULL) {
				delete[]this->numeWebsite;
			}
			this->numeWebsite = new char[strlen(numeWebsite) + 1];
			strcpy_s(this->numeWebsite, strlen(numeWebsite) + 1, numeWebsite);
		}
	}

	friend ostream& operator<<(ostream& ecran, const MagazinOnline& m) {
		ecran << (Magazine)m;
		ecran << m.vizitatoriZilnici << ", " << m.numeWebsite << endl;
		return ecran;
	}

	friend istream& operator>>(istream& cit, MagazinOnline& m) {
		cit >> (Magazine&)m;
		cout << "Numar vizitatori zilnici: ";
		cit >> m.vizitatoriZilnici;
		if (m.numeWebsite != NULL) {
			delete[]m.numeWebsite;
		}
		char aux1[50];
		cout << "Numele website-ului: ";
		cit >> aux1;
		m.numeWebsite = new char[strlen(aux1) + 1];
		strcpy_s(m.numeWebsite, strlen(aux1) + 1, aux1);
		return cit;
	}
}; 

class AngajatiFullTime : public Angajati, public Resurse {
private:
	bool asigurareMedicala;
	int nrOreSaptamanal;
	char* titluPozitie;
public:

	void DescrieResursa() {
		cout << "Angajatii au lucrat in aceasta saptamana " << nrOreSaptamanal << " ore." << endl;
	}

	AngajatiFullTime() : Resurse(), Angajati("camasa", 5000) {
		this->asigurareMedicala = true;
		this->nrOreSaptamanal = 40;
		this->titluPozitie = new char[strlen("Manager") + 1];
		strcpy_s(this->titluPozitie, strlen("Manager") + 1, "Manager");
	}


	AngajatiFullTime(bool asigurareMedicala, int nrOreSaptamanal, const char* titluPozitie) : Resurse(), Angajati() {
		this->asigurareMedicala = asigurareMedicala;
		this->nrOreSaptamanal = nrOreSaptamanal;
		this->titluPozitie = new char[strlen(titluPozitie) + 1];
		strcpy_s(this->titluPozitie, strlen(titluPozitie) + 1, titluPozitie);
	}

	AngajatiFullTime(bool asigurareMedicala, int nrOreSaptamanal, const char* titluPozitie, string uniforma, float salariu, int nrAngajati, string* numeAngajati) : Resurse(), Angajati(uniforma, salariu, nrAngajati, numeAngajati) {
		this->asigurareMedicala = asigurareMedicala;
		this->nrOreSaptamanal = nrOreSaptamanal;
		this->titluPozitie = new char[strlen(titluPozitie) + 1];
		strcpy_s(this->titluPozitie, strlen(titluPozitie) + 1, titluPozitie);
	}

	AngajatiFullTime(const AngajatiFullTime& ang) : Resurse(), Angajati(ang) {
		this->asigurareMedicala = ang.asigurareMedicala;
		this->nrOreSaptamanal = ang.nrOreSaptamanal;
		this->titluPozitie = new char[strlen(ang.titluPozitie) + 1];
		strcpy_s(this->titluPozitie, strlen(ang.titluPozitie) + 1, ang.titluPozitie);
	}

	AngajatiFullTime operator=(const AngajatiFullTime& ang) {
		if (this != &ang) {
			(Angajati)*this = (Angajati)ang;
			this->asigurareMedicala = ang.asigurareMedicala;
			this->nrOreSaptamanal = ang.nrOreSaptamanal;
			if (this->titluPozitie != NULL) {
				delete[]this->titluPozitie;
			}
			this->titluPozitie = new char[strlen(ang.titluPozitie) + 1];
			strcpy_s(this->titluPozitie, strlen(ang.titluPozitie) + 1, ang.titluPozitie);
		}
		return *this;
	}

	~AngajatiFullTime() {
		if (this->titluPozitie != NULL) {
			delete[]this->titluPozitie;
		}
	}

	bool getAsigurareMedicala() {
		return this->asigurareMedicala;
	}
	void setAsigurareMedicala(bool asigurareMedicala) {
		this->asigurareMedicala = asigurareMedicala;
	}

	int getNrOreSaptamanal() {
		return this->nrOreSaptamanal;
	}
	void setNrOreSaptamanal(int nrOreSaptamanal) {
		if (this->nrOreSaptamanal > 0) {
			this->nrOreSaptamanal = nrOreSaptamanal;
		}
	}

	char* getTitluPozitie() {
		return titluPozitie;
	}
	void setTitluPozitie(const char* titluPozitie) {
		if (strlen(titluPozitie) > 0) {
			if (this->titluPozitie != NULL) {
				delete[]this->titluPozitie;
			}
			this->titluPozitie = new char[strlen(titluPozitie) + 1];
			strcpy_s(this->titluPozitie, strlen(titluPozitie) + 1, titluPozitie);
		}
	}

	friend ostream& operator<<(ostream& ecran, const AngajatiFullTime& a) {
		ecran << (Angajati)a;
		ecran << a.asigurareMedicala << ", " << a.nrOreSaptamanal << ", " << a.titluPozitie << endl;
		return ecran;
	}

	friend istream& operator>>(istream& citire, AngajatiFullTime& a) {
		citire >> (Angajati&)a;
		cout << "Are asigurare medicala? : ";
		citire >> a.asigurareMedicala;
		cout << "Numar ore lucrate saptamanal: ";
		citire >> a.nrOreSaptamanal;
		if (a.titluPozitie != NULL) {
			delete[]a.titluPozitie;
		}
		char aux[30];
		cout << "Titlul pozitiei ocupate de angajat: ";
		citire >> aux;
		a.titluPozitie = new char[strlen(aux) + 1];
		strcpy_s(a.titluPozitie, strlen(aux) + 1, aux);
		return citire;
	}
};

class ObiecteResurse {
private:
	int nrObiecte;
	Resurse** r;
public:
	ObiecteResurse() {
		this->nrObiecte = 10;
		this->r = new Resurse * [10];
		for (int i = 0; i < 10; i++) {
			this->r[i] = new Angajati;
		}
	}
	Resurse*& operator[](int i) {
		if (i >= 0 && i < this->nrObiecte) {
			return this->r[i];
		}
	}
};

void main() {
	//Magazine magazin1;
	//magazin1.afisareMagazine();

	//string* numeArticole = new string[3];
	//numeArticole[0] = "tricouri";
	//numeArticole[1] = "pantaloni";
	//numeArticole[2] = "veste";

	//Magazine magazin2("Nike", 30);
	//magazin2.afisareMagazine();
	//magazin2.adaugareArticol("geci");
	//magazin2.afisareMagazine();

	//Magazine magazin3("Adidas", 35, 3, numeArticole);
	//magazin3.afisareMagazine();

	///*cout << magazin2.getNrInventar() << endl;*/
	//cout << Magazine::getNrInventar() << endl;
	//Magazine m1 = magazin2;
	//Magazine m2(magazin2);
	//magazin2.afisareMagazine();
	//m1 = magazin2;
	//m1.afisareMagazine();
	//cout << m1.getNrTotalMagazine() << endl;
	//cout << m1.getNumeFirma() << endl;
	//m1.setNumeFirma("Puma");
	//cout << m1.getNumeFirma() << endl;
	//cout << m1.getSuprafata() << endl;
	//m1.setSuprafata(40);
	//cout << m1.getSuprafata() << endl;
	//cout << m1.getNrArticole() << endl;
	//m1.setNrArticole(7);
	//cout << m1.getNrArticole() << endl;

	//string* vector = new string[2]{ "sepci","palarii" };
	//m1.setArticole(2, vector);
	//cout << m1;
	//cout << *m1.getNumeArticole()<< endl;
	///*cout << m1.getNumeArticole() << endl;*/
	//cout << m1.getNumeArticol(1) << endl;
	//delete[]vector;
	//cout << getArticole(m1);
	//cout << endl;
	//
	//Magazine magazin4;
	//magazin4 += magazin2;
	//magazin4.afisareMagazine();
	//if (magazin3 != magazin4) {
	//	cout << "Cele 2 magazine sunt diferite.";
	//}
	//else cout << "Cele 2 magazine sunt identice.";
	//cout << endl;
	//magazin1.afisareMagazine();
	//magazin1[0] = "palarii";
	//magazin1.afisareMagazine();

	/*Magazine m5;
	Magazine m6("Sephora", 38);
	cin >> m5;
	ofstream afisare("magazine.txt", ios::out);
	afisare << m5;
	afisare.close();
	ifstream citire("magazine.txt", ios::in);
	citire >> m6;
	cout << m6;
	citire.close();

	string* v = new string[2];
	v[0] = "tricouri";
	v[1] = "adidasi";
	Magazine m7("Nike", 26.8, 2, v);
	fstream f("magazin.bin", ios::out | ios::binary);
	m7.scrieInFisierBinar(f);
	f.close();*/

	//Angajati angajat1;
	//angajat1.afisareAngajati();

	//Angajati angajat2("camasa", 2800);
	//angajat2.afisareAngajati();
	//angajat2.adaugareAngajat("Ioana");
	//angajat2.afisareAngajati();

	//string* numeAngajati = new string[3];
	//numeAngajati[0] = "Alex";
	//numeAngajati[1] = "Andrei";
	//numeAngajati[2] = "Maria";

	//Angajati angajat3("camasa", 3000, 3, numeAngajati);
	//angajat3.afisareAngajati();

	//cout << Angajati::getIdAngajat() << endl; 
	//Angajati a1 = angajat2;
	//Angajati a2(angajat2);
	//angajat2.afisareAngajati();
	//cout << a1.getNrMaximZileConcediu() << endl;
	//cout << a1.getUniforma() << endl;
	//a1.setUniforma("costum");
	//cout << a1.getUniforma() << endl;
	//cout << a1.getSalariu() << endl;
	//a1.setSalariu(4000);
	//cout << a1.getSalariu() << endl;
	//cout << a1.getNrAngajati() << endl;
	//a1.setNrAngajati(2);
	//cout << a1.getNrAngajati() << endl;

	//string* vector1= new string[2]{ "Ana", "Raluca" };
	//a1.setAngajati(2, vector1);
	//a1.afisareAngajati();
	//cout << *a1.getNumeAngajati() << endl;
	//cout << a1.getNumeAngajati() << endl; 
	//cout << a1.getNumeAngajat(1) << endl;
	//delete[]vector1;
	//cout << getSirAngajati(a1);
	//cout << endl;
	//cout << a1;
	//Angajati a4;
	//a4 = a1 + angajat3;
	//cout << a4;
	//Angajati a5;
	//a5 = a1 + 1500;
	//cout << a5;
	//if (a1 > a5) {
	//	cout << "Angajatii din magazinul 1 au un salariu mai mare/sunt mai numerosi.";
	//}
	//else cout << "Angajatii din magazinul 5 au un salariu mai mare/sunt mai numerosi.";
	//cout << endl;

	/*Angajati a6;
	Angajati a7("camasa", 3100);
	cin >> a6;
	ofstream afisare1("angajati.txt", ios::out);
	afisare1 << a6;
	afisare1.close();
	ifstream citire1("angajati.txt", ios::in);
	citire1 >> a7;
	cout << a7;
	citire1.close();

	string* v2 = new string[3];
	v2[0] = "Andreea";
	v2[1] = "Ioana";
	v2[2] = "Bianca";
	Angajati a8("Nike", 26.8, 2, v2);
	fstream fisBin("angajat.bin", ios::out | ios::binary);
	a8.scrieInFisierBinar(fisBin);
	fisBin.close();*/

	//Produse produs1;
	//produs1.afisareProdus();

	//Produse produs2(120, 1);
	//produs2.afisareProdus();
	//produs2.adaugareProdus("pantaloni");
	//produs2.afisareProdus();

	//string* numeProduse = new string[3];
	//numeProduse[0] = "geaca";
	//numeProduse[1] = "blugi";
	//numeProduse[2] = "adidasi";

	//Produse produs3(150, 3, 3, numeProduse);
	//produs3.afisareProdus();

	//cout << Produse::getNrInventar() << endl;
	//Produse p1 = produs2;
	//Produse p2(produs2);
	//produs2.afisareProdus();
	//cout << p1.getTVA() << endl;
	//cout << p1.getPret() << endl;
	//p1.setPret(250);
	//cout << p1.getPret() << endl;
	//cout << p1.getGreutate() << endl;
	//p1.setGreutate(5);
	//cout << p1.getGreutate() << endl;
	//cout << p1.getCantitate() << endl;
	//p1.setCantitate(4);
	//cout << p1.getCantitate() << endl;

	//string* vector2 = new string[4] {"adidasi", "palarii", "sacouri", "tricouri"};
	//p1.setProduse(4, vector2);
	//p1.afisareProdus();
	//cout << *p1.getNumeProduse() << endl;
	////cout << p1.getNumeProduse() << endl;
	//cout << p1.getNumeProdus(1) << endl;
	//delete[]vector2;
	//cin >> produs1;
	//produs1.afisareProdus();
	//if (p1 >= produs3) {
	//	cout << "Produsele sunt mai scumpe.";
	//	}
	//else cout << "Produsele sunt mai ieftine.";
	//cout << endl;
	//Produse p3;
	//p3 = p1 - produs3;
	//p3.afisareProdus();

	///*const int numarProduse_P = 2;
	//std::vector<Produse>vectorProduse(numarProduse_P);


	//for (int i = 0; i < numarProduse_P; ++i) {
	//	cout << "Introduceti datele pentru obiectul Produs la pozitia " << i << ":\n";
	//	cin >> vectorProduse[i];
	//}
	//cout << endl << endl;
	//for (int i = 0; i < numarProduse_P; ++i) {
	//	cout << "Afisare obiect Produs la pozitia " << i << ":\n";
	//	cout << vectorProduse[i];
	//}

	//const int numar_linii = 2;
	//const int numar_coloane = 2;

	//Produse matriceProduse[numar_linii][numar_coloane];
	//for (int i = 0; i < numar_linii; ++i) {
	//	for (int j = 0; j < numar_coloane; ++j) {
	//		cout<<"Introduceti datele pentru obiectul Produs la pozitia ["<<i<<"]["<<j<<"]:\n";
	//		cin >> matriceProduse[i][j];
	//		cout << endl;
	//	}
	//}

	//for (int i = 0; i < numar_linii; ++i) {
	//	for (int j = 0; j < numar_coloane; ++j) {
	//		cout << "Afisare obiect Produs la pozitia [" << i << "][" << j << "]:\n";
	//		cout << matriceProduse[i][j];
	//	}
	//}*/

	//Inventar inventar1("Adidasi", "31 Octombrie", p1);
	//Inventar inventar2(produs3);
	//Inventar i3;
	//Inventar i4(p2);
	//i3 = inventar1;
	//inventar1.afisareInventar();
	//inventar2.getDenumire();
	//cout << inventar1.getCantitateProdus() << endl;
	//inventar1.afisareInventar();
	//inventar2.afisareInventar();
	//cout << endl;
	//cout << i3;
	//cin >> i4;
	//cout << i4;

	/*MagazinOnline mag1;
	MagazinOnline mag2(200, "Zara.com");
	MagazinOnline mag3 = mag1;
	MagazinOnline mag4;
	mag4 = mag1;
	cout << mag4;
	cin >> mag1;
	cout << mag1;
	MagazinOnline mag5;
	cout << mag5.getVizitatoriZilnici() << endl;
	mag5.setVizitatoriZilnici(250);
	cout << mag5.getVizitatoriZilnici() << endl;
	cout << mag5.getNumeWebsite() << endl;
	mag5.setNumeWebsite("Puma.com");
	cout << mag5.getNumeWebsite() << endl;*/

	//AngajatiFullTime ang1;
	//AngajatiFullTime ang2(true, 40, "Manager");
	//AngajatiFullTime ang3 = ang1;
	//AngajatiFullTime ang4;
	//ang4 = ang1;
	//cout << ang4;
	//cin >> ang1;
	//cout << ang1<<endl;
	//AngajatiFullTime ang5;
	//cout<<ang5.getAsigurareMedicala() << endl;
	//ang5.setAsigurareMedicala(0);
	//cout << ang5.getAsigurareMedicala() << endl;
	//cout << ang5.getNrOreSaptamanal() << endl;
	//ang5.setNrOreSaptamanal(35);
	//cout << ang5.getNrOreSaptamanal() << endl;
	//cout << ang5.getTitluPozitie() << endl;
	//ang5.setTitluPozitie("Asistent");
	//cout << ang5.getTitluPozitie() << endl;

	ObiecteResurse o;
	o[0] = new Angajati;
	o[1] = new Produse;
	o[2] = new AngajatiFullTime;
	o[3] = new Angajati;
	o[4] = new AngajatiFullTime;
	o[5] = new Produse;
	o[6] = new Produse;
	o[7] = new AngajatiFullTime;
	o[8] = new Angajati;
	o[9] = new Angajati;

	for (int i = 0; i < 10; i++) {
		o[i]->DescrieResursa();
		cout << endl;
	}
}