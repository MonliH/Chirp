/*
This file isn't the parser by itself, but the custom parser generator. The actual parsing is happening in syntax.cpp
*/
#include "parser.h"
#include "../cli/log.h"

parser::parser() {
    this->tkn_pos = 0;
    this->tokens.reserve(1);
}

void parser::setTokens(const std::vector<token>& newTokens)
{
    for(token t : newTokens)
    {
        this->tokens.push_back(t);
    }

    this->tokens.push_back(token(token_name::end_of_string,""));
}

token parser::getToken()
{
    token t;
    t = this->tokens.at(this->tkn_pos);
    return t;
}

void parser::nextToken()
{
    if(this->tkn_pos + 1 <= this->tokens.size())
    {
        // good
        this->tkn_pos++;
        cli::log(cli::log_level::debug,"Advanced to " + std::to_string(tkn_pos) + ": " +  getToken().value);
    }
    else
    {
        // bad
        cli::log(cli::log_level::warning, "(parsing) Cannot go forward");
    }
}

void parser::backtrack()
{
    if(this->tkn_pos - 1 >= 0)
    {
        this->tkn_pos -= 1;
        cli::log(cli::log_level::debug,"Backtracked to " + std::to_string(tkn_pos) + ": " +  getToken().value);
    }
    else
    {
        cli::log(cli::log_level::debug,"(parser) Cannot backtrack any further");
    }
}

token parser::lookAhead()
{
    token t;

    if(this->tkn_pos + 1 <= this->tokens.size())
    {
        t = this->tokens.at(this->tkn_pos + 1);
    }
    else
    {
        cli::log(cli::log_level::warning, "(parsing) Cannot look ahead");
    }

    return t;
}

token parser::lookBehind()
{
    token t;

    if(this->tkn_pos > 0)
    {
        t = this->tokens.at(this->tkn_pos - 1);
    }
    else
    {
        cli::log(cli::log_level::warning, "(parsing) Cannot look behind");
    }

    return t;
}
