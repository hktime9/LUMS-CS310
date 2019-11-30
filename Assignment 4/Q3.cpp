#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <sstream>

using namespace std;

int getk(string filename)
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
	int k= stoi(number);
	return k;
}

int* getSetNumbers(string filename, int &setSize)
{
	ifstream input(filename);
	string line;
	int lineNumber= 0;
	int* array;
	while(getline(input, line))
	{
		if(lineNumber==0)
		{
			lineNumber++;
			continue;
		}
		if(lineNumber==1)
		{
			int spaces= 0;
			int lineLength= line.length();
			for(int i=2;i<lineLength;i++)
			{
				if(line[i]==' ')
				{
					spaces++;
				}
			}
			int size= spaces+1;
			setSize= size;
			array= new int[size];
			int here= 0;
			line= line+' ';
			string toPush="";
			for(int i=2;i<lineLength+1;i++)
			{
				if(line[i]==' ')
				{
					int entry= stoi(toPush);
					array[here]= entry;
					here++;
					toPush= "";
				}
				else
				{
					toPush= toPush+line[i];
				}
			}
		}
		else
		{
			break;
		}
		lineNumber++;
	}
	return array;
}

void printArray(int* array, int n)
{
	for(int i=0;i<n;i++)
	{
		cout << array[i] << " | ";
	}
	cout << endl;
}

vector<vector <int>> combinations(int num1, int num2, int k, int* set, int start, int end, int setSize, vector<vector <int>>** memo)
{
	if(memo[num1][num2].size()!=0)
	{
		return memo[num1][num2];
	}
	if(memo[num2][num1].size()!=0)
	{
		vector<vector <int>> retVec;
		retVec.push_back(memo[num2][num1][0]);
		retVec.push_back(memo[num2][num1][2]);
		retVec.push_back(memo[num2][num1][1]);
		return retVec;
	}
	if(setSize==0)
	{
		vector<vector<int>> temp;
		vector<int> main;
		for(int i=0;i<3;i++)
		{
			temp.push_back(main);
		}
		if(num1-num2==k)
		{
			temp[0].push_back(1);
			memo[num1][num2]= temp;
			return temp;
		}
		if(num2-num1==k)
		{
			temp[0].push_back(1);
			memo[num1][num2]= temp;
			return temp;
		}
		temp[0].push_back(0);
		memo[num1][num2]= temp;
		return temp;
	}
	int element= set[start];
	setSize--;
	vector<vector<int>> result1= combinations(num1+element,num2,k,set,start+1,end,setSize,memo);
	vector<vector<int>> result2= combinations(num1,num2+element,k,set,start+1,end,setSize,memo);
	if(result1[0][0])
	{
		result1[1].push_back(element);
		memo[num1][num2]= result1;
		return result1;
	}
	else if(result2[0][0])
	{
		result2[2].push_back(element);
		memo[num1][num2]= result2;
		return result2;
	}
	else
	{
		memo[num1][num2]= result1;
		return result1;
	}
}

vector<vector <int>>** makeMemo(int* set, int n)
{
	vector<vector <int>>** memo;
	int sum= 0;
	for(int i=0;i<n;i++)
	{
		sum= sum+set[i];
	}
	memo = new vector<vector <int>>*[sum+1];
	for(int i=0;i<sum+1;i++)
	{
		memo[i] = new vector<vector <int>>[sum+1];
	}
	return memo;

}

void showResult(vector<vector<int>> matrix)
{
	system("CLS");
	if(matrix[0][0])
	{
		cout << "Possible" << endl;
		int sumS1=0;
		cout << "S1: ";
		for(int i=0;i<matrix[1].size();i++)
		{
			cout << matrix[1][i] << " ";
			sumS1= sumS1 + matrix[1][i];
		}
		cout << " sum= " << sumS1 << endl;
		int sumS2=0;	
		cout << "S2: ";
		for(int i=0;i<matrix[2].size();i++)
		{
			cout << matrix[2][i] << " ";
			sumS2= sumS2 + matrix[2][i];
		}
		cout << " sum= " << sumS2 << endl;
		cout << "Difference: " << sumS1 << " - " << sumS2 << "= " << sumS1-sumS2 << endl;
	}
	else
	{
		cout << "Impossible" << endl;
	}
	return;
}

int main()
{
	string filename;
	system("DIR");
	cout << endl;
	cout << "Which input file to use? ";
	cin >> filename;
	int k= getk(filename);
	int setSize= 0;
	int* numSet= getSetNumbers(filename, setSize);
	vector<vector <int>>** memo= makeMemo(numSet, setSize);
	vector<vector<int>> result= combinations(0,0,k,numSet,0,setSize-1,setSize,memo);
	showResult(result);
	return 0;
}