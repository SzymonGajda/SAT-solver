//
// Created by szymon on 27.05.2020.
//

#ifndef SAT_SIMPLIFIER_H
#define SAT_SIMPLIFIER_H


#include "Absyn.H"

class Simplifier : public Visitor {
public:

    bool isNot = false;
    bool isChange = false;

    Formula *simplifiedFormula;

    void visitFormula(Formula* p);
    void visitFormIff(FormIff* p);
    void visitFormImplies(FormImplies* p);
    void visitFormOr(FormOr* p);
    void visitFormAnd(FormAnd* p);
    void visitFormNot(FormNot* p);
    void visitFormVar(FormVar* p);
    void visitFormFalse(FormFalse* p);
    void visitFormTrue(FormTrue* p);

    void visitInteger(Integer x);
    void visitChar(Char x);
    void visitDouble(Double x);
    void visitString(String x);
    void visitIdent(Ident x);

};


#endif //SAT_SIMPLIFIER_H
