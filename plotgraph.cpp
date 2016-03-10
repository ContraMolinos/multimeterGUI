#include "plotgraph.h"
#include <QDebug>

plotGraph::plotGraph()
{

}

/*!
 * \brief plotGraph::paint
 * \param painter
 * \param option
 * \param widget
 */
void plotGraph::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //qDebug()<<"Paint "<<xmin<<","<<xmax<<"  "<<ymin<<","<<ymax;
    bRect=widget->rect();
    paintAxis(painter,option,widget);
    plotData(painter,option,widget);
}

//So far, it returns a fake value. Need to implement.
QRectF plotGraph::boundingRect() const
{
    return QRectF(0,0,100,100);
}

void plotGraph::setXaxis(qreal minVal, qreal maxVal)
{
    qreal diff=maxVal-minVal;
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

void plotGraph::setYaxis(qreal minVal, qreal maxVal)
{
    qreal diff=maxVal-minVal;
    if(diff>0)
    {
        ymin=minVal-0.01*diff;
        ymax=maxVal+0.01*diff;
    }
    else
    {
        ymin=minVal-1;
        ymax=minVal+1;
    }
}

void plotGraph::setXsticks(int nSticks)
{
    nx=nSticks;
}

void plotGraph::setYsticks(int nSticks)
{
    ny=nSticks;
}

void plotGraph::linkData(const QVector<QPair<qreal, qreal> > *dat)
{
    data=dat;
}

/*!
 * \brief plotGraph::paintAxis
 * Calculates the scale and limits of the axis and draws it.
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

    //Labels and sticksfor the X axis.
    for(int i=0;i<nx+1;i++)
    {
        p1=origin+QPoint(i*(rightX.x()-origin.x())/nx,0);
        p2=p1+QPoint(0,5);
        //So far, x axis is reading number, not time.
        QString str=QString::number(round(xmin+i*(xmax-xmin)/nx),'f',0);
        QFontMetrics fm(painter->font());
        painter->drawLine(p1,p2);
        painter->drawText(p2+QPoint(-fm.width(str)/2,fm.height()),str);
    }

    //Labels and sticks for the y axis.
    for(int i=0;i<ny+1;i++)
    {
        p1=origin+QPoint(0,i*(upperY.y()-origin.y())/ny);
        p2=p1-QPoint(5,0);
        QString str=QString::number(ymin+i*(ymax-ymin)/ny,'f',2);
        painter->setFont(QFont(painter->font().toString(),8));
        QFontMetrics fm(painter->font());
        painter->drawLine(p1,p2);
        painter->drawText(p2+QPoint(-fm.width(str)-3,fm.height()/3),str);
    }

    painter->setPen(oldpen);
}

/*!
 * \brief plotGraph::plotData
 * Draws the data on the widget.
 * \param painter
 * \param option
 * \param widget
 */
void plotGraph::plotData(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QVector<QPoint> datPoint;
    QVector<QLineF> datLines;
    for(QVector<QPair<qreal,qreal> >::const_iterator i=data->begin();i!=data->end();++i)
    {
        try
        {
        datPoint.append(real2Coord(*i));
        }catch(std::out_of_range e)
        {
            qWarning()<<e.what();
        }
        //painter->drawPoint(datPoint);
    }
    if(datPoint.size()<2)
        return;
    for(QVector<QPoint>::const_iterator i=datPoint.begin();i!=datPoint.end()-1;++i)
    {
        datLines.append(QLineF((*i),(*(i+1))));
    }
    painter->drawLines(datLines);
}

/*!
 * \brief plotGraph::real2Coord
 * Transform reading coordinates to widget coordinates.
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
        QString error="Value out of range:"+QString::number(dpoint.first)+","+QString::number(dpoint.second)+
                " ("+QString::number(origin.x())+","+QString::number(origin.y())+") "+
                " ("+QString::number(upperY.y())+","+QString::number(rightX.x())+") ->"
                "("+QString::number(x)+","+QString::number(y)+")";
        throw std::out_of_range(error.toStdString());
    }

    coord=QPoint(x,y);
    //qDebug()<<dpoint<<" "<<coord<<" x=["<<origin.x()<<"-"<<rightX.x()<<"]; y=["<<upperY.y()<<"-"<<origin.y()<<"]";
    //qDebug()<<xmin<<","<<xmax<<"   "<<ymin<<","<<ymax;
    return coord;

}

