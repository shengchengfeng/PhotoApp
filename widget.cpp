#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    initWidget();
    initHeadWid();
    initFuncWid();
    initScreenShotWidget();
    initMoreEffect();

    showPhoto();

    connect(headWid,SIGNAL(sig_minBtnClicked()),this,SLOT(slt_minWidget()));
    connect(headWid,SIGNAL(sig_closeBtnClicked()),this,SLOT(close()));
    connect(headWid,SIGNAL(sig_openBtnClicked()),this,SLOT(slt_choosePhoto()));
    connect(headWid,SIGNAL(sig_saveBtnClicked()),this,SLOT(slt_saveImage()));
    connect(headWid,SIGNAL(sig_settingBtnClicked()),this,SLOT(slt_settingWidget()));

    connect(funcWid,SIGNAL(sig_playBtnClicked()),this,SLOT(slt_timeOut()));
    connect(funcWid,SIGNAL(sig_stopBtnClicked()),this,SLOT(slt_stopTimer()));
    connect(funcWid,SIGNAL(sig_preBtnClicked()),this,SLOT(slt_preBtnClicked()));
    connect(funcWid,SIGNAL(sig_nextBtnClicked()),this,SLOT(slt_nextBtnClicked()));
    connect(funcWid->getSizeSlider(),SIGNAL(valueChanged(int)),this,SLOT(slt_changeSize(int)));
    connect(funcWid->getTransparentSlider(),SIGNAL(valueChanged(int)),this,SLOT(slt_changeTransparent(int)));
    connect(funcWid,SIGNAL(sig_rotatBtnClicked()),this,SLOT(slt_changeRotat()));
    connect(funcWid,SIGNAL(sig_moreEffect()),this,SLOT(slt_moreEffect()));

    connect(moreEffectWidget,SIGNAL(sig_greyClicked()),this,SLOT(slt_changeGrey()));
    connect(moreEffectWidget,SIGNAL(sig_lightenClicked()),this,SLOT(slt_changeLighten()));
    connect(moreEffectWidget,SIGNAL(sig_warmClicked()),this,SLOT(slt_changeWarm()));
    connect(moreEffectWidget,SIGNAL(sig_coldClicked()),this,SLOT(slt_changeCold()));
    connect(moreEffectWidget,SIGNAL(sig_saturationClicked()),this,SLOT(slt_changeSaturation()));
}


Widget::~Widget()
{

}

void Widget::initWidget()
{
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setFixedSize(1000,800);
    this->move((QApplication::desktop()->width()-this->width())/2,(QApplication::desktop()->height()-this->height())/2);
    mDragWindow=false;

    photoLabel=new QLabel(this);
    photoLabel->resize(1000,600);
    photoLabel->move(0,80);
    photoLabel->setStyleSheet("background-color:#FFE1FF");

    QDir dir(QApplication::applicationDirPath()+QString(dir.separator())+"photo");
    QList<QFileInfo> *fileInfo=new QList<QFileInfo>(dir.entryInfoList());
    for(int i=2;i<fileInfo->count();i++)
    {
        photoNames<<fileInfo->at(i).absoluteFilePath();
    }
    photoIndex=0;
    timer=new QTimer(this);
    timeInterval=2000;
    rotatNum=90;

    connect(timer,SIGNAL(timeout()),this,SLOT(slt_timeOut()));
}

void Widget::initHeadWid()
{
     headWid=new headWidget(this);

}

void Widget::initFuncWid()
{
    funcWid=new funcWidget(this);
}

void Widget::initScreenShotWidget()
{
    screenShotWidget=new screenShot();

    for(int i=0;i<photoNames.size();++i)
    {
        QPixmap photoPixmap(photoNames[i]);
        QListWidgetItem *photoItem=new QListWidgetItem(QIcon(photoPixmap.scaled(200,150,Qt::IgnoreAspectRatio,Qt::SmoothTransformation)),"",screenShotWidget->getPhotoListWidget());
        photoItem->setSizeHint(QSize(200,150));
        screenShotWidget->getPhotoListWidget()->insertItem(i,photoItem);
    }
    screenShotWidget->show();
    connect(screenShotWidget,SIGNAL(sig_photoItemClick(int)),this,SLOT(slt_itemClick(int)));
    connect(this,SIGNAL(sig_setItemIndex(int)),screenShotWidget,SLOT(slt_setCurrentRow(int)));
}

void Widget::initMoreEffect()
{
    moreEffectWidget=new moreeffect();
}

void Widget::showPhoto()
{
    img.load(photoNames[photoIndex]);
    if((img.height()>photoLabel->height())||(img.width()>photoLabel->width()))
    {
        QImage tempImg=img.scaled(photoLabel->width(),photoLabel->height(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
        img=tempImg;
    }
    photoLabel->setPixmap(QPixmap::fromImage(img));
    photoLabel->setAlignment(Qt::AlignCenter);
}

void Widget::setBtnsCanClick()
{
    headWid->getOpenBtn()->setEnabled(true);
    headWid->getSaveBtn()->setEnabled(true);
    headWid->getSettingBtn()->setEnabled(true);

    funcWid->getPreBtn()->setEnabled(true);
    funcWid->getNextBtn()->setEnabled(true);
    funcWid->getSizeSlider()->setEnabled(true);
    funcWid->getTransparentSlider()->setEnabled(true);
    funcWid->getRotatBtn()->setEnabled(true);
}

void Widget::setBtnsCanNotClick()
{
    headWid->getOpenBtn()->setEnabled(false);
    headWid->getSaveBtn()->setEnabled(false);
    headWid->getSettingBtn()->setEnabled(false);

    funcWid->getPreBtn()->setEnabled(false);
    funcWid->getNextBtn()->setEnabled(false);
    funcWid->getSizeSlider()->setEnabled(false);
    funcWid->getTransparentSlider()->setEnabled(false);
    funcWid->getRotatBtn()->setEnabled(false);
}

void Widget::hideMoreEffectWidget()
{
    moreEffectWidget->hide();
}

void Widget::setSliders()
{
    funcWid->getSizeSlider()->setValue(100);
    funcWid->getTransparentSlider()->setValue(100);
}

void Widget::slt_timeOut()
{
    hideMoreEffectWidget();
    setBtnsCanNotClick();

    timer->start(timeInterval);
    slt_nextBtnClicked();
}

void Widget::slt_stopTimer()
{
    if(timer->isActive())
    {
        timer->stop();
        setBtnsCanClick();
    }
}

void Widget::slt_preBtnClicked()
{
    setSliders();
    hideMoreEffectWidget();

    photoIndex-=1;
    if(photoIndex==-1)
    {
        photoIndex=photoNames.size()-1;
    }
    emit sig_setItemIndex(photoIndex);
    showPhoto();
}

void Widget::slt_nextBtnClicked()
{
    setSliders();
    hideMoreEffectWidget();

    photoIndex+=1;
    if(photoIndex==photoNames.size())
    {
        photoIndex=0;
    }
    emit sig_setItemIndex(photoIndex);
    showPhoto();
}

void Widget::slt_changeSize(int num)
{
    hideMoreEffectWidget();

    QImage tempImg=img.scaled(photoLabel->width()*num/100,photoLabel->height()*num/100,Qt::KeepAspectRatio,Qt::SmoothTransformation);
    photoLabel->setPixmap(QPixmap::fromImage(tempImg));
    photoLabel->setAlignment(Qt::AlignCenter);
}

void Widget::slt_changeTransparent(int num)
{
    hideMoreEffectWidget();

    QImage tempImg=img;
    QColor bgcolor=palette().color(QPalette::Window);
    float v=0.01*num;
    int width=img.width(),height=img.height();

    for(int h=0;h<height;h++)
    {
        for(int w=0;w<width;w++)
        {
            int alpha=qAlpha(img.pixel(w,h));
            if(alpha==0)
            {
                int red=qRed(bgcolor.rgb());
                int green=qGreen(bgcolor.rgb());
                int blue=qBlue(bgcolor.rgb());
                tempImg.setPixel(w,h,qRgb(red,green,blue));

            }
            else
            {
                int red=(int)((qRed(bgcolor.rgb()))*(1-v)+(qRed(img.pixel(w,h)))*v);
                int green=(int)((qGreen(bgcolor.rgb()))*(1-v)+(qGreen(img.pixel(w,h)))*v);
                int blue=(int)((qBlue(bgcolor.rgb()))*(1-v)+(qBlue(img.pixel(w,h)))*v);
                tempImg.setPixel(w,h,qRgb(red,green,blue));
            }
        }
    }
    photoLabel->setPixmap(QPixmap::fromImage(tempImg));
    photoLabel->setAlignment(Qt::AlignCenter);
}

void Widget::slt_changeRotat()
{
    hideMoreEffectWidget();

    matrix.rotate(rotatNum);
    QImage tempImg= img.transformed(matrix);
    photoLabel->setPixmap(QPixmap::fromImage(tempImg));
    photoLabel->setAlignment(Qt::AlignCenter);
}

void Widget::slt_choosePhoto()
{
    hideMoreEffectWidget();

    QStringList tempPhotoNames=QFileDialog::getOpenFileNames(this,tr("请选择图片"),qApp->applicationDirPath(),tr("Images (*.png *.bmp *.jpg)"));
    if(tempPhotoNames.size()>0)
    {
       // qDebug()<<"选择了"<<photoNames.size()<<"张图片"<<endl;
        if(timer->isActive())
        {
            timer->stop();
        }
        photoIndex=0;
        photoNames=tempPhotoNames;
        showPhoto();
        screenShotWidget->close();
        initScreenShotWidget();
    }
    else
    {
        qDebug()<<tempPhotoNames.size();
        QMessageBox::information(this,tr("提示"),tr("没有选中任何图片"));
    }
}

void Widget::slt_saveImage()
{
    QString newFileName = QFileDialog::getSaveFileName(this,tr("Save Image"),"./",tr("Images (*.png *.bmp *.jpg)"));
    if(newFileName.isEmpty())
    {
        QMessageBox::information(this,"提示","您放弃了保存！");
        return;
    }
    qDebug()<<newFileName;

    const QPixmap *savePix=photoLabel->pixmap();
    qDebug()<<savePix->save(newFileName);
}

void Widget::slt_moreEffect()
{
    moreEffectWidget->show();
}

void Widget::slt_changeGrey()
{
    /*
    我们要学习的第一个技术就是将彩色图转换成灰度图，我们首先要明白的一点就是，其实标准的灰度图就是每个像素点的
    三个通道的值一样或者近似，我们的策略就是将每个像素的每个通道的值都调成一样，取R,G,B值为三者的算数平均数就
    可以了，比如原色是RGB(169,204,69), 那么最终的RGB就是（169+204+69）/3 = 147.
    */
    QImage * newImage = new QImage(img.width(), img.height(), QImage::Format_ARGB32);
    QColor oldColor;
    for(int x = 0; x<newImage->width(); x++)
    {
          for(int y = 0; y<newImage->height(); y++)
          {
                oldColor = QColor(img.pixel(x,y));
                int average = (oldColor.red()+oldColor.green()+oldColor.blue())/3;
                newImage->setPixel(x,y,qRgb(average,average,average));
          }
    }
    photoLabel->setPixmap(QPixmap::fromImage(*newImage));
    photoLabel->setAlignment(Qt::AlignCenter);
}

void Widget::slt_changeLighten()
{
    /*
    就如之前我们提到的，白色用RGB(255,255,255)表示，黑色用RGB(0,0,0)表示，所以如果我们需要提高图片的亮度
   （颜色接近白色），我们需要同时增加三个通道的数值，反之就是变暗。
    在这里我们添加了一个函数参数来决定要提高多少亮度，如果参数是负数的话就是减少亮度了。
    在每个通道都加上delta值之后，需要做的就是让它不要低于0且不要高于255.
    */
    QImage * newImage = new QImage(img.width(), img.height(), QImage::Format_ARGB32);
    QColor oldColor;
    int newRed,newGreen,newBlue;
    for(int x = 0; x<newImage->width(); x++)
    {
          for(int y = 0; y<newImage->height(); y++)
          {
                oldColor = QColor(img.pixel(x,y));
                 newRed=oldColor.red()+lightenNum;
                 newGreen=oldColor.green()+lightenNum;
                 newBlue=oldColor.blue()+lightenNum;

                newRed=qBound(0,newRed,255);
                newGreen=qBound(0,newGreen,255);
                newBlue=qBound(0,newBlue,255);
                newImage->setPixel(x,y,qRgb(newRed,newGreen,newBlue));
          }
    }
    photoLabel->setPixmap(QPixmap::fromImage(*newImage));
    photoLabel->setAlignment(Qt::AlignCenter);
}

void Widget::slt_changeCold()
{
    /*
    当我们说一一幅暖色调的图片的时候通常是因为这张图色调偏黄。我们没有黄色的通道，但是红色和绿色混合起来就是黄色，
    所以我们增加这两个通道值，然后蓝色通道值不变就好了
    */
    QImage * newImage = new QImage(img.width(), img.height(), QImage::Format_ARGB32);
    QColor oldColor;
    int newBlue;
    for(int x = 0; x<newImage->width(); x++)
    {
          for(int y = 0; y<newImage->height(); y++)
          {
                oldColor = QColor(img.pixel(x,y));

                newBlue=oldColor.blue()+coldAndWarmNum;
                newBlue=qBound(0,newBlue,255);

                newImage->setPixel(x,y,qRgb(oldColor.red(),oldColor.green(),newBlue));
          }
    }

    photoLabel->setPixmap(QPixmap::fromImage(*newImage));
    photoLabel->setAlignment(Qt::AlignCenter);
}

void Widget::slt_changeWarm()
{
    /*
    如果说暖色调的图片偏黄色，那么冷色调的图片应该就是偏蓝色了。在这个方法里面我们只增加蓝色通道的值，红色和绿色的值不变。
    冷色调的图片可以联想到未来，死亡或者，冷。*/
    QImage * newImage = new QImage(img.width(), img.height(), QImage::Format_ARGB32);
    QColor oldColor;
    int newRed,newGreen;
    for(int x = 0; x<newImage->width(); x++)
    {
          for(int y = 0; y<newImage->height(); y++)
          {
                oldColor = QColor(img.pixel(x,y));

                newRed=oldColor.red()+coldAndWarmNum;
                newGreen=oldColor.green()+coldAndWarmNum;

                newRed=qBound(0,newRed,255);
                newGreen=qBound(0,newGreen,255);

                newImage->setPixel(x,y,qRgb(newRed,newGreen,oldColor.blue()));
          }
    }
    photoLabel->setPixmap(QPixmap::fromImage(*newImage));
    photoLabel->setAlignment(Qt::AlignCenter);
}

void Widget::slt_changeSaturation()
{
    QImage * newImage = new QImage(img.width(), img.height(), QImage::Format_ARGB32);

    QColor oldColor;
    QColor newColor;
    int h,s,l;
    //颜色由三个通道组成：红，绿，蓝，尽管如此，RGB不是唯一一个表示色彩的方式
    //在这里，我们使用HSL格式表示色彩 - hue（色相）, saturation（饱和度）, lightness（明度）
    for(int x=0; x<newImage->width(); x++)
    {
        for(int y=0; y<newImage->height(); y++)
        {
            oldColor = QColor(img.pixel(x,y));

            newColor = oldColor.toHsl();
            h = newColor.hue();
            s = newColor.saturation()+saturationNum;
            l = newColor.lightness();

            s = qBound(0, s, 255);
            newColor.setHsl(h, s, l);
            newImage->setPixel(x, y, qRgb(newColor.red(), newColor.green(), newColor.blue()));
        }
    }

    photoLabel->setPixmap(QPixmap::fromImage(*newImage));
    photoLabel->setAlignment(Qt::AlignCenter);
}

void Widget::closeEvent(QCloseEvent *event)
{
    screenShotWidget->close();
    moreEffectWidget->close();
}

void Widget::slt_minWidget()
{
    this->showMinimized();
}

void Widget::slt_settingWidget()
{
    settingWid=new settingWidget();

    settingWid->getTimerIntervalSpinBox()->setValue(timeInterval/1000);
    settingWid->getRotatNumSpinBox()->setValue(qAbs(rotatNum));
    if(rotatNum>0)
    {
        settingWid->getLeftRadioBtn()->setChecked(true);
    }
    else
    {
         settingWid->getRightRadioBtn()->setChecked(true);
    }
    settingWid->getLightSpinBox()->setValue(lightenNum);
    settingWid->getColdAndWarmSpinBox()->setValue(coldAndWarmNum);
    settingWid->getSaturationSpinBox()->setValue(saturationNum);
    settingWid->show();

    connect(settingWid,SIGNAL(sig_okBtnClicked()),this,SLOT(slt_okSettting()));
}

void Widget::slt_okSettting()
{
    timeInterval=settingWid->getTimerIntervalSpinBox()->value()*1000;
    rotatNum=settingWid->getRotatNumSpinBox()->value();
    if(settingWid->getLeftRadioBtn()->isChecked())
    {
        rotatNum=rotatNum;
    }
    else
    {
        rotatNum=-rotatNum;
    }
    lightenNum=settingWid->getLightSpinBox()->value();
    coldAndWarmNum=settingWid->getColdAndWarmSpinBox()->value();
    saturationNum=settingWid->getSaturationSpinBox()->value();

    settingWid->close();
}

void Widget::slt_itemClick(int index)
{
    photoIndex=index;
    showPhoto();
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    if (mDragWindow && (event->buttons() && Qt::LeftButton))
    {
        this->move(event->globalPos() - mousePoint);
        event->accept();
    }
}

void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    mDragWindow=false;
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    int mouseX=event->x(),mouseY=event->y();
    if((mouseX>=0&&mouseX<=1000) && (mouseY>=0&&mouseY<=80))
    {
        if(event->button()==Qt::LeftButton)
        {
            mousePoint=event->globalPos()-this->pos();
            event->accept();
            mDragWindow=true;
        }
    }
}
