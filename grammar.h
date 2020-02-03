#ifndef GRAMMAR_H_
#define GRAMMAR_H_
#include<iostream>
#include<list>
#include<vector>
#include <stdio.h>
#include<string>
#include <string.h>
#include<algorithm>
using namespace std;
struct GrammarRules
{
    string left;
    string right1;
    string right2;
};

class Grammar{
list<GrammarRules> rules;
list<string> terminals;
list<string> nonTerminals;
public:
    Grammar()
    {
    }
Grammar(list<string>& term,list<string>& nonTerm,list<GrammarRules>& rul);
Grammar(Grammar const& grammar);
Grammar& operator=(Grammar const& grammar);
void addTerminals(list<string>&);
void addNonTerminals(list<string>&);
void addRules(string&,string&,string&);
void addNonTerminal(string& nonTerm)
{
    nonTerminals.push_back(nonTerm);
}
void generateNonTerminal(string&);
void setRules(list<GrammarRules> rules);
void setTerminals(list<string> terminals);
void setNonTerminals(list<string> nonTerminals);
GrammarRules getRule()const;
GrammarRules getEraseRule();
list<string> getTerminals()const;
list<string> getNonTerminals()const;
list<GrammarRules> getAllRules()const;
string generateRandomString(size_t length);
bool findNonTerminal(string&);
void print();
};
GrammarRules Grammar::getRule()const
{
    return rules.front();
}
GrammarRules Grammar::getEraseRule()
{
    GrammarRules result=this->rules.front();
    this->rules.pop_front();
    return result;
}
list<GrammarRules> Grammar::getAllRules()const
{
    return rules;
}
list<string> Grammar::getTerminals()const
{
    return terminals;
}
list<string> Grammar::getNonTerminals()const
{
    return nonTerminals;
}

Grammar::Grammar(list<string>& term,list<string>& nonTerm,list<GrammarRules>& rul)
{
    setTerminals(term);
    setNonTerminals(nonTerm);
    setRules(rul);
}
Grammar::Grammar(Grammar const& grammar)
{
    setTerminals(grammar.terminals);
    setNonTerminals(grammar.nonTerminals);
    setRules(grammar.rules);
}
Grammar& Grammar::operator=(Grammar const& grammar)
{
      if (&grammar != this)
      {
    setRules(grammar.rules);
    setTerminals(grammar.terminals);
    setNonTerminals(grammar.nonTerminals);
      }
  return *this;

}
void Grammar::addTerminals(list<string>& terminals)
{
    list<string>::iterator it=terminals.begin();
    while(it!=terminals.end())
     {
         this->terminals.push_back(*it);
         it++;
     }
}
void Grammar::addNonTerminals(list<string>& nonTerminals)
{
    list<string>::iterator it=nonTerminals.begin();
    while(it!=nonTerminals.end())
     {
         this->nonTerminals.push_back(*it);
         it++;
     }
}
void Grammar::addRules(string& left,string& term1,string& term2)
{
    GrammarRules newRule;
    newRule.left=left;
    newRule.right1=term1;
    newRule.right2=term2;
    this->rules.push_back(newRule);
};
void Grammar::setRules(list<GrammarRules> rules)
{
   while(!this->rules.empty())
   {
       this->rules.erase(this->rules.begin());
   }
      while(!rules.empty())
     {
         this->rules.push_back(rules.front());
         rules.pop_front();
     }
}
void Grammar::setTerminals(list<string> terminals)
{
       while(!this->terminals.empty())
   {
       this->terminals.erase(this->terminals.begin());
   }
        while(!terminals.empty())
     {
         this->terminals.push_back(terminals.front());
         terminals.pop_front();
     }
}
void Grammar::setNonTerminals(list<string> nonTerminals)
{
        while(!this->nonTerminals.empty())
   {
       this->nonTerminals.erase(this->nonTerminals.begin());
   }
      while(!nonTerminals.empty())
     {
         this->nonTerminals.push_back(nonTerminals.front());
         nonTerminals.pop_front();
     }
}
string Grammar::generateRandomString(size_t length)
{
  const char* charMap = "ABCDEFGHIJKLMNOPQRSTUVWXYZ123456789";
  const size_t charMapLength = strlen(charMap);
  auto generator = [&](){ return charMap[rand()%charMapLength]; };
  string result;
  result.reserve(length);
  generate_n(back_inserter(result), length, generator);
  return result;
}
void Grammar::generateNonTerminal(string& newNonTerminal)
{
    int len=1;
    newNonTerminal="Z";
    while(findNonTerminal(newNonTerminal))
    {
        int combination=0;
        while(findNonTerminal(newNonTerminal) && combination<len*35)
        {
            newNonTerminal=generateRandomString(len);
            combination++;
        }
        len++;
    }
}
bool Grammar::findNonTerminal(string& nonTerminal)
{
    list<string>::iterator it=nonTerminals.begin();
    while(it!=nonTerminals.end())
    {
        if(*it==nonTerminal)return true;
        else it++;
    }
    return false;

}
void Grammar::print()
{
    for(list<GrammarRules>::iterator itrule=rules.begin();itrule!=rules.end();itrule++)
    {
        GrammarRules currentRule=*itrule;
        cout<<"rule:"<<currentRule.left<<'-'<<currentRule.right1<<' '<<currentRule.right2<<endl;
    }
    for(list<string>::iterator itTerm=terminals.begin();itTerm!=terminals.end();itTerm++)
    {
        cout<<"terminals:"<<endl<<*itTerm<<endl;
    }
    for(list<string>::iterator itNonTerm=nonTerminals.begin();itNonTerm!=nonTerminals.end();itNonTerm++)
    {
        cout<<"nonTerminals:"<<endl<<*itNonTerm<<endl;
        cout<<"nonTerminals:"<<endl<<*itNonTerm<<endl;
    }
}
#endif
