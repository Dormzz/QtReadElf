//
// Created by dormz on 2023/11/20.
//

#ifndef QTREADELF_MAINUI_H
#define QTREADELF_MAINUI_H

#include <QWidget>
#include <iostream>

QT_BEGIN_NAMESPACE
namespace Ui { class MainUI; }
QT_END_NAMESPACE

class MainUI : public QWidget {
Q_OBJECT

public:
    explicit MainUI(QWidget *parent = nullptr);

    ~MainUI() override;

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;

    void dropEvent(QDropEvent *event) override;


private:
    Ui::MainUI *ui;
};


#endif //QTREADELF_MAINUI_H
