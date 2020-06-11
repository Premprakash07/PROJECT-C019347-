#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
#include<time.h>
using namespace std;

int account_no=0;
float balance, credit, debit;

class dob{
    protected:
    int date, month, year;
    public:
    void get_dob(){
        cin>>date>>month>>year;
    }
    void print(){
        cout<<date<<"/"<<month<<"/"<<year<<endl;
    }
};

class account:public dob{
    char name[30], fathers_name[30], mothers_name[30], gen, address[100];
    char pin[4];
    float bal=0;     
    public:
    int acc_no;
    account(){
        acc_no=++account_no;
    }
    account(int){}                    
    ~account(){}
    void display(){
        cout<<"ACCOUNT NO. : "<<account_no<<endl<<
        "NAME : "<<name<<endl<<
        "BALANCED : "<<bal<<endl;
    }
    void get_data(){
        fstream acc, passbook;
        string file=to_string(acc_no)+".txt";
        string pass=to_string(acc_no)+"_passbook.txt";
        acc.open(file, ios::app | ios::binary);
        passbook.open(pass, ios::app | ios::binary);
        cout<<"Enter name of the account holder : ";
        cin.getline(name, sizeof(name));
        cout<<endl;
        cout<<"Enter gender (M/F/T) : ";
        cin>>gen;
        cout<<endl;
        cout<<"Enter date of birth (dd/mm/yyyy) : ";
        get_dob();
        cout<<endl;
        cout<<"Enter Father's name of the account holder : ";
        cin.getline(fathers_name, sizeof(fathers_name));
        cout<<endl;
        cout<<"Enter Mother's name of the account holder : ";
        cin.getline(mothers_name, sizeof(mothers_name));
        cout<<endl;
        cout<<"Enter Address of the account holder : ";
        cin.getline(address, sizeof(address));
        cout<<endl;
        while(true){
            char pn[4], p[4];
            cout<<"Create a four digit PIN : ";
            cin>>p;
            cout<<"\nConfirm PIN : ";
            cin>>pn;
            cout<<endl;
            if(p==pn){
                copy(p, p+4, pin);
                exit;
            } 
            else cout<<"PIN doesn't  match!!!\nTry again";
        }
        acc.write((char*)this, sizeof(*this));
        passbook<<endl<<endl<<setw(50)<<left<<"Transaction"<<setw(35)<<"Time"<<setw(10)<<"Credit"
            <<setw(10)<<"Debit"<<setw(10)<<"Balance";
        acc.close();
        passbook.close();
    }
    void withdrawal();
    void deposit();
    void update();
    void change_pin();
};

void account::withdrawal(){ 
    float w; 
    char p[4];                     
    cout<<"Enter the withdrawal amount : ";
    cin>>w;
    cout<<endl;
    cout<<"Enter PIN : ";
    cin>>p;
    cout<<endl;
    if(p==pin){                               
        bal=bal-w;
        balance=bal;
        debit=w;
        cout<<"Your remaining balance is : "<<bal<<endl;
    }    
    else{
        cout<<"WRONG PIN!!!\nTRY AGAIN"<<endl;
    }
}

void account::deposit(){ 
    float d;                             
    cout<<"Enter the deposit amount : ";
    cin>>d;
    cout<<endl;
    bal=bal+d;
    balance=bal;
    credit=d;
    cout<<"Balance : "<<bal<<endl;
    //update file 
}
void account:: update(){
    cout<<"CHOOSE : "<<endl<<
    "1 : NAME"<<endl<<
    "2 : FATHER'S NAME"<<endl<<
    "3 : MOTHER'S NAME"<<endl<<
    "4 : DATE OF BIRTH"<<endl<<
    "5 : ADDRESS"<<endl;

    int o;
    switch (o)
    {
    case 1:{
        cout<<"ENTER THE NAME : "<<endl;
        cin.getline(name, sizeof(name));
        break;
    }
    case 2:{
        cout<<"ENTER THE FATHHER'S NAME : "<<endl;
        cin.getline(fathers_name, sizeof(fathers_name));
        break;
    }
    case 3:{
        cout<<"ENTER THE MOTHER'S NAME : "<<endl;
        cin.getline(mothers_name, sizeof(mothers_name));
        break;
    }
    case 4:{
        this->get_dob();
        break;
    }
    case 5:{
        cout<<"ENTER THE ADDRESS : "<<endl;
        cin.getline(address, sizeof(address));
        break;
    }
    
    default:
        break;
    }
}
void account::change_pin(){
    char p[4], pn[4], pc[4];
    cout<<"ENTER THE OLD PIN";
    cin>>p;
    if (p==pin){
        cout<<"ENTER YOUR NEW 4-DIGIT PIN : "<<endl;
        cin>>pn;
        cout<<"CONFIRM PIN : "<<endl;
        cin>>pc;
        if(pn==pc){
            copy(pn, pn+4, pin);
        }
        else{
            cout<<"PIN DOESN'T MATCH!!! \nTRY AGAIN!!!";
        }        
    }
    else{
        cout<<"WRONG PIN!!! \nTRY AGAIN!!!";
    }   
}

int main(){

    int ac;
    int op;
    fstream acc, passbook;
    account acco(1);

    int o;
    char ch;
    cout<<"ENTER YOUR CHOICE"<<endl<<
    "1 : CREATE ACCOUNT"<<endl<<
    "2 : ALREADY HAVE AN ACCOUNT"<<endl;
    cin>>o;
    if(o==1){
        do{
            system("CLS");                                 
            account a;
            a.get_data();
            cout<<"ACCOUNT CREATED SUCCESSFULLY. :)"<<endl;
            a.~account();
            cout<<"Would you like to create another account(y/n) : ";
            cin>>ch;
        } while (ch=='y' || ch=='Y');                       
    }

    else if(o==2){
        system("CLS");                                     
        cout<<"Enter the account no. : ";
        cin>>ac;
        string file=to_string(ac)+".txt";
        string pass=to_string(ac)+"_passbook.txt";
        acc.open(file, ios::out | ios::binary);
        if(!acc){
            cout<<"NO SUCH ACCOUNT EXIST!!!"<<endl;
        }
        else{ 
            acc.seekg(0);
            acc.read((char*)&acco, sizeof(acco));
            passbook.open(pass, ios::app | ios::binary);                          
            cout<<"ENTER AN OPTION"<<endl<<            
            "1 : MONEY DEPOSIT"<<endl<<
            "2 : CASH WITHDRAWAL"<<endl<<
            "3 : CHANGE PIN"<<endl<<
            "4 : CHECK BALANCE"<<endl<<
            "5 : UPDATE PERSONAL DETAILS"<<endl<<
            "6 : PRINT PASSBOOK"<<endl;
            cin>>op;
        }
    }
    else cout<<"INVALID OPTION SELECTED"<<endl;

    switch(op){
        case 1: {
            acco.deposit();
            acc.write((char*)&acco, sizeof(acco));
            time_t t; 
            struct tm * tt; 
            time (&t); 
            tt=localtime(&t);
            acc.seekg(0, ios::end);
            passbook<<setw(50)<<left <<"CASH DEPOSIT"<<setw(35)<<asctime(tt)
                <<setw(10)<<setprecision(2)<<credit<<setw(10)<<"  "<<setw(10)<<balance;
            
            acco.~account();                 
            cout<<"MONEY DEPOSITED SUCCESSFULLY. :)"<<endl;
            acc.close();
            passbook.close();                    
            break;
        }
        case 2: {
            acco.withdrawal();
            acc.write((char*)&acco, sizeof(acco));
             time_t t; 
            struct tm * tt; 
            time (&t); 
            tt=localtime(&t);
            acc.seekg(0, ios::end);
            passbook<<setw(50)<<left<<"CASH WITHDRAWAL"<<setw(35)<<asctime(tt)
                <<setw(10)<<setprecision(2)<<" "<<setw(10)<<debit<<setw(10)<<balance;
            
            acco.~account();
            acc.close();
            passbook.close();
            break;
        }
        case 3: {
            acco.change_pin();
            acc.write((char*)&acco, sizeof(acco));
            time_t t; 
            struct tm * tt; 
            time (&t); 
            tt=localtime(&t);
            acc.seekg(0, ios::end);
            passbook<<setw(50)<<left<<"PIN CHANGE"<<setw(35)<<asctime(tt)
                <<setw(10)<<setprecision(2)<<" "<<setw(10)<<" "<<setw(10)<<balance;
        
            acco.~account();
            cout<<"PIN CHANGED SUCCESSFULLY. :)"<<endl;
            acc.close();
            passbook.close();
            break;
        }
        case 4: {
            acco.display();
            acco.~account();
            acc.close();
            break;
        }
        case 5:{
            acco.update();
            acc.write((char*)&acco, sizeof(acco));
            acc.seekg(0, ios::end);
            time_t t; 
            struct tm * tt; 
            time (&t); 
            tt=localtime(&t);
            acc.seekg(0, ios::end);
            passbook<<setw(50)<<left<<"ACCOUNT UPDATED"<<setw(35)<<asctime(tt)
                <<setw(10)<<setprecision(2)<<" "<<setw(10)<<" "<<setw(10)<<balance;
        
            acco.~account();
            cout<<"ACCOUNT UPDATED SUCCESSFULLY. :)"<<endl;
            acc.close();
            passbook.close();
            break;
        }
        case 6:{
            string pass_book;
            passbook.seekg(0);
            passbook>>pass_book;
            cout<<pass_book;
            passbook.close();
        }
        default: 
            break;
    }

    return 0;
}
    