#include <iostream>
#include <string>

using namespace std;

class grade{
    public:
        grade(int midterm=0, int final=0, int hw1=0, int hw2=0, int hw3=0){}

        int average, haverage;



        bool hwaverage(){
            haverage=(hw1+hw2+hw3)/3;
            if(haverage>80)return true;
            return false;
        }

        bool iszero(){
            if(midterm==0 || final==0 || hw1==0 || hw2==0 || hw3==0)return false;
            return true;
        }

        bool totalaverage(){
            average=(midterm+final+hw1+hw2+hw3)*0.2;
            if(average>50)return true;
            else if(iszero()==true  && hwaverage()==true)return true;
            return false;
        }

    private:
        int midterm, final, hw1, hw2, hw3;

};

class student{
    public:
        student(){
            name = "none", surname = "none", ispassed = false;
        }
        void input(){
            cout<<"Enter the name of student: "<< endl;
            cin>>name;
            cout<<"Enter the surname of student: "<< endl;
            cin>>surname;

            int a,b,c,d,e;
            cout<<"enter your grades in order: "<<endl;
            cin>>a>>b>>c>>d>>e;
            grade(a,b,c,d,e);
        }
        string name, surname;
        grade cse;
        
        void print(){   
            cout<<"Studenet : "<<name<<" "<<surname<<endl;
            cout<<"hw average is: "<<cse.haverage<<endl;
            cout<<"total average is: "<<cse.average<<endl;

            if (ispassed==true)cout<<"congrats youve passed the class "<<endl;
            else cout<<"aga be";

        }

    private:
        bool ispassed = cse.totalaverage();
    
};

int main(){
    student ebrar;
    student hakan;
    student ahmet;
    ebrar.input();
    ebrar.print();
}