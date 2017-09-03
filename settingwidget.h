#ifndef SETTINGWIDGET_H
#define SETTINGWIDGET_H

#include <QWidget>
#include "head.h"

class settingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit settingWidget(QWidget *parent = 0);
    ~settingWidget();
    void initWidget();
    QSpinBox* getTimerIntervalSpinBox();
    QSpinBox* getRotatNumSpinBox();
    QRadioButton* getLeftRadioBtn();
    QRadioButton* getRightRadioBtn();
    QSpinBox* getLightSpinBox();
    QSpinBox* getColdAndWarmSpinBox();
    QSpinBox* getSaturationSpinBox();
signals:
    void sig_okBtnClicked();
public slots:
    void slt_okBtnClicked();
private:
    QLabel *titleLabel;
    QPushButton *okBtn,*cancleBtn;

    QLabel *timeIntervalLabel,*rotatOrientationLabel,*rotatNumLabel,*lightenLabel,*coldAndWarmLabel,*saturationLabel;
    QSpinBox *timeIntervalSpinBox,*rotatNumSpinBox,*lightenSpinBox,*coldAndWarmSpinBox,*saturationSpinBox;
    QRadioButton *leftRadioBtn,*rightRadioBtn;
};

#endif // SETTINGWIDGET_H
