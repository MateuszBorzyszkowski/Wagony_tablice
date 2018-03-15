#pragma
#include <iostream>

const int MAXINT = -2147483647;

class Stos
{
private:
	int rozmiar_tab;
	int sptr;			//wskaznik stosu
	int *tab;			//tab dynamiczna
	int licznik;
public:
	Stos(int x);
	~Stos();
	bool empty(void);
	int top(void);
	int top_drugie(void);
	int size(void);
	void push(int v);
	void pop(void);
	void wypisz(int liczba);
};

Stos::Stos(int x)
{
	rozmiar_tab = x;
	tab = new int[x];
	sptr = 0;
	licznik = 0;
}
Stos::~Stos()
{
	delete[] tab;
}

bool Stos::empty(void)
{
	return !sptr;
}
int Stos::top(void)
{
	if (sptr) return tab[sptr - 1];
	return -MAXINT;
}
int Stos::top_drugie(void)
{
	if (sptr) return tab[sptr - 2];
	return -MAXINT;
}
int Stos::size(void)
{
	return licznik;
}
void Stos::push(int v)
{
	if (sptr < rozmiar_tab)
	{
		tab[sptr++] = v;
		licznik++;
	}
}
void Stos::pop(void)
{
	if (sptr)
	{
		sptr--;
		licznik--;
	}
}
void Stos::wypisz(int liczba)
{
	if (sptr)
	{
		//std::cout << top() << " ";
		sptr--;
	}

	int x = 0;
	while (x < liczba)
	{
		if (x == liczba - 1)
		{
			std::cout << "TAK";
			break;
		}
		if (tab[sptr] < tab[sptr - 1])
		{
			std::cout << "NIE";
			break;
		}
		else
		{
			pop();
		}
		x++;
	}

}



int main()
{
	int liczba_wagonow;
	int pom;
	int *tab_reverse;

	std::cin >> liczba_wagonow;

	Stos tor_boczny(liczba_wagonow);
	Stos bocznica(liczba_wagonow);
	Stos tor_peron(liczba_wagonow);

	tab_reverse = new int[liczba_wagonow];


	//ZACZYTANIE NA TOR BOCZNY I ODWROCENIE KOLEJNOSCI
	while (std::cin.good())
	{
		for (int i = 0; i < liczba_wagonow; i++)
		{
			std::cin >> tab_reverse[i];
		}
	}

	for (int i = liczba_wagonow - 1; i >= 0; i--)
	{
		tor_boczny.push(tab_reverse[i]);
	}
	//==================================================

	bool flaga = true;
	while (flaga)
	{
		if (bocznica.empty())														//jesli bocznica jest pusta to ide do toru bocznego
		{
			if (tor_boczny.empty())													// jesli tor boczny jest pusty to wszystko znajduje się juz na torze peron
			{
				std::cout << "WSZYSTKO NA PERONIE";
			}
			else																	// jesli tor boczny nie jest pusty to sprawdzamy czy sa co najmniej 2 wagony
			{
				if (tor_boczny.size() > 1)											// jesli sa co najmniej 2 wagony na torze bocznym to porownuje je, ktory jest wiekszy
				{
					if (tor_boczny.top() < tor_boczny.top_drugie())					// jesli wagon z gory jest wiekszy to idzie na tor peron
					{
						pom = tor_boczny.top();
						tor_boczny.pop();
						tor_peron.push(pom);
					}
					else															// jesli wagon z gory jest mniejszy to idzie na bocznice		
					{
						pom = tor_boczny.top();
						tor_boczny.pop();
						bocznica.push(pom);
					}
				}
				else																// jesli jest tylko 1 wagon na torze bocznym to przenies go na tor peron
				{
					pom = tor_boczny.top();
					tor_boczny.pop();
					tor_peron.push(pom);
				}
			}
		}
		else																		// jesli bocznica nie jest pusta
		{
			if (tor_boczny.empty())													// jesli tor boczny jest pusty to z bocznicy przenosimy na tor do peronu (nie mozemy przeniesc na tor boczny, jest to niedozwolone)
			{
				pom = bocznica.top();
				bocznica.pop();
				tor_peron.push(pom);
			}
			else																	// jesli tor boczny nie jest pusty to porownuje gore z toru bocznego i bocznicy
			{
				if (tor_boczny.top() < bocznica.top())								// jesli na torze bocznym jest wieksza gora niz na gorze bocznicy to sprawdzam czy sa chociaz 2 wagony na torze bocznym
				{
					if (tor_boczny.size() > 1)										// jesli na torze bocznym sa chociaz 2 wagony to je porownuje ktory jest wiekszy
					{
						if (tor_boczny.top() < tor_boczny.top_drugie())				// jesli wagon z gory jest wiekszy to idzie na tor peron
						{
							pom = tor_boczny.top();
							tor_boczny.pop();
							tor_peron.push(pom);
						}
						else														// jesli wagon z gory jest mniejszy to idzie na bocznice		
						{
							pom = tor_boczny.top();
							tor_boczny.pop();
							bocznica.push(pom);
						}
					}
					else															// jesli jest tylko 1 wagon na torze bocznym to przenies go na tor peron
					{
						pom = tor_boczny.top();
						tor_boczny.pop();
						tor_peron.push(pom);
					}
				}
				else																// jesli gora na bocznicy jest wieksza niz na torze bocznym to z bocznicy idzie na tor peron
				{
					pom = bocznica.top();
					bocznica.pop();
					tor_peron.push(pom);
				}
			}
		}

		if (tor_boczny.empty())
			if (bocznica.empty())
				flaga = false;
	}






	//std::cout << "Tor boczny: ";
	//while (!tor_boczny.empty())
	//{
	//	tor_boczny.wypisz();
	//}
	//std::cout << "\nBocznica: ";
	//while (!bocznica.empty())
	//{
	//	bocznica.wypisz();
	//}
	//std::cout << "\nTor peron: ";
	//while (!tor_peron.empty())
	//{
	//	tor_peron.wypisz();
	//}

	//std::cout << "Tor boczny: ";
	tor_peron.wypisz(liczba_wagonow);
	

	delete[]tab_reverse;
	return 0;
}