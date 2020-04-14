#ifndef BATTERYICONLABEL_H
#define BATTERYICONLABEL_H

#include <QLabel>
#include <QPainter>
#include <QPair>
#include <QPixmap>

#include "sizes.h"

class BatteryIcon : public QLabel
{
    Q_OBJECT

public:
    BatteryIcon(QWidget *parent = 0);

    void updateIcon();

private:
    QPixmap batteryicons[4];

    void setBatteryIcon();
    QPair<int, bool> getBatteryState();
};

#endif  // BATTERYICONLABEL_H