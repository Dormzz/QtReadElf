//
// Created by dormz on 2023/11/20.
//

// You may need to build the project (run Qt uic code generator) to get "ui_TestUI.h" resolved

#include "mainui.h"
#include "ui_MainUI.h"
#include <QDragEnterEvent>
#include <QLabel>
#include <QDropEvent>
#include <QMimeData>
#include <QFile>


MainUI::MainUI(QWidget *parent) :
        QWidget(parent), ui(new Ui::MainUI) {
    setAcceptDrops(true); // 启用拖拽操作
    ui->setupUi(this);
}

MainUI::~MainUI() {
    delete ui;
}

void MainUI::dragEnterEvent(QDragEnterEvent *event) {
    // 检查是否有文件被拖拽进来
    if (event->mimeData()->hasUrls()) {
        event->acceptProposedAction(); // 接受拖拽操作
    }
}

void MainUI::dropEvent(QDropEvent *event) {
// 获取拖拽进来的文件列表
    QList<QUrl> urls = event->mimeData()->urls();

    // 处理拖拽的文件
    for (const QUrl &url: urls) {
        QString fileName = url.toLocalFile();
        // 在这里处理文件，例如打印文件路径
        qDebug() << "文件路径：" << fileName;
        QFile file(fileName);
        qDebug() << "文件大小为:" <<file.size() ;
//        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
//            QTextStream in(&file);
//
//            // 逐行读取文件内容并显示
//            while (!in.atEnd()) {
//                QString line = in.readLine();
//                // 在这里可以对读取的每一行进行处理
//                qDebug() << line;
//            }
//            // 关闭文件
//            file.close();
//        }
    }
}
