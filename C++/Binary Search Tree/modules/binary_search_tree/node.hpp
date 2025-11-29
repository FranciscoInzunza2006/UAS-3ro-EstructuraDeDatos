//
// Created by Franc on 29/11/2025.
//

#pragma once

class Node
{
public:
    int key{};
    Node* left = nullptr;
    Node* right = nullptr;

    explicit Node(const int key) : key(key) {}
    Node(const int key, Node* left, Node* right) : key(key), left(left), right(right){}
};
