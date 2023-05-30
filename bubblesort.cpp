#include<iostream>
#include<omp.h>

using namespace std;

void parallel_bubble_sort(int arr[],int n){
	#pragma opm parallel
	{
		int i,temp,flag=1;
		while(flag){
			flag=0;
			#pragma omp parallel for
			for(i=0;i<n-1;i++){
				if(arr[i]>arr[i+1])
				{
					temp=arr[i];
					arr[i]=arr[i+1];
					arr[i+1]=temp;
					flag=1;
				}
			
			}
		}
	}

}

void bubble_sort(int arr[],int n){
	{
		int i,temp,flag=1;
		while(flag){
			flag=0;
			for(i=0;i<n-1;i++){
				if(arr[i]>arr[i+1])
				{
					temp=arr[i];
					arr[i]=arr[i+1];
					arr[i+1]=temp;
					flag=1;
				}
			
			}
		}
	}

}

int main()
{
	int arr[]={1,5,6,4,3,2,7};
	int n=sizeof(arr)/sizeof(arr[0]);
	for(int i=0;i<n;i++){
		cout<<arr[i]<<" ";
	}
	
	double start=omp_get_wtime();
	bubble_sort(arr,n);
	double end=omp_get_wtime();
	cout<<"\nAfter Sorting\n";
	for(int i=0;i<n;i++){
		cout<<arr[i]<<" ";
	}
	cout<<"\nTime taken :: "<<(end-start);
	
	return 0;
}
