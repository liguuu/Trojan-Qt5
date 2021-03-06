#include "editdialog.h"
#include "ui_editdialog.h"
#include "trojanvalidator.h"
#include "ip4validator.h"
#include "portvalidator.h"

EditDialog::EditDialog(Connection *_connection, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditDialog),
    connection(_connection)
{
    ui->setupUi(this);

    /* initialisation and validator setup */
    IP4Validator *addrValidator = new IP4Validator(this);
    PortValidator *portValidator = new PortValidator(this);
    ui->serverPortEdit->setValidator(portValidator);
    ui->localPortEdit->setValidator(portValidator);
    //Maybe we shouldn't validate local address using IPv4 format?
    ui->localAddrEdit->setValidator(addrValidator);

    ui->nameEdit->setText(connection->profile.name);
    ui->serverAddrEdit->setText(connection->profile.serverAddress);
    ui->serverPortEdit->setText(QString::number(connection->profile.serverPort));
    ui->verifyCertificateCheckBox->setChecked(connection->profile.verifyCertificate);
    ui->verifyHostnameCheckBox->setChecked(connection->profile.verifyHostname);
    ui->pwdEdit->setText(connection->profile.password);
    ui->localAddrEdit->setText(connection->profile.localAddress);
    ui->localPortEdit->setText(QString::number(connection->profile.localPort));
    ui->localHttpPortEdit->setText(QString::number(connection->profile.localHttpPort));
    ui->dualRadioButton->setChecked(connection->profile.dualMode);
    ui->tcpFastOpenCheckBox->setChecked(connection->profile.tcpFastOpen);
    ui->resetDateEdit->setDate(connection->profile.nextResetDate);
    ui->resetDateEdit->setMinimumDate(QDate::currentDate());
    ui->autoStartCheckBox->setChecked(connection->profile.autoStart);

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &EditDialog::save);

    this->adjustSize();
}

EditDialog::~EditDialog()
{
    delete ui;
}

void EditDialog::save()
{
    connection->profile.name = ui->nameEdit->text();
    connection->profile.serverAddress = ui->serverAddrEdit->text().trimmed();
    connection->profile.serverPort = ui->serverPortEdit->text().toUShort();
    connection->profile.verifyCertificate = ui->verifyCertificateCheckBox->isChecked();
    connection->profile.verifyHostname = ui->verifyHostnameCheckBox->isChecked();
    connection->profile.localAddress = ui->localAddrEdit->text();
    connection->profile.localPort = ui->localPortEdit->text().toUShort();
    connection->profile.localHttpPort = ui->localHttpPortEdit->text().toUShort();
    connection->profile.dualMode = ui->dualRadioButton->isChecked();
    connection->profile.tcpFastOpen = ui->tcpFastOpenCheckBox->isChecked();
    connection->profile.password = ui->pwdEdit->text();
    connection->profile.nextResetDate = ui->resetDateEdit->date();
    connection->profile.autoStart = ui->autoStartCheckBox->isChecked();

    this->accept();
}
