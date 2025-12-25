#pragma once
#include <memory>
struct Node {
	virtual ~Node() = default;
	virtual double evaluate() const = 0;
};

struct NumberNode : public Node {
	double value;
	NumberNode(double val) : value(val) {};
	double evaluate() const override { return value; }
};

struct BinaryOpNode : public Node {
	char op;
	std::unique_ptr<Node> left;
	std::unique_ptr<Node> right;

	BinaryOpNode(char op, std::unique_ptr<Node> l, std::unique_ptr<Node> r)
		: op(op), left(std::move(l)), right(std::move(r)) {}
	double evaluate() const override {
		double l_val = left->evaluate();
		double r_val = right->evaluate();

		switch (op) {
			case '+':
				return l_val + r_val;
			case '-':
				return l_val - r_val;
			case '*':
				return l_val * r_val;
			case '/':
				return l_val / r_val;

			case '%':
				return (int)l_val % (int)r_val;

			default:
				return 0;
		}
	}
};
