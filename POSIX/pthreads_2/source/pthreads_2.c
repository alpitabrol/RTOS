/*
 * pthreads_2.c
 *
 *  Created on: Sep. 16, 2019
 *      Author: takis
<<<<<<< Updated upstream
 
 edited main code by : alpit abrol
=======
>>>>>>> Stashed changes
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define	MAXINTS		100// maximum number of integers that user may enter

/*
 * 	global variables
 */
int	num_ints=0;	// current number of integers entered by user
int	done=0;		// flag indicating completion of user data entry
float	average=0.0;	// global storage for the average

/*
 *	function to display the set of numbers periodically
 */
void	disp_sorted(int *data)
{
	if (num_ints != 0)
	{
		printf("the current (sorted) integer set is: ");
		for (int i=0; i!=num_ints; ++i)
		{
			printf("%d ", data[i]);
		}
		printf("\n");
	}
	return;              	// return the pointer to x
}

/*
 *	thread function to display the average of the set of numbers periodically
 */
void 	disp_avg(float x)
{
	printf("the current average is: %f\n", x);
	return;
}


/*
 *	thread function computes average of current set
 */
void	*avg_thread(void *arr)
{
	int		*x = (int *) arr;	// cast the passed data to integer type
	int		sum;				// storage for the sum

	while (done==0)
	{
		sum=0;
		// add up the integer set
		for (int i=0; i!=num_ints; ++i)
		{
			sum += x[i];
		}
		// calculate average, if possible
		if (num_ints !=0)
		{
			average = (float) (sum/num_ints);
		}
	}
	return x; // return the set, unchanged
}

/*
 * thread function sorts data set in its current set
 */
void	*bubb_sort_thread(void *arr)
{
	int		*x = (int *) arr;	// cast the passed data to integer type
	int		swaps; 			// a flag indicating if a swap has occurred (if none occur, this set is sorted)
	int		temp;

	//while (num_ints != MAXINTS)
	while (done==0)
	{
		if (num_ints != 0)
		{
			swaps = 1;
			while (swaps==1)
			{
				swaps = 0; // if a swap occurs, this flag toggled
				for (int i=0; i!=(num_ints-1); ++i)
				{
					if (x[i] > x[i+1]) // elements must be in ascending order, if not ...
					{	// ... then swap!
						temp 	= x[i];
						x[i] 	= x[i+1];
						x[i+1] 	= temp;
						swaps  	= 1; // a swap has occurred
					}
				}
			}
		}
	}
	return x; // return the set, sorted
}

int main()
{

    pthread_t 	thread_calc_1;	// our handle for the averaging thread
    pthread_t	thread_calc_2;	// our handle for the sorting thread
    int 	set[MAXINTS]; 	// storage for our numbers
    int 	count,input;

    printf("Enter number of integers to be sorted: \t");
       scanf("%d",&count);

    // initialize set to zero
    for (int i=0; i != count; ++i)
    {
    	set[i]=0;
    }

    // create threads
    if(pthread_create(&thread_calc_1, NULL, &avg_thread, (void *)set)!=0)
    {
    	printf("Thread 1 not created\n");
    	return 1;
    }

    if(pthread_create(&thread_calc_2, NULL, &bubb_sort_thread, (void *)set)!=0)
    {
    	printf("Thread 2 not created\n");
    	return 1;
    }

    printf("Enter the numbers to be sorted\n");
    while (num_ints != count)
    {
    	scanf("%d", &input);
    	set[num_ints]=input;
    	num_ints++;
    	usleep(2000); // let pthreads to run
    	disp_sorted(set);
    	disp_avg(average);
    	printf("Number of intergers :%d\n",num_ints);
    }



    done=1; // user has finished entering data
    return 0;
}
