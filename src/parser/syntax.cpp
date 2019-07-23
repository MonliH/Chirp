/*
Phase 3: Syntax analysis parser

This is the actual parser(but I didn't call it that). It reads the tokens generated by the lexer, and generates a parse tree.
This should use a bottom up parsing algorithm, but I'm not sure which.
*/
#include "syntax.h"

#include "../cli/log.h"
#include <iostream>

/*
Test grammar

Statement
Stat -> Decl
Decl -> data_type VarDec

VarDec -> confirm identifier
*/

// I have no idea if this is ok, but this seems to work
namespace syntax
{
    parser* local_env; // *munchii is triggered*
    tree* local_tree;

    bool match(token t)
    {
        if(local_env->getToken().name == t.name)
        {
            local_env->nextToken();
            return true;
        }
        else
        {
            return false;
        }
        
    }

    bool expect(token t)
    {

    }

    // === Handwritten grammar(probably temporary) ===

    void Vardec()
    {
        if(local_env->getToken().name == token_name::confirm)
        {
            if(local_env->lookAhead().name == token_name::identifier)
            {
                std::cout<<"Variable matched"<<std::endl;
            }
        }
    }

    bool Decl()
    {
        if(local_env->getToken().name == token_name::data_type)
        {
            local_env->nextToken();
            Vardec();
            return true;
        }
        else
        {
            return false;
        }
    }

    void Stat()
    {
        if(Decl())
        {
        cli::log(LOG,"Ok, so two nodes should have been added to the tree");

        node* root = local_tree->getRoot();

        node statement("statement");
        node declaration("declaration");

        statement.addChild(&declaration);
        root->addChild(&statement);

        }
        else
        {
            // welp
        }
    }

    void parse(parser* p,tree* t)
    {
        node root("root");
        t->setRoot(&root);

        local_tree = t;
        local_env = p;

        Stat();
    }
}
