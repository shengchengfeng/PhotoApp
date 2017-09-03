#ifndef FUNCWIDGET_H
#define FUNCWIDGET_H

#include <QWidget>
#include "head.h"
class funcWidget : public QWidget
{
    Q_OBJECT
public:
    explicit funcWidget(QWidget *parent = 0);
    ~funcWidget();
    void initWidget();
    QPushButton* getPlayBtn();
    QPushButton* getStopBtn();
    QPushButton* getPreBtn();
    QPushButton* getNextBtn();
    QPushButton* getRotatBtn();
    QPushButton* getMoreEffectBtn();

    QSlider* getSizeSlider();
    QSlider* getTransparentSlider();
protected:
    void paintEvent(QPaintEvent *e);
signals:
    void sig_playBtnClicked();
    void sig_stopBtnClicked();
    void sig_preBtnClicked();
    void sig_nextBtnClicked();
    void sig_rotatBtnClicked();
    void sig_moreEffect();
public slots:
    void slt_playBtnClicked();
    void slt_stopBtnClicked();
    void slt_preBtnClicked();
    void slt_nextBtnClicked();
    void slt_rotatBtnClicked();
    void slt_moreEffect();
private:
    QPushButton *playBtn,*stopBtn,*preBtn,*nextBtn,*rotatBtn,*moreEffectBtn;
    QSlider *sizeSlider,*transparentSlider;
    QLabel *maxLabel,*smallLabel,*transparentLabel;
};

#endif // FUNCWIDGET_H
