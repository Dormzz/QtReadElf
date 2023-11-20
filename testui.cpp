//
// Created by dormz on 2023/11/20.
//

// You may need to build the project (run Qt uic code generator) to get "ui_TestUI.h" resolved

#include "testui.h"
#include "ui_TestUI.h"


TestUI::TestUI(QWidget *parent) :
        QWidget(parent), ui(new Ui::TestUI) {
    ui->setupUi(this);
}

TestUI::~TestUI() {
    delete ui;
}
