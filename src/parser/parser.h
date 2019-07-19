/*
This doesn't do the actual parsing, this is more of a shared structure that multiple parts of the compiler
will share, mostly the syntax analyser and semantic analyser.
*/

#include "tree.h"

#include "token.h"

static struct parser 
{
    tree parseTree;

    // Shouldn't be accessed directly by the syntax analyser
    token tokenCluster;
} parser;