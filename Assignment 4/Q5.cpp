#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <stdlib.h>
#include <time.h>
#include <climits>

using namespace std;

struct point
{
	int i;
	int j;
};

int** makeGrid(int n)
{
	int** grid;
	grid= new int*[n];
	for(int i=0;i<n;i++)
	{
		grid[i]= new int[n];
	}
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			grid[i][j]= 0;
		}
	}
	return grid;
}

void printArray(int** array, int row, int col)
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

void genRandomValues(int** &grid, int n, int start, int end)
{
	srand (time(NULL));
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			grid[i][j]= rand() % end+(start);
		}
	}
}

int isValid(int n, int len)
{
	int required= n*n;
	if(len==required)
	{
		return 1;
	}
	else if(len>required)
	{
		return 0;
	}
	else
	{
		return -1;
	}
}

bool getFromArray(int** &grid, int n, int* array, int len)
{
	int valid= isValid(n, len);
	if(valid!=-1)
	{
		if(valid==0)
		{
			cout << "Input array's size more than elements to fill. Using the first " << n*n << " numbers" << endl;
		}
		int counter= 0;
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<n;j++)
			{
				grid[i][j]= array[counter];
				counter++;
			}
		}
		return 1;
	}
	else
	{
		cout << "Insufficient length. Please re-enter:" << endl;
		return 0;
	}

}

int* getInputArray(int size)
{
	int* array;
	array= new int[size];
	for(int i=0;i<size;i++)
	{
		cout << "Enter element at index " << i << ": ";
		cin >> array[i];
	}
	return array;
}

int** makeMemo(int num)
{
	int** memo;
	memo= new int*[num];
	for(int i=0;i<num;i++)
	{
		memo[i]= new int[num];
	}
	for(int i=0;i<num;i++)
	{
		for(int j=0;j<num;j++)
		{
			memo[i][j]= 0;
		}
	}
	return memo;
}

void populateMemo(int** &memo, int memoSize, int** grid, int n)
{
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			memo[i+1][j+1]= grid[i][j]+memo[i][j+1]+memo[i+1][j]-memo[i][j];
		}
	}
}

int maxProfit(int** memo, int** grid, int n, point &rightLowerCorner, int &subMatrixSize)
{
	int max= INT_MIN;
	int total= INT_MIN;

	for(int k=1;k<n;k++)
	{
		for (int i = k - 1; i < n; i++)
		{
			for (int j = k - 1; j < n; j++)
			{				
				total = memo[i][j];
				if (i - k >= 0)
				{
					total = total - memo[i - k][j];
				}
				if (j - k >= 0)
				{
					total = total - memo[i][j - k];
				}
				if (i - k >= 0 && j - k >= 0)
				{
					total = total + memo[i - k][j - k];
				}
				if (total > max)
				{
					max = total;
					rightLowerCorner.i= i;
					rightLowerCorner.j= j;
					subMatrixSize= k;
				}
			}
		}
	}
	return max;
}

int* readArray(string filename, int &size)//HAVE TO IMPLEMENT
{
	ifstream input(filename);
	string line;
	int lineNumber= 0;
	while(getline(input, line))
	{
		lineNumber++;
	}
	size= lineNumber;
	int* retArray;
	retArray= new int[size];
	int here=0;
	ifstream file(filename);
	string lines;
	while(getline(file, lines))
	{
		lines= lines+' ';
		int lineLength= lines.length();
		string toPush= "";
		for(int i=0;i<lineLength;i++)
		{
			if(lines[i]==' ')
			{
				int entry= stoi(toPush);
				retArray[here]= entry;
				here++;
				toPush= "";
			}
			else
			{
				toPush= toPush+lines[i];
			}
		}
	}
	return retArray;
}

int getWidth(point start, point end)
{
	return (end.j-start.j)+1;
}

int** removeZeros(int** memo, int size)
{
	int** array;
	array= new int*[size-1];
	for(int i=0;i<size-1;i++)
	{
		array[i]= new int[size-1];
	}
	for(int i=1;i<size;i++)
	{
		for(int j=1;j<size;j++)
		{
			array[i-1][j-1]= memo[i][j];
		}
	}
	return array;
}

point topLeftCorner(point rightLowerCorner, int squareSize)
{
	point left;
	left.i= rightLowerCorner.i-squareSize+1;
	left.j= rightLowerCorner.j-squareSize+1;
	return left;
}

int main()
{
	int n;
	cout << "Enter n: ";
	cin >> n;
	int** grid= makeGrid(n);
	char choice='0';
	cout << "1) Use an existing array to make Grid" << endl;
	cout << "2) Generate a random grid using maximum and minimum values" << endl;
	cout << "****ANY OTHER KEY TO EXIT****" << endl;
	cout << "How to populate the grid? ";
	cin >> choice;
	system("CLS");
	if(choice=='1')
	{
		char choice2= '0';
		cout << "1) Read array from text file" << endl;//HAVE TO IMPLEMENT
		cout << "2) Manually enter 1-D array of size " << n*n << endl;
		cout << "****ANY OTHER KEY TO EXIT****" << endl;
		cout << "How to make array? ";
		cin >> choice2;
		system("CLS");
		int* manualArray;
		int size;
		if(choice2=='1')//HAVE TO IMPLEMENT
		{
			size= 0;
			string filename;
			cout << "Enter the name of file containing the array: ";
			cin >> filename;
			manualArray= readArray(filename, size);
			
		}  
		else if(choice2=='2')
		{
			size= n*n;
			manualArray= getInputArray(size);
		}
		else
		{
			cout << "Exiting..." << endl;
			return 0;
		}
		getFromArray(grid, n, manualArray, size);
	}
	else if(choice=='2')
	{
		int max, min;
		cout << "Enter maximum value: ";
		cin >> max;
		cout << "Enter minimum value: ";
		cin >> min;
		if(min>max)
		{
			int temp= min;
			min= max;
			max= temp;
			cout << "Minimum cant be greater than maximum. Fixing this error..." << endl;
			cout << "Swapped!!! ^__^" << endl;
		}
		genRandomValues(grid,n,min,max);
	}
	else
	{
		cout << "Exiting..." << endl;
		return 0;
	}
	int** memo= makeMemo(n+1);
	populateMemo(memo, n+1, grid, n);
	memo= removeZeros(memo, n+1);
	point start, end;
	start.i,start.j,end.i,end.j= 0;
	int squareSize= 0;
	int maxSum= maxProfit(memo, grid, n, end, squareSize);
	start= topLeftCorner(end, squareSize);
	system("CLS");
	printArray(grid,n,n);
	cout << endl;
	cout << "Width: " << squareSize << endl;
	cout << endl;
	cout << endl;
	cout << "top left: (" << start.i << "," << start.j << ")" << endl;
	cout << "bottom right: (" << end.i << "," << end.j << ")" << endl;
	cout << endl;
	cout << endl;
	cout << "Sum: " << maxSum << endl;
	cout << endl;
}