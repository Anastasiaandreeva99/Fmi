#include<iostream>
#include<list>
#include<vector>
#include<string>
#include<stack>
#include"functions.h"
using namespace std;
//here are some help functions that seperate the different parts of the input and build the grammar after that the automata also

bool isTerminal(string& input)
{
    return (input.size()==1 && !(input>="A" && input<="Z"));
}
void rulesFromString(string& input,string& left,list<string>& rightString)
{
    string::iterator it=input.begin();
    for(it; it!=input.end()&&*it!='-'; it++)
    {
        left.push_back(*it);
    }
    while(it!=input.end())//(Sisi-a b | )
    {
        it++;
        string newData;
        while(it!=input.end() && *it!=' ')
        {
            newData.push_back(*it);
            it++;
        }
        rightString.push_back(newData);
    }
}
void stringToList(string& str,list<string>& l)
{
    string::iterator it = str.begin();
    while(it!=str.end())
    {
        string newData;
        while(it!=str.end() && *it!=' ')
        {
            newData.push_back(*it);
            it++;
        }
        l.push_back(newData);
        if(it!=str.end())
            it++;
    }
}

void separateString(string& input,list<string>& listStrings)
{
    string left;
    string::iterator it=input.begin();
    for(it; it!=input.end()&&*it!='-'; it++)
    {
        left.push_back(*it);
    }
    left.push_back(*it);
    while(it!=input.end())
    {
        string newString;
        newString.append(left);
        it++;
        while(it!=input.end() && *it!='|')
        {
            newString.push_back(*it);
            it++;
        }
        listStrings.push_back(newString);
    }
}
void readRule(list<string> rightString,string& left,Grammar& grammar )//trnasforming rules
{
    if(rightString.size()==1)
    {
        string first=rightString.front();
        string final="f";
        if(isTerminal(first))
        grammar.addRules(left,first,final);
        else grammar.addRules(left,epsilon,first);
    }
    else
    {
        if(rightString.size()<=2)
        {
            string first=rightString.front();//proverka ako e ssmo edno
            rightString.pop_front();
            string second=rightString.front();
            grammar.addRules(left,first,second);
        }
        else
        {
            string help= rightString.front();
            rightString.pop_front();
            string newNonTerminal;
            grammar.generateNonTerminal(newNonTerminal);
            grammar.addRules(left,help,newNonTerminal);
            grammar.addNonTerminal(newNonTerminal);
            readRule(rightString,newNonTerminal,grammar);
        }
    }
}

void readGrammar(list<string>& rules,string& terminals,string& nonTerminals,Grammar& grammar)//build a grammar
{

    list<string> listTerminals;
    list<string> listNonTerminals;
    stringToList(terminals,listTerminals);
    stringToList(nonTerminals,listNonTerminals);
    grammar.addTerminals(listTerminals);
    grammar.addNonTerminals(listNonTerminals);
    for(list<string>::iterator it=rules.begin(); it!=rules.end(); it++)
    {
        string& rule=*it;
        string leftNonTerminal;
        list<string> rightData;
        rulesFromString(rule,leftNonTerminal,rightData);
        //if(!findNonTemrinal(leftNonTerminal))
        //cout<<"Error,the Non Terminal is not in this grammar"<<endl;
        //else
        readRule(rightData,leftNonTerminal,grammar);
    }
}
void toAutomat(Grammar& grammar,StackAutomata& newAutomata)//transforoming grammar o an automat
{
    list<string> allnon=grammar.getNonTerminals();
    string final="f";
    newAutomata.addNonTerminal(final);
    newAutomata.addAllNonTerminals(allnon);

    list<string> allterm=grammar.getTerminals();
    newAutomata.addAllTerminals(allterm);
    list<GrammarRules> rules=grammar.getAllRules();
    for(list<GrammarRules>::iterator it=rules.begin(); it!=rules.end(); it++)
    {
        GrammarRules grammarRule=*it;
        newAutomata.addDelta(grammarRule.left,grammarRule.right1,grammarRule.right2);
    }
}
void read(list<string>& rules,string& terminals,string& nonTerminals,StackAutomata& automata)
{
    list<string> listRules;
    for(list<string>::iterator it=rules.begin(); it!=rules.end(); it++)
    {
        separateString(*it,listRules);
    }
    Grammar grammar;
    readGrammar(listRules,terminals,nonTerminals,grammar);
    toAutomat(grammar,automata);
}
string substract(string& fileContents)
{
    unsigned found = fileContents.find_first_of(":");
    string command=fileContents.substr(0,found);
    fileContents= fileContents.substr( found + 1 );
    return command;
}
string getContent(string& fileContents) //Getting terminals or non terminals
{
    unsigned found = fileContents.find_first_of(";");
    string terminals = fileContents.substr(1,found-1);
    fileContents= fileContents.substr(found +1);
    return terminals;
}
string getRule(string& fileContents)//GETTING ONLY ONE RULE
{
    unsigned found = fileContents.find_first_of(",");
    string rule = fileContents.substr(0,found);
    fileContents= fileContents.substr(found +1);
    return rule;
}
void readTerminalsNonTerminals(string& term,string& nonTerm,string& fileContents)
{
    if(substract(fileContents)=="Terminals")
    {
        term=getContent(fileContents);
        substract(fileContents);
        nonTerm=getContent(fileContents);
    }
    else
    {
        nonTerm=getContent(fileContents);
        substract(fileContents);
        term=getContent(fileContents);
    }

}
void readRules(list<string>& rulesList,string& rules)//get rules from inout
{

    while(rules.find("END")!=0)
    {
        string newrule=getRule(rules);
        rulesList.push_back(newrule);
    }
    return ;
}
