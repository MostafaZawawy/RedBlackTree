#include <iostream>
#include <fstream>
#include <string.h>
#include <math.h>
#include<bits/stdc++.h>
using namespace std;
typedef struct node{
    struct node*left;
    struct node*right;
    struct node*parent;
    char*word;
    bool color;
}node;
node*createNode(char*word){
node*newNode=(node*)malloc(sizeof(node));
newNode->word=(char*)malloc(sizeof(char)*30);
newNode->left=NULL;
newNode->right=NULL;
newNode->parent=NULL;
strcpy(newNode->word,word);
newNode->color=1;

//1 is red
//0 i black
    return newNode ;
}

node*rightRotate(node *&A);
node*leftRotate(node *&A);
void balanceTree(node*&root,node*&node);
node*insertNode(node*&root,node*Node) {
    if (root == NULL) {
        return Node;
    }
    if (strcasecmp(root->word,Node->word) > 0) {
        root->left  =insertNode(root->left, Node);
        root->left->parent=root;

    } else if (strcasecmp(root->word,Node->word) < 0) {
        root->right= insertNode(root->right,Node);
        root->right->parent=root;



    }
return root;
}
node*buildTree(string filepath){
    char a[30];
    ifstream file ;
    file.open(filepath);
    node *root = NULL;

    if(file.is_open())
    {
    while(file.getline(a,30)){
        node*Node=createNode(a);
        root=insertNode(root,Node);
        balanceTree(root,Node);
           }
    }
    else cout<<"Cant open file"<<endl;
    file.close();

return root;
}
void balanceTree(node*&root,node*&Node) {
     node *p =NULL;
     node *uncle=NULL;
     node *grandP=NULL;


    while(Node!=root && Node->parent->color!=0 && Node->color==1){
        p= Node->parent;
        grandP = p->parent;

        if (grandP->right == p)
            uncle = grandP->left;
        else
            uncle = grandP->right;

        if ( uncle!=NULL && uncle->color==1) {
            //uncle is red
            uncle->color = false;
            p->color = false;
            grandP->color = true;
          Node=grandP;
        }

        else if(uncle==NULL || uncle->color==0) {

            //first check for triangle form for parent is right
            if (p == grandP->right) {
                if (Node == p->left) {
                    grandP->right= rightRotate(p);
                    Node=p;


                }
                else if(Node == p->right) {
                    //check line form for parent is right
                    p->color=!p->color;
                    grandP->color=!grandP->color;
                    if(grandP->parent!=NULL) {
                        if (grandP->parent->left == grandP)
                            grandP->parent->left = leftRotate(grandP);
                        else grandP->parent->right = leftRotate(grandP);

                    }
                    else{ root=p;
                        leftRotate(grandP);}

                   }
                }
            else {
                //check for triangle form fot parent is left
                if (Node == p->right) {
                    grandP->left = leftRotate(p);
                    Node=p;

                }
                else {
                    p->color=!p->color;
                    grandP->color=!grandP->color;
                    if(grandP->parent!=NULL)
                    {
                    if(grandP->parent->left==grandP)
                        grandP->parent->left=rightRotate(grandP);
                    else
                        grandP->parent->right=rightRotate(grandP);
                    }
                    else {root=p;
                        rightRotate(grandP);
                    }

                }
            }


        }

    }
    root->color=false;
}

node*search(node*root,node*Node){

    if(root==NULL){
        return root;
    }
    if(strcasecmp(root->word,Node->word)==0 ){
        return  Node;

    }
    else if (strcasecmp(root->word,Node->word)>0){
        return search(root->left,Node);}
    else if (strcasecmp(root->word,Node->word)<0){
        return search(root->right,Node);}

}
node *rightRotate(node *&A) {
    node*B=A->left;
    node*P=A->parent;
    A->left=B->right;
    if(B->right) {
        B->right->parent=A;
    }
    B->right=A;
    A->parent=B;
    B->parent=P;
    if(P) {
        if (A == P->left)
            P->left = B;
        else
            P->right = B;
    }
    return  B;
}
node* leftRotate(node *&A){
    node*B=A->right;
    node*P=A->parent;
    A->right= B->left;
    if(B->left) {

        B->left->parent=A;
    }
    B->left=A;
    A->parent=B;
    B->parent=P;
    if(P) {
        if (A == P->left)
            P->left = B;
        else
            P->right = B;
    }
    return  B;
}
int treeHeight(node*root){

        return (NULL == root) ? -1 : 1 + max(treeHeight(root->right), treeHeight(root->left));

}
int main() {
    char*string;
    node*root;
    node*Node;

    string=(char*)malloc(sizeof(char)*30);
    cout<<"Enter file name:";
    cin>>string;
    cout<<endl;
    root=buildTree(string);
    cout<<"Tree Height is:"<<treeHeight(root)<<endl;

    cout<<"Search of a word:";
     cin >> string;
     cout<<endl;
    Node=createNode(string);
    if(search(root,Node)==NULL)
        printf("NO word not found \n");
    else if( strcasecmp(search(root,Node)->word,Node->word)==0)
      cout<<"YES word found!\n";
    else cout<<"NO word not found\n";
    free(Node);

   cout<<"Insert word:";
   cin>>string;
   Node=createNode(string);
    if(search(root,Node)==NULL){
       root=insertNode(root,Node);
       balanceTree(root,Node);
       printf("Word inserted \n");

    }
    else
        cout<<"ERROr: word is already found!\n";
free(Node);
cout<<"search for inserted word:";
cin >> string;
Node=createNode(string);

    if(search(root,Node)==NULL)
    printf("NO word not found \n");
    else if (strcasecmp(search(root, Node)->word, Node->word) != 0)
        cout << "NO word not found\n";
    else cout << "YES word found!\n";





    return 0;
}
