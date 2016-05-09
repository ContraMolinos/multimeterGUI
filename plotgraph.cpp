/*! \file plotgraph.cpp
*/

#include "plotgraph.h"
#include <QDebug>

/*!
 * \brief Override of the paint method of QGraphicsScene.
 * \param painter
 * \param option
 * \param widget
 */
void plotGraph::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    bRect=widget->rect();
    paintAxis(painter,option,widget);
    plotData(painter,option,widget);
    if(scene!=NULL)
        scene->setSceneRect(bRect);
    //qDebug()<<widget->accessibleName()<<widget->winId()<<widget->rect();
}

/*!
 * \brief Returns the bounding rectangle of the graph.
 * \return
 * So far, it returns a fake value. Need to implement.
 */
QRectF plotGraph::boundingRect() const
{
    return QRectF(0,0,100,100);
}

/*!
 * \brief Sets the maximum and minimum values of the x axis.
 * \param minVal
 * \param maxVal
 */
void plotGraph::setXaxis(qint64 minVal, qint64 maxVal)
{
    qint64 diff=maxVal-minVal;
    if(diff>0)
    {
        xmin=minVal;
        xmax=maxVal;
    }
    else
    {
        xmin=minVal;
        xmax=minVal+1;
    }
}

/*!
 * \brief Sets the maximum and minimum values of the y axis.
 * \param minVal
 * \param maxVal
 */
void plotGraph::setYaxis(qreal minVal, qreal maxVal)
{
    qreal diff=maxVal-minVal;
    if(diff>0)
    {
        ymin=minVal-0.01*fabs(minVal);
        ymax=maxVal+0.01*fabs(minVal);
    }
    else
    {
        ymin=minVal-1;
        ymax=minVal+1;
    }
}

/*!
 * \brief Selects the appropriate unit depending on the multimeter setting.
 * \param U
 */
void plotGraph::setUnit(int U)
{
    if(U==2||U==5||U==3||U==6)
    {
        unit="A";
        return;
    }
    if(U==0||U==1)
    {
        unit="V";
        return;
    }
    if(U==8)
    {
        unit=QChar(0x03A9);
        return;
    }
    if(U==9)
    {
        unit="F";
        return;
    }
    if(U==10)
    {
        unit="Hz";
        return;
    }
    if(U==23)
    {
        unit="dBm";
        return;
    }
    if(U==21)
    {
        unit="hFe";
        return;
    }
    else
    {
        unit="";
    }
}

/*!
 * \brief Calculates the scale and limits of the axis and draws it.
 * \param painter
 * \param option
 * \param widget
 */
void plotGraph::paintAxis(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen oldpen=painter->pen();
    QPen pen;
    pen.setWidth(2);
    painter->setPen(pen);
    upperY=bRect.topLeft()+QPoint(axisMargin+20,axisMargin);
    origin=bRect.bottomLeft()+QPoint(axisMargin+20,-axisMargin);
    rightX=bRect.bottomRight()-QPoint(axisMargin-20,axisMargin);
    QPoint p1,p2;

    //Y Axis
    painter->drawLine(origin,upperY);
    //X Axis
    painter->drawLine(origin,rightX);
    pen.setWidth(1);
    painter->setPen(pen);

    labelXaxis(painter, p1, p2);

    labelYaxis(painter,p1,p2);

    painter->setPen(oldpen);
}

/*!
 * \brief Draws the data on the widget.
 * \param painter
 * \param option
 * \param widget
 */
void plotGraph::plotData(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QList<QPoint> datPoint;
    QVector<QLineF> datLines;
    for(QList<QPair<qint64,qreal> >::const_iterator i=data->begin();i!=data->end();++i)
    {
        try
        {
            if((*i).first>=xmin)
                datPoint.append(real2Coord(*i));
        }catch(std::out_of_range e)
        {
            qWarning()<<e.what();
        }
    }
    if(datPoint.size()<2)
        return;
    for(QList<QPoint>::const_iterator i=datPoint.begin();i!=datPoint.end()-1;++i)
    {
        datLines.append(QLineF((*i),(*(i+1))));
    }
    painter->drawLines(datLines);
}

/*!
 * \brief Adds labels to the X axis.
 * \param painter
 * \param p1  QPoint variable that will hold the coordinates of the upper side of the tick lines.
 * \param p2  QPoint variable that will hold the coordinates of the lower side of the tick lines.
 */
void plotGraph::labelXaxis(QPainter *painter, QPoint &p1, QPoint &p2)
{

    QFontMetrics fm(painter->font());
    int step=static_cast<int>(round((xmax-xmin)/nx));
    for(int i=0;i<nx;++i)
    {
        p1=origin+QPoint(i*(rightX.x()-origin.x())/nx,0);
        p2=p1+QPoint(0,5);
        //Setting time in x axis
        qreal val;
        if(data->isEmpty())
            val=0;
        else
            val=xmin+i*step;
        QString str=QString::number(static_cast<float>(val)/1000,'f',2);
        painter->drawLine(p1,p2);
        painter->drawText(p2+QPoint(-fm.width(str)/2,fm.height()),str);
    }
    p1=origin+QPoint((rightX.x()-origin.x()),0);
    p2=p1+QPoint(0,5);
    painter->drawText(p2+QPoint(-10,20),"(s.)");
}

/*!
 * \brief Adds labels to the Y axis.
 * \param painter
 * \param p1  QPoint variable that will hold the coordinates of the right side of the tick lines.
 * \param p2  QPoint variable that will hold the coordinates of the left side of the tick lines.
 */
void plotGraph::labelYaxis(QPainter *painter, QPoint &p1, QPoint &p2)
{
    QVector<QString> labels;
    painter->setFont(QFont(painter->font().toString(),8));
    QFontMetrics fm(painter->font());
    int exponent=0;
    int maxWidth=0;
    qreal absmax=std::max(fabs(ymax),fabs(ymin));
    if(absmax>9999)
        exponent=floor(log10(absmax))-1;
    else if(absmax<1)
        exponent=floor(log10(absmax));

    for(int i=0;i<ny+1;i++)
    {
        labels.push_back(QString::number((ymin+i*(ymax-ymin)/ny)/pow(10,exponent),'f',3));
        int w=fm.width(labels.back());
        if(w>maxWidth)
            maxWidth=w;
    }
    for(int i=0;i<ny+1;i++)
    {
        p1=origin+QPoint(0,i*(upperY.y()-origin.y())/ny);
        p2=p1-QPoint(5,0);
        painter->drawLine(p1,p2);
        painter->drawText(p2+QPoint(-maxWidth-3,fm.height()/3),labels.at(i));
    }

    if(exponent!=0)
    {
        painter->drawText(p2+QPoint(-maxWidth,-fm.height()),QString("x10"));
        painter->setFont(QFont(painter->font().toString(),6));
        painter->drawText(p2+QPoint(-maxWidth+fm.width("x10"),-fm.height()-5),QString::number(exponent));
    }

    painter->setFont(QFont(painter->font().toString(),8));
    painter->drawText(p2+QPoint(-maxWidth+fm.width("x10")+10,-fm.height()),unit);
}

/*!
 * \brief Transforms reading coordinates to widget coordinates.
 * \param dpoint
 * \return
 */
QPoint plotGraph::real2Coord(const QPair<qreal, qreal> dpoint)
{
    QPoint coord;
    int x,y;
    x=round((dpoint.first-xmin)/(xmax-xmin)*(rightX.x()-origin.x()))+origin.x();
    y=origin.y()-round((dpoint.second-ymin)/(ymax-ymin)*(origin.y()-upperY.y()));
    //The value is out of range.
    if(x<origin.x()||y<upperY.y()||x>rightX.x()||y>origin.y())
    {
        QString error="Value out of range: "+QString::number(dpoint.first)+","+QString::number(dpoint.second)+
                " ("+QString::number(origin.x())+","+QString::number(origin.y())+") "+
                " ("+QString::number(upperY.y())+","+QString::number(rightX.x())+") ->"
                "("+QString::number(x)+","+QString::number(y)+")";
        throw std::out_of_range(error.toStdString());
    }

    coord=QPoint(x,y);
    return coord;

}

