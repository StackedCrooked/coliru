void List::InsertBack(int x)
{
    Node *temp = root;
    Node *nNode = new Node(x);

    if (root == NULL)
        root = nNode;
    else
    {
        while (temp->next)
            temp = temp->next;
        temp->next = nNode;
    }
}

int main()
{
    
}