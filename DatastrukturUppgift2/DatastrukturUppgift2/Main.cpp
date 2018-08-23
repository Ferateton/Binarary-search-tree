#include "BinarySearchTree.h"
#include "BinarySearchTree.cpp"
#include <string>
#include "Main.h"

Main::Main(void) { }
Main::~Main(void) { }

int main() {
	BinarySearchTree<string, string, int, int> b;
	int ch;
	int tmp3, tmp4;
	string tmp1, tmp2;
	if (b.Load())
		cout << "Register loaded" << endl;
	while (1) {
		cout << endl << endl;
		cout << " Game Register " << endl;
		cout << " ============================ " << endl;
		cout << " 1. Insertion" << endl;
		cout << " 2. In-Order Traversal " << endl;
		cout << " 3. Delete " << endl;
		cout << " 4. Search by name" << endl;
		cout << " 5. Search by genre" << endl;
		cout << " 6. Save the register" << endl;
		cout << " 7. Exit " << endl;
		cout << " Enter your choice : ";
		cin >> ch;
		switch (ch) {
		case 1: cout << " Enter name of game to be inserted : ";
			cin.ignore(1);
			getline(cin, tmp1);
			cout << " Genre: ";
			getline(cin, tmp2);
			cout << " Year it was made: ";
			cin >> tmp3;
			cout << " Rating 1-5: ";
			cin.ignore(1);
			cin >> tmp4;
			b.Insert(tmp1, tmp2, tmp3, tmp4);
			cout << "\n Inserted: " << tmp1;
			break;
		case 2: cout << endl;
			cout << " In-order traversal " << endl;
			cout << " ============================" << endl;
			b.Print();
			break;

		case 3: cout << " Enter name of game to be deleted : ";
			cin.clear();
			cin.ignore(1);
			getline(cin, tmp1);
			b.Delete(tmp1);                     
			break;
		case 4: cout << " Search by name : ";
			cin.ignore(1);
			getline(cin, tmp1);
			b.Find(tmp1, "");                   
			break;
		case 5: cout << " Search by genre : ";
			cin.ignore(1);
			getline(cin, tmp1);
			b.Find("", tmp1);                  
			break;
		case 6: b.Save();
			break;
		case 7: system("pause");
			return 0;
			break;
		}
	}
}