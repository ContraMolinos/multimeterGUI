/*! \file lcd.cpp
*/
#include "lcd.h"

#include<QDebug>

/*! \brief LCD::LCD. Constructor
 * \param data
 * \param parent
 */
LCD::LCD(const RS22812 *data, QWidget *parent):QLabel(parent), data(data)
{
    if(parent!=NULL)
    {
        this->setGeometry(50,30,400,100);
        this->setStyleSheet("QLabel {background-color:white;}");
        this->setFrameShape(QLabel::Box);
        this->setLineWidth(2);
        this->setFrameShadow(QLabel::Raised);
    }
    else
    {
        this->setGeometry(30,50,400,100);
        this->setVisible(true);
    }
}

/*!
 * \brief LCD::paintEvent. Paint event handler.
 * \param event
 * It redraws the LCD widget every time there is an update.
 */
void LCD::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPen pen;
    QFont font=painter.font();
    QPoint unitPosition=this->geometry().bottomRight()-QPoint(font.SizeResolved*30,this->height()/3);
    QString units;
    QPoint stringPosition=this->geometry().bottomLeft()+QPoint(this->width()/5,-this->height()/4);

    Flags f=data->getFlags();
    //uint mode=data->getMode();
    QString sVal=data->getDigitString();
    if(f.tilde)
        sVal="~"+sVal;
    if(f.dash)
        sVal="-"+sVal;

    //First, all the flags are writen in light gray.
    pen.setColor(Qt::lightGray);
    painter.setPen(pen);
    int pos[lbl.length()];
    pos[0]=10;
    for(int i=1;i<lbl.length();i++)
        pos[i]=pos[i-1]+painter.fontMetrics().width(lbl[i-1])+7;


    for(int i=0;i<lbl.length();i++)
    {
        painter.drawText(pos[i],20,lbl[i]);
    }
    pen.setColor(Qt::black);
    painter.setPen(pen);
    // "Auto","RS232","Hold","Rel","MAX","MIN","hFE","dBm","Cont","Diode","%","S"
    if(f.Auto)  painter.drawText(pos[0],20,lbl[0]);
    if(f.RS232)  painter.drawText(pos[1],20,lbl[1]);
    if(f.Hold)  painter.drawText(pos[2],20,lbl[2]);
    if(f.REL)  painter.drawText(pos[3],20,lbl[3]);
    if(f.MAX)  painter.drawText(pos[4],20,lbl[4]);
    if(f.MIN)  painter.drawText(pos[5],20,lbl[5]);
    if(f.hFE)  painter.drawText(pos[6],20,lbl[6]);
    if(f.dBm)  painter.drawText(pos[7],20,lbl[7]);
    if(f.continuity)  painter.drawText(pos[8],20,lbl[8]);
    if(f.Diode)  painter.drawText(pos[9],20,lbl[9]);
    if(f.percent)  painter.drawText(pos[10],20,lbl[10]);
    if(f.s)  painter.drawText(pos[11],20,lbl[11]);

    font.setPointSize(16);
    painter.setFont(font);
    //Display the units.
    if(f.k) units="k";
    if(f.M) units="M";
    if(f.m) units="m";
    if(f.n) units="n";
    if(f.u) units=QChar(0x03BC);    //micro
    if(f.A) units+="A";
    if(f.dBm)   units+="dBm";
    if(f.F) units+="F";
    if(f.Hz)    units+="Hz";
    if(f.Ohms)  units+=QChar(0x03A9);
    if(f.V) units+="V";
    painter.drawText(unitPosition,units);
    font.setPointSize(36);
    painter.setFont(font);
    painter.drawText(stringPosition,sVal);

    QLabel::paintEvent(event);
}

