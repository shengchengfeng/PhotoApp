#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <headwidget.h>
#include <funcwidget.h>
#include <screenshot.h>
#include <moreeffect.h>
#include <settingwidget.h>

#include "head.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();
    void initWidget();
    void initHeadWid();
    void initFuncWid();
    void initScreenShotWidget();
    void initMoreEffect();

    void showPhoto();
    void setBtnsCanClick();
    void setBtnsCanNotClick();
    inline void hideMoreEffectWidget();
    inline void setSliders();
signals:
    void sig_setItemIndex(int );
public slots:
    void slt_itemClick(int index);
    void slt_timeOut();
    void slt_stopTimer();
    void slt_preBtnClicked();
    void slt_nextBtnClicked();
    void slt_changeSize(int num);
    void slt_changeTransparent(int num);
    void slt_changeRotat();

    void slt_choosePhoto();
    void slt_saveImage();
    void slt_minWidget();
    void slt_settingWidget();
    void slt_okSettting();
    void slt_moreEffect();
    void slt_changeGrey();
    void slt_changeLighten();
    void slt_changeCold();
    void slt_changeWarm();
    void slt_changeSaturation();
protected:
    void closeEvent(QCloseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
private:
    bool mDragWindow;
    QPoint mousePoint;
    QLabel *photoLabel;
    QStringList photoNames;
    QImage img;
    int photoIndex,timeInterval,rotatNum;
    QTimer *timer;
    QMatrix matrix;
    int lightenNum=70,coldAndWarmNum=70,saturationNum=30;

    headWidget *headWid;
    funcWidget *funcWid;
    screenShot *screenShotWidget;
    moreeffect *moreEffectWidget;
    settingWidget *settingWid;
};

#endif // WIDGET_H
