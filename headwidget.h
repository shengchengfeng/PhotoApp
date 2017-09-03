#ifndef HEADWIDGET_H
#define HEADWIDGET_H

#include <QWidget>
#include "head.h"
class headWidget : public QWidget
{
    Q_OBJECT
public:
    explicit headWidget(QWidget *parent = 0);
    ~headWidget();
    void initWidget();
    QPushButton* getOpenBtn();
    QPushButton* getSaveBtn();
    QPushButton* getSettingBtn();
protected:
    void paintEvent(QPaintEvent *e);

signals:
    void sig_openBtnClicked();
    void sig_saveBtnClicked();
    void sig_settingBtnClicked();
    void sig_minBtnClicked();
    void sig_closeBtnClicked();
public slots:
    void slt_openBtnClicked();
    void slt_saveBtnClicked();
    void slt_settingBtnClicked();
    void slt_minBtnClicked();
    void slt_closeBtnClicked();
private:
    QPushButton *openBtn,*saveBtn;
    QPushButton *settingBtn,*minBtn,*closeBtn;
};

#endif // HEADWIDGET_H
