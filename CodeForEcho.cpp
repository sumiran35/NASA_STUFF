/*
  NASA_MINDS PROJECT
  PROGRAM FOR ECHO SYSTEM
  VERSION 1.0.0
  11/22/23
*/

//#include <SPI.h>
#include <MFRC522.h>
#include <cstdio>
#include <string>

#define Echo
#define Arduino
#define Real

#ifdef (Arduino)
  #define Echo EchoArd
#elif (Real)
  #define Echo EchoReal
#endif

#define RST_PIN1 11     // Define the RST pin on the RFID module
#define SS_PIN1 12     // Define the SDA (SS) pin on the RFID module
#define RST_PIN2 9    // Define the RST pin on the RFID module
#define SS_PIN2 10     // Define the SDA (SS) pin on the RFID module
#define RST_PIN3 7     // Define the RST pin on the RFID module
#define SS_PIN3 8     // Define the SDA (SS) pin on the RFID module
#define RST_PIN4 5     // Define the RST pin on the RFID module
#define SS_PIN4 6     // Define the SDA (SS) pin on the RFID module
#define RST_PIN5 3     // Define the RST pin on the RFID module
#define SS_PIN5 4     // Define the SDA (SS) pin on the RFID module
#define RST_PIN6 1     // Define the RST pin on the RFID module
#define SS_PIN6 2     // Define the SDA (SS) pin on the RFID module

MFRC522 reader1(SS_PIN1, RST_PIN1); //Create example instance
MFRC522 reader2(SS_PIN2, RST_PIN2); //Create example instance
MFRC522 reader3(SS_PIN3, RST_PIN3); //Create example instance
MFRC522 reader4(SS_PIN4, RST_PIN4); //Create example instance
MFRC522 reader5(SS_PIN5, RST_PIN5); //Create example instance
MFRC522 reader6(SS_PIN6, RST_PIN6); //Create example instance


void setup() {
  if (EchoArd)
  {
    Serial.begin(9600);
    SPI.begin();
    reader1.PCD_Init();
    reader2.PCD_Init();
    reader3.PCD_Init();
    reader4.PCD_Init();
    reader5.PCD_Init();
    reader6.PCD_Init();
  }
  else
  {
    printf("No Real devices connected.");
    exit(EXIT_FAILURE);
  }

  int grid[2][3][3]; //Define a matrix of 2 rows with 3 column each with 3 antennas
  MFRC522* readers[6] = {reader1, reader2, reader3, reader4, reader5, reader6};
  int sum = 0;
  int sumReader[6];
  int row, column, element;
  for (row; row < 2; ++row)
  {
    for (column; column < 3; ++column)
    {
      for (element; element < 3; ++element)
      {
        grid[row][column][element] = 0; //Populate all elements to 0 at first
      }
    }
  }
  row, column, element = 0; //Set position back to 0
}

void loop() {
  int readerNum = 0;
  sum = 0;

  if (NULL == readers[readerNum])
  {
    isTagFound(); //Check if tag is found
    digitalWrite(7, LOW); //Powers Off Arduino
  }

  if (isCardInRange(readers[readerNum])) //Check if card is in range for each reader
  {
    grid[row][column][element]++;
  }

  ++readerNum;
}

int isCardInRange(MFRC522& reader) {
  // Look for RFID tags
  if (reader.PICC_IsNewCardPresent() && reader.PICC_ReadCardSerial()) {
    reader.PICC_HaltA();
    return 1;  // Card is in range
  } else {
    return 0; // No card in range
  }
}

bool isTagFound() {
  calculateSums();
  int max = sumReader[0];
  int maxIndex = 0;
  for(int index = 0; index < 6; ++index)
  {
    if(sumReader[index] > max) //Case when group is bigger than first group
    {
      max = sumReader[index];
      maxIndex = index;
      printf("RFID tag is in the range of Antenna Block at: Row %d, Column %d", maxIndex/3, maxIndex%3);

    }
    else if(sumReader[index] == max) //Case when group 1 is the highest
    {
      printf("RFID tag is in the range of Antenna Block at: Row %d, Column %d", maxIndex/3, maxIndex%3);
    }
  }
}

//Function takes in elements in a certain block
//and sums the total in that area
// it then puts the sum for the reader in a array called sumReader
//which holds the sum for each group of antennas

void calculateSums() {
  for(int i = 0; i < 2; ++i)
  {
    for(int j=0; j<3; ++j)
    {
      for(int k=0; k<3; ++k)
      {
        sum+=grid[i][j][k];
      }
      sumReader[readerNum] = sum;
    }
  }
}







// #include <cstdio> //Allows for C use in C++
// #include<iostream>
// using namespace std;

// // note: the matrix starting point is at (0.0)
// int arr[7][7];

// void triggerSignal(int x, int y)
// {
//     arr[x][y] = 1;
// }

// int main(void) 
// {  
//     int count = 1;
//     for(int i = 0; i < 8; i++)
//     {
//         for(int j = 0; j <8; j++)
//         {
//             arr[i][j] = 0;
//             count++;
//         }
//     }
		

// 	triggerSignal(0,1);
	
// 		int i,j;
	
// 	puts("Printing a 2D Array\n");

// 	for(i=0;i<8;i++)
// 	{
// 		for(j=0;j<8;j++)
// 		{
// 			cout<<"\t"<<arr[i][j];
// 		}
// 		cout<<endl;
// 	}
// }