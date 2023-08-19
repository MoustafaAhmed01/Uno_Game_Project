/*
*  Copy rights for Eng. Moustafa Ahmed Adel @ Cairo University Faculty of Engineering
*  It's not allowed to copy the code before getting permission.
*
*																	UNO GAME
*	This project is unde the superrvision of Dr. Omar Naser  @Cairo University Faculty of Engineering (Embedded Systems)-Data Structure
*	>>Use small letters only.
*	Welcome to our game. This code was fully made by us! Nothing is copied! No idea was stolen from anywhere! Even the idea of the game was just a mind storm from us.
*	From scratch to 6800+ line!
* Note:
*		-This code is designed to play with a computer or a secondplayer (Another person), if you chose to play with a computer you will have three modes (normal - hard - insane) will be discussed
*		-In this code we have used stack and linked list ( stack > storing the cards , linked list > Players cards.
*
*	Illustration for the game:
* Illustrating in steps:
* 1- At first we started initializing  a structure variable CARD inside class 'Cards', it will an array[108] As Uno consists of 108 card.
*	This structure variable will contain the ref,color,NUM,type (Where ref will be a reference for each card as we will use it to shuffle the cards and then calling it back
*	Cards[i].Color > will be the color of each card as red, yellow, green and blue or wild ( wild > plusfour and colorchange cards)
*	For more info about how to play Uno check this website ( simple illustration) : https://www.ultraboardgames.com/uno/game-rules.php
*
* 2- After shuffling the cards ( this function will be discussed), started using the stack function to store all the cards[108] inside it and it will just be used for drawing cards using pop function
*
* 3- starting to distribute the cards on the players (7 cards for each player) using pop function
*
* 4- Playerone and Playertwo are two objects for linked list class will represent the first player and the second player(computer or real person)
*
* 5- we will turn the firstcard using the the UNO class function Game which initiates the game > pop function
*
* 6- Taking the firstplayer as the first one who will play.
*
* ******************************************************************************************************************************************************
* * ****Some abbrevtaions:
*
* 1- normal card : like red 3, yellow 5. In a simple method ( Color + Number, type = normal)
* 2- Power cards: like Red skip, blue reverse ( Color + skip, blue, reverse ( Color = color , type = (skip, reverse,plustwo) NUM = -1) i.e. Higher periority
* 3- wild cards: Colorchange or Plusfour ( color = "wild" , type = Plusfour, Colorchange , NUM = -1) i.e. Higher periority
*
* ******************************************************************************************************************************************************
* ---------------------Difference between easy - normal - hard - insane-------------------------
* well, Easy : It just play like a little bit random ( Priority : Normal cards > wild cards[colorchange - plusfour]), just finds the first card could be played and don't think what gonna happen next
*
* Normal : - wild ( random ) > normal cards (random)
*
*  Hard: (Priority : Power > Plusfour > Normal > Colorchange): we can say it has kinda small brain as it searchs for power card first if not then searchs plusfour then normal then Colorchange
* Note:
*		Plusfour was made before normal cards to increase the cards of the first player ASAP and using colorchange at the end to find any exit if it doesn't have any card to play with the ground card;
*
*	Insane: ( Priority : 1- Power( checking for skip,reverse,plustwo at first) it will NOT just play it if found! it will check if it has another card from the same color or even another card from the same type
						 2- plusfour as said before
						 3- Normal cards ( letting the priority for the cards having a number with different color)
						 4- Colorchange if it doesn't have anything to play
*
*
*/

/*
* IDFILE : card on ground
* First : First player cards
* Second : Second Player cards
*/

/*
* Assist : UNO object
* Playerone & Playertwo : linked list object
* call : Cards object
* readycards : stack object
*
*/

#include<iostream>
#include<stack>
#include<cstring>
#include<string>
#include<fstream>
#include<stdlib.h>
#include<limits>
#include<ctype.h>
#include<algorithm>
#include<time.h>
#include<chrono>

using namespace std;

auto start = chrono::steady_clock::now();

#define MAX 200	//Stack array size
int Anothertrytest;		//Drawing one time only for playerone
int Anothertrytest2;	//Drawing one time only for playertwo
int PlayedCards[106]; //worst case that each player could have at least 1 
int PlayedCardsNumber = 0;
char* choose = new char[20]; // computer or player
char* difficulty = new char[20]; // normal hard insane

// This class is used to start the game as it checks the firstcard and then starts to call the players
class UNO
{
private:
	void firstplayer(int refe);
	void secondplayer(int refe);
	void computernormal(int refe);
	void computereasy(int refe);
	void computerhard(int refe);
	void computerInsane(int refe);
public:
	void Game();
	void FetchingH();
}Assist;

// counts as the Main thing of this code.
class Cards
{
private:
	struct CARD
	{
		int NUM, ref;
		string Color, type;
	};

	void Initialize(struct CARD* arr, int n);
	void Identifying(struct CARD* decA);
	void stackM(struct CARD* arr);
	void firstPlayerCards(struct CARD* arr);
	void secondPlayerCards(struct CARD* arr);
	void computercards(struct CARD* arr);
	void ID(struct CARD* arr, int key);
	void ID2(struct CARD* arr, int key); // Printing the ground card
public:
	int NUM, Color;
	string type;

	struct CARD cardss[108];

	void InitializeH();
	void firstPlayercardsH();
	void secondPlayercardsH();
	void computercardsH();
	void IDH(int key);
	void IDH2(int key);
	void drawH1(int key);
	void drawH2(int key);

	Cards()
	{
		NUM = Color = 0;
	}

	void output()
	{
		for (int i = 0; i <= 107; i++)
		{
			cout << ' ' << cardss[i].ref;
		}
	}


}call;

//Linked list
class link
{
private:

	link* head;
	link* tail;
	int length;

public:

	int data;
	link* next;
	link* prevs;

	//Construction

	link()
	{
		head = tail = NULL;
		length = 0;
	}

	// Checking the list

	bool IsEmpty()
	{
		return length == 0;
	}

	//Entering new data at first position
	void push(int new_data)
	{
		link* new_node = new link();
		new_node->data = new_data;

		if (length == 0)
		{
			head = tail = new_node;
			new_node->next = new_node->prevs = NULL;
			length++;
		}
		else
		{
			new_node->next = head;
			new_node->prevs = head->prevs;
			head->prevs = new_node;

			head = new_node;
			length++;
		}
	}

	void last(int new_data)
	{
		link* new_node = new link();
		new_node->data = new_data;

		if (length == 0)
		{
			push(new_data);
		}
		else
		{
			tail->next = new_node;
			new_node->next = NULL;
			new_node->prevs = tail;
			tail = new_node;
			length++;

		}
	}

	void insert(int pos, int new_data)
	{

		if (pos == 0)
		{
			push(new_data);
		}
		else if (pos > length || pos < 0)
		{
			cout << "Please enter a correct poisition your linklist length = " << length;
		}
		else
		{
			link* new_node = new link();
			new_node->data = new_data;

			link* cur = head;

			for (int i = 1; i < pos; i++)
			{
				cur = cur->next;
			}
			new_node->next = cur->next;
			new_node->prevs = cur;
			cur->next = new_node;
			length++;
		}
	}

	void insertA(int pos, int new_data)
	{
		link* curr = head;
		link* temp = curr;
		link* new_node = new link();
		new_node->data = new_data;

		if (pos == length)
		{
			last(new_data);
		}
		else if (length == 0)
		{
			push(new_data);
		}
		else
		{
			for (int i = 1; i <= pos; i++)
			{
				temp - curr;
				curr = curr->next;
			}
			new_node->next = curr->next;
			new_node->prevs = temp;
			curr->next = new_node;
			length++;
		}
	}

	void clearing()
	{
		link* temp;
		while (length > 1)
		{
			temp = head;
			head = head->next;
			head->prevs = NULL;
			delete temp;
			length--;
		}
		if (length == 1)
		{
			head = tail = NULL;
			length--;
			return;
		}

		return;
	}

	void del(int key)
	{
		link* temp = head;
		link* next;
		link* prev;

		if (length == 1)
		{
			head = tail = NULL;
			length--;
			return;
		}
		else if (temp->data == key && temp->next != NULL)
		{

			head = head->next;
			head->prevs = NULL;
			delete temp;
			length--;
			return;
		}
		else
		{
			while (temp->next != NULL && temp->data != key)
			{
				temp = temp->next;
			}
			if (temp->next == NULL)
			{
				if (temp->data == key)
				{
					prev = temp->prevs;
					prev->next = NULL;
					tail = prev;
					delete temp;
					length--;
				}
				else
					cout << "Not found " << endl;
				return;
			}
			else
			{
				prev = temp->prevs;
				prev->next = temp->next;
				next = temp->next;
				next->prevs = prev;
				delete temp;
				length--;
			}
		}
	}
	void search(int key)
	{
		int count = 0;
		link* temp = head;

		if (length == 0)
		{
			cout << "You have no data in our list" << endl;
		}
		else if (length == 1)
		{
			if (head->data == key)
			{
				cout << "It is found at position 0 ." << endl;
			}
			else
				cout << " Not Found " << endl;
		}
		else
		{

			while (temp->data != key && temp->next != NULL)
			{
				count++;
				temp = temp->next;
			}

			if (temp->next == NULL)
			{
				if (temp->data == key)
				{
					cout << " It is found at position.. = " << count << endl;
				}
				else
				{
					cout << " Not found." << endl;
				}
			}
			else
			{
				cout << " It is found at position. = " << count << endl;
			}
		}
	}

	void rev()
	{
		link* next;
		link* curr = head;
		link* prev = NULL;

		if (length == 0)
		{
			cout << " Nothing will be changed" << endl;
		}
		else
		{

			while (curr != NULL)
			{
				next = curr->next;
				curr->next = prev;
				prev = curr;
				curr = next;
			}
			tail = head;
			head = prev;
		}
	}

	void pl()
	{
		cout << " Head->Data = " << head->data << endl;
		cout << " Last->Data = " << tail->data << endl;
	}

	int len()
	{
		//cout << " Length = " << length << endl;
		return length;
	}

	void print1()
	{
		link* cur = head;
		ofstream firstplayercards("First.txt");
		while (cur != NULL)
		{
			firstplayercards << cur->data << ' ';
			//cout << cur->data << " ";
			cur = cur->next;
		}
		firstplayercards.close();
	}

	void print2()
	{
		link* cur = head;
		ofstream secondplayercards("Second.txt");
		while (cur != NULL)
		{

			secondplayercards << cur->data << ' ';
			//cout << cur->data << " ";
			cur = cur->next;
		}
		secondplayercards.close();
	}

}Playerone, Playertwo;

//Stack
class Stack
{
	int top;

public:
	void distributer();
	int a[MAX]; // Maximum size of Stack

	Stack()
	{
		top = -1;
	}
	bool push(int x);
	int pop();
	int peek();
	bool isEmpty();
}readycards;

bool Stack::push(int x)
{
	if (top >= (MAX - 1)) {
		//cout << "Stack Overflow";
		return false;
	}
	else {
		a[++top] = x;
		//cout << x << " pushed into stack\n";
		return true;
	}
}

int Stack::pop()
{
	if (top < 0) {
		cout << "Stack Underflow";
		return -2;
	}
	else {
		int x = a[top--];
		return x;
	}
}

int Stack::peek()
{
	if (top < 0)
	{
		cout << "Stack is Empty";
		return -2;
	}
	else
	{
		int x = a[top];
		return x;
	}
}

bool Stack::isEmpty()
{
	return (top < 0);
}

//Distributes the cards on the players.
void UNO::FetchingH()
{
	//First Player
	for (int i = 1; i <= 7; i++)
	{
		Playerone.push(readycards.peek());
		readycards.pop();
	}
	//Second Player
	for (int i = 1; i <= 7; i++)
	{
		Playertwo.push(readycards.peek());
		readycards.pop();
	}
}

//calls the next 3 functions
void Cards::InitializeH()
{
	Initialize(cardss, 107);
	Identifying(cardss);
	stackM(cardss);
}

//Shuffling the cards
void Cards::Initialize(struct CARD* arr, int n)
{
	//This array will contain in his ref a numbers from 0 to 108
	// then wiil be shuffled using rand() function and srand to pick the array elements randomly
	for (int i = 0; i <= 107; i++)
	{
		arr[i].ref = i;
	}

	if (n > 1)
	{
		int i;
		srand(time(NULL));
		for (i = 0; i < n - 1; i++)
		{
			int j = i + rand() / (RAND_MAX / (n - i) + 1);
			int t = arr[j].ref;
			arr[j].ref = arr[i].ref;
			arr[i].ref = t;
		}
	}
	int temp = rand() % 100;
	int t = arr[temp].ref;
	arr[temp].ref = arr[107].ref;
	arr[107].ref = t;

	temp = rand() % 100;
	t = arr[temp].ref;
	arr[temp].ref = arr[0].ref;
	arr[0].ref = t;
}

void shuffle()
{
	cout << "\n Refilling the stack again\n";
	PlayedCardsNumber -= 2; //to leave the firstcard as it is

	if (PlayedCardsNumber > 1)
	{
		int i;
		srand(time(NULL));
		for (i = 0; i < PlayedCardsNumber - 1; i++)
		{
			int j = i + rand() / (RAND_MAX / (PlayedCardsNumber - i) + 1);
			int t = PlayedCards[j];
			PlayedCards[j] = PlayedCards[i];
			PlayedCards[i] = t;
		}
	}
	int temp = rand() % 100;
	int t = PlayedCards[temp];
	PlayedCards[temp] = PlayedCards[1];
	PlayedCards[PlayedCardsNumber] = t;

	temp = rand() % 100;
	t = PlayedCards[temp];
	PlayedCards[temp] = PlayedCards[0];
	PlayedCards[0] = t;

	for (int i = 0; i < PlayedCardsNumber; i++)
	{
		readycards.push(PlayedCards[i]);
	}
	return;
}

void Cards::Identifying(struct CARD* decA)
{
	int i, number;
	string ccolor, power;

	ifstream Cardsrecognize;
	Cardsrecognize.open("CardSource.txt", ios::binary);

	if (!Cardsrecognize)// file couldn't be opened
	{
		cout << "Error: file could not be opened" << endl;
	}
	//declaring...

	Cardsrecognize >> i;
	while (i <= 107)
	{

		if (i >= 0 && i <= 39 || i >= 52 && i <= 87)
		{
			Cardsrecognize >> decA[i].Color;
			Cardsrecognize >> decA[i].NUM;
			decA[i].type = "normal";
		}

		else if (i >= 40 && i <= 51 || i >= 88 && i <= 99)
		{
			Cardsrecognize >> decA[i].Color;
			Cardsrecognize >> decA[i].type;
			decA[i].NUM = -1;
		}

		else if (i >= 100 && i <= 107)
		{
			Cardsrecognize >> decA[i].Color;
			Cardsrecognize >> decA[i].type;
			decA[i].NUM = -1;
		}


		Cardsrecognize >> i;
	}
	//int test = 107;
	//cout << endl;
	//cout << "Getting the output : " << decA[test].Color<<' ' << decA[test].NUM <<' '<< decA[test].ref <<' '<< decA[test].type;

	Cardsrecognize.close();
}

void Cards::stackM(struct CARD* arr)
{

	for (int i = 0; i <= 107; i++)
	{
		readycards.push(arr[i].ref);
	}
}

//this function and the next just calls another function which displays the first and second player cards
void Cards::firstPlayercardsH()
{
	firstPlayerCards(cardss);
}

void Cards::secondPlayercardsH()
{
	secondPlayerCards(cardss);
}

void Cards::computercardsH()
{
	computercards(cardss);
}

void info()
{

	cout << "\n*****************************************************************************************************************\n";
	cout << "*                                                                                                               *\n";
	cout << "*                                                                                                               *\n";
	cout << "* Displaying the priority of each mode :                                                                        *\n";
	cout << "*                                                                                                               *\n";
	cout << "*            -Easy Mode : 1- Normal and Power Cards (Random)                                                    *\n*	                  2- Wild cards (Random)                                                                *\n";
	cout << "*                                                                                                               *\n";
	cout << "*            -Normal Mode : 1- Wild cards(Random)                                                               *\n*	                    2- Normal                                                                           *\n";
	cout << "*                                                                                                               *\n";
	cout << "*            -Hard Mode : 1- Power                                                                              *\n*                         2- Wild Plusfour								        *\n*	                  3- Normal						   				*\n*	                  4- Wild Colorchange									*\n";
	cout << "*                                                                                                               *\n";
	cout << "*            -Insane Mode : 1-Power( Changed some probabilities)                                                *\n*			    2- Wild Plusfour									*\n*			    3- Normal cards (Playing on the number to change the color if possible)             *\n*			    4- Wild Colorchange								        *\n";
	cout << "*                                                                                                               *\n";
	cout << "*****************************************************************************************************************\n";
	return;
}
// Computer or Player ? easy - normal - hard - insane
void Decide()
{
	cout << " \n\n Note : " << endl << "      - 'Four' options are avilable for computer : EASY, NORMAL, HARD and INSANE mode!\n      -  Please type small letters only!\n" << endl;
	cout << " Who do you want to play with ? : ( 'computer' - 'secondplayer' ) " << endl << " Your Answer : ";
repeat1:

	cin.getline(choose, 20);

	for (int i = 0; i < 20; i++)
	{
		if (isalpha(choose[i]) && isalpha(choose[strlen(choose) - i - 1]))
		{
			if (strcmp(choose, "secondplayer") == 0 || strcmp(choose, "computer") == 0)
			{
				break;
			}
			else
			{
				cout << " \nPlease enter a correct answer ( computer - secondplayer )" << endl << "\n Your Answer : ";
				goto repeat1;
			}
		}
		else
		{
			cout << " Please enter letters only!\n Your Answer :  " << endl;
			goto repeat1; //re-enters again

		}

	}



	if (strcmp(choose, "computer") == 0)
	{

		char information[15];
		cout << "\n\n Wanna know more info about computer's modes ? : ";
		cout << " Enter Yes or No\n Your Answer : ";
	repeat:

		cin.getline(information, 14);

		for (int i = 0; i < 14; i++)
		{
			if (isalpha(information[i]) && isalpha(information[strlen(information) - i - 1]))
			{
				if (strcmp(information, "Yes") == 0 || strcmp(information, "No") == 0)
				{
					break;
				}
				else
				{
					cout << " \nPlease enter a correct answer ( Yes - No )" << endl << " \n Your Answer : ";
					goto repeat;
				}
			}
			else
			{
				cout << " Please enter letters only!\n Your Answer :  " << endl;
				goto repeat; //re-enters again

			}

		}

		if (strcmp(information, "Yes") == 0)
		{
			info();
		}

		cout << "\n Choose the Difficulty level ( easy - normal - hard - insane )\n Your Answer : ";
	repeat2:

		cin.getline(difficulty, 20);
		for (int i = 0; i < 20; i++)
		{
			if (isalpha(choose[i]) && isalpha(choose[strlen(choose) - i - 1]))
			{
				if (strcmp(difficulty, "easy") == 0 || strcmp(difficulty, "normal") == 0 || strcmp(difficulty, "hard") == 0 || strcmp(difficulty, "insane") == 0)
				{
					break;
				}
				else
				{
					cout << " \nPlease enter a correct answer ( easy - normal - hard - insane )" << endl << " Your Answer : ";
					goto repeat2;
				}
			}
			else
			{
				cout << " Please enter letters only!\n Your Answer  : " << endl;
				goto repeat2; //re-enters again

			}
		}
	}
	cout << "\n Note : \n      Computer's cards will be displayed so we can check of it plays correct or not and how does it play. \n\n";

}

// picking the firstcard

void UNO::Game()
{

	//Adding the values in file

	Playerone.print1(); //Printing Playerone and two cards in First.txt and Second.txt respectively
	Playertwo.print2();



	int firstcard = readycards.peek();

	if (Playerone.len() != 0 || Playertwo.len() != 0) //Just Making sure
	{
		//start == 0 m3naha 2n lesa hnl3b 3la 2wl wr2a khals b3d kda hn8yr l start

		if (firstcard == 100 || firstcard == 102 || firstcard == 104 || firstcard == 106) //if cards == plusfour return it back and pop another one
		{
			//Pick Another card
			int temp = readycards.peek();
			readycards.pop();
			firstcard = readycards.peek();
			readycards.pop();
			readycards.push(temp);

		}
		else
		{
			readycards.pop();
		}
		call.IDH2(firstcard);

		auto end = chrono::steady_clock::now();
		cout << "\n\n  Time required till entering the first input : " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms" << endl;

		Decide();

		if (firstcard >= 0 && firstcard <= 39 || firstcard >= 52 && firstcard <= 87 || firstcard >= 100 && firstcard <= 107) // if normal
		{
			firstplayer(firstcard);
			return;
		}
		else if (firstcard >= 40 && firstcard <= 51 || firstcard >= 88 && firstcard <= 99) // if it was power card ( reverse - skip - plustwo)
		{
			string power;
			ifstream IDfile;
			IDfile.open("IDFILE.txt", ios::binary);
			IDfile >> power >> power;
			if (power == "skip" || power == "reverse")
			{
				if (strcmp(choose, "computer") == 0)
				{
					if (strcmp(difficulty, "normal") == 0)
					{
						computernormal(firstcard);
						return;
					}
					else if (strcmp(difficulty, "hard") == 0)
					{
						computerhard(firstcard);
						return;
					}
					else if (strcmp(difficulty, "easy") == 0)
					{
						computereasy(firstcard);
						return;
					}
					else
					{
						computerInsane(firstcard);
						return;
					}
				}
				else
				{
					secondplayer(firstcard);
					return;
				}

			}
			else //Plustwo
			{
				call.drawH1(2);
				if (strcmp(choose, "computer") == 0)
				{
					if (strcmp(difficulty, "normal") == 0)
					{
						computernormal(firstcard);
						return;
					}
					else if (strcmp(difficulty, "hard") == 0)
					{
						computerhard(firstcard);
						return;
					}
					else if (strcmp(difficulty, "easy") == 0)
					{
						computereasy(firstcard);
						return;
					}
					else
					{
						computerInsane(firstcard);
						return;
					}
				}
				else
				{
					secondplayer(firstcard);
					return;
				}


			}
		}

	}
}

bool checkk(float n) //checks if the number if float or not (returns true if yes)
{
	int x = n;

	float temp = n - x;
	if (temp > 0) {
		return false;
	}
	return true;
}

//firstuser starts to play
void UNO::firstplayer(int refe)
{
	if (Playerone.len() == 0 || Playertwo.len() == 0) //check if the game is over or not
	{
		if (Playerone.len() == 0)
		{
			cout << " **********You Won!********** \n" << endl;
			return;
		}
		else
		{
			cout << " **********Player TWO Won !**********\n" << endl;
			return;
		}
	}

	bool cardscheck = true;


	for (int i = 0; i < PlayedCardsNumber; i++)
	{
		if (PlayedCards[i] == refe)
		{
			i++;
			for (i; i < PlayedCardsNumber; i++)
			{
				if (PlayedCards[i] == refe)
				{
					cardscheck = false;
					break;
				}
				else
				{
					cardscheck = true;
					break;
				}
			}
			break;

		}
		else
		{
			cardscheck = true;
		}
	}
	if (cardscheck)
	{
		PlayedCards[PlayedCardsNumber] = refe;
		PlayedCardsNumber++;
	}


	bool test = false;

	cout << " \n\n>>>>>Your Turn<<<<< \n" << endl;

	Anothertrytest = 0;

Anothertry: //try again after drawing a card

	cout << "********************\n*                  *\n";
	cout << "*  Card on Ground  *";
	cout << " \n*                  *\n       ";
	call.IDH(refe); //prints the ground card and add it to IDFILE.exe so it can be used later
	cout << "*                  *\n" << "********************\n";

	call.firstPlayercardsH();

	if (refe >= 0 && refe <= 39 || refe >= 52 && refe <= 87) //incoming card 'refe' was normal card
	{
		cout << endl;

		//Dlw2ty 3yzyn nakhod ref bta3 2wl card m3ana w nshof ynf3 nl3bo wla la lw la f nakhod card tany w hakza lw mfysh f hn3ml pop mrten

		//Reading first player cards
		ifstream firstplayercards;
		firstplayercards.open("First.txt", ios::binary); //First.exe has the printed reference for each card within the player more simple than using firstplayercards>next.
		int pcr;
		//Reading the ground card
		ifstream IDfile;
		IDfile.open("IDFILE.txt", ios::binary); // As we said: gound card
		string gcc;
		int gcn;
		IDfile >> gcc;
		IDfile >> gcn;
		IDfile.close();

		int i = Playerone.len();

		//Asking for that card to be played

		firstplayercards >> pcr;

		for (int m = 0; m < i; m++) //checking if we have anycard can be played if not draw one card if not then pass the play
		{
			if (call.cardss[pcr].Color == gcc || call.cardss[pcr].NUM == gcn || call.cardss[pcr].type == "colorchange" || call.cardss[pcr].type == "plusfour")
			{
				test = true;
				break;
			}
			else

				firstplayercards >> pcr;
			test = false;
		}

		firstplayercards.close();
		if (test)
		{
			cout << "What card do you want to play ? \n Your Answer :  ";
		repeat1:


			int order;

			while (true) // we have a card
			{
			repeat33:

				cin >> order;
				if (cin.fail())
				{
					cout << " Please enter the order (Integer only)  ";
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n'); //ignoring the coming input and deleting it's buffer as if the user entered any char which takes a greater size than intgers, so we just delete this buffer and let the user re-enter this value.
				}
				else
				{
					if (checkk(order)) //making sure that the user entered an intger
					{
						if (order > 0) //making sure that the input a postive intger
						{
							break;
						}
						else
						{
							cout << " >>Please enter a postive INTGER only:  ";
							goto repeat33; //re-enters again
						}

					}
					else
					{
						cout << " >>Please enter an intger as 5 , 2 not 5.7 or any decimals:  ";
						goto repeat33; //re-enters again
					}

					break;
				}
			}

			if (order > Playerone.len() || order < 0) // Entered a correct order
			{
				cout << "Please enter a correct value between '1' and '" << Playerone.len() << "' \n Your Answer : ";
				goto repeat1;
			}

			ifstream firstplayercards;
			firstplayercards.open("First.txt", ios::binary);

			for (int k = 0; k < order; k++) //picking from the player the chosen card
			{
				firstplayercards >> pcr;
			}
			firstplayercards.close();

			if (call.cardss[pcr].Color == gcc || call.cardss[pcr].NUM == gcn) //Having the same color or number
			{
				if (call.cardss[pcr].NUM == gcn) //If number so play it
				{
					cout << " Card on ground : " << call.cardss[pcr].Color << ' ' << call.cardss[pcr].NUM;
					cout << endl;
					Playerone.del(pcr);
					Playerone.print1();

					ofstream IDfile("IDFILE.txt");
					IDfile << call.cardss[pcr].Color << ' ' << call.cardss[pcr].NUM;
					IDfile.close();

					if (Playerone.len() == 1)
					{

						cout << endl << "\n**********" << "   UNO   " << "**********\n" << endl;

					}
					if (strcmp(choose, "computer") == 0)
					{
						if (strcmp(difficulty, "normal") == 0)
						{
							computernormal(pcr);
							return;
						}
						else if (strcmp(difficulty, "hard") == 0)
						{
							computerhard(pcr);
							return;
						}
						else if (strcmp(difficulty, "easy") == 0)
						{
							computereasy(pcr);
							return;
						}
						else
						{
							computerInsane(pcr);
							return;
						}
					}
					else
					{
						secondplayer(pcr);
						return;
					}
				}

				else // means it's a color
				{
					if (call.cardss[pcr].NUM == -1) // if it was a power card ( skip - reverse - plustwo = -1)
					{
						if (call.cardss[pcr].type == "reverse" || call.cardss[pcr].type == "skip") // replay
						{
							Playerone.del(pcr);
							Playerone.print1();

							if (Playerone.len() == 1)
							{

								cout << endl << "\n**********" << "   UNO   " << "**********\n" << endl;

							}

							firstplayer(pcr);
							return;

						}
						else if (call.cardss[pcr].type == "drawtwo") // draw two cards for the second player and replay
						{
							call.drawH2(2);
							Playerone.del(pcr);
							Playerone.print1();
							if (Playerone.len() == 1)
							{
								;
								cout << endl << "\n**********" << "   UNO   " << "**********\n" << endl;

							}
							firstplayer(pcr);
							return;

						}

						cout << " Card on ground : " << call.cardss[pcr].Color << ' ' << call.cardss[pcr].type; // then it is a normal card
						cout << endl;
						Playerone.del(pcr);
						Playerone.print1();
						ofstream IDfile("IDFILE.txt");
						IDfile << call.cardss[pcr].Color << ' ' << call.cardss[pcr].type;
						IDfile.close();
						if (Playerone.len() == 1)
						{
							cout << endl << "\n**********" << "   UNO   " << "**********" << endl;
						}
						if (strcmp(choose, "computer") == 0) //condition to see who we are playing with
						{
							if (strcmp(difficulty, "normal") == 0)
							{
								computernormal(pcr);
								return;
							}
							else if (strcmp(difficulty, "hard") == 0)
							{
								computerhard(pcr);
								return;
							}
							else if (strcmp(difficulty, "easy") == 0)
							{
								computereasy(pcr);
								return;
							}
							else
							{
								computerInsane(pcr);
								return;
							}
						}
						else
						{
							secondplayer(pcr);
							return;
						}
					}
					else
					{
						cout << " Card on ground : " << call.cardss[pcr].Color << ' ' << call.cardss[pcr].NUM;
						cout << endl;
						Playerone.del(pcr);
						Playerone.print1();

						ofstream IDfile("IDFILE.txt");
						IDfile << call.cardss[pcr].Color << ' ' << call.cardss[pcr].NUM;
						IDfile.close();

						if (Playerone.len() == 1)
						{
							cout << endl << "\n**********" << "   UNO   " << "**********" << endl;
						}
						if (strcmp(choose, "computer") == 0)
						{
							if (strcmp(difficulty, "normal") == 0)
							{
								computernormal(pcr);
								return;
							}
							else if (strcmp(difficulty, "hard") == 0)
							{
								computerhard(pcr);
								return;
							}
							else if (strcmp(difficulty, "easy") == 0)
							{
								computereasy(pcr);
								return;
							}
							else
							{
								computerInsane(pcr);
								return;
							}
						}
						else
						{
							secondplayer(pcr);
							return;
						}
					}
				}


			}
			else if (call.cardss[pcr].Color == "wild") // if not color or number check for colorchange and plusfour
			{
				if (call.cardss[pcr].type == "colorchange") //just del the played card and reprint it to print the new cards in First.txt
				{
					Playerone.del(pcr);
					Playerone.print1();
					goto cc;
				}
				else
				{
					call.drawH2(4);
					Playerone.del(pcr);
					Playerone.print1();
					goto cc; // go to choose the color
				}
			}
			else
			{
				cout << " You can't play this card, try again " << endl; // chose a random card which can't be played
				goto Anothertry;
			}
		}
		else // You don't have anycard to be played then let's draw a card
		{
			if (Anothertrytest == 0) // to make it draw one time only 
			{
				cout << endl;
				cout << " Drawing a card : \n";
				call.drawH1(1);
				cout << endl;

				Anothertrytest++;
				goto Anothertry;
			}
			else // nothing can be played after drawing a card
			{
				if (strcmp(choose, "computer") == 0)
				{
					if (strcmp(difficulty, "normal") == 0)
					{
						computernormal(refe);
						return;
					}
					else if (strcmp(difficulty, "hard") == 0)
					{
						computerhard(refe);
						return;
					}
					else if (strcmp(difficulty, "easy") == 0)
					{
						computereasy(refe);
						return;
					}
					else
					{
						computerInsane(refe);
						return;
					}
				}
				else
				{
					secondplayer(refe);
					return;
				}
			}
		}

	}

	else if (refe >= 40 && refe <= 51 || refe >= 88 && refe <= 99) // Power card ( reverse - skip - plustwo)
	{

		ifstream firstplayercards;
		firstplayercards.open("First.txt", ios::binary);
		int pcr;
		//Reading the ground card
		ifstream IDfile;
		IDfile.open("IDFILE.txt", ios::binary);
		string gcc, gct;
		IDfile >> gcc;
		IDfile >> gct;
		IDfile.close();
		int i = Playerone.len();

		firstplayercards >> pcr;

		for (int m = 0; m < i; m++) // checks if anything can be played 
		{
			if (call.cardss[pcr].Color == gcc || call.cardss[pcr].type == gct || call.cardss[pcr].type == "colorchange" || call.cardss[pcr].type == "plusfour")
			{
				test = true;
				break;
			}
			else
				firstplayercards >> pcr;
			test = false;
		}

		if (test) //same us previous 
		{
			cout << "What card do you want to play ? \n Your Answer :";
		repeat2:


			int order;

			while (true)
			{
			repeat3:

				cin >> order;
				if (cin.fail())
				{
					cout << " Please enter the order (Integer only) \n Your Answer : ";
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n'); //ignoring the coming input and deleting it's buffer as if the user entered any char which takes a greater size than intgers, so we just delete this buffer and let the user re-enter this value.
				}
				else
				{
					if (checkk(order)) //making sure that the user entered an intger
					{
						if (order > 0) //making sure that the input a postive intger
						{
							break;
						}
						else
						{
							cout << " >>Please enter a postive INTGER only\n Your Answer : ";
							goto repeat3; //re-enters again
						}

					}
					else
					{
						cout << " >>Please enter an intger as 5 , 2 not 5.7 or any decimals\n Your Answer : ";
						goto repeat3; //re-enters again
					}

					break;
				}
			}
			if (order > Playerone.len() || order < 0)
			{
				cout << "Please enter a correct value between '1' and '" << Playerone.len() << "' \n Your Answer : ";
				goto repeat2;
			}

			ifstream firstplayercards;
			firstplayercards.open("First.txt", ios::binary);

			for (int k = 0; k < order; k++)
			{
				firstplayercards >> pcr;
			}
			firstplayercards.close();

			if (call.cardss[pcr].Color == gcc) //Comparing the colors
			{
				if (call.cardss[pcr].NUM == -1)
				{
					if (call.cardss[pcr].type == "reverse" || call.cardss[pcr].type == "skip")
					{
						Playerone.del(pcr);
						Playerone.print1();
						if (Playerone.len() == 1)
						{
							cout << endl << "\n**********" << "   UNO   " << "**********" << endl;
						}
						firstplayer(pcr);
						return;

					}
					else if (call.cardss[pcr].type == "drawtwo")
					{
						call.drawH2(2);
						Playerone.del(pcr);
						Playerone.print1();
						if (Playerone.len() == 1)
						{
							cout << endl << "\n**********" << "   UNO   " << "**********" << endl;
						}
						firstplayer(pcr);
						return;

					}
					cout << " Card on ground : " << call.cardss[pcr].Color << ' ' << call.cardss[pcr].type;
					cout << endl;
					Playerone.del(pcr);
					Playerone.print1();
					ofstream IDfile("IDFILE.txt");
					IDfile << call.cardss[pcr].Color << ' ' << call.cardss[pcr].type;
					IDfile.close();
					if (Playerone.len() == 1)
					{
						cout << endl << "\n**********" << "   UNO   " << "**********" << endl;
					}
					if (strcmp(choose, "computer") == 0)
					{
						if (strcmp(difficulty, "normal") == 0)
						{
							computernormal(pcr);
							return;
						}
						else if (strcmp(difficulty, "hard") == 0)
						{
							computerhard(pcr);
							return;
						}
						else if (strcmp(difficulty, "easy") == 0)
						{
							computereasy(pcr);
							return;
						}
						else
						{
							computerInsane(pcr);
							return;
						}
					}
					else
					{
						secondplayer(pcr);
						return;
					}
				}


				else
				{
					cout << " Card on ground : " << call.cardss[pcr].Color << ' ' << call.cardss[pcr].NUM;
					cout << endl;
					Playerone.del(pcr);
					Playerone.print1();
					ofstream IDfile("IDFILE.txt");
					IDfile << call.cardss[pcr].Color << ' ' << call.cardss[pcr].NUM;
					IDfile.close();
					if (Playerone.len() == 1)
					{
						cout << endl << "\n**********" << "   UNO   " << "**********" << endl;
					}
					if (strcmp(choose, "computer") == 0)
					{
						if (strcmp(difficulty, "normal") == 0)
						{
							computernormal(pcr);
							return;
						}
						else if (strcmp(difficulty, "hard") == 0)
						{
							computerhard(pcr);
							return;
						}
						else if (strcmp(difficulty, "easy") == 0)
						{
							computereasy(pcr);
							return;
						}
						else
						{
							computerInsane(pcr);
							return;
						}
					}
					else
					{
						secondplayer(pcr);
						return;
					}
				}
			}

			else if (call.cardss[pcr].type == gct)

			{
				if (call.cardss[pcr].type == "reverse" || call.cardss[pcr].type == "skip")
				{
					Playerone.del(pcr);
					Playerone.print1();
					if (Playerone.len() == 1)
					{
						cout << endl << "\n**********" << "   UNO   " << "**********" << endl;
					}
					firstplayer(pcr);
					return;

				}
				else if (call.cardss[pcr].type == "drawtwo")
				{
					call.drawH2(2);
					Playerone.del(pcr);
					Playerone.print1();
					if (Playerone.len() == 1)
					{
						cout << endl << "\n**********" << "   UNO   " << "**********" << endl;
					}
					firstplayer(pcr);
					return;

				}
			}
			else if (call.cardss[pcr].Color == "wild")
			{
				if (call.cardss[pcr].type == "colorchange")
				{
					Playerone.del(pcr);
					Playerone.print1();
					goto cc;
				}
				else
				{
					call.drawH2(4);
					Playerone.del(pcr);
					Playerone.print1();
					goto cc;
				}
			}
			else
			{
				cout << "\n You can't play this card, try again " << endl; // chose a random card which can't be played
				goto Anothertry;
			}

		}

		else
		{
			if (Anothertrytest == 0)
			{
				cout << endl;
				cout << " Drawing a card : \n";
				call.drawH1(1);
				cout << endl;

				Anothertrytest++;
				goto Anothertry;
			}
			else
			{
				cout << " \n Missed your turn " << endl;
				Anothertrytest = 0;
				if (strcmp(choose, "computer") == 0)
				{
					if (strcmp(difficulty, "normal") == 0)
					{
						computernormal(refe);
						return;
					}
					else if (strcmp(difficulty, "hard") == 0)
					{
						computerhard(refe);
						return;
					}
					else if (strcmp(difficulty, "easy") == 0)
					{
						computereasy(refe);
						return;
					}
					else
					{
						computerInsane(refe);
						return;
					}
				}
				else
				{
					secondplayer(refe);
					return;
				}
			}

		}
		Anothertrytest = 0;
	}
	else if (refe >= 100 && refe <= 107) //wild cards ( plusfour - colorchange)
	{

	cc:

		cout << " What Color do you wish ? \n Your Answer : ";
		char* color = new char[12];

		cin.getline(color, 12);

		for (int i = 0; i < 12; i++)
		{
			if (isalpha(color[i]) && isalpha(color[strlen(color) - i - 1]))
			{
				if (strcmp(color, "red") == 0 || strcmp(color, "blue") == 0 || strcmp(color, "green") == 0 || strcmp(color, "yellow") == 0)
				{
					break;
				}
				else
				{
					cout << " \nPlease enter a correct color as green, yellow, blue, red ( in small letters )\n" << endl;
					goto cc;
				}
			}
			else
			{
				cout << " Please enter letters only!\n " << endl;
				goto cc; //re-enters again

			}
		}

		cout << " Play on the color only " << endl;

		if (strcmp(color, "red") == 0)
		{
			firstplayer(0);
			return;
		}
		else if (strcmp(color, "blue") == 0)
		{
			firstplayer(20);
			return;
		}
		else if (strcmp(color, "yellow") == 0)
		{
			firstplayer(10);
			return;
		}
		else
		{
			firstplayer(30);
			return;
		}

	}
}

void UNO::computerInsane(int refe) //Power > Power from another color > Wild Plusfour > searching for matched numbers > matched colors > wild colorchange
{
	if (Playerone.len() == 0 || Playertwo.len() == 0)
	{
		if (Playerone.len() == 0)
		{
			cout << " **********You Won! **********\n" << endl;
			return;
		}
		else
		{
			cout << " **********Computer  Won !**********\n" << endl;
			return;
		}
	}

	bool cardscheck = true;


	for (int i = 0; i < PlayedCardsNumber; i++) //Adding played cards in array so it can be used again if stack goes empty
	{
		if (PlayedCards[i] == refe)
		{
			i++;
			for (i; i < PlayedCardsNumber; i++)
			{
				if (PlayedCards[i] == refe)
				{
					cardscheck = false;
					break;
				}
				else
				{
					cardscheck = true;
					break;
				}
			}
			break;

		}
		else
		{
			cardscheck = true;
		}
	}
	if (cardscheck)
	{
		PlayedCards[PlayedCardsNumber] = refe;
		PlayedCardsNumber++;
	}
	bool test = false;

	cout << " \n>>>>>Computer's Turn<<<< \n" << endl;

	Anothertrytest2 = 0;
Anothertry:

	cout << "********************\n*                  *\n";
	cout << "*  Card on Ground  *";
	cout << " \n*                  *\n       ";
	call.IDH(refe);
	cout << "*                  *\n" << "********************\n";

	int red, green, blue, yellow, rs, rv, rt, ys, yv, yt, gs, gv, gt, bs, bv, bt, wc, wf, pcr;
	red = green = blue = yellow = rs = rv = rt = ys = yv = yt = gs = gv = gt = bs = bv = bt = wc = wf = 0;
	//3yzyn n3rf m3ana kam card mn kol lon l n2dr nl3bhom

	ifstream secondplayercards;
	secondplayercards.open("Second.txt", ios::binary);

	for (int w = 0; w < Playertwo.len(); w++)
	{
		secondplayercards >> pcr;
		if (call.cardss[pcr].Color == "red")
		{
			if (call.cardss[pcr].NUM == -1)
			{
				if (call.cardss[pcr].type == "skip")
				{
					rs++;
				}
				else if (call.cardss[pcr].type == "reverse")
				{
					rv++;
				}
				else
				{
					rt++;
				}
			}
			else
				red++; //y3ny raakm 3ady  l if statment l fo2 de m3naha power 
		}
		else if (call.cardss[pcr].Color == "green")
		{
			if (call.cardss[pcr].NUM == -1)
			{
				if (call.cardss[pcr].type == "skip")
				{
					gs++;
				}
				else if (call.cardss[pcr].type == "reverse")
				{
					gv++;
				}
				else
				{
					gt++;
				}
			}
			else
				green++; //y3ny raakm 3ady  l if statment l fo2 de m3naha power 
		}
		if (call.cardss[pcr].Color == "yellow")
		{
			if (call.cardss[pcr].NUM == -1)
			{
				if (call.cardss[pcr].type == "skip")
				{
					ys++;
				}
				else if (call.cardss[pcr].type == "reverse")
				{
					yv++;
				}
				else
				{
					yt++;
				}
			}
			else
				yellow++; //y3ny raakm 3ady  l if statment l fo2 de m3naha power 
		}
		else if (call.cardss[pcr].Color == "blue")
		{
			if (call.cardss[pcr].NUM == -1)
			{
				if (call.cardss[pcr].type == "skip")
				{
					bs++;
				}
				else if (call.cardss[pcr].type == "reverse")
				{
					bv++;
				}
				else
				{
					bt++;
				}
			}
			else
				blue++; //y3ny raakm 3ady  l if statment l fo2 de m3naha power 
		}
		else if (call.cardss[pcr].Color == "wild")
		{
			if (call.cardss[pcr].type == "colorchange")
			{
				wc++;
			}
			else
			{
				wf++;
			}
		}
	}
	secondplayercards.close();

	call.secondPlayercardsH();
	//call.computercardsH();

	if (refe >= 0 && refe <= 39 || refe >= 52 && refe <= 87)
	{

		//Dlw2ty 3yzyn nakhod ref bta3 2wl card m3ana w nshof ynf3 nl3bo wla la lw la f nakhod card tany w hakza lw mfysh f hn3ml pop mrten

		//Reading first player cards
		ifstream secondplayercards1;
		secondplayercards1.open("Second.txt", ios::binary);
		//Reading the ground card
		ifstream IDfile;
		IDfile.open("IDFILE.txt", ios::binary);
		string gcc;
		int gcn;
		IDfile >> gcc;
		IDfile >> gcn;
		IDfile.close();
		int i = Playertwo.len();
		secondplayercards1 >> pcr;

		for (int m = 0; m < i; m++)
		{
			if (call.cardss[pcr].Color == gcc || call.cardss[pcr].NUM == gcn || call.cardss[pcr].type == "colorchange" || call.cardss[pcr].type == "plusfour")
			{
				test = true;
				break;
			}
			else
				secondplayercards1 >> pcr;
			test = false;
		}
		secondplayercards1.close();

		if (test)
		{

			ifstream secondplayercards2;
			secondplayercards2.open("Second.txt", ios::binary);
			//Power check (skip - reverse - plustwo) ( will be played if and only if there is another card from the same color or type)
			for (int j = 0; j < i; j++)
			{
				secondplayercards2 >> pcr;
				if (call.cardss[pcr].Color == gcc)
				{
					if (call.cardss[pcr].NUM == -1)
					{
						if (call.cardss[pcr].Color == "red")
						{
							if (red >= 1)
							{
							red1:

								if (call.cardss[pcr].type == "reverse" || call.cardss[pcr].type == "skip")
								{
									Playertwo.del(pcr);
									Playertwo.print2();
									if (Playertwo.len() == 1)
									{
										cout << endl << "\n**********" << "   UNO   " << "**********" << endl;
									}
									secondplayercards2.close();
									computerInsane(pcr);
									return;

								}
								else if (call.cardss[pcr].type == "drawtwo")
								{
									call.drawH1(2);
									Playertwo.del(pcr);
									Playertwo.print2();
									if (Playertwo.len() == 1)
									{
										cout << endl << "\n**********" << "   UNO   " << "**********" << endl;
									}
									secondplayercards2.close();
									computerInsane(pcr);
									return;
								}

							}
							else if (call.cardss[pcr].type == "skip")
							{
								if (gs >= 1 || ys >= 1 || bs >= 1)
								{
									if (gs >= 1)
									{
										if (green >= 1)
										{
											goto red1;
										}
									}
									else if (ys >= 1)
									{
										if (yellow >= 1)
										{
											goto red1;
										}
									}
									else if (bs >= 1)
									{
										if (blue >= 1)
										{
											goto red1;
										}
									}
								}
							}
							else if (call.cardss[pcr].type == "reverse")
							{
								if (gv >= 1 || yv >= 1 || bv >= 1)
								{
									if (gv >= 1)
									{
										if (green >= 1)
										{
											goto red1;
										}
									}
									else if (ys >= 1)
									{
										if (yellow >= 1)
										{
											goto red1;
										}
									}
									else if (bs >= 1)
									{
										if (blue >= 1)
										{
											goto red1;
										}
									}
								}

							}
							else if (call.cardss[pcr].type == "drawtwo")
							{
								if (gt >= 1 || yt >= 1 || bt >= 1)
								{
									if (gt >= 1)
									{
										if (green >= 1)
										{
											goto red1;
										}
									}
									else if (yt >= 1)
									{
										if (yellow >= 1)
										{
											goto red1;
										}
									}
									else if (bt >= 1)
									{
										if (blue >= 1)
										{
											goto red1;
										}
									}
								}
							}

						}

						else if (call.cardss[pcr].Color == "yellow")
						{
							if (yellow >= 1)
							{
							yellow1:

								if (call.cardss[pcr].type == "reverse" || call.cardss[pcr].type == "skip")
								{
									Playertwo.del(pcr);
									Playertwo.print2();
									if (Playertwo.len() == 1)
									{
										cout << endl << "\n**********" << "   UNO   " << "**********" << endl;
									}
									secondplayercards2.close();
									computerInsane(pcr);
									return;
								}
								else if (call.cardss[pcr].type == "drawtwo")
								{
									call.drawH1(2);
									Playertwo.del(pcr);
									Playertwo.print2();
									if (Playertwo.len() == 1)
									{
										cout << endl << "\n**********" << "   UNO   " << "**********" << endl;
									}
									secondplayercards2.close();
									computerInsane(pcr);
									return;
								}

							}
							else if (call.cardss[pcr].type == "skip")
							{
								if (gs >= 1 || rs >= 1 || bs >= 1)
								{
									if (gs >= 1)
									{
										if (green >= 1)
										{
											goto yellow1;
										}
									}
									else if (rs >= 1)
									{
										if (red >= 1)
										{
											goto yellow1;
										}
									}
									else if (bs >= 1)
									{
										if (blue >= 1)
										{
											goto yellow1;
										}
									}
								}
							}
							else if (call.cardss[pcr].type == "reverse")
							{
								if (gv >= 1 || rv >= 1 || bv >= 1)
								{
									if (gv >= 1)
									{
										if (green >= 1)
										{
											goto yellow1;
										}
									}
									else if (rs >= 1)
									{
										if (red >= 1)
										{
											goto yellow1;
										}
									}
									else if (bs >= 1)
									{
										if (blue >= 1)
										{
											goto yellow1;
										}
									}
								}

							}
							else if (call.cardss[pcr].type == "drawtwo")
							{
								if (gt >= 1 || yt >= 1 || bt >= 1)
								{
									if (gt >= 1)
									{
										if (green >= 1)
										{
											goto yellow1;
										}
									}
									else if (rt >= 1)
									{
										if (yellow >= 1)
										{
											goto yellow1;
										}
									}
									else if (bt >= 1)
									{
										if (blue >= 1)
										{
											goto yellow1;
										}
									}
								}
							}

						}

						else if (call.cardss[pcr].Color == "green")
						{

							if (green >= 1)
							{
							green1:

								if (call.cardss[pcr].type == "reverse" || call.cardss[pcr].type == "skip")
								{
									Playertwo.del(pcr);
									Playertwo.print2();
									if (Playertwo.len() == 1)
									{
										cout << endl << "\n**********" << "   UNO   " << "**********" << endl;
									}
									secondplayercards2.close();
									computerInsane(pcr);
									return;

								}
								else if (call.cardss[pcr].type == "drawtwo")
								{
									call.drawH1(2);
									Playertwo.del(pcr);
									Playertwo.print2();
									if (Playertwo.len() == 1)
									{
										cout << endl << "\n**********" << "   UNO   " << "**********" << endl;
									}
									secondplayercards2.close();
									computerInsane(pcr);
									return;
								}

							}
							else if (call.cardss[pcr].type == "skip")
							{
								if (ys >= 1 || rs >= 1 || bs >= 1)
								{
									if (ys >= 1)
									{
										if (yellow >= 1)
										{
											goto green1;
										}
									}
									else if (rs >= 1)
									{
										if (red >= 1)
										{
											goto green1;
										}
									}
									else if (bs >= 1)
									{
										if (blue >= 1)
										{
											goto green1;
										}
									}
								}
							}
							else if (call.cardss[pcr].type == "reverse")
							{
								if (yv >= 1 || rv >= 1 || bv >= 1)
								{
									if (yv >= 1)
									{
										if (yellow >= 1)
										{
											goto green1;
										}
									}
									else if (rs >= 1)
									{
										if (red >= 1)
										{
											goto green1;
										}
									}
									else if (bs >= 1)
									{
										if (blue >= 1)
										{
											goto green1;
										}
									}
								}

							}
							else if (call.cardss[pcr].type == "drawtwo")
							{
								if (rt >= 1 || yt >= 1 || bt >= 1)
								{
									if (rt >= 1)
									{
										if (red >= 1)
										{
											goto green1;
										}
									}
									else if (rt >= 1)
									{
										if (yellow >= 1)
										{
											goto green1;
										}
									}
									else if (bt >= 1)
									{
										if (blue >= 1)
										{
											goto green1;
										}
									}
								}
							}


						}
						else if (call.cardss[pcr].Color == "blue")
						{
							if (blue >= 1)
							{
							blue1:

								if (call.cardss[pcr].type == "reverse" || call.cardss[pcr].type == "skip")
								{
									Playertwo.del(pcr);
									Playertwo.print2();
									if (Playertwo.len() == 1)
									{
										cout << endl << "\n**********" << "   UNO   " << "**********" << endl;
									}
									secondplayercards2.close();
									computerInsane(pcr);
									return;

								}
								else if (call.cardss[pcr].type == "drawtwo")
								{
									call.drawH1(2);
									Playertwo.del(pcr);
									Playertwo.print2();
									if (Playertwo.len() == 1)
									{
										cout << endl << "\n**********" << "   UNO   " << "**********" << endl;
									}
									secondplayercards2.close();
									computerInsane(pcr);
									return;
								}
							}
							else if (call.cardss[pcr].type == "skip")
							{
								if (gs >= 1 || rs >= 1 || ys >= 1)
								{
									if (gs >= 1)
									{
										if (green >= 1)
										{
											goto blue1;
										}
									}
									else if (rs >= 1)
									{
										if (red >= 1)
										{
											goto blue1;
										}
									}
									else if (ys >= 1)
									{
										if (yellow >= 1)
										{
											goto blue1;
										}
									}
								}
							}
							else if (call.cardss[pcr].type == "reverse")
							{
								if (gv >= 1 || rv >= 1 || yv >= 1)
								{
									if (gv >= 1)
									{
										if (green >= 1)
										{
											goto blue1;
										}
									}
									else if (rs >= 1)
									{
										if (red >= 1)
										{
											goto blue1;
										}
									}
									else if (bs >= 1)
									{
										if (yellow >= 1)
										{
											goto blue1;
										}
									}
								}

							}
							else if (call.cardss[pcr].type == "drawtwo")
							{
								if (gt >= 1 || yt >= 1 || yt >= 1)
								{
									if (gt >= 1)
									{
										if (green >= 1)
										{
											goto blue1;
										}
									}
									else if (rt >= 1)
									{
										if (yellow >= 1)
										{
											goto blue1;
										}
									}
									else if (yt >= 1)
									{
										if (blue >= 1)
										{
											goto blue1;
										}
									}
								}
							}
						}

					}

				}
			}
			secondplayercards2.close();

			ifstream secondplayercards3;
			secondplayercards3.open("Second.txt", ios::binary);
			int x;
			//2nd priority for plusfour card
			for (int j = 0; j < i; j++)
			{
				secondplayercards3 >> x;

				if (call.cardss[x].Color == "wild")
				{
					if (call.cardss[x].type == "plusfour")
					{
						call.drawH1(4);
						secondplayercards3.close();
						if (red >= 1)
						{
							Playertwo.del(x);
							Playertwo.print2();
							secondplayercards3.close();
							computerInsane(0);
							return;
						}
						else if (yellow >= 1)
						{
							Playertwo.del(x);
							Playertwo.print2();
							secondplayercards3.close();
							computerInsane(10);
							return;
						}
						else if (blue >= 1)
						{
							Playertwo.del(x);
							Playertwo.print2();
							secondplayercards3.close();
							computerInsane(20);
							return;
						}
						else
						{
							Playertwo.del(x);
							Playertwo.print2();
							secondplayercards3.close();
							computerInsane(30);
							return;
						}
					}

				}
			}
			secondplayercards3.close();

			ifstream secondplayercards6;
			secondplayercards6.open("Second.txt", ios::binary);
			for (int l = 0; l < i; l++) //Numbers
			{
				secondplayercards6 >> pcr;
				if (call.cardss[pcr].NUM == gcn)
				{
					cout << " Card on ground : " << call.cardss[pcr].Color << ' ' << call.cardss[pcr].NUM;
					cout << endl;
					Playertwo.del(pcr);
					Playertwo.print2();
					ofstream IDfile("IDFILE.txt");
					IDfile << call.cardss[pcr].Color << ' ' << call.cardss[pcr].NUM;
					IDfile.close();
					if (Playertwo.len() == 1)
					{
						cout << endl << "**********" << "   UNO   " << "**********" << endl;
					}
					secondplayercards6.close();
					firstplayer(pcr);
					return;
				}
			}
			secondplayercards6.close();

			ifstream secondplayercards4;
			secondplayercards4.open("Second.txt", ios::binary);
			//3rd priority for normal cards
			for (int j = 0; j < i; j++)
			{
				secondplayercards4 >> pcr;

				if (call.cardss[pcr].Color == gcc || call.cardss[pcr].NUM == gcn)
				{
					if (call.cardss[pcr].NUM == gcn)
					{
						cout << " Card on ground : " << call.cardss[pcr].Color << ' ' << call.cardss[pcr].NUM;
						cout << endl;
						Playertwo.del(pcr);
						Playertwo.print2();
						ofstream IDfile("IDFILE.txt");
						IDfile << call.cardss[pcr].Color << ' ' << call.cardss[pcr].NUM;
						IDfile.close();
						if (Playertwo.len() == 1)
						{
							cout << endl << "\n**********" << "   UNO   " << "**********" << endl;
						}
						secondplayercards4.close();
						firstplayer(pcr);
						return;
					}

					else
					{
						if (call.cardss[pcr].NUM == -1)
						{
							if (call.cardss[pcr].type == "reverse" || call.cardss[pcr].type == "skip")
							{
								Playertwo.del(pcr);
								Playertwo.print2();
								if (Playertwo.len() == 1)
								{
									cout << endl << "\n**********" << "   UNO   " << "**********" << endl;
								}
								secondplayercards4.close();
								computerInsane(pcr);
								return;

							}
							else if (call.cardss[pcr].type == "drawtwo")
							{
								call.drawH1(2);
								Playertwo.del(pcr);
								Playertwo.print2();
								if (Playertwo.len() == 1)
								{
									cout << endl << "\n**********" << "   UNO   " << "**********" << endl;
								}
								secondplayercards4.close();
								computerInsane(pcr);
								return;

							}

							cout << " Card on ground : " << call.cardss[pcr].Color << ' ' << call.cardss[pcr].type;
							cout << endl;
							Playertwo.del(pcr);
							Playertwo.print2();
							ofstream IDfile("IDFILE.txt");
							IDfile << call.cardss[pcr].Color << ' ' << call.cardss[pcr].type;
							IDfile.close();
							if (Playertwo.len() == 1)
							{
								cout << endl << "\n**********" << "   UNO   " << "**********" << endl;
							}
							secondplayercards4.close();
							firstplayer(pcr);
							return;
						}
						else
						{
							cout << " Card on ground : " << call.cardss[pcr].Color << ' ' << call.cardss[pcr].NUM;
							cout << endl;
							Playertwo.del(pcr);
							Playertwo.print2();
							ofstream IDfile("IDFILE.txt");
							IDfile << call.cardss[pcr].Color << ' ' << call.cardss[pcr].NUM;
							IDfile.close();
							if (Playertwo.len() == 1)
							{
								cout << endl << "\n**********" << "   UNO   " << "**********" << endl;
							}
							secondplayercards4.close();
							firstplayer(pcr);
							return;
						}
					}


				}
			}
			secondplayercards4.close();

			ifstream secondplayercards5;
			secondplayercards5.open("Second.txt", ios::binary);
			//last priority for colorchange
			for (int k = 0; k < i; k++)
			{
				secondplayercards5 >> x;

				if (call.cardss[x].Color == "wild")
				{
					if (call.cardss[x].type == "colorchange")
					{
						secondplayercards5.close();
						if (red >= 1)
						{
							Playertwo.del(x);
							Playertwo.print2();
							secondplayercards5.close();
							computerInsane(0);
							return;
						}
						else if (yellow >= 1)
						{
							Playertwo.del(x);
							Playertwo.print2();
							secondplayercards5.close();
							computerInsane(10);
							return;
						}
						else if (blue >= 1)
						{
							Playertwo.del(x);
							Playertwo.print2();
							secondplayercards5.close();
							computerInsane(20);
							return;
						}
						else
						{
							Playertwo.del(x);
							Playertwo.print2();
							secondplayercards5.close();
							computerInsane(30);
							return;
						}
					}
				}
			}
			secondplayercards5.close();
		}
		else
		{
			if (Anothertrytest2 == 0)
			{
				cout << endl;
				cout << " Drawing a card : \n";
				call.drawH2(1);
				cout << endl;

				Anothertrytest2++;
				goto Anothertry;
			}
			else
			{
				cout << " \n Computer's Round Missed " << endl;
				Anothertrytest2 = 0;
				firstplayer(refe);
				return;
			}

		}
		Anothertrytest2 = 0;

	}

	else if (refe >= 40 && refe <= 51 || refe >= 88 && refe <= 99)
	{

		ifstream secondplayercards1;
		secondplayercards1.open("Second.txt", ios::binary);
		int pcr;
		//Reading the ground card
		ifstream IDfile;
		IDfile.open("IDFILE.txt", ios::binary);
		string gcc, gct;
		IDfile >> gcc;
		IDfile >> gct;
		IDfile.close();
		int i = Playertwo.len();

		secondplayercards1 >> pcr;

		for (int m = 0; m < i; m++)
		{
			if (call.cardss[pcr].Color == gcc || call.cardss[pcr].type == gct || call.cardss[pcr].type == "colorchange" || call.cardss[pcr].type == "plusfour")
			{
				test = true;
				break;
			}
			else
				secondplayercards1 >> pcr;
			test = false;
		}
		secondplayercards1.close();

		if (test)
		{
		repeat4:

			ifstream secondplayercards2;
			secondplayercards2.open("Second.txt", ios::binary);
			// power check
			for (int j = 0; j < i; j++)
			{
				secondplayercards2 >> pcr;
				if (call.cardss[pcr].Color == gcc)
				{
					if (call.cardss[pcr].NUM == -1)
					{
						if (call.cardss[pcr].Color == "red")
						{
							if (red >= 1)
							{
							red2:

								if (call.cardss[pcr].type == "reverse" || call.cardss[pcr].type == "skip")
								{
									Playertwo.del(pcr);
									Playertwo.print2();
									if (Playertwo.len() == 1)
									{
										cout << endl << "\n**********" << "   UNO   " << "**********" << endl;
									}
									secondplayercards2.close();
									computerInsane(pcr);
									return;

								}
								else if (call.cardss[pcr].type == "drawtwo")
								{
									call.drawH1(2);
									Playertwo.del(pcr);
									Playertwo.print2();
									if (Playertwo.len() == 1)
									{
										cout << endl << "\n**********" << "   UNO   " << "**********" << endl;
									}
									secondplayercards2.close();
									computerInsane(pcr);
									return;
								}

							}
							else if (call.cardss[pcr].type == "skip")
							{
								if (gs >= 1 || ys >= 1 || bs >= 1)
								{
									if (gs >= 1)
									{
										if (green >= 1)
										{
											goto red2;
										}
									}
									else if (ys >= 1)
									{
										if (yellow >= 1)
										{
											goto red2;
										}
									}
									else if (bs >= 1)
									{
										if (blue >= 1)
										{
											goto red2;
										}
									}
								}
							}
							else if (call.cardss[pcr].type == "reverse")
							{
								if (gv >= 1 || yv >= 1 || bv >= 1)
								{
									if (gv >= 1)
									{
										if (green >= 1)
										{
											goto red2;
										}
									}
									else if (ys >= 1)
									{
										if (yellow >= 1)
										{
											goto red2;
										}
									}
									else if (bs >= 1)
									{
										if (blue >= 1)
										{
											goto red2;
										}
									}
								}

							}
							else if (call.cardss[pcr].type == "drawtwo")
							{
								if (gt >= 1 || yt >= 1 || bt >= 1)
								{
									if (gt >= 1)
									{
										if (green >= 1)
										{
											goto red2;
										}
									}
									else if (yt >= 1)
									{
										if (yellow >= 1)
										{
											goto red2;
										}
									}
									else if (bt >= 1)
									{
										if (blue >= 1)
										{
											goto red2;
										}
									}
								}
							}

						}

						else if (call.cardss[pcr].Color == "yellow")
						{
							if (yellow >= 1)
							{
							yellow2:

								if (call.cardss[pcr].type == "reverse" || call.cardss[pcr].type == "skip")
								{
									Playertwo.del(pcr);
									Playertwo.print2();
									if (Playertwo.len() == 1)
									{
										cout << endl << "\n**********" << "   UNO   " << "**********" << endl;
									}
									secondplayercards2.close();
									computerInsane(pcr);
									return;

								}
								else if (call.cardss[pcr].type == "drawtwo")
								{
									call.drawH1(2);
									Playertwo.del(pcr);
									Playertwo.print2();
									if (Playertwo.len() == 1)
									{
										cout << endl << "\n**********" << "   UNO   " << "**********" << endl;
									}
									secondplayercards2.close();
									computerInsane(pcr);
									return;
								}

							}
							else if (call.cardss[pcr].type == "skip")
							{
								if (gs >= 1 || rs >= 1 || bs >= 1)
								{
									if (gs >= 1)
									{
										if (green >= 1)
										{
											goto yellow2;
										}
									}
									else if (rs >= 1)
									{
										if (red >= 1)
										{
											goto yellow2;
										}
									}
									else if (bs >= 1)
									{
										if (blue >= 1)
										{
											goto yellow2;
										}
									}
								}
							}
							else if (call.cardss[pcr].type == "reverse")
							{
								if (gv >= 1 || rv >= 1 || bv >= 1)
								{
									if (gv >= 1)
									{
										if (green >= 1)
										{
											goto yellow2;
										}
									}
									else if (rs >= 1)
									{
										if (red >= 1)
										{
											goto yellow2;
										}
									}
									else if (bs >= 1)
									{
										if (blue >= 1)
										{
											goto yellow2;
										}
									}
								}

							}
							else if (call.cardss[pcr].type == "drawtwo")
							{
								if (gt >= 1 || yt >= 1 || bt >= 1)
								{
									if (gt >= 1)
									{
										if (green >= 1)
										{
											goto yellow2;
										}
									}
									else if (rt >= 1)
									{
										if (yellow >= 1)
										{
											goto yellow2;
										}
									}
									else if (bt >= 1)
									{
										if (blue >= 1)
										{
											goto yellow2;
										}
									}
								}
							}

						}

						else if (call.cardss[pcr].Color == "green")
						{

							if (green >= 1)
							{
							green2:

								if (call.cardss[pcr].type == "reverse" || call.cardss[pcr].type == "skip")
								{
									Playertwo.del(pcr);
									Playertwo.print2();
									if (Playertwo.len() == 1)
									{
										cout << endl << "\n**********" << "   UNO   " << "**********" << endl;
									}
									secondplayercards2.close();
									computerInsane(pcr);
									return;

								}
								else if (call.cardss[pcr].type == "drawtwo")
								{
									call.drawH1(2);
									Playertwo.del(pcr);
									Playertwo.print2();
									if (Playertwo.len() == 1)
									{
										cout << endl << "\n**********" << "   UNO   " << "**********" << endl;
									}
									secondplayercards2.close();
									computerInsane(pcr);
									return;
								}

							}
							else if (call.cardss[pcr].type == "skip")
							{
								if (ys >= 1 || rs >= 1 || bs >= 1)
								{
									if (ys >= 1)
									{
										if (yellow >= 1)
										{
											goto green2;
										}
									}
									else if (rs >= 1)
									{
										if (red >= 1)
										{
											goto green2;
										}
									}
									else if (bs >= 1)
									{
										if (blue >= 1)
										{
											goto green2;
										}
									}
								}
							}
							else if (call.cardss[pcr].type == "reverse")
							{
								if (yv >= 1 || rv >= 1 || bv >= 1)
								{
									if (yv >= 1)
									{
										if (yellow >= 1)
										{
											goto green2;
										}
									}
									else if (rs >= 1)
									{
										if (red >= 1)
										{
											goto green2;
										}
									}
									else if (bs >= 1)
									{
										if (blue >= 1)
										{
											goto green2;
										}
									}
								}

							}
							else if (call.cardss[pcr].type == "drawtwo")
							{
								if (rt >= 1 || yt >= 1 || bt >= 1)
								{
									if (rt >= 1)
									{
										if (red >= 1)
										{
											goto green2;
										}
									}
									else if (rt >= 1)
									{
										if (yellow >= 1)
										{
											goto green2;
										}
									}
									else if (bt >= 1)
									{
										if (blue >= 1)
										{
											goto green2;
										}
									}
								}
							}


						}
						else if (call.cardss[pcr].Color == "blue")
						{
							if (blue >= 1)
							{
							blue2:

								if (call.cardss[pcr].type == "reverse" || call.cardss[pcr].type == "skip")
								{
									Playertwo.del(pcr);
									Playertwo.print2();
									if (Playertwo.len() == 1)
									{
										cout << endl << "\n**********" << "   UNO   " << "**********" << endl;
									}
									secondplayercards2.close();
									computerInsane(pcr);
									return;

								}
								else if (call.cardss[pcr].type == "drawtwo")
								{
									call.drawH1(2);
									Playertwo.del(pcr);
									Playertwo.print2();
									if (Playertwo.len() == 1)
									{
										cout << endl << "\n**********" << "   UNO   " << "**********" << endl;
									}
									secondplayercards2.close();
									computerInsane(pcr);
									return;
								}
							}
							else if (call.cardss[pcr].type == "skip")
							{
								if (gs >= 1 || rs >= 1 || ys >= 1)
								{
									if (gs >= 1)
									{
										if (green >= 1)
										{
											goto blue2;
										}
									}
									else if (rs >= 1)
									{
										if (red >= 1)
										{
											goto blue2;
										}
									}
									else if (ys >= 1)
									{
										if (yellow >= 1)
										{
											goto blue2;
										}
									}
								}
							}
							else if (call.cardss[pcr].type == "reverse")
							{
								if (gv >= 1 || rv >= 1 || yv >= 1)
								{
									if (gv >= 1)
									{
										if (green >= 1)
										{
											goto blue2;
										}
									}
									else if (rs >= 1)
									{
										if (red >= 1)
										{
											goto blue2;
										}
									}
									else if (bs >= 1)
									{
										if (yellow >= 1)
										{
											goto blue2;
										}
									}
								}

							}
							else if (call.cardss[pcr].type == "drawtwo")
							{
								if (gt >= 1 || yt >= 1 || yt >= 1)
								{
									if (gt >= 1)
									{
										if (green >= 1)
										{
											goto blue2;
										}
									}
									else if (rt >= 1)
									{
										if (yellow >= 1)
										{
											goto blue2;
										}
									}
									else if (yt >= 1)
									{
										if (blue >= 1)
										{
											goto blue2;
										}
									}
								}
							}
						}

					}

				}
			}
			secondplayercards2.close();

			ifstream secondplayercards3;
			secondplayercards3.open("Second.txt", ios::binary);
			int x;
			//plus four
			for (int j = 0; j < i; j++)
			{
				secondplayercards3 >> x;

				if (call.cardss[x].Color == "wild")
				{
					if (call.cardss[x].type == "plusfour")
					{
						call.drawH1(4);
						secondplayercards3.close();
						if (red >= 1)
						{
							Playertwo.del(x);
							Playertwo.print2();
							secondplayercards3.close();
							computerInsane(0);
							return;
						}
						else if (yellow >= 1)
						{
							Playertwo.del(x);
							Playertwo.print2();
							secondplayercards3.close();
							computerInsane(10);
							return;
						}
						else if (blue >= 1)
						{
							Playertwo.del(x);
							Playertwo.print2();
							secondplayercards3.close();
							computerInsane(20);
							return;
						}
						else
						{
							Playertwo.del(x);
							Playertwo.print2();
							secondplayercards3.close();
							computerInsane(30);
							return;
						}
					}

				}
			}
			secondplayercards3.close();

			ifstream secondplayercards4;
			secondplayercards4.open("Second.txt", ios::binary);
			//normal cards ( color + number)
			for (int j = 0; j < i; j++)
			{
				secondplayercards4 >> pcr;


				if (call.cardss[pcr].Color == gcc)
				{
					if (call.cardss[pcr].NUM == -1)
					{
						if (call.cardss[pcr].type == "reverse" || call.cardss[pcr].type == "skip")
						{
							Playertwo.del(pcr);
							Playertwo.print2();
							if (Playertwo.len() == 1)
							{
								cout << endl << "**********" << "   UNO   " << "**********" << endl;
							}
							secondplayercards4.close();
							computerInsane(pcr);
							return;

						}
						else if (call.cardss[pcr].type == "drawtwo")
						{
							call.drawH1(2);
							Playertwo.del(pcr);
							Playertwo.print2();
							if (Playertwo.len() == 1)
							{
								cout << endl << "**********" << "   UNO   " << "**********" << endl;
							}
							secondplayercards4.close();
							computerInsane(pcr);
							return;

						}
						cout << " Card on ground : " << call.cardss[pcr].Color << ' ' << call.cardss[pcr].type;
						cout << endl;
						Playertwo.del(pcr);
						Playertwo.print2();
						ofstream IDfile("IDFILE.txt");
						IDfile << call.cardss[pcr].Color << ' ' << call.cardss[pcr].type;
						IDfile.close();
						if (Playertwo.len() == 1)
						{
							cout << endl << "**********" << "   UNO   " << "**********" << endl;
						}
						secondplayercards4.close();
						firstplayer(pcr);
						return;
					}

					else
					{
						cout << " Card on ground : " << call.cardss[pcr].Color << ' ' << call.cardss[pcr].NUM;
						cout << endl;
						Playertwo.del(pcr);
						Playertwo.print2();
						ofstream IDfile("IDFILE.txt");
						IDfile << call.cardss[pcr].Color << ' ' << call.cardss[pcr].NUM;
						IDfile.close();
						if (Playertwo.len() == 1)
						{
							cout << endl << "**********" << "   UNO   " << "**********" << endl;
						}
						secondplayercards4.close();
						firstplayer(pcr);
						return;
					}
				}
				else if (call.cardss[pcr].type == gct)
				{
					if (call.cardss[pcr].type == "reverse" || call.cardss[pcr].type == "skip")
					{
						Playertwo.del(pcr);
						Playertwo.print2();
						if (Playertwo.len() == 1)
						{
							cout << endl << "**********" << "   UNO   " << "**********" << endl;
						}
						secondplayercards4.close();
						computerInsane(pcr);
						return;

					}
					else if (call.cardss[pcr].type == "drawtwo")
					{
						call.drawH1(2);
						Playertwo.del(pcr);
						Playertwo.print2();
						if (Playertwo.len() == 1)
						{
							cout << endl << "**********" << "   UNO   " << "**********" << endl;
						}
						secondplayercards4.close();
						computerInsane(pcr);
						return;

					}
				}

			}
			secondplayercards4.close();

			ifstream secondplayercards5;
			secondplayercards5.open("Second.txt", ios::binary);
			//last priority for colorchange
			for (int k = 0; k < i; k++)
			{
				secondplayercards5 >> x;

				if (call.cardss[x].Color == "wild")
				{
					if (call.cardss[x].type == "colorchange")
					{
						secondplayercards5.close();
						if (red >= 1)
						{
							Playertwo.del(x);
							Playertwo.print2();
							secondplayercards5.close();
							computerInsane(0);
							return;
						}
						else if (yellow >= 1)
						{
							Playertwo.del(x);
							Playertwo.print2();
							secondplayercards5.close();
							computerInsane(10);
							return;
						}
						else if (blue >= 1)
						{
							Playertwo.del(x);
							Playertwo.print2();
							secondplayercards5.close();
							computerInsane(20);
							return;
						}
						else
						{
							Playertwo.del(x);
							Playertwo.print2();
							secondplayercards5.close();
							computerInsane(30);
							return;
						}
					}
				}
			}
			secondplayercards5.close();
		}
		else
		{
			if (Anothertrytest2 == 0)
			{
				cout << endl;
				cout << " Drawing a card : \n";
				call.drawH2(1);
				cout << endl;

				Anothertrytest2++;
				goto Anothertry;
			}
			else
			{
				cout << " Computer's Round Missed : " << endl;
				Anothertrytest2 = 0;
				firstplayer(refe);
				return;
			}
			Anothertrytest2 = 0;
		}
	}

	else if (refe >= 100 && refe <= 107)
	{
	ccc:

		cout << " What Color do you wish ? : ";
		char* color = new char[12];
		cin.getline(color, 12);

		for (int i = 0; i < 12; i++)
		{
			if (isalpha(color[i]) && isalpha(color[strlen(color) - i - 1]))
			{
				if (strcmp(color, "red") == 0 || strcmp(color, "blue") == 0 || strcmp(color, "green") == 0 || strcmp(color, "yellow") == 0)
				{
					break;
				}
				else
				{
					cout << " \nPlease enter a correct color as green, yellow, blue, red" << endl;
					goto ccc;
				}
			}
			else
			{
				cout << " Please enter letters only! : " << endl;
				goto ccc; //re-enters again

			}
		}

		cout << " Play on the color only " << endl;

		if (strcmp(color, "red") == 0)
		{
			computerInsane(0);
			return;
		}
		else if (strcmp(color, "blue") == 0)
		{
			computerInsane(20);
			return;
		}
		else if (strcmp(color, "yellow") == 0)
		{
			computerInsane(10);
			return;
		}
		else
		{
			computerInsane(30);
			return;
		}

	}
}

void UNO::computerhard(int refe) // Power(skip-reverse-Plustwo) if it doesn't have any another card to play then moves to the next step > Plusfour > normalcards color or number (random) > colorchange
{
	if (Playerone.len() == 0 || Playertwo.len() == 0)
	{
		if (Playerone.len() == 0)
		{
			cout << " **********You Won!********** \n" << endl;
			return;
		}
		else
		{
			cout << "**********Computer  Won !**********\n" << endl;
			return;
		}
	}
	bool cardscheck = true;


	for (int i = 0; i < PlayedCardsNumber; i++)
	{
		if (PlayedCards[i] == refe)
		{
			i++;
			for (i; i < PlayedCardsNumber; i++)
			{
				if (PlayedCards[i] == refe)
				{
					cardscheck = false;
					break;
				}
				else
				{
					cardscheck = true;
					break;
				}
			}
			break;

		}
		else
		{
			cardscheck = true;
		}
	}
	if (cardscheck)
	{
		PlayedCards[PlayedCardsNumber] = refe;
		PlayedCardsNumber++;
	}
	bool test = false;

	cout << " \n>>>>>Computer's Turn<<<< \n" << endl;

	Anothertrytest2 = 0;
Anothertry:

	cout << "********************\n*                  *\n";
	cout << "*  Card on Ground  *";
	cout << " \n*                  *\n       ";
	call.IDH(refe);
	cout << "*                  *\n" << "********************\n";

	int red, green, blue, yellow, rs, rv, rt, ys, yv, yt, gs, gv, gt, bs, bv, bt, wc, wf, pcr;
	red = green = blue = yellow = rs = rv = rt = ys = yv = yt = gs = gv = gt = bs = bv = bt = wc = wf = 0;
	//3yzyn n3rf m3ana kam card mn kol lon l n2dr nl3bhom

	ifstream secondplayercards;
	secondplayercards.open("Second.txt", ios::binary);

	for (int w = 0; w < Playertwo.len(); w++)
	{
		secondplayercards >> pcr;
		if (call.cardss[pcr].Color == "red")
		{
			if (call.cardss[pcr].NUM == -1)
			{
				if (call.cardss[pcr].type == "skip")
				{
					rs++;
				}
				else if (call.cardss[pcr].type == "reverse")
				{
					rv++;
				}
				else
				{
					rt++;
				}
			}
			else
				red++; //y3ny raakm 3ady  l if statment l fo2 de m3naha power 
		}
		else if (call.cardss[pcr].Color == "green")
		{
			if (call.cardss[pcr].NUM == -1)
			{
				if (call.cardss[pcr].type == "skip")
				{
					gs++;
				}
				else if (call.cardss[pcr].type == "reverse")
				{
					gv++;
				}
				else
				{
					gt++;
				}
			}
			else
				green++; //y3ny raakm 3ady  l if statment l fo2 de m3naha power 
		}
		if (call.cardss[pcr].Color == "yellow")
		{
			if (call.cardss[pcr].NUM == -1)
			{
				if (call.cardss[pcr].type == "skip")
				{
					ys++;
				}
				else if (call.cardss[pcr].type == "reverse")
				{
					yv++;
				}
				else
				{
					yt++;
				}
			}
			else
				yellow++; //y3ny raakm 3ady  l if statment l fo2 de m3naha power 
		}
		else if (call.cardss[pcr].Color == "blue")
		{
			if (call.cardss[pcr].NUM == -1)
			{
				if (call.cardss[pcr].type == "skip")
				{
					bs++;
				}
				else if (call.cardss[pcr].type == "reverse")
				{
					bv++;
				}
				else
				{
					bt++;
				}
			}
			else
				blue++; //y3ny raakm 3ady  l if statment l fo2 de m3naha power 
		}
		else if (call.cardss[pcr].Color == "wild")
		{
			if (call.cardss[pcr].type == "colorchange")
			{
				wc++;
			}
			else
			{
				wf++;
			}
		}
	}
	secondplayercards.close();

	call.secondPlayercardsH();
	//call.computercardsH();

	if (refe >= 0 && refe <= 39 || refe >= 52 && refe <= 87)
	{

		//Dlw2ty 3yzyn nakhod ref bta3 2wl card m3ana w nshof ynf3 nl3bo wla la lw la f nakhod card tany w hakza lw mfysh f hn3ml pop mrten

		//Reading first player cards
		ifstream secondplayercards1;
		secondplayercards1.open("Second.txt", ios::binary);
		//Reading the ground card
		ifstream IDfile;
		IDfile.open("IDFILE.txt", ios::binary);
		string gcc;
		int gcn;
		IDfile >> gcc;
		IDfile >> gcn;
		IDfile.close();
		int i = Playertwo.len();
		secondplayercards1 >> pcr;

		for (int m = 0; m < i; m++)
		{
			if (call.cardss[pcr].Color == gcc || call.cardss[pcr].NUM == gcn || call.cardss[pcr].type == "colorchange" || call.cardss[pcr].type == "plusfour")
			{
				test = true;
				break;
			}
			else
				secondplayercards1 >> pcr;
			test = false;
		}
		secondplayercards1.close();

		if (test)
		{

			ifstream secondplayercards2;
			secondplayercards2.open("Second.txt", ios::binary);
			//Power check (skip - reverse - plustwo) ( will be played if and only if there is another card from the same color or type)
			for (int j = 0; j < i; j++)
			{
				secondplayercards2 >> pcr;
				if (call.cardss[pcr].Color == gcc)
				{
					if (call.cardss[pcr].NUM == -1)
					{
						if (call.cardss[pcr].Color == "red")
						{
							if (red >= 1)
							{
								if (call.cardss[pcr].type == "reverse" || call.cardss[pcr].type == "skip")
								{
									Playertwo.del(pcr);
									Playertwo.print2();
									if (Playertwo.len() == 1)
									{
										cout << endl << "\n**********" << "   UNO   " << "**********" << endl;
									}
									secondplayercards2.close();
									computerhard(pcr);
									return;

								}
								else if (call.cardss[pcr].type == "drawtwo")
								{
									call.drawH1(2);
									Playertwo.del(pcr);
									Playertwo.print2();
									if (Playertwo.len() == 1)
									{
										cout << endl << "\n**********" << "   UNO   " << "**********" << endl;
									}
									secondplayercards2.close();
									computerhard(pcr);
									return;
								}

							}
						}

						else if (call.cardss[pcr].Color == "yellow")
						{
							if (yellow >= 1)
							{
								if (call.cardss[pcr].type == "reverse" || call.cardss[pcr].type == "skip")
								{
									Playertwo.del(pcr);
									Playertwo.print2();
									if (Playertwo.len() == 1)
									{
										cout << endl << "\n**********" << "   UNO   " << "**********" << endl;
									}
									secondplayercards2.close();
									computerhard(pcr);
									return;

								}
								else if (call.cardss[pcr].type == "drawtwo")
								{
									call.drawH1(2);
									Playertwo.del(pcr);
									Playertwo.print2();
									if (Playertwo.len() == 1)
									{
										cout << endl << "\n**********" << "   UNO   " << "**********" << endl;
									}
									secondplayercards2.close();
									computerhard(pcr);
									return;
								}

							}

						}
						else if (call.cardss[pcr].Color == "green")
						{
							if (green >= 1)
							{
								if (call.cardss[pcr].type == "reverse" || call.cardss[pcr].type == "skip")
								{
									Playertwo.del(pcr);
									Playertwo.print2();
									if (Playertwo.len() == 1)
									{
										cout << endl << "\n**********" << "   UNO   " << "**********" << endl;
									}
									secondplayercards2.close();
									computerhard(pcr);
									return;

								}
								else if (call.cardss[pcr].type == "drawtwo")
								{
									call.drawH1(2);
									Playertwo.del(pcr);
									Playertwo.print2();
									if (Playertwo.len() == 1)
									{
										cout << endl << "\n**********" << "   UNO   " << "**********" << endl;
									}
									secondplayercards2.close();
									computerhard(pcr);
									return;
								}

							}
						}
						else if (call.cardss[pcr].Color == "blue")
						{
							if (blue >= 1)
							{
								if (call.cardss[pcr].type == "reverse" || call.cardss[pcr].type == "skip")
								{
									Playertwo.del(pcr);
									Playertwo.print2();
									if (Playertwo.len() == 1)
									{
										cout << endl << "\n**********" << "   UNO   " << "**********" << endl;
									}
									secondplayercards2.close();
									computerhard(pcr);
									return;

								}
								else if (call.cardss[pcr].type == "drawtwo")
								{
									call.drawH1(2);
									Playertwo.del(pcr);
									Playertwo.print2();
									if (Playertwo.len() == 1)
									{
										cout << endl << "\n**********" << "   UNO   " << "**********" << endl;
									}
									secondplayercards2.close();
									computerhard(pcr);
									return;
								}
							}
						}

					}

				}
			}
			secondplayercards2.close();

			ifstream secondplayercards3;
			secondplayercards3.open("Second.txt", ios::binary);
			int x;
			//2nd priority for plusfour card
			for (int j = 0; j < i; j++)
			{
				secondplayercards3 >> x;

				if (call.cardss[x].Color == "wild")
				{
					if (call.cardss[x].type == "plusfour")
					{
						call.drawH1(4);
						secondplayercards3.close();
						if (red >= 1)
						{
							Playertwo.del(x);
							Playertwo.print2();
							secondplayercards3.close();
							computerhard(0);
							return;
						}
						else if (yellow >= 1)
						{
							Playertwo.del(x);
							Playertwo.print2();
							secondplayercards3.close();
							computerhard(10);
							return;
						}
						else if (blue >= 1)
						{
							Playertwo.del(x);
							Playertwo.print2();
							secondplayercards3.close();
							computerhard(20);
							return;
						}
						else
						{
							Playertwo.del(x);
							Playertwo.print2();
							secondplayercards3.close();
							computerhard(30);
							return;
						}
					}

				}
			}
			secondplayercards3.close();

			ifstream secondplayercards4;
			secondplayercards4.open("Second.txt", ios::binary);
			//3rd priority for normal cards
			for (int j = 0; j < i; j++)
			{
				secondplayercards4 >> pcr;

				if (call.cardss[pcr].Color == gcc || call.cardss[pcr].NUM == gcn)
				{
					if (call.cardss[pcr].NUM == gcn)
					{
						cout << " Card on ground : " << call.cardss[pcr].Color << ' ' << call.cardss[pcr].NUM;
						cout << endl;
						Playertwo.del(pcr);
						Playertwo.print2();
						ofstream IDfile("IDFILE.txt");
						IDfile << call.cardss[pcr].Color << ' ' << call.cardss[pcr].NUM;
						IDfile.close();
						if (Playertwo.len() == 1)
						{
							cout << endl << "\n**********" << "   UNO   " << "**********" << endl;
						}
						secondplayercards4.close();
						firstplayer(pcr);
						return;
					}

					else
					{
						if (call.cardss[pcr].NUM == -1)
						{
							if (call.cardss[pcr].type == "reverse" || call.cardss[pcr].type == "skip")
							{
								Playertwo.del(pcr);
								Playertwo.print2();
								if (Playertwo.len() == 1)
								{
									cout << endl << "\n**********" << "   UNO   " << "**********" << endl;
								}
								secondplayercards4.close();
								computerhard(pcr);
								return;

							}
							else if (call.cardss[pcr].type == "drawtwo")
							{
								call.drawH1(2);
								Playertwo.del(pcr);
								Playertwo.print2();
								if (Playertwo.len() == 1)
								{
									cout << endl << "\n**********" << "   UNO   " << "**********" << endl;
								}
								secondplayercards4.close();
								computerhard(pcr);
								return;

							}

							cout << " Card on ground : " << call.cardss[pcr].Color << ' ' << call.cardss[pcr].type;
							cout << endl;
							Playertwo.del(pcr);
							Playertwo.print2();
							ofstream IDfile("IDFILE.txt");
							IDfile << call.cardss[pcr].Color << ' ' << call.cardss[pcr].type;
							IDfile.close();
							if (Playertwo.len() == 1)
							{
								cout << endl << "\n**********" << "   UNO   " << "**********" << endl;
							}
							secondplayercards4.close();
							firstplayer(pcr);
							return;
						}
						else
						{
							cout << " Card on ground : " << call.cardss[pcr].Color << ' ' << call.cardss[pcr].NUM;
							cout << endl;
							Playertwo.del(pcr);
							Playertwo.print2();
							ofstream IDfile("IDFILE.txt");
							IDfile << call.cardss[pcr].Color << ' ' << call.cardss[pcr].NUM;
							IDfile.close();
							if (Playertwo.len() == 1)
							{
								cout << endl << "\n**********" << "   UNO   " << "**********" << endl;
							}
							secondplayercards4.close();
							firstplayer(pcr);
							return;
						}
					}


				}
			}
			secondplayercards4.close();

			ifstream secondplayercards5;
			secondplayercards5.open("Second.txt", ios::binary);
			//last priority for colorchange
			for (int k = 0; k < i; k++)
			{
				secondplayercards5 >> x;

				if (call.cardss[x].Color == "wild")
				{
					if (call.cardss[x].type == "colorchange")
					{
						secondplayercards5.close();
						if (red >= 1)
						{
							Playertwo.del(x);
							Playertwo.print2();
							secondplayercards5.close();
							computerhard(0);
							return;
						}
						else if (yellow >= 1)
						{
							Playertwo.del(x);
							Playertwo.print2();
							secondplayercards5.close();
							computerhard(10);
							return;
						}
						else if (blue >= 1)
						{
							Playertwo.del(x);
							Playertwo.print2();
							secondplayercards5.close();
							computerhard(20);
							return;
						}
						else
						{
							Playertwo.del(x);
							Playertwo.print2();
							secondplayercards5.close();
							computerhard(30);
							return;
						}
					}
				}
			}
			secondplayercards5.close();
		}
		else
		{
			if (Anothertrytest2 == 0)
			{
				cout << endl;
				cout << " Drawing a card : \n";
				call.drawH2(1);
				cout << endl;

				Anothertrytest2++;
				goto Anothertry;
			}
			else
			{
				cout << " \n Computer's Round Missed " << endl;
				Anothertrytest2 = 0;
				firstplayer(refe);
				return;
			}

		}
		Anothertrytest2 = 0;

	}

	else if (refe >= 40 && refe <= 51 || refe >= 88 && refe <= 99)
	{

		ifstream secondplayercards1;
		secondplayercards1.open("Second.txt", ios::binary);
		int pcr;
		//Reading the ground card
		ifstream IDfile;
		IDfile.open("IDFILE.txt", ios::binary);
		string gcc, gct;
		IDfile >> gcc;
		IDfile >> gct;
		IDfile.close();
		int i = Playertwo.len();

		secondplayercards1 >> pcr;

		for (int m = 0; m < i; m++)
		{
			if (call.cardss[pcr].Color == gcc || call.cardss[pcr].type == gct || call.cardss[pcr].type == "colorchange" || call.cardss[pcr].type == "plusfour")
			{
				test = true;
				break;
			}
			else
				secondplayercards1 >> pcr;
			test = false;
		}
		secondplayercards1.close();

		if (test)
		{
		repeat4:

			ifstream secondplayercards2;
			secondplayercards2.open("Second.txt", ios::binary);
			// power check
			for (int j = 0; j < i; j++)
			{
				secondplayercards2 >> pcr;
				if (call.cardss[pcr].Color == gcc)
				{
					if (call.cardss[pcr].NUM == -1)
					{
						if (call.cardss[pcr].Color == "red")
						{
							if (red >= 1)
							{
								if (call.cardss[pcr].type == "reverse" || call.cardss[pcr].type == "skip")
								{
									Playertwo.del(pcr);
									Playertwo.print2();
									if (Playertwo.len() == 1)
									{
										cout << endl << "\n**********" << "   UNO   " << "**********" << endl;
									}
									secondplayercards2.close();
									computerhard(pcr);
									return;

								}
								else if (call.cardss[pcr].type == "drawtwo")
								{
									call.drawH1(2);
									Playertwo.del(pcr);
									Playertwo.print2();
									if (Playertwo.len() == 1)
									{
										cout << endl << "\n**********" << "   UNO   " << "**********" << endl;
									}
									secondplayercards2.close();
									computerhard(pcr);
									return;
								}

							}
						}

						else if (call.cardss[pcr].Color == "yellow")
						{
							if (yellow >= 1)
							{
								if (call.cardss[pcr].type == "reverse" || call.cardss[pcr].type == "skip")
								{
									Playertwo.del(pcr);
									Playertwo.print2();
									if (Playertwo.len() == 1)
									{
										cout << endl << "\n**********" << "   UNO   " << "**********" << endl;
									}
									secondplayercards2.close();
									computerhard(pcr);
									return;
								}
								else if (call.cardss[pcr].type == "drawtwo")
								{
									call.drawH1(2);
									Playertwo.del(pcr);
									Playertwo.print2();
									if (Playertwo.len() == 1)
									{
										cout << endl << "\n**********" << "   UNO   " << "**********" << endl;
									}
									secondplayercards2.close();
									computerhard(pcr);
									return;
								}

							}

						}
						else if (call.cardss[pcr].Color == "green")
						{
							if (green >= 1)
							{
								if (call.cardss[pcr].type == "reverse" || call.cardss[pcr].type == "skip")
								{
									Playertwo.del(pcr);
									Playertwo.print2();
									if (Playertwo.len() == 1)
									{
										cout << endl << "\n**********" << "   UNO   " << "**********" << endl;
									}
									secondplayercards2.close();
									computerhard(pcr);
									return;
								}
								else if (call.cardss[pcr].type == "drawtwo")
								{
									call.drawH1(2);
									Playertwo.del(pcr);
									Playertwo.print2();
									if (Playertwo.len() == 1)
									{
										cout << endl << "\n**********" << "   UNO   " << "**********" << endl;
									}
									secondplayercards2.close();
									computerhard(pcr);
									return;
								}

							}
						}
						else if (call.cardss[pcr].Color == "blue")
						{
							if (blue >= 1)
							{
								if (call.cardss[pcr].type == "reverse" || call.cardss[pcr].type == "skip")
								{
									Playertwo.del(pcr);
									Playertwo.print2();
									if (Playertwo.len() == 1)
									{
										cout << endl << "\n**********" << "   UNO   " << "**********" << endl;
									}
									secondplayercards2.close();
									computerhard(pcr);
									return;
								}
								else if (call.cardss[pcr].type == "drawtwo")
								{
									call.drawH1(2);
									Playertwo.del(pcr);
									Playertwo.print2();
									if (Playertwo.len() == 1)
									{
										cout << endl << "\n**********" << "   UNO   " << "**********" << endl;
									}
									secondplayercards2.close();
									computerhard(pcr);
									return;
								}
							}
						}

					}

				}
			}
			secondplayercards2.close();

			ifstream secondplayercards3;
			secondplayercards3.open("Second.txt", ios::binary);
			int x;
			//plus four
			for (int j = 0; j < i; j++)
			{
				secondplayercards3 >> x;

				if (call.cardss[x].Color == "wild")
				{
					if (call.cardss[x].type == "plusfour")
					{
						call.drawH1(4);
						secondplayercards3.close();
						if (red >= 1)
						{
							Playertwo.del(x);
							Playertwo.print2();
							secondplayercards3.close();
							computerhard(0);
							return;
						}
						else if (yellow >= 1)
						{
							Playertwo.del(x);
							Playertwo.print2();
							secondplayercards3.close();
							computerhard(10);
							return;
						}
						else if (blue >= 1)
						{
							Playertwo.del(x);
							Playertwo.print2();
							secondplayercards3.close();
							computerhard(20);
							return;
						}
						else
						{
							Playertwo.del(x);
							Playertwo.print2();
							secondplayercards3.close();
							computerhard(30);
							return;
						}
					}

				}
			}
			secondplayercards3.close();


			ifstream secondplayercards4;
			secondplayercards4.open("Second.txt", ios::binary);
			//normal cards ( color + number)
			for (int j = 0; j < i; j++)
			{
				secondplayercards4 >> pcr;


				if (call.cardss[pcr].Color == gcc)
				{
					if (call.cardss[pcr].NUM == -1)
					{
						if (call.cardss[pcr].type == "reverse" || call.cardss[pcr].type == "skip")
						{
							Playertwo.del(pcr);
							Playertwo.print2();
							if (Playertwo.len() == 1)
							{
								cout << endl << "\n**********" << "   UNO   " << "**********" << endl;
							}
							secondplayercards4.close();
							computerhard(pcr);
							return;

						}
						else if (call.cardss[pcr].type == "drawtwo")
						{
							call.drawH1(2);
							Playertwo.del(pcr);
							Playertwo.print2();
							if (Playertwo.len() == 1)
							{
								cout << endl << "\n**********" << "   UNO   " << "**********" << endl;
							}
							secondplayercards4.close();
							computerhard(pcr);
							return;

						}
						cout << " Card on ground : " << call.cardss[pcr].Color << ' ' << call.cardss[pcr].type;
						cout << endl;
						Playertwo.del(pcr);
						Playertwo.print2();
						ofstream IDfile("IDFILE.txt");
						IDfile << call.cardss[pcr].Color << ' ' << call.cardss[pcr].type;
						IDfile.close();
						if (Playertwo.len() == 1)
						{
							cout << endl << "\n**********" << "   UNO   " << "**********" << endl;
						}
						secondplayercards4.close();
						firstplayer(pcr);
						return;
					}

					else
					{
						cout << " Card on ground : " << call.cardss[pcr].Color << ' ' << call.cardss[pcr].NUM;
						cout << endl;
						Playertwo.del(pcr);
						Playertwo.print2();
						ofstream IDfile("IDFILE.txt");
						IDfile << call.cardss[pcr].Color << ' ' << call.cardss[pcr].NUM;
						IDfile.close();
						if (Playertwo.len() == 1)
						{
							cout << endl << "\n**********" << "   UNO   " << "**********" << endl;
						}
						secondplayercards4.close();
						firstplayer(pcr);
						return;
					}
				}
				else if (call.cardss[pcr].type == gct)
				{
					if (call.cardss[pcr].type == "reverse" || call.cardss[pcr].type == "skip")
					{
						Playertwo.del(pcr);
						Playertwo.print2();
						if (Playertwo.len() == 1)
						{
							cout << endl << "\n**********" << "   UNO   " << "**********" << endl;
						}
						secondplayercards4.close();
						computerhard(pcr);
						return;

					}
					else if (call.cardss[pcr].type == "drawtwo")
					{
						call.drawH1(2);
						Playertwo.del(pcr);
						Playertwo.print2();
						if (Playertwo.len() == 1)
						{
							cout << endl << "\n**********" << "   UNO   " << "**********" << endl;
						}
						secondplayercards4.close();
						computerhard(pcr);
						return;

					}
				}

			}
			secondplayercards4.close();

			ifstream secondplayercards5;
			secondplayercards5.open("Second.txt", ios::binary);
			//last priority for colorchange
			for (int k = 0; k < i; k++)
			{
				secondplayercards5 >> x;

				if (call.cardss[x].Color == "wild")
				{
					if (call.cardss[x].type == "colorchange")
					{
						secondplayercards5.close();
						if (red >= 1)
						{
							Playertwo.del(x);
							Playertwo.print2();
							secondplayercards5.close();
							computerhard(0);
							return;
						}
						else if (yellow >= 1)
						{
							Playertwo.del(x);
							Playertwo.print2();
							secondplayercards5.close();
							computerhard(10);
							return;
						}
						else if (blue >= 1)
						{
							Playertwo.del(x);
							Playertwo.print2();
							secondplayercards5.close();
							computerhard(20);
							return;
						}
						else
						{
							Playertwo.del(x);
							Playertwo.print2();
							secondplayercards5.close();
							computerhard(30);
							return;
						}
					}
				}
			}
			secondplayercards5.close();
		}
		else
		{
			if (Anothertrytest2 == 0)
			{
				cout << endl;
				cout << " Drawing a card : \n";
				call.drawH2(1);
				cout << endl;

				Anothertrytest2++;
				goto Anothertry;
			}
			else
			{
				cout << " Computer's Round Missed : " << endl;
				Anothertrytest2 = 0;
				firstplayer(refe);
				return;
			}
			Anothertrytest2 = 0;
		}
	}

	else if (refe >= 100 && refe <= 107)
	{
	ccc:

		cout << " What Color do you wish ? : ";
		char* color = new char[12];
		cin.getline(color, 12);

		for (int i = 0; i < 12; i++)
		{
			if (isalpha(color[i]) && isalpha(color[strlen(color) - i - 1]))
			{
				if (strcmp(color, "red") == 0 || strcmp(color, "blue") == 0 || strcmp(color, "green") == 0 || strcmp(color, "yellow") == 0)
				{
					break;
				}
				else
				{
					cout << " \nPlease enter a correct color as green, yellow, blue, red" << endl;
					goto ccc;
				}
			}
			else
			{
				cout << " Please enter letters only! : " << endl;
				goto ccc; //re-enters again

			}
		}

		cout << " Play on the color only " << endl;

		if (strcmp(color, "red") == 0)
		{
			computerhard(0);
			return;
		}
		else if (strcmp(color, "blue") == 0)
		{
			computerhard(20);
			return;
		}
		else if (strcmp(color, "yellow") == 0)
		{
			computerhard(10);
			return;
		}
		else
		{
			computerhard(30);
			return;
		}

	}
}

void UNO::computernormal(int refe) // Checks for wild cards (Plusfour & colorchange) > Normal cards
{
	if (Playerone.len() == 0 || Playertwo.len() == 0)
	{
		if (Playerone.len() == 0)
		{
			cout << " **********You Won! **********\n" << endl;
			return;
		}
		else
		{
			cout << "**********Computer Won !**********\n" << endl;
			return;
		}
	}

	bool cardscheck = true;


	for (int i = 0; i < PlayedCardsNumber; i++)
	{
		if (PlayedCards[i] == refe)
		{
			i++;
			for (i; i < PlayedCardsNumber; i++)
			{
				if (PlayedCards[i] == refe)
				{
					cardscheck = false;
					break;
				}
				else
				{
					cardscheck = true;
					break;
				}
			}
			break;

		}
		else
		{
			cardscheck = true;
		}
	}
	if (cardscheck)
	{
		PlayedCards[PlayedCardsNumber] = refe;
		PlayedCardsNumber++;
	}

	bool test = false;

	cout << " \n>>>>>Computer's Turn<<<< \n" << endl;

	Anothertrytest2 = 0;
Anothertry:

	cout << "********************\n*                  *\n";
	cout << "*  Card on Ground  *";
	cout << " \n*                  *\n       ";
	call.IDH(refe);
	cout << "*                  *\n" << "********************\n";

	int red, green, blue, yellow, rs, rv, rt, ys, yv, yt, gs, gv, gt, bs, bv, bt, wc, wf, pcr;
	red = green = blue = yellow = rs = rv = rt = ys = yv = yt = gs = gv = gt = bs = bv = bt = wc = wf = 0;
	//3yzyn n3rf m3ana kam card mn kol lon l n2dr nl3bhom

	ifstream secondplayercards;
	secondplayercards.open("Second.txt", ios::binary);

	for (int w = 0; w < Playertwo.len(); w++)
	{
		secondplayercards >> pcr;
		if (call.cardss[pcr].Color == "red")
		{
			if (call.cardss[pcr].NUM == -1)
			{
				if (call.cardss[pcr].type == "skip")
				{
					rs++;
				}
				else if (call.cardss[pcr].type == "reverse")
				{
					rv++;
				}
				else
				{
					rt++;
				}
			}
			else
				red++; //y3ny raakm 3ady  l if statment l fo2 de m3naha power 
		}
		else if (call.cardss[pcr].Color == "green")
		{
			if (call.cardss[pcr].NUM == -1)
			{
				if (call.cardss[pcr].type == "skip")
				{
					gs++;
				}
				else if (call.cardss[pcr].type == "reverse")
				{
					gv++;
				}
				else
				{
					gt++;
				}
			}
			else
				green++; //y3ny raakm 3ady  l if statment l fo2 de m3naha power 
		}
		if (call.cardss[pcr].Color == "yellow")
		{
			if (call.cardss[pcr].NUM == -1)
			{
				if (call.cardss[pcr].type == "skip")
				{
					ys++;
				}
				else if (call.cardss[pcr].type == "reverse")
				{
					yv++;
				}
				else
				{
					yt++;
				}
			}
			else
				yellow++; //y3ny raakm 3ady  l if statment l fo2 de m3naha power 
		}
		else if (call.cardss[pcr].Color == "blue")
		{
			if (call.cardss[pcr].NUM == -1)
			{
				if (call.cardss[pcr].type == "skip")
				{
					bs++;
				}
				else if (call.cardss[pcr].type == "reverse")
				{
					bv++;
				}
				else
				{
					bt++;
				}
			}
			else
				blue++; //y3ny raakm 3ady  l if statment l fo2 de m3naha power 
		}
		else if (call.cardss[pcr].Color == "wild")
		{
			if (call.cardss[pcr].type == "colorchange")
			{
				wc++;
			}
			else
			{
				wf++;
			}
		}
	}
	secondplayercards.close();
	//call.computercardsH();
	call.secondPlayercardsH();

	if (refe >= 0 && refe <= 39 || refe >= 52 && refe <= 87)
	{

		//Dlw2ty 3yzyn nakhod ref bta3 2wl card m3ana w nshof ynf3 nl3bo wla la lw la f nakhod card tany w hakza lw mfysh f hn3ml pop mrten

		//Reading first player cards
		ifstream secondplayercardsss;
		secondplayercardsss.open("Second.txt", ios::binary);
		//Reading the ground card
		ifstream IDfile;
		IDfile.open("IDFILE.txt", ios::binary);
		string gcc;
		int gcn;
		IDfile >> gcc;
		IDfile >> gcn;
		IDfile.close();
		int i = Playertwo.len();
		secondplayercardsss >> pcr;

		for (int m = 0; m < i; m++)
		{
			if (call.cardss[pcr].Color == gcc || call.cardss[pcr].NUM == gcn || call.cardss[pcr].type == "colorchange" || call.cardss[pcr].type == "plusfour")
			{
				test = true;
				break;
			}
			else
				secondplayercardsss >> pcr;
			test = false;
		}
		secondplayercardsss.close();

		if (test)
		{
			ifstream secondplayercards;
			secondplayercards.open("Second.txt", ios::binary);
			int x;
			for (int j = 0; j < i; j++)
			{
				secondplayercards >> x;

				if (call.cardss[x].Color == "wild")
				{
					if (call.cardss[x].type == "plusfour")
					{
						call.drawH1(4);
						secondplayercards.close();
						if (red >= 1)
						{
							Playertwo.del(x);
							Playertwo.print2();
							computernormal(0);
							return;
						}
						else if (yellow >= 1)
						{
							Playertwo.del(x);
							Playertwo.print2();
							computernormal(10);
							return;
						}
						else if (blue >= 1)
						{
							Playertwo.del(x);
							Playertwo.print2();
							computernormal(20);
							return;
						}
						else
						{
							Playertwo.del(x);
							Playertwo.print2();
							computernormal(30);
							return;
						}
					}
					else
					{
						secondplayercards.close();
						if (red >= 1)
						{
							Playertwo.del(x);
							Playertwo.print2();
							computernormal(0);
							return;
						}
						else if (yellow >= 1)
						{
							Playertwo.del(x);
							Playertwo.print2();
							computernormal(10);
							return;
						}
						else if (blue >= 1)
						{
							Playertwo.del(x);
							Playertwo.print2();
							computernormal(20);
							return;
						}
						else
						{
							Playertwo.del(x);
							Playertwo.print2();
							computernormal(30);
							return;
						}
					}
				}
			}
			secondplayercards.close();

			ifstream secondplayercardss;
			secondplayercardss.open("Second.txt", ios::binary);

			for (int j = 0; j < i; j++)
			{
				secondplayercardss >> pcr;

				if (call.cardss[pcr].Color == gcc || call.cardss[pcr].NUM == gcn)
				{
					if (call.cardss[pcr].NUM == gcn)
					{
						cout << " Card on ground : " << call.cardss[pcr].Color << ' ' << call.cardss[pcr].NUM;
						cout << endl;
						Playertwo.del(pcr);
						Playertwo.print2();
						ofstream IDfile("IDFILE.txt");
						IDfile << call.cardss[pcr].Color << ' ' << call.cardss[pcr].NUM;
						IDfile.close();
						if (Playertwo.len() == 1)
						{
							cout << endl << "\n**********" << "   UNO   " << "**********" << endl;
						}
						firstplayer(pcr);
						return;
					}

					else
					{
						if (call.cardss[pcr].NUM == -1)
						{
							if (call.cardss[pcr].type == "reverse" || call.cardss[pcr].type == "skip")
							{
								Playertwo.del(pcr);
								Playertwo.print2();
								if (Playertwo.len() == 1)
								{
									cout << endl << "\n**********" << "   UNO   " << "**********" << endl;
								}
								computernormal(pcr);
								return;

							}
							else if (call.cardss[pcr].type == "drawtwo")
							{
								call.drawH1(2);
								Playertwo.del(pcr);
								Playertwo.print2();
								if (Playertwo.len() == 1)
								{
									cout << endl << "\n**********" << "   UNO   " << "**********" << endl;
								}
								computernormal(pcr);
								return;

							}

							cout << " Card on ground : " << call.cardss[pcr].Color << ' ' << call.cardss[pcr].type;
							cout << endl;
							Playertwo.del(pcr);
							Playertwo.print2();
							ofstream IDfile("IDFILE.txt");
							IDfile << call.cardss[pcr].Color << ' ' << call.cardss[pcr].type;
							IDfile.close();
							if (Playertwo.len() == 1)
							{
								cout << endl << "\n**********" << "   UNO   " << "**********" << endl;
							}
							firstplayer(pcr);
							return;
						}
						else
						{
							cout << " Card on ground : " << call.cardss[pcr].Color << ' ' << call.cardss[pcr].NUM;
							cout << endl;
							Playertwo.del(pcr);
							Playertwo.print2();
							ofstream IDfile("IDFILE.txt");
							IDfile << call.cardss[pcr].Color << ' ' << call.cardss[pcr].NUM;
							IDfile.close();
							if (Playertwo.len() == 1)
							{
								cout << endl << "\n**********" << "   UNO   " << "**********" << endl;
							}
							firstplayer(pcr);
							return;
						}
					}


				}
			}
			secondplayercardss.close();
		}
		else
		{
			if (Anothertrytest2 == 0)
			{
				cout << endl;
				cout << " Drawing a card : \n";
				call.drawH2(1);
				cout << endl;

				Anothertrytest2++;
				goto Anothertry;
			}
			else
			{
				cout << " \n Round Missed " << endl;
				Anothertrytest2 = 0;
				firstplayer(refe);
				return;
			}

		}
		Anothertrytest2 = 0;

	}

	else if (refe >= 40 && refe <= 51 || refe >= 88 && refe <= 99)
	{

		ifstream secondplayercards;
		secondplayercards.open("Second.txt", ios::binary);
		int pcr;
		//Reading the ground card
		ifstream IDfile;
		IDfile.open("IDFILE.txt", ios::binary);
		string gcc, gct;
		IDfile >> gcc;
		IDfile >> gct;
		IDfile.close();
		int i = Playertwo.len();

		secondplayercards >> pcr;

		for (int m = 0; m < i; m++)
		{
			if (call.cardss[pcr].Color == gcc || call.cardss[pcr].type == gct || call.cardss[pcr].type == "colorchange" || call.cardss[pcr].type == "plusfour")
			{
				test = true;
				break;
			}
			else
				secondplayercards >> pcr;
			test = false;
		}
		if (test)
		{
		repeat4:

			ifstream secondplayercards;
			secondplayercards.open("Second.txt", ios::binary);
			int x;
			for (int j = 0; j < i; j++)
			{
				secondplayercards >> x;

				if (call.cardss[x].Color == "wild")
				{
					if (call.cardss[x].type == "plusfour")
					{
						call.drawH1(4);
						secondplayercards.close();
						if (red >= 1)
						{
							Playertwo.del(x);
							Playertwo.print2();
							computernormal(0);
							return;
						}
						else if (yellow >= 1)
						{
							Playertwo.del(x);
							Playertwo.print2();
							computernormal(10);
							return;
						}
						else if (blue >= 1)
						{
							Playertwo.del(x);
							Playertwo.print2();
							computernormal(20);
							return;
						}
						else
						{
							Playertwo.del(x);
							Playertwo.print2();
							computernormal(30);
							return;
						}
					}
					else
					{
						secondplayercards.close();
						if (red >= 1)
						{
							Playertwo.del(x);
							Playertwo.print2();
							computernormal(0);
							return;
						}
						else if (yellow >= 1)
						{
							Playertwo.del(x);
							Playertwo.print2();
							computernormal(10);
							return;
						}
						else if (blue >= 1)
						{
							Playertwo.del(x);
							Playertwo.print2();
							computernormal(20);
							return;
						}
						else
						{
							Playertwo.del(x);
							Playertwo.print2();
							computernormal(30);
							return;
						}
					}
				}
			}
			secondplayercards.close();


			ifstream secondplayercardss;
			secondplayercardss.open("Second.txt", ios::binary);

			for (int j = 0; j < i; j++)
			{
				secondplayercardss >> pcr;


				if (call.cardss[pcr].Color == gcc)
				{
					if (call.cardss[pcr].NUM == -1)
					{
						if (call.cardss[pcr].type == "reverse" || call.cardss[pcr].type == "skip")
						{
							Playertwo.del(pcr);
							Playertwo.print2();
							if (Playertwo.len() == 1)
							{
								cout << endl << "\n**********" << "   UNO   " << "**********" << endl;
							}
							secondplayercards.close();
							computernormal(pcr);
							return;

						}
						else if (call.cardss[pcr].type == "drawtwo")
						{
							call.drawH1(2);
							Playertwo.del(pcr);
							Playertwo.print2();
							if (Playertwo.len() == 1)
							{
								cout << endl << "\n**********" << "   UNO   " << "**********" << endl;
							}
							secondplayercards.close();
							computernormal(pcr);
							return;
						}
						cout << " Card on ground : " << call.cardss[pcr].Color << ' ' << call.cardss[pcr].type;
						cout << endl;
						Playertwo.del(pcr);
						Playertwo.print2();
						ofstream IDfile("IDFILE.txt");
						IDfile << call.cardss[pcr].Color << ' ' << call.cardss[pcr].type;
						IDfile.close();
						if (Playertwo.len() == 1)
						{
							cout << endl << "\n**********" << "   UNO   " << "**********" << endl;
						}
						secondplayercards.close();
						firstplayer(pcr);
						return;
					}

					else
					{
						cout << " Card on ground : " << call.cardss[pcr].Color << ' ' << call.cardss[pcr].NUM;
						cout << endl;
						Playertwo.del(pcr);
						Playertwo.print2();
						ofstream IDfile("IDFILE.txt");
						IDfile << call.cardss[pcr].Color << ' ' << call.cardss[pcr].NUM;
						IDfile.close();
						if (Playertwo.len() == 1)
						{
							cout << endl << "\n**********" << "   UNO   " << "**********" << endl;
						}
						secondplayercards.close();
						firstplayer(pcr);
						return;
					}
				}
				else if (call.cardss[pcr].type == gct)
				{
					if (call.cardss[pcr].type == "reverse" || call.cardss[pcr].type == "skip")
					{
						Playertwo.del(pcr);
						Playertwo.print2();
						if (Playertwo.len() == 1)
						{
							cout << endl << "\n**********" << "   UNO   " << "**********" << endl;
						}
						secondplayercards.close();
						computernormal(pcr);
						return;

					}
					else if (call.cardss[pcr].type == "drawtwo")
					{
						call.drawH1(2);
						Playertwo.del(pcr);
						Playertwo.print2();
						if (Playertwo.len() == 1)
						{
							cout << endl << "\n**********" << "   UNO   " << "**********" << endl;
						}
						secondplayercards.close();
						computernormal(pcr);
						return;
					}
				}
				else if (call.cardss[pcr].Color == "wild")
				{
					if (call.cardss[pcr].type == "colorchange")
					{
						Playertwo.del(pcr);
						Playertwo.print2();
						secondplayercards.close();
						goto ccc;
					}
					else
					{
						call.drawH1(4);
						Playertwo.del(pcr);
						Playertwo.print2();
						secondplayercards.close();
						goto ccc;
					}
				}

			}
			secondplayercards.close();
		}
		else
		{
			if (Anothertrytest2 == 0)
			{
				cout << endl;
				cout << " Drawing a card : \n";
				call.drawH2(1);
				cout << endl;

				Anothertrytest2++;
				goto Anothertry;
			}
			else
			{
				cout << " Round passed : " << endl;
				Anothertrytest2 = 0;
				firstplayer(refe);
				return;
			}
			Anothertrytest2 = 0;
		}
	}

	else if (refe >= 100 && refe <= 107)
	{
	ccc:

		cout << " What Color do you wish ? : ";
		char* color = new char[12];
		cin.getline(color, 12);

		for (int i = 0; i < 12; i++)
		{
			if (isalpha(color[i]) && isalpha(color[strlen(color) - i - 1]))
			{
				if (strcmp(color, "red") == 0 || strcmp(color, "blue") == 0 || strcmp(color, "green") == 0 || strcmp(color, "yellow") == 0)
				{
					break;
				}
				else
				{
					cout << " \nPlease enter a correct color as green, yellow, blue, red" << endl;
					goto ccc;
				}
			}
			else
			{
				cout << " Please enter letters only! : " << endl;
				goto ccc; //re-enters again

			}
		}

		cout << " Play on the color only " << endl;

		if (strcmp(color, "red") == 0)
		{
			computernormal(0);
			return;
		}
		else if (strcmp(color, "blue") == 0)
		{
			computernormal(20);
			return;
		}
		else if (strcmp(color, "yellow") == 0)
		{
			computernormal(10);
			return;
		}
		else
		{
			computernormal(30);
			return;
		}

	}
}

void UNO::computereasy(int refe) // check for normal cards (random) > colorchange > plusfour
{
	if (Playerone.len() == 0 || Playertwo.len() == 0)
	{
		if (Playerone.len() == 0)
		{
			cout << " **********You Won! **********\n" << endl;
			return;
		}
		else
		{
			cout << "**********Computer Won !**********\n" << endl;
			return;
		}
	}

	bool cardscheck = true;


	for (int i = 0; i < PlayedCardsNumber; i++)
	{
		if (PlayedCards[i] == refe)
		{
			i++;
			for (i; i < PlayedCardsNumber; i++)
			{
				if (PlayedCards[i] == refe)
				{
					cardscheck = false;
					break;
				}
				else
				{
					cardscheck = true;
					break;
				}
			}
			break;

		}
		else
		{
			cardscheck = true;
		}
	}
	if (cardscheck)
	{
		PlayedCards[PlayedCardsNumber] = refe;
		PlayedCardsNumber++;
	}

	bool test = false;

	cout << " \n>>>>>Computer's Turn<<<< \n" << endl;

	Anothertrytest2 = 0;
Anothertry:

	cout << "********************\n*                  *\n";
	cout << "*  Card on Ground  *";
	cout << " \n*                  *\n       ";
	call.IDH(refe);
	cout << "*                  *\n" << "********************\n";

	int red, green, blue, yellow, rs, rv, rt, ys, yv, yt, gs, gv, gt, bs, bv, bt, wc, wf, pcr;
	red = green = blue = yellow = rs = rv = rt = ys = yv = yt = gs = gv = gt = bs = bv = bt = wc = wf = 0;
	//3yzyn n3rf m3ana kam card mn kol lon l n2dr nl3bhom

	ifstream secondplayercards;
	secondplayercards.open("Second.txt", ios::binary);

	for (int w = 0; w < Playertwo.len(); w++)
	{
		secondplayercards >> pcr;
		if (call.cardss[pcr].Color == "red")
		{
			if (call.cardss[pcr].NUM == -1)
			{
				if (call.cardss[pcr].type == "skip")
				{
					rs++;
				}
				else if (call.cardss[pcr].type == "reverse")
				{
					rv++;
				}
				else
				{
					rt++;
				}
			}
			else
				red++; //y3ny raakm 3ady  l if statment l fo2 de m3naha power 
		}
		else if (call.cardss[pcr].Color == "green")
		{
			if (call.cardss[pcr].NUM == -1)
			{
				if (call.cardss[pcr].type == "skip")
				{
					gs++;
				}
				else if (call.cardss[pcr].type == "reverse")
				{
					gv++;
				}
				else
				{
					gt++;
				}
			}
			else
				green++; //y3ny raakm 3ady  l if statment l fo2 de m3naha power 
		}
		if (call.cardss[pcr].Color == "yellow")
		{
			if (call.cardss[pcr].NUM == -1)
			{
				if (call.cardss[pcr].type == "skip")
				{
					ys++;
				}
				else if (call.cardss[pcr].type == "reverse")
				{
					yv++;
				}
				else
				{
					yt++;
				}
			}
			else
				yellow++; //y3ny raakm 3ady  l if statment l fo2 de m3naha power 
		}
		else if (call.cardss[pcr].Color == "blue")
		{
			if (call.cardss[pcr].NUM == -1)
			{
				if (call.cardss[pcr].type == "skip")
				{
					bs++;
				}
				else if (call.cardss[pcr].type == "reverse")
				{
					bv++;
				}
				else
				{
					bt++;
				}
			}
			else
				blue++; //y3ny raakm 3ady  l if statment l fo2 de m3naha power 
		}
		else if (call.cardss[pcr].Color == "wild")
		{
			if (call.cardss[pcr].type == "colorchange")
			{
				wc++;
			}
			else
			{
				wf++;
			}
		}
	}
	secondplayercards.close();

	//call.computercardsH();
	call.secondPlayercardsH();

	if (refe >= 0 && refe <= 39 || refe >= 52 && refe <= 87)
	{

		//Dlw2ty 3yzyn nakhod ref bta3 2wl card m3ana w nshof ynf3 nl3bo wla la lw la f nakhod card tany w hakza lw mfysh f hn3ml pop mrten

		//Reading first player cards
		ifstream secondplayercardsss;
		secondplayercardsss.open("Second.txt", ios::binary);
		//Reading the ground card
		ifstream IDfile;
		IDfile.open("IDFILE.txt", ios::binary);
		string gcc;
		int gcn;
		IDfile >> gcc;
		IDfile >> gcn;
		IDfile.close();
		int i = Playertwo.len();
		int x;
		secondplayercardsss >> pcr;

		for (int m = 0; m < i; m++)
		{
			if (call.cardss[pcr].Color == gcc || call.cardss[pcr].NUM == gcn || call.cardss[pcr].type == "colorchange" || call.cardss[pcr].type == "plusfour")
			{
				test = true;
				break;
			}
			else
				secondplayercardsss >> pcr;
			test = false;
		}
		secondplayercardsss.close();

		if (test)
		{
			ifstream secondplayercardss;
			secondplayercardss.open("Second.txt", ios::binary);

			for (int j = 0; j < i; j++) //normal
			{
				secondplayercardss >> pcr;

				if (call.cardss[pcr].Color == gcc || call.cardss[pcr].NUM == gcn)
				{
					if (call.cardss[pcr].NUM == gcn)
					{
						cout << " Card on ground : " << call.cardss[pcr].Color << ' ' << call.cardss[pcr].NUM;
						cout << endl;
						Playertwo.del(pcr);
						Playertwo.print2();
						ofstream IDfile("IDFILE.txt");
						IDfile << call.cardss[pcr].Color << ' ' << call.cardss[pcr].NUM;
						IDfile.close();
						if (Playertwo.len() == 1)
						{
							cout << endl << "\n**********" << "   UNO   " << "**********" << endl;
						}
						firstplayer(pcr);
						return;
					}

					else
					{
						if (call.cardss[pcr].NUM == -1)
						{
							if (call.cardss[pcr].type == "reverse" || call.cardss[pcr].type == "skip")
							{
								Playertwo.del(pcr);
								Playertwo.print2();
								if (Playertwo.len() == 1)
								{
									cout << endl << "\n**********" << "   UNO   " << "**********" << endl;
								}
								computereasy(pcr);
								return;

							}
							else if (call.cardss[pcr].type == "drawtwo")
							{
								call.drawH1(2);
								Playertwo.del(pcr);
								Playertwo.print2();
								if (Playertwo.len() == 1)
								{
									cout << endl << "\n**********" << "   UNO   " << "**********" << endl;
								}
								computereasy(pcr);
								return;

							}

							cout << " Card on ground : " << call.cardss[pcr].Color << ' ' << call.cardss[pcr].type;
							cout << endl;
							Playertwo.del(pcr);
							Playertwo.print2();
							ofstream IDfile("IDFILE.txt");
							IDfile << call.cardss[pcr].Color << ' ' << call.cardss[pcr].type;
							IDfile.close();
							if (Playertwo.len() == 1)
							{
								cout << endl << "\n**********" << "   UNO   " << "**********" << endl;
							}
							firstplayer(pcr);
							return;
						}
						else
						{
							cout << " Card on ground : " << call.cardss[pcr].Color << ' ' << call.cardss[pcr].NUM;
							cout << endl;
							Playertwo.del(pcr);
							Playertwo.print2();
							ofstream IDfile("IDFILE.txt");
							IDfile << call.cardss[pcr].Color << ' ' << call.cardss[pcr].NUM;
							IDfile.close();
							if (Playertwo.len() == 1)
							{
								cout << endl << "\n**********" << "   UNO   " << "**********" << endl;
							}
							firstplayer(pcr);
							return;
						}
					}


				}
			}
			secondplayercardss.close();

			ifstream secondplayercards;
			secondplayercards.open("Second.txt", ios::binary);
			for (int j = 0; j < i; j++)
			{
				secondplayercards >> x;

				if (call.cardss[x].Color == "wild")
				{

					if (call.cardss[x].type == "colorchange")
					{
						secondplayercards.close();
						if (red >= 1)
						{
							Playertwo.del(x);
							Playertwo.print2();
							computereasy(0);
							return;
						}
						else if (yellow >= 1)
						{
							Playertwo.del(x);
							Playertwo.print2();
							computereasy(10);
							return;
						}
						else if (blue >= 1)
						{
							Playertwo.del(x);
							Playertwo.print2();
							computereasy(20);
							return;
						}
						else
						{
							Playertwo.del(x);
							Playertwo.print2();
							computereasy(30);
							return;
						}
					}
				}
			}
			secondplayercards.close();

			ifstream secondplayercards3;
			secondplayercards3.open("Second.txt", ios::binary);
			//3rd priority for plusfour card
			for (int j = 0; j < i; j++)
			{
				secondplayercards3 >> x;

				if (call.cardss[x].Color == "wild")
				{
					if (call.cardss[x].type == "plusfour")
					{
						call.drawH1(4);
						secondplayercards3.close();
						if (red >= 1)
						{
							Playertwo.del(x);
							Playertwo.print2();
							secondplayercards3.close();
							computereasy(0);
							return;
						}
						else if (yellow >= 1)
						{
							Playertwo.del(x);
							Playertwo.print2();
							secondplayercards3.close();
							computereasy(10);
							return;
						}
						else if (blue >= 1)
						{
							Playertwo.del(x);
							Playertwo.print2();
							secondplayercards3.close();
							computereasy(20);
							return;
						}
						else
						{
							Playertwo.del(x);
							Playertwo.print2();
							secondplayercards3.close();
							computereasy(30);
							return;
						}
					}

				}
			}
			secondplayercards3.close();
		}
		else
		{
			if (Anothertrytest2 == 0)
			{
				cout << endl;
				cout << " Drawing a card : \n";
				call.drawH2(1);
				cout << endl;

				Anothertrytest2++;
				goto Anothertry;
			}
			else
			{
				cout << " \n Round Missed " << endl;
				Anothertrytest2 = 0;
				firstplayer(refe);
				return;
			}

		}
		Anothertrytest2 = 0;

	}

	else if (refe >= 40 && refe <= 51 || refe >= 88 && refe <= 99)
	{

		ifstream secondplayercards;
		secondplayercards.open("Second.txt", ios::binary);
		int pcr;
		//Reading the ground card
		ifstream IDfile;
		IDfile.open("IDFILE.txt", ios::binary);
		string gcc, gct;
		IDfile >> gcc;
		IDfile >> gct;
		IDfile.close();
		int i = Playertwo.len();

		secondplayercards >> pcr;

		for (int m = 0; m < i; m++)
		{
			if (call.cardss[pcr].Color == gcc || call.cardss[pcr].type == gct || call.cardss[pcr].type == "colorchange" || call.cardss[pcr].type == "plusfour")
			{
				test = true;
				break;
			}
			else
				secondplayercards >> pcr;
			test = false;
		}
		if (test)
		{
		repeat4:

			ifstream secondplayercards;
			secondplayercards.open("Second.txt", ios::binary);
			int x;
			for (int j = 0; j < i; j++)
			{
				secondplayercards >> x;

				if (call.cardss[x].Color == "wild")
				{
					if (call.cardss[x].type == "plusfour")
					{
						call.drawH1(4);
						secondplayercards.close();
						if (red >= 1)
						{
							Playertwo.del(x);
							Playertwo.print2();
							computereasy(0);
							return;
						}
						else if (yellow >= 1)
						{
							Playertwo.del(x);
							Playertwo.print2();
							computereasy(10);
							return;
						}
						else if (blue >= 1)
						{
							Playertwo.del(x);
							Playertwo.print2();
							computereasy(20);
							return;
						}
						else
						{
							Playertwo.del(x);
							Playertwo.print2();
							computereasy(30);
							return;
						}
					}
					else
					{
						secondplayercards.close();
						if (red >= 1)
						{
							Playertwo.del(x);
							Playertwo.print2();
							computereasy(0);
							return;
						}
						else if (yellow >= 1)
						{
							Playertwo.del(x);
							Playertwo.print2();
							computereasy(10);
							return;
						}
						else if (blue >= 1)
						{
							Playertwo.del(x);
							Playertwo.print2();
							computereasy(20);
							return;
						}
						else
						{
							Playertwo.del(x);
							Playertwo.print2();
							computereasy(30);
							return;
						}
					}
				}
			}
			secondplayercards.close();


			ifstream secondplayercardss;
			secondplayercardss.open("Second.txt", ios::binary);

			for (int j = 0; j < i; j++)
			{
				secondplayercardss >> pcr;


				if (call.cardss[pcr].Color == gcc)
				{
					if (call.cardss[pcr].NUM == -1)
					{
						if (call.cardss[pcr].type == "reverse" || call.cardss[pcr].type == "skip")
						{
							Playertwo.del(pcr);
							Playertwo.print2();
							if (Playertwo.len() == 1)
							{
								cout << endl << "\n**********" << "   UNO   " << "**********" << endl;
							}
							secondplayercards.close();
							computereasy(pcr);
							return;

						}
						else if (call.cardss[pcr].type == "drawtwo")
						{
							call.drawH1(2);
							Playertwo.del(pcr);
							Playertwo.print2();
							if (Playertwo.len() == 1)
							{
								cout << endl << "\n**********" << "   UNO   " << "**********" << endl;
							}
							secondplayercards.close();
							computereasy(pcr);
							return;
						}
						cout << " Card on ground : " << call.cardss[pcr].Color << ' ' << call.cardss[pcr].type;
						cout << endl;
						Playertwo.del(pcr);
						Playertwo.print2();
						ofstream IDfile("IDFILE.txt");
						IDfile << call.cardss[pcr].Color << ' ' << call.cardss[pcr].type;
						IDfile.close();
						if (Playertwo.len() == 1)
						{
							cout << endl << "\n**********" << "   UNO   " << "**********" << endl;
						}
						secondplayercards.close();
						firstplayer(pcr);
						return;
					}

					else
					{
						cout << " Card on ground : " << call.cardss[pcr].Color << ' ' << call.cardss[pcr].NUM;
						cout << endl;
						Playertwo.del(pcr);
						Playertwo.print2();
						ofstream IDfile("IDFILE.txt");
						IDfile << call.cardss[pcr].Color << ' ' << call.cardss[pcr].NUM;
						IDfile.close();
						if (Playertwo.len() == 1)
						{
							cout << endl << "\n**********" << "   UNO   " << "**********" << endl;
						}
						secondplayercards.close();
						firstplayer(pcr);
						return;
					}
				}
				else if (call.cardss[pcr].type == gct)
				{
					if (call.cardss[pcr].type == "reverse" || call.cardss[pcr].type == "skip")
					{
						Playertwo.del(pcr);
						Playertwo.print2();
						if (Playertwo.len() == 1)
						{
							cout << endl << "\n**********" << "   UNO   " << "**********" << endl;
						}
						secondplayercards.close();
						computereasy(pcr);
						return;

					}
					else if (call.cardss[pcr].type == "drawtwo")
					{
						call.drawH1(2);
						Playertwo.del(pcr);
						Playertwo.print2();
						if (Playertwo.len() == 1)
						{
							cout << endl << "\n**********" << "   UNO   " << "**********" << endl;
						}
						secondplayercards.close();
						computereasy(pcr);
						return;
					}
				}
				else if (call.cardss[pcr].Color == "wild")
				{
					if (call.cardss[pcr].type == "colorchange")
					{
						Playertwo.del(pcr);
						Playertwo.print2();
						secondplayercards.close();
						goto ccc;
					}
					else
					{
						call.drawH1(4);
						Playertwo.del(pcr);
						Playertwo.print2();
						secondplayercards.close();
						goto ccc;
					}
				}

			}
			secondplayercards.close();
		}
		else
		{
			if (Anothertrytest2 == 0)
			{
				cout << endl;
				cout << " Drawing a card : \n";
				call.drawH2(1);
				cout << endl;

				Anothertrytest2++;
				goto Anothertry;
			}
			else
			{
				cout << " Round passed : " << endl;
				Anothertrytest2 = 0;
				firstplayer(refe);
				return;
			}
			Anothertrytest2 = 0;
		}
	}

	else if (refe >= 100 && refe <= 107)
	{
	ccc:

		cout << " What Color do you wish ? : ";
		char* color = new char[12];
		cin.getline(color, 12);

		for (int i = 0; i < 12; i++)
		{
			if (isalpha(color[i]) && isalpha(color[strlen(color) - i - 1]))
			{
				if (strcmp(color, "red") == 0 || strcmp(color, "blue") == 0 || strcmp(color, "green") == 0 || strcmp(color, "yellow") == 0)
				{
					break;
				}
				else
				{
					cout << " \nPlease enter a correct color as green, yellow, blue, red" << endl;
					goto ccc;
				}
			}
			else
			{
				cout << " Please enter letters only! : " << endl;
				goto ccc; //re-enters again

			}
		}

		cout << " Play on the color only " << endl;

		if (strcmp(color, "red") == 0)
		{
			computereasy(0);
			return;
		}
		else if (strcmp(color, "blue") == 0)
		{
			computereasy(20);
			return;
		}
		else if (strcmp(color, "yellow") == 0)
		{
			computereasy(10);
			return;
		}
		else
		{
			computereasy(30);
			return;
		}

	}
}

void UNO::secondplayer(int refe) //Another real player
{
	if (Playerone.len() == 0 || Playertwo.len() == 0)
	{
		if (Playerone.len() == 0)
		{
			cout << "********** You Won! **********\n" << endl;
			return;
		}
		else
		{
			cout << "**********Player TWO Won !**********\n" << endl;
			return;
		}
	}

	bool cardscheck = true;


	for (int i = 0; i < PlayedCardsNumber; i++)
	{
		if (PlayedCards[i] == refe)
		{
			i++;
			for (i; i < PlayedCardsNumber; i++)
			{
				if (PlayedCards[i] == refe)
				{
					cardscheck = false;
					break;
				}
				else
				{
					cardscheck = true;
					break;
				}
			}
			break;

		}
		else
		{
			cardscheck = true;
		}
	}
	if (cardscheck)
	{
		PlayedCards[PlayedCardsNumber] = refe;
		PlayedCardsNumber++;
	}
	bool test = false;

	cout << " \n>>>>>2nd Player Turn<<<<< \n" << endl;


	Anothertrytest2 = 0;

Anothertry2:

	cout << "********************\n*                  *\n";
	cout << "*  Card on Ground  *";
	cout << " \n*                  *\n       ";
	call.IDH(refe);
	cout << "*                  *\n" << "********************\n";

	call.secondPlayercardsH();

	if (refe >= 0 && refe <= 39 || refe >= 52 && refe <= 87)
	{
		cout << endl;

		//Dlw2ty 3yzyn nakhod ref bta3 2wl card m3ana w nshof ynf3 nl3bo wla la lw la f nakhod card tany w hakza lw mfysh f hn3ml pop mrten

		//Reading first player cards
		ifstream secondplayercards1;
		secondplayercards1.open("Second.txt", ios::binary);
		int pcr;
		//Reading the ground card
		ifstream IDfile;
		IDfile.open("IDFILE.txt", ios::binary);
		string gcc;
		int gcn;
		IDfile >> gcc;
		IDfile >> gcn;
		IDfile.close();
		int i = Playertwo.len();

		//Asking for that card to be played

		secondplayercards1 >> pcr;

		for (int m = 0; m < i; m++)
		{
			if (call.cardss[pcr].Color == gcc || call.cardss[pcr].NUM == gcn || call.cardss[pcr].type == "colorchange" || call.cardss[pcr].type == "plusfour")
			{
				test = true;
				break;
			}
			else
				secondplayercards1 >> pcr;
			test = false;
		}
		secondplayercards1.close();

		if (test)
		{


			cout << "which card do you want to play ? \n Your Answer : ";
		repeat3:

			int order;
			while (true) // we have a card
			{
			repeat333:

				cin >> order;
				if (cin.fail())
				{
					cout << " Please enter the order (Integer only)  ";
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n'); //ignoring the coming input and deleting it's buffer as if the user entered any char which takes a greater size than intgers, so we just delete this buffer and let the user re-enter this value.
				}
				else
				{
					if (checkk(order)) //making sure that the user entered an intger
					{
						if (order > 0) //making sure that the input a postive intger
						{
							break;
						}
						else
						{
							cout << " >>Please enter a postive INTGER only:\n Your Answer :  ";
							goto repeat333; //re-enters again
						}

					}
					else
					{
						cout << " >>Please enter an intger as 5 , 2 not 5.7 or any decimals\n Your Answer :  ";
						goto repeat333; //re-enters again
					}

					break;
				}
			}

			if (order > Playertwo.len() || order < 0)
			{
				cout << "Please enter a correct value between '1' and '" << Playerone.len() << "' \n Your Answer : ";
				goto repeat3;
			}
			ifstream secondplayercards2;
			secondplayercards2.open("Second.txt", ios::binary);

			for (int k = 0; k < order; k++)
			{
				secondplayercards2 >> pcr;
			}
			secondplayercards2.close();

			if (call.cardss[pcr].Color == gcc || call.cardss[pcr].NUM == gcn)
			{
				if (call.cardss[pcr].NUM == gcn)
				{
					cout << " Card on ground : " << call.cardss[pcr].Color << ' ' << call.cardss[pcr].NUM;
					cout << endl;
					Playertwo.del(pcr);
					Playertwo.print2();
					ofstream IDfile("IDFILE.txt");
					IDfile << call.cardss[pcr].Color << ' ' << call.cardss[pcr].NUM;
					IDfile.close();
					if (Playertwo.len() == 1)
					{
						cout << endl << "\n**********" << "   UNO   " << "**********" << endl;
					}
					firstplayer(pcr);
					return;
				}

				else
				{
					if (call.cardss[pcr].NUM == -1)
					{
						if (call.cardss[pcr].type == "reverse" || call.cardss[pcr].type == "skip")
						{
							Playertwo.del(pcr);
							Playertwo.print2();
							if (Playertwo.len() == 1)
							{
								cout << endl << "\n**********" << "   UNO   " << "**********" << endl;
							}
							secondplayer(pcr);
							return;
						}
						else if (call.cardss[pcr].type == "drawtwo")
						{
							call.drawH1(2);
							Playertwo.del(pcr);
							Playertwo.print2();
							if (Playertwo.len() == 1)
							{
								cout << endl << "\n**********" << "   UNO   " << "**********" << endl;
							}
							secondplayer(pcr);
							return;
						}

						cout << " Card on ground : " << call.cardss[pcr].Color << ' ' << call.cardss[pcr].type;
						cout << endl;
						Playertwo.del(pcr);
						Playertwo.print2();
						ofstream IDfile("IDFILE.txt");
						IDfile << call.cardss[pcr].Color << ' ' << call.cardss[pcr].type;
						IDfile.close();
						if (Playertwo.len() == 1)
						{
							cout << endl << "\n**********" << "   UNO   " << "**********" << endl;
						}
						firstplayer(pcr);
						return;
					}
					else
					{
						cout << " Card on ground : " << call.cardss[pcr].Color << ' ' << call.cardss[pcr].NUM;
						cout << endl;
						Playertwo.del(pcr);
						Playertwo.print2();
						ofstream IDfile("IDFILE.txt");
						IDfile << call.cardss[pcr].Color << ' ' << call.cardss[pcr].NUM;
						IDfile.close();
						if (Playertwo.len() == 1)
						{
							cout << endl << "\n**********" << "   UNO   " << "**********" << endl;
						}
						firstplayer(pcr);
						return;
					}
				}


			}
			else if (call.cardss[pcr].Color == "wild")
			{
				if (call.cardss[pcr].type == "colorchange")
				{
					Playertwo.del(pcr);
					Playertwo.print2();
					goto ccc;
				}
				else
				{
					call.drawH1(4);
					Playertwo.del(pcr);
					Playertwo.print2();
					goto ccc;
				}
			}
			else
			{
				cout << " You can't play this card, try again " << endl;
				goto Anothertry2;
			}
		}
		else
		{
			if (Anothertrytest == 0)
			{
				cout << endl;
				cout << " Drawing a card : \n";
				call.drawH2(1);
				cout << endl;

				Anothertrytest++;
				goto Anothertry2;
			}
			else
			{
				Anothertrytest = 0;
				firstplayer(refe);
				return;
			}
			Anothertrytest = 0;
		}

		Anothertrytest = 0;
	}

	else if (refe >= 40 && refe <= 51 || refe >= 88 && refe <= 99)
	{

		ifstream secondplayercards3;
		secondplayercards3.open("Second.txt", ios::binary);
		int pcr;
		//Reading the ground card
		ifstream IDfile;
		IDfile.open("IDFILE.txt", ios::binary);
		string gcc, gct;
		IDfile >> gcc;
		IDfile >> gct;
		IDfile.close();
		int i = Playertwo.len();

		secondplayercards3 >> pcr;

		for (int m = 0; m < i; m++)
		{
			if (call.cardss[pcr].Color == gcc || call.cardss[pcr].type == gct || call.cardss[pcr].type == "colorchange" || call.cardss[pcr].type == "plusfour")
			{
				test = true;
				break;
			}
			else
				secondplayercards3 >> pcr;
			test = false;
		}
		secondplayercards3.close();

		if (test)
		{
		repeat4:

			cout << "Which card do you want to play ? : ";
			int order;

			while (true)
			{
			repeat31:

				cin >> order;
				if (cin.fail())
				{
					cout << " Please enter the order (Integer only) \n Your Answer : ";
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n'); //ignoring the coming input and deleting it's buffer as if the user entered any char which takes a greater size than intgers, so we just delete this buffer and let the user re-enter this value.
				}
				else
				{
					if (checkk(order)) //making sure that the user entered an intger
					{
						if (order > 0) //making sure that the input a postive intger
						{
							break;
						}
						else
						{
							cout << " >>Please enter a postive INTGER only\n Your Answer : ";
							goto repeat31; //re-enters again
						}

					}
					else
					{
						cout << " >>Please enter an intger as 5 , 2 not 5.7 or any decimals\n Your Answer : ";
						goto repeat31; //re-enters again
					}

					break;
				}
			}
			if (order > Playertwo.len() || order < 0)
			{
				cout << "Please enter a correct value : ";
				goto repeat4;
			}
			ifstream secondplayercards4;
			secondplayercards4.open("Second.txt", ios::binary);

			for (int k = 0; k < order; k++)
			{
				secondplayercards4 >> pcr;
			}
			secondplayercards4.close();

			if (call.cardss[pcr].Color == gcc)
			{
				if (call.cardss[pcr].NUM == -1)
				{
					if (call.cardss[pcr].type == "reverse" || call.cardss[pcr].type == "skip")
					{
						Playertwo.del(pcr);
						Playertwo.print2();
						if (Playertwo.len() == 1)
						{
							cout << endl << "\n**********" << "   UNO   " << "**********" << endl;
						}
						secondplayercards4.close();
						secondplayer(pcr);
						return;

					}
					else if (call.cardss[pcr].type == "drawtwo")
					{
						call.drawH1(2);
						Playertwo.del(pcr);
						Playertwo.print2();
						if (Playertwo.len() == 1)
						{
							cout << endl << "\n**********" << "   UNO   " << "**********" << endl;
						}
						secondplayercards4.close();
						secondplayer(pcr);
						return;
					}
					cout << " Card on ground : " << call.cardss[pcr].Color << ' ' << call.cardss[pcr].type;
					cout << endl;
					Playertwo.del(pcr);
					Playertwo.print2();
					ofstream IDfile("IDFILE.txt");
					IDfile << call.cardss[pcr].Color << ' ' << call.cardss[pcr].type;
					IDfile.close();
					if (Playertwo.len() == 1)
					{
						cout << endl << "\n**********" << "   UNO   " << "**********" << endl;
					}
					secondplayercards4.close();
					firstplayer(pcr);
					return;
				}

				else
				{
					cout << " Card on ground : " << call.cardss[pcr].Color << ' ' << call.cardss[pcr].NUM;
					cout << endl;
					Playertwo.del(pcr);
					Playertwo.print2();
					ofstream IDfile("IDFILE.txt");
					IDfile << call.cardss[pcr].Color << ' ' << call.cardss[pcr].NUM;
					IDfile.close();
					if (Playertwo.len() == 1)
					{
						cout << endl << "\n**********" << "   UNO   " << "**********" << endl;
					}
					secondplayercards4.close();
					firstplayer(pcr);
					return;
				}
			}
			else if (call.cardss[pcr].type == gct)
			{
				if (call.cardss[pcr].type == "reverse" || call.cardss[pcr].type == "skip")
				{
					Playertwo.del(pcr);
					Playertwo.print2();
					if (Playertwo.len() == 1)
					{
						cout << endl << "\n**********" << "   UNO   " << "**********" << endl;
					}
					secondplayercards4.close();
					secondplayer(pcr);
					return;
				}
				else if (call.cardss[pcr].type == "drawtwo")
				{
					call.drawH1(2);
					Playertwo.del(pcr);
					Playertwo.print2();
					if (Playertwo.len() == 1)
					{
						cout << endl << "\n**********" << "   UNO   " << "**********" << endl;
					}
					secondplayercards4.close();
					secondplayer(pcr);
					return;
				}
			}
			else if (call.cardss[pcr].Color == "wild")
			{
				if (call.cardss[pcr].type == "colorchange")
				{
					Playertwo.del(pcr);
					Playertwo.print2();
					secondplayercards4.close();
					goto ccc;
				}
				else
				{
					call.drawH1(4);
					Playertwo.del(pcr);
					Playertwo.print2();
					secondplayercards4.close();
					goto ccc;
				}
			}
			{
				cout << "\n You can't play this card, try again " << endl; // chose a random card which can't be played
				goto Anothertry2;
			}

		}

		else
		{
			if (Anothertrytest2 == 0)
			{
				cout << endl;
				cout << " Drawing a card : \n";
				call.drawH2(1);
				cout << endl;

				Anothertrytest2++;
				goto Anothertry2;
			}
			else
			{
				cout << " Round passed : " << endl;
				Anothertrytest2 = 0;
				secondplayercards3.close();
				firstplayer(refe);
				return;
			}
			Anothertrytest2 = 0;
		}
	}
	else if (refe >= 100 && refe <= 107)
	{
	ccc:

		cout << " What Color do you wish ? (red, yellow, blue, green) : ";
		char* color = new char[12];
		cin.getline(color, 12);
		//Making sure that the user entered a correct answer
		for (int i = 0; i < 12; i++)
		{
			if (isalpha(color[i]) && isalpha(color[strlen(color) - i - 1]))
			{
				if (strcmp(color, "red") == 0 || strcmp(color, "blue") == 0 || strcmp(color, "green") == 0 || strcmp(color, "yellow") == 0)
				{
					break;
				}
				else
				{
					cout << " \nPlease enter a correct color as green, yellow, blue, red" << endl;
					goto ccc;
				}
			}
			else
			{
				cout << " Please enter letters only!\n : " << endl;
				goto ccc; //re-enters again

			}
		}

		cout << " Play on the color only " << endl;

		if (strcmp(color, "red") == 0)
		{
			secondplayer(0);
			return;
		}
		else if (strcmp(color, "blue") == 0)
		{
			secondplayer(20);
			return;
		}
		else if (strcmp(color, "yellow") == 0)
		{
			secondplayer(10);
			return;
		}
		else
		{
			secondplayer(30);
			return;
		}

	}
}

// If the length of anyone == 0 then end the game
bool check()
{
	if (Playerone.len() == 0 || Playertwo.len() == 0)
	{
		char playagain[15];
		cout << "\n\n Wanna Play again ?  ";
		cout << "Please enter Yes or No\n Your Answer : ";
	repeat:

		cin.getline(playagain, 14);

		for (int i = 0; i < 14; i++)
		{
			if (isalpha(playagain[i]) && isalpha(playagain[strlen(playagain) - i - 1]))
			{
				if (strcmp(playagain, "Yes") == 0 || strcmp(playagain, "No") == 0)
				{
					break;
				}
				else
				{
					cout << " \nPlease enter a correct answer ( Yes - No )" << endl << " \n Your Answer : ";
					goto repeat;
				}
			}
			else
			{
				cout << " Please enter letters only!\n Your Answer :  " << endl;
				goto repeat; //re-enters again

			}

		}

		if (strcmp(playagain, "Yes") == 0)
		{
			while (!readycards.isEmpty()) //Clearing the stack
			{
				readycards.pop();
			}
			Playerone.clearing();
			Playertwo.clearing();
			return true;
		}
		else
		{
			cout << "\n\n		•°•°•°•°•°•°•°•°•°•°•°•°•°•°•°•Thanks for playing our game!•°•°•°•°•°•°•°•°•°•°•°•°•°•°•°•\n\n";
			return false;
		}


	}
	else
	{
		cout << "\nError\n";
	}
}

//those two funtions draws some cards to the linked list object Playerone and Two where key is the number of cards to draw
void Cards::drawH1(int key)
{
	for (int i = 0; i < key; i++)
	{
		if (readycards.isEmpty())
		{
			shuffle();
		}
		Playerone.last(readycards.peek());
		readycards.pop();
	}
	Playerone.print1(); //Saves the new update in the file
	return;
}
void Cards::drawH2(int key)
{
	for (int i = 0; i < key; i++)
	{
		if (readycards.isEmpty())
		{
			shuffle();
		}
		Playertwo.last(readycards.peek());
		readycards.pop();
	}
	Playertwo.print2(); //Saves the new update in the file
	return;
}

void Cards::IDH2(int key)
{
	ID2(cardss, key);
}

//Just printing the ground card in a file
void Cards::ID2(struct CARD* arr, int key)
{
	ofstream IDfile("IDFILE.txt");

	//cout << " Key = " << key << endl;
	int i = key;

	if (i >= 0 && i <= 39 || i >= 52 && i <= 87)
	{
		IDfile << arr[key].Color << ' ' << arr[key].NUM;
	}
	else if (i >= 40 && i <= 51 || i >= 88 && i <= 99)
	{
		IDfile << arr[key].Color << ' ' << arr[key].type;
	}
	else if (i >= 100 && i <= 107)
	{
		IDfile << arr[key].Color << ' ' << arr[key].type;
	}
	else
	{
		cout << " You don't have this card " << endl;
	}
	IDfile.close();
	return;
}

void Cards::IDH(int key)
{
	ID(cardss, key);
	return;
}

//Diplaying and printing the ground card
void Cards::ID(struct CARD* arr, int key)
{
	ofstream IDfile("IDFILE.txt");

	//cout << " Key = " << key << endl;
	int i = key;

	if (i >= 0 && i <= 39 || i >= 52 && i <= 87)
	{
		IDfile << arr[key].Color << ' ' << arr[key].NUM;
		cout << arr[key].Color << ' ' << arr[key].NUM << endl;
	}
	else if (i >= 40 && i <= 51 || i >= 88 && i <= 99)
	{
		IDfile << arr[key].Color << ' ' << arr[key].type;
		cout << arr[key].Color << ' ' << arr[key].type << endl;
	}
	else if (i >= 100 && i <= 107)
	{
		IDfile << arr[key].Color << ' ' << arr[key].type;
		cout << arr[key].Color << ' ' << arr[key].type << endl;
	}
	else
	{
		cout << " You don't have this card " << endl;
	}
	IDfile.close();
	return;
}

//Function bt display l cards bt3tk
void Cards::firstPlayerCards(struct CARD* arr)
{
	int i;

	ifstream firstplayercards;
	firstplayercards.open("First.txt", ios::binary);
	int x;
	cout << " \nYour cards are : " << endl;
	cout << "*******************\n";
	if (Playerone.len() > 0)
	{
		for (i = 0; i < Playerone.len(); i++)
		{
			firstplayercards >> x;

			if (x >= 0 && x <= 39 || x >= 52 && x <= 87)
			{
				cout << arr[x].Color << ' ' << arr[x].NUM << ' ' << "  Order : " << i + 1 << endl;
			}
			else if (x >= 40 && x <= 51 || x >= 88 && x <= 99)
			{
				cout << arr[x].Color << ' ' << arr[x].type << "  Order : " << i + 1 << endl;
			}
			else if (x >= 100 && x <= 107)
			{
				cout << arr[x].Color << ' ' << arr[x].type << "  Order : " << i + 1 << endl;
			}
			else
			{
				cout << " You don't have this card " << endl;
			}
		}
		cout << "\n*******************" << endl;
	}
	else
		cout << " You Don't have any extra cards ";
	firstplayercards.close();
	return;
}

//bt display l cards l m3 l 2osadk computer y3ny
void Cards::secondPlayerCards(struct CARD* arr)
{
	int i;

	ifstream secondplayercards;
	secondplayercards.open("Second.txt", ios::binary);
	int x;
	cout << " \n 2nd Player cards are : " << endl << "*******************" << endl;
	if (Playertwo.len() > 0)
	{
		for (i = 0; i < Playertwo.len(); i++)
		{
			secondplayercards >> x;

			if (x >= 0 && x <= 39 || x >= 52 && x <= 87)
			{
				cout << arr[x].Color << ' ' << arr[x].NUM << ' ' << "  Order : " << i + 1 << endl;
			}
			else if (x >= 40 && x <= 51 || x >= 88 && x <= 99)
			{
				cout << arr[x].Color << ' ' << arr[x].type << "  Order : " << i + 1 << endl;
			}
			else if (x >= 100 && x <= 107)
			{
				cout << arr[x].Color << ' ' << arr[x].type << "  Order : " << i + 1 << endl;
			}
			else
			{
				cout << " You don't have this card " << endl;
			}
		}
		cout << "\n*******************" << endl;
	}
	else
		cout << " You Don't have any extra cards ";
	secondplayercards.close();
	return;
}

// Not displaying computer cards
void Cards::computercards(struct CARD* arr)
{
	cout << " \n Computer Cards : " << endl << "*******************" << endl;
	if (Playertwo.len() > 0)
	{
		cout << "  " << Playertwo.len() << " Cards	\n";
		for (int i = 0; i < Playertwo.len(); i++)
		{
			cout << "# ";
		}
		cout << "\n*******************" << endl;
	}
	else
		cout << " You Don't have any extra cards ";
	return;
}



int main()
{

playagain:
	

	cout << "						*******UNO GAME*******\n";
	cout << "    >This Game was fully made by:\n";
	cout << "				Moustafa Ahmed Adel Mohamed		Section: 4		BN: 11	\n";
	cout << "							   @Cairo University Faculty of Engineering\n";
	cout << "							   Electronics and Communication - EECE2024\n";
	cout << "							   This project was made under supervision of Dr. Omar Naser\n";
	cout << "							   Start date: 4/15/2022 -------End Date: 4/24/2022";


	//Initializing..
	call.InitializeH();

	//Starting 
	Assist.FetchingH();

	//Playing

	Assist.Game();

	if (check())
	{
		system("CLS");
		goto playagain;
	}
	return 0;
}