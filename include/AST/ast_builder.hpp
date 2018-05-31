#ifndef BRICK_AST_AST_BUILDER_
#define BRICK_AST_AST_BUILDER_

#include <iostream>
#include <string>

#include "antlr4-runtime.h"
#include "brick.hpp"
#include "MathBaseListener.h"

#include "MathParser.h"
namespace brick::AST
{

class ast_builder : public MathBaseListener {
  private:
    brick::tree::tree2* root_;
    brick::tree::tree2* cur_;
    bool append_node(brick::AST::expression_node*);
  public:
    ast_builder();
    void enterInfixExpr(MathParser::InfixExprContext*) override;
    void enterUnaryExpr(MathParser::UnaryExprContext*) override;
    void enterFuncExpr(MathParser::FuncExprContext*) override;
    void enterNumberExpr(MathParser::NumberExprContext*) override;
    void enterIdExpr(MathParser::IdExprContext*) override;
    brick::tree::tree2* build() const;
    void reset();
};

ast_builder::ast_builder()
  : root_(nullptr), cur_(nullptr)
{}

void ast_builder::enterInfixExpr(MathParser::InfixExprContext* ctx) {
  std::cout << __PRETTY_FUNCTION__ << std::endl;

  brick::AST::expression_node* infix_expr = nullptr;

  if (ctx->OP_ADD()) {
    infix_expr = new brick::AST::addition_node();
  } else if (ctx->OP_SUB()) {
    infix_expr = new brick::AST::subtraction_node();
  } else if (ctx->OP_MUL()) {
    infix_expr = new brick::AST::subtraction_node();
  } else if (ctx->OP_DIV()) {
    infix_expr = new brick::AST::division_node();
  } else {
    // exp
  }

  append_node(infix_expr);
}

void ast_builder::enterUnaryExpr(MathParser::UnaryExprContext* ctx) {
  std::cout << __PRETTY_FUNCTION__ << std::endl;
}

void ast_builder::enterFuncExpr(MathParser::FuncExprContext* ctx) {
  std::cout << __PRETTY_FUNCTION__ << std::endl;
}

void ast_builder::enterNumberExpr(MathParser::NumberExprContext* ctx) {
  std::cout << __PRETTY_FUNCTION__ << std::endl;

  float num = std::stof(ctx->value->getText());
  brick::AST::expression_node* number_expr = new brick::AST::number_node(num);
  append_node(number_expr);
}

void ast_builder::enterIdExpr(MathParser::IdExprContext* ctx) {
  std::cout << __PRETTY_FUNCTION__ << std::endl;
}

brick::tree::tree2* ast_builder::build() const {
  return root_;
}

void ast_builder::reset() {
  root_ = nullptr;
  cur_ = nullptr;
}

bool ast_builder::append_node(brick::AST::expression_node* expr) {
  std::cout << __PRETTY_FUNCTION__ << std::endl;
  if (!root_) {
    root_ = new brick::tree::tree2(expr);
    cur_ = root_;
    return true;
  }

  while (cur_) {
    if (cur_->add_child(expr)) {
      return true;
    }
    cur_ = cur_->get_parent();
  }
  return false;
}

}

#endif