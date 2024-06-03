#ifndef TEST_COSCRUDGUI_H
#define TEST_COSCRUDGUI_H

#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QMessageBox>
#include "../Domain/Observer.h"
#include "../Service/DisciplinaService.h"

// Forward declaration of disciplinaGui
class disciplinaGui;

class CosCRUDGui : public QWidget, public Observer {
    Q_OBJECT
    friend class disciplinaGui;
public:
    explicit CosCRUDGui(DisciplinaService& dS): service{dS} {}

    ~CosCRUDGui() = default;

    void update() override
    {
        reloadContractList(service.getContractList());
    }
    DisciplinaService& service;
private:

    disciplinaGui* main = nullptr;

    QListWidget* windowList;
    QPushButton* butonEmptyContract;
    QPushButton* butonPopulateContract;
    QPushButton* butonAcasa;

    QLabel* labelAddContract;

    QLabel* labelPopulateContract = new QLabel("Populeaza Contract:",nullptr);
    QLineEdit* populateContract{};

    void generateContractGUI();
    void initContractGUI();
    void reloadContractList(const std::vector<Disciplina>& disciplinaList);
    void connectSignalSlots();
};

#endif // TEST_COSCRUDGUI_H
