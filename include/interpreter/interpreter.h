#pragma once
#include <string>
#include "../ast/expr.h"
#include "../ast/stmt.h"

int evaluate(Expr* expr);
void execute(Stmt* stmt);
void defineVariable(const std::string& name, int value);
