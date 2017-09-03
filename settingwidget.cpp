#include "settingwidget.h"

settingWidget::settingWidget(QWidget *parent) : QWidget(parent)
{
    initWidget();
}

settingWidget::~settingWidget()
{

}

void settingWidget::initWidget()
{
    this->setFixedSize(500,400);
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::Dialog);
    this->setWindowModality(Qt::ApplicationModal);
    this->setStyleSheet("background-color:#FFE1FF;");

    QFrame *frame=new QFrame(this);
    frame->setFixedSize(500,50);
    frame->setStyleSheet("background-color:skyblue");

    titleLabel=new QLabel("设  置",this);
    titleLabel->setFixedSize(60,40);
    titleLabel->move((this->width()-titleLabel->width())/2,5);
    titleLabel->setStyleSheet("background-color:skyblue;font-family:微软雅黑;font-size:20px");

    timeIntervalLabel=new QLabel("时 间 间 隔(s):",this);
    timeIntervalLabel->setFixedSize(120,30);
    timeIntervalLabel->move(90,65);
    timeIntervalLabel->setStyleSheet("font-family:微软雅黑;font-size:18px");

    rotatOrientationLabel=new QLabel("旋 转 方 向:",this);
    rotatOrientationLabel->setFixedSize(120,30);
    rotatOrientationLabel->move(90,110);
    rotatOrientationLabel->setStyleSheet("font-family:微软雅黑;font-size:18px");

    rotatNumLabel=new QLabel("旋 转 度 数:",this);
    rotatNumLabel->setFixedSize(120,30);
    rotatNumLabel->move(90,180);
    rotatNumLabel->setStyleSheet("font-family:微软雅黑;font-size:18px");

    timeIntervalSpinBox=new QSpinBox(this);
    timeIntervalSpinBox->setFixedSize(55,30);
    timeIntervalSpinBox->move(250,65);
    timeIntervalSpinBox->setRange(1,10);
    timeIntervalSpinBox->setValue(2);
    timeIntervalSpinBox->setStyleSheet("font-family:微软雅黑;font-size:18px");

    leftRadioBtn=new QRadioButton("顺 时 针",this);
    leftRadioBtn->setChecked(true);
    leftRadioBtn->setStyleSheet("font-family:微软雅黑;font-size:18px");
    leftRadioBtn->move(250,110);

    rightRadioBtn=new QRadioButton("逆 时 针",this);
    rightRadioBtn->setStyleSheet("font-family:微软雅黑;font-size:18px");
    rightRadioBtn->move(250,145);
    QButtonGroup *ratatoGroup=new QButtonGroup(this);
    ratatoGroup->addButton(leftRadioBtn,0);
    ratatoGroup->addButton(rightRadioBtn,1);

    rotatNumSpinBox=new QSpinBox(this);
    rotatNumSpinBox->setFixedSize(55,30);
    rotatNumSpinBox->move(250,180);
    rotatNumSpinBox->setRange(1,90);
    rotatNumSpinBox->setValue(90);
    rotatNumSpinBox->setStyleSheet("font-family:微软雅黑;font-size:18px");

    lightenLabel=new QLabel("亮  度:",this);
    lightenLabel->setFixedSize(60,30);
    lightenLabel->move(130,225);
    lightenLabel->setStyleSheet("font-family:微软雅黑;font-size:18px");

    lightenSpinBox=new QSpinBox(this);
    lightenSpinBox->setFixedSize(55,30);
    lightenSpinBox->move(250,225);
    lightenSpinBox->setRange(30,90);
    lightenSpinBox->setValue(70);
    lightenSpinBox->setStyleSheet("font-family:微软雅黑;font-size:18px");

    coldAndWarmLabel=new QLabel("冷 暖 色:",this);
    coldAndWarmLabel->setFixedSize(100,30);
    coldAndWarmLabel->move(110,270);
    coldAndWarmLabel->setStyleSheet("font-family:微软雅黑;font-size:18px");

    coldAndWarmSpinBox=new QSpinBox(this);
    coldAndWarmSpinBox->setFixedSize(55,30);
    coldAndWarmSpinBox->move(250,270);
    coldAndWarmSpinBox->setRange(30,90);
    coldAndWarmSpinBox->setValue(70);
    coldAndWarmSpinBox->setStyleSheet("font-family:微软雅黑;font-size:18px");

    saturationLabel=new QLabel("饱 和 度:",this);
    saturationLabel->setFixedSize(100,30);
    saturationLabel->move(110,310);
    saturationLabel->setStyleSheet("font-family:微软雅黑;font-size:18px");

    saturationSpinBox=new QSpinBox(this);
    saturationSpinBox->setFixedSize(55,30);
    saturationSpinBox->move(250,313);
    saturationSpinBox->setRange(30,90);
    saturationSpinBox->setValue(70);
    saturationSpinBox->setStyleSheet("font-family:微软雅黑;font-size:18px");

    okBtn=new QPushButton("确定",this);
    okBtn->setFixedSize(50,40);
    okBtn->move(150,350);
    okBtn->setStyleSheet("font-family:微软雅黑;font-size:18px;border-radius:5px;background-color:skyblue");

    cancleBtn=new QPushButton("取消",this);
    cancleBtn->setFixedSize(50,40);
    cancleBtn->move(300,350);
    cancleBtn->setStyleSheet("font-family:微软雅黑;font-size:18px;border-radius:5px;background-color:skyblue");


    connect(cancleBtn,SIGNAL(clicked(bool)),this,SLOT(close()));
    connect(okBtn,SIGNAL(clicked(bool)),this,SLOT(slt_okBtnClicked()));
}

QSpinBox *settingWidget::getTimerIntervalSpinBox()
{
    return timeIntervalSpinBox;
}

QSpinBox *settingWidget::getRotatNumSpinBox()
{
    return rotatNumSpinBox;
}

QRadioButton *settingWidget::getLeftRadioBtn()
{
    return leftRadioBtn;
}

QRadioButton *settingWidget::getRightRadioBtn()
{
    return rightRadioBtn;
}

QSpinBox *settingWidget::getLightSpinBox()
{
    return lightenSpinBox;
}

QSpinBox *settingWidget::getColdAndWarmSpinBox()
{
    return coldAndWarmSpinBox;
}

QSpinBox *settingWidget::getSaturationSpinBox()
{
    return saturationSpinBox;
}

void settingWidget::slt_okBtnClicked()
{
    emit sig_okBtnClicked();
}
