#include<stdio.h>
#include<stdlib.h>

void display(int*, int);
void bubble(int*, int);
int main()
{
	
	int a[]={30,25,10,22,11,9,12}; 
	int n=sizeof(a)/sizeof(int); 

	printf("\nThe original array is:-\n");
	display(a, n);

	bubble(a,n);
	printf("\nThe sorted array:\n");
	display(a,n);

	return 0;
}
void display(int* a, int n)
{
	int i;
	for (i = 0; i < n; i++)
		printf("%d\t", *(a + i));
}
void bubble(int* a, int n)
{
	int i, j, temp;
	for (i = 0; i < n - 1; i++)
		for (j = 0; j < n - 1 - i; j++)
			if (*(a + j) > * (a + j + 1))
			{
				temp = *(a + j);
				*(a + j) = *(a + j + 1);
				*(a + j + 1) = temp;
			}
}
