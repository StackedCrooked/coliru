#include <string>
#include <iostream>
#include "BTNode.h"
#include "board.h"
using namespace std;
template<class T> class BTree
{
    BTree(board startboard, T startplayer)
	{
		treeboard = startboard;
		player = startplayer;
		root = new BTNode(treeboard, player,-1,-1);
	}
	
	~BTree()
	{
		delete root;
	}
	int sumtree()
	{
		if (root->getvalue(-1) > root->getvalue(1))
			return root->getchildposition(-1);
		else
			return root->getchildposition(1);
	}

	T player;
	board treeboard;
	BTNode *root;
};