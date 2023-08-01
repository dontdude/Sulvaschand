/* Product Billing Using C++ Program*/
/* HighSchool Project made by Chandan Mishra */
#include<iostream.h> // For input and output
#include<conio.h> // For clrscr()
#include<stdio.h> // For gets and puts
#include<iomanip.h> // For setw
#include<fstream.h> //For input\output in file stream
#include<process.h> //For exit()
#include<graphics.h> //For Graphics

class product{
    int prd_no; //Product number
    char prd_name[20]; //Product name
    float prd_price; //Price of that product
    float prd_dsc; //Maximum Discount on product
    int prd_qty; //Quantity of product buyed
    public:
    void create_prd(){ // Function to create product
    clrscr();
        cout<<setw(10)<<"Enter The Product Number. "<<"\n";
        cin>>prd_no;
        cout<<setw(15)<<"Enter The Product Name. "<<"\n";
        gets(prd_name);
        cout<<setw(15)<<"Enter The Price Of The Product. "<<"\n";
        cin>>prd_price;
        cout<<setw(15)<<"Enter The Discount On The Product. "<<"\n";
        cin>>prd_dsc;
    }
    void show_prd(){ // Function to show detail of exsisting product
    clrscr();
        cout<<"\n"<<setw(15)<<"The Product Number Is:- "<<prd_no;
        cout<<"\n"<<setw(15)<<"The Product Name Is:- "<<prd_name;
        cout<<"\n"<<setw(15)<<"The Price Of Product Is:- "<<prd_price;
        cout<<"\n"<<setw(15)<<"The Discount On The Product Is:- "<<prd_dsc;
    }
    int pno(){
        return(prd_no); 
    }
    char*pname(){
        return prd_name;
    }
    float pprice(){
        return(prd_price); 
    }
    float pdsc(){
        return(prd_dsc); 
    }
    int pqty(){
        return(prd_qty); 
    } 
}pr; //class product ends with pr as an object

fstream pf;
class admin:public product { // Inherited class of class product
    public:
    void Insert();
    void Search(int n);
    void Modify();
    void Delete();
};
void admin::Insert(){ /*Function to write a product on memory*/
    pf.open("shop.dat",ios::out|ios::app);
    pr.create_prd();
    pf.write((char*)&pr,sizeof(product));
    pf.close();
    cout<<"\n"<<setw(15)<<"The Product Has Been Created";
    getch();
}
void admin::Search(int n){ /* Function to search a product from memory*/
    int f=0;
    pf.open("shop.dat",ios::in);
    while(pf.read((char*)&pr,sizeof(product))) {
        if(pr.pno()==n)
        {clrscr();
        pr.show_prd();
        f=1; }
    }
    pf.close();
    if(f==0)
    cout<<"\nIncorrect !! ..\nThe Product Of This Name Doesn't Exsist";
    getch();
}
void admin::Modify(){ /* Function to modify the exsisting product detail*/
    int no,found=0;
    clrscr();
    cout<<"\n"<<setw(15)<<"Please Enter The Product Number Of The Product";
    cin>>no;
    pf.open("shop.dat",ios::in|ios::out);
    while(pf.read((char*)&pr,sizeof(product))&&found==0)
    { if(pr.pno()==no)
    {
    pr.show_prd();
    cout<<"\n"<<setw(15)<<"Enter The New Detail Of Product ";
    pr.create_prd();
    int pos=-1*sizeof(pr);
    pf.seekp(pos,ios::cur);
    pf.write((char*)&pr,sizeof(product));
    cout<<"\nRecord Updated !!";
    found=1; }
    }
    pf.close();
    if(found==0)
    cout<<"\nRecord Not Found!!";
    getch();
}
void admin::Delete(){ //Function to delete the exsisting product
    int no;
    clrscr();
    cout<<"\n"<<setw(15)<<"Enter The Product Number Of The Product You Want To Delete";
    cin>>no;
    pf.open("shop.dat",ios::in|ios::out);
    fstream pf2;
    pf2.open("temp.dat",ios::out);
    pf.seekg(0,ios::beg);
    while(pf.read((char*)&pr,sizeof(product)))
    {
    if(pr.pno()!=no)
    {
    pf2.write((char*)&pr,sizeof(product));}
    }
    pf2.close();
    pf.close();
    remove("shop.dat");
    rename("temp.dat","shop.dat");
    cout<<"\nRecord Deleted!!";
    getch();
}
void Menu() { 
    clrscr();
    pf.open("shop.dat",ios::in);
    if(!pf)
    {
    cout<<" ERROR!!!! File Could Not Be Open"<<"\n\n";
    cout<<"Go To Admin Menu To Create File";
    cout<<"\n\n Program is closing ......";
    getch();
    exit(0);
    }
    cout<<"\n\n\n"<<"\t\t\t\tPRODUCT MENU"<<"\n\n\n";
    cout<<" Product Number Product Name Product Price \n";
    while(pf.read((char*)&pr,sizeof(pr)))
    {
    cout<<" "<<pr.pno()<<" "<<pr.pname()<<"\t\t\t"<<pr.pprice()<<endl;
    }
    pf.close(); 
}
void Place_Order() {
    int Order[50],Quantity[50],C=0;
    float Amount,Damt,Total=0;
    char ch='y';
    Menu();
    cout<<"\n PLACE YOUR ORDER \n";
    while(ch=='Y'||ch=='y'){
    cout<<"\n\n"<<"Enter The Product Number";
    cin>>Order[C];
    cout<<"\n\n"<<"Enter Quantity In Number";
    cin>>Quantity[C];
    C++;
    cout<<"\n\n"<<"Do You Want To Order Another Product? (Y/N)";
    cin>>ch;
    }
    cout<<"\n\n"<<"Thank You For Placing The Order";
    getch();
    clrscr();
    cout<<"\n\n\t\t\t\t\tBILL\nProduct No. || Product Name || Quantity || Price || Amount || Discounted
    Amount \n";
    for(int i=0;i<=C;i++)
    {
    pf.open("shop.dat",ios::in);
    pf.read((char*)&pr,sizeof(pr));
    while(!pf.eof())
    {
    if(pr.pno()==Order[i])
    {
    Amount=pr.pprice()*Quantity[i];
    Damt=(Amount-(Amount*pr.pdsc()/100));
    cout<<"\n\n"<<"Order["<<i+1<<"]"<<" || "<<pr.pname()<<" || "<<Quantity[i];
    cout<<" || "<<pr.pprice()<<" || "<<Amount<<" || "<<Damt;
    Total+=Damt;
    }
    pf.read((char*)&pr,sizeof(pr));
    } pf.close();
    }
    cout<<"\n\n\t\t\t\t Total ="<<Total;
    cout<<" \n\n\n\t\t\t You Have To Pay $"<<Total;
    getch();
}
/*INTRODUCTION FUNCTION*/
void Intro()
{ clrscr();
cout<<"\n\n\n\n\n\n\n\n S U L V A S C H A N D ";
cout<<"\n\n\n S U P E R M A R K E T";
cout<<"\n\n\n B I L L I N G";
getch();
}
/*THE MAIN FUNCTION OF THE PROGRAM*/
void main(){
Intro();
int ch;
admin ad;
clrscr();
char ans='y';
while(ans=='y'||ans=='Y'){
cout<<"\n\n\n"<<setw(50)<<"Enter The Choice \n"<<"1. Main Menu\n"<<"2. Admin
Section\n"<<"3. Exit\n";
cin>>ch;
switch(ch){
case 1:{
clrscr();
int t;
cout<<"\n"<<setw(10)<<"Main Menu\n"<<"1.Customer"<<"\n"<<"2.Product List
"<<"\n"<<"3.Exit\n";
cin>>t;
switch(t){
case 1:{
Place_Order();
}break;
case 2:{
cout<<"\n\t\t\tThe Available Products Are\n";
Menu();}break;
case 3:{ exit(0);
}break; }
cout<<"\n"<<setw(25)<<"Want To Enter Again(y/n)";
cin>>ans;
}
break;
case 2:{
int c;
clrscr();
cout<<"\n"<<setw(20)<<"Enter Your Choice Again:-\n"<<"1. Insert\n"<<"2. Search\n"<<"3.
Modify\n"<<"4. Delete\n"<<"5.Display\n"<<"6. Exit()\n";
cin>>c;
switch(c){
case 1:{char a='y';
while((a=='Y')||(a=='y'))
{
ad.Insert();
cout<<"\nWant To Enter Again(y/n):-";
cin>>a;
}clrscr();
}
break;
case 2:{
int num;
cout<<"\n"<<setw(15)<<"Enter The Product Number.";
cin>>num;
char a='y';
while((a=='Y')||(a=='y'))
{
ad.Search(num);
cout<<"\nWant To Search Again(y/n):-";
cin>>a;
} clrscr();
} break;
case 3:{
char a='y';
while((a=='Y')||(a=='y'))
{
ad.Modify();
cout<<"\nWant To Modify Again(y/n):-";
cin>>a;
}clrscr(); }
break;
case 4:{
char a='y';
while((a=='Y')||(a=='y'))
{
ad.Delete();
cout<<"\nWant To Delete Again(y/n):-";
cin>>a;
}clrscr(); }
break;
case 5:{
char t='n';
while((t=='N')||(t=='n'))
{ Menu();
cout<<"\nWant To Go Back(y/n):-";
cin>>t;
}clrscr();
} break;
case 6:{
exit(0);}
break;
}}
break;
case 3:{ exit(0); }
break;
default :{
cout<<"\nYou Have Entered A Wrong Choice....Want To Enter Again (y/n) ";
} } }
getch();
}