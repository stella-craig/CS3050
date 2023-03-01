#include <cs3050.h>

//Bubblesort function
void bubblesort(void *array, 
				size_t nitems, 
				size_t size, 
				int (*CompareFunc)(const void *, const void*))
{
	for (int i=0;i<nitems;i++) //for all elements in the array
	{
		for (int j=0;j<nitems-1;j++) //and for all but 1 element in the array
		{
			void * item1 = array + j*size; 		//set item1 to be A[j]
			void * item2 = array + (j+1)*size;	//set item2 to be A[j+1]
			if (CompareFunc(item1,item2)>0)		//if item1 is larger than item2
			{
				Swap(item1,item2,size);			//swap item1 and item2
			}
		}
	}
}

//Insertionsort function
void insertionsort(void *array, //generalized array pointer
				size_t nitems, 	//number of items in the array
				size_t size, 	
				int (*CompareFunc)(const void *, const void*))	//Comparison function
{

	size_t loopCounter, location; //initalize counter and location variables
	void * holder = malloc(size); //initalize a holder variable to hold the item we're moving (malloced size because thats how big each item in our array is)

	for (loopCounter = 1; loopCounter <= nitems-1; loopCounter++) //loop through the array starting at the second element because one element is inheriently already sorted
	{
		location = loopCounter; //set the location we're comparing to our location variable
		Copy(holder, array+location*size, size); //make a copy of the variable we're comparing as to not lose that data

		while ((location>0) && CompareFunc(holder, array+(location-1)*size)<0) //while the item to the left is larger than the item we're comparing
		{
			Copy(array+location*size, array+(location-1)*size, size); //copy the larger data to the right
			location = location - 1; //decrement the location (move to the left)
		}
		Copy(array+location*size, holder, size); //set the location data to the data we saved, setting it in order for the subarray A[0:loopCounter]
	}
	


	//The following code was my previous attempt to use the swap function. This algorithm works, but has significantly more swaps, making it less efficient than the one above. :)
	/*
	size_t loopCounter, location;		//initialize variables; loopCounter counts up for the loop and location refers to the location we're checking for order/swapping/comparing at

	for (loopCounter = 1; loopCounter <= nitems-1; loopCounter++)	//loop starting at 1 through all of the rest of the items in the array
	{
		location = loopCounter;	//set location to where we are in the loop

		while ((location>0) && CompareFunc(array+location*size, array+(location-1)*size)<0)	//while the location is greater than 0 (outside of the array) and the item to the left is larger than the item at our location
		{
			Swap(array+(location-1)*size, array+location*size, size);	//Swap the item with the larger item to the left of it, so they are in order (ascending)
			location = location - 1;	//decrement to move further left and check for the rest to be in order
		}	//exit for loop when you reach the beginning of the array or when the array is in order
	}
	*/

}
