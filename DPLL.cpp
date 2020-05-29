//
// Created by szymon on 28.05.2020.
//

#include <map>
#include <algorithm>
#include <iostream>
#include "DPLL.h"

CNF DPLL::propagateUnit(CNF cnf) {
    while (cnf.cnf.begin()->clause.size() == 1) {
        CNF clausesToAddBack;
        Literal literal = *cnf.cnf.begin()->clause.begin();
        Literal negatedLiteral = literal;
        negatedLiteral.isPositive = !negatedLiteral.isPositive;
        for (auto it = cnf.cnf.begin(); it != cnf.cnf.end();) {
            if (it->clause.find(literal) != it->clause.end()) {
                it = cnf.cnf.erase(it);
            } else {
                if (it->clause.find(negatedLiteral) != it->clause.end()) {
                    Clause cl = *it;
                    cl.clause.erase(negatedLiteral);
                    clausesToAddBack.cnf.insert(cl);
                    it = cnf.cnf.erase(it);
                } else {
                    ++it;
                }
            }
        }
        cnf.cnf.insert(clausesToAddBack.cnf.begin(), clausesToAddBack.cnf.end());
        clausesToAddBack.cnf.clear();
    }
    return cnf;
}

bool DPLL::empty_intersection(const Clause &c, const std::set<Literal> &s2) {
    auto s1 = c.clause;
    auto i = s1.begin();
    auto j = s2.begin();
    while (i != s1.end() && j != s2.end()) {
        if (*i == *j)
            return false;
        else if (*i < *j)
            ++i;
        else
            ++j;
    }
    return true;
}

CNF DPLL::eliminatePureLiterals(CNF cnf) {
    std::set<Literal> literals;
    std::set<Literal> literalsToEliminate;
    String lastLiteral;
    for (const auto &cl : cnf.cnf) {
        literals.insert(cl.clause.begin(), cl.clause.end());
    }
    for (const auto &l : literals) {
        if (l.isPositive) {
            if (lastLiteral != l.ident) {
                literalsToEliminate.insert(l);
            }
        }
        lastLiteral = l.ident;
    }
    for (auto it = cnf.cnf.begin(); it != cnf.cnf.end();) {
        if (!empty_intersection(*it, literalsToEliminate)) {
            it = cnf.cnf.erase(it);
        } else {
            ++it;
        }
    }
    return cnf;
}

String DPLL::getSplittingLiterals(const CNF &cnf) {
    std::vector<std::pair<int, String>> res;
    std::map<String, int> map;
    for (const auto &cl : cnf.cnf) {
        for (const auto &l : cl.clause) {
            if (map.find(l.ident) == map.end()) {
                map[l.ident] = 0;
            } else {
                map[l.ident]++;
            }
        }
    }
    res.reserve(map.size());
    for (const auto &p : map) {
        res.emplace_back(p.second, p.first);
    }
    return std::max_element(res.begin(), res.end())->second;
}


bool DPLL::runDPLL(CNF cnf) {
    if (!cnf.cnf.empty() && !cnf.cnf.begin()->clause.empty()) {
        cnf = propagateUnit(cnf);
        cnf = eliminatePureLiterals(cnf);
    }
    if (!cnf.cnf.empty() && !cnf.cnf.begin()->clause.empty()) {
        String splittingLiterals = getSplittingLiterals(cnf);
        Clause positive, negative;
        positive.clause.insert(Literal(splittingLiterals, true));
        negative.clause.insert(Literal(splittingLiterals, false));
        cnf.cnf.insert(positive);
        if (runDPLL(cnf)) {
            return true;
        }
        cnf.cnf.erase(positive);
        cnf.cnf.insert(negative);
        return runDPLL(cnf);
    }
    return cnf.cnf.empty();
}








