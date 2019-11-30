#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <sstream>

using namespace std;

int getn(string filename)
{
	ifstream infile(filename);
	string sline;
	if(infile.good())
	{
		getline(infile, sline);
	}
	infile.close();
	int size= sline.length();
	string number= "";
	int start= 2;
	while(start<=size)
	{
		number= number+sline[start];
		start++;
	}
	int n= stoi(number);
	return n;
}

void makeArrays(int* &rh, int* &rl, int n)
{
	rh= new int[n];
	rl= new int[n];
	for(int i=0;i<n;i++)
	{
		rh[i]= -1;
		rl[i]= -1;
	}
	return;
}

void populateArrays(string filename, int* &rh, int* &rl, int n)
{
	ifstream input(filename);
	string line;
	int lineNumber= 0;
	while(getline(input, line))
	{
		line= line+' ';
		if(lineNumber==0)
		{
			lineNumber++;
			continue;
		}
		int lineLength= line.length();
		int here= 0;
		string toPush= "";
		for(int i=3;i<lineLength;i++)
		{
			if(line[i]==' ')
			{
				int entry= stoi(toPush);
				if(line[1]=='H')
				{
					rh[here]= entry;
					here++;
				}
				else
				{
					rl[here]= entry;
					here++;
				}
				toPush="";
			}
			else
			{
				toPush= toPush+line[i];
			}
		}
		lineNumber++;
	}
}

void printArray(int* array, int size)
{
	for(int i=0;i<size;i++)
	{
		cout << array[i] << " | ";
	}
	cout << endl;
}

int max(int a, int b)
{
	if(a>b)
	{
		return a;
	}
	return b;
}

int maxRevenue(int* rh, int* rl, int n, int* &memo, int* &results)
{
	if(n<=0)
	{
		return 0;
	}
	if(memo[n-1]==-1)
	{
		int term1= rh[n-1]+maxRevenue(rh, rl, n-2, memo, results);
		int term2= rl[n-1]+maxRevenue(rh, rl, n-1, memo, results);
		memo[n-1]= max(term1, term2);
		if(memo[n-1]==term1)
		{
			results[n-1]= 1;
		} 
		else
		{
			results[n-1]= 0;
		}
		return memo[n-1];
	}
	else
	{
		return memo[n-1];
	}
}

void weeklyDecisions(int* &results, int n)
{
	for(int i=n-1;i>=0;i--)
	{
		if(i==0)
		{
			return;
		}
		else
		{
			if(results[i]==1)
			{
				results[i-1]= -1;
			}
		}
	}
}

void ShowWeeklyOutput(int* results, int* rh, int* rl, int n)
{
	for(int i=0;i<n;i++)
	{
		if(results[i]==1)
		{
			cout << "Week " << i+1 << ": High " << rh[i] << endl;
		}
		else if(results[i]==0)
		{
			cout << "Week " << i+1 << ": Low " << rl[i] << endl;
		}
		else if(results[i]==-1)
		{
			cout << "Week " << i+1 << ": Priming" << endl;
		}
	}
}

int main()
{
	string filename;
	cout << "Enter input file name: ";
	cin >> filename;
	int n= getn(filename);
	int* rh;
	int* rl;
	int* results;
	int* memo;
	makeArrays(rh, rl, n);
	makeArrays(results, memo, n);
	populateArrays(filename, rh, rl, n);
	int totRevenue= maxRevenue(rh, rl, n, memo, results);
	weeklyDecisions(results, n);
	ShowWeeklyOutput(results, rh, rl, n);
	cout << "Total Revenue: " << totRevenue << endl;
}