// GRA W WOJNE
// przetasowana talia rozstaje rozdzielona między dwóch graczy
// bitwa/runda polega na jednoczesnym wyłożeniu przez obu graczy po jednej karcie z wierzchu swojej talii 
// gracz który wyłozy karte o wiekszej wartości wygrywa
// po wygraniu gracz zabiera wszystkie wyłożone karty i umiescza je z tyłu swojej talii
// wygrywa osoba która pozbawi kart drugiego przeciwnika
// w przypadku wyłożeniu przez graczy kart o jednakowej wartości, rozpoczyna się wojna
// w przypadku wojny gracze wykładają po dwie karty, pierwsze odsloniete, nie biorące udziału w bitwie oraz drugie, bitewne
// między graczami zawiązuje się ponownie bitwa, teraz między wyłożonymi ostatnio kartami bitewnymi
// jeżeli wyłożone w wojnie karty bitewne również są sobie równe, dokłada się do nich kolejne karty na tych samych zasadach
// po wygraniu wojny gracz umieszcza w swojej talii wszystkie karty wyłożone przez obu graczy (wliczając te odsłoniete)
// jeżeli wojna wywiąże się a jeden z graczy posiada mniej kart niż potrzeba do prowadzenia gry, zostaje z miejsca ich pozbawiony i przegrywa

#include "pch.h" // biblioteka startowa w najnowszej wersji visuala
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

struct karta
{
	string figura;
	string kolor;
	int wartosc;
	int il_w; // parametr uzywany w karcie pomocniczej do określenia ilości wojen w danej turze
	int pkt_g = 26; // parametr uzywany w karcie pomocniczej do przypisywania nastepnym kolejkom gracza wygranych kart
	int pkt_k = 26; // parametr uzywany w karcie pomocniczej do przypisywania nastepnym kolejkom komputera wygranych kart
};

karta talia[52], talia_przetasowana[52], gracz[10000], komputer[10000], pomocnicza;
int wsk_k_k = 26, wsk_k_g = 26, i = 0; // wskaznik ilosci kart w talii gracza i komputera oraz wskaznik kolejki kart

karta generatortalii()
{
	for (int i = 0; i < 9; i++)
	{
		talia[i].figura = to_string(i + 2);
		talia[i + 9].figura = to_string(i + 2);
		talia[i + 18].figura = to_string(i + 2);
		talia[i + 27].figura = to_string(i + 2);
		talia[i + 31].figura = "walet";
		talia[i + 35].figura = "dama";
		talia[i + 39].figura = "krol";
		talia[i + 43].figura = "as";

		talia[i].wartosc = i;
		talia[i + 9].wartosc = i;
		talia[i + 18].wartosc = i;
		talia[i + 27].wartosc = i;
		talia[i + 31].wartosc = 9;
		talia[i + 35].wartosc = 10;
		talia[i + 39].wartosc = 11;
		talia[i + 43].wartosc = 12;
	}
	for (int i = 0; i < 13; i++)
	{
		talia[i * 4].kolor = "pik";
		talia[(i * 4) + 1].kolor = "kier";
		talia[(i * 4) + 2].kolor = "trefl";
		talia[(i * 4) + 3].kolor = "karo";
	}
	return (talia[52]);
}

int sprawdz_tasowanie(int iLiczba, int tab[], int ile)
{
	if (ile == 0)
		return false;
	int i = 0;
	do
	{
		if (tab[i] == iLiczba)
			return true;

		i++;
	} while (i < ile);
	return false;
}

karta tasowanie()
{
	srand(time(NULL));
	int dolosowania[52];
	int wylosowanych = 0;
	do
	{
		int liczba = rand() % 52 + 0;
		if (sprawdz_tasowanie(liczba, dolosowania, wylosowanych) == false)
		{
			dolosowania[wylosowanych] = liczba;
			wylosowanych++;
		}
	} while (wylosowanych < 52);
	for (int i = 0; i < 52; i++)
	{
		talia_przetasowana[i] = talia[dolosowania[i]];
	}
	return (talia_przetasowana[52]);
}

karta rozdzielenie_kart()
{
	for (int i = 0; i < 26; i++)
	{
		gracz[i].kolor = talia_przetasowana[i].kolor;
		gracz[i].figura = talia_przetasowana[i].figura;
		gracz[i].wartosc = talia_przetasowana[i].wartosc;
	}
	for (int i = 26; i < 52; i++)
	{
		komputer[i - 26].kolor = talia_przetasowana[i].kolor;
		komputer[i - 26].figura = talia_przetasowana[i].figura;
		komputer[i - 26].wartosc = talia_przetasowana[i].wartosc;
	}
	return (komputer[52], gracz[52]);
}

int wojna2()
{
	if (gracz[i].wartosc == komputer[i].wartosc)
	{
		cout << "WOJNA." << endl;
		cin.get();
		cout << endl << "Twoja odslonieta karta to: " << gracz[i + 1].figura << " " << gracz[i + 1].kolor << " a twoja karta bitewna to: " << gracz[i + 2].figura << " " << gracz[i + 2].kolor << ".";
		cout << endl << "Odslonieta karta przeciwnika to: " << komputer[i + 1].figura << " " << komputer[i + 1].kolor << " a karta bitewna przeciwnika to: " << komputer[i + 2].figura << " " << komputer[i + 2].kolor << "." << endl << endl;
		i+=2;
		pomocnicza.il_w++;
	}
	if (gracz[i].wartosc > komputer[i].wartosc)
	{
		i = i - (2 * pomocnicza.il_w);
		cout << "Wojna wygrana.";
		for (int d = 0; d < pomocnicza.il_w; d++)
		{
			gracz[pomocnicza.pkt_g] = komputer[i];
			gracz[pomocnicza.pkt_g + 1] = gracz[i];
			gracz[pomocnicza.pkt_g + 2] = komputer[i + 1];
			gracz[pomocnicza.pkt_g + 3] = gracz[i + 1];
			gracz[pomocnicza.pkt_g + 4] = komputer[i + 2];
			gracz[pomocnicza.pkt_g + 5] = gracz[i + 2];
			pomocnicza.pkt_g += 6;
			wsk_k_g+=3;
			wsk_k_k-=3;
			i += 3;
			return 0;
		}
	}
	else if (gracz[i].wartosc < komputer[i].wartosc)
	{
		i = i - (2 * pomocnicza.il_w);
		cout << "Wojna przegrana.";
		for (int d = 0; d < pomocnicza.il_w; d++)
		{
			komputer[pomocnicza.pkt_k] = gracz[i];
			komputer[pomocnicza.pkt_k + 1] = komputer[i];
			komputer[pomocnicza.pkt_k + 2] = gracz[i + 1];
			komputer[pomocnicza.pkt_k + 3] = komputer[i + 1];
			komputer[pomocnicza.pkt_k + 4] = gracz[i + 2];
			komputer[pomocnicza.pkt_k + 5] = komputer[i + 2];
			pomocnicza.pkt_k += 6;
			wsk_k_g -= 3;
			wsk_k_k += 3;
			i += 3;
			return 0;
		}
	}
	wojna2();
}

void wojna()
{
	int XD = 0;
	int runda = 1;
	do
	{
		system("cls");
		cout << "i: " << i << "    " << "Pkt g: " << pomocnicza.pkt_g << "    " << "Pkt k: " << pomocnicza.pkt_k << endl;

		cout << "GRA KARCIANA WOJNA " << endl << "Wojne wygrywa osoba ktora pozbawi przeciwnika wszystkich kart." << endl;
		cout << endl << "Runda: " << runda;
		cout << endl << "Ilosc twoich kart: " << wsk_k_g << ".";
		cout << endl << "Ilosc kart przeciwnika: " << wsk_k_k << "." << endl;
		cout << endl << "Aby wylozyc karte i przechodzic dalej naciskaj [ENTER]";
		cin.get();

		cout << endl << "Twoja karta to: " << gracz[i].figura << " " << gracz[i].kolor << ".";
		cout << endl << "Karta przeciwnika to: " << komputer[i].figura << " " << komputer[i].kolor << "." << endl << endl;

		if (i == 10000)
		{
			cout << endl << "Sesja trwa zbyt dlugo, uklad kart prawdopodobnie zapetlil gre." << endl;
			XD = 1;
		}

		if (gracz[i].wartosc > komputer[i].wartosc)
		{
			cout << "Bitwa wygrana.";
			gracz[pomocnicza.pkt_g] = komputer[i];
			gracz[pomocnicza.pkt_g + 1] = gracz[i];
			pomocnicza.pkt_g += 2;
			wsk_k_g++;
			wsk_k_k--;
			i++;
		}
		else if (gracz[i].wartosc < komputer[i].wartosc)
		{
			cout << "Bitwa przegrana.";
			komputer[pomocnicza.pkt_k] = gracz[i];
			komputer[pomocnicza.pkt_k + 1] = komputer[i];
			pomocnicza.pkt_k += 2;
			wsk_k_g--;
			wsk_k_k++;
			i++;
		}
		else if (gracz[i].wartosc == komputer[i].wartosc)
		{
			if (wsk_k_g > 2 && wsk_k_k > 2)
			{
				pomocnicza.il_w = 0;
				wojna2();
			}
			else if (wsk_k_g < 3)
			{
				cout << endl << "GRA PRZEGRANA" << endl;
				XD = 1;
			}
			else if (wsk_k_k < 3)
			{
				cout << endl << "GRA WYGRANA" << endl;
				XD = 1;
			}
		}
		cin.get();
		runda++;
		if (wsk_k_k <= 0)
		{
			cout << endl << "GRA WYGRANA" << endl;
			XD = 1;
		}
		if (wsk_k_g <= 0)
		{
			cout << endl <<  "GRA PRZEGRANA" << endl;
			XD = 1;
		}
	} while (XD != 1);
}

int main()
{
	generatortalii();
	tasowanie();
	rozdzielenie_kart();
	wojna();
	cout << endl;
	getchar;
}
