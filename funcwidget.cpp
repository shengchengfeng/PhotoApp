#include "funcwidget.h"

funcWidget::funcWidget(QWidget *parent) : QWidget(parent)
{
    initWidget();
}

funcWidget::~funcWidget()
{

}

void funcWidget::initWidget()
{
    this->setFixedSize(1000,120);
    this->move(0,680);
    this->setStyleSheet("background-color:#B0E0E6");
    QString btnStyle="QPushButton{border:1px solid green;border-radius:8px;font-family:微软雅黑;font-size:18px}"
                      "QPushButton:hover{border:1px solid blue;border-radius:8px;font-family:微软雅黑;font-size:20px}"
                      "QPushButton:pressed{border:1px solid red;border-radius:8px;font-family:微软雅黑;font-size:18px}";

    playBtn=new QPushButton("播放",this);
    playBtn->setFixedSize(80,80);
    playBtn->move(60,20);
    playBtn->setStyleSheet(btnStyle);

    stopBtn=new QPushButton("停止",this);
    stopBtn->setFixedSize(80,80);
    stopBtn->move(160,20);
    stopBtn->setStyleSheet(btnStyle);

    preBtn=new QPushButton("前一张",this);
    preBtn->setFixedSize(80,80);
    preBtn->move(260,20);
    preBtn->setStyleSheet(btnStyle);

    nextBtn=new QPushButton("后一张",this);
    nextBtn->setFixedSize(80,80);
    nextBtn->move(360,20);
    nextBtn->setStyleSheet(btnStyle);

    sizeSlider=new QSlider(Qt::Horizontal,this);
    sizeSlider->resize(180,10);
    sizeSlider->setRange(1,200);
    sizeSlider->setValue(100);
    sizeSlider->move(470,20);

    smallLabel=new QLabel("-",this);
    smallLabel->setFixedSize(28,28);
    smallLabel->move(480,27);
    smallLabel->setStyleSheet("font-size:20px;font-weight:bold;font-family:微软雅黑");

    maxLabel=new QLabel("+",this);
    maxLabel->setFixedSize(28,28);
    maxLabel->move(625,27);
    maxLabel->setStyleSheet("font-size:20px;font-weight:bold;font-family:微软雅黑");

    transparentSlider=new QSlider(Qt::Horizontal,this);
    transparentSlider->resize(180,10);
    transparentSlider->setRange(0,100);
    transparentSlider->setValue(100);
    transparentSlider->move(470,70);

    transparentLabel=new QLabel("透 明 度",this);
    transparentLabel->setFixedSize(100,30);
    transparentLabel->move(530,78);
    transparentLabel->setStyleSheet("font-size:20px;font-family:微软雅黑");

    rotatBtn=new QPushButton("旋转",this);
    rotatBtn->setFixedSize(80,80);
    rotatBtn->move(680,20);
    rotatBtn->setStyleSheet(btnStyle);

    moreEffectBtn=new QPushButton("更 多 效 果",this);
    moreEffectBtn->setFixedSize(130,50);
    moreEffectBtn->move(790,35);
    moreEffectBtn->setStyleSheet(btnStyle);

    connect(playBtn,SIGNAL(clicked(bool)),this,SLOT(slt_playBtnClicked()));
    connect(stopBtn,SIGNAL(clicked(bool)),this,SLOT(slt_stopBtnClicked()));
    connect(preBtn,SIGNAL(clicked(bool)),this,SLOT(slt_preBtnClicked()));
    connect(nextBtn,SIGNAL(clicked(bool)),this,SLOT(slt_nextBtnClicked()));
    connect(rotatBtn,SIGNAL(clicked(bool)),this,SLOT(slt_rotatBtnClicked()));
    connect(moreEffectBtn,SIGNAL(clicked(bool)),this,SLOT(slt_moreEffect()));
}

QPushButton *funcWidget::getPlayBtn()
{
    return playBtn;
}

QPushButton *funcWidget::getStopBtn()
{
    return stopBtn;
}

QPushButton *funcWidget::getPreBtn()
{
    return preBtn;
}

QPushButton *funcWidget::getNextBtn()
{
    return nextBtn;
}

QPushButton *funcWidget::getRotatBtn()
{
    return rotatBtn;
}

QPushButton *funcWidget::getMoreEffectBtn()
{
    return moreEffectBtn;
}

QSlider *funcWidget::getSizeSlider()
{
    return sizeSlider;
}

QSlider *funcWidget::getTransparentSlider()
{
    return transparentSlider;
}

void funcWidget::paintEvent(QPaintEvent *e)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    QWidget::paintEvent(e);
}

void funcWidget::slt_playBtnClicked()
{
    emit sig_playBtnClicked();
}

void funcWidget::slt_stopBtnClicked()
{
    emit sig_stopBtnClicked();
}

void funcWidget::slt_preBtnClicked()
{
    emit sig_preBtnClicked();
}

void funcWidget::slt_nextBtnClicked()
{
    emit sig_nextBtnClicked();
}

void funcWidget::slt_rotatBtnClicked()
{
    emit sig_rotatBtnClicked();
}

void funcWidget::slt_moreEffect()
{
     emit sig_moreEffect();
}
