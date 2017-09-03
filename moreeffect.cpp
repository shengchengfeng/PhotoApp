#include "moreeffect.h"

moreeffect::moreeffect(QWidget *parent) : QWidget(parent)
{
    initWidget();
}

moreeffect::~moreeffect()
{

}

void moreeffect::initWidget()
{
    this->setFixedSize(200,600);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setStyleSheet("background-color:#FFE1FF");
    this->move(QApplication::desktop()->width()-this->width(),(QApplication::desktop()->height()-this->height())/2);

    QString btnStyle="QPushButton{border:1px solid green;border-radius:5px;font-family:微软雅黑;font-size:16px}"
                      "QPushButton:hover{border:1px solid blue;border-radius:5px;font-family:微软雅黑;font-size:18px}"
                      "QPushButton:pressed{border:1px solid red;border-radius:5px;font-family:微软雅黑;font-size:16px}";

    greyBtn=new QPushButton("灰 度",this);
    greyBtn->setFixedSize(80,80);
    greyBtn->move(60,50);
    greyBtn->setStyleSheet(btnStyle);

    lightenBtn=new QPushButton("加 亮",this);
    lightenBtn->setFixedSize(80,80);
    lightenBtn->move(60,150);
    lightenBtn->setStyleSheet(btnStyle);

    warmBtn=new QPushButton("暖 色 调",this);
    warmBtn->setFixedSize(80,80);
    warmBtn->move(60,250);
    warmBtn->setStyleSheet(btnStyle);

    coldBtn=new QPushButton("冷 色 调",this);
    coldBtn->setFixedSize(80,80);
    coldBtn->move(60,350);
    coldBtn->setStyleSheet(btnStyle);

    saturationBtn=new QPushButton("饱 和",this);
    saturationBtn->setFixedSize(80,80);
    saturationBtn->move(60,450);
    saturationBtn->setStyleSheet(btnStyle);

    connect(greyBtn,SIGNAL(clicked(bool)),this,SLOT(slt_greyClicked()));
    connect(lightenBtn,SIGNAL(clicked(bool)),this,SLOT(slt_lightClicked()));
    connect(warmBtn,SIGNAL(clicked(bool)),this,SLOT(slt_warmClicked()));
    connect(coldBtn,SIGNAL(clicked(bool)),this,SLOT(slt_coldClicked()));
    connect(saturationBtn,SIGNAL(clicked(bool)),this,SLOT(slt_saturationClicked()));

}

void moreeffect::slt_greyClicked()
{
    emit sig_greyClicked();
}

void moreeffect::slt_lightClicked()
{
    emit sig_lightenClicked();
}

void moreeffect::slt_warmClicked()
{
    emit sig_warmClicked();
}

void moreeffect::slt_coldClicked()
{
    emit sig_coldClicked();
}

void moreeffect::slt_saturationClicked()
{
    emit sig_saturationClicked();
}
