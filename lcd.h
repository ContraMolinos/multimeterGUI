#ifndef LCD_H
#define LCD_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QPainter>
#include <QVector>
#include <QFontMetrics>
#include "rs22812.h"

/*! \class LCD
 * \brief The LCD class displays the numerical value read.
 *
 * This class will show a representation of the multimeter's display showing the same values that are shown in the multimeter.
 */
class LCD : public QLabel
{
    Q_OBJECT

public:
    explicit LCD(const RS22812 *data,QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *event);

private:
    const QVector<QString> lbl={"Auto","RS232","Hold","Rel","MAX","MIN","hFE","dBm","Cont","Diode","%","S"};
    const RS22812 *data;
};

#endif // LCD_H
