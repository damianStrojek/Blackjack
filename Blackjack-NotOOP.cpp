// Basic Programming main project
// Damian Strojek s184407 2020 EiT
// @ Copyright 2020, Damian Strojek, All rights reserved.
#include <iostream>
#include <time.h>
#include <cstdlib>
#include <iomanip>
#include <vector>

using std::cout;
using std::cin;
using std::vector;
using std::swap;

//STAŁE KTÓRYCH UŻYWAM W CAŁYM PROGRAMIE
const int ACE = 11;
const int J = 12;			//RÓŻNE WARTOŚCI JOPKA, KRÓLA I KRÓLOWEJ ŻEBYM BYŁ
const int Q = 13;           //W STANIE JE IDENTYFIKOWAĆ PRZY WYŚWIETLANIU KART
const int K = 14;
const int NOTMORE = 21;

void cardRED(int card);
void cardBLACK(int card);
void cardPIK(int card);
void colorSelection(int color, int card);
void initDeck(vector<int> &deck, vector<int> &color, vector<int> &playerHand, vector<int> &playerColor, vector<int> &computerHand, vector<int> &computerColor);
void shuffleDeck(int &CARDSNUMBER, vector<int> &deck, vector<int> &color);
void playerCards(int &CARDSNUMBER, vector<int> &playerHand, vector<int> &playerColor, vector<int> &deck, vector<int> &color);
void computerCards(int &CARDSNUMBER, vector<int> &computerHand, vector<int> &computerColor, vector<int> &deck, vector<int> &color);
bool checkACE(int &scorePlayer, int &yourTokens, int actualBet, vector<int> &playerHand);
void scoreCARDS(int &scorePlayer, int &scoreComputer, vector<int> playerHand, vector<int> computerHand);
void scoreHIT(int &score, int cardHIT);
bool computerPicking(int &scoreComputer, int &actualBet, int &CARDSNUMBER, vector<int> &deck);
bool blackjack(int scorePlayer, int scoreComputer, int &yourTokens, int actualBet);
bool check(int &scorePlayer, int cardHIT, int scoreComputer, int &yourTokens, int actualBet, vector<int> playerHand);
void HIT(int scorePlayer, int scoreComputer, int &CARDSNUMBER, int &yourTokens, int actualBet, vector<int> &deck, vector<int> &color, vector<int> &computerColor, vector<int> &computerHand, vector<int> &playerHand);
void STAND(int scorePlayer, int scoreComputer, int &CARDSNUMBER, int &yourTokens, int actualBet, vector<int> &deck, vector<int> &computerHand, vector<int> &computerColor, vector<int> &color, vector<int> &playerHand);
void DOUBLEDOWN(int scorePlayer, int scoreComputer, int &CARDSNUMBER, int &yourTokens, int actualBet, vector<int> &color, vector<int> &deck, vector<int> &computerHand, vector<int> &computerColor, vector<int> &playerHand);
void SPLIT(int scorePlayer, int scoreComputer, int &CARDSNUMBER, int &yourTokens, int actualBet, vector<int> &playerHand, vector<int> &playerColor, vector<int> &color, vector<int> &deck, vector<int> &computerHand, vector<int> &computerColor);
int menu(int scorePlayer);

int main(){
    system("cls"); 
	int yourTokens= 100;
	int CARDSNUMBER = 39;      //ZMIENIAM TA ZMIENNA TYLKO DLA PEWNOSCI ZE WSZYSTKO DZIAŁA JAK POWINNO, NIE JEST ONA TAK NAPRAWDE WYMAGANA BO WSZYSTKO ODBYWA SIE BEZ NIEJ
	int actualBet = 0;
	int scorePlayer = 0, scoreComputer = 0;
	bool KONIEC = false;

	vector<int> deck;
	vector<int> playerHand;
	vector<int> computerHand;
	vector<int> color;
	vector<int> playerColor;
	vector<int> computerColor;

	while(!KONIEC){
		cout << "\nYou have " << yourTokens<< " tokens. How many would you like to bet?  ";     //ILE TOKENOW POSIADA GRACZ I ILE CHCE ICH ZABETOWAC
		cin >> actualBet;
		if(yourTokens > 0 && actualBet > 0 & actualBet <= yourTokens){  						//SPRAWDZENIE CZY W OGOLE MOZNA W TEN SPOSOB ZABETOWAC     
			CARDSNUMBER = 39;       																//RESETUJEMY ILOSC KART CO KAZDA RUNDE - LICZBA TA SIE ZMIENIA
			initDeck(deck, color, playerHand, playerColor, computerHand, computerColor);        																	//TWORZYMY NOWA TALIE KART CO KAZDA RUNDE
			shuffleDeck(CARDSNUMBER, deck, color);   															//TASOWANIE
			system("cls");            

			playerCards(CARDSNUMBER, playerHand, playerColor, deck, color);         		//LOSOWANIE KART GRACZA
			computerCards(CARDSNUMBER, computerHand, computerColor, deck, color);      			//LOSOWANIE KART KOMPUTERA

			cout << "\nCards that you have rolled: \n";
			for(int i = 0; i < 2; i++){
				colorSelection(playerColor[i], playerHand[i]); 	 								//POKAZANIE KART GRACZA
			}

			cout << "\nOne of computer's card:\n";
			colorSelection(computerColor[0], computerHand[0]); 									//POKAZANIE KART NA DLONI KOMPUTERA
			scorePlayer = 0;
			scoreComputer = 0;
			scoreCARDS(scorePlayer, scoreComputer, playerHand, computerHand);												//POLICZENIE WARTOSCI KART

			if(scorePlayer > NOTMORE){
				if( checkACE(scorePlayer, yourTokens, actualBet, playerHand) ){                              //SPRAWDZENIE CZY NIE BĘDZIE BARDZIEJ KORZYSTNIE ZMIANA WARTOSCI ASA Z 11 NA 1 ALBO NA ODWRÓT
					continue;
				}
			}
			
			if( blackjack(scorePlayer, scoreComputer, yourTokens, actualBet) ){					//BLACKJACKA SPRAWDZAMY JUZ TUTAJ BO MOZLIWE JEST ZE PO DWOCH PIERWYCH
				continue;																		//KARTACH KOMPUTER ALBO GRACZ MAJA SUME WARTOSCI = 21
			}					

			int x = menu(scorePlayer);
			switch(x){
				case 1:	HIT(scorePlayer, scoreComputer, CARDSNUMBER, yourTokens, actualBet, deck, color, computerColor, computerHand, playerHand);
						//DOBIERZ KARTE PO CZYM COMPUTER ZACZYNA DOBIERAC KARTY,
						//POTEM MOZEMY WYBRAC CZY DOBIERAMY JESZCZE RAZ CZY SPRAWDZAMY WYNIK
						break;
				case 2:	STAND(scorePlayer, scoreComputer, CARDSNUMBER, yourTokens, actualBet, deck, computerHand, computerColor, color, playerHand);
						//NIE BIERZEMY KARTY TYLKO COMPUTER ZACZYNA DOBIERAC KARTY, 
						//A POTEM DOPIERO MOZEMY SAMI ZDECYDOWAC CZY DOBIERAMY CZY NIE
						break;
				case 3: DOUBLEDOWN(scorePlayer, scoreComputer, CARDSNUMBER, yourTokens, actualBet, color, deck, computerHand, computerColor, playerHand);
						//ZWIEKSZAMY BET O 100% I DOBIERAMY JEDNA KARTE DLA SIEBIE, ALE TYLKO JEDNO
						//WIEC OD RAZU POTEM DOBIERA KOMPUTER DO WARTOSCI >= 17 I SPRAWDZAMY WYGRANA
						break;
				case 4: SPLIT(scorePlayer, scoreComputer, CARDSNUMBER, yourTokens, actualBet, playerHand, playerColor, color, deck, computerHand, computerColor);
						//MOZNA GO WYKONAC JEDYNIE JESLI DWIE PIERWSZE KARTY GRACZA MIALY TA SAMA WARTOSC
						//W TYM PRZYPADKU DZIELIMY JEDNA REKE NA DWIE OSOBNE I ROZGRYWAMY TAK JAKBY DWIE GRY.
						break;
				default: KONIEC = true;
						 break;
			}
			if(yourTokens < 0){
				KONIEC = true;
				break;
			}
		}
		else{
			cout << "Bad value in actual Bet.\n";
			KONIEC = true;
		}

		if(yourTokens > 0){
			cout << "*****************************************************************";
			cout << "\nDo you still want to play? If yes press 1, otherwise press 2.\n";    //SPYTANIE SIE CZY GRACZ CHCE GRAC DALEJ CZY CHCE ZAKONCZYC W TYM MOMENCIE
			int x;
			cin >> x;
			if(x == 1){
				KONIEC = false;
			}
			else if(x == 2){
				KONIEC = true;
			}
			else{
				KONIEC = true;
			}
		}
	}

	system("cls");
	cout << "Thank you for the game. Your token balance = " << yourTokens << ".\n";
	if(yourTokens < 0){
		cout << "You need to pay me " << yourTokens << " tokens that you owe me. Here is my paypal : pgstudent2020@paypal.\n";  //JEZELI ILOSC TOKENOW JEST NA MINUSIE
	}
    return 0;
}

//WYŚWIETLANIE SIĘ KARTY O ZNAKU CZERWONEGO SERCA
void cardRED(int card){
	if(card >= 11 || card == 1){
		char znak;
		if(card == 11 || card == 1){
			znak = 'A';
		}
		else if(card == 12){
			znak = 'J';
		}
		else if(card == 13){
			znak = 'Q';
		}
		else if(card == 14){
			znak = 'K';
		}
		cout << " _ _ _ _ _ _ _ _ _ _   \n";
		cout << "|                    | \n";
		cout << "|  " << znak << "                 | \n";
		cout << "|                    | \n";
		cout << "|      ##    ##      | \n";
		cout << "|     ####  ####     | \n";
		cout << "|     ##########     | \n";
		cout << "|      ########      | \n";
		cout << "|       ######       | \n";
		cout << "|        ####        | \n";
		cout << "|         ##         | \n";
		cout << "|                    | \n";
		cout << "|                 " <<	znak << "  | \n";
		cout << "|_ _ _ _ _ _ _ _ _ _ | \n";
	}
	else if(card == 10){
		cout << "\n";
		cout << " _ _ _ _ _ _ _ _ _ _   \n";
		cout << "|                    | \n";
		cout << "|  " << card << "                | \n";
		cout << "|                    | \n";
		cout << "|      ##    ##      | \n";
		cout << "|     ####  ####     | \n";
		cout << "|     ##########     | \n";
		cout << "|      ########      | \n";
		cout << "|       ######       | \n";
		cout << "|        ####        | \n";
		cout << "|         ##         | \n";
		cout << "|                    | \n";
		cout << "|                 " <<	card << " | \n";
		cout << "|_ _ _ _ _ _ _ _ _ _ | \n";
	}
	else{
		cout << "\n";
		cout << " _ _ _ _ _ _ _ _ _ _   \n";
		cout << "|                    | \n";
		cout << "|  " << card << "                 | \n";
		cout << "|                    | \n";
		cout << "|      ##    ##      | \n";
		cout << "|     ####  ####     | \n";
		cout << "|     ##########     | \n";
		cout << "|      ########      | \n";
		cout << "|       ######       | \n";
		cout << "|        ####        | \n";
		cout << "|         ##         | \n";
		cout << "|                    | \n";
		cout << "|                 " <<	card << "  | \n";
		cout << "|_ _ _ _ _ _ _ _ _ _ | \n";
	}
}

//WYŚWIETLANIE SIĘ KARTY O ZNAKU CZARNEGO SERCA
void cardBLACK(int card){
	if(card >= 11 || card == 1){
		char znak;
		if(card == 11 || card == 1){
			znak = 'A';
		}
		else if(card == 12){
			znak = 'J';
		}
		else if(card == 13){
			znak = 'Q';
		}
		else if(card == 14){
			znak = 'K';
		}
		cout << " _ _ _ _ _ _ _ _ _ _   \n";
		cout << "|                    | \n";
		cout << "|  " << znak << "                 | \n";
		cout << "|                    | \n";
		cout << "|         ##         | \n";
		cout << "|        ####        | \n";
		cout << "|       ######       | \n";
		cout << "|      ########      | \n";
		cout << "|     ##########     | \n";
		cout << "|     ####  ####     | \n";
		cout << "|      ##    ##      | \n";
		cout << "|                    | \n";
		cout << "|                 " << znak << "  | \n";
		cout << "|_ _ _ _ _ _ _ _ _ _ | \n";
	}
	else if(card == 10){
		cout << "\n";
		cout << " _ _ _ _ _ _ _ _ _ _   \n";
		cout << "|                    | \n";
		cout << "|  " << card << "                | \n";
		cout << "|                    | \n";
		cout << "|      ##    ##      | \n";
		cout << "|     ####  ####     | \n";
		cout << "|     ##########     | \n";
		cout << "|      ########      | \n";
		cout << "|       ######       | \n";
		cout << "|        ####        | \n";
		cout << "|         ##         | \n";
		cout << "|                    | \n";
		cout << "|                 " <<	card << " | \n";
		cout << "|_ _ _ _ _ _ _ _ _ _ | \n";
	}
	else{
		cout << "\n";
		cout << " _ _ _ _ _ _ _ _ _ _   \n";
		cout << "|                    | \n";
		cout << "|  " << card << "                 | \n";
		cout << "|                    | \n";
		cout << "|         ##         | \n";
		cout << "|        ####        | \n";
		cout << "|       ######       | \n";
		cout << "|      ########      | \n";
		cout << "|     ##########     | \n";
		cout << "|     ####  ####     | \n";
		cout << "|      ##    ##      | \n";
		cout << "|                    | \n";
		cout << "|                 " << card << "  | \n";
		cout << "|_ _ _ _ _ _ _ _ _ _ | \n";\
	}
}

//WYŚWIETLANIE SIĘ KARTY O ZNAKU PIK
void cardPIK(int card){
	if(card >= 11 || card == 1){
		char znak;
		if(card == 11 || card == 1){
			znak = 'A';
		}
		else if(card == 12){
			znak = 'J';
		}
		else if(card == 13){
			znak = 'Q';
		}
		else if(card == 14){
			znak = 'K';
		}
		cout << " _ _ _ _ _ _ _ _ _ _   \n";
		cout << "|                    | \n";
		cout << "|  " << znak << "                 | \n";
		cout << "|                    | \n";
		cout << "|         ##         | \n";
		cout << "|        ####        | \n";
		cout << "|       ######       | \n";
		cout << "|      ########      | \n";
		cout << "|       ######       | \n";
		cout << "|        ####        | \n";
		cout << "|         ##         | \n";
		cout << "|                    | \n";
		cout << "|                 " << znak << "  | \n";
		cout << "|_ _ _ _ _ _ _ _ _ _ | \n";\
	}
	else if(card == 10){
		cout << "\n";
		cout << " _ _ _ _ _ _ _ _ _ _   \n";
		cout << "|                    | \n";
		cout << "|  " << card << "                | \n";
		cout << "|                    | \n";
		cout << "|      ##    ##      | \n";
		cout << "|     ####  ####     | \n";
		cout << "|     ##########     | \n";
		cout << "|      ########      | \n";
		cout << "|       ######       | \n";
		cout << "|        ####        | \n";
		cout << "|         ##         | \n";
		cout << "|                    | \n";
		cout << "|                 " <<	card << " | \n";
		cout << "|_ _ _ _ _ _ _ _ _ _ | \n";
	}
	else{
		cout << "\n";
		cout << " _ _ _ _ _ _ _ _ _ _   \n";
		cout << "|                    | \n";
		cout << "|  " << card << "                 | \n";
		cout << "|                    | \n";
		cout << "|         ##         | \n";
		cout << "|        ####        | \n";
		cout << "|       ######       | \n";
		cout << "|      ########      | \n";
		cout << "|       ######       | \n";
		cout << "|        ####        | \n";
		cout << "|         ##         | \n";
		cout << "|                    | \n";
		cout << "|                 " <<	card << "  | \n";
		cout << "|_ _ _ _ _ _ _ _ _ _ | \n";
	}
}

//WYŚWIETLENIE SIĘ JEDNEJ KARTY O DANYM KOLORZE
void colorSelection(int color, int card){
	if(color >= 1 && color <= 13){
		cardRED(card);
	}
	else if(color >= 14 && color <= 26){
		cardBLACK(card);
	}
	else if(color >= 27){
		cardPIK(card);
	}
}

//INICJALIZACJA TALII KART (RESET DO STANU POCZĄTKOWEGO) ORAZ WARTOSCI KART W DLONIACH OBU GRACZY
void initDeck(vector<int> &deck, vector<int> &color, vector<int> &playerHand, vector<int> &playerColor, vector<int> &computerHand, vector<int> &computerColor){
	deck = { ACE,2,3,4,5,6,7,8,9,10,J,Q,K,
	         ACE,2,3,4,5,6,7,8,9,10,J,Q,K,
	         ACE,2,3,4,5,6,7,8,9,10,J,Q,K };
	color = { 1,2,3,4,5,6,7,8,9,10,11,12,13,               //TE NUMERY POSIADAJĄ KARTY O ZNAKU CZERWONE SERCE
			  14,15,16,17,18,19,20,21,22,23,24,25,26,      //TE NUMERY POSIADAJĄ KARTY O ZNAKU CZARNE SERCE
			  27,28,29,30,31,32,33,34,35,36,37,38,39 };    //TE NUMERY POSIADAJĄ KARTY O ZNAKU PIK
	playerHand = { 0, 0 };
	playerColor = { 0, 0 };
	computerHand = { 0, 0 };
	computerColor = { 0, 0 };
}

//LOSOWANIE TALII KART
void shuffleDeck(int &CARDSNUMBER, vector<int> &deck, vector<int> &color){

	srand((unsigned)time(0));
	
	for (int i = 0; i < CARDSNUMBER; i++) 
		swap(deck[i], deck[rand() % CARDSNUMBER]);		//PRZELOSOWANIE TALII KART
	for (int i = 0; i < CARDSNUMBER; i++) 
		swap(color[i], color[rand() % CARDSNUMBER]);		//PRZELOSOWANIE KOLORU
}

//WYLOSOWANIE DWOCH KART DLA GRACZA
void playerCards(int &CARDSNUMBER, vector<int> &playerHand, vector<int> &playerColor, vector<int> &deck, vector<int> &color){
	for(int i = 0; i < 2; i++){
		playerHand[i] = deck.front();		//POBRANIE PIERWSZEJ KARTY Z POCZĄTKU
		deck.erase(deck.begin());			//USUNIĘCIE TEJ KARTY ABY SIĘ NIE POWTÓRZYŁA
	}
	for(int i = 0; i < 2; i++){
		playerColor[i] = color.front();		//POBRANIE PIERWSZEGO KOLORU
		color.erase(color.begin());			//USUNIĘCIE GO
	}
	CARDSNUMBER -= 2;  //ODEJMUJEMY ILOSC KART KTORE WYLOSOWALISMY ABY CARDSNUMBER W TALII SIE ZGADZALA
}

//WYCIAGNIECIE DWOCH KART DLA KOMPUTERA
void computerCards(int &CARDSNUMBER, vector<int> &computerHand, vector<int> &computerColor, vector<int> &deck, vector<int> &color){
	for(int i = 0; i < 2; i++){
		computerHand[i] = deck.front();		//TA SAMA OPERACJA CO PRZY DOBIERANIU GRACZA
		deck.erase(deck.begin());
	}
	for(int i = 0; i < 2; i++){
		computerColor[i] = color.front();
		color.erase(color.begin());
	}
	CARDSNUMBER -= 2; //ODJECIE DWOCH KART Z TALII ABY ILOSC KART W TALII SIE ZGADZALA DO PRZYSZLYCH RACHUNKOW
}

//SPRAWDZENIE WARTOSCI KART, CZY NIE MA PRZYPADKIEM ASA KTOREGO KORZYSTNIEJ BY BYLO ZAMIENIC
//NA WARTOSC 1 ALBO ZOSTAWIC GO Z WARTOŚCIĄ 11. SPRAWDZAMY TO TYLKO W PRZYPADKU GDY MAMY PONAD 21 WARTOSCI
//W KARTACH. NIE ROBIMY TEGO SAMEGO DLA KRUPIERA, NIGDZIE NIE PRZECZYTAŁEM O TYM ŻE KRUPIER MOŻE SOBIE ZAMIENIAĆ WARTOŚĆ ASA
bool checkACE(int &scorePlayer, int &yourTokens, int actualBet, vector<int> &playerHand){     
	if(playerHand[0] == 11){                               
		playerHand[0] = 1;                                
		scorePlayer = playerHand[0] + playerHand[1];
		return false;
	}	
	else if(playerHand[1] == 11){
		playerHand[1] = 1;
		scorePlayer = playerHand[0] + playerHand[1];
		return false;
	}
	else if(scorePlayer > NOTMORE){
		cout << "Unlucky, you lost all your tokens. Your score : " << scorePlayer << ".\n";
		yourTokens -= actualBet;
		return true;
	}   
	else{
		return false;
	}             
}

//OBLICZENIE WARTOSCI KART W OBU DŁONIACH
void scoreCARDS(int &scorePlayer, int &scoreComputer, vector<int> playerHand, vector<int> computerHand){
	//KARTY GRACZA
	if(playerHand[0] == 12 || playerHand[0] == 13 || playerHand[0] == 14){
		scorePlayer += 10;
	}
	else{
		scorePlayer += playerHand[0];
	}
	if(playerHand[1] == 12 || playerHand[1] == 13 || playerHand[1] == 14){
		scorePlayer += 10;
	}
	else{
		scorePlayer += playerHand[1];
	}

	//KARTY KRUPIERA
	if(computerHand[0] == 12 || computerHand[0] == 13 || computerHand[0] == 14){
		scoreComputer+= 10;
	}
	else{
		scoreComputer += computerHand[0];
	}
	if(computerHand[1] == 12 || computerHand[1] == 13 || computerHand[1] == 14){
		scoreComputer += 10;
	}
	else{
		scoreComputer += computerHand[1];
	}
}

//OBLICZENIE WARTOSCI KART PO DOBRANIU JEDNEJ KARTY
void scoreHIT(int &score, int cardHIT){
	if(cardHIT == 12 || cardHIT == 13 || cardHIT == 14){		//IDENTYFIKUJEMY CZY PRZYPADKIEM NIE JEST TO KRÓL, KRÓLOWA LUB JOPEK
		score += 10;
	}
	else{
		score += cardHIT;
	}
}	

//DOBIERANIE KART PRZEZ KOMPUTER AZ NIE OSIAGNIE WARTOSCI 17 LUB WYZEJ
bool computerPicking(int &scoreComputer, int &actualBet, int &CARDSNUMBER, vector<int> &deck){
	int cardHIT = 0;
	while(scoreComputer <= 16){                                                 //TUTAJ MAMY DOBIERANIE KART PRZEZ KOMPUTER AZ NIE DOJDZIE DO WARTOSCI
		cardHIT = deck.front();                                    	            //WIEKSZEJ LUB ROWNEJ 17
		deck.erase(deck.begin());												//KOLOR JEST NIE WAŻNY BO KARTY NIGDY NIE POKAŻEMY
		CARDSNUMBER--;
		
		scoreHIT(scoreComputer, cardHIT);										//OBLICZAMY WARTOSC KART PO DOBRANIU TEJ JEDNEJ KARTY
	}

	if(scoreComputer > NOTMORE){
		return false;
	}
	else{
		return true;
	}
}

//SPRAWDZENIE CZY ZADEN Z GRACZY NIE POSIADA BLACKJACKA
//BLACKJACK TO WARTOŚĆ KART = 21 I JEDNOCZEŚNIEJ JEST TO OD RAZU WYGRANA
bool blackjack(int scorePlayer, int scoreComputer, int &yourTokens, int actualBet){
	if(scoreComputer == NOTMORE){
		cout << "You lost all your tokens because computer have 'Blackjack' - exactly 21 value in cards.\n";
		yourTokens -= actualBet;
		return true;
	}
	else if(scorePlayer == NOTMORE){
		cout << "You win! You have 'BlackJack'! All tokens go to you!\n";
		yourTokens += actualBet;
		return true;
	}
	else{
		return false;
	}
}

//SPRAWDZENIE WYGRANEGO
bool check(int &scorePlayer, int cardHIT, int scoreComputer, int &yourTokens, int actualBet, vector<int> playerHand){
	if(playerHand[0] == 1 || playerHand[1] == 1 || cardHIT == 1){              
		if((scorePlayer + 10) <= 21){                        		//DODAJEMY 10 BO MAMY JUŻ WARTOŚĆ 1 ZAPISANĄ JAKO TEN JEDEN AS              
			scorePlayer += 10;
			if(scorePlayer > scoreComputer){
				cout << "You win! All tokens go to you. Your score : " << scorePlayer << " , score of computer : " << scoreComputer << ".\n";
				yourTokens += actualBet;
				return true;
			}
			else{
				cout << "You lost your money. Your score : " << scorePlayer << " , score of computer : " << scoreComputer << ".\n";
				yourTokens -= actualBet;
				return true;
			}
		}
		else{
			if(scorePlayer > scoreComputer){
				cout << "You win! All tokens go to you. Your score : " << scorePlayer << " , score of computer : " << scoreComputer << ".\n";
				yourTokens += actualBet;
				return true;
			}
			else{
				cout << "You lost your money. Your score : " << scorePlayer << " , score of computer : " << scoreComputer << ".\n";
				yourTokens -= actualBet;
				return true;
			}
		}
	}
	else{
		if(scorePlayer > scoreComputer){
			cout << "You win! All tokens go to you. Your score : " << scorePlayer << " , score of computer : " << scoreComputer << ".\n";
			yourTokens += actualBet;
			return true;
		}
		else{
			cout << "You lost your money. Your score : " << scorePlayer << " , score of computer : " << scoreComputer << ".\n";
			yourTokens -= actualBet;
			return true;
		}
	}
}

//HIT - DOBIERAMY JEDNA KARTE, NASTEPNIE KOMPUTER DOBIERA TYLE KART ABY MIEC SUME WARTOSCI KART WYZSZA LUB ROWNA 17
void HIT(int scorePlayer, int scoreComputer, int &CARDSNUMBER, int &yourTokens, int actualBet, vector<int> &deck, vector<int> &color, vector<int> &computerColor, vector<int> &computerHand, vector<int> &playerHand){

	system("cls");
	cout << "Card that you have chosen : \n";

	int cardHIT = deck.front();
	deck.erase(deck.begin());  
	int colorHIT = color.front();
	color.erase(color.begin());     

	CARDSNUMBER--;

	colorSelection(colorHIT, cardHIT);      //WYBIERAMY NOWĄ KARTE
	
	scoreHIT(scorePlayer, cardHIT);      //DODAJEMY WARTOSC KARTY DO WYNIKU

	if(scorePlayer > NOTMORE){
		if( checkACE(scorePlayer, yourTokens, actualBet, playerHand) ){                              //SPRAWDZENIE CZY NIE BĘDZIE BARDZIEJ KORZYSTNIE ZMIANA WARTOSCI ASA Z 11 NA 1 ALBO NA ODWRÓT
			return;
		}
	}
	
	if( !(computerPicking(scoreComputer, actualBet, CARDSNUMBER, deck)) ){
		cout << "Computer has more than 21 value in cards. You win. All tokens go to you.\n";
		yourTokens += actualBet;
		return;
	}

	cout << "Computer cards :\n";
	colorSelection(computerColor[0], computerHand[0]);
	colorSelection(computerColor[1], computerHand[1]);
	
	if( blackjack(scorePlayer, scoreComputer, yourTokens, actualBet) ){											//SPRAWDZENIE CZY PRZYPADKIEM NIKT NIE MA BLACKJACKA
		return;																									//BLACKJACK ZDARZA SIE W SYTUACJI W KTOREJ JEDEN Z GRACZY MA SUME WARTOSCI KART
	}																											//ROWNA 21. W TYM PRZYPADKU ON WYGRYWA CHYBA ZE KOMPUTER MA ROWNIEZ 21

	while(scorePlayer < NOTMORE){                                                                               //ZAPETLAMY WYBOR DOBRANIA KARTY ALBO ZAKOCZENIA RUNDY W TYM MOMENCIE
		cout << "Now you have card with sum of values = " << scorePlayer <<". What do you want to do?\n";
		cout << "1. HIT (take another card from the dealer)\n" <<
				"2. END AND CHECK WHO WINS\n";
		int x = 0;
		cin >> x;
		switch(x){ 
			case 1:	
					cardHIT = deck.front();
					deck.erase(deck.begin());
					colorHIT = color.front();
					color.erase(color.begin());

					cout << "The card you chose : \n";
					colorSelection(colorHIT, cardHIT);
					CARDSNUMBER--;
					
					scoreHIT(scorePlayer, cardHIT);

					if(scorePlayer > NOTMORE){
						if( checkACE(scorePlayer, yourTokens, actualBet, playerHand) ){                              //SPRAWDZENIE CZY NIE BĘDZIE BARDZIEJ KORZYSTNIE ZMIANA WARTOSCI ASA Z 11 NA 1 ALBO NA ODWRÓT
							return;
						}
					}
					break;
			case 2: if( check(scorePlayer, cardHIT, scoreComputer, yourTokens, actualBet, playerHand) ){
						return;
					}
					break;
			default: exit(1);
		}
	}
}

//GDY WYBIERAMY ZE CHCEMY CZEKAC TO ZOSTAJEMY Z NASZYMI DWOMA KARTAMI I CZEKAMY NA TO AZ KOMPUTER DOBIERZE LUB NIE DOBIERZE
//(TO DRUGIE ZDARZA SIE WTEDY GDY SUMA DWOCH PIERWSZYCH KART JEST >= 17) DODATKOWYCH KART. NASTEPNIE MAMY ZNOW WYBOR
//CZY PRZYPADKIEM NIE CHCEMY DOBRAC KARTY
void STAND(int scorePlayer, int scoreComputer, int &CARDSNUMBER, int &yourTokens, int actualBet, vector<int> &deck, vector<int> &computerHand, vector<int> &computerColor, vector<int> &color, vector<int> &playerHand){
	system("cls");
	int cardHIT = 0, colorHIT = 0;

	if( !(computerPicking(scoreComputer, actualBet, CARDSNUMBER, deck)) ){
		cout << "Computer has more than 21 value in cards. You win. All tokens go to you.\n";
		yourTokens += actualBet;
		return;
	}

	cout << "Computer cards :\n";
	colorSelection(computerColor[0], computerHand[0]);
	colorSelection(computerColor[1], computerHand[1]);

	if( blackjack(scorePlayer, scoreComputer, yourTokens, actualBet) ){										         //SPRAWDZENIE BLACKJACKA
		return;																								
	}

	while(scorePlayer < NOTMORE){                                                                                        //TAKA SAMA PETLA JAK WCZESNIEJ
		cout << "Now you have card with sum of values = " << scorePlayer << ". What do you want to do?\n";
		cout << "1. HIT (take another card from the dealer)\n" <<
				"2. END AND CHECK WHO WINS\n";
		int x = 0;
		cin >> x;
		switch(x){
			case 1:	system("cls");
					cardHIT = deck.front();
					deck.erase(deck.begin());
					colorHIT = color.front();
					color.erase(color.begin());

					cout << "Your card : \n";
					colorSelection(colorHIT, cardHIT);

					CARDSNUMBER--;
					
					scoreHIT(scorePlayer, cardHIT);

					if(scorePlayer > NOTMORE){
						if( checkACE(scorePlayer, yourTokens, actualBet, playerHand) ){                              //SPRAWDZENIE CZY NIE BĘDZIE BARDZIEJ KORZYSTNIE ZMIANA WARTOSCI ASA Z 11 NA 1 ALBO NA ODWRÓT
							return;
						}
					}
					
					break;
			case 2: if( check(scorePlayer, cardHIT, scoreComputer, yourTokens, actualBet, playerHand) ){
						return;
					}
					break;
			default: exit(1);
		}
	}
}

//PRZY PODWOJENIU STAWKI ZWIEKSZAMY AKTUALNY BET * 2, ALE GRACZ JEST ZMUSZONY DO DOBRANIA TYLKO I WYLACZNIE JEDNEJ KARTY
//ZASADY KOMPUTERA ZOSTAJĄ TAKIE SAME - DOBIERA AŻ DO >= 17.
void DOUBLEDOWN(int scorePlayer, int scoreComputer, int &CARDSNUMBER, int &yourTokens, int actualBet, vector<int> &color, vector<int> &deck, vector<int> &computerHand, vector<int> &computerColor, vector<int> &playerHand){
	system("cls");

	actualBet = actualBet * 2;
	cout << "You have chosen to double down the actual bet. Right now bet = " << actualBet << "\n";
	cout << "Card that you have chosen : ";

	int cardHIT = deck.front();
	deck.erase(deck.begin());
	int colorHIT = color.front();
	color.erase(color.begin());

	CARDSNUMBER--;

	colorSelection(colorHIT, cardHIT);
	scoreHIT(scorePlayer, cardHIT);

	cout << "Computer cards :\n";
	colorSelection(computerColor[0], computerHand[0]);
	colorSelection(computerColor[1], computerHand[1]);

	if(scorePlayer > NOTMORE){
		if( checkACE(scorePlayer, yourTokens, actualBet, playerHand) ){                              //SPRAWDZENIE CZY NIE BĘDZIE BARDZIEJ KORZYSTNIE ZMIANA WARTOSCI ASA Z 11 NA 1 ALBO NA ODWRÓT
			return;
		}
	}

	if( !(computerPicking(scoreComputer, actualBet, CARDSNUMBER, deck)) ){
		cout << "Computer has more than 21 value in cards. You win. All tokens go to you.\n";
		yourTokens += actualBet;
		return;

	}

	if( blackjack(scorePlayer, scoreComputer, yourTokens, actualBet) ){											//SPRAWDZENIE BLACKJACKA
		return;																								
	}

	if( check(scorePlayer, cardHIT, scoreComputer, yourTokens, actualBet, playerHand) ){
		return;
	}
}

//JEZELI NASZE DWIE PIERWSZE KARTY SA TAKIE SAME TO JESTESMY W STANIE PODZIELIC NASZA RUNDE NA DWIE OSOBNE RUNDY W KTORYCH WALCZYC BEDZIEMY O TA
//SAMA STAWKE WIEC MOZEMY DWA RAZY WIECEJ ALE MNIEJSZYM RYZYKIEM NIZ W PRZYPADKU DOUBLEDOWN
void SPLIT(int scorePlayer, int scoreComputer, int &CARDSNUMBER, int &yourTokens, int actualBet, vector<int> &playerHand, vector<int> &playerColor, vector<int> &color, vector<int> &deck, vector<int> &computerHand, vector<int> &computerColor){
	if(playerHand[0] == playerHand[1]){                                                                             //SPRAWDZAMY CZY W OGOLE TAKIE ZAGRANIE JEST MOZLIWE
		system("cls");
		cout << "You did choose to split. Now you are going to decide firstly for your first hand and secondly for your second hand. You cant split again.\n";
		int doubleCard  = playerHand[0];

		//PIERWSZA REKA
		cout << "***************************************************\n";
		cout << "FIRST HAND :\n";	

		initDeck(deck, color, playerHand, playerColor, computerHand, computerColor);
		shuffleDeck(CARDSNUMBER, deck, color);

		playerHand[0] = doubleCard;
		playerColor[0] = color.front();
		color.erase(color.begin());

		playerHand[1] = deck.front();
		playerColor[1] = color.front();
		color.erase(color.begin());
		deck.erase(deck.begin());

		CARDSNUMBER -= 2;

		computerCards(CARDSNUMBER, computerHand, computerColor, deck, color);

		for(int i = 0; i < 2; i++){
			colorSelection(playerColor[i], playerHand[i]);
		}

		cout << "Your bet on this round is " << actualBet << " tokens.\n";
		
		scoreCARDS(scorePlayer, scoreComputer, playerHand, computerHand);

		cout << "Sum of your cards: " << scorePlayer << "\n";

		int x = 0;
		cout << "Now you can:\n1. HIT (take another card from the dealer)" <<
		"\n2. STAND (Take no more cards, choose if you have 21 value)" <<
		"\n3. DOUBLE DOWN (Increase the bet x2 and take only one card)" <<
		"\n4. EXIT\n";
		cout << "Whats your decision?   ";
		cin >> x;
		switch(x){                                                                              //KOPIUJEMY TUTAJ FORMULKE Z INT MAIN PONIEWAZ DZIALA TO NA TEJ SAMEJ ZASADZIE
			case 1:	HIT(scorePlayer, scoreComputer, CARDSNUMBER, yourTokens, actualBet, deck, color, computerColor, computerHand, playerHand);          //ALE BEZ OPCJI SPLIT
					//DOBIERZ KARTE PO CZYM COMPUTER ZACZYNA DOBIERAC KARTY,
					//POTEM MOZEMY WYBRAC CZY DOBIERAMY JESZCZE RAZ CZY SPRAWDZAMY WYNIK
					break;
			case 2:	STAND(scorePlayer, scoreComputer, CARDSNUMBER, yourTokens, actualBet, deck, computerHand, computerColor, color, playerHand);
					//NIE BIERZEMY KARTY TYLKO COMPUTER ZACZYNA DOBIERAC KARTY, 
					//A POTEM DOPIERO MOZEMY SAMI ZDECYDOWAC CZY DOBIERAMY CZY NIE
					break;
			case 3: DOUBLEDOWN(scorePlayer, scoreComputer, CARDSNUMBER, yourTokens, actualBet, color, deck, computerHand, computerColor, playerHand);
					//ZWIEKSZAMY BET O 100% I DOBIERAMY JEDNA KARTE DLA SIEBIE, ALE TYLKO JEDNO
					//WIEC OD RAZU POTEM DOBIERA KOMPUTER DO WARTOSCI >= 17 I SPRAWDZAMY WYGRANA
					break;
			default: cout << "Bad key. End of the game.\n";
					 exit(1); 
					
		}

		//DRUGA REKA
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		cin.ignore();
		cin.ignore();
		system("cls");

		cout << "***************************************************\n";
		cout << "SECOND HAND :\n";	                                                         //POWTARZAMY TO WSZYSTKO CO WCZESNIEJ, ALE DLA DRUGIEJ REKI

		initDeck(deck, color, playerHand, playerColor, computerHand, computerColor);
		shuffleDeck(CARDSNUMBER, deck, color);

		playerHand[0] = doubleCard;
		playerColor[0] = color.front();
		color.erase(color.begin());

		playerHand[1] = deck.front();
		deck.erase(deck.begin());
		playerColor[1] = color.front();
		color.erase(color.begin());

		CARDSNUMBER -= 2;

		computerCards(CARDSNUMBER, computerHand, computerColor, deck, color);

		for(int i = 0; i < 2; i++){
			colorSelection(playerColor[i], playerHand[i]);
		}

		cout << "Your bet on this round is " << actualBet << " tokens.\n";
		
		scoreCARDS(scorePlayer, scoreComputer, playerHand, computerHand);

		cout << "Sum of your cards: " << scorePlayer << "\n";

		x = 0;
		cout << "Now you can:\n1. HIT (take another card from the dealer)" <<
		"\n2. STAND (Take no more cards, choose if you have 21 value)" <<
		"\n3. DOUBLE DOWN (Increase the bet x2 and take only one card)" <<
		"\n4. EXIT\n";
		cout << "Whats your decision?   ";
		cin >> x;
		switch(x){
			case 1:	HIT(scorePlayer, scoreComputer, CARDSNUMBER, yourTokens, actualBet, deck, color, computerColor, computerHand, playerHand);
					//DOBIERZ KARTE PO CZYM COMPUTER ZACZYNA DOBIERAC KARTY,
					//POTEM MOZEMY WYBRAC CZY DOBIERAMY JESZCZE RAZ CZY SPRAWDZAMY WYNIK
					break;
			case 2:	STAND(scorePlayer, scoreComputer, CARDSNUMBER, yourTokens, actualBet, deck, computerHand, computerColor, color, playerHand);
					//NIE BIERZEMY KARTY TYLKO COMPUTER ZACZYNA DOBIERAC KARTY, 
					//A POTEM DOPIERO MOZEMY SAMI ZDECYDOWAC CZY DOBIERAMY CZY NIE
					break;
			case 3: DOUBLEDOWN(scorePlayer, scoreComputer, CARDSNUMBER, yourTokens, actualBet, color, deck, computerHand, computerColor, playerHand);
					//ZWIEKSZAMY BET O 100% I DOBIERAMY JEDNA KARTE DLA SIEBIE, ALE TYLKO JEDNO
					//WIEC OD RAZU POTEM DOBIERA KOMPUTER DO WARTOSCI >= 17 I SPRAWDZAMY WYGRANA
					break;
			default: cout << "Bad key. End of the game.\n";
					 exit(1); 
					
		}	
	}
	else{
		cout << "Your cards are not the same. Because of this you need to rematch.\n";
		return;
	}
}

//MENU NA POCZATKU GRY
int menu(int scorePlayer){

	cout << "Sum of your cards: " << scorePlayer << "\n";
	cout << "Now you can:\n1. HIT (take another card from the dealer)" <<
	"\n2. STAND (Take no more cards)" <<
	"\n3. DOUBLE DOWN (Increase the bet x2 and take only one card)" <<
	"\n4. SPLIT (Only if your cards are the same. You make two separate games with two separate bets.)" <<
	"\n5. EXIT\n";
	cout << "Whats your decision?   ";

	int x = 0;
	cin >> x;

	return x;
}