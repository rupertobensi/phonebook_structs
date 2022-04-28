#include <iostream>
#include <string> //for getline
#include <windows.h> //for cls
#include <stdlib.h>
#include <fstream> //IO files
#include <vector>
#include <sstream> // stringstream

using namespace std;

struct Person {
  int id;
  string firstName, lastName, phone, email, adress;
};

void readContacts(vector <Person> &contacts) {
  fstream file;
  file.open("file.txt", ios::in);
  if (!file.good()) {
    cout << "Your phonebook is empty. Please add some contacts!" << endl;
    cout << "Press Enter to Continue";
    cin.sync(), cin.get();
  }

  else {
    string line, part;
    Person contact;
    vector <string> tempVector;

    while(getline(file, line)) {
      stringstream partedLine (line);
      while(getline(partedLine, part, '|')) {
          tempVector.push_back(part);
      }
      contact.id = atoi(tempVector[0].c_str());
      contact.firstName = tempVector[1];
      contact.lastName = tempVector[2];
      contact.phone = tempVector[3];
      contact.email = tempVector[4];
      contact.adress = tempVector[5];
      contacts.push_back(contact);
      tempVector.clear();
    }
  }
  file.close();
}

void addAContact(vector <Person> &contacts) {
  Person contact;

  cout << "Whats the first name?" << endl;
  cin >> contact.firstName;
  cout << "Last name?" << endl;
  cin >> contact.lastName;
  cout << "Phone number?" << endl;
  cin.ignore();
  getline(cin, contact.phone);
  cout << "E-mail?" << endl;
  cin >> contact.email;
  cout << "Adress?" << endl;
  cin.ignore();
  getline(cin, contact.adress);

  int size = contacts.size();

  if (size == 0) {
    contact.id = 1;
  }

  else {
    contact.id = contacts[size - 1].id + 1;
  }

  contacts.push_back(contact);

  fstream file;
  file.open("file.txt", ios::out | ios::app); // ios::app appends
  file << contacts[size].id << "|";
  file << contacts[size].firstName << "|";
  file << contacts[size].lastName << "|";
  file << contacts[size].phone << "|";
  file << contacts[size].email << "|";
  file << contacts[size].adress << "|" << endl;
  file.close();

}

void askForEnter () {
  cout << "Press Enter to Continue";
  cin.ignore(), cin.get();
}

void displayContacts(vector <Person> &contacts) {
  cout << endl << "You have " << contacts.size() << " current contacts in your phonebook: "  << endl;

  for (int i = 0; i < contacts.size(); i++) {
    cout << "id: " << contacts[i].id;
    cout << "  First name: " << contacts[i].firstName << "  Last name: " << contacts[i].lastName << "  Phone: " << contacts[i].phone;
    cout << "  email: " << contacts[i].email << "  Adress: " << contacts[i].adress << endl << endl;
  }
}

void searchContactsByFirstName(vector <Person> &contacts) {
  string search;
  int counter = 0;
  cout << "Please, enter the first name to search" << endl;
  cin >> search;

  for (int i = 0; i < contacts.size(); i++) {
    if (contacts[i].firstName == search) {
      counter++;
      cout << "* Found a contact with id number: " << contacts[i].id << endl;
      cout << "First name: " << contacts[i].firstName << "  Last name: " << contacts[i].lastName << "  Phone :" << contacts[i].phone;
      cout << "  email: " << contacts[i].email << "  Adress: " << contacts[i].adress << endl << endl;
    }
  }

  if (counter == 0) {
    cout << "There is no contact with this first name" << endl;
  }
}

void searchContactsByLastName(vector <Person> &contacts) {
  string search;
  int counter = 0;
  cout << "Please, enter the last name to search" << endl;
  cin >> search;

  for (int i = 0; i < contacts.size(); i++) {
    if (contacts[i].lastName == search) {
      counter++;
      cout << "* Found a contact with id number: " << contacts[i].id << endl;
      cout << "First name: " << contacts[i].firstName << "  Last name: " << contacts[i].lastName << "  Phone :" << contacts[i].phone;
      cout << "  email: " << contacts[i].email << "  Adress: " << contacts[i].adress << endl << endl;
    }
  }

  if (counter == 0) {
    cout << "There is no contact with this last name" << endl;
  }
}

void rearrangeContacts(vector <Person> &contacts) {
  ofstream fileDelete("file.txt");
  fstream file;
  int size = contacts.size();

  for (int i = 0; i < size; i ++) {
  file.open("file.txt", ios::out | ios::app); // ios::app appends
  file << contacts[i].id << "|";
  file << contacts[i].firstName << "|";
  file << contacts[i].lastName << "|";
  file << contacts[i].phone << "|";
  file << contacts[i].email << "|";
  file << contacts[i].adress << "|" << endl;
  file.close();
  }
  contacts.clear();
  readContacts(contacts);
}

void removeAContact(vector <Person> &contacts) {
  int id;
  int counter = 0;
  displayContacts(contacts);
  cout << "Which id should get removed?" << endl;
  cin >> id;

  for (int i = 0; i < contacts.size(); i++) {

    if (contacts[i].id == id) {
    counter++;
      cout << "Are you sure? Press 'y' to confirm or 'n' to abort" << endl;
      char choice;
      cin >> choice;
      switch (choice) {
        case 'y': {
          contacts.erase(contacts.begin() + i);
          rearrangeContacts(contacts);
          break;
          }
        case 'n': {
          break;
        }
        default: {
          break;
        }
      }
    }
  }
  if (counter == 0) {
    cout << "There is no person with this id!" << endl;
    Sleep(1500);
  }
}

void editFirstName(vector <Person> &contacts, int id) {
  cout << "Enter new first name for the contact" << endl;
  for (int i = 0; i < contacts.size(); i ++) {
    if (contacts[i].id == id) {
      cin >> contacts[i].firstName;
      rearrangeContacts(contacts);
    }
  }
}

void editLastName(vector <Person> &contacts, int id) {
  int counter = 0;
  cout << "Enter new last name for the contact" << endl;
  for (int i = 0; i < contacts.size(); i ++) {
    if (contacts[i].id == id) {
      cin >> contacts[i].lastName;
      rearrangeContacts(contacts);
    }
  }
}

void editPhone(vector <Person> &contacts, int id) {
  cout << "Enter new phone number for the contact" << endl;
  for (int i = 0; i < contacts.size(); i ++) {
    if (contacts[i].id == id) {
      cin.ignore();
      getline(cin, contacts[i].phone);
      rearrangeContacts(contacts);
    }
  }
}

void editEmail(vector <Person> &contacts, int id) {
  cout << "Enter new email for the contact" << endl;
  for (int i = 0; i < contacts.size(); i ++) {
    if (contacts[i].id == id) {
      cin >> contacts[i].email;
      rearrangeContacts(contacts);
    }
  }
}

void editAdress(vector <Person> &contacts, int id) {
  cout << "Enter new adress for the contact" << endl;
  for (int i = 0; i < contacts.size(); i ++) {
    if (contacts[i].id == id) {
      cin.ignore();
      getline(cin, contacts[i].adress);
      rearrangeContacts(contacts);
    }
  }
}

int main () {
  vector <Person> contacts;
  readContacts(contacts);

  while (1) {
    char choice;
    system("cls");
    cout << "1. Add a contact" << endl;
    cout << "2. Search contacts by first name" << endl;
    cout << "3. Search contacts by last name" << endl;
    cout << "4. Display all contacts" << endl;
    cout << "5. Remove a contact" << endl;
    cout << "6. Edit a contact" << endl;
    cout << "9. Quit program" << endl;

    cin >> choice;

    if (choice == '1') {
      addAContact(contacts);
    }

    else if (choice == '2') {
      searchContactsByFirstName(contacts);
      askForEnter();
    }

    else if (choice == '3') {
      searchContactsByLastName(contacts);
      askForEnter();
    }

    else if (choice == '4') {
      displayContacts(contacts);
      askForEnter();
    }

    else if (choice == '5') {
      removeAContact(contacts);
    }

    else if (choice == '6') {
      int id;
      int counter = 0;
      char choice2;
      system("cls");
      displayContacts(contacts);
      cout << "Which contact do you want to edit? Enter id number" << endl;
      cin >> id;

      for (int i = 0; i < contacts.size(); i++) {
        if (contacts[i].id == id) {
          counter++;
        }
      }

      switch (counter) {
        case 0: {
          cout << "There is no person with this id!" << endl;
          Sleep(1500);
          break;
        }

        default: {
          cout << "What do you want to edit?" << endl;
          cout << "1. First Name" << endl;
          cout << "2. Last name" << endl;
          cout << "3. Phone number" << endl;
          cout << "4. E-mail"<< endl;
          cout << "5. Adress" << endl;
          cout << "6. Return to main menu" << endl;
          cin >> choice2;

          switch (choice2) {
            case '1': {
              editFirstName(contacts, id);
              break;
            }

            case '2': {
              editLastName(contacts, id);
              break;
            }

            case '3': {
              editPhone(contacts, id);
              break;
            }

            case '4': {
              editEmail(contacts, id);
              break;
            }

            case '5': {
              editAdress(contacts, id);
              break;
            }

            case '6': {
              break;
            }

            default: {
              break;
            }
          }
          break;
        }
      }
    }

    else if (choice == '9') {
      exit(0);
    }
  }

  return 0;
}