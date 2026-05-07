#pragma once

#include <cstdint>
#include <bits/stdc++.h>

class Node
{
public:
    std::map<int, uint64_t> BitBoardMap;
    std::vector<Node *> children;
    Node(std::map<int, uint64_t> &Map) { BitBoardMap = Map; }
};

class Tree
{
public:
    Node *root;

    Tree(std::map<int, uint64_t> RootMap)
    {
        root = new Node(RootMap);
    }
    void addChild(Node *parent, std::map<int, uint64_t> ChildMap);
};