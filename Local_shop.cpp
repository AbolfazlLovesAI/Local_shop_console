#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <iomanip>
using namespace std;

struct GoodNode
{
	unsigned int code;
	string name;
	int price;
	int amount;
	GoodNode* next;
};
struct PurchaseNode
{
	unsigned int code;
	int price;
	string date;
	PurchaseNode* next;
};
struct PaymentNode
{
	int amount;
	string date;
	PaymentNode* next;
};
struct CustomerNode
{
	string phone;
	string fname, lname;
	string address;
	PurchaseNode* first_purchase;
	PaymentNode* first_payment;
	CustomerNode* next;
};
struct BedehkaranNode
{
	string fname, lname;
	int due;
	BedehkaranNode* next;
};

void getinfo(CustomerNode*, GoodNode*);
void sabtmoshtari(CustomerNode*);
void virayesh_customer(CustomerNode*);
void sabtkala(GoodNode*);
void virayesh_goods(GoodNode*);
void kharid(CustomerNode*, GoodNode*, string);
void pardakht(CustomerNode*, string);
void bedehkaran(CustomerNode*);
void vaziyat(CustomerNode*);
void WritePP(CustomerNode*);

template <class LinkList>
void DeleteList(LinkList);

int main()
{
	system("color 07");

	CustomerNode* FirstCustomer;
	FirstCustomer = new CustomerNode;
	GoodNode* FirstGood;
	FirstGood = new GoodNode;

	getinfo(FirstCustomer, FirstGood);


	time_t t = time(0);
	tm* now = localtime(&t);
	string date = to_string(now->tm_year + 1900) + '-' + to_string(now->tm_mon + 1) + '-' + to_string(now->tm_mday);

	while (true)
	{
		system("cls");
		int choice;

		cout << "Welcome Back\n1-Sabt Moshtari\n2-Virayesh etela'at moshtari\n3-sabt kala\n4-virayesh kala" << endl;
		cout << "5-kharid kala\n6-pardakht\n7-list bedehkaran\n8-vaziyat moshtari\n9-Khroj" << endl;
		cout << "input your choice's Number: ";
		cin >> choice;

		switch (choice)
		{
		case 1: sabtmoshtari(FirstCustomer); break;
		case 2: virayesh_customer(FirstCustomer); break;
		case 3: sabtkala(FirstGood); break;
		case 4: virayesh_goods(FirstGood); break;
		case 5: kharid(FirstCustomer, FirstGood, date); break;
		case 6: pardakht(FirstCustomer, date); break;
		case 7: bedehkaran(FirstCustomer); break;
		case 8: vaziyat(FirstCustomer); break;
		case 9:
			DeleteList(FirstCustomer);
			DeleteList(FirstGood);
			cout << "\n\nHave a great time\n"; system("pause"); exit(0); break;
		default: system("cls"); cout << "Wrong input.."; break;
		}

	}

}
void getinfo(CustomerNode* FirstCustomer, GoodNode* FirstGood)
{
	ifstream CustomerInfo("C:\\Shop\\customer.txt");
	ifstream GoodsInfo("C:\\Shop\\goods.txt");
	ifstream PurchaseInfo("C:\\Shop\\purchase.txt");
	ifstream PaymentInfo("C:\\Shop\\payment.txt");


	getline(CustomerInfo, FirstCustomer->phone);
	getline(CustomerInfo, FirstCustomer->fname);
	getline(CustomerInfo, FirstCustomer->lname);
	getline(CustomerInfo, FirstCustomer->address);
	CustomerNode* CurrentCustomer = FirstCustomer;
	CustomerNode* LastCustomer;

	while (true)
	{
		string phonenumber;
		if (getline(CustomerInfo, phonenumber))
		{
			LastCustomer = new CustomerNode;
			LastCustomer->phone = phonenumber;
			getline(CustomerInfo, LastCustomer->fname);
			getline(CustomerInfo, LastCustomer->lname);
			getline(CustomerInfo, LastCustomer->address);
			CurrentCustomer->next = LastCustomer;
			CurrentCustomer = CurrentCustomer->next;
		}
		else
		{
			CurrentCustomer->next = NULL;
			break;
		}

	}


	CurrentCustomer = FirstCustomer;
	PurchaseNode* CurrentP;
	PurchaseNode* newP;
	while (CurrentCustomer != NULL)
	{
		CurrentCustomer->first_purchase;
		CurrentP = CurrentCustomer->first_purchase;
		string number = CurrentCustomer->phone;
		string readnumber, pdate, temp;
		int pcode, pprice;
		int counter = 0;
		while (getline(PurchaseInfo, readnumber))
		{
			PurchaseInfo >> pcode;
			getline(PurchaseInfo, temp);
			//PurchaseInfo.ignore();
			getline(PurchaseInfo, pdate);
			PurchaseInfo >> pprice;

			if (readnumber == number)
			{
				newP = new PurchaseNode;
				counter++;
				newP->code = pcode;
				newP->date = pdate;
				newP->price = pprice;

				if (counter == 1)
				{
					CurrentCustomer->first_purchase = newP;
					CurrentP = newP;
				}
				else
				{
					CurrentP->next = newP;
					CurrentP = CurrentP->next;
				}
			}
			PurchaseInfo.ignore();

		}
		if (counter == 0)
		{
			CurrentCustomer->first_purchase = NULL;
		}
		else
			CurrentP->next = NULL;
		CurrentCustomer = CurrentCustomer->next;
		PurchaseInfo.clear();
		PurchaseInfo.seekg(0);
	}


	CurrentCustomer = FirstCustomer;
	PaymentNode* CurrentPay;
	PaymentNode* LastPay;

	while (CurrentCustomer != NULL)
	{

		CurrentPay = CurrentCustomer->first_payment;
		string number = CurrentCustomer->phone;
		string readnumber, pdate;
		int pamount, counter = 0;
		while (getline(PaymentInfo, readnumber))
		{
			getline(PaymentInfo, pdate);
			PaymentInfo >> pamount;

			if (readnumber == number)
			{
				LastPay = new PaymentNode;
				counter++;
				LastPay->amount = pamount;
				LastPay->date = pdate;

				if (counter == 1)
				{
					CurrentCustomer->first_payment = LastPay;
					CurrentPay = CurrentCustomer->first_payment;
				}
				else
				{
					CurrentPay->next = LastPay;
					CurrentPay = CurrentPay->next;
				}
			}
			PaymentInfo.ignore();
		}
		if (counter == 0)
			CurrentCustomer->first_payment = NULL;
		else
			CurrentPay->next = NULL;
		CurrentCustomer = CurrentCustomer->next;
		PaymentInfo.clear();
		PaymentInfo.seekg(0);
	}


	GoodNode* CurrentGood = FirstGood;
	GoodsInfo >> FirstGood->code;
	GoodsInfo.ignore();
	getline(GoodsInfo, FirstGood->name);
	GoodsInfo >> FirstGood->price;
	GoodsInfo >> FirstGood->amount;
	GoodNode* LastGood;

	int GoodsCode;
	while (GoodsInfo >> GoodsCode)
	{
		LastGood = new GoodNode;
		LastGood->code = GoodsCode;
		GoodsInfo.ignore();
		getline(GoodsInfo, LastGood->name);
		GoodsInfo >> LastGood->price;
		GoodsInfo >> LastGood->amount;
		CurrentGood->next = LastGood;
		CurrentGood = CurrentGood->next;
	}
	CurrentGood->next = NULL;
	CustomerInfo.close();
	PurchaseInfo.close();
	PaymentInfo.close();
	GoodsInfo.close();
}


void sabtmoshtari(CustomerNode* FirstCustomer)
{
	system("cls");
	cin.ignore();
	string number, fname, lname, addres;
	ofstream customer("C:\\Shop\\customer.txt", ios::app);

	CustomerNode* CurrentCustomer = FirstCustomer;
	cout << "number: "; getline(cin, number);
	if (number[0] != '0' || number[1] != '9' || number.length() != 11)
	{
		system("cls");
		cout << "wrong nuumber..."; system("pause");
		customer.close();
		return;
	}
	while (CurrentCustomer->next != NULL)
	{

		if (number == CurrentCustomer->phone || number == CurrentCustomer->next->phone)
		{
			system("cls");
			cout << "This number has already been used..";
			system("pause");
			customer.close();
			return;
		}
		CurrentCustomer = CurrentCustomer->next;
	}

	cout << "First Name: "; getline(cin, fname);
	cout << "Last Name: "; getline(cin, lname);
	cout << "Addres: "; getline(cin, addres);

	CustomerNode* NewCustomer;
	NewCustomer = new CustomerNode;
	NewCustomer->phone = number;
	NewCustomer->fname = fname;
	NewCustomer->lname = lname;
	NewCustomer->address = addres;
	CurrentCustomer->next = NewCustomer;

	customer << number << endl << fname << endl << lname << endl << addres << endl;
	customer.close();
	system("cls"); cout << "Customer saved.." << system("pause");

}

void virayesh_customer(CustomerNode* FirstCustomer)
{
	system("cls");
	CustomerNode* ChosenCustomer = FirstCustomer;
	CustomerNode* CurrentCustomer;
	CurrentCustomer = FirstCustomer;

	int counter = 1, ChoiceCustomer;
	for (counter = 1; CurrentCustomer != NULL; counter++)
	{
		cout << counter << "->" << CurrentCustomer->fname << ' ' << CurrentCustomer->lname << endl;
		CurrentCustomer = CurrentCustomer->next;
	}

	cout << "Which customer wants to change information: "; cin >> ChoiceCustomer;

	if (ChoiceCustomer > counter || ChoiceCustomer < 1)
	{
		cout << "Wrong input.."; system("pause");
		return;
	}

	system("cls");
	for (int i = 1; i < ChoiceCustomer; i++)
		ChosenCustomer->next;

	string newphone, phonecheck = ChosenCustomer->phone;
	cout << "New Number: "; cin >> newphone;
	if (newphone[0] != '0' || newphone[1] != '9' || newphone.length() != 11)
	{
		system("cls");
		cout << "wrong nuumber..."; system("pause");
		return;
	}

	ChosenCustomer->phone = newphone;
	cout << "New address: "; cin >> ChosenCustomer->address;

	system("cls");
	cout << "operation successfull.."; system("pause");
}

void sabtkala(GoodNode* FirstGood)
{
	system("cls");
	string product_name, otherinfo; int tagcheck, code = 1000, tag, price, instock;

	ofstream goods("C:\\Shop\\goods.txt", ios::app);

	int lastcode = 0;
	GoodNode* CurrentGood = FirstGood;
	GoodNode* LastGood;
	while (CurrentGood != NULL)
	{
		lastcode = CurrentGood->code;
		LastGood = CurrentGood;
		CurrentGood = CurrentGood->next;
	}
	lastcode++;
	cin.ignore();
	cout << "Product's name: "; getline(cin, product_name);
	cout << "price: "; cin >> price;
	cout << "how many do we have in stock? "; cin >> instock;
	goods << lastcode << endl << product_name << endl << price << endl << instock << endl;
	goods.close();

	GoodNode* NewGood;
	NewGood = new GoodNode;
	NewGood->code = lastcode;
	NewGood->name = product_name;
	NewGood->price = price;
	NewGood->amount = instock;
	NewGood->next = NULL;
	LastGood->next = NewGood;

	ofstream Goods("C:\\Shop\\goods.txt");
	CurrentGood = FirstGood;
	while (CurrentGood != NULL)
	{
		Goods << CurrentGood->code << endl << CurrentGood->name << endl << CurrentGood->price << endl << CurrentGood->amount << endl;
		CurrentGood = CurrentGood->next;
	}
	Goods.close();
	system("cls");
	cout << "operation successfull.."; system("pause");
}

void virayesh_goods(GoodNode* FirstGood)
{
	system("cls");
	GoodNode* CurrentGood = FirstGood;
	int ChosenCode;

	while (CurrentGood != NULL)
	{
		cout << CurrentGood->code << "->" << CurrentGood->name << "\n<price>" << CurrentGood->price << "\n<amount>" << CurrentGood->amount << endl;
		cout << endl;
		CurrentGood = CurrentGood->next;
	}
	cout << "\nInput the Good code that you want to change: ";
	cin >> ChosenCode;

	CurrentGood = FirstGood;
	bool isfound = false;
	while (CurrentGood != NULL)
	{
		if (ChosenCode == CurrentGood->code)
		{
			isfound = true;
			cout << "new price: "; cin >> CurrentGood->price;
			cout << "New stock amount: "; cin >> CurrentGood->amount;

			system("cls"); cout << "Good info was Changed succesfully.."; system("pause");
			break;
		}
		CurrentGood = CurrentGood->next;
	}
	if (!isfound)
	{
		system("cls");
		cout << "No such product exist in inventory\n";
		system("pause");
	}
	else
	{
		ofstream Goodsfile("C:\\Shop\\goods.txt");
		CurrentGood = FirstGood;
		while (CurrentGood != NULL)
		{
			Goodsfile << CurrentGood->code << endl << CurrentGood->name << endl << CurrentGood->price << endl << CurrentGood->amount << endl;
			CurrentGood = CurrentGood->next;
		}
		Goodsfile.close();
	}
}

void kharid(CustomerNode* FirstCustomer, GoodNode* FirstGood, string date)
{
	system("cls");
	CustomerNode* ChosenCustomer = FirstCustomer;
	CustomerNode* CurrentCustomer;
	CurrentCustomer = FirstCustomer;

	int counter = 1, ChoiceCustomer;
	for (counter = 1; CurrentCustomer != NULL; counter++)
	{
		cout << counter << "->" << CurrentCustomer->fname << ' ' << CurrentCustomer->lname << endl;
		CurrentCustomer = CurrentCustomer->next;
	}
	cout << "Which customer wants to buy Goods: "; cin >> ChoiceCustomer;
	if (ChoiceCustomer > counter || ChoiceCustomer < 1)
	{
		cout << "Wrong input.."; system("pause");
		return;
	}
	system("cls");
	for (int i = 1; i < ChoiceCustomer; i++)
		ChosenCustomer->next;

	char GoodChoice;
	GoodNode* CurrentGood = FirstGood;
	while (true)
	{
		if (CurrentGood == NULL)
		{
			cout << "no more Good available at  time.."; system("pause");
			CurrentGood = FirstGood;
		}
		cout << "Code: " << CurrentGood->code << endl;
		cout << "Name: " << CurrentGood->name << endl;
		cout << "price: " << CurrentGood->price << endl;
		cout << "Available in stock: " << CurrentGood->amount << endl;
		cout << "if this is your Choice,input 'y'\nif you want to see the next thing, input 'n'\nand to cancel procces input 'c'" << endl;
		cin >> GoodChoice;
		system("cls");
		if (GoodChoice == 'y')
		{
			break;
		}
		else if (GoodChoice == 'n')
			CurrentGood = CurrentGood->next;
		else if (GoodChoice == 'c')
			return;
		else
		{
			cout << "Wrong input. Try again" << endl;
			system("pause");
		}
	}

	PurchaseNode* CurrentPurchase;
	CurrentPurchase = ChosenCustomer->first_purchase;
	while (CurrentPurchase->next != NULL)
		CurrentPurchase = CurrentPurchase->next;
	PurchaseNode* newP;
	newP = new PurchaseNode;
	newP->code = CurrentGood->code;
	newP->price = CurrentGood->price;
	newP->date = date;
	newP->next = NULL;
	CurrentPurchase->next = newP;

	ofstream purchases("C:\\Shop\\purchase.txt", ios::app);
	purchases << ChosenCustomer->phone << endl << newP->code << endl << newP->date << endl << newP->price << endl;
	purchases.close();
}

void pardakht(CustomerNode* FirstCustomer, string date)
{
	system("cls");

	CustomerNode* ChosenCustomer = FirstCustomer;
	CustomerNode* CurrentCustomer;
	CurrentCustomer = FirstCustomer;

	int counter = 1, ChoiceCustomer;
	for (counter = 1; CurrentCustomer != NULL; counter++)
	{
		cout << counter << "->" << CurrentCustomer->fname << ' ' << CurrentCustomer->lname << endl;
		CurrentCustomer = CurrentCustomer->next;
	}
	cout << "Which customer wants to Pay: "; cin >> ChoiceCustomer;
	if (ChoiceCustomer > counter || ChoiceCustomer < 1)
	{
		system("cls");
		cout << "Wrong input.."; system("pause");
		return;
	}
	system("cls");
	for (int i = 1; i < ChoiceCustomer; i++)
		ChosenCustomer = ChosenCustomer->next;

	PurchaseNode* CurrentPurchase = ChosenCustomer->first_purchase;
	PaymentNode* CurrentPayment = ChosenCustomer->first_payment;
	PaymentNode* LastPayment;
	int Allpurchase = 0, Allpay = 0;
	while (CurrentPurchase != NULL)
	{
		Allpurchase += CurrentPurchase->price;
		CurrentPurchase = CurrentPurchase->next;
	}
	while (CurrentPayment != NULL)
	{
		Allpay += CurrentPayment->amount;
		LastPayment = CurrentPayment;
		CurrentPayment = CurrentPayment->next;
	}

	int amount, MAX = Allpurchase - Allpay;
	cout << "Due: " << MAX << "\nHow Much do you want to pay? "; cin >> amount;
	if (amount > MAX || amount <= 0)
	{
		system("cls");
		cout << "not suitable.."; system("pause");
		return;
	}
	PaymentNode* newPay;
	newPay = new PaymentNode;
	newPay->amount = amount;
	newPay->date = date;
	newPay->next = NULL;
	LastPayment->next = newPay;

	ofstream payments("C:\\Shop\\payment.txt", ios::app);
	payments << ChosenCustomer->phone << endl << date << endl << amount << endl;
}

void bedehkaran(CustomerNode* FirstCustomer)
{
	system("cls");

	CustomerNode* CurrentCustomer = FirstCustomer;
	BedehkaranNode* FirstBedehkar = NULL;
	BedehkaranNode* CurrentBedehkar;
	int counter = 0;
	while (CurrentCustomer != NULL)
	{
		PurchaseNode* CurrentPurchase = CurrentCustomer->first_purchase;
		PaymentNode* CurrentPayment = CurrentCustomer->first_payment;
		PaymentNode* LastPayment;
		int Allpurchase = 0, Allpay = 0;
		while (CurrentPurchase != NULL)
		{
			Allpurchase += CurrentPurchase->price;
			CurrentPurchase = CurrentPurchase->next;
		}
		while (CurrentPayment != NULL)
		{
			Allpay += CurrentPayment->amount;
			LastPayment = CurrentPayment;
			CurrentPayment = CurrentPayment->next;
		}

		int Due = Allpurchase - Allpay;
		if (Due > 0 && counter == 0)
		{
			counter++;
			CurrentBedehkar = new BedehkaranNode;
			CurrentBedehkar->due = Due;
			CurrentBedehkar->fname = CurrentCustomer->fname;
			CurrentBedehkar->lname = CurrentCustomer->lname;
			FirstBedehkar = CurrentBedehkar;
			CurrentBedehkar->next = NULL;
		}
		else if (Due > 0 && counter != 0)
		{
			BedehkaranNode* newBedehkar;
			newBedehkar = new BedehkaranNode;
			newBedehkar->due = Due;
			newBedehkar->fname = CurrentCustomer->fname;
			newBedehkar->lname = CurrentCustomer->lname;
			newBedehkar->next = NULL;
			CurrentBedehkar->next = newBedehkar;
			CurrentBedehkar = CurrentBedehkar->next;
		}
		CurrentCustomer = CurrentCustomer->next;
	}
	system("cls");
	if (FirstBedehkar == NULL)
	{

		cout << "None of Customers have any Dues..";
		system("pause");
		return;
	}
	CurrentBedehkar = FirstBedehkar;
	for (int i = 1; CurrentBedehkar != NULL; i++)
	{
		cout << i << "->" << CurrentBedehkar->fname << ' ' << CurrentBedehkar->lname << " = " << CurrentBedehkar->due << endl;
		CurrentBedehkar = CurrentBedehkar->next;
	}
	system("pause");
}

void vaziyat(CustomerNode* FirstCustomer)
{
	system("cls");

	CustomerNode* ChosenCustomer = FirstCustomer;
	CustomerNode* CurrentCustomer;
	CurrentCustomer = FirstCustomer;

	int counter = 1, ChoiceCustomer;
	for (counter = 1; CurrentCustomer != NULL; counter++)
	{
		cout << counter << "->" << CurrentCustomer->fname << ' ' << CurrentCustomer->lname << endl;
		CurrentCustomer = CurrentCustomer->next;
	}
	cout << "Which customer wants to Pay: "; cin >> ChoiceCustomer;
	if (ChoiceCustomer > counter || ChoiceCustomer < 1)
	{
		system("cls");
		cout << "Wrong input.."; system("pause");
		return;
	}
	system("cls");
	for (int i = 1; i < ChoiceCustomer; i++)
		ChosenCustomer->next;

	PurchaseNode* CurrentPurchase = ChosenCustomer->first_purchase;
	PaymentNode* CurrentPayment = ChosenCustomer->first_payment;
	PaymentNode* LastPayment;
	int Allpurchase = 0, Allpay = 0;
	while (CurrentPurchase != NULL)
	{
		Allpurchase += CurrentPurchase->price;
		CurrentPurchase = CurrentPurchase->next;
	}
	while (CurrentPayment != NULL)
	{
		Allpay += CurrentPayment->amount;
		LastPayment = CurrentPayment;
		CurrentPayment = CurrentPayment->next;
	}

	int Due = Allpurchase - Allpay;

	cout << "Name: " << ChosenCustomer->fname << endl;
	cout << "Last Name: " << ChosenCustomer->lname << endl;
	cout << "Number: " << ChosenCustomer->phone << endl;
	cout << "Address: " << ChosenCustomer->address << endl;
	cout << "Due: " << Due << endl;
	cout << "----------Purchases-----------" << endl;
	CurrentPurchase = ChosenCustomer->first_purchase;
	while (CurrentPurchase != NULL)
	{
		cout << "Code: " << CurrentPurchase->code << endl;
		cout << "Date: " << CurrentPurchase->date << endl;
		cout << "Price: " << CurrentPurchase->price << endl;
		cout << "*******" << endl;
		CurrentPurchase = CurrentPurchase->next;
	}
	cout << "-----------Payments-----------" << endl;
	CurrentPayment = ChosenCustomer->first_payment;
	while (CurrentPayment != NULL)
	{
		cout << "Date: " << CurrentPayment->date << endl;
		cout << "Amount: " << CurrentPayment->amount << endl;
		cout << "*******" << endl;
		CurrentPayment = CurrentPayment->next;
	}
	system("pause");
}

template <class LinkList>
void DeleteList(LinkList first)
{
	LinkList current = first;
	while (current->next != NULL)
	{
		LinkList temp = current;
		current = current->next;
		delete temp;
	}
}