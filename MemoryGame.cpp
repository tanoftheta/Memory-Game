#include "MemoryGame.hpp"
#include <cstdlib> //srand, rand
#include <ctime>
#include <iomanip> //setw
#include <iostream> //std
#include <vector>
using namespace std;

int* randomize(int numSlots); //function to randomize layout
void swap(int* arr, int i, int j);
void displaySeparateLine(int numSlots);

//TODO: implement by students
MemoryGame::MemoryGame() //default constructor, 
    //set numPairs = 3, numSlots = 2 * numPairs + 2,
    //put 3 pairs of randomly generated ints in [0, 1000)
    //randomly in numSlots blocks. 
    //Note that 2 added after 2 * numPairs means number of 
    //two extra blocks without actual data.
{
    srand(time(NULL)); //TODO: uncomment this line to see
        //different layouts of numbers in different runnings.
        //time(NULL) is the current running time.
        //use the current running time to grow random sequence
        //Since running time differs,
        //the random sequence looks different
        //at different running time.
    srand(1); //TODO: add this before submitting to gradescope,
        //or autograde script cannot handle random input.

    //TODO: your code here
    int numPairs = 3; //do not write int numPairs = 3;
    int numSlots = 8; //3 pairs residing in 8 spaces,
    int * nums = new int[3];
    for(int d=0; d < 3; d++)
    {
        nums[d] = rand() % 1000;
    }
    values = new string[numSlots];
    int * arr = randomize(numSlots);
    for(int i=0; i < numSlots; i++)
    {
        if (i < numSlots - 2)
        {
            values[arr[i]] = to_string(nums[i/2]);
        }
        else
        {
            values[arr[i]] = ""; 
        }
    }//there are two empty spaces
    //IMPORTANT:
    //generate three random ints in [0, 1000),
    //randomly set them in the layout of the spaces,
    //that is, set up values array.
    delete[] nums; 
    nums = nullptr; 
    delete[] arr; 
    arr = nullptr; 
}

//TODO: implement by students
MemoryGame::~MemoryGame()
{

}

//TODO: implement by students
//randomize is not a member function,
//so there is no MemoryGame:: before function name randomize.
//Return an array of randomly allocated 0, 1, .., size-1
//In constructors, randomly assign the data in dataVector 
//to array values
int* randomize(int size)
{
    int *randarray = new int[size];
    for (int i = 0; i < size; i ++)
    {
        randarray[i] = i; 
    }
    int ind1; 
    while (size>0)
    {
        ind1 = rand() % size; 
        swap(randarray, ind1, size-1);
        size--;
    }
    return randarray; 
}

//TODO: implement by students
//int* arr means int array arr, which implies the address
//of the first element of array arr.
//swap arr[i] and arr[j] in array of ints arr.
void swap(int *arr, int i, int j)
{
    int temp = arr[i]; 
    arr[i] = arr[j]; 
    arr[j] = temp; 
}

//Display -----+ for numSlots times.
//Add an extra + when for the first block (when index i is 0).
//So suppose numSlots is 8, we get
//+-----+-----+-----+-----+-----+-----+-----+-----+
//followed by a new line.
void displaySeparateLine(int numSlots)
{
    for (int i = 0; i < numSlots+1; i++)
    {
        if (i == 0)
        {
           cout << "+";
        }
        else 
        {
        cout << "-----+";
        }
    }
    cout << endl;
}

//TODO: implement by students
//display the items in values array where bShown is true.
void MemoryGame::display(bool* bShown)
{
    int numSlots = 8; 
    cout << " "; 
    for (int i=0; i < numSlots; i++)
    {
        cout << setw(3) << i; 
        cout << setw(3) << " "; 
    }
    cout << endl;
    displaySeparateLine(8);
    for (int i = 0; i < numSlots; i++)
    {
        if (bShown[i])
        {
            cout << "|" << setw(5) << values[i];
        }
        else 
        {
            cout << "|" << setw(5) << ""; 
        }
    }
    cout << "|" << endl; 
    displaySeparateLine(8);
}

//TODO: implement by students
//rules for a round
//(1) pick a number, flip it
//(2) pick a second number, if the number is the same as
//    previous pick, display the second number,
//    otherwise, unflip the previous pick.
//(3) Finish until every pair are chosen correctly.
void MemoryGame::play()
{
    bool* bShown = new bool[numSlots];
    display(bShown); 
    int index, first; 
    int numFlips, pairsFound=0; 
    while (pairsFound<3)
    {
        cout << "Pick a cell to flip: " ; 
        cin >> index; 
        while (index < 0 || index > 7 || bShown[index] == true) //validate input 
        {
            if (bShown[index]== true)
            {
                cout << "The cell indexed at " << index << " is shown." << endl; 
            }
            cout << "Re-enter an index: "; 
            cin >> index; 
        }
        if (numFlips % 2 == 0) //if this is the first flip 
        {
            bShown[index] = true; 
            first = index; 
        }
        else
        {
            if (values[index]==values[first] && values[first] != "")
            {
                bShown[index]=true; 
                pairsFound++; 
            }
            else 
            {
                bShown[first]=false;
                first = index; 
            }
        }
        display(bShown);
        numFlips += 1;
    }
    cout << "Congratulations! Take " << numFlips << " steps to find all matched pairs." << endl;
    delete[] bShown; 
    bShown = nullptr; 
}