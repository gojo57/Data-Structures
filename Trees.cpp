#include<bits/stdc++.h>
#define ll long long
using namespace std;

template <typename T>
class TreeNode{
    public:
    T data;
    vector <TreeNode<T>*> children;
    TreeNode(T data){
        this->data = data;
    }
    ~TreeNode(){
        for(int i = 0; i<root->children.size(); i++){
            delete children[i];
        }
    }
};

void printTree(TreeNode<int>* root){
    if(root==NULL) return;  //edge case
    cout<<root->data<<": ";
    for(int i = 0; i<root->children.size(); i++){
        cout<<root->children[i]->data<<", ";
    }
    cout<<endl;
    for(int i = 0; i<root->children.size(); i++){
        printTree(root->children[i]);
    }
}

void printTreeLevelWise(TreeNode<int>* root){
    queue<TreeNode<int>*> q;
    q.push(root);
    while(!q.empty()){
        TreeNode<int>* f = q.front();
        q.pop();
        cout<<f->data<<": ";
        for(int i = 0; i<f->children.size(); i++){
            cout<<f->children[i]->data<<", ";
        }
        cout<<endl;

        for(int i = 0; i<f->children.size(); i++){
            q.push(f->children[i]);
        }
    }
}

TreeNode<int>* takeInput(){ //recursive method
    int rootData;
    cout<<"Enter data"<<endl;
    cin>>rootData;
    TreeNode<int>* root = new TreeNode<int>(rootData);
    // how many children
    int n; 
    cout<<"Enter the children of "<<rootData<<endl;
    cin>>n;

    for(int i = 0; i<n; i++){
        TreeNode<int>* child = takeInput();
        root->children.push_back(child);
    }
    return root;
}

TreeNode<int>* takeInputLevelWise(){
    int rootData;
    cout<<"Enter root data"<<endl;
    cin>>rootData;
    TreeNode<int>* root = new TreeNode<int>(rootData);
    queue<TreeNode<int>*> q;
    q.push(root);
    while(!q.empty()){
        TreeNode<int>* f = q.front();
        q.pop();
        cout<<"Enter number of children of "<<f->data<<endl;
        int n; cin>>n;
        for(int i = 0; i<n; i++){
            int childData;
            cout<<"Enter "<<i<<" th child of "<<f->data<<endl;
            cin>>childData;
            TreeNode<int>* child = new TreeNode<int>(childData);
            q.push(child);
            f->children.push_back(child);
        }
    }
    return root;
}

int countNodes(TreeNode<int>* root){
    if(root==NULL) return 0;
    int ans = 1;
    for(int i = 0; i<root->children.size(); i++){
        ans+=countNodes(root->children[i]);
    }
    return ans;
}

int height(TreeNode<int>* root){
    if(root==NULL) return 0;
    int mx = 0;
    for(int i = 0; i<root->children.size(); i++){
        // int childHeight = height(root->children[i]);
        // if(childHeight>mx) mx = childHeight;
        mx = max(mx, height(root->children[i]));
    }
    return mx+1;
}

void printAtLevelK(TreeNode<int>* root, int k){
    if(root==NULL) return;
    if(k==0) {cout<<root->data<<" "; return;}
    for(int i = 0; i<root->children.size(); i++){
        printAtLevelK(root->children[i], k-1);
    }
}

void printAtLevelKOtherWay(TreeNode<int>* root, int k, int c=0){
    if(root==NULL) return;
    if(k==c) {cout<<root->data<<" "; return;}
    for(int i = 0; i<root->children.size(); i++){
        printAtLevelKOtherWay(root->children[i], k, c+1);
    }
}

int countLeafNodes(TreeNode<int>* root){
    if(root==NULL) return 0;
    if(root->children.size()==0) return 1;
    int ans = 0;
    for(int i = 0; i<root->children.size(); i++){
        ans+=countLeafNodes(root->children[i]);
    }
    return ans;
}

void countLeafNodesOtherWay(TreeNode<int>* root, int &ans){
    if(root->children.size()==0) {ans++; return;}
    for(int i = 0; i<root->children.size(); i++){
        countLeafNodesOtherWay(root->children[i], ans);
    }
}

void preOrderTraversal(TreeNode<int>* root){
    if(root==NULL) return;
    cout<<root->data<<" ";
    for(int i = 0; i<root->children.size(); i++){
        preOrderTraversal(root->children[i]);
    }
}

void postOrderTraversal(TreeNode<int>* root){
    if(root==NULL) return;
    for(int i = 0; i<root->children.size(); i++){
        postOrderTraversal(root->children[i]);
    }
    cout<<root->data<<" ";
}

void deleteTree(TreeNode<int>* root){ //used post order traversal
    if(root==NULL) return;
    for(int i = 0; i<root->children.size(); i++){
        deleteTree(root->children[i]);
    }
    delete root;
}

// 1 3 2 3 4 2 5 6 2 7 8 0 0 0 0 1 9 0
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TreeNode<int>* root = new TreeNode<int>(1);    
    // TreeNode<int>* n1 = new TreeNode<int>(2);    
    // TreeNode<int>* n2 = new TreeNode<int>(3);

    // root->children.push_back(n1);
    // root->children.push_back(n2);

    // TreeNode<int>* root = takeInput();
    TreeNode<int>* root = takeInputLevelWise();
    // printTree(root);
    printTreeLevelWise(root);
    cout<<"Total nodes "<< countNodes(root)<<endl;
    cout<<"Height "<< height(root)<<endl;
    cout<<"Nodes at level 2"<<endl;
    printAtLevelK(root,2);
    printAtLevelKOtherWay(root,2);
    cout<<endl;
    cout<<"No of leaf nodes: "<<countLeafNodes(root)<<endl;
    int totalLeafNodes = 0;
    countLeafNodesOtherWay(root, totalLeafNodes);
    cout<<"No of leaf nodes: "<<totalLeafNodes<<endl;

    cout<<"Pre order traversal: ";
    preOrderTraversal(root);
    cout<<endl;
    cout<<"Post order traversal: ";
    postOrderTraversal(root);

    // deleteTree(root);
    delete(root);

    // cout<<<<<<endl;
    // printAtLevelK(root, 2);
    // cout<<<<height(root)<<<<endl;
    // cout<<<<countNodes(root)<<<<endl;
    return 0;
}