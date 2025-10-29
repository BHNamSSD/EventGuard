#ifndef FORMRULESDIALOG_H
#define FORMRULESDIALOG_H

#include <QDialog>
#include "rule.h"


namespace Ui {
class FormRulesDialog;
}

class FormRulesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FormRulesDialog(QWidget *parent = nullptr);
    //explicit FormRulesDialog(QWidget *parent = nullptr, Rule * = nullptr);
    ~FormRulesDialog();

    void setRuleData(Rule *);
    //bool getStatus();

private:
    Ui::FormRulesDialog *ui;
    Rule *ruleData;

};

#endif // FORMRULESDIALOG_H
