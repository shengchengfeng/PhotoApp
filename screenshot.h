#ifndef SCREENSHOT_H
#define SCREENSHOT_H

#include <QWidget>
#include "head.h"

class screenShot : public QWidget
{
    Q_OBJECT
public:
    explicit screenShot(QWidget *parent = 0);
    ~screenShot();
    QListWidget* getPhotoListWidget();

    void initWidget();
signals:
    void sig_photoItemClick(int);

public slots:
    void slt_itemClick(int index);
    void slt_setCurrentRow(int raw);
    void slt_minBtnClick();
    void slt_hideBtnClick();
private:
    QListWidget *photoListWidget;
    QPushButton *minBtn,*hideBtn;
    int count;
};

#endif // SCREENSHOT_H
