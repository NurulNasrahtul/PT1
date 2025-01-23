//Name:1.MOHAMMAD YAZID BIN MOHD KHAIRUDDIN A24CS0117
//     2.NURUL NASRAHTUL BALQIS BINTI MOHAMAD FAZLI A24CS0177
//Date of Completion: 22/1/2025

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;
#define MAX  100
#define month 12       

//Task 1 
//define structure
struct monthlydata  //struct for monthly data
{
int     evacuees[month],
        resources[month], 
        expenditures[month];
};

struct tot  //struct for total evacuees, total resources and total expenditures
{
int     evacuees,
        resources, 
        expenditures; 
};

struct center  //struct for relief center information
{
 string      code, 
             name,
             state;
 monthlydata monthly;
 tot         total;

double avg,totalexpendersper;
};

//function prototype
void readInput(center reliefCenter[], int& line);
void map(center reliefCenter[], int& line);
void data(center reliefCenter[], int& line);
void total(center reliefCenter[], int& line);
void report(const center reliefCenter[], int line,double toteva,double totres,double totexpend,double avg[],double totexpendersper[]);

//main function
int main() 
{
    center reliefCenter[MAX];
    int line = 0;
    double toteva = 0.0, totres = 0.0, totexpend = 0.0;
    double avg[MAX] = {0.0}, totexpendersper[MAX] = {0.0};

    readInput(reliefCenter, line);
    map(reliefCenter, line);
    total(reliefCenter, line);
    report(reliefCenter,line, toteva, totres, totexpend, avg, totexpendersper);
     
    system ("pause");
    return 0;
}

//Task 2 
//read and validate input files
void readInput(center reliefCenter[], int& line)
{
    ifstream centerFile("center.txt");
    ifstream evacueesFile("evacuees.txt");
    ifstream resourcesFile("resources.txt");
    ifstream expendituresFile("expenditures.txt");

    if (!centerFile || !evacueesFile || !resourcesFile || !expendituresFile) //input file checking
    {
        cout << "Some of the file cant be found" << endl;
        system ("pause");
        exit(1);
    }

    string code;
    line=0;
    
    while (getline(centerFile, code) && line < MAX) 
    {
        reliefCenter[line].code = code;

        for (int i = 0; i < month; ++i) //data consistency checking
        {
           if (!( evacueesFile >> reliefCenter[line].monthly.evacuees[i])||
               !( resourcesFile >> reliefCenter[line].monthly.resources[i])||
               !( expendituresFile >> reliefCenter[line].monthly.expenditures[i]))
               {
                 cout << "Data is not consistent!" << endl;
                 system ("pause");
                 exit(1);
               }
        }
        line++;
    }
        centerFile.close();
        evacueesFile.close();
        resourcesFile.close();
        expendituresFile.close();
}

//Task 3
//to map the center code to the center name and state
void map(center reliefCenter[], int& line){ 
    
    string codes[]={"TGR","JHR","KLT","TRG","SGR","KDU","KCH"};//center codes
    string names[]={"Tanjung Relief Center","Johor Relief Center","Kelantan Relief Center","Terengganu Relief Center",//center names
                    "Sungai Relief Center","Kudat Relief Center","Kuching Relief Center"};
    string states[]={"Selangor","Johor","Kelantan","Terengganu","Perak","Sabah","Sarawak"};//center states

        for (int i = 0; i < line; ++i) 
    {
        for (int j = 0; j < 7; ++j) 
        { 
            if (reliefCenter[i].code.substr(0, 3) == codes[j]) //array updating
            {
                reliefCenter[i].name = names[j];
                reliefCenter[i].state = states[j];
                
            }
        }
    }
}

//Task 4
//to perform data analysis and calculate the total evacuees, total resources, total expenditures, 
//average resources per evacuees and expenditures per evacuees
void total(center reliefCenter[], int& line){

    double toteva=0,totres=0,totexpend=0,avg [line]={0},totexpendersper[line]={0};

    for(int i=0;i < line; ++i){
        reliefCenter[i].total.evacuees=0;
        reliefCenter[i].total.resources=0;
        reliefCenter[i].total.expenditures=0;

        for (int j = 0; j < month; ++j) 
            {
                reliefCenter[i].total.evacuees += reliefCenter[i].monthly.evacuees[j];
                reliefCenter[i].total.resources += reliefCenter[i].monthly.resources[j];
                reliefCenter[i].total.expenditures += reliefCenter[i].monthly.expenditures[j];
            }

        toteva +=reliefCenter[i].total.evacuees;
        totres +=reliefCenter[i].total.resources;
        totexpend +=reliefCenter[i].total.expenditures;

        reliefCenter[i].avg = (reliefCenter[i].total.evacuees > 0) ? (reliefCenter[i].total.resources / (double)reliefCenter[i].total.evacuees) : 0.0;
        reliefCenter[i].totalexpendersper = (reliefCenter[i].total.evacuees > 0) ? (reliefCenter[i].total.expenditures / (double)reliefCenter[i].total.evacuees) : 0.0;

    }
}

//Task 5
//To display the Flood Relief Report 
void report(const center reliefCenter[],int line,double toteva,double totres,double totexpend,double avg[],double totexpendersper[]){
    cout << left << setw(20) << "CENTER CODE" << setw(25) << "CENTER NAME" << setw(12) << "STATE"
         << setw(16) << "ANNUAL EVAC" << setw(18) << "ANNUAL RES"
         << setw(21) << "ANNUAL EXP (RM)" << setw(20) << "Avg RES/EVAC"
         << setw(20) << "EXP/EVAC (RM)" << endl;

    cout << string(150, '-') << endl;

    // Display data for each center
    for (int i = 0; i < line; ++i) {
        cout << left << setw(15) << reliefCenter[i].code
             << setw(30) << reliefCenter[i].name
             << setw(15) << reliefCenter[i].state
             << setw(15) << reliefCenter[i].total.evacuees
             << setw(20) << reliefCenter[i].total.resources
             << setw(20) << reliefCenter[i].total.expenditures
             << setw(20) << fixed << setprecision(2) << reliefCenter[i].avg
             << setw(25) << fixed << setprecision(2) << reliefCenter[i].totalexpendersper
             << endl;
    }

    cout << string(150, '-') << endl;

    double totalExpenditures = 0.0;
    int highestEvacuees = 0, highestEvacueesIndex = -1;
    int lowestExpenditures = INT_MAX, lowestExpendituresIndex = -1;
    int monthlyEvacuees[month] = {0};
    int centerCount = line;

    // Calculate the total expenditures and determine center with highest evacuaees and lowest expenditures
    for (int i = 0; i < centerCount; ++i) {
        totalExpenditures += reliefCenter[i].total.expenditures;

        if (reliefCenter[i].total.evacuees > highestEvacuees) {
            highestEvacuees = reliefCenter[i].total.evacuees;
            highestEvacueesIndex = i;
        }

        if (reliefCenter[i].total.expenditures < lowestExpenditures) {
            lowestExpenditures = reliefCenter[i].total.expenditures;
            lowestExpendituresIndex = i;
        }

        // Sum evacuees for each month
        for (int j = 0; j < month; ++j) {
            monthlyEvacuees[j] += reliefCenter[i].monthly.evacuees[j];
        }
    }

    // Determine the month with highest and lowest evacuees
    int highestMonthEvacuees = 0, lowestMonthEvacuees = INT_MAX;
    int highestMonthIndex = -1, lowestMonthIndex = -1;

    for (int i = 0; i < month; ++i) {
        if (monthlyEvacuees[i] > highestMonthEvacuees) {
            highestMonthEvacuees = monthlyEvacuees[i];
            highestMonthIndex = i;
        }

        if (monthlyEvacuees[i] < lowestMonthEvacuees) {
            lowestMonthEvacuees = monthlyEvacuees[i];
            lowestMonthIndex = i;
        }
    }
    cout << endl;
    cout << "SUMMARY:" << endl;
    cout << "Total Expenditures:RM " <<fixed <<setprecision(2)<< totalExpenditures << endl;
    cout << "Center with Highest Evacuees: " << reliefCenter[highestEvacueesIndex].name << " (" << reliefCenter[highestEvacueesIndex].state << ")" << endl;
    cout << "Center with Lowest Expenditures: " << reliefCenter[lowestExpendituresIndex].name << " (" << reliefCenter[lowestExpendituresIndex].state << ")" << endl;
    cout << "Month with Highest Evacuees: Month " << highestMonthIndex + 1 << " (" << highestMonthEvacuees << " evacuees)" << endl;
    cout << "Month with Lowest Evacuees: Month " << lowestMonthIndex + 1 << " (" << lowestMonthEvacuees << " evacuees)" << endl << endl;
    
}