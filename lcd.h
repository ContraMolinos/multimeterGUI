/*! Multimeter GUI
 * GUI for the RS-232 mode of the Radio Shack 22-812.
   Copyright (C) 2016  FJ Salguero

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef LCD_H
#define LCD_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QPainter>
#include <QVector>
#include <QFontMetrics>
#include "rs22812.h"

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
