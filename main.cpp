#include <iostream>
#include <vector>
#include <windows.h>
#include <fstream>
#include <string>
#include <bits/stdc++.h>

using namespace std;

struct Person
{
    int id;
    string name;
    string surname;
    string telephoneNumber;
    string email;
    string adress;
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
    cout << "9. Zakoncz program" << endl;
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
                newPerson.name += line[i];
                break;
            case 2:
                newPerson.surname += line[i];
                break;
            case 3:
                newPerson.telephoneNumber += line[i];
                break;
            case 4:
                newPerson.email += line[i];
                break;
            case 5:
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
    return newPerson;
}

void readDataFromFile(vector <Person> &friends)
{
    Person newPerson;
    fstream file;
    string line = "";
    int lineNumber = 1;
    file.open("friends_nowy_format.txt", ios::in | ios::app);

    if (!file.good())
    {
        cout << "Blad otwarcia pliku" << endl;
    }
    else
    {
        while (getline(file, line))
        {
            newPerson = splitLineIntoStructFields(line);
            friends.push_back(newPerson);
            lineNumber++;
        }
    }
}

void writeIntoFile(Person toWrite)
{
    fstream file;
    file.open("friends_nowy_format.txt", ios::app);

    if (!file.good())
    {
        cout << "Blad otwarcia pliku wyjsciowego" << endl;
    }
    else
    {
        file << toWrite.id << "|";
        file << toWrite.name << "|";
        file << toWrite.surname << "|";
        file << toWrite.telephoneNumber << "|";
        file << toWrite.email << "|";
        file << toWrite.adress << "|" << endl;
    }

    file.close();
}


void updateFile(vector <Person> friends)
{
    fstream file;
    file.open("friends_nowy_format.txt", ios::out);

    for (size_t i = 0; i < friends.size(); i++)
    {
        file << friends[i].id << "|";
        file << friends[i].name << "|";
        file << friends[i].surname << "|";
        file << friends[i].telephoneNumber << "|";
        file << friends[i].email << "|";
        file << friends[i].adress << "|" << endl;
    }
    file.close();
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


void addRecipient(vector <Person> &friends)
{
    Person newPerson;

    if (friends.size()==0)
    {
        newPerson.id = 1;
    }
    else
    {
        newPerson.id = friends[friends.size()-1].id + 1;
    }
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
                friends.erase(friends.begin() + i);

                updateFile(friends);
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
            updateFile(friends);
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

int main()
{
    vector <Person> friends;
    readDataFromFile(friends);
    char input = 0;

    while (input != '9')
    {
        displayMenu();
        input = getChar();

        switch (input)
        {
        case '1':
            addRecipient(friends);
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
        case '9':
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
