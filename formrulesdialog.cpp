#include "formrulesdialog.h"
#include "ui_formrulesdialog.h"

FormRulesDialog::FormRulesDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::FormRulesDialog)
{
    // ui->label_setName->setText(ruleData->getRuleName());
    // ui->label_setDirection->setText(ruleData->getRuleInOut());
    // ui->label_setPort->setText(ruleData->getRulePort());
    // ui->label_setProtocol->setText(ruleData->getRuleTCPorUDP());
    // ui->label_setIP->setText(ruleData->getRuleIP());
    ruleData = new Rule();
    ui->setupUi(this);
}

FormRulesDialog::~FormRulesDialog()
{
    delete ui;
}

void FormRulesDialog::setRuleData(Rule *setRuleData)
{
    ruleData = setRuleData;
    ui->label_setName->setText(ruleData->getRuleName());
    ui->label_setDirection->setText(ruleData->getRuleInOut());
    ui->label_setPort->setText(ruleData->getRulePort());
    ui->label_setProtocol->setText(ruleData->getRuleTCPorUDP());
    ui->label_setIP->setText(ruleData->getRuleIP());
}

// bool FormRulesDialog::getStatus()
// {
//     if()
//     {

//     }
// }
