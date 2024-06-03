#include "contracteRdonlyGui.h"
#include "cosCRUDGui.h"
#include <QPainter>
#include <cstdlib>
#include <ctime>

ContracteRDONLYGUI::ContracteRDONLYGUI(CosCRUDGui* c) : cos{c} {
    this->build_UI();
    cos->service.addObserver(this);
}

void ContracteRDONLYGUI::build_UI() {
    auto* mainly = new QHBoxLayout;
    this->setLayout(mainly);
}

void ContracteRDONLYGUI::update() {
    this->repaint();
}

void ContracteRDONLYGUI::paintEvent(QPaintEvent* ev) {
    QPainter p(this);
    srand(time(nullptr));

    int x = -20;
    for (int i = 1; i <= cos->service.getContractList().size(); i++) {
        x += 40;
        const int forma = rand() % 4;
        const int inaltime = rand() % 130;
        const int start_y = rand() % 60;
        QColor color;

        const int color_num = rand() % 10;
        switch (color_num) {
            case 0: color = Qt::red; break;
            case 1: color = Qt::green; break;
            case 2: color = Qt::black; break;
            case 3: color = Qt::blue; break;
            case 4: color = Qt::lightGray; break;
            case 5: color = Qt::yellow; break;
            case 6: color = Qt::cyan; break;
            case 7: color = Qt::magenta; break;
            case 8: color = Qt::darkGreen; break;
            case 9: color = Qt::darkBlue; break;
            default: break;
        }

        switch (forma) {
            case 0: p.drawRect(x, start_y, 20, inaltime); break;
            case 1: p.drawEllipse(x, start_y, 20, inaltime); break;
            case 2: p.fillRect(x, start_y, 20, inaltime, color); break;
            default: p.fillRect(x, start_y, 20, inaltime, color); break;
        }
    }
}

ContracteRDONLYGUI::~ContracteRDONLYGUI()
{
    cos->service.removeObserver(this);
}