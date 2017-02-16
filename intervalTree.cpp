#include<bits/stdc++.h>
using namespace std;
struct node{
int low,high,maxxie;
node *left;
node *right;
};

node* Insert(node *root,int l,int h)
{
    if(root==NULL)
    {
        node* temp = new node();
    temp->low = l;
    temp->high = h;
    temp->maxxie = h;
    temp->left = NULL;
    temp->right = NULL;

        root = temp;
    }
    else if(l > root->low )
    {
        root->maxxie = max(root->high,h);
        root->right = Insert(root->right,l,h);
    }
    else
    {
        root->maxxie = max(root->high,h);
        root->left = Insert(root->left,l,h);
    }
    return root;

}

node* Search(node *root,int l,int h)
{
    if (root == NULL)
            return NULL;
        if (root->low<=h && root->high>=l)
            return root;
        if (root->left != NULL && (root->left)->maxxie >= l)
            return Search(root->left, l, h);
        return Search(root->right, l, h);

}
void change(node* node1, node* node2){
	node1->low=node2->low;
	node1->high=node2->high;
}
void remove(node* current,node* root, node* parent, bool head){
	//head=true here indicates it is the root node
	int child=0;
	bool left=false, right=false;
	if(current->low <= parent->low) left=true;
	else right=true;

	if(current->left) child++;
	if(current->right) child++;

	if(child==0){
		if(head){
			parent=NULL;
			return;
		}
		if(left) parent->left=NULL;
		else parent->right=NULL;
	}
	else if(child==1){
		if(head){
			if(current->left) root=root->left;
			else root=root->right;
			return;
		}
		if(left){
			if(current->right) parent->left=current->right;
			else parent->left=current->left;
		}
		else{
			if(current->right) parent->right=current->right;
			else parent->right=current->left;
		}
	}
	else{
		node* temp=current;
		temp=temp->left;
		if(temp->right){
			while(temp->right){
				parent=temp;
				temp=temp->right;
			}
			change(current, temp);
			parent->right=NULL;
		}
		else{
			change(current, temp);
			remove(temp, root,current, false);
		}
	}
}
node* deletenode(node* root,node* temp_node)
{
    node* current=new node();
    current = root;
	node *parent= new node();
	parent = root;
	//eleminate the case when we have to delete the root node itself
	//take care of that later
	while(true){
		if(current==NULL){
			cout<<"The requested interval to delete does not exist"<<endl;
			break;
		}
		if(temp_node->low < current->low){
			parent=current; current=current->left;
		}
		else if(temp_node->low > current->low){
			parent=current; current=current->right;
		}
		else{
			remove(current,root, parent, false);
			break;
		}
	}
}

int main()
{
 node *root = NULL;
 cout<<"Enter how many intervals to insert"<<endl;
 int n,l,h;
 cin>>n;
 for(int i=1;i<=n;i++)
 {

     cin>>l>>h;
     root = Insert(root,l,h);
 }
 cout<<root->low<<endl;
 cout<<"Enter number of search queries"<<endl;
 cin>>n;
 for(int i=1;i<=n;i++)
 {
     cin>>l>>h;
     node *temp = new node();
     temp = Search(root,l,h);
     if(temp)
     {
         cout<<"There is Overlap and the Overlap Interval is : "<<temp->low<<" "<<temp->high<<endl;
     }
     else
        cout<<"Overlapping Interval not found"<<endl;
 }
 cout<<"Enter number of nodes to delete"<<endl;
 cin>>n;
 for(int i=1;i<=n;i++)
 {

    cin>>l>>h;
     node *temp = new node();
     node* temp = new node();
    temp->low = l;
    temp->high = h;
    temp->maxxie = h;
    temp->left = NULL;
    temp->right = NULL;

     deletenode(root,temp);
     cout<<"The given interval is deleted"<<endl;
 }
 return 0;
}
