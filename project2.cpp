#include <iostream>
#include <fstream>
#include <algorithm> 
#include <chrono>
#include <stdlib.h>

using namespace std;
using namespace std::chrono;

class Student
{
    private:

    ifstream read;
    ofstream write;
    string name , grade , readData;
    float marks;
    int counter , store , flag , rollNumber , deleteCounter;

    public:

    Student()
    {
        name = grade = "\0";
        marks = 0.0;
        counter = store = deleteCounter = flag = 0; 
    }
    void insertStudentData(string Name , string Grade , float Marks , int RollNumber)
    {
        name = Name;
        grade = Grade;
        marks = Marks;
        rollNumber = RollNumber;

        write.open("studentData.txt" , ios::app);

        write << name << endl;
        write << grade << endl;
        write << marks << endl;
        write << rollNumber << endl;
        
        write.close();
    }
    int numberOfLine()
    {
        counter = 0;

        read.open("studentData.txt");

        while(getline(read , readData))
        {
            counter++;
        }        

        read.close();

        return counter;
    }
    void readStudentData()
    {
        store = numberOfLine()/4;

        if(store == 0)
        {
            cout << "File is empty" << endl;
            return;
        }

        read.open("studentData.txt");

        cout << "Name" << "\t" << "Roll Number" << "\t" << "Marks" << "\t" << "Grade" << endl;

        for(int i = 1 ; i <= store ; i++)
        {
            read >> name;
            read >> grade;
            read >> marks;
            read >> rollNumber;

            cout << name << "  \t   " << rollNumber << "   \t  " << marks << " \t " << grade << endl;
        }

        read.close();
    }
    void deleteStudentData(int RollNumber)
    {
        flag = 0;

        store = numberOfLine()/4;

        if(store == 0)
        {
            cout << "File is empty" << endl;
            return;
        }

        read.open("studentData.txt");
        write.open("temp.txt" , ios::app);

        for(int i = 1 ; i <= store ; i++)
        {
            read >> name;
            read >> grade;
            read >> marks;
            read >> rollNumber;

            if(RollNumber == rollNumber)
            {
                cout << endl;
                cout << "Name : " <<name << endl;
                cout << "Roll Number : "  << rollNumber << endl;
                cout << "Marks : "  << marks << endl;
                cout << "Grade : "  << grade << endl;
                cout << "***********************************" << endl;
                cout << "* Above student record is deleted *" << endl;
                cout << "***********************************" << endl;

                flag = 1;
            }
            else
            {
                write << name << endl;
                write << grade << endl;
                write << marks << endl;
                write << rollNumber << endl;
            }
        }

        read.close();
        write.close();

        remove("studentData.txt");
        rename("temp.txt" , "studentData.txt");
    }
    void searchStudent(int index)
    {
        flag = 0;

        read.open("studentData.txt");

        while(!read.eof())
        {
            read >> name;
            read >> grade;
            read >> marks;
            read >> rollNumber;

            if(rollNumber == index)
            {
                cout << "Name : " << name<< endl;
                cout << "Roll Number : " << rollNumber << endl;
                cout << "Marks : " << marks << endl;
                cout << "Grade : " << grade << endl; 

                flag = 1;

                break;
            }
        }    
        read.close();
    }
    int getFlag()
    {
        return flag;
    }
};
class Algorithum
{
    private:

    string processes[100];
    double waitingTime[100] , burstTime[100] , turnAroundTime[100];
    int length;

    public:

    Algorithum()
    {
        length = -1;
    }  
    void getBurstTimeAndProcess(string process , double time)
    {
        ++length;

        processes[length] = process;
        burstTime[length] = time;
    }
    void fcfsWorking(int size)
    {
        waitingTime[0] = 0.0;

        for(int  i = 1 ; i < size ; i++)
        {
            waitingTime[i] = burstTime[i - 1] + waitingTime[i - 1];
        }

        for(int i = 0 ; i < size ; i++)
        {
            turnAroundTime[i] = waitingTime[i] + burstTime[i];
        }
    }
    void display(int size)
    {
        double average = 0.0 , sum = 0.0;

        cout << "Process      Burst Time\t  Waiting Time \t Turn Around Time" << endl << endl;

        for(int i = 0 ; i < size ; i++)
        {
            cout << processes[i] << "\t\t" << burstTime[i] << "\t\t" << waitingTime[i] << "\t\t" << turnAroundTime[i] << endl;
        }

        for(int i = 0 ; i < size ; i++)
        {
            sum = waitingTime[i] + sum;
        }

        average = sum / size;

        cout << "Average waiting time is : " << average << endl;

        average = 0.0;
        sum = 0.0;

        for(int i = 0 ; i < size ; i++)
        {
            sum = turnAroundTime[i] + sum;
        }

        average = sum / size;

        cout << "Average turn around time is : " << average << endl;
    }
    int getLength()
    {
        return length;
    }
};

int main()
{
    Student objStudent;
    Algorithum objAlgorithum;

    string name = "\0" , grade = "\0";
    float marks = 0.0;
    int rollNumber = 0 , choice = 0 , index = 0;
    double storedTime = 0.0;
    char nextPortion , nextPortion1;

    do
    { 
        cout << endl;
        cout << "1. Enter Student Data" << endl;
        cout << "2. Read Student Data" << endl;
        cout << "3. Delete Student Data" << endl;
        cout << "4. Search Student " << endl;
        cout << "5. FCFS" << endl;
        cout << "0. Quit" << endl;
        cout << "Enter your choice : ";
        cin >> choice;

        while(choice < 0 || choice > 5)
        {
            cout << endl << "Invalid input" << endl;
            cout << endl << "Enter Again : ";
            cin >> choice; 
        } 

        system("CLS");

        if(choice == 1)
        {
            auto starting = high_resolution_clock::now();

            cout << "Enter name : ";
            cin >> name;
            cout << "Enter roll number : ";
            cin >> rollNumber;
            cout << "Enter marks : ";
            cin >> marks;
            cout << "Enter Grade : ";
            cin >> grade;

            objStudent.insertStudentData(name , grade , marks , rollNumber);

            auto ending = high_resolution_clock::now();
            auto duration = duration_cast<milliseconds>(ending - starting);
            storedTime = duration.count();
            
            objAlgorithum.getBurstTimeAndProcess("Insert" , storedTime);
        }
        else if(choice == 2)
        {
            auto starting = high_resolution_clock::now();

            objStudent.readStudentData();

            auto ending = high_resolution_clock::now();
            auto duration = duration_cast<milliseconds>(ending - starting);
            storedTime = duration.count();

            objAlgorithum.getBurstTimeAndProcess("Read" , storedTime);
        }
        else if(choice == 3)
        {
            auto starting = high_resolution_clock::now();

            if(objStudent.numberOfLine() == 0)
            {
                cout << "File is empty" << endl;
                goto nextPortion;
            }

            cout << "Enter the Roll Number you want to delete : ";
            cin >> index;

            objStudent.deleteStudentData(index);

            if(objStudent.getFlag() == 0)
            {
                cout << "Roll Number Doesn't exists" << endl;
            }

            nextPortion:;

            auto ending = high_resolution_clock::now();
            auto duration = duration_cast<milliseconds>(ending - starting);
            storedTime = duration.count();

            objAlgorithum.getBurstTimeAndProcess("Delete" , storedTime);
        }
        else if(choice == 4)
        {
            auto starting = high_resolution_clock::now();

            if(objStudent.numberOfLine() == 0)
            {
                cout << "File is empty" << endl;
                goto nextPortion1;
            }

            cout << "Enter the Roll Number you want to search : ";
            cin >> index;

            objStudent.searchStudent(index);

            if(objStudent.getFlag() == 0)
            {
                cout << "Roll Number Doesn't exists" << endl;
            }

            nextPortion1:;

            auto ending = high_resolution_clock::now();
            auto duration = duration_cast<milliseconds>(ending - starting);
            storedTime = duration.count();

            objAlgorithum.getBurstTimeAndProcess("Search" , storedTime);
        }
        else if(choice == 5)
        {
            objAlgorithum.fcfsWorking(objAlgorithum.getLength() + 1);
            objAlgorithum.display(objAlgorithum.getLength() + 1);
        }
    } while(choice != 0);    

    return 0;
}