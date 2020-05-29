//
// Created by szymon on 27.05.2020.
//

#ifndef SAT_CNF_H
#define SAT_CNF_H

#include <set>
#include <vector>
#include "Absyn.H"

class Literal {
public:
    String ident;
    bool isPositive;

    Literal(const String &ident, bool isPositive);

    bool operator<(const Literal &other) const;

    bool operator==(const Literal &other) const;
};

struct literal_compare {
    bool operator()(const Literal &lhs, const Literal &rhs) const {
        return lhs < rhs;
    }
};

class Clause {
public:
    std::set<Literal, literal_compare> clause;
};

struct clause_compare {
    bool operator()(const Clause &lhs, const Clause &rhs) const {
        if (lhs.clause.size() < rhs.clause.size()) {
            return true;
        }
        if (lhs.clause.size() > rhs.clause.size()) {
            return false;
        }
        return lhs.clause < rhs.clause;
    }
};

class CNF {
public:
    std::set<Clause, clause_compare> cnf;
};


#endif //SAT_CNF_H
