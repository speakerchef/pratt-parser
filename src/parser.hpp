#pragma once
#include "lexer.hpp"
#include <cstddef>
#include <cstdlib>
#include <memory>
#include <optional>
#include <tuple>
#include <utility>

enum class BinOp {
    ADD,
    SUB,
    MULT,
    DIV,
};


struct Expression {
    std::string atom;
    std::tuple<BinOp, std::vector<Expression>> operation;
};

struct NodeBinaryExpr {
    std::string atom;
    BinOp op;
    std::unique_ptr<NodeBinaryExpr> lhs;
    std::unique_ptr<NodeBinaryExpr> rhs;

    void print(size_t depth) const;
    std::string op_to_string(BinOp bop) const;
};


inline std::tuple<float, float> get_binding_power(BinOp bop) {
    switch (bop) {
        case BinOp::SUB:
        case BinOp::ADD:  { return {1, 1.1}; }
        case BinOp::DIV:
        case BinOp::MULT: { return {2, 2.1}; }
    }
}

class Parser {
    public:
    Parser(std::vector<Token>&& toks) noexcept : m_tokens(std::move(toks)) {}
    [[nodiscard]] std::unique_ptr<NodeBinaryExpr> parse_expr(float min_rbp);

private:
    std::vector<Token> m_tokens;
    size_t m_tok_ptr = 0;
    inline std::optional<Token> next() {
        if (m_tokens.empty() || m_tok_ptr >= m_tokens.size()) {
            return std::nullopt;
        }
        return m_tokens.at(m_tok_ptr++);
    }
    inline std::optional<Token> peek() const {
        if (m_tokens.empty() || m_tok_ptr >= m_tokens.size()) {
            return std::nullopt;
        }
        return m_tokens.at(m_tok_ptr);
    }
    inline BinOp set_op(const std::string& optype) {
        if (optype == "+") {
            return BinOp::ADD;
        }
        else if (optype == "-") {
            return BinOp::SUB;
        }
        else if (optype == "*") {
            return BinOp::MULT;
        }
        else if (optype == "/") {
            return BinOp::DIV;
        }
        std::println(stderr, "Error: Invalid binary operator.");
        exit(EXIT_FAILURE);
    }
};

