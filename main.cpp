#include<iostream>
#include<fstream>
#include<string>
using namespace std;
//CSV phonebook
void addContact(const string& name)//Create a new phonebook or Open an existing phonebook and adding a user to it! (phonebook name pass in function)
{
    fstream fi;
    fi.open(name+".csv",ios::out | ios::app);
    if(!fi.is_open())
    {
        cout<<"Error Creating/Opening file!\n";
        return;
    }

    string contactName;
    string contactNumber;
    short int numberOfNumbers;

    cout<<"Enter the Name of user you want to Add: ";
    getline(cin,contactName);

    cout<<"How many number do you wanna add for "<<contactName<<" : ";
    cin>>numberOfNumbers;

    fi<<contactName;

    while (!numberOfNumbers<1)
    {
        cout<<"Enter Number of user you want to Add: ";
        cin>>contactNumber;
        fi<<","<<contactNumber;//file is CSV(comma seprated values)
        --numberOfNumbers;
    }
    fi<<"\n";
    
    fi.close();
}

bool showContact(const string& name)//Reading Existing phonebook!
{
    fstream fi;
    fi.open(name+".csv",ios::in);
    if(!fi.is_open())
    {
        cout<<"Error Opening file! Maybe it does not eixst!\n";
        return false;//if there is no phonebook with that name , function returns false!
    }

    string line;
    while(getline(fi,line))//while there is a line in file put that line to string line variable
    {
        cout<<line<<endl;
    }
    cout<<"==============================================\n";

    fi.close();
    return true;
}

void searchContact(const string&name,const string& key)//Search by name or phone number
{
    fstream fi;
    fi.open(name+".csv",ios::in);
    if(!fi.is_open())
    {
        cout<<"Error Opening file! Maybe it does not eixst!\n";
        return;
    }

    string line;
    bool find=false;

    while(getline(fi,line))
    {
        if(line.find(key)!=string::npos)//if there is key in that line, show the line
        {
            cout<<line<<endl;
            find=true;
        }
    }

    if(!find)//if the key not found
        cout<<"NOT FOUND!\n";

    fi.close();
}

void deleteContact(const string&name)
{
    if(!showContact(name))//if phonebook is not exist terminate operation, if it exist show contacts of phonebook
    {
        cout<<"\nfile not found so the operation has been terminated!\n";
        return;
    }

    cout<<"\n\nWhich one do you wanna delete (Starts from 1): ";
    int choise;
    cin>>choise;
    
    fstream fi;
    fi.open(name+".csv",ios::in);
    if(!fi.is_open())
    {
        cout<<"Unknown Error!\n";
        return;
    }

    fstream fi2;
    fi2.open("Temp.csv",ios::out | ios::app);

    string line;
    while(getline(fi,line))//copy every line of fi file to fi2 file except a line that should remove
    {
        --choise;
        if(choise==0)
            continue;
        fi2<<line+"\n";
    }

    fi.close();

    string N=name+".csv";

    if (fi2.tellg()==0)//Is the new file Empty?, if it's Empty delete that phonebook
    {
        remove("Temp.csv");
        remove(N.c_str());
        fi2.close();
        return;
    }

    fi2.close();

    remove(N.c_str());//remove old file
    rename("Temp.csv",N.c_str());//rename new file to the name of old file
}

int main()
{
    //addContact("Contacts");
    //showContact("Contacts");
    //searchContact("Contacts","my number");
    //deleteContact("Contacts");
}

/*
can you add more functions?
functions ideas: Update, Delete a number(not user),etc.

Is this code look bad?
I will appreciate if you contribute in that project and make the code better :)
*/