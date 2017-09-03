#ifndef MOREEFFECT_H
#define MOREEFFECT_H

#include <QWidget>
#include "head.h"

class moreeffect : public QWidget
{
    Q_OBJECT
public:
    explicit moreeffect(QWidget *parent = 0);
    ~moreeffect();
    void initWidget();


signals:
     void sig_greyClicked();
     void sig_lightenClicked();
     void sig_warmClicked();
     void sig_coldClicked();
     void sig_saturationClicked();

public slots:
     void slt_greyClicked();
     void slt_lightClicked();
     void slt_warmClicked();
     void slt_coldClicked();
     void slt_saturationClicked();

private:
   QPushButton *greyBtn,*lightenBtn,*warmBtn,*coldBtn,*saturationBtn;
};

#endif // MOREEFFECT_H
