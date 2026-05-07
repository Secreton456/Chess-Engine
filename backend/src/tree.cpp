#include <cstdint>
#include <bitset>
#include <bits/stdc++.h>
#include <../include/board.hpp>
#include <../include/tree.hpp>
typedef uint64_t U64;

void Tree::addChild(Node *parent, std::map<int, uint64_t> ChildMap)
{
    parent->children.push_back(new Node(ChildMap));
}
