#include "build.h"
#include "cli/log.h"
#include "cli/cli.h"
#include "parser.h"
#include "parser/lexer.h"
#include "parser/syntax.h"
#include "gen/gen_ir.h"
#include "gen/gen_asm.h"
#include "drawing/simple_tree_drawer.hpp"
#include <iostream>

std::string compile(std::string source)
{
    cli::log(cli::log_level::debug, "Debug messages are now visible");
    cli::log(cli::log_level::warning, "The compiler still doesn't generate the generated assembly code, use the -asm flag.");
    std::vector<token> tokens = lexer::tokenize(source);

    parser p_env;
    p_env.setTokens(tokens);

    tree parseTree;
    auto root = std::make_unique<node>("root");
    parseTree.setRoot(std::move(root));

    syntax::parse(&p_env,&parseTree);

    if(cli::draw_tree()){
       cli::log(cli::log_level::log, "Drawing syntax tree"); 
       simple_tree_drawer("test").draw(parseTree);
    }
    std::vector<ir::operation> intermediate;
    intermediate = gen::make_ir(&parseTree);

    std::string output;
    output = gen::make_asm(intermediate);

    cli::log(cli::log_level::success, "Code analysis succesfull");

    return output;
}

void build()
{

}
