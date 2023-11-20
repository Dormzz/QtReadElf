//
// Created by dormz on 2023/11/20.
//

#ifndef QTREADELF_TESTUI_H
#define QTREADELF_TESTUI_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class TestUI; }
QT_END_NAMESPACE

class TestUI : public QWidget {
Q_OBJECT

public:
    explicit TestUI(QWidget *parent = nullptr);

    ~TestUI() override;

private:
    Ui::TestUI *ui;
};


#endif //QTREADELF_TESTUI_H
