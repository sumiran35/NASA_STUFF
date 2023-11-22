
#include <cstdio> //Allows for C use in C++
#include<iostream>
using namespace std;

// note: the matrix starting point is at (0.0)
int arr[3][6];
void sendSignal()
{
    
}
void triggerSignal(int x, int y)
{
    arr[x][y] = 1;
}

int main(void) 
{  
    int count = 1;
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j <8; j++)
        {
            arr[i][j] = 0;
            count++;
        }
    }
		

	triggerSignal(0,1);
	
		int i,j;
	
	puts("Printing a 2D Array\n");

	for(i=0;i<8;i++)
	{
		for(j=0;j<8;j++)
		{
			cout<<"\t"<<arr[i][j];
		}
		cout<<endl;
	}
}