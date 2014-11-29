#include<iostream>
#include<fstream>
#include<string>
#include<cstring>
#include<stdlib.h>
#define NUM 172
using namespace std;

float gp_Ex;
string us_Ex;
//class to store the data from the text file.
class student
{
    string id;
    string name;
    string usn;
    string scores;
    float gpa;
    static float gpa_acc[NUM];      //static array for storing the gpa
    static int count;               //an array pointer for the gpa_acc

    public:
    friend void print_equals(student&);
    void get_details(string, string, string, string);
    void calc_gpa();
    void print_details(string);
    int disp_rank(float);
    static void sort_gpa()      //static func for sorting the gpa array in decreasing order(bubble sort)
     {
        int i,j;
        float temp;
        for(i=0;i<NUM-1;i++)
            for(j=0;j<NUM-i-1;j++)
            {
                if (gpa_acc[j]<gpa_acc[j+1])
                {
                    temp=gpa_acc[j];
                    gpa_acc[j]=gpa_acc[j+1];
                    gpa_acc[j+1]=temp;
                }
            }
    }

};

void student::get_details(string a, string b, string c, string d)
{
        id=a;
        usn=b;
        name=c;
        scores=d;
}

void student:: calc_gpa()
//convert the string into an array
{
    string grades=scores;
    string arr[18];
    int i,j=0;
    for(i=0;i<grades.length();i++)
    {
        if(grades[i]!=' ')
        {
            arr[j]+=grades[i];
        }
        else
            j++;
    }
//calc the gpa using the array
    int sto=0;
    for(i=0;i<18;i=i+3)
    {
        sto=sto+atoi(arr[i].c_str())*atoi(arr[i+2].c_str());
    }
    gpa=sto/25.0;
    gpa_acc[count]=gpa;
    count++;            //increse the gpa pointer
}

void student::print_details(string u)
//print the details of the object, if the input usn matches the object usn
{
     if(u==usn)
    {

        cout<<name<<endl;
        cout<<usn<<endl;
        cout<<"Your SGPA of 4th sem is: "<<gpa<<endl;
        cout<<"Your SGPA position(rank) is: "<<disp_rank(gpa);
        gp_Ex=gpa;              //global variable for storing the gpa n usn of the input usn(user)
        us_Ex=usn;
    }
}

//print the details of the students having same gpa
void print_equals(student &a)
{
    if(a.usn != us_Ex)
    {
        if(gp_Ex==a.gpa)
        {
            cout<<a.usn<<"       "<<a.name<<endl;
        }
    }
}

//function to find out the sgpa position
int student::disp_rank(float gp1)
{
    float ele=gpa_acc[0];
    int rank=1;
    for(int i = 0; i < NUM; i++)
    {

        if(gpa_acc[i] == gp1)
       {
           return rank;
       }
       if(gpa_acc[i+1] != gpa_acc[i])
       {
           rank++;
       }

    }
}



float student::gpa_acc[NUM];
int student::count=0;



int main()
{
    int i;
    string a,b,c,d;
    student st[NUM];        //array of abjects
    ifstream res("RES.txt");    //opening the text file
    for(i=0;i<NUM;i++)      //reading the data in the text file into the array of objects
    {
        getline(res, a);    //reads the serial number
        getline(res, b);    //reads USN
        getline(res, c);    //reads name
        getline(res, d);    //reads the scores
        st[i].get_details(a,b,c,d);     //writes data into the objects
    }


    for(i=0;i<=NUM-1;i++)      //calculating sgpa for each object
    {
        st[i].calc_gpa();
    }
    student::sort_gpa();    //calling the function to sort the gpa
    cout<<"********************************************************************************"<<endl;
    string ip_usn;      //input usn declaration
    int option_X;
    cout<<"\t\t\tSGPA analysis program\n";
    cout<<"\t\tAnalysing 4th sem ECE(2013-14) results\n\n\n";
    cout<<"\t\t   You have the following options:"<<endl;
    cout<<"\t\t\t1 : View only result"<<endl;
    cout<<"\t\t\t2 : View complete analysis"<<endl;
    cout<<"\t\t\t3 : Quit the process"<<endl;
    cout<<"********************************************************************************"<<endl;
    do
    {
        cout<<endl<<endl;
        cout<<"\t\t\t______________________"<<endl;
        cout<<"\t\t\t| Enter your choice: |"<<endl;
        cout<<"\t\t\t --------------------"<<endl;
        cin>>option_X;      //menu variable

        switch(option_X)
        {
           case 1 : cout<<"Enter the USN(in caps): "<<endl;     //print only result
                    cin>>ip_usn;
                    cout<<endl<<endl;
                    cout<<"********************************************************************************"<<endl;
                     for(i=0;i<=NUM-1;i++)
                     {
                         st[i].print_details(ip_usn);
                     }
                     cout<<endl<<endl<<"********************************************************************************"<<endl;
                     cout<<endl;
                     break;
           case 2 : cout<<"Enter the USN(in caps): "<<endl;     //print the result analysis
                    cin>>ip_usn;
                    cout<<endl<<endl;
                    cout<<"********************************************************************************"<<endl;
                    for(i=0;i<=NUM-1;i++)
                    {
                        st[i].print_details(ip_usn);
                    }
                    cout<<endl<<endl<<"This GPA is tied with:"<<endl;
                    for(int i = 0; i < NUM; i++)
                    {
                        print_equals(st[i]);
                    }
                    cout<<endl<<"********************************************************************************"<<endl;
                    break;
           case 3 :
                    cout<<"Source code available at https://github.com/hgsujay/SGPA_Cpp   "<<endl;
                    cout<<"press any key to quit\n";
                    char quit;
                    cin>>quit;

                    cout<<"Quiting the process...";
                    for(int i=0;i<=10000000;i++)
                    {
                        cout<<"";
                    }
                    break;

            default :
                        cout<<"incorrect option"<<endl;
                        break;
        }
    }while(option_X != 3);
    return 0;
}
