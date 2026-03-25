#include "parser.hpp"
#include "lexer.hpp"
#include <cstddef>
#include <memory>

std::unique_ptr<NodeBinaryExpr> Parser::parse_expr(float min_rbp) {
    BinOp op;
    auto lhs = std::make_unique<NodeBinaryExpr>();
    lhs->atom = next().value().value;

    while (peek().has_value() && peek().value().type == TokenType::BIN_OP) {
        op = set_op(peek().value().value);

        auto [lbp, rbp] = get_binding_power(op);

        if (lbp < min_rbp) {
            break;
        }
        next();

        auto rhs = parse_expr(rbp);
        auto node = std::make_unique<NodeBinaryExpr>();
        node->op = op;
        node->lhs = std::move(lhs);
        node->rhs = std::move(rhs);

        lhs = std::move(node);
    }
    return lhs;
}

std::string NodeBinaryExpr::op_to_string(BinOp bop) const {
    switch (bop) {
        case BinOp::ADD: return "+"; 
        case BinOp::SUB: return "-"; 
        case BinOp::MULT: return "*"; 
        case BinOp::DIV: return "/"; 
    }
}

void NodeBinaryExpr::print(size_t depth) const {
      std::string indent(2, ' ');
    if (!lhs && !rhs) {
        std::print("{}{}", indent, atom);
        return;
    }
    std::print("{}({}", indent, op_to_string(op));
    if (lhs) lhs->print(depth + 1);
    if (rhs) rhs->print(depth + 1);
    std::print("{})", indent); 
}

