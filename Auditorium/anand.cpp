#include<iostream>
using namespace std;
#include<string.h>
#include<fstream>
#include<stdlib.h>
#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<time.h>
#include<conio.h>
#include<iomanip>

class ticket
{
private:
    int booked;
    int remaingSeat;
    char name[20];
    int i,j;
    int row;
    int column;
    char name1[30];
public:
    ticket()
    {

       strcpy(name,"No name");
       booked=0;
       row=0;
       column=0;
       remaingSeat=400;
     }
    void rowcol(int,int);
    void showData();
    void titleDataMovie();
    void display();
    int updateBookedticket(char *);
    void updateSeatsSlot();
};
class bookticket
{
    char name[20];
    int row,col;
    ticket tic;
    string date1;
public:

    void generate(char *cname,ticket tus,int x,int y,string date)
    {
        strcpy(name,cname);
        tic=tus;
        row=x;
        col=y;
        date1=date;
    }
    void display_()
    {
        cout<<"\n\n";
        cout<<"\t\t\t\t-------------------------------\n\n";
        cout<<"\t\t\t\tDetails of customer\n\n";
        cout<<"\t\t\t\tcustomer name ="<<name;
        cout<<"\n\t\t\t\tseats of customer ="<<"seats["<<row<<"]"<<"["<<col<<"]";
        cout<<"\n\t\t\t\tDate of booking="<<date1;


    }
};
class seatSloat
{
private:
    char seats[10][10];
    int i,j;
public:
    seatSloat()
    {
        i=0;j=0;
        for(i=0;i<10;i++)
        {
            for(j=0;j<10;j++)
            {
                seats[i][j]='A';
            }
            if(j==10)
                cout<<"\n";
        }
    }
    void storeSeats()
    {
        ofstream fout;
        fout.open("tickets.dat",ios::out|ios::binary);
        fout.write((char*)this,sizeof(*this));
        fout.close();
    }
    int updateTicket(int x,int y)
{
    fstream file;
    ofstream fout;
    file.open("tickets.dat",ios::in|ios::out|ios::ate|ios::binary);
    file.seekg(0);
    file.read((char*)this,sizeof(*this));
        if(seats[x][y]=='A')
        {
            seats[x][y]='B';
            fout.open("temp.dat",ios::out|ios::binary);
            fout.write((char*)this,sizeof(*this));
            fout.close();
            cout<<"Seats booked successfully";
        }
        else
        {
            cout<<"seats already booked!!!\n";
            return 0;
        }
        file.close();
        remove("tickets.dat");
        rename("temp.dat","tickets.dat");


}
   void showseats()
   {

       cout<<"\t\t\t\t\t\t\t\t         SEATS SLOTS            \n";


       cout<<"\n\n          ------------------------------------------------------------------------------------------------------------------------------------------------\n\n\n";
       for(int i=0;i<10;i++)
        {
            cout<<"\t\t";
            for(int j=0;j<10;j++)
            {

            cout<<"seat"<<"["<<i<<"]"<<"["<<j<<"]"<<seats[i][j]<<"   ";
            }
            if(j==10)
                cout<<"\n\n";
        }
        cout<<"\n\t AVALABLE A\n\t BOOKED  B\n";
         cout<<"\n\n       ---------------------------------------------------------------------------------------------------------------------------------------------\n\n\n";
   }
   int seatsslot()
{
    ifstream fin;
    int x=0;
    fin.open("tickets.dat",ios::in|ios::binary);
    fin.read((char*)this,sizeof(*this));
    if(!fin)
    {

       return 1;
    }

    else
    {
        showseats();
        fin.close();

    }

}


};



int menu()
{
    cout<<"\t\t\t\t\t\t            AUDITORIUM TICKET BOOKING SYSTEM                      \n";
    cout<<"\t\t\t\t\t\t                                                                  \n";
    cout<<"\t\t\t\t\t\t                                                                  \n";
    cout<<"\t\t\t\t\t\t                  1.Book Ticket                                   \n";
    cout<<"\t\t\t\t\t\t                  2.List of Booked ticket                         \n";
    cout<<"\t\t\t\t\t\t                  3.Show seats slot                               \n";
    cout<<"\t\t\t\t\t\t                  4.Exit                                          \n";
    cout<<"\t\t\t\t\t\t\t\tEnter your choice ::";
    int choice;
    cin>>choice;
    return choice;
}

int main()
{
    ticket t;
    int x=0;
    int flag1=0;
    bookticket t2;
    char get;
    fstream G;
    fstream F;
    char name[30];
    int a,b;
    int i,j;
    seatSloat s1;
    string date;
    while(1)
    {

        m:
            system("cls");
        switch(menu())
        {
        case 1:
            s1.seatsslot();
            cout<<"Enter Your name::";
            cin.ignore();
            cin.getline(name,29);
            s:
            cout<<"Enter row and column::";
            cin>>a>>b;
            cout<<"Enter Date::";
            cin>>date;
            if(a>=10||b>=10)
            {
                cout<<"\n\n\t\t\t\t-----------SEAT IS OUT OF RANGE!!!----------\n";
                cout<<"\t\t\t\t-----------PLEASE ENTER VALID SEAT NO.!!!----------\n";
            }
            else
            {

                if(s1.updateTicket(a,b))
                {
                     t2.generate(name,t,a,b,date);
                     G.open("bookedticket.dat",ios::app|ios::binary);
                     G.write((char*)&t2,sizeof(t2));
                     G.close();
                     t2.display_();
                }
                else
                {
                    goto s;
                }



            }

            break;
        case 2:
              G.open("bookedticket.dat",ios::in|ios::binary);
              G.read((char*)&t2,sizeof(t2));
              if(!G)
                cout<<"Data is not avalable";
              else
              {
                  while(!G.eof())
                  {
                       t2.display_();
                       G.read((char*)&t2,sizeof(t2));
                       x++;

                  }
              }
              G.close();
              cout<<"\n\n Total Number of Booked ticket :"<<x;
              break;
        case 3:
            s1.seatsslot();


            break;
        case 4:
        cout<<"\t\t\t\t\t\t\t        THANKS FOR USING OUR APPLICATION           \n";
            exit(0);
        default:
            cout<<"\n\n\t\t\t\t\t\tINVALID CHOICE!!!";
        }
       cout<<"\n\n\t\t\t\t\t\t\tpress y for continue";
       cin>>get;
       if(get=='y'||get=='Y')
        goto m;






}


}



