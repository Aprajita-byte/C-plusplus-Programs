//************************************************************************************************
//                                     HEADER FILES 
//************************************************************************************************
#include<iostream>
#include<fstream>
#include<cctype>
#include<iomanip>
using namespace std;

//************************************************************************************************
//                                CLASSES USED IN PROJECT
//************************************************************************************************
class account{
    int acno;
    char name[50];
    int deposit;
    char type;
    public:
    void create_account(); //function to get input from user
    void show_account() const;  //function to show data on screen
    void modify();  //function to add new data
    void dep(int);  //function to accept amount and add to balance
    void draw(int);  //function to accept amount and subtract from balance
    void report()const;  //function to show data in tabular format
    int retacno()const;  //function to return account number
    int retdeposit()const;  //function to return balance amount
    char rettype()const;  //function to return type of account
}; 
//******************************class end here****************************************************
void account :: create_account(){
    cout<<"\nEnter the Account Number(6-digit No.):";
    cin>>acno;
    cout<<"\nEnter the Name of Account holder:";
    cin.ignore();
    cin.getline(name,50);
    cout<<"\nEnter the type of Account (C for current/S for saving):";
    cin>>type;
    type = toupper(type);
    cout<<"\nEnter the Initial Amount (>=500 for saving and >=1000 for current):";
    cin>>deposit;
    cout<<"\n\nAccount Created Successfully...............\n";
}
void account :: show_account() const{
    cout<<"\n\n----------Account and Balance Details----------"<<endl;
    cout<<"Account Number : "<<acno<<endl;
    cout<<"Account Holder Name : "<<name<<endl;
    cout<<"Type of Account : "<<type<<endl;
    cout<<"Balance Amount : "<<deposit<<endl;

}
void account :: modify(){
    cout<<"\nAccount Number :"<<acno;
    cout<<"\n\nEnter the Modified Account Holder Name:";
    cin.ignore();
    cin.getline(name,50);
    cout<<"\nEnter the Modified the type of Account (C for current/S for saving):";
    cin>>type;
    type = toupper(type);
    cout<<"\nEnter the Modified Balance Amount:";
    cin>>deposit;
    cout<<"\nAccount Modified Successfully...............\n";
}
void account :: dep(int x){
    deposit += x;
}
void account :: draw(int x){
    deposit -= x;
}
void account :: report()const{
    cout<<acno<<setw(10)<<" "<<name<<setw(20)<<" "<<type<<setw(18)<<" "<<deposit<<endl;
}
int account :: retacno() const{
    return acno;
}
int account :: retdeposit() const{
    return deposit;
}
char account :: rettype() const{
    return type;
}
//************************************************************************************************
//                              FUNCTION DECLARATION
//************************************************************************************************
void write_account();  //function to write record in binary file
void display_sp(int);  //function to display account details given by user
void modify_account(int);  //function to modify record of file
void delete_account(int);  //function to delete record of file
void display_all();  //function display all the details of account
void deposit_withdraw(int,int);  //function to deposit/withdraw amount from given account
void intro();  //introductory screen function
//************************************************************************************************
//                             MAIN FUNCTION OF PROGRAM
//************************************************************************************************
int main()
{
    char ch;
    int num;
    intro();
    do{
        system("cls");
        cout<<"\n\n-----------------MAIN MENU-----------------"<<endl;
        cout<<"\n1.NEW ACCOUNT";
        cout<<"\n2.DEPOSIT AMOUNT";
        cout<<"\n3.WITHDRAW AMOUNT";
        cout<<"\n4.BALANCE ENQUIRY";
        cout<<"\n5.ALL ACCOUNT HOLDERS LIST";
        cout<<"\n6.CLOSE AN ACCOUNT";
        cout<<"\n7.MODIFY AN ACCOUNT";
        cout<<"\n8.EXIT";
        cout<<"\n\nSelect your option(1-8):";
        cin>>ch;
        system("cls");
        switch(ch){
            case '1':
            write_account();
            break;
            case '2':
            cout<<"\nEnter Account Number:";cin>>num;
            deposit_withdraw(num,1);
            break;
             case '3':
            cout<<"\nEnter Account Number:";cin>>num;
            deposit_withdraw(num,2);
            break;
             case '4':
            cout<<"\nEnter Account Number:";cin>>num;
            display_sp(num);
            break;
            case '5':
            display_all();
            break;
            case '6':
            cout<<"\nEnter Account Number:";cin>>num;
            delete_account(num);
            break;
            case '7':
            cout<<"\nEnter Account Number:";cin>>num;
            modify_account(num);
            break;
            case '8':
            cout<<"\n\nThanks For Using Bank Management System...............";
            break;
            default:cout<<"\a";
            }
            cin.ignore();
            cin.get();
    }while(ch != '8');
    return 0;
}
//*************************************************************************************************
//                          FUNCTION TO WRITE IN FILE
//*************************************************************************************************
void write_account(){
    account ac;
    ofstream outfile;
    outfile.open("Account.dat",ios :: binary | ios :: app);
    ac.create_account();
    outfile.write(reinterpret_cast<char*> (&ac), sizeof(account));
    outfile.close();
}
//*************************************************************************************************
//                    FUNCTION TO READ SPECIFIC RECORD FROM FILE
//*************************************************************************************************
void display_sp(int n){
    account ac;
    bool flag = false;
    ifstream infile;
    infile.open("Account.dat",ios :: binary);
    if(!infile){
        cout<<("File could not be open!! Press any Key........");
        return;
    }
    while(infile.read(reinterpret_cast<char*> (&ac), sizeof(account))){
        if(ac.retacno() == n){
            ac.show_account();
            flag = true;
        }
    }
    infile.close();
    if(flag == false)
    cout<<"\nAccount Number does not exist!";
}
//*************************************************************************************************
//                            FUNCTION TO MODIFY RECORD OF FILE
//*************************************************************************************************
void modify_account(int n){
    bool found = false;
    account ac;
    fstream file;
    file.open("Account.dat",ios :: binary | ios :: in | ios :: out);
    if(!file){
        cout<<("File could not be open!! Press any Key........");
        return;
    }
    while(!file.eof() && found == false){
        file.read(reinterpret_cast<char*> (&ac), sizeof(account));
        if(ac.retacno() == n){
            ac.show_account();
            cout<<"\nEnter the new details of Account:"<<endl;
            ac.modify();
            int pos = (-1) * static_cast <int> (sizeof(account));
            file.seekp(pos,ios :: cur);
            file.write(reinterpret_cast<char*> (&ac), sizeof(account));
            cout<<"\n\nRecord Updated Successfully...............";
            found = true;
        }
    }
    file.close();
    if(found == false)
    cout<<"\nRecord Not Found!";
}
//*************************************************************************************************
//                          FUNCTION TO DELETE THE RECORD OF FILE
//*************************************************************************************************
void delete_account(int n){
    account ac;
    ifstream infile;
    ofstream outfile;
    infile.open("Account.dat",ios :: binary | ios :: in );
    if(!infile){
        cout<<("File could not be open!! Press any Key........");
        return;
    }
    outfile.open("Temp.dat",ios :: binary);
    infile.seekg(0,ios :: beg);
    while(infile.read(reinterpret_cast<char*> (&ac), sizeof(account))){
        if(ac.retacno() != n){
            outfile.write(reinterpret_cast<char*> (&ac), sizeof(account));
        }
    }
    infile.close();
    outfile.close();
    remove("Account.dat");
    rename("Temp.dat","Account.dat");
    cout<<"\n\nAccount Deleted Successfully...............";
}
//************************************************************************************************
//                          FUNCTION TO DISPLAY ALL ACCOUNT DETAILS
//************************************************************************************************

void display_all(){
    account ac;
    ifstream infile;
    infile.open("Account.dat",ios :: binary );
    if(!infile){
        cout<<("File could not be open!! Press any Key........");
        return;
    }
    cout<<"\n\n------------Account Holders List------------\n";
    cout<<"----------------------------------------------------------------------------------\n";
    cout<<"A/c No.           Name                     Type of Account              Balance\n";
    cout<<"----------------------------------------------------------------------------------\n";
    while(infile.read(reinterpret_cast<char*> (&ac), sizeof(account))){
        ac.report();
    }
    infile.close();
}
//************************************************************************************************
//                          FUNCTION TO DEPOSIT AND WITHDRAW AMOUNT
//************************************************************************************************
void deposit_withdraw(int n,int option){
    int amt;
    bool found = false;
    fstream file;
    account ac;
    file.open("Account.dat",ios :: binary | ios :: in | ios :: out);
    if(!file){
        cout<<("File could not be open!! Press any Key........");
        return;
    }
    while(!file.eof() && found == false){
        file.read(reinterpret_cast<char*> (&ac), sizeof(account));
        if(ac.retacno() == n){
            ac.show_account();
            if(option == 1){
                cout<<"\nEnter the amount to be deposited:";
                cin>>amt;
                ac.dep(amt);
            }
            if(option == 2){
                cout<<"\nEnter the amount to be withdraw:";
                cin>>amt;
                int bal = ac.retdeposit() - amt;
                if((bal< 500 && ac.rettype() == 'S') || (bal< 1000 && ac.rettype() == 'C'))
                 cout<<"\nInsufficience Balance!";
                else
                 ac.draw(amt);
            }  
             int pos = (-1) * static_cast <int> (sizeof(ac));
            file.seekp(pos,ios :: cur);
            file.write(reinterpret_cast<char*> (&ac), sizeof(account));
            cout<<"\n\nRecord Updated Successfully...............";
            found = true;
        }
    }
    file.close();
    if(found == false)
    cout<<"\nRecord Not Found!";
}
//************************************************************************************************
//                                INDRODUCTION FUNCTION
//************************************************************************************************
void intro(){
    cout<<"\n------------------BANK MANAGEMENT SYSTEM---------------------"<<endl;
    cout<<"\nEnter to start.........";
    cin.get();
}
//************************************************************************************************
//                                 END OF THE PROJECT
//************************************************************************************************






