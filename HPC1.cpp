#include <iostream>
#include <omp.h>
#include <stack>
#include <queue>
using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left, *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

void parallel_bfs(TreeNode *root)
{
    queue<TreeNode *> q;
    q.push(root);
    while (!q.empty())
    {
        int qSize = q.size();
        #pragma omp paralle for
        for (int i = 0; i < qSize; i++)
        {
            TreeNode *node;
            #pragma omp critical
            {
                node = q.front();
                q.pop();
                cout << node->val << " ";
            }
            if (node->left)
                q.push(node->left);
            if (node->right)
                q.push(node->right);
        }
    }
}

void parallel_dfs(TreeNode *root)
{
    stack<TreeNode *> s;
    s.push(root);
    while (!s.empty())
    {
        int sSize = s.size();
        #pragma omp paralle for
        for (int i = 0; i < sSize; i++)
        {
            TreeNode *node;
            #pragma omp critical
            {
                node = s.top();
                s.pop();
                cout << node->val << " ";
            }
            if (node->right)
                s.push(node->right);
            if (node->left)
                s.push(node->left);
        }
    }
}

int main()
{
    TreeNode *root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->left = new TreeNode(6);
    root->right->right = new TreeNode(7);

    cout << "\nParallel BFS Traversal: ";
    parallel_bfs(root);
    
    
    cout << "\nParallel DFS Traversal: ";
    parallel_dfs(root);
    return 0;
}