#include<iostream>
#include<list>
#include<vector>
#include<string>
#include<stack>
#include <fstream>
#include"transformfromreading.h"
void loadFile(StackAutomata& automata)//getting everything from the file
{
    setConsoleColor(FOREGROUND_BLUE);
    cout<<"FileName:"<<endl;
    string filename;
    setConsoleColor(FOREGROUND_RED);
    cin>>filename;
    ifstream file(filename);
    string str;
    string fileContents;
    while (getline(file, str))
    {
        fileContents += str;

    }
    string terminals;
    string nonTerminals;
    list<string> rules;
    readTerminalsNonTerminals(terminals,nonTerminals,fileContents);
    substract(fileContents);
    readRules(rules,fileContents);
    read(rules,terminals,nonTerminals,automata);
    automata.print();
    setConsoleColor(FOREGROUND_BLUE);
    cout<<"----------------------------------------------------------------------------------------------------------"<<endl;

}
using namespace std;
int main()
{ //reading from file
    string command;

    setConsoleColor(FOREGROUND_BLUE);
    cout<<"Welcome!"<<endl<<"Here are some instructions"<<endl;
    cout<<"Your file should be:"<<endl<<"Terminals: term1 term2 term3 ......"<<endl<<"Non_Terminals: nterm1 nterm2 neterm3 ......"<<endl<<"Rules:"<<endl<<"rule1,rule2,END"<<endl<<"---------------------------------------------"<<endl;
    setConsoleColor(FOREGROUND_BLUE);
    cout<<"To add new grammar from file - LoadFile"<<endl<<"To search for a word - Word"<<endl<<"Union of two grammars - Union"<<endl<<"Else - END"<<endl<<"Concatenetion of two grammars - Concat"<<endl<<"Klene star - Klene"<<endl;
    while(command!="END")//different commands
    {
        setConsoleColor(FOREGROUND_RED);
        cin>>command;
        if(command == "Word")
        {
             StackAutomata automata1;
                loadFile(automata1);
            string word;
            cout<<"type word:"<<endl;
            cin>>word;
            setConsoleColor(FOREGROUND_GREEN);
            cout<<"Is '"<<word<<"' in the grammar language?"<<endl;
            cout<<"'"<<word<<"'";
            setConsoleColor(FOREGROUND_RED );
            if(automata1.findWord(word))
                cout<<" is in the language of the grammar"<<endl;
            else
                cout<<" is not recognised"<<endl;
        }
        else
        {
            if(command == "LoadFile" )
            {
                StackAutomata automata1;
                loadFile(automata1);
            }
            else
            {
                if(command=="Union")
                {
                    StackAutomata automata1,automata2,newAutomata;
                    loadFile(automata1);
                    loadFile(automata2);
                    newAutomata=unionStackAutomata(automata1,automata2);
                    setConsoleColor(FOREGROUND_RED );
                    cout<<"Union Automata"<<endl;
                    newAutomata.print();
                }
                else
                {
                    if(command=="Concat")
                {
                    StackAutomata automata1,automata2,newAutomata;
                    loadFile(automata1);
                    loadFile(automata2);
                    newAutomata=concatAutomata(automata1,automata2);
                    setConsoleColor(FOREGROUND_RED );
                    cout<<"Concat Automata"<<endl;
                    newAutomata.print();
                }
                else
                {
                     if(command=="Klene")
                {
                    StackAutomata automata1,newAutomata;
                    loadFile(automata1);

                    newAutomata=kleneAutomata(automata1);
                    setConsoleColor(FOREGROUND_RED );
                    cout<<"Klene Automata"<<endl;
                    newAutomata.print();
                }
                else cout<<"ERROR"<<endl;
                }
                }
            }
        }
    }
    return 0;
}
