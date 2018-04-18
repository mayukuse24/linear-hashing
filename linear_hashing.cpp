#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <fstream>
#include <algorithm>
#include <stdlib.h>

using namespace std;

vector<vector<int>> table;

int mod=5,elecount=0;
int spointer=0;
int max_buffer_size=6;

void print_table() //Debug purpose
{
    for(int i=0;i<table.size();i++)
    {
	cout<<i<<" --> ";
	for(int j=0;j<table[i].size();j++)
	{
	    if(j == max_buffer_size) //display overflow records separately
		cout<<" ## ";
	    
	    cout<<table[i][j]<<" ";
	}
	cout<<endl;
    }
}

void split_table()
{
    float thresh = (elecount*100)/(table.size()*max_buffer_size);
    //cout<<"Thresh= "<<thresh<<endl;
    if(thresh >= 75.0)
    {
	table.push_back(vector<int>());
	
	int loc,temp;
	for(int i=0;i<table[spointer].size();i++)
	{
	    loc = abs(table[spointer][i]) % (mod * 2) ;
	    
	    if(loc != spointer) //Shifting elements to other bucket if index is different from split pointer
	    {
		table[loc].push_back(table[spointer][i]);
		table[spointer].erase(table[spointer].begin() + i);
		i--; //Removing element causes next element to shift left in vector. TODO : Very poor fix, change this.
	    }
	}
	spointer++;

	if(spointer == mod) //One level completed
	{
	    spointer = 0; //start from first bucket
	    mod *= 2;
	    //print_table();
	}
    }
}

void insert(int key)
{
    int loc = abs(key) % mod;
    if(loc < spointer)
    {
	loc = abs(key) % (mod*2);
    }

    if(find(table[loc].begin(), table[loc].end(), key) == table[loc].end())
	cout<<key<<endl;
    
    table[loc].push_back(key);
    elecount++; //keeps track of total elements currently in linear hash table
    
    split_table(); //Check if threshold > 75% and split at split pointer
}

int main(int argc,char *argv[])
{
    //cout<<"Linear Hash Table"<<endl;

    if(argc < 3)
    {
	cerr<<"Usage: ./prog filename M B"<<endl;
	return -1;
    }
    
    //Make initial table size as mod
    for(int i=0;i<mod;i++)
    {
	table.push_back(vector<int>());
    }

    ifstream infile(argv[1]);
    string line;
    while (getline(infile, line))
    {
	istringstream iss(line);
	int a;
	if (!(iss >> a)) { break; } // error
	
	// process 
	insert(a);
    }
    /*
    insert(4);
    insert(5);
    insert(6);
    insert(12);
    */

    //cout<<endl<<endl;
    //print_table();
}
