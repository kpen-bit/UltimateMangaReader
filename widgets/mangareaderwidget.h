#ifndef MANGAREADERWIDGET_H
#define MANGAREADERWIDGET_H

#include <QWidget>
#include "mangainfo.h"

namespace Ui {
class MangaReaderWidget;
}

class MangaReaderWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MangaReaderWidget(QWidget *parent = 0);
    ~MangaReaderWidget();

    void showImage(const QString &path);
    void updateReaderLabels(MangaInfo *currentmanga);

    void setFrontLightPanelState(int lightmin, int lightmax, int light, int comflightmin, int comflightmax, int comflight);


public slots:
    void addImageToCache(const QString &path);
    void updateTime();

signals:
    void changeView(int page);
    void advancPageClicked(bool direction);
    void closeApp();
    void back();
    void frontlightchanged(int light, int comflight);

private slots:
    void on_pushButtonReaderHome_clicked();
    void on_pushButtonReaderBack_clicked();
    void on_pushButtonReaderClose_clicked();

    void on_mangaImageContainer_clicked(QPoint pos);
    void on_horizontalSliderLight_valueChanged(int value);

    void on_horizontalSliderComfLight_valueChanged(int value);

private:
    Ui::MangaReaderWidget *ui;

    void adjustSizes();

    QList<QPixmap *> imgcache;
    QList<QString> imgcachepaths;
};

#endif // MANGAREADERWIDGET_H
