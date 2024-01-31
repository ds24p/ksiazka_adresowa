#include <iostream>
#include <vector>
#include <windows.h>
#include <fstream>
#include <string>
#include <bits/stdc++.h>
#include <cstdio>

using namespace std;

struct Person
{
    int id;
    int userIdPerson;
    string name;
    string surname;
    string telephoneNumber;
    string email;
    string adress;
};

struct User
{
    int userId;
    string userName;
    string password;
};

void displayMenu()
{
    system("cls");
    cout << "-----------------------MENU---------------------" << endl;
    cout << "Wybierz opcje z menu: " << endl;
    cout << "1. Dodaj adresata" << endl;
    cout << "2. Wyszukaj po imieniu" << endl;
    cout << "3. Wyszukaj po nazwisku" << endl;
    cout << "4. Wyswietl wszystkich adresatow" << endl;
    cout << "5. Usun adresata" << endl;
    cout << "6. Edytuj adresata" << endl;
    cout << "7. Zmien haslo" << endl;
    cout << "9. Wyloguj sie" << endl;
}

string readLine()
{
    string input;
    getline(cin, input);
    return input;
}

int readInt()
{
    string input;
    int number;

    while(true)
    {
        getline(cin, input);

        stringstream myStream(input);

        if (myStream >> number)
        {
            break;
        }
        cout << "To nie jest liczba. Wpisz ponownie" << endl;
    }
    return number;
}

char getChar()
{
    string inputStr = "";
    char inputChar = (0);

    while(true)
    {
        inputStr = readLine();

        if (inputStr.length() == 1)
        {
            inputChar = inputStr[0];
            break;
        }
        cout << "To nie jest pojedynczy znak, sproboj ponownie." << endl;
    }

    return inputChar;
}

Person splitLineIntoStructFields(string line)
{
    Person newPerson;
    char separator = '|';
    int i = 0;
    string helpWithId = "";
    string helpWithUserId = "";

    int fieldNumber = 0;
    while (line[i] != '\0')
    {
        if (line[i] != separator)
        {
            switch(fieldNumber)
            {
            case 0:
                helpWithId += line[i];
                break;
            case 1:
                helpWithUserId += line[i];
                break;
            case 2:
                newPerson.name += line[i];
                break;
            case 3:
                newPerson.surname += line[i];
                break;
            case 4:
                newPerson.telephoneNumber += line[i];
                break;
            case 5:
                newPerson.email += line[i];
                break;
            case 6:
                newPerson.adress += line[i];
                break;
            }
        }
        else
        {
            fieldNumber++;
        }
        i++;
    }
    newPerson.id = stoi(helpWithId);
    newPerson.userIdPerson = stoi(helpWithUserId);
    return newPerson;
}

void readDataFromFile(vector <Person> &friends, int currentUserId)
{
    Person newPerson;
    fstream file;
    string line = "";
    int lineNumber = 1;
    file.open("persons.txt", ios::in | ios::app);

    if (!file.good())
    {
        cout << "Blad otwarcia pliku" << endl;
    }
    else
    {
        while (getline(file, line))
        {
            newPerson = splitLineIntoStructFields(line);
            if (newPerson.userIdPerson == currentUserId)
            {
                friends.push_back(newPerson);
            }
            lineNumber++;
        }
    }
}

void writeIntoFile(Person toWrite)
{
    fstream file;
    file.open("persons.txt", ios::app);

    if (!file.good())
    {
        cout << "Blad otwarcia pliku wyjsciowego" << endl;
    }
    else
    {
        file << toWrite.id << "|";
        file << toWrite.userIdPerson << "|";
        file << toWrite.name << "|";
        file << toWrite.surname << "|";
        file << toWrite.telephoneNumber << "|";
        file << toWrite.email << "|";
        file << toWrite.adress << "|" << endl;
    }

    file.close();
}


void updateFile(Person updatedFriend, char mode)
{
    fstream file;
    file.open("persons.txt", ios::in);
    fstream newFile;
    newFile.open("persons_new.txt", ios::app);

    int i = 0;
    string line = "";
    while (getline(file, line))
    {
        i = 0;
        string helpWithId = "";
        int contactId = 0;
        while (line[i] != '|')
        {
            helpWithId += line[i];
            i++;
        }
        contactId = stoi(helpWithId);

        if(contactId == updatedFriend.id && mode == 'e')
        {
            newFile << updatedFriend.id << "|";
            newFile << updatedFriend.userIdPerson << "|";
            newFile << updatedFriend.name << "|";
            newFile << updatedFriend.surname << "|";
            newFile << updatedFriend.telephoneNumber << "|";
            newFile << updatedFriend.email << "|";
            newFile << updatedFriend.adress << "|" << endl;
        }
        else if(contactId == updatedFriend.id && mode == 'd')
        {
            ;
        }
        else
        {
            newFile << line << endl;
        }
    }
    file.close();
    newFile.close();

    remove("persons.txt");

    if (rename("persons_new.txt", "persons.txt") != 0)
		perror("Error renaming file");
	else
		cout << "File renamed successfully";
}

void printPerson(Person person)
{
    cout << "Numer id: " << person.id << endl;
    cout << "Imie: " << person.name << endl;
    cout << "Nazwisko: " << person.surname << endl;
    cout << "Numer telefonu: " << person.telephoneNumber << endl;
    cout << "Email: " << person.email << endl;
    cout << "Adres: " << person.adress << endl << endl;
}

int findId()
{
    fstream file;
    file.open("persons.txt", ios::in);

    int i = 0;
    int contactId = 0;
    string line = "";
    while (getline(file, line))
    {
        i = 0;
        string helpWithId = "";
        contactId = 0;
        while (line[i] != '|')
        {
            helpWithId += line[i];
            i++;
        }
        contactId = stoi(helpWithId);
    }
    return contactId + 1;
}

void addRecipient(vector <Person> &friends, int currentUserId)
{
    Person newPerson;

    newPerson.id = findId();

    newPerson.userIdPerson = currentUserId;
    cout << "Podaj imie dodawanej osoby: ";
    newPerson.name = readLine();
    cout << "Podaj nazwisko dodawanej osoby: ";
    newPerson.surname = readLine();
    cout << "Podaj numer telefonu dodawanej osoby: ";
    newPerson.telephoneNumber = readLine();
    cout << "Podaj email dodawanej osoby: ";
    newPerson.email = readLine();
    cout << "Podaj adres pocztowy dodawanej osoby: ";
    newPerson.adress = readLine();

    friends.push_back(newPerson);
    writeIntoFile(newPerson);

    cout << "Dodano nastepujaca osobe: " << endl << endl;
    printPerson(newPerson);

    system("pause");
}

void showAllFriends(vector <Person> &friends)
{
    for (size_t i = 0; i < friends.size(); i++)
    {
        printPerson(friends[i]);
    }
    if (friends.size() == 0)
    {
        cout << "Lista kontaktow jest pusta..." << endl << endl;
    }
    system("pause");
}

void searchForName(vector <Person> &friends)
{
    string searchedName;
    bool doesNotExist = true;
    cout << "Podaj imie osoby/osob ktore chcesz znalezc: ";
    searchedName = readLine();

    for (size_t i = 0; i < friends.size(); i++)
    {
        if (friends[i].name == searchedName)
        {
            printPerson(friends[i]);
            doesNotExist = false;
        }
    }
    if (doesNotExist)
    {
        cout << "W Twojej bazie przyjaciol nie istnieje osoba o podanym imieniu. "
             << endl
             << endl;
    }
    system("pause");
}

void searchForSurname(vector <Person> &friends)
{
    string searchedSurname;
    bool doesNotExist = true;
    cout << "Podaj nazwisko osoby/osob ktore chcesz znalezc: ";
    searchedSurname = readLine();

    for (size_t i = 0; i < friends.size(); i++)
    {
        if (friends[i].surname == searchedSurname)
        {
            printPerson(friends[i]);
            doesNotExist = false;
        }
    }
    if (doesNotExist)
    {
        cout << "W Twojej bazie przyjaciol nie istnieje osoba o podanym nazwisku. "
             << endl
             << endl;
    }
    system("pause");
}

void deleteContact(vector <Person> &friends)
{
    int deletedId = 0;
    bool doesNotExist = true;

    cout << "Podaj id kontaktu, ktory chcesz usunac: " << endl;
    deletedId = readInt();

    for (size_t i = 0; i < friends.size(); i++)
    {
        if (friends[i].id == deletedId)
        {
            doesNotExist = false;
            cout << "Czy na pewno chcesz usunac kontakt o id: "<< deletedId << "? Potwierdz wybierajac 't' " << endl;
            char choice = getChar();
            if(choice == 't')
            {
                cout << "Usuwam kontakt o id: " << deletedId << endl;
                updateFile(friends[i], 'd');
                friends.erase(friends.begin() + i);
            }

        }
    }
    if (doesNotExist)
    {
        cout << "W Twojej bazie przyjaciol nie istnieje kontakt o podanym id. "
             << endl
             << endl;
    }
    system("pause");
}

void displayMenuForContactEdition()
{
    system("cls");
    cout << "Wybierz odpowiednia opcje:" << endl;
    cout << "1. Edycja imienia" << endl;
    cout << "2. Edycja nazwiska" << endl;
    cout << "3. Edycja numeru telefonu" << endl;
    cout << "4. Edycja adresu email" << endl;
    cout << "5. Edycja adresu" << endl;
    cout << "6. Powrot do menu glownego" << endl;
}

void editContactFields(Person &person)
{
    char choice = 0;
    while (choice != '6')
    {
        displayMenuForContactEdition();
        choice = getChar();

        switch (choice)
        {
        case '1':
            cout << "Nowe imie: " << endl;
            person.name = readLine();
            break;
        case '2':
            cout << "Nowe nazwisko: " << endl;
            person.surname = readLine();
            break;
        case '3':
            cout << "Nowy numer telefonu: " << endl;
            person.telephoneNumber = readLine();
            break;
        case '4':
            cout << "Nowy adres email: " << endl;
            person.email = readLine();
            break;
        case '5':
            cout << "Nowy adres zamieszkania: " << endl;
            person.adress = readLine();
            break;
        case '6':
            break;
        default:
            cout << "Wprowadziles znak nieobslugiwany przez menu programu. Sproboj ponownie." << endl;
            system("pause");
            break;
        }
    }
}

void editContact(vector <Person> &friends)
{
    int editedId = 0;
    bool doesNotExist = true;

    cout << "Podaj id kontaktu, ktory chcesz edytowac: " << endl;
    editedId = readInt();

    for (size_t i = 0; i < friends.size(); i++)
    {
        if (friends[i].id == editedId)
        {
            doesNotExist = false;
            cout << "Edycja kontaktu o id: " << editedId << endl;
            editContactFields(friends[i]);
            cout << "Dane kontaktu po edycji:" << endl;
            printPerson(friends[i]);
            updateFile(friends[i], 'e');
        }
    }
    if (doesNotExist)
    {
        cout << "W Twojej bazie przyjaciol nie istnieje kontakt o podanym id. Wybierz opcje: "
             << endl << "1. Ponowne wprowadzenie id" << endl
             << endl << "Dowolny znak. Powrot do menu glownego" << endl;
        int choice = getChar();
        if(choice == '1')
        {
            editContact(friends);
        }
    }
    system("pause");

}

void updateUserFile(vector <User> users);

void changePassword(int currentUserId, vector <User> &users)
{
    string newPassword = "";
    cout << "Podaj nowe haslo: ";
    newPassword = readLine();

    for (size_t i = 0; i < users.size(); i++)
    {
        if (users[i].userId == currentUserId)
        {
            users[i].password = newPassword;
            break;
        }
    }

    updateUserFile(users);
    cout << "Haslo zostalo zmienione" << endl;
    system("pause");
}

void oldMain(int currentUserId, vector <User> &users)
{
    vector <Person> friends;
    readDataFromFile(friends, currentUserId);
    char input = 0;

    while (input != '9')
    {
        displayMenu();
        input = getChar();

        switch (input)
        {
        case '1':
            addRecipient(friends, currentUserId);
            break;
        case '2':
            searchForName(friends);
            break;
        case '3':
            searchForSurname(friends);
            break;
        case '4':
            showAllFriends(friends);
            break;
        case '5':
            deleteContact(friends);
            break;
        case '6':
            editContact(friends);
            break;
        case '7':
            changePassword(currentUserId, users);
            break;
        case '9':
            cout << "Nastapi wylogowanie uzytkownika o Id: " << currentUserId << endl;
            system("pause");
            break;
        default:
            cout << "Wprowadziles znak nieobslugiwany przez menu programu. Sproboj ponownie." << endl;
            system("pause");
            break;
        }
    }
}

void displayLoginMenu()
{
    system("cls");
    cout << "Wybierz odpowiednia opcje:" << endl;
    cout << "1. Logowanie" << endl;
    cout << "2. Rejestracja" << endl;
    cout << "3. Zamknij program" << endl;
}

User splitLineIntoStructFieldsUser(string line)
{
    User newUser;
    char separator = '|';
    int i = 0;
    string helpWithId = "";

    int fieldNumber = 0;
    while (line[i] != '\0')
    {
        if (line[i] != separator)
        {
            switch(fieldNumber)
            {
            case 0:
                helpWithId += line[i];
                break;
            case 1:
                newUser.userName += line[i];
                break;
            case 2:
                newUser.password += line[i];
                break;
            }
        }
        else
        {
            fieldNumber++;
        }
        i++;
    }
    newUser.userId = stoi(helpWithId);
    return newUser;
}

void readUsersDataFromFile(vector <User> &users)
{
    User newUser;
    fstream file;
    string line = "";
    int lineNumber = 1;
    file.open("uzytkownicy.txt", ios::in | ios::app);

    if (!file.good())
    {
        cout << "Blad otwarcia pliku" << endl;
    }
    else
    {
        while (getline(file, line))
        {
            newUser = splitLineIntoStructFieldsUser(line);
            users.push_back(newUser);
            lineNumber++;
        }
    }
}

void writeUserIntoFile(User toWrite)
{
    fstream file;
    file.open("uzytkownicy.txt", ios::app);

    if (!file.good())
    {
        cout << "Blad otwarcia pliku wyjsciowego" << endl;
    }
    else
    {
        file << toWrite.userId << "|";
        file << toWrite.userName << "|";
        file << toWrite.password << "|" << endl;
    }

    file.close();
}


void updateUserFile(vector <User> users)
{
    fstream file;
    file.open("uzytkownicy.txt", ios::out);

    for (size_t i = 0; i < users.size(); i++)
    {
        file << users[i].userId << "|";
        file << users[i].userName<< "|";
        file << users[i].password << "|" << endl;
    }
    file.close();
}

void printUser(User user)
{
    cout << "Numer id: " << user.userId << endl;
    cout << "Nazwa uzytkownika: " << user.userName << endl;
    cout << "Haslo uzytkownika: " << user.password << endl << endl;
}

void registerUser(vector <User> &users)
{
    User newUser;

    if (users.size() == 0)
    {
        newUser.userId = 1;
    }
    else
    {
        newUser.userId = users[users.size()-1].userId + 1;
    }
    cout << "Podaj nazwe uzytkownika: ";
    newUser.userName = readLine();
    cout << "Podaj haslo uzytkownika: ";
    newUser.password = readLine();

    users.push_back(newUser);
    writeUserIntoFile(newUser);

    cout << "Zarejestrowano nastepujacego uzytkownika: " << endl << endl;
    printUser(newUser);

    system("pause");
}

int logIn(vector <User> users)
{
    string name, password;
    int attempt = 3;
    cout << "Podaj nazwe uzytkownika: ";
    name = readLine();
    for (size_t i = 0; i < users.size(); i++)
    {
        if(users[i].userName == name)
        {
            while(attempt > 0)
            {
                cout << "Podaj haslo uzytkownika: ";
                password = readLine();
                if(users[i].password == password)
                {
                    return users[i].userId;
                }
                else
                {
                    attempt--;
                    cout << "Niepoprawne haslo. " << "Pozostalo " << attempt << " prob." << endl;
                }
            }
            return 0;
        }
    }
    cout << "Nieodnaleziono uzytkownika o podanej nazwie" << endl;
    return 0;
}

int main()
{
    vector <User> users;
    readUsersDataFromFile(users);
    char input = '0';
    int currentUserId = 0;
    while (input != '3')
    {
        displayLoginMenu();
        input = getChar();

        switch (input)
        {
        case '1':
            currentUserId = logIn(users);
            if(currentUserId)
            {
                oldMain(currentUserId, users);
            }
            else
            {
                cout << "Nieudane logowanie." << endl;
                system("pause");
            }
            break;
        case '2':
            registerUser(users);
            break;
        case '3':
            break;
        default:
            cout << "Wprowadziles znak nieobslugiwany przez menu programu. Sproboj ponownie." << endl;
            system("pause");
            break;
        }
    }

    cout << "Koncze program" << endl;

    return 0;
}
