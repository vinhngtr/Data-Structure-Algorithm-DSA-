enum BalanceValue
{
    LH = -1,
    EH = 0,
    RH = 1
};

Node *rotateRight(Node *root){
    Node *p1 = root->pleft;
    Node *p2 = p1->right;
    p1->right = root;
    root->left = p2;
    return p1;
}

Node *rotateLeft(Node *root){
    Node *p1 = root->pright;
    Node *p2 = p1->pleft;
    p1->left = root;
    root->pRight = p2;
    return p1;
}