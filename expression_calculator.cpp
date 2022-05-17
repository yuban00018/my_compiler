//
// Created by Fish on 2022/5/17.
//

#include "expression_calculator.h"

const std::vector<std::pair<Element, std::vector<Element>>>
ExpressionCalculator::production = {    // 文法：产生式
        {null, {Expr}},
        {Expr, {Expr, Plus, Term}},
        {Expr, {Plus, Term}},
        {Expr, {Term}},
        {Term, {Term, Multi, Factor}},
        {Term, {Factor}},
        {Factor, {lparen, Expr, rparen}},
        {Factor, {ident}},
        {Factor, {number}},
        {Plus, {plus_}},
        {Plus, {minus_}},
        {Multi, {times}},
        {Multi, {slash}}};

const std::vector<std::map<Element, std::pair<Action, int>>> ExpressionCalculator::f = { //LR(0)分析表
        // 0
        {
                {lparen, {Shift, 1}},
                {plus_, {Shift, 2}},
                {minus_, {Shift, 3}},
                {ident, {Shift, 8}},
                {number, {Shift, 9}},
                {Expr, {Goto, 4}},
                {Term, {Goto, 7}},
                {Factor, {Goto, 5}},
                {Plus, {Goto, 6}}},
        // 1
        {
                {lparen, {Shift, 1}},
                {plus_, {Shift, 2}},
                {minus_, {Shift, 3}},
                {ident, {Shift, 8}},
                {number, {Shift, 9}},
                {Expr, {Goto, 10}},
                {Term, {Goto, 7}},
                {Factor, {Goto, 5}},
                {Plus, {Goto, 6}}},
        // 2
        {
                {lparen, {Reduce, 9}},
                {ident, {Reduce, 9}},
                {number, {Reduce, 9}},
        },
        // 3
        {
                {lparen, {Reduce, 10}},
                {number, {Reduce, 10}},
                {ident, {Reduce, 10}}},
        // 4
        {
                {plus_, {Shift, 2}},
                {minus_, {Shift, 3}},
                {null, {Accept, 0}},
                {Plus, {Goto, 11}}},
        // 5
        {
                {rparen, {Reduce, 5}},
                {plus_, {Reduce, 5}},
                {minus_, {Reduce, 5}},
                {times, {Reduce, 5}},
                {slash, {Reduce, 5}},
                {null, {Reduce, 5}}},
        // 6
        {
                {lparen, {Shift, 1}},
                {ident, {Shift, 8}},
                {number, {Shift, 9}},
                {Term, {Goto, 12}},
                {Factor, {Goto, 5}}},
        // 7
        {
                {rparen, {Reduce, 3}},
                {plus_, {Reduce, 3}},
                {minus_, {Reduce, 3}},
                {times, {Shift, 13}},
                {slash, {Shift, 14}},
                {null, {Reduce, 3}},
                {Multi, {Goto, 15}}},
        // 8
        {
                {rparen, {Reduce, 7}},
                {plus_, {Reduce, 7}},
                {minus_, {Reduce, 7}},
                {times, {Reduce, 7}},
                {slash, {Reduce, 7}},
                {null, {Reduce, 7}}},
        // 9
        {
                {rparen, {Reduce, 8}},
                {plus_, {Reduce, 8}},
                {minus_, {Reduce, 8}},
                {times, {Reduce, 8}},
                {slash, {Reduce, 8}},
                {null, {Reduce, 8}}},
        // 10
        {
                {rparen, {Shift, 16}},
                {plus_, {Shift, 2}},
                {minus_, {Shift, 3}},
                {Plus, {Goto, 11}}},
        // 11
        {
                {lparen, {Shift, 1}},
                {ident, {Shift, 8}},
                {number, {Shift, 9}},
                {Term, {Goto, 17}},
                {Factor, {Goto, 5}}},
        // 12
        {
                {rparen, {Reduce, 2}},
                {plus_, {Reduce, 2}},
                {minus_, {Reduce, 2}},
                {times, {Shift, 13}},
                {slash, {Shift, 14}},
                {null, {Reduce, 2}},
                {Multi, {Goto, 15}}},
        // 13
        {
                {lparen, {Reduce, 11}},
                {ident, {Reduce, 11}},
                {number, {Reduce, 11}},
        },
        // 14
        {
                {lparen, {Reduce, 12}},
                {ident, {Reduce, 12}},
                {number, {Reduce, 12}}},
        // 15
        {
                {lparen, {Shift, 1}},
                {ident, {Shift, 8}},
                {number, {Shift, 9}},
                {Factor, {Goto, 18}}},
        // 16
        {
                {rparen, {Reduce, 6}},
                {plus_, {Reduce, 6}},
                {minus_, {Reduce, 6}},
                {times, {Reduce, 6}},
                {slash, {Reduce, 6}},
                {null, {Reduce, 6}}},
        // 17
        {
                {rparen, {Reduce, 1}},
                {plus_, {Reduce, 1}},
                {minus_, {Reduce, 1}},
                {times, {Shift, 13}},
                {slash, {Shift, 14}},
                {null, {Reduce, 1}},
                {Multi, {Goto, 15}}},
        // 18
        {
                {rparen, {Reduce, 4}},
                {plus_, {Reduce, 4}},
                {minus_, {Reduce, 4}},
                {times, {Reduce, 4}},
                {slash, {Reduce, 4}},
                {null, {Reduce, 4}}}};

Element getElement(const std::string& s)
{
    if (s == "number") return number;
    if (s == "ident") return ident;
    if (s == "plus") return plus_;
    if (s == "minus") return minus_;
    if (s == "times") return times;
    if (s == "slash") return slash;
    if (s == "lparen") return lparen;
    if (s == "rparen") return rparen;
    throw NoSuchElementException();
}
std::ostream& operator<<(std::ostream& out, const Element& obj)
{
    switch (obj)
    {
        case plus_:
            out << "+";
            break;
        case minus_:
            out << "-";
            break;
        case times:
            out << "*";
            break;
        case slash:
            out << "/";
            break;
        default:
            break;
    }
}
std::ostream& operator<<(std::ostream& out, const Action& act)
{
    switch (act)
    {
        case Accept:
            out << "Accept";
            break;
        case Shift:
            out << "Shift";
            break;
        case Reduce:
            out << "Reduce";
            break;
        case Goto:
            out << "Goto";
            break;
        default:
            break;
    }
    return out;
}
void __printitem(const std::pair<TResult, std::string>& item)
{
    if (item.second == "")
        std::cout << item.first;
    else
        std::cout << item.second;
}

ExpressionException::ExpressionException(Element obj) { msg = (getErrorMessage(obj)); }

std::string ExpressionException::getErrorMessage(Element obj)
{
    std::string msg = "Unexpect ";
    switch (obj)
    {
        case number:
            msg += "number";
            break;
        case ident:
            msg += "ident";
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
            msg += "EOF";
            break;
        default:
            msg = "Unknown Error";
            break;
    }
    msg.push_back('.');
    return msg;
}

std::pair<Action, int> ExpressionCalculator::getNext(int current, Element type)
{   // 通过栈顶数据和读入字符，根据LR(0)分析表，判断下一步Action
    auto it = f[current].find(type);
    if (it == f[current].end()) throw ExpressionException(type);
    return it->second;
}

std::pair<Element, std::vector<Element>> ExpressionCalculator::getReduce(int id)
{   // 生成递归过程依据的文法
    return production[id];
}

TResult ExpressionCalculator::getLexval(Element obj, std::string token)
{
    if (obj == number) return std::stoi(token);
    if (obj < number) return static_cast<TResult>(obj);
    return 0;
}

TResult ExpressionCalculator::calc(TResult lhs, TResult op, TResult rhs)
{
    if (op == plus_) return lhs + rhs;
    if (op == minus_) return lhs - rhs;
    if (op == times) return lhs * rhs;
    if (op == slash) return rhs ? lhs / rhs : 0;
    // :(
    std::cout << lhs << op<< rhs << std::endl;
    assert(false);
}

TResult ExpressionCalculator::calc(TResult op, TResult rhs)
{
    if (op == plus_) return +rhs;
    if (op == minus_) return -rhs;
    // :(
    assert(false);
}

void ExpressionCalculator::print(Element op,
                                 std::pair<TResult, std::string> lhs,
                                 std::pair<TResult, std::string> rhs,
                                 std::pair<TResult, std::string> res)
{
    std::cout << '(' << op << ',';
    __printitem(lhs);
    std::cout << ',';
    __printitem(rhs);
    std::cout << ',';
    __printitem(res);
    std::cout << ')' << std::endl;
}

void ExpressionCalculator::print(Element op,
                                 std::pair<TResult, std::string> rhs,
                                 std::pair<TResult, std::string> res)
{
    std::cout << '(' << op << ',';
    std::cout << ' ' << ',';
    __printitem(rhs);
    std::cout << ',';
    __printitem(res);
    std::cout << ')' << std::endl;
}

TResult ExpressionCalculator::calculate(const std::vector<std::pair<Element, std::string>>& elements) const
{
    // state, token, result, id
    int counter = 0;
    std::stack<std::tuple<int, Element, std::pair<TResult, std::string>>> s;    // 状态，符号，数值，id 栈
    s.push(std::make_tuple(0, null, std::make_pair(0, "")));
    for (auto&& [element, token] : elements)
    {
        for (;;)
        {
            auto action = getNext(std::get<0>(s.top()), element);
            // 根据获取的Action类型，进行下一步分析。
            if (action.first == Shift)
            {   // 移进
                s.push(std::make_tuple(action.second, element,
                                       std::make_pair(getLexval(element, token), token)));
                break;
            }
            else if (action.first == Reduce)
            {
                auto it = getReduce(action.second);
                auto reduce = it.second;
                std::reverse(reduce.begin(), reduce.end());
                static std::pair<TResult, std::string> buffer[3];
                static int sz;
                sz = 0;
                for (auto&& r : reduce)
                {
                    assert(r == std::get<1>(s.top()));
                    buffer[sz++] = std::get<2>(s.top());
                    s.pop();
                }
                std::pair<TResult, std::string> res;
                if (sz == 1)
                    res = buffer[0];
                else if (sz == 2)
                {
                    res = std::make_pair(calc(buffer[1].first, buffer[0].first), "t" + std::to_string(++counter));
                    print(static_cast<Element>(buffer[1].first), buffer[0], res);
                }
                else if (sz == 3)
                {
                    if (buffer[2].second == "(" && buffer[0].second == ")")
                        res = buffer[1];
                    else
                    {
                        res = std::make_pair(calc(buffer[2].first, buffer[1].first, buffer[0].first), "t" + std::to_string(++counter));
                        print(static_cast<Element>(buffer[1].first), buffer[2], buffer[0], res);
                    }
                }
                else //:(
                    assert(false);
                auto go = getNext(std::get<0>(s.top()), it.first);
                assert(go.first == Goto);
                // std::cerr << go.first << ' ' << go.second << std::endl;
                s.push(std::make_tuple(go.second, it.first, res));
            }
            else if (action.first == Accept)
                return std::get<2>(s.top()).first;
            else // :(
                assert(false);
        }
    }
    // ：(
    assert(false);
}
