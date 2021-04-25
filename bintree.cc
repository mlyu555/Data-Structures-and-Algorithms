#include <vector>
using namespace std;

struct TreeNode {
    int value;
    TreeNode *left;
    TreeNode *right;
};


// 增删查改+创建销毁

int CreateTree(TreeNode *root, vector<int> &elems);
int AddElem(TreeNode *root, int e);
int DelElem(TreeNode *root, int e);
int DestoryTree(TreeNode *root);
int SearchElem(TreeNode *root, int e);
