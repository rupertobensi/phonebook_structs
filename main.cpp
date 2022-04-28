#include <iostream>
#include <string> //for getline
#include <windows.h> //for cls
#include <stdlib.h>
#include <fstream> //IO files
#include <vector>
#include <sstream> // stringstream

using namespace std;

struct User {
    int id;
    string name, password;
};

struct Person {
  int id, userID;
  string firstName, lastName, phone, email, adress;
};

void readUsers(vector <User> &users) {
  fstream file;
  file.open("user.txt", ios::in);
  if (!file.good()) {
    cout << "Your phonebook is empty. Please add some contacts!" << endl;
    cout << "Press Enter to Continue";
    cin.sync(), cin.get();
  }

  else {
    string line, part;
    User user;
    vector <string> tempVector;

    while(getline(file, line)) {
      stringstream partedLine (line);
      while(getline(partedLine, part, '|')) {
          tempVector.push_back(part);
      }
      user.id = atoi(tempVector[0].c_str());
      user.name = tempVector[1];
      user.password = tempVector[2];
      users.push_back(user);
      tempVector.clear();
    }
  }
  file.close();
}

void addAUser (vector <User> &users) {
  User user;
  string name;
  int size = users.size();
  int counter = 0;

  cout << "Enter user name" << endl;
  cin >> name;

  for (int i = 0; i < size; i++) {
    if (users[i].name == name) {
      counter++;
    }
  }
 
  if (counter == 0) {
    if (size == 0) {
    user.id = 1;
    }

    else {
      user.id = users[size - 1].id + 1;
    }

    user.name = name;
    cout << "Enter password" << endl;
    cin >> user.password;
    users.push_back(user);

    fstream file;
    file.open("user.txt", ios::out | ios::app); // ios::app appends
    file << users[size].id << "|";
    file << users[size].name << "|";
    file << users[size].password << "|" << endl;
    file.close();
  }
  else cout << "User name already taken!" << endl;

}

int logIn (vector <User> &users) {
  string name, password;
  int size = users.size();
  cout << size << " <- SIZE" << endl;
  cout << "Enter user name" << endl;
  cin >> name;

  for (int i = 0; i < size; i++) {
    if (users[i].name == name) {
      for (int j = 0; j < 3; j++) {
        cout << "Enter password. You have " << 3 - j << " attempts left" << endl;
        cin >> password;

        if (users[i].password == password) {
          cout << "You are logged in" << endl;
          Sleep(1000);
          return users[i].id;
        }
      }
    }
  }
  cout << "No such user has been registered!" << endl;
  return 0;
}

void changePassword(vector <User> &users, int userID) {
  cout << "Enter new password" << endl;
  for (int i = 0; i < users.size(); i ++) {
    if (users[i].id == userID) {
      cin >> users[i].password;
    }
  }

  ofstream fileDelete("user.txt");
  fstream file;
  int size = users.size();

  for (int i = 0; i < size; i ++) {
  file.open("user.txt", ios::out | ios::app); // ios::app appends
  file << users[i].id << "|";
  file << users[i].name << "|";
  file << users[i].password << "|" << endl;
  file.close();
  }
  users.clear();
  readUsers(users);

}

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
      contact.userID = atoi(tempVector[1].c_str());
      contact.firstName = tempVector[2];
      contact.lastName = tempVector[3];
      contact.phone = tempVector[4];
      contact.email = tempVector[5];
      contact.adress = tempVector[6];
      contacts.push_back(contact);
      tempVector.clear();
    }
  }
  file.close();
}

void addAContact(vector <Person> &contacts, int userID) {

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
  file << userID << "|";
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
  for (int i = 0; i < contacts.size(); i ++){
    if (contacts[i].id == id) {
      cin.ignore();
      getline(cin, contacts[i].adress);
      rearrangeContacts(contacts);
    }
  }
}

int main () {
  vector <User> users;
  vector <Person> contacts;
  readContacts(contacts);
  readUsers(users);
  int userID = 0;

  while (1) {
    if (userID == 0 ) {
      char choice;
      system("cls");
      cout << "1. Log in" << endl;
      cout << "2. Register" << endl;
      cout << "3. Quit program" << endl;

      cin >> choice;

      if (choice == '1') {
        userID = logIn(users);
        cout << endl << userID << " user id " << endl;
        Sleep(1500);
      }

      else if (choice == '2') {
        addAUser(users);
        askForEnter();
      }

      else if (choice == '3') {
        exit(0);
      }
    }
    
    else {
      char choice;
      system("cls");
      cout << "1. Add a contact" << endl;
      cout << "2. Search contacts by first name" << endl;
      cout << "3. Search contacts by last name" << endl;
      cout << "4. Display all contacts" << endl;
      cout << "5. Remove a contact" << endl;
      cout << "6. Edit a contact" << endl;
      cout << "7. Change password" << endl;
      cout << "8. Log out" << endl;

      cin >> choice;

      if (choice == '1') {
        addAContact(contacts, userID);
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

      else if (choice == '7') {
        changePassword(users, userID);
      }

      else if (choice == '8') {
        userID = 0;
      }
    }
  }

  return 0;
}
