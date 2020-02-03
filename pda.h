#include<iostream>
#include<stack>
#include<string>
#include<list>
#include<windows.h>
#include<map>
using namespace std;
typedef map<pair<string,string>,list<string>> deltamap;
string epsilon="@";
void setConsoleColor(WORD c)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
//pushdown automata class
class StackAutomata
{
    list<string> nonTerminals;//Non terminals and is it the start non terminal
    list<string> terminals;//terminals
    deltamap delta;
    string start;
    stack<char> words;
public:
    StackAutomata();
    StackAutomata(list<string>& nonTerminals,list<string>& terminals,string& start);
    void addAllNonTerminals(list<string>& nonTerminals);
    void addAllTerminals(list<string>& terminals);
    void addNonTerminals(string& non_terminal);
    void addTerminal(string& terminal);
    void addDelta(string&, string&, string&);
    void setStart(string& start);
    void addDeltas(deltamap& deltas);
    void unionAutomata(StackAutomata& );
    void print();
    bool findNonTerminal(string newStart);
    bool findTerminal(string& term)
    {
        for(list<string> :: iterator it=terminals.begin();it!=terminals.end();it++)
        {
            if(*it==term)return true;
        }
        return false;
    }
    bool findWord(string& word);
    bool findWordRecursion(stack<string>& wordInStack,string& current);
    bool isEmpty()const
    {
        return delta.empty();
    }
    string getStart()const
    {
        return start;
    }
    deltamap getDeltas()const
    {
        return delta;
    }
    void addNonTerminal(string& t)
    {
        nonTerminals.push_back(t);
    }

    list<string> getAllNonTerm()const
    {
        return nonTerminals;
    }
    list<string> getAllTerm()const
    {
        return terminals;
    }
    void reset();
    bool Empty();
    bool isEmpty(string);
    bool isFinal(list<string>&);
};
StackAutomata::StackAutomata(list<string>& nonTerminals,list<string>& terminals,string& start)
{
    addAllTerminals(terminals);
    addAllNonTerminals(nonTerminals);
    setStart(start);
}
StackAutomata::StackAutomata() {};
void StackAutomata::addDeltas(deltamap& deltas)
{
    for(deltamap::iterator it=deltas.begin(); it!=deltas.end(); it++)
    {
        pair<string,string> fromwith=it->first;
        string from=fromwith.first;
        string with=fromwith.second;
        list<string> to=it->second;
        for(list<string>::iterator it=to.begin(); it!=to.end(); it++)
            addDelta(from,with,*it);
    }
}
bool StackAutomata::findNonTerminal(string newStart)
{
    for(list<string>::iterator it =nonTerminals.begin();it!=nonTerminals.end();it++)
    {
        if (*it==newStart)return true;
    }
    return false;
}
void StackAutomata::addAllNonTerminals(list<string>& nonTerminals)
{
    if(!nonTerminals.empty() && start.empty())
    {
        start=nonTerminals.front();
    }
    for(list<string>::iterator it=nonTerminals.begin() ; it!=nonTerminals.end(); it++)
    {
        if(!(*it=="f" && findNonTerminal(*it)))
        this->nonTerminals.push_back(*it);
    }

}
void StackAutomata::addAllTerminals(list<string>& terminals)
{
    for(list<string>::iterator it=terminals.begin() ; it!=terminals.end(); it++)
    {
        this->terminals.push_back(*it);
    }
}
void StackAutomata::addNonTerminals(string& non_terminal)
{
    this->nonTerminals.push_back(non_terminal);
}
void StackAutomata::addTerminal(string& terminal)
{
    this->terminals.push_back(terminal);
}
void StackAutomata::addDelta(string& from, string& with, string& to)
{
    pair<string,string> key ;
    key.first = from;
    key.second = with;
    if(delta.count(key)== 0)
    {
        list<string> toList;
        toList.push_back(to);
        delta.emplace(pair<pair<string&,string&>,list<string>&> (pair<string&,string&>(from,with),toList));
    }
    else
        delta.find(key)->second.push_back(to);
}
void StackAutomata::setStart(string& start)
{
    this->start=start;
}
void StackAutomata::unionAutomata(StackAutomata& automata)
{
    list<string> new_nonTerminals=automata.getAllNonTerm();
    list<string> new_terminals=automata.getAllTerm();
    addAllNonTerminals(new_nonTerminals);
    addAllTerminals(new_terminals);
    string  new_start="Ss";
    string start1=getStart();
    string start2=automata.getStart();
    addDelta(new_start,epsilon,start1);
    addDelta(new_start,epsilon,start2);
    start="Ss";
    deltamap new_deltas=automata.getDeltas();
    addDeltas(new_deltas);
}
void StackAutomata::print()
{
        system("color 0");
    setConsoleColor(FOREGROUND_GREEN);
    cout<<"Start: ";
    setConsoleColor(FOREGROUND_RED );
    cout<<start<<endl;
    setConsoleColor(FOREGROUND_GREEN);
    cout<<"terminals:"<<endl;
    setConsoleColor(FOREGROUND_RED );
    for(list<string>::iterator iterm=terminals.begin(); iterm!=terminals.end(); iterm++)
    {
        cout<<*iterm<<endl;
    }
    setConsoleColor(FOREGROUND_GREEN);
    cout<<"nonTerminals:"<<endl;
        setConsoleColor(FOREGROUND_RED );
    for(list<string>::iterator interm=nonTerminals.begin(); interm!=nonTerminals.end(); interm++)
    {
        cout<<*interm<<endl;
    }
    //print deltas
        setConsoleColor(FOREGROUND_GREEN);
    cout<<"deltas:"<<endl;
    for(auto const& pairs: delta)
    {
        pair<string,string> key=pairs.first;
        string key1=key.first;
        string key2=key.second;
        list<string> value=pairs.second;
            setConsoleColor(FOREGROUND_RED );

        for(list<string>::iterator it = value.begin(); it!=value.end(); it++)
        {
            cout<<"("<<key1<<","<<key2<<")="<<*it<<endl;
        }
    }
}

bool StackAutomata::findWord(string& word)
{
    if(this->isEmpty())
        return false;
    stack<string> wordInStack;
    for(string::reverse_iterator it = word.rbegin(); it!=word.rend(); it++)
    {
        string help;
        string strIt;
        strIt.push_back(*it);
        if(!findTerminal(strIt)&& strIt!="@")return false;
        help.push_back(*it);
        wordInStack.push(help);
    }
    string current=this->getStart();
    //string currentletter= wordInStack.top();
    //pair<string,string> keypairstart =pair<string,string>(current,currentletter);
    return findWordRecursion(wordInStack,current);
}
bool StackAutomata::findWordRecursion(stack<string>& wordInStack,string& current)
{
    if(wordInStack.empty() && current == "f")return true;
    if(!wordInStack.empty() && current == "f")return false;
    pair<string,string> keypair = pair<string,string>(current,wordInStack.top());
    pair<string,string> keypairEpsilon = pair<string,string>(current,"@");
    string lastLetter=wordInStack.top();
    wordInStack.pop();
    if(delta.count(keypair)==1 || delta.count(keypairEpsilon)==1 )
    {
        list<string> value = delta.find(keypair)->second;
        list<string>::iterator it= value.begin();
        while(it!=value.end())
        {
           if(findWordRecursion(wordInStack,*it))return true;
           else wordInStack.push(lastLetter);
           it++;

        }
    }
    else
        return false;
}
bool StackAutomata::Empty()
{
    return isEmpty(this->getStart());
}
bool StackAutomata :: isFinal(list<string>& l)
{
    bool found=false;

    for(auto const x: l)
    {
        if (x=="f")found = true;
    }

return found;
}
bool StackAutomata::isEmpty(string cur)//part of the bonus-not working properly
{
    list<pair<string,string>> pairList;
    for(auto const it: this->getDeltas())
    {   pair<string,string> current = it.first;
        if(current.first == cur)pairList.push_back(current);
    }
    bool found = false;
    while(!pairList.empty() && !found)
    {
        list<string> next= (this->getDeltas()).find(pairList.front())->second;
        bool found1= false;
        while(!next.empty() && !found1)
        {
            if (isFinal(next))found1= true;
            else
            {
                if (isEmpty(next.front()))found1=true;
            }
            next.pop_front();
        }
        if(found1) found = true;
        pairList.pop_front();
    }
      return found;
}
