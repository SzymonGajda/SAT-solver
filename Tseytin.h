//
// Created by szymon on 27.05.2020.
//

#ifndef SAT_TSEYTIN_H
#define SAT_TSEYTIN_H

#include "Absyn.H"
#include "CNF.h"


class Tseytin : public Visitor {
public:
    int lastIdentNum = 0;
    CNF cnf;

    String getIdent(int num);

    Tseytin();

    void visitFormula(Formula *p);

    void visitFormIff(FormIff *p);

    void visitFormImplies(FormImplies *p);

    void visitFormOr(FormOr *p);

    void visitFormAnd(FormAnd *p);

    void visitFormNot(FormNot *p);

    void visitFormVar(FormVar *p);

    void visitFormFalse(FormFalse *p);

    void visitFormTrue(FormTrue *p);

    void visitInteger(Integer x);

    void visitChar(Char x);

    void visitDouble(Double x);

    void visitString(String x);

    void visitIdent(Ident x);

    CNF getCNFForIff(String v1, String v2, String v3);

    CNF getCNFForVar(String v1, String v2);

    CNF getCNFForTrue(String v1);

    CNF getCNFForFalse(String v1);

    CNF getCNFForNot(String v1, String v2);

    CNF getCNFForAnd(String v1, String v2, String v3);

    CNF getCNFForOr(String v1, String v2, String v3);

    CNF getCNFForImplies(String v1, String v2, String v3);
};


#endif //SAT_TSEYTIN_H
