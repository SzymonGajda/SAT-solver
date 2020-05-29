//
// Created by szymon on 27.05.2020.
//

#include <iostream>
#include "Tseytin.h"
#include "CNF.h"

void Tseytin::visitFormula(Formula *p) {

}

void Tseytin::visitFormImplies(FormImplies *p) {
    String v1, v2, v3;
    v1 = getIdent(lastIdentNum);
    lastIdentNum++;
    v2 = getIdent(lastIdentNum);
    p->formula_1->accept(this);
    v3 = getIdent(lastIdentNum);
    p->formula_2->accept(this);
    auto localCnf = getCNFForImplies(v1, v2, v3);
    cnf.cnf.insert(localCnf.cnf.begin(), localCnf.cnf.end());
}

void Tseytin::visitFormIff(FormIff *p) {
    String v1, v2, v3;
    v1 = getIdent(lastIdentNum);
    lastIdentNum++;
    v2 = getIdent(lastIdentNum);
    p->formula_1->accept(this);
    v3 = getIdent(lastIdentNum);
    p->formula_2->accept(this);
    auto localCnf = getCNFForIff(v1, v2, v3);
    cnf.cnf.insert(localCnf.cnf.begin(), localCnf.cnf.end());
}

void Tseytin::visitFormOr(FormOr *p) {
    String v1, v2, v3;
    v1 = getIdent(lastIdentNum);
    lastIdentNum++;
    v2 = getIdent(lastIdentNum);
    p->formula_1->accept(this);
    v3 = getIdent(lastIdentNum);
    p->formula_2->accept(this);
    auto localCnf = getCNFForOr(v1, v2, v3);
    cnf.cnf.insert(localCnf.cnf.begin(), localCnf.cnf.end());
}

void Tseytin::visitFormAnd(FormAnd *p) {
    String v1, v2, v3;
    v1 = getIdent(lastIdentNum);
    lastIdentNum++;
    v2 = getIdent(lastIdentNum);
    p->formula_1->accept(this);
    v3 = getIdent(lastIdentNum);
    p->formula_2->accept(this);
    auto localCnf = getCNFForAnd(v1, v2, v3);
    cnf.cnf.insert(localCnf.cnf.begin(), localCnf.cnf.end());
}

void Tseytin::visitFormNot(FormNot *p) {
    String v1, v2;
    v1 = getIdent(lastIdentNum);
    lastIdentNum++;
    v2 = getIdent(lastIdentNum);
    p->formula_->accept(this);
    auto localCnf = getCNFForNot(v1, v2);
    cnf.cnf.insert(localCnf.cnf.begin(), localCnf.cnf.end());
}

void Tseytin::visitFormVar(FormVar *p) {
    String v1;
    v1 = getIdent(lastIdentNum);
    auto localCnf = getCNFForVar(v1, p->string_);
    cnf.cnf.insert(localCnf.cnf.begin(), localCnf.cnf.end());
    lastIdentNum++;
}

void Tseytin::visitFormFalse(FormFalse *p) {
    String v1;
    v1 = getIdent(lastIdentNum);
    auto localCnf = getCNFForFalse(v1);
    cnf.cnf.insert(localCnf.cnf.begin(), localCnf.cnf.end());
    lastIdentNum++;
}

void Tseytin::visitFormTrue(FormTrue *p) {
    String v1;
    v1 = getIdent(lastIdentNum);
    auto localCnf = getCNFForTrue(v1);
    cnf.cnf.insert(localCnf.cnf.begin(), localCnf.cnf.end());
    lastIdentNum++;
}

void Tseytin::visitString(String x) {

}

void Tseytin::visitInteger(Integer x) {

}

void Tseytin::visitChar(Char x) {

}

void Tseytin::visitDouble(Double x) {

}

void Tseytin::visitIdent(Ident x) {

}


// a -> b  ==  ~a \/ b

//v1 <==> v2
CNF Tseytin::getCNFForVar(String v1, String v2) {
    CNF cnf;
    Clause cl;
    cl.clause.insert(Literal(v1, false));
    cl.clause.insert(Literal(v2, true));
    cnf.cnf.insert(cl);
    cl.clause.clear();
    cl.clause.insert(Literal(v1, true));
    cl.clause.insert(Literal(v2, false));
    cnf.cnf.insert(cl);
    return cnf;
}


// a <==> T  =  a -> T /\ T -> a = ~a \/ T /\ F \/ a = [a]
CNF Tseytin::getCNFForTrue(String v1) {
    CNF cnf;
    Clause cl;
    cl.clause.insert(Literal(v1, true));
    cnf.cnf.insert(cl);
    return cnf;
}

// a <==> F  =  a -> F /\ F -> a = ~a \/ F /\ T \/ a = [~a]
CNF Tseytin::getCNFForFalse(String v1) {
    CNF cnf;
    Clause cl;
    cl.clause.insert(Literal(v1, false));
    cnf.cnf.insert(cl);
    return cnf;
}

// v1 <==> ~v2 = v1 -> ~v2 /\ ~v2 -> v1 = ~v1 \/ ~v2 /\ v2 \/ v1 = [v1, v2], [~v1, ~v2]
CNF Tseytin::getCNFForNot(String v1, String v2) {
    CNF cnf;
    Clause cl;
    cl.clause.insert(Literal(v1, true));
    cl.clause.insert(Literal(v2, true));
    cnf.cnf.insert(cl);
    cl.clause.clear();
    cl.clause.insert(Literal(v1, false));
    cl.clause.insert(Literal(v2, false));
    cnf.cnf.insert(cl);
    return cnf;
}

// v1 <==> v2 /\ v3  =  v1 -> v2 /\ v3  /\  v2 /\ v3 -> v1 = ~v1 \/ (v2 /\ v3)  /\ ~v2 \/ ~v3 \/ v1 = [~v1, v2], [~v1, v3], [~v2, ~v3, v1]
CNF Tseytin::getCNFForAnd(String v1, String v2, String v3) {
    CNF cnf;
    Clause cl;
    cl.clause.insert(Literal(v1, false));
    cl.clause.insert(Literal(v2, true));
    cnf.cnf.insert(cl);
    cl.clause.clear();
    cl.clause.insert(Literal(v1, false));
    cl.clause.insert(Literal(v3, true));
    cnf.cnf.insert(cl);
    cl.clause.clear();
    cl.clause.insert(Literal(v1, true));
    cl.clause.insert(Literal(v2, false));
    cl.clause.insert(Literal(v3, false));
    cnf.cnf.insert(cl);
    return cnf;
}


// v1 <==> v2 \/ v3  =  v1 -> v2 \/ v3  /\  v2 \/ v3 -> v1 = ~v1 \/ v2 \/ v3  /\ ~v2 /\ ~v3 \/ v1 = [~v1, v2, v3], [v1, ~v2], [v1, ~v3]
CNF Tseytin::getCNFForOr(String v1, String v2, String v3) {
    CNF cnf;
    Clause cl;
    cl.clause.insert(Literal(v1, true));
    cl.clause.insert(Literal(v2, false));
    cnf.cnf.insert(cl);
    cl.clause.clear();
    cl.clause.insert(Literal(v1, true));
    cl.clause.insert(Literal(v3, false));
    cnf.cnf.insert(cl);
    cl.clause.clear();
    cl.clause.insert(Literal(v1, false));
    cl.clause.insert(Literal(v2, true));
    cl.clause.insert(Literal(v3, true));
    cnf.cnf.insert(cl);
    return cnf;
}

//v1 <==> v2 -> v3  =  v1 -> (v2 -> v3) /\ (v2 -> v3) -> v1 = ~v1 \/ (~v2 \/ v3)  /\  ~(~v2 \/ v3) \/ v1 = [~v1, ~v2, v3], [v1, v2], [v1, ~v3]
CNF Tseytin::getCNFForImplies(String v1, String v2, String v3) {
    CNF cnf;
    Clause cl;
    cl.clause.insert(Literal(v1, true));
    cl.clause.insert(Literal(v2, true));
    cnf.cnf.insert(cl);
    cl.clause.clear();
    cl.clause.insert(Literal(v1, true));
    cl.clause.insert(Literal(v3, false));
    cnf.cnf.insert(cl);
    cl.clause.clear();
    cl.clause.insert(Literal(v1, false));
    cl.clause.insert(Literal(v2, false));
    cl.clause.insert(Literal(v3, true));
    cnf.cnf.insert(cl);
    return cnf;
}


//v1 <==> (v2 <==> v3) = v1 -> (v2 -> v3 /\ V3 -> v2) /\ (v2 -> v3 /\ V3 -> v2) -> v1
//~v1 \/ (~v2 \/ v3 /\ ~v3 \/ v2) = [~v1, ~v2, v3], [~v1, v2, ~v3]
//~(~v2 \/ v3 /\ ~v3 \/ v2) \/ v1 = (v2 /\ ~v3 \/ v3 /\ ~v2) \/ v1 = [v1, v2], [v1, ~v3], [v1, v3], [v1, ~v2] - v1 must be true - unit propagation
CNF Tseytin::getCNFForIff(String v1, String v2, String v3) {
    CNF cnf;
    Clause cl;
    cl.clause.insert(Literal(v1, false));
    cl.clause.insert(Literal(v2, false));
    cl.clause.insert(Literal(v3, true));
    cnf.cnf.insert(cl);
    cl.clause.clear();
    cl.clause.insert(Literal(v1, false));
    cl.clause.insert(Literal(v2, true));
    cl.clause.insert(Literal(v3, false));
    cnf.cnf.insert(cl);
    return cnf;
}

String Tseytin::getIdent(int num) {
    return "f_" + std::to_string(num);
}

Tseytin::Tseytin() {
    lastIdentNum = 0;
    String v0 = getIdent(0);
    Clause cl;
    cl.clause.insert(Literal(v0, true));
    cnf.cnf.insert(cl);
}

