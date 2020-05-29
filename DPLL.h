//
// Created by szymon on 28.05.2020.
//

#ifndef SAT_DPLL_H
#define SAT_DPLL_H


#include "CNF.h"

class DPLL {
public:

    static bool empty_intersection(const Clause &c, const std::set<Literal> &s2);

    static CNF propagateUnit(CNF cnf);

    static CNF eliminatePureLiterals(CNF cnf);

    static bool runDPLL(CNF cnf);

    static String getSplittingLiterals(const CNF &cnf);
};


#endif //SAT_DPLL_H
