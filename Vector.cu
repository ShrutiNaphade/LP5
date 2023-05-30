#include<stdio.h>
#include<iostream>

using namespace std;

__global__ void VectorAdd(int* a,int* b,int* c,int size){
	int tid=blockIdx.x*blockDim.x+threadIdx.x;
	if(tid<size){
		c[tid]=a[tid]+b[tid];
	}
}

int main(){
	
	int size=500;
	int numbytes=size*sizeof(int);
	
	int* h_a=(int*)malloc(numbytes);
	int* h_b=(int*)malloc(numbytes);
	int* h_c=(int*)malloc(numbytes);
	
	for(int i=0;i<size;i++){
		h_a[i]=i;
		h_b[i]=size-i;
	}
	
	int* d_a;
	int* d_b;
	int* d_c;
	cudaMalloc((void**)&d_a,numbytes);
	cudaMalloc((void**)&d_b,numbytes);
	cudaMalloc((void**)&d_c,numbytes);
	
	cudaMemcpy(d_a,h_a,numbytes,cudaMemcpyHostToDevice);
	cudaMemcpy(d_b,h_b,numbytes,cudaMemcpyHostToDevice);
	
	int blocksize=256;
	int gridsize=(size+blocksize-1)/blocksize;
	
	VectorAdd<<<gridsize,blocksize>>>(d_a,d_b,d_c,size);
	
	cudaMemcpy(h_c,d_c,numbytes,cudaMemcpyDeviceToHost);
	
	for(int i=0;i<size;i++){
		cout<<"\n"<<h_a[i]<<"+"<<h_b[i]<<"="<<h_c[i];
	}
	
	cudaFree(d_a);
	cudaFree(d_b);
	cudaFree(d_c);
	
	free(h_a);
	free(h_b);
	free(h_c);
	
	
	return 0;
}
