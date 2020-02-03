#include<iostream>
using namespace std;
#include<string>
#include"grammar.h"
#include"pda.h"
StackAutomata unionStackAutomata(StackAutomata& automata1,StackAutomata& automata2)//makes the union automata
{
    StackAutomata newAutomata;
    list<string> nonTerminals1=automata1.getAllNonTerm();
    list<string> terminals1=automata1.getAllTerm();
    list<string> nonTerminals2=automata2.getAllNonTerm();
    list<string> terminals2=automata2.getAllTerm();
    string  newStart="Ss";
    string start1=automata1.getStart();
    string start2=automata2.getStart();
    newAutomata.setStart(newStart);
    newAutomata.addAllNonTerminals(nonTerminals1);
    newAutomata.addAllNonTerminals(nonTerminals2);
    newAutomata.addAllTerminals(terminals1);
    newAutomata.addAllTerminals(terminals2);
    newAutomata.addDelta(newStart,epsilon,start1);//add new start and epsilon deltas to the two starts
    newAutomata.addDelta(newStart,epsilon,start2);
    deltamap deltas1=automata1.getDeltas();
    deltamap deltas2=automata2.getDeltas();
    newAutomata.addDeltas(deltas1);
    newAutomata.addDeltas(deltas2);
    return newAutomata;
}
bool findNonTerminal(list<string> nonTerminals,string& newStart) //help function
{
    for(list<string>::iterator it =nonTerminals.begin();it!=nonTerminals.end();it++)
    {
        if (*it==newStart)return true;
    }
    return false;
}
string generateConcatStart(StackAutomata& automata1,StackAutomata& automata2) // generating new start name
{
    string begginingString="Concat";
    list<string> nonTerminals=automata1.getAllNonTerm();
    list<string> nonTerminals2=automata1.getAllNonTerm();
    while (findNonTerminal(nonTerminals,begginingString) || findNonTerminal(nonTerminals2,begginingString))
    {
        begginingString + "Concat";
    }
    return begginingString;
}
StackAutomata concatAutomata(StackAutomata& automata1,StackAutomata& automata2)//concatenation
{
    StackAutomata newAutomata;
    list<string> nonTerminals1=automata1.getAllNonTerm();
    list<string> terminals1=automata1.getAllTerm();
    list<string> nonTerminals2=automata2.getAllNonTerm();
    list<string> terminals2=automata2.getAllTerm();
    string  newStart=generateConcatStart(automata1,automata2);
    string start1=automata1.getStart();
    string start2=automata2.getStart();

    newAutomata.setStart(newStart);
    newAutomata.addAllNonTerminals(nonTerminals1);
    newAutomata.addAllNonTerminals(nonTerminals2);
    newAutomata.addAllTerminals(terminals1);
    newAutomata.addAllTerminals(terminals2);
    newAutomata.addDelta(newStart,epsilon,start1);//adding new start and epsilon delta from the new start to the first one
    deltamap deltas1=automata1.getDeltas();
    for(auto& it:deltas1) //add deltas from the final of the first automata to the final of the second
    {
        list<string>& values = it.second;
            for(auto& x : values)
            {
                if(x=="f")
                {x=start2;
                cout<<x<<endl;
                }
            }
    }
    deltamap deltas2=automata2.getDeltas();
    newAutomata.addDeltas(deltas1);
    newAutomata.addDeltas(deltas2);
 return newAutomata;
}
string generateKleneStart(StackAutomata& automata1)//klene star
{
    string begginingString="Klene";
    list<string> nonTerminals=automata1.getAllNonTerm();
    while (findNonTerminal(nonTerminals,begginingString))
    {
        begginingString + "Klene";
    }
    return begginingString;
}
StackAutomata kleneAutomata(StackAutomata& automata1)
{
    StackAutomata newAutomata;
    list<string> nonTerminals1=automata1.getAllNonTerm();
    list<string> terminals1=automata1.getAllTerm();
    string  newStart=generateKleneStart(automata1);
    string start1=automata1.getStart();
    newAutomata.setStart(newStart);
    newAutomata.addAllNonTerminals(nonTerminals1);
    newAutomata.addAllTerminals(terminals1);
    newAutomata.addDelta(newStart,epsilon,start1);
    deltamap deltas1=automata1.getDeltas();

    string finalF = "f";
    newAutomata.addDelta(newStart,epsilon,finalF);//adding epsilon delta
    newAutomata.addDeltas(deltas1);

 return newAutomata;
}
bool findNonTemrinal(list<string>& nonTerminals,string newStart)
{
    for(list<string>::iterator it =nonTerminals.begin();it!=nonTerminals.end();it++)
    {
        if (*it==newStart)return true;
    }
    return false;
}

