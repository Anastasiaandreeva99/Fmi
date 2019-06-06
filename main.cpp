#include<iostream>
#include "pointer.h"
#include "transition.h"
#include "state.h"
#include "automat.h"
#include "nfa.h"
#include"list.h"
#include<cstring>
#include<fstream>
#include<vector>
#include <cstdlib>
#include"functions.h"
/*
Reading from file:
AUTOMATE INPUT-
Automate
state1 state2 ......;
state1 symbol state2
....................
stateN symbolN stateN;
Start
start_state_name;
Final
number_of__final_states final_state1 final_state2............;
COMMANDS INPUT
Command
Print id
List
Union id1 id2
Concat id1 id2
Un id
Recognise id
Final id
Empty id
*/
void save(string file_name,ofstream& output,List automates_list)
{
    output.open(file_name);
    if(output.is_open())
    {
        int help_id=automates_list[automates_list.getNumber_of_elements()-1].getId();
        Printfunc(automates_list,help_id,output);
    }
}
int main()
{
    List automates_list;
    string command,file_name;
    string save;
    int id1,id2;
    string word;
    bool is_file_open;
    ifstream example_file;
    std::cin>>command;
    while(command!="Åxit")
    {
        if(command=="Open" && !is_file_open)
        {
            std::cin>>file_name;
            example_file.open(file_name);
            is_file_open=true;
            vector<state> StateVector;
            string line;
            char transition;
            state * final_states;
            state start_state;
            int number_final_states=0;
            char state_name;
            string automate_part;
            //reading the states
            if(example_file.is_open())
            {
                std::cout<<"Opened"<<std::endl;
                if(example_file.peek()!='\0')
                {
                example_file>>state_name;
                if(state_name='(')
                {
                while(example_file>>state_name && state_name!=')')
                {
                    Transition new_transition;
                    state  new_s{state_name,new_transition};
                    StateVector.push_back(new_s);
                }
                }
                //reading transitions
                char transition_symbol;
                char _to_state;
                example_file>>state_name;
                if(state_name='(')
                {
                while(example_file>>state_name && state_name!=')' && _to_state!=')')
                {
                    if(StateVector.empty())
                    {
                        std::cout<<"Error"<<std::endl;
                        break;
                    }
                    else
                    {
                        int size=StateVector.size();
                        int index=0;
                        while(StateVector[index].getState_name()!=state_name && index<size)index++;
                        if(index==size)
                        {
                            std::cout<<"Error";
                            break;
                        }
                        else
                        {
                            example_file>>transition_symbol;
                            example_file>>_to_state;
                            pointer new_pointer{_to_state,transition_symbol};
                            StateVector[index].addPointer(new_pointer);
                        }
                    }
                }
                }
                //reading start state and final states
                string start_or_final;
                while(getline(example_file,start_or_final))
                {
                    //start state reading
                    if(start_or_final=="Start")
                    {
                        int index=0;
                        example_file>>state_name;
                        while(StateVector[index].getState_name()!=state_name && index<StateVector.size())
                            index++;
                        if(index<StateVector.size())
                        {
                            start_state=StateVector[index];
                        }
                        else
                        {
                            std::cout<<"Error in start state"<<std::endl;
                        }
                    }
                    //final states reading
                    if(start_or_final=="Final")
                    {
                        example_file>>state_name;
                if(state_name='(')
                {
                        example_file>>number_final_states;
                        final_states=new state[number_final_states+1];
                        int input_index=0;
                        while(example_file>>state_name && input_index<number_final_states && state_name!=')')
                        {
                            int index=0;
                            while(StateVector[index].getState_name()!=state_name && index<StateVector.size())
                                index++;
                            if(index<StateVector.size())
                            {
                                final_states[input_index]=StateVector[index];
                                input_index++;
                            }
                            else
                                std::cout<<"Error in final states"<<std::endl;
                        }
                   }
                   }
                }
                //we will copy th vector here ,because our automate work with array not with vector
                state* states=new state[StateVector.size()];//we will copy th vector here ,because our automate work with array not with vector
                for(int copy_index=0; copy_index<StateVector.size(); copy_index++)
                {
                    states[copy_index]=StateVector[copy_index];
                }
                int number_of_states=StateVector.size();
                Automat new_automat(start_state,states,number_of_states,final_states,number_final_states);
                Nfa automat_with_id(new_automat);
                automates_list.add_element(automat_with_id);
            }
            }
            else
                example_file.close();
            cout<<"The File is empty!The file is closed!"<<endl;
        }
        if(command=="Print" && is_file_open)
        {
            std::cin>>id1;
            std::cout<<"print"<<std::endl;
            automates_list.getAutomat(id1).print(std::cout);
        }
        if(command=="List" && is_file_open)
        {
            std::cout<<"list"<<std::endl;
            Listfunction(automates_list,std::cout);
        }
        if(command=="Union" && is_file_open)
        {
            std::cin>>id1>>id2;
            Union(automates_list,id1,id2,std::cout);
            std::cout<<"Do you want to save this ?"<<std::endl;
            std::cin>>save;
            if(save=="yes")
            {
                //example_file.close();
                ofstream output;
                output.open(file_name);
                if(output.is_open())
                {
                    int help_id=automates_list[automates_list.getNumber_of_elements()-1].getId();
                    Printfunc(automates_list,help_id,output);
                }
                std::cout<<"Saved"<<std::endl;
            }
            std::cout<<"Do you want to save this as?"<<std::endl;
            std::cin>>save;
            if(save=="yes")
            {
                std::cout<<"File:"<<std::endl;
                ofstream output;
                string save_directory;
                std::cin>>save_directory;
                output.open(save_directory);
                if(output.is_open())
                {
                    int help_id=automates_list[automates_list.getNumber_of_elements()-1].getId();
                    Printfunc(automates_list,help_id,output);
                }
                std::cout<<"Saved"<<std::endl;
            }
        }
        if(command=="Un" && is_file_open)
        {
            std::cin>>id1;
            Un(automates_list,id1,std::cout);
            std::cout<<"Do you want to save this ?"<<std::endl;
            std::cin>>save;
            if(save=="yes")
            {
                //example_file.close();
                ofstream output;
                output.open(file_name);
                if(output.is_open())
                {
                    int help_id=automates_list[automates_list.getNumber_of_elements()-1].getId();
                    Printfunc(automates_list,help_id,output);
                }
                std::cout<<"Saved"<<std::endl;
            }
            std::cout<<"Do you want to save this as?"<<std::endl;
            std::cin>>save;
            if(save=="yes")
            {
                std::cout<<"File:"<<std::endl;
                ofstream output;
                string save_directory;
                std::cin>>save_directory;
                output.open(save_directory);
                if(output.is_open())
                {
                    int help_id=automates_list[automates_list.getNumber_of_elements()-1].getId();
                    Printfunc(automates_list,help_id,output);
                }
                std::cout<<"Saved"<<std::endl;
            }
        }
        if(command=="Concat" && is_file_open)
        {
            std::cin>>id1>>id2;
            Concat(automates_list,id1,id2,std::cout);
            std::cout<<"Do you want to save this ?"<<std::endl;
            std::cin>>save;
            if(save=="yes")
            {
                //example_file.close();
                ofstream output;
                output.open(file_name);
                if(output.is_open())
                {
                    int help_id=automates_list[automates_list.getNumber_of_elements()-1].getId();
                    Printfunc(automates_list,help_id,output);
                }
                std::cout<<"Saved"<<std::endl;
            }
            std::cout<<"Do you want to save this as?"<<std::endl;
            std::cin>>save;
            if(save=="yes")
            {
                std::cout<<"File:"<<std::endl;
                ofstream output;
                string save_directory;
                std::cin>>save_directory;
                output.open(save_directory);
                if(output.is_open())
                {
                    int help_id=automates_list[automates_list.getNumber_of_elements()-1].getId();
                    Printfunc(automates_list,help_id,output);
                }
                std::cout<<"Saved"<<std::endl;
            }
        }
        if(command=="Empty" && is_file_open)
        {
            std::cin>>id1;
            Empty(automates_list,id1,std::cout);
        }
        if(command=="Final" && is_file_open)
        {
            std::cin>>id1;
            Final(automates_list,id1,std::cout);
        }
        if(command=="Deterministic" && is_file_open)
        {
            std::cin>>id1;
            if(Deterministic(automates_list,id1))std::cout<<"yes"<<std::endl;
            std::cout<<"no";
        }
        if(command=="Recognise" && is_file_open)
        {
            char* input;
            std::cin>>id1;
            std::cin>>input;
            string word(input);
            int n = word.length();
            char* _word= new char[n];
            strcpy(_word, word.c_str());
            if(Recognise(automates_list,id1,_word,std::cout))std::cout<<"Yes"<<std::endl;
            else std::cout<<"no!"<<std::endl;
        }
        if(command=="Close")
        {
            is_file_open=false;
            example_file.close();
            std::cout<<"Closed"<<std::endl;
        }
        std::cin>>command;
    }
    return 0;
}

