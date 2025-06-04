/* Hidden stub code will pass a root argument to the function below. Complete the function to solve the challenge. Hint: you may want to write one or more helper functions.

The Node struct is defined as follows:
	struct Node {
		int data;
		Node* left;
		Node* right;
	}
*/
//#include<iostream>
//#include <utility>
//#include <tuple>
//using namespace std;

//std::tuple<bool,int,int> checkBST2(Node* root);

bool checkBST(Node* root) {
     if(!root)
        return true;
    bool t;
    int min,max;
    return checkBST2(root,&min,&max);
    //return t;
}

bool checkBST2(Node* root,int* min,int* max) {

    *min = root->data;
    *max = root->data;
    //printf("%d\n",root->data);
    if(root->left){
        //printf("left\n");
        bool lt;
        int lmin,lmax;
        lt = checkBST2(root->left,&lmin,&lmax);
        if(!lt)
            return false;
        if(lmin>=root->data)
            return false;
        if(lmax>=root->data)
            return false;
        *min = lmin;
    }
    //else
    //    printf("no left\n");

    if(root->right){
        //printf("right\n");
        bool rt;
        int rmin,rmax;
        rt = checkBST2(root->right,&rmin,&rmax);
        //printf("right %d %d %d\n",root->data,rmin,rmax);
        if(!rt)
            return false;
        if(rmin<=root->data)
            return false;
        if(rmax<=root->data)
            return false;
        *max = rmax;
    }
    //else
    //    printf("no right\n");
    return true;
}
