#include "screenshot.h"

screenShot::screenShot(QWidget *parent) : QWidget(parent)
{
    initWidget();
}

screenShot::~screenShot()
{

}

QListWidget *screenShot::getPhotoListWidget()
{
    return photoListWidget;
}

void screenShot::initWidget()
{
    this->setFixedSize(270,800);
    this->move(0,(QApplication::desktop()->height()-this->height())/2);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setStyleSheet("background-color:#FFE1FF");

    QString btnStyle="QPushButton{border:1px solid green;border-radius:5px;font-family:微软雅黑;font-size:16px}"
                      "QPushButton:hover{border:1px solid blue;border-radius:5px;font-family:微软雅黑;font-size:18px}"
                      "QPushButton:pressed{border:1px solid red;border-radius:5px;font-family:微软雅黑;font-size:16px}";

    minBtn=new QPushButton("最小",this);
    minBtn->setFixedSize(40,40);
    minBtn->move(175,15);
    minBtn->setStyleSheet(btnStyle);

    hideBtn=new QPushButton("隐藏",this);
    hideBtn->setFixedSize(40,40);
    hideBtn->move(225,15);
    hideBtn->setStyleSheet(btnStyle);

    count=0;
    connect(minBtn,SIGNAL(clicked(bool)),this,SLOT(slt_minBtnClick()));
    connect(hideBtn,SIGNAL(clicked(bool)),this,SLOT(slt_hideBtnClick()));

    photoListWidget=new QListWidget(this);
    photoListWidget->setFixedSize(250,650);
    photoListWidget->move(10,85);
    photoListWidget->setIconSize(QSize(196,146));
    photoListWidget->setViewMode(QListView::IconMode);
    photoListWidget->setSpacing(15);
//    photoListWidget->setStyleSheet("QListWidget::item:selected{background:#FF0000}"
//                                   "QListWidget::item:hover{background:#00FF00;}");
    photoListWidget->setStyleSheet("QListWidget::item:selected{border:2px solid green}"
                                   "QListWidget::item:hover{border:2px solid red}");

    connect(photoListWidget,SIGNAL(currentRowChanged(int)),this,SLOT(slt_itemClick(int)));
}

void screenShot::slt_itemClick(int index)
{
    emit sig_photoItemClick(index);
}

void screenShot::slt_setCurrentRow(int raw)
{
    photoListWidget->setCurrentRow(raw);
}

void screenShot::slt_minBtnClick()
{
    this->showMinimized();
}

void screenShot::slt_hideBtnClick()
{
    count+=1;
    if(count==1)
    {
        this->move(-240,(QApplication::desktop()->height()-this->height())/2);
        hideBtn->setText("显示");
    }
    if(count==2)
    {
        this->move(0,(QApplication::desktop()->height()-this->height())/2);
        hideBtn->setText("隐藏");
        count=0;
    }
}
