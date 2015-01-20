
static void
ipmc_bier_remove_encap_leaf_from_list( ipv4mc_bier_st *bier_node,
                                       ipv4mc_encap_leaf_st *encap_leaf)
{
    ipv4mc_bier_encap_leaf_node *tmp, *prev;

    /* Point to head of list */
    tmp = bier_node->encap_leaf_list;
    if (tmp != NULL) {
        while(tmp != NULL) {
            if (tmp->encap_leaf == encap_leaf) {
                if (bier_node->encap_leaf_list == tmp) {
                    bier_node->encap_leaf_list = tmp->next;
                    free(tmp);
                } else {
                    prev->next = tmp->next;
                    free(tmp);
                }
            } else {
                prev = tmp;
                tmp = tmp->next;
            }
        }
    }
}