// Name: Ali Bayati 
// Problem: Hash Table
// Chapter  8 


#include<iostream>
#include<string>
#include<fstream>

using namespace std;
struct book
{
	int bookId, quantity;
	string title, author;
	float cost, price;

};
void loadTable(book[], int);
int getHashKey(int, int);void loadBook(book[], book, int);
void printBook(book);void clearTable(book[], int);
void placeOrder(book[], int);
int menu();

int main()
{
	int size, mch;
	int ovc=0;
	cout << "Enter the size of the hash table :";
	cin >> size;
	book *newbook = new book[size];
	clearTable(newbook, size);
	loadTable(newbook, size);
	mch = menu();

	while (mch !=2)
	{
		if(mch==1)
		placeOrder(newbook, size);
		mch=menu();
	}
		return 0;
}
int menu()
{
	int ch;
	cout << "1. Place Order \n";
	cout << "2. Exit\n";
	cout << "Enter Choice :";
	cin >> ch;
		
	return ch;
}
void placeOrder(book newbook[], int size)
{
	int bookID,key,qty, rec = 1;
	
	cout << "Enter Book ID :";
	cin >> bookID;
	key = getHashKey(bookID, size);
	while (newbook[key].bookId!=bookID && newbook[key].bookId !=-1)
	{
		rec++;
		key = (key + 1) % size;
	}
	if (newbook[key].bookId != -1)
	{
		printBook(newbook[key]);
		cout << "*** Looked at " << rec << " records ***\n";
		cout << "Enter Quantity Desired :";
		cin >> qty;
		
		while (newbook[key].quantity < qty)
		{
			cout << "Invalid Quantity !\n";
			cout << "Try again :";
			cin >> qty;
		}
		newbook[key].quantity -= qty;
		cout << "Order Total :  " << newbook[key].price*qty << endl;
		cout << "Order Profit : " << (newbook[key].price - newbook[key].cost) *qty << endl;
	}
	else
		cout << "Book is not Found !\n";
}


void loadBook(book newbook[], book onebook, int size)
{
	
	int key,arya=0 ;
	
	key = getHashKey(onebook.bookId, size);
	while (newbook[key].bookId != -1&&onebook.bookId!=newbook[key].bookId)
	{
	
		key = (key + 1) % size;
		
	}
		
	newbook[key] = onebook;

}


void loadTable(book newbook[], int size)
{
	cout << "Loading Hash Table ...\n";
	book tt;
	string line, word,d;
	int i=0,key,arya=0;
	d = "#";
	ifstream inFile;
	inFile.open("inventory.txt");
	while (i<102)
	{
		
		getline(inFile, line);
		word = line.substr(0, line.find(d));
		tt.bookId = stoi(word);
		line.erase(0, line.find(d) + 1);
		word = line.substr(0, line.find(d));
		tt.title = word;
		line.erase(0, line.find(d) + 1);
		word = line.substr(0, line.find(d));
		tt.author = word;
		line.erase(0, line.find(d) + 1);
		word = line.substr(0, line.find(d));
		tt.cost = stof(word);
		line.erase(0, line.find(d) + 1);
		word = line.substr(0, line.find(d));
		tt.price = stof(word);
		line.erase(0, line.find(d) + 1);
		tt.quantity = stoi(line);
		i++;
		
		loadBook(newbook, tt, size);
		key = getHashKey(tt.bookId, size);
		while (newbook[key].bookId != -1 && tt.bookId != newbook[key].bookId)
		{
			arya++;
			key = (key + 1) % size;
			cout << "Collision " << arya << endl;
		}
	}
	inFile.close();
	
	
	cout << i << " Books loaded " << endl;
	
	
	
	
	
}
void clearTable(book newbook[] , int size)
{
	for (int i = 0; i <= size; i++)
		newbook[i].bookId=-1;
	
}

int getHashKey(int bookId, int size)
{
	return bookId % size;
}

void printBook(book onebook)
{
	cout << "Book ID   : " << onebook.bookId << endl;
	cout << "Title     : " << onebook.title << endl;
	cout << "Autho     : " << onebook.author << endl;
	cout << "Cost      : " << onebook.cost << endl;
	cout << "Price     : " << onebook.price << endl;
	cout << "Quantity  : " << onebook.quantity << endl;
	
}
/*Output
Enter the size of the hash table :444
Loading Hash Table ...
Collision 1
Collision 2
Collision 3
Collision 4
Collision 5
Collision 6
Collision 7
Collision 8
Collision 9
Collision 10
Collision 11
Collision 12
Collision 13
Collision 14
Collision 15
102 Books loaded
1. Place Order
2. Exit
Enter Choice :1
Enter Book ID :107307
Book ID   : 107307
Title     : Barchester Towers
Autho     : Anthony Trollope
Cost      : 2.1
Price     : 9.99
Quantity  : 10
*** Looked at 2 records ***
Enter Quantity Desired :11
Invalid Quantity !
Try again :10
Order Total :  99.9
Order Profit : 78.9
1. Place Order
2. Exit
Enter Choice :1
Enter Book ID :107307
Book ID   : 107307
Title     : Barchester Towers
Autho     : Anthony Trollope
Cost      : 2.1
Price     : 9.99
Quantity  : 0
*** Looked at 2 records ***
Enter Quantity Desired :0
Order Total :  0
Order Profit : 0
1. Place Order
2. Exit
Enter Choice :1
Enter Book ID :159274
Book ID   : 159274
Title     : Gulliver's Travels
Autho     : Jonathan Swift
Cost      : 4.13
Price     : 9.99
Quantity  : 6
*** Looked at 1 records ***
Enter Quantity Desired :1
Order Total :  9.99
Order Profit : 5.86
1. Place Order
2. Exit
Enter Choice :2
Press any key to continue . . .
*/