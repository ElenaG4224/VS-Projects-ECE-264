#include "ast.h"
#include <assert.h>
#include <stdlib.h>

struct AST_node *to_ast(struct CST_node *cst) 
{ 
    if (cst == NULL)
    {
        return NULL;
    } 

    enum cst_node_type currType = cst->type;

    if (currType == NODE_EXPR)
    {
        if (cst->expr.expr_rest == NULL || cst->expr.expr_rest->expr_rest.expr == NULL)
        {
            return to_ast(cst->expr.term);
        }
        else
        {
            struct AST_node * newNode = malloc(sizeof(struct AST_node));
            if (newNode == NULL)
            {
                return NULL;
            }
            newNode->type = NODE_ADD;
            newNode->left = to_ast(cst->expr.term);
            newNode->right = to_ast(cst->expr.expr_rest->expr_rest.expr);
            return newNode;
        }
    }
    else if (currType == NODE_TERM)
    {
        if (cst->term.term_rest == NULL || cst->term.term_rest->term_rest.term == NULL)
        {
            return to_ast(cst->term.factor);
        }
        else
        {
            struct AST_node * newNode = malloc(sizeof(struct AST_node));
            if (newNode == NULL)
            {
                return NULL;
            }
            newNode->type = NODE_MUL;
            newNode->left = to_ast(cst->term.factor);
            newNode->right = to_ast(cst->term.term_rest->term_rest.term);
            return newNode;

        }
    }
    else if (currType == NODE_FACTOR)
    {
        struct AST_node * newNode = malloc(sizeof(struct AST_node));
        if (newNode == NULL)
        {
            return NULL;
        }

        if (cst->factor.expr == NULL)
        {
            newNode->type = NODE_LITERAL;
            newNode->literal = cst->factor.literal;
        }
        else //()
        {
            free(newNode);
            newNode = to_ast(cst->factor.expr);
        }

        if (cst->factor.negated == true)
        {
            struct AST_node * negNode = malloc(sizeof(struct AST_node));
            negNode->type = NODE_NEG;
            negNode->left = newNode;
            negNode->right = NULL;

            return negNode;
        }

        return newNode;
        
    }

    return NULL;
}

void free_ast(struct AST_node *ast) 
{
    if (ast == NULL)
    {
        return;
    }
    free_ast(ast->left);
    free_ast(ast->right);
    free(ast);

    return;
}

int interpret(struct AST_node *ast) //post-order
{ 
    if (ast ==  NULL)
    {
        return 0; //-1 OG ?
    }

    if (ast->type == NODE_ADD)
    {
        return interpret(ast->left) + interpret(ast->right);
    }
    else if (ast->type == NODE_MUL)
    {
        return interpret(ast->left) * interpret(ast->right);
    }
    else if (ast->type == NODE_NEG)
    {
        return interpret(ast->left) * -1;
    }
    else if (ast->type == NODE_LITERAL)
    {
        return ast->literal;
    }

    return 0;

}

/*
2. ast.c – Clean Up and Calculate

to_ast() → Converts messy parse boxes into a clean tree
(e.g. turn [(11 + 12) * 3] into * newNode with children +, 3)

interpret() → Walks the tree and computes the result

If newNode is + → add left and right

If newNode is * → multiply left and right

If newNode is number → return it

Workflow in Simple Terms:
parse_cst.c → Label all math parts

to_ast() → Build a clean diagram (tree)

interpret() → Solve the math using the tree
Analogy:
First person: Circles parts of the math sentence

Second person: Makes a neat diagram

Third person: Does the math*/