#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
void *quick_sort(void *struct_args);
/*Structure to send multiple arguments in a thread*/
struct array_para
{
	int max;
	int min;
	int arr[100];
};

/*
 * thread function sorts data set in its current set
 */
int main()
{

	pthread_t thread;
	int s=0; //variable for size of array
	int arr[10];//array initializing

	printf("Enter the number of elements in array: ");
	scanf("%d",&s);

	printf("Enter the elements of array to be sorted: ");
	for(int i=0;i<s;i++)
	{
		scanf("%d",&arr[i]);
	}

	struct array_para arg ;
	arg.min=0;
	arg.max=s-1;
	for(int i=0;i<s;i++)
			{
				arg.arr[i]=arr[i];
			printf("%d %d ",&arr[i],&arg.arr[i]);
			}
printf("\n");
	pthread_create(&thread,NULL,&quick_sort,&arg);

	//printf("Thread 1 not created!!");
	//return 1;


pthread_join(thread,NULL);

	printf("Sorted Array: ");

	for(int i=0;i<s;i++)
			printf(" %p ",&arg.arr[i]);


	return 0;
}


void *quick_sort(void *struct_args)
{
	struct array_para *args = (struct array_para *) struct_args;
	int size = sizeof(args->arr);
	int min = args->min;
	int max = args->max;
	int a[size];
	for(int i=0;i<size;i++)
	{
		a[i]=args->arr[i];
	}

printf("%d %d %d",&size,&min,&max);
	int pivot= min;
	int temp=0;
	pthread_t thread_2;
	pthread_t thread_3;
	int i=min;
	int j=max;

if(i<j)
{
		while(a[i]<=a[pivot]&& i < max)
			i++;
		while(a[j]>a[pivot])
			j--;
	if(i<j)
	{
		temp=a[i];
		a[i]=a[j];
		a[j]=temp;
	}

	temp=a[pivot];
	a[pivot]=a[j];
	a[j]=temp;

	/*struct array_para arg1,arg2;


	int a[size];
	for(int i=0;i<size;i++)
	{
		a[i]=args->arr[i];
	}

	arg1.min = min;
	arg1.max = j-1;
	for(int i=0;i<size;i++)
		{
			arg1.arr[i]=a[i];
		}

	arg2.min = j+1;
	arg2.max = max;
	for(int i=0;i<size;i++)
			{
				arg2.arr[i]=a[i];
			}

if(pthread_create(&thread_2,NULL,*quick_sort,&arg1)!=0)
	{
	printf("thread 2 not created!! ");
	return 0;
	}
pthread_join(thread_2,NULL);
if(pthread_create(&thread_3,NULL,*quick_sort,&arg2)!=0)
	{
	printf("thread 3 not created");
	return 0;
	}
pthread_join(thread_3,NULL);
*/
}
return args;
}
