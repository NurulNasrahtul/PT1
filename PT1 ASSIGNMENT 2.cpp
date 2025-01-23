//Name:1.MOHAMMAD YAZID BIN MOHD KHAIRUDDIN A24CS0117
//     2.NURUL NASRAHTUL BALQIS BINTI MOHAMAD FAZLI A24CS0177
//Date of Completion: 10/1/2025

#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

int SIZE = 25;
int readInput(string stud_name[],double asgm[],double lab_exc[],double mid_term[],double final_exam[]);//function prototype for reading the input file
void calculateTotalAndGrade(string stud_name[],double asgm[],double lab_exc[],double mid_term[],double final_exam[], double tot_marks[],char grade[],int SIZE);//function prototype for calculating the total marks and grade of each student
void displayOutput(string stud_name[],double asgm[],double lab_exc[],double mid_term[],double final_exam[], double tot_marks[],char grade[],int SIZE);//function prototype for displaying the output in a tabular format
void displayAnalysis(string stud_name[],double tot_mark[],char grade[],int SIZE);//function prototype for displaying the class average, highest and lowest marks, and grade histogram


int main() { //main function
    string stud_name[SIZE];
    double asgm[SIZE], lab_exc[SIZE], mid_term[SIZE], final_exam[SIZE]; 
    double tot_marks[SIZE];
    char grade[SIZE];    
    SIZE=readInput(stud_name,asgm,lab_exc, mid_term, final_exam);
    calculateTotalAndGrade(stud_name,asgm,lab_exc, mid_term, final_exam, tot_marks, grade, SIZE);
    displayOutput(stud_name,asgm,lab_exc, mid_term, final_exam, tot_marks, grade,SIZE);
    displayAnalysis(stud_name, tot_marks, grade,SIZE);
    
    system ("pause");
    return 0;
}


int readInput (string stud_name[],double asgm[],double lab_exc[],double mid_term[],double final_exam[]) { // to read data from file studRec.txt and calculate the total number of students
    fstream inputfile;
    inputfile.open ("studRec.txt", ios::in);//open the file

    if (!inputfile.is_open()){//check if the file is opened
        cout << "ERROR!! Input file could not be opened\n";
        exit(1);
    }

    int tot_students = 0;

    while(!inputfile.eof() && tot_students < SIZE) {//read the data from the file
        getline(inputfile, stud_name[tot_students],',');
        inputfile >> asgm[tot_students] >> lab_exc[tot_students] >> mid_term[tot_students] >> final_exam[tot_students];
        inputfile.ignore();
        tot_students++;

    }

    inputfile.close();//close the file
    return tot_students;//return the total number of students
 
}

void calculateTotalAndGrade(string stud_name[],double asgm[],double lab_exc[],double mid_term[],double final_exam[], double tot_marks[],char grade[],int SIZE) { //to calculate the total marks and grade of each student
    
    for (int i = 0; i < SIZE; i++) {
        tot_marks[i] = asgm[i] + lab_exc[i] + mid_term[i] + final_exam[i];//calculate the total marks of each student

        if ((tot_marks[i] > 84) && (tot_marks[i] <= 100)) {//calculate the grade of each student
            grade [i] = 'A';
        }
        else if ((tot_marks[i] > 69) && (tot_marks[i] < 85)) {
            grade [i] = 'B';
        }
        else if ((tot_marks[i] > 54) && (tot_marks[i] < 70)) {
            grade [i] = 'C';
        }
        else if ((tot_marks[i] > 39) && (tot_marks[i] < 55)) {
            grade [i] = 'D';
        }
        else {
            grade [i] = 'F';
        }
    }
  
}


void displayOutput(string stud_name[],double asgm[],double lab_exc[],double mid_term[],double final_exam[], double tot_marks[],char grade[],int SIZE) {// to display the output in a tabular format

    cout << "Student Name\t\t  Assignment\tLab Excercise\t  Mid Term\tFinal Exam\tTotal Marks\tGrade\n";
    cout << "================================================================================================================\n";
    for(int i = 0; i < SIZE ; i++) {
        cout << left;
        cout << setw(18) << stud_name[i] << right << fixed << setprecision(1) << setw(15) << asgm[i] << setw(15) << lab_exc[i] << setw(15) << mid_term[i] << setw(15) << final_exam[i] <<setprecision(2)<< setw(18) << tot_marks[i] << setw(12) << grade[i] << endl;
    }
    cout << endl << endl;

}


void displayAnalysis(string stud_name[],double tot_marks[],char grade[],int SIZE) {// to display the class average, highest and lowest marks, and grade histogram

    double highest = 0.0;
    string highest_name;
    double lowest = 100.0;
    string lowest_name;
    double total = 0;
    double avg_marks = 0;
    int num_A=0,num_B=0,num_C=0,num_D=0,num_F=0;

    for (int i = 0; i < SIZE; i++) {//calculate the class average, highest and lowest marks, and grade histogram
        switch(grade[i]){
            case 'A': num_A++; break;
            case 'B': num_B++; break;
            case 'C': num_C++; break;
            case 'D': num_D++; break;
            default: num_F++; break;
        }
        if (tot_marks[i] > highest) {//calculate the highest
            highest = tot_marks[i];
            highest_name = stud_name[i];

        }
        if (tot_marks[i] < lowest){//calculate the lowest
            lowest = tot_marks[i];
            lowest_name = stud_name[i];
        }
        total += tot_marks[i];//calculate the total
    }   

    avg_marks = total / SIZE;//calculate the average


    cout << "Class Average Marks: " << avg_marks << endl;
    cout << "Highest Score: " <<highest_name<<" ("<< highest<<")" << endl;
    cout << "Lowest Score: " <<lowest_name<<" ("<< lowest <<")"<< endl << endl;

    cout << "Grade Histogram "<< endl;
    cout<< "A: ";
    for(int j=0;j<num_A;j++){//display the grade histogram
        cout<<"++";
    }
    cout<<" ("<<(static_cast<double>(num_A)/SIZE)*100<<"%)"<<endl;
    cout<<"B: ";
    for(int k=0;k<num_B;k++){
        cout<<"++";
    }
    cout<<" ("<<(static_cast<double>(num_B)/SIZE)*100<<"%)"<<endl;
    cout<<"C: ";
    for(int p=0;p<num_C;p++){
        cout<<"++";
    }
    cout<<" ("<<(static_cast<double>(num_C)/SIZE)*100<<"%)"<<endl;
    cout<< "D: ";
    for(int q=0;q<num_D;q++){
        cout<<"++";
    }
    cout<<" ("<<(static_cast<double>(num_D)/SIZE)*100<<"%)"<<endl;
    cout<< "F: ";
    for(int d=0;d<num_F;d++){
        cout<<"++";
    }
    cout<<" ("<<(static_cast<double>(num_F)/SIZE)*100<<"%)"<<endl;
    

}
