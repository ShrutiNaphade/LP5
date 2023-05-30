#include<bits/stdc++.h>
using namespace std;

struct Treenode{
	int val;
	Treenode* left;
	Treenode* right;
	Treenode(int x):val(x),left(NULL),right(NULL){}
};

void bfs(Treenode* root){
	queue<Treenode*> q;
	q.push(root);
	while(!q.empty()){
		Treenode* node=q.front();
		q.pop();
		cout<<node->val<<" ";
		if(node->left)
			q.push(node->left);
		if(node->right)
			q.push(node->right);
	}
}

void parallel_bfs(Treenode * root){
	queue<Treenode*> q;
	q.push(root);
	while(!q.empty()){
		int qsize=q.size();
		#pragma omp parallel for
		for(int i=0;i<qsize;i++){
			Treenode* node;
			#pragma omp critical
			{
				node=q.front();
				q.pop();
				cout<<node->val<<" ";
			}
			if(node->left)
				q.push(node->left);
			if(node->right)
				q.push(node->right);
		}
	}
}

int main()
{
	Treenode* root=new Treenode(1);
	root->left=new Treenode(2);
	root->right=new Treenode(3);
	root->left->left=new Treenode(4);
	root->left->right=new Treenode(5);
	root->right->left=new Treenode(6);
	root->right->right=new Treenode(7);
	
	auto start=chrono::high_resolution_clock::now();
	bfs(root);
	auto end=chrono::high_resolution_clock::now();
	cout<<"Sequential bfs takes "<<chrono::duration_cast<chrono::microseconds>(end-start).count();
	
	auto start1=chrono::high_resolution_clock::now();
	parallel_bfs(root);
	auto end1=chrono::high_resolution_clock::now();
	cout<<"Parallel bfs takes "<<chrono::duration_cast<chrono::microseconds>(end1-start1).count();
	return 0;
}
