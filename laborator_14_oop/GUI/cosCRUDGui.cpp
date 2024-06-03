#include "cosCRUDGui.h"
#include "../Domain/exception.h"

void CosCRUDGui::initContractGUI() {

    //main layout
    auto* lyMain = new QHBoxLayout{};
    setLayout(lyMain);

    //left part
    auto* left = new QWidget;
    auto* lyleft = new QVBoxLayout;
    left->setLayout(lyleft);

    // schimba pe lista de contracte
    auto* form0 = new QWidget;
    auto* lyform0 = new QFormLayout;
    form0->setLayout(lyform0);
    butonAcasa = new QPushButton("Schimba pe meniul principal");
    lyform0->addWidget(butonAcasa);
    lyleft->addWidget(form0);


    // popularea listei de masini de spalat
    auto* form2 = new QWidget;
    auto* lyform2 = new QFormLayout;
    form2->setLayout(lyform2);
    populateContract = new QLineEdit{};
    lyform2->addRow(labelPopulateContract, populateContract);
    butonPopulateContract = new QPushButton("Genereaza masini");
    lyform2->addWidget(butonPopulateContract);
    lyleft->addWidget(form2);

    // golirea listei de masini de spalat
    butonEmptyContract = new QPushButton("Goleste lista de masini de spalat");
    lyleft->addWidget(butonEmptyContract);


    // lista curenta de masini
    auto* right = new QWidget;
    auto* lyright = new QHBoxLayout;
    right->setLayout(lyright);
    windowList = new QListWidget;
    lyright->addWidget(windowList);

    lyMain->addWidget(left);
    lyMain->addWidget(right);
}

void CosCRUDGui::connectSignalSlots()
{
    service.addObserver(this);
    QObject::connect(butonEmptyContract, &QPushButton::clicked, [&]()
    {
        this->service.emptyContract();
        this->reloadContractList(this->service.getContractList());
        QMessageBox::information(this, "Info", QString::fromStdString("Lista a fost golita cu succes!"));
    });
    QObject::connect(butonPopulateContract, &QPushButton::clicked, this, &CosCRUDGui::generateContractGUI);
    QObject::connect(butonAcasa, &QPushButton::clicked, [&]()
    {
        hide();
    });
}

void CosCRUDGui::generateContractGUI() {
    try
    {
        int nr = populateContract->text().toInt();
        populateContract->clear();
        this->service.populateContract(nr);
        this->reloadContractList(this->service.getContractList());
        QMessageBox::information(this, "Info", QString::fromStdString("Masinile au fost adaugate cu succes!"));
        service.notify();
    }
    catch (const InvalidGenerateNumber& err)
    {
        QMessageBox::warning(this, "Eroare", QString::fromStdString(err.getMessage()));
    }
}

void CosCRUDGui::reloadContractList(const std::vector<Disciplina>& disciplinaList){
    windowList->clear();
    for (const auto& d : disciplinaList)
    {
        QString itemText =
                QString::fromStdString(d.getDenumire()) + " | " +
                QString::number(d.getOre()) + " | " +
                QString::fromStdString(d.getTip()) + " | " +
                QString::fromStdString(d.getProfesor());
        auto* item = new QListWidgetItem(itemText);
        windowList->addItem(item);
    }
}




