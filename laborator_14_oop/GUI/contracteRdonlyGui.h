#ifndef TEST_CONTRACTERDONLYGUI_H
#define TEST_CONTRACTERDONLYGUI_H

#include "disciplinaGui.h"
#include "cosCRUDGui.h" // Ensure this is included
#include "../Domain/Observer.h"
#include <QPainter>
#include <QWidget>

class ContracteRDONLYGUI : public QWidget, public Observer {
    Q_OBJECT
    friend class CosCRUDGui;
    friend class disciplinaGui;
    // Pointer to the current CosCRUDGui
    CosCRUDGui* cos;

public:
    // Constructor
    ContracteRDONLYGUI(CosCRUDGui* c);

    // Build UI
    void build_UI();

    // Update method from Observer
    void update() override;

    // Paint event
    void paintEvent(QPaintEvent* ev) override;

    // Destructor
    ~ContracteRDONLYGUI();
};

#endif // TEST_CONTRACTERDONLYGUI_H
