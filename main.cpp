#include<iostream>
#include<fstream>
#include<string>
using namespace std;

const string FILE_NAME = "Contacts.csv";

//CSV phonebook
void addContact()//Create a new phonebook or Open an existing phonebook and adding a user to it! (phonebook name pass in function)
{
    fstream fin; // File stream variable
    string contactName; // The name of the contact
    string contactNumber; // The number of the contact
    unsigned short int numberOfUserContactNumbers; // the amount of user contact numbers to be added

    fin.open(FILE_NAME.c_str(),ios::out | ios::app);

    //Check if the file is open, cancel function if it is not
    if(!fin.is_open())
    {
        cout << "Error Creating/Opening file!\n";
        return;
    }

    cout<<"Enter the name of user you want to add: ";
    getline(cin,contactName);

    cout << "How many contact numbers do you wanna add for " << contactName << " : ";
    cin>>numberOfUserContactNumbers;

    fin << contactName;

    while (!numberOfUserContactNumbers < 1)
    {
        cout << "Enter the number of user you want to Add: ";

        cin>>contactNumber;

        fin << "," << contactNumber;//file is CSV(comma seprated values)

        --numberOfUserContactNumbers;
    }

    fin << "\n";
    
    fin.close();
}

bool showContact()//Reading Existing phonebook!
{
    fstream fin; // File stream variable
    string line; // The line being read from the file

    fin.open(FILE_NAME.c_str(),ios::in);

    //Check if the file is open, cancel function if it is not
    if(!fin.is_open())
    {
        cout << "Error Opening file! Maybe it does not eixst!\n";
        return false;//if there is no phonebook with that name , function returns false!
    }

    
    while(getline(fin,line))//while there is a line in file put that line to string line variable
    {
        cout << line << endl;
    }
    cout << "==============================================\n";

    fin.close();
    return true;
}

void searchContact(const string& key)//Search by name or phone number
{
    fstream fin; // File stream variable
    string line; // The line being read from the file
    bool found = false; // The condition if the contact has been found

    //Check if the file is open, cancel function if it is not
    fin.open(FILE_NAME.c_str(),ios::in);

    if(!fin.is_open())
    {
        cout<<"Error Opening file! Maybe it does not eixst!\n";
        return;
    }  

    //Break the loop once at the end of the file, or if the contact has been found
    while(getline(fin,line) && !found)
    {
        if(line.find(key)!=string::npos)//if there is key in that line, show the line
        {
            cout<<line<<endl;
            found=true;
        }
    }

    if(!found)//if the key not found
        cout<<"NOT FOUND!\n";

    fin.close();
}

void deleteContact()
{
    unsigned int choice; // the choice from the user
    fstream fin; // File stream variable
    fstream fin2; // File stream variable
    string line; // The line being read from the file

    if(!showContact())//if phonebook is not exist terminate operation, if it exist show contacts of phonebook
    {
        cout<<"\nfile not found so the operation has been terminated!\n";
        return;
    }

    cout << "\n\nWhich one do you wanna delete (Starts from 1): ";
    cin>>choice;
    
    fin.open(FILE_NAME.c_str(),ios::in);

    if(!fin.is_open())
    {
        cout<<"Unknown Error!\n";
        return;
    }

    fin2.open("Temp.csv",ios::out | ios::app);

    while(getline(fin,line))//copy every line of fi file to fi2 file except a line that should remove
    {
        --choice;
        if(choice==0)
            continue;
        fin2 << line + "\n";
    }

    fin.close();

    if (fin2.tellg()==0)//Is the new file Empty?, if it's Empty delete that phonebook
    {
        remove("Temp.csv");
        remove(FILE_NAME.c_str());
        fin2.close();
        return;
    }

    fin2.close();

    remove(FILE_NAME.c_str());//remove old file
    rename("Temp.csv",FILE_NAME.c_str());//rename new file to the name of old file
}

int main()
{
    //addContact();
    //showContact();
    //searchContact("my number");
    //deleteContact();
}

/*
can you add more functions?
functions ideas: Update, Delete a number(not user),etc.

Is this code look bad?
I will appreciate if you contribute in that project and make the code better :)
*/