#include<iostream>
#include<omp.h>
#include<climits>

using namespace std;

void min_reduction(int arr[],int n){
	int min=INT_MAX;
	#pragma omp parallel for reduction(min:min)
	for(int i=0;i<n;i++){
		if(arr[i]<min)
			min=arr[i];	
	}
	cout<<"\nMinimun value :: "<<min;
}

void max_reduction(int arr[],int n){
	int max=INT_MIN;
	#pragma omp parallel for reduction(max:max)
	for(int i=0;i<n;i++){
		if(arr[i]>max)
			max=arr[i];
	}
	cout<<"\nMaximum value :: "<<max;
}

void sum_avg_reduction(int arr[],int n){
	int sum=0;
	#pragma omp parallel for reduction(+:sum)
	for(int i=0;i<n;i++)
		sum+=arr[i];
	cout<<"\nSum ::" <<sum;
	cout<<"\nAverage :: "<<((double)sum/n); 
}

int main(){
	int arr[]={1,2,3,4,5};
	int n=sizeof(arr)/sizeof(arr[0]);
	min_reduction(arr,n);
	max_reduction(arr,n);
	sum_avg_reduction(arr,n);
	return 0;
	
}
