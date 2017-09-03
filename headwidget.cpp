#include "headwidget.h"

headWidget::headWidget(QWidget *parent) : QWidget(parent)
{
    initWidget();
}

headWidget::~headWidget()
{

}

void headWidget::initWidget()
{
    this->setFixedSize(1000,80);
    this->setStyleSheet("background-color:skyblue");

    QString btnStyle="QPushButton{border:1px solid green;border-radius:8px;font-family:微软雅黑;font-size:18px}"
                      "QPushButton:hover{border:1px solid blue;border-radius:8px;font-family:微软雅黑;font-size:20px}"
                      "QPushButton:pressed{border:1px solid red;border-radius:8px;font-family:微软雅黑;font-size:18px}";
    openBtn=new QPushButton("打 开",this);
    openBtn->setFixedSize(100,50);
    openBtn->move(50,15);
    openBtn->setStyleSheet(btnStyle);

    saveBtn=new QPushButton("保 存",this);
    saveBtn->setFixedSize(100,50);
    saveBtn->move(180,15);
    saveBtn->setStyleSheet(btnStyle);

    settingBtn=new QPushButton("设置",this);
    settingBtn->setFixedSize(50,50);
    settingBtn->move(750,15);
    settingBtn->setStyleSheet(btnStyle);

    minBtn=new QPushButton("最小",this);
    minBtn->setFixedSize(50,50);
    minBtn->move(820,15);
    minBtn->setStyleSheet(btnStyle);

    closeBtn=new QPushButton("关闭",this);
    closeBtn->setFixedSize(50,50);
    closeBtn->move(890,15);
    closeBtn->setStyleSheet(btnStyle);

    connect(openBtn,SIGNAL(clicked(bool)),this,SLOT(slt_openBtnClicked()));
    connect(saveBtn,SIGNAL(clicked(bool)),this,SLOT(slt_saveBtnClicked()));
    connect(settingBtn,SIGNAL(clicked(bool)),this,SLOT(slt_settingBtnClicked()));
    connect(minBtn,SIGNAL(clicked(bool)),this,SLOT(slt_minBtnClicked()));
    connect(closeBtn,SIGNAL(clicked(bool)),this,SLOT(slt_closeBtnClicked()));
}

QPushButton *headWidget::getOpenBtn()
{
    return openBtn;
}

QPushButton *headWidget::getSaveBtn()
{
    return saveBtn;
}

QPushButton *headWidget::getSettingBtn()
{
    return settingBtn;
}

void headWidget::paintEvent(QPaintEvent *e)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    QWidget::paintEvent(e);
}

void headWidget::slt_openBtnClicked()
{
    emit sig_openBtnClicked();
}

void headWidget::slt_saveBtnClicked()
{
    emit sig_saveBtnClicked();
}

void headWidget::slt_settingBtnClicked()
{
    emit sig_settingBtnClicked();
}

void headWidget::slt_minBtnClicked()
{
    emit sig_minBtnClicked();
}

void headWidget::slt_closeBtnClicked()
{
    emit sig_closeBtnClicked();
}
