//
// Created by szymon on 27.05.2020.
//

#include "CNF.h"

Literal::Literal(const String &ident, bool isPositive) : ident(ident), isPositive(isPositive) {}

bool Literal::operator<(const Literal &other) const {
    if (ident < other.ident) {
        return true;
    }
    if (ident > other.ident) {
        return false;
    }
    if ((isPositive && other.isPositive) || !(isPositive || other.isPositive)) {
        return false;
    }
    return !isPositive;
}

bool Literal::operator==(const Literal &other) const {
    return ident == other.ident && (isPositive == other.isPositive);
}

