/* tree.c */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

static const char *StringFromLabel[] = {
    /* list all other node labels, if any */
    /* The list must coincide with the label_t enum in tree.h */
    /* To avoid listing them twice, see https://stackoverflow.com/a/10966395 */
    FOREACH_LABEL(GENERATE_STRING)
    "Assign",
    "else",
    "if",
    "while",
    "return",
    "&&",
    "||",
    "!"
};

Node *makeNode(label_t label) {
    Node *node = malloc(sizeof(Node));
    if (!node) {
        printf("Run out of memory\n");
        exit(1);
    }
    node->label = label;
    node->name = NULL;
    node-> firstChild = node->nextSibling = NULL;
    node->lineno = 0;
    node->visited = 0;
    node->isnum = 0;
    node->lineno = lineno;
    return node;
}

void addSibling(Node *node, Node *sibling) {
    Node *curr = node;
    while (curr->nextSibling != NULL) {
        curr = curr->nextSibling;
    }
    curr->nextSibling = sibling;
}

void addChild(Node *parent, Node *child) {
    if (parent->firstChild == NULL) {
        parent->firstChild = child;
    }
    else {
        addSibling(parent->firstChild, child);
    }
}

void deleteTree(Node *node) {
    if (node->firstChild) {
        deleteTree(node->firstChild);
    }
    if (node->nextSibling) {
        deleteTree(node->nextSibling);
    }
    if (node->name)
        free(node->name);
    free(node);
}

void searchNode(Node *from, label_t target, Node **res) {
    static int found = 0;
    if (from != NULL && from->label == target){
        *res = from;
        found = 1;
        return;
    }
    for (Node *child = from->firstChild; child != NULL; child = child->nextSibling) {
        searchNode(child, target, res);
        if (found)
            break;
    }
}

void printTree(Node *node) {
    static bool rightmost[128]; // tells if node is rightmost sibling
    static int depth = 0;       // depth of current node
    for (int i = 1; i < depth; i++) { // 2502 = vertical line
        printf(rightmost[i] ? "    " : "\u2502   ");
    }
    if (depth > 0) { // 2514 = L form; 2500 = horizontal line; 251c = vertical line and right horiz 
        printf(rightmost[depth] ? "\u2514\u2500\u2500 " : "\u251c\u2500\u2500 ");
    }   
    if(node->isnum){
        printf("%s : %d", StringFromLabel[node->label], node->val);
    }
    else if (node->name)
        printf("%s : %s", StringFromLabel[node->label], node->name);
    else
        printf("%s", StringFromLabel[node->label]);
    printf("\n");
    depth++;
    for (Node *child = node->firstChild; child != NULL; child = child->nextSibling) {
        rightmost[depth] = (child->nextSibling) ? false : true;
        printTree(child);
    }
    depth--;
}
