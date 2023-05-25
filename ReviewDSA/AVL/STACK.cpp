#include <iostream>
#include <stack>
#include <string>
#include <queue>
using namespace std;

// EX1:
/**
 * ops = "52CD+"

'5' - add to the record. Record now is [5]
'2' - add to the record. Record now is [5,2]
'C' - invalid the previous score (2). Record now is [5]
'D' - Record new score that is double of previous score (5*2). Record now is [5,10]
'+' - Record a new score that is the sum of the previous two scores. Record now is [5,10,15]
*/
int baseballScore(string ops)
{
    int size = ops.length();
    stack<int> ntv;
    int top;
    for (int i = 0; i < size; i++)
    {
        if (ops[i] >= 48 && ops[i] <= 57)
        {
            top = (int)(ops[i] - 48);
            ntv.push(top);
            continue;
        }
        else if (ops[i] == 'C')
        {
            if (!ntv.empty())
            {
                ntv.pop();
            }
            else
            {
                continue;
            }
        }
        else if (ops[i] == 'D')
        {
            if (!ntv.empty())
            {
                top = ntv.top() * 2;
                ntv.push(top);
            }
            else
            {
                continue;
            }
        }
        else if (ops[i] == '+')
        {
            if (ntv.size() >= 2)
            {
                top = ntv.top();
                ntv.pop();
                int newtop = ntv.top() + top;
                ntv.push(top);
                ntv.push(newtop);
                continue;
            }
            else
            {
                continue;
            }
        }
    }
    int res = 0;
    while (!ntv.empty())
    {
        res += ntv.top();
        ntv.pop();
    }
    return res;
}
/**
 * push: this->list.add(0, item)
 * pop: DK: if(!this->list.empty()) return this->list.removeAt(0);
 * Top: 
 */
long long nthNiceNumber(int n) {
    queue<long long> q;
    q.push(2);
    q.push(5);
    n -= 1;
    while(n--){
        long long x = q.front();
        q.pop();
        q.push(x * 10 + 2);
        q.push(x * 10 + 5);
    }
    return q.front();
}
int idx = 0;
while(arr.size() > 1){
    index = (index + k - 1) % arr.size();
    arr.erase(arr.begin() + index);
}
return arr[0];
int maxNode(Node *root){
    int res = root->val;
    if(root->left){
        res = max(res, maxNode(root->left));
    }
    if(root->right){
        res = max(res, maxNode(root->right));
    }
    return res;
}
int getAcentor(BTNode *node){
    if(node == nullptr){
        return 0;
    }else{
        bool flag = true;
        if(node->left && node->val < maxNode(node->left))
            flag = false;
        if()

        return (flag ? 1 : 0) + getAcentor(node->left) + 
    }
}
int main()
{
    string a = "524CD9++";
    cout << baseballScore(a);
}