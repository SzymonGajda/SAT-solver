//
// Created by szymon on 27.05.2020.
//

#include "Simplifier.h"

void Simplifier::visitFormula(Formula *p) {

}

void Simplifier::visitFormIff(FormIff *p) {
    if (p->formula_1->toString() == "FormTrue") {
        isChange = true;
        p->formula_2->accept(this);
        return;
    }
    if (p->formula_1->toString() == "FormFalse") {
        isChange = true;
        FormNot *temp = new FormNot(p->formula_2);
        temp->accept(this);
        temp->formula_ = nullptr;
        delete temp;
        return;
    }
    if (p->formula_2->toString() == "FormTrue") {
        isChange = true;
        p->formula_1->accept(this);
        return;
    }
    if (p->formula_2->toString() == "FormFalse") {
        isChange = true;
        FormNot *temp = new FormNot(p->formula_1);
        temp->accept(this);
        temp->formula_ = nullptr;
        delete temp;
        return;
    }
    p->formula_1->accept(this);
    Formula *f1 = simplifiedFormula;
    p->formula_2->accept(this);
    simplifiedFormula = new FormIff(f1, simplifiedFormula);
}

void Simplifier::visitFormImplies(FormImplies *p) {
    if (p->formula_2->toString() == "FormTrue") {
        isChange = true;
        simplifiedFormula = new FormTrue();
        return;
    }
    if (p->formula_1->toString() == "FormFalse") {
        isChange = true;
        simplifiedFormula = new FormTrue();
        return;
    }
    if (p->formula_1->toString() == "FormTrue") {
        isChange = true;
        p->formula_2->accept(this);
        return;
    }
    if (p->formula_2->toString() == "FormFalse") {
        isChange = true;
        FormNot *temp = new FormNot(p->formula_1);
        temp->accept(this);
        temp->formula_ = nullptr;
        delete temp;
        return;
    }
    p->formula_1->accept(this);
    Formula *f1 = simplifiedFormula;
    p->formula_2->accept(this);
    simplifiedFormula = new FormImplies(f1, simplifiedFormula);
}

void Simplifier::visitFormOr(FormOr *p) {
    if (p->formula_1->toString() == "FormTrue") {
        isChange = true;
        simplifiedFormula = new FormTrue();
        return;
    }
    if (p->formula_1->toString() == "FormFalse") {
        isChange = true;
        p->formula_2->accept(this);
        return;
    }
    if (p->formula_2->toString() == "FormTrue") {
        isChange = true;
        simplifiedFormula = new FormTrue();
        return;
    }
    if (p->formula_2->toString() == "FormFalse") {
        isChange = true;
        p->formula_1->accept(this);
    }
    p->formula_1->accept(this);
    Formula *f1 = simplifiedFormula;
    p->formula_2->accept(this);
    simplifiedFormula = new FormOr(f1, simplifiedFormula);
}

void Simplifier::visitFormAnd(FormAnd *p) {
    if (p->formula_1->toString() == "FormTrue") {
        isChange = true;
        p->formula_2->accept(this);
        return;
    }
    if (p->formula_1->toString() == "FormFalse") {
        isChange = true;
        simplifiedFormula = new FormFalse();
        return;
    }
    if (p->formula_2->toString() == "FormTrue") {
        isChange = true;
        p->formula_1->accept(this);
        return;
    }
    if (p->formula_2->toString() == "FormFalse") {
        isChange = true;
        simplifiedFormula = new FormFalse();
        return;
    }
    p->formula_1->accept(this);
    Formula *f1 = simplifiedFormula;
    p->formula_2->accept(this);
    simplifiedFormula = new FormAnd(f1, simplifiedFormula);
}

void Simplifier::visitFormNot(FormNot *p) {
    if (isNot) {
        isChange = true;
        isNot = false;
        p->formula_->accept(this);
        return;
    }
    if (p->formula_->toString() == "FormNot") {
        isChange = true;
        isNot = true;
        p->formula_->accept(this);
        return;
    }
    if (p->formula_->toString() == "FormTrue") {
        isChange = true;
        simplifiedFormula = new FormFalse();
        return;
    }
    if (p->formula_->toString() == "FormFalse") {
        isChange = true;
        simplifiedFormula = new FormTrue();
        return;
    }
    p->formula_->accept(this);
    simplifiedFormula = new FormNot(simplifiedFormula);
}

void Simplifier::visitFormVar(FormVar *p) {
    simplifiedFormula = new FormVar(p->string_);
}

void Simplifier::visitFormFalse(FormFalse *p) {
    simplifiedFormula = new FormFalse();
}

void Simplifier::visitFormTrue(FormTrue *p) {
    simplifiedFormula = new FormTrue();
}

void Simplifier::visitInteger(Integer x) {

}

void Simplifier::visitChar(Char x) {

}

void Simplifier::visitDouble(Double x) {

}

void Simplifier::visitString(String x) {

}

void Simplifier::visitIdent(Ident x) {

}
