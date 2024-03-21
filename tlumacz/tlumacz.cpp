#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
//#include <funkcje.h>
using namespace std;

//DEFINIOWANIE STRUKTURY SLOWNIKA POL-ANG
struct plen {
	string pl;
	string en;
	struct plen* left = NULL;
	struct plen* right = NULL;
};

//DEFINIOWANIE WEZLA STRUKTURY SLOWNIKA POL-ANG
struct plen* node_plen(string key, string key2) {
	//WCZYTYWANIE STRUKTURY
	struct plen* root = new struct plen();
	//WCZYTYWANIE DANYCH
	root->pl = key;
	root->en = key2;
	//PRZESKOK
	root->left = root->right = NULL;
	//ZWRACANIE WARTOSCI
	return root;
}

//FUNKCJA DO WPROWADZANIA DANYCH DO STRUKTURY DRZEWA SLOWNIKA POL-ANG
struct plen* insert_plen(struct plen* root, string key, string key2) {
	//JEZELI DRZEWO JEST PUSTE DODAJE ELEMENT NA POCZATEK DRZEWA
	if (root == NULL) return node_plen(key,key2);
	//JEZELI ELEMENT JEST MNIEJSZY NIZ POPRZEDNI ELEMENT DODAJE GO NA LEWA STRONE
	if (key < root->pl) {
		root->left = insert_plen(root->left, key, key2);
	}
	//JEZELI JEST WIEKSZY NIZ POPRZEDNI ELEMETNT DODAJE GO NA PRAWA STRONE
	else {
		root->right = insert_plen(root->right, key, key2);
	}
	//ZWRACA WARTOSC WEZLA
	return root;
}

//SPRAWDZA, CZY DANE SLOWO ISTNIEJE W DRZEWIE
bool checkword_plen(struct plen* root, string key) {
	//PETLA, KTORA ZATRZYMUJE SIE, JEZELI NATRAFIMY NA KONIEC LISTY
	while (root != NULL) {
		//JEZELI ISTNIEJE FUNKCJA ZWRACA WARTOSC TRUE I KONCZY DZIALANIE
		if (root->pl == key) return true;
		//JEZELI NIE MA ELEMENTU, SZUKA GO DALEJ
		if (root->pl > key) root = root->left;
		else root = root->right;
	}
	//DOMYSLNIE ZWRACA FALSE, JEZELI WCZESNIEJ NIC NIE ZWROCONO
	return false;
}

//FUNKCJA, KTORA PODMIENIA POJEDYNCZE SLOWO NA JEGO ODPOWIEDNIK W INNYM JEZYKU
string translate_plen(struct plen* root, string key) {
	string output = "";
	//PETLA, KTORA ZATRZYMUJE SIE, JEZELI NATRAFIMY NA KONIEC LISTY
	while (root != NULL) {
		//JEZELI ZNAJDZIE SLOWO, TO ZWRACA SLOWO ANGIELSKIE
		if (root->pl == key) output = root->en;
		//JEZELI WARTOSC KOLEJNA JEST WIEKSZA, TO IDZIE W LEWO
		if (root->pl > key) root = root->left;
		//JEZELI JEST MNIEJSZA, IDZIE W PRAWO DRZEWA
		else root = root->right;
	}
	return output;
}

//DEFINIOWANIE STRUKTURY SLOWNIKA ANG-POL
struct enpl {
	string en;
	string pl;
	struct enpl* left = NULL;
	struct enpl* right = NULL;
};

//DEFINIOWANIE WEZLA STRUKTURY SLOWNIKA ANG-POL
struct enpl* node_enpl(string key, string key2) {
	//WCZYTYWANIE STRUKTURY
	struct enpl* root = new struct enpl();
	//WCZYTYWANIE DANYCH
	root->en = key;
	root->pl = key2;
	//PRZESKOK
	root->left = root->right = NULL;
	//ZWRACANIE WARTOSCI WEZLA
	return root;
}

//FUNKCJA DO WPROWADZANIA DANYCH DO STRUKTURY DRZEWA SLOWNIKA ANG-POL
struct enpl* insert_enpl(struct enpl* root, string key, string key2) {
	//JEZELI DRZEWO JEST PUSTE DODAJE ELEMENT NA POCZATEK DRZEWA
	if (root == NULL) return node_enpl(key, key2);
	//JEZELI ELEMENT JEST MNIEJSZY NIZ POPRZEDNI ELEMENT DODAJE GO NA LEWA STRONE
	if (key < root->en) {
		root->left = insert_enpl(root->left, key, key2);
	}
	//JEZELI JEST WIEKSZY NIZ POPRZEDNI ELEMETNT DODAJE GO NA PRAWA STRONE
	else {
		root->right = insert_enpl(root->right, key, key2);
	}
	//ZWRACA WARTOSC WEZLA
	return root;
}

//SPRAWDZA, CZY DANE SLOWO ISTNIEJE W DRZEWIE
bool checkword_enpl(struct enpl* root, string key) {
	//PETLA, KTORA ZATRZYMUJE SIE, JEZELI NATRAFIMY NA KONIEC LISTY
	while (root != NULL) {
		//JEZELI ISTNIEJE FUNKCJA ZWRACA WARTOSC TRUE I KONCZY DZIALANIE
		if (root->en == key) return true;
		//JEZELI NIE MA ELEMENTU, SZUKA GO DALEJ.
		if (root->en > key) root = root->left;
		else root = root->right;
	}
	//DOMYSLNIE ZWRACA FALSE, JEZELI WCZESNIEJ NIC NIE ZWROCONO
	return false;
}

//FUNKCJA, KTORA PODMIENIA POJEDYNCZE SLOWO NA JEGO ODPOWIEDNIK W INNYM JEZYKU
string translate_enpl(struct enpl* root, string key) {
	string output = "";
	//PETLA, KTORA ZATRZYMUJE SIE, JEZELI NATRAFIMY NA KONIEC LISTY
	while (root != NULL) {
		//JEZELI ZNAJDZIE SLOWO, TO ZWRACA SLOWO POLSKIE
		if (root->en == key) output = root->pl;
		//JEZELI WARTOSC KOLEJNA JEST WIEKSZA, TO IDZIE W LEWO
		if (root->en > key) root = root->left;
		//JEZELI JEST MNIEJSZA, IDZIE W PRAWO DRZEWA
		else root = root->right;
	}
	return output;
}

//FUNCKJA KTORA DZIELI ZDANIE NA SLOWA
//WYKORZYSTANA DO WYDOBYCIA SLOW ZE SLOWNIKA
//			0 - PL
//			1 - EN
string getword(string words, int lang) {
	//definiowanie zmienych
	string word, output[2];
	stringstream iss(words);
	//DOMYSLNA ITERACJA
	int i = 0;
	//PETLA KTORA PRZYDIZELA SLOWA DO TABLICY
	while (iss >> word) {
		output[i] = word;
		i++;
	}
	//ZWRACA WARTOSC
	return output[lang];
}

int main(int argc, char* argv[]) {
	//zmienna slownika
	string s="";
	//zmienna wejscia
	string i="";
	//zmienna wyjscia
	string o="";
	//zmienna kierunku tlumaczenia
	string k = "enpl";
	//pomoc
	bool h = false;

	//sprawdzanie argumentow i przypisywanie ich do zmiennych
	for (int x = 1; x < argc; x++) {
		if (strcmp(argv[x], "-s") == 0) s = argv[x + 1];
		if (strcmp(argv[x], "-i") == 0) i = argv[x + 1];
		if (strcmp(argv[x], "-o") == 0) o = argv[x + 1];
		if (strcmp(argv[x], "-k") == 0) k = argv[x + 1];
		if (strcmp(argv[x], "-h") == 0) h = true;
	}
	//czynnosc wykonywania, jezeli wywolano h lub jezeli nie podano argumentow
	if (h == true || argc == 1) {
		cout
			<< "[PLIKI POMOCY]" << endl << "Uruchom program z poziomu linii polecen wprowadzajac dane w parametrach: " << endl
			<< "-s - plik slownika" << endl
			<< "-i - plik wejscia" << endl
			<< "-o - plik wyjscia" << endl
			<< "-k - kierunek tlumaczenia (plen|enpl)" << endl
			<< "np. tlumacz.exe -s s.txt -i i.txt -o o.txt -k plen";
		exit(0);
	}
	//weryfikacja, czy wprowadzano wymagane dane
	if(s.empty() == true) {
		cout << "Nie podano pliku slownika!";
		exit(6);
	}
	if (i.empty() == true) {
		cout << "Nie podano pliku wejscia!";
		exit(7);
	}
	if (o.empty() == true) {
		cout << "Nie podano pliku wyjscia!";
		exit(8);
	}
	if (k != "enpl" && k != "plen") {
		cout << "Podany kierunek tlumaczenia jest nieprawidlowy! (plen|enpl)";
		exit(9);
	}
	//...
	ofstream output;
	struct enpl* enpl = NULL;
	struct plen* plen = NULL;
	//OTWIERANIE PLIKU WYJSCIOWEGO o
	output.open(o);
	//CZYSZCZENIE PLIKU WYJSCIOWEGO o
	output.flush();
	//SPRAWDZA CZY PLIK SLOWNIKA JEST PLIKIEM WYJSCIOWYM
	//JEZELI TAK, ZWRACA WARTOSC 5 A DO PLIKU OUTPUT WPISUJE KOMUNIKAT BLEDU
	if (s == o) {
		output << "{BLAD 3: PLIK WYJSCIOWY NIE MOZE BYC PLIKIEM SLOWNIKA}";
		cout << "BLAD 3: PLIK WYJSCIOWY NIE MOZE BYC PLIKIEM SLOWNIKA";
		exit(5);
	}
	//SPRAWDZA CZY PLIK WEJSCIOWY JEST PLIKIEM WYJSCIOWYM
	//JEZELI TAK, ZWRACA WARTOSC 6 A DO PLIKU OUTPUT WPISUJE KOMUNIKAT BLEDU
	if (i == o) {
		output << "{BLAD 4: PLIK WEJSCIOWY NIE MOZE BYC PLIKIEM WYJSCIOWYM}";
		cout << "BLAD 4: PLIK WEJSCIOWY NIE MOZE BYC PLIKIEM WYJSCIOWYM";
		exit(6);
	}

	//DEFINIOWANIE ZMIENNEJ PLIKU SLOWNIKA
	ifstream file_dict(s);
	//SPRAWDZA, CZY MOZLIWE BYLO OTOWRZENIE PLIKU SLOWNIKA
	if (file_dict.is_open()) {
		//DEFINIOWANIE ZMIENNEJ PLIKU WEJSCIA
		ifstream file_input(i);
		//SPRAWDZA CZY MOZLIWE BYLO OTWORZENIE PLIKU WEJSCIA
		if (file_input.is_open()) {
			//DEFINIOWANIE ZMIENNYCH
			string inp_dict, str_dict, inp_input, str_input, temp = "";
			//WCZYTUJEMY LINIJKA PO LINIJCE ZAWARTOSC SLOWNIKA
			while (getline(file_dict, inp_dict)) {
				//SPRAWDZAMY, JAKI KIERUNEK TLUMACZENIA WYBRANO
				if (k == "enpl") {
					//WPROWADZANIE DANYCH DO SLOWNIKA ANG-POL
					enpl = insert_enpl(enpl, getword(inp_dict, 1), getword(inp_dict, 0));
				}
				else {
					//WPROWADZANIE DANYCH DO SLOWNIKA POL-ANG
					plen = insert_plen(plen, getword(inp_dict, 0), getword(inp_dict, 1));
				}
			}
			//CZYSZCZENIE ZMIENNYCH
			inp_dict.clear();
			str_dict.clear();
			//ZAMYKANIE PLIKU SLOWNIKA
			file_dict.close();
			//WCZYTUJEMY DANE Z PLIKU WEJSCIA LINIJKA PO LINIJCE
			while (getline(file_input, inp_input)) {
				//DEFINIOWANIE ZMIENNYCH
				string word;
				stringstream oneword(inp_input);
				//DZIELENIE SLOWA NA WYRAZY
				while (oneword >> word) {
					//WCZYTUJEMY OSTATNI ZNAK SLOWA
					string lastchar = word.substr(word.length() - 1, word.length() - 1);
					//JEZELI ZNAK NIE JEST TO . , ? ! TO NULLUJEMY ZMIENNA
					if (lastchar != "." && lastchar != "," && lastchar != "?" && lastchar != "!") lastchar = "";
					//JEZELI JEST, TO SKRACAMY SLOWO O OSTATNI ZNAK
					else word = word.substr(0, word.length() - 1);

					//SPRAWDZAMY KIERUNEK TLUMACZENIA
					if (k == "enpl") {
						//SPRAWDZANIE, CZY SLOWO ISTNIEJE W SLOWNIKU
						if (checkword_enpl(enpl, word) == true) {
							//JEZELI TAK, TO DODAJEMY TLUMACZENIE TEGO SLOWA DO temp, DODAJAC OSTATNI ZNAK TEGO SLOWA
							temp = temp + translate_enpl(enpl, word) + lastchar + " ";
						}
						//JEZELI NIE ISTNIEJE, TO ZWRACAMY SLOWO W KWADRATACH, DODAJAC OSTATNI ZNAK
						else {
							temp = temp + "[" + word + "]" + lastchar + " ";
						}
					}
					else {
						//SPRAWDZANIE, CZY SLOWO ISTNIEJE W SLOWNIKU
						if (checkword_plen(plen, word) == true) {
							//JEZELI TAK, TO DODAJEMY TLUMACZENIE TEGO SLOWA DO temp, DODAJAC OSTATNI ZNAK TEGO SLOWA
							temp = temp + translate_plen(plen, word) + lastchar + " ";
						}
						//JEZELI NIE ISTNIEJE, TO ZWRACAMY SLOWO W KWADRATACH, DODAJAC OSTATNI ZNAK
						else {
							temp = temp + "[" + word + "]" + lastchar + " ";
						}
					}
				}
			}
			//USUWAMY ZBEDNA SPACJE NA KONCU ZDANIA
			temp = temp.substr(0, temp.length() - 1);
			//ZAPISUJEMY temp DO PLIKU
			output << temp;
			//CZYSCIMY temp I INNE ZMIENNE
			temp.clear();
			inp_input.clear();
			str_input.clear();
			//ZAMYKAMY PLIK WEJSCIA
			file_input.close();
		}
		//JEZELI NIE MOZNA BYLO OTWORZYC PLIKU WEJSCIOWEGO DODAJE KOMUNIKAT DO OUTPUT, KONCZY PROGRAM Z WARTOSCIA 4
		else {
			output << "{BLAD 2: PROGRAM NIE MOGL OTWORZYC PLIKU WEJSCIOWEGO}";
			cout << "BLAD 2: PROGRAM NIE MOGL OTWORZYC PLIKU WEJSCIOWEGO";
			exit(4);
		}
	}
	//JEZELI NIE MOZNA BYLO OTWORZYC PLIKU SLOWNIKA DODAJE KOMUNIKAT DO OUTPUT, KONCZY PROGRAM Z WARTOSCIA 2
	else {
		output << "{BLAD 1: PROGRAM NIE MOGL OTWORZYC PLIKU SLOWNIKA}";
		cout << "BLAD 1: PROGRAM NIE MOGL OTWORZYC PLIKU SLOWNIKA";
		exit(2);
	}
	//ZAMYKANIE PLIKU WYJSCIA
	output.close();
	//ZWRACANIE KOMUNIKATU O ZAKONCZONYM DZIALANIU PROGRAMU
	cout << "Program przetlumaczyl podany tekst.";
	//ZWRACANIE WARTOSCI 0
	return 0;
}