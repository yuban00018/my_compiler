//
// Created by Eddie on 2022/5/3.
//

#include "expression_analyzer.h"
#include <iostream>
#include <algorithm>
#include <stack>

Element get_type(const std::string& s) {
    if (s == "ident") return ident;
    if (s == "number") return number;
    if (s == "plus") return plus_;
    if (s == "minus") return minus_;
    if (s == "times") return times;
    if (s == "slash") return slash;
    if (s == "lparen") return lparen;
    if (s == "rparen") return rparen;
    return error;
}

std::string get_error_type(Element e) {
    std::string msg = "Unexpected ";
    switch (e) {
        case ident:
            msg += "ident";
            break;
        case number:
            msg += "number";
            break;
        case plus_:
            msg += "operator \"+\"";
            break;
        case minus_:
            msg += "operator \"-\"";
            break;
        case times:
            msg += "operator \"*\"";
            break;
        case slash:
            msg += "operator \"/\"";
            break;
        case lparen:
            msg += "delimiter \"(\"";
            break;
        case rparen:
            msg += "delimiter \")\"";
            break;
        case null:
            msg += "stop";
            break;
        default:
            msg += "error";
            break;
    }
    return msg;
}

std::vector<Element> next(Element current, Element type) {
    auto t = first.find(current)->second;
    if (t.find(type) == t.end()) {
        std::cout << get_error_type(type);
        return {error};
    }
    std::vector<Element> res = t.find(type)->second;
    std::reverse(res.begin(), res.end());
    return res;
}

bool expression_validator(const std::vector<std::pair<Element, std::string>> &elements) {
    std::stack<Element> s;
    s.push(expr_);
    int counter = 0;
    for (auto &token: elements) {
        ++counter;
        // 如果不是终结符则循环
        while (s.top()>=expr_) {
            auto cur = s.top();
            s.pop();
            auto t = next(cur, token.first);
            if (!t.empty() && t.at(0) == error)return false;
            for (auto &it: t) s.push(it);
        }
        if (s.top() != token.first) {
            std::cout << counter << ':';
            std::cout << get_error_type(token.first) << '\n';
            return false;
        }
        s.pop();
    }
    return true;
}