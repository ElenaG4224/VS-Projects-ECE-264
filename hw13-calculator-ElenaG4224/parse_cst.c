#include "cst.h"

#include <stdlib.h>
#include <string.h>


struct CST_node *parse_expr(struct stream *s) 
{
    if(s == NULL)
    {
        return NULL;
    }

    struct CST_node * exprNode = malloc (sizeof(struct CST_node));
    if (exprNode == NULL)
    {
        return NULL;
    }
    exprNode->type = NODE_EXPR;

    struct CST_node * term = parse_term(s);
    struct CST_node * expr_rest = parse_expr_rest(s);

    if (term != NULL && expr_rest != NULL)
    {
        exprNode->expr.term = term;
        exprNode->expr.expr_rest = expr_rest;
        return exprNode;
    }

    free(exprNode);
    free_cst(term);
    free_cst(expr_rest);

    return NULL; 
}

struct CST_node *parse_expr_rest(struct stream *s) 
{ 
    if(s == NULL)
    {
        return NULL;
    }

    struct CST_node * exprRestNode = malloc (sizeof(struct CST_node));
    if (exprRestNode == NULL)
    {
        return NULL;
    }
    exprRestNode->type = NODE_EXPR_REST;

    struct token tokenized = peek(s);
    if (tokenized.type == TOK_ADD)
    {
        next(s);
        if (parse_expr(s) == NULL)
        {
            free(exprRestNode);
            return NULL;
        }
        exprRestNode->expr_rest.op = '+';
        exprRestNode->expr_rest.expr = parse_expr(s);
    
        return exprRestNode; 
    }
    else if (tokenized.type == TOK_EOF)
    {
        exprRestNode->expr_rest.op = '\0';
        exprRestNode->expr_rest.expr = NULL;

        return exprRestNode;

    }

    free(exprRestNode);
    return NULL;
}

struct CST_node *parse_term(struct stream *s) 
{
    if(s == NULL)
    {
        return NULL;
    }

    struct CST_node * termNode = malloc (sizeof(struct CST_node));
    if (termNode == NULL)
    {
        return NULL;
    }
    termNode->type = NODE_TERM;

    struct CST_node * factor = parse_factor(s);
    struct CST_node * term_rest = parse_term_rest(s);

    if (factor != NULL && term_rest != NULL)
    {
        termNode->term.factor = factor;
        termNode->term.term_rest = term_rest;
        return termNode;
    }
    free(termNode);
    free_cst(factor);
    free_cst(term_rest);

    return NULL;  
}

struct CST_node *parse_term_rest(struct stream *s) 
{ 
    if(s == NULL)
    {
        return NULL;
    }

    struct CST_node * termRestNode = malloc (sizeof(struct CST_node));
    if (termRestNode == NULL)
    {
        return NULL;
    }
    termRestNode->type = NODE_TERM_REST;

    struct token tokenized = peek(s);
    if (tokenized.type == TOK_MUL) 
    {
        next(s);
        termRestNode->term_rest.op = '*';
        termRestNode->term_rest.term = parse_term(s);
    
        return termRestNode; 
    }
    else if (tokenized.type == TOK_EOF)
    {
        termRestNode->term_rest.op = '\0';
        termRestNode->term_rest.term = NULL;
    
        return termRestNode; 
    }
    
    free(termRestNode);
    return NULL; 
}

struct CST_node *parse_factor(struct stream *s) 
{ 
    if(s == NULL)
    {
        return NULL;
    }

    struct CST_node * factorNode = malloc (sizeof(struct CST_node));
    if (factorNode == NULL)
    {
        return NULL;
    }
    factorNode->type = NODE_FACTOR;

    struct token tokenized = peek(s);
    if (tokenized.type == TOK_LITERAL)
    {
        tokenized = next(s);
        factorNode->factor.literal = atoi(tokenized.start);
        factorNode->factor.expr = NULL;
        factorNode->factor.negated = false;

        return factorNode;
    }
    else if(tokenized.type == TOK_LPAREN)
    {
        next(s);
        struct CST_node * expr = parse_expr(s);
        if (expr == NULL || tokenized.type != TOK_RPAREN)
        {
            free(factorNode);
            if (expr != NULL)
            {
                free_cst(expr);
            } 
            return NULL;
        }
        next (s);
        factorNode->factor.literal = 0;
        factorNode->factor.expr = expr;
        factorNode->factor.negated = false;

        return factorNode;

    }
    else if(tokenized.type == TOK_NEG)
    {
        free(factorNode);
        tokenized = next(s);
        factorNode = parse_factor(s);
        if (factorNode != NULL)
        {
            factorNode->factor.negated = !factorNode->factor.negated;
            return factorNode;
        }

        return NULL;
    }
    
    free(factorNode);
    return NULL; 
}

void free_cst(struct CST_node *cst) 
{
    if (cst == NULL)
    {
        return;
    }

    enum cst_node_type node = cst->type;

    switch (node)
    {
        case NODE_EXPR: 
            free_cst(cst->expr.term);
            free_cst(cst->expr.expr_rest); 
            break;
        case NODE_EXPR_REST: 
            free_cst(cst->expr_rest.expr);
            break;
        case NODE_TERM:
            free_cst(cst->term.factor);
            free_cst(cst->term.term_rest);
            break;
        case NODE_TERM_REST:
            free_cst(cst->term_rest.term);
            break;
        case NODE_FACTOR:
            free_cst(cst->factor.expr);
            break;
    }

    free(cst);
    return;
}



/*Goal:
Build a calculator that understands parentheses and order of operations.

Files Overview:
1. parse_cst.c – Break Down the Math

parse_expr() → Looks for +

parse_term() → Looks for *

parse_factor() → Looks for numbers, -, or ()

Builds nested nodes (like drawing boxes around parts of the equation)

Example:

Input: (11 + 12) * 3

Recognizes:

Parentheses → (11 + 12)

Addition inside → 11 + 12

Multiplication with 3 */

