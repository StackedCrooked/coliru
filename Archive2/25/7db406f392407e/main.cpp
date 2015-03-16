    void sort_list(node*& header)
    {
        node *newList = 0;
        node *curSourceHead = header;

        //while items are still in the list continue to sort, why doesn't this work?
        while (list_length(curSourceHead) > 0 )
        {
            node::value_type theData = curSourceHead->data();
            newList = list_add_sorted(newList, theData);  //
            list_head_remove(curSourceHead);
        }
        header = newList;
    }
