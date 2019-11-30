#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <sstream>

using namespace std;

string* getStrings(string filename, int &err)
{
	ifstream input(filename);
	string line;
	int lineNumber= 0;
	int here= 0;
	int capacity= 3;
	err= 0;
	string* returnString;
	returnString= new string[capacity];
	while(getline(input, line))
	{
		if(here>=capacity)
		{
			err= 1;
			break;
		}
		returnString[here]= line;
		here++;
		lineNumber++;
	}
	if(lineNumber<capacity)
	{
		err= 2;
	}
	return returnString;
}

bool isInterleaving(string s1, int s1_start, int s1_end, string s2, int s2_start, int s2_end, string s3, int s3_start, int s3_end)
{
	if(s3_start==s3_end)
	{
		if((s1_start!=s1_end)||(s2_start!=s2_end))
		{
			return false;
		}
		if((s1_start==s1_end)&&(s2_start==s2_end))
		{
			return true;
		}
	}
	if((s1[0]==s3[0])&&(s2[0]==s3[0]))
	{
		bool result1= isInterleaving(s1, s1_start+1, s1_end, s2, s2_start, s2_end, s3, s3_start+1, s3_end);
		bool result2= isInterleaving(s1, s1_start, s1_end, s2, s2_start+1, s2_end, s3, s3_start+1, s3_end);
		return result1||result2;
	}
	if((s1[0]==s3[0])&&(s2[0]!=s3[0]))
	{
		return isInterleaving(s1, s1_start+1, s1_end, s2, s2_start, s2_end, s3, s3_start+1, s3_end);
	}
	if((s2[0]==s3[0])&&(s1[0]!=s3[0]))
	{
		return isInterleaving(s1, s1_start, s1_end, s2, s2_start+1, s2_end, s3, s3_start+1, s3_end);
	}
}

void populateMemo(string s1, string s2, string s3, bool** &memo)
{
	int row= s1.length()+1;
	int col= s2.length()+1;

	for(int i=0;i<row;i++)
	{
		for(int j=0;j<col;j++)
		{
			int curr= i+j-1;
			if(i==0&&j==0)
			{
				memo[i][j]= true;
			}
			else if(i==0)
			{
				if(s3[curr]==s2[j-1])
				{
					memo[i][j]= memo[i][j-1];
				}
			}
			else if(j==0)
			{
				if(s3[curr]==s1[i-1])
				{
					memo[i][j]= memo[i-1][j];
				}
			}
			else
			{
				bool result1;
				if(s1[i-1]==s3[curr])
				{
					result1= memo[i-1][j];
				}
				else
				{
					result1= false;
				}
				bool result2;
				if(s2[j-1]==s3[curr])
				{
					result2= memo[i][j-1];
				}
				else
				{
					result2= false;
				}
				memo[i][j]= result1||result2;
			}
		}
	}
}

bool** makeMemo(int row, int col)
{
	bool** memo;
	memo= new bool*[row];
	for(int i=0;i<row;i++)
	{
		memo[i]= new bool[col];
	}
	for(int i=0;i<row;i++)
	{
		for(int j=0;j<col;j++)
		{
			memo[i][j]= false;
		}
	}
	memo[0][0]= true;
	return memo;
}

void printArray(bool** array, int row, int col)
{
	for(int i=0;i<row;i++)
	{
		for(int j=0;j<col;j++)
		{
			cout << array[i][j] << " | ";
		}
		cout << endl;
	}
}

bool isValid(string s1, string s2, string s3)
{
	if(s1.length()+s2.length()==s3.length())
	{
		return true;
	}
	return false;
}

int main()
{
	string filename;
	cout << "Enter input file name: ";
	cin >> filename;
	string* elements;
	int error= 0;
	elements= getStrings(filename, error); 
	if(error==1)
	{
		cout << "more than 3 elements in the input file" << endl;
		return 1;
	}
	if(error==2)
	{
		cout << "less than 3 elements in the input file" << endl;
		return 2;
	}
	string s1= elements[0];
	string s2= elements[1];
	string s3= elements[2];
	if(isValid(s1,s2,s3))
	{
		int dimRow= s1.length()+1;
		int dimCol= s2.length()+1;
		bool** memo= makeMemo(dimRow, dimCol);
		populateMemo(s1,s2,s3,memo);
		bool result= memo[dimRow-1][dimCol-1];
		if(result)
		{
			cout << "VALID" << endl;
		}
		else
		{
			cout << "INVALID" << endl;
		}
		printArray(memo,dimRow,dimCol);
		return 0;
	}
	else
	{
		cout << "INVALID" << endl;
		return 0;
	}

}