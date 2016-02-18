#include "rs22812.h"
#include <QDebug>

RS22812::RS22812(QObject *parent) : QObject(parent)
{
    mode=0;
    resetFlags();
}

/*!
 * \brief RS22812::getVal
 * Returns the numeric value of the reading.
 * \return
 */
float RS22812::getVal() const
{
    float val;
    bool isNumber;
    val=digits.toFloat(&isNumber);
    if(!isNumber)
    {
        qDebug()<<digits;
        throw "No number.";
    }
    if(flags.dash)
        val=-val;
    return val;
}

Flags RS22812::getFlags() const
{
    return flags;
}

QString RS22812::getDigitString() const
{
    return digits;
}

uint RS22812::getMode() const
{
    return mode;
}

/*!
 * \brief RS22812::byte2Digit
 * Translates the RS 22-812 byte value of the LCD mapping into a digit.
 * \param byte  RS 22-812 byte value
 * \return  String with the equivalent digit.
 */
QString RS22812::byte2Digit(uchar byte)
{
    QString digit;
    switch(byte)
    {
    case 215:
        digit="0";
        break;
    case 80:
        digit="1";
        break;
    case 181:
        digit="2";
        break;
    case 241:
        digit="3";
        break;
    case 114:
        digit="4";
        break;
    case 227:
        digit="5";
        break;
    case 231:
        digit="6";
        break;
    case 81:
        digit="7";
        break;
    case 247:
        digit="8";
        break;
    case 243:
        digit="9";
        break;
    case 39:
        digit="F";
        break;
    case 55:
        digit="P";
        break;
    case 167:
        digit="E";
        break;
    case 135:
        digit="C";
        break;
    case 134:
        digit="L";
        break;
    case 118:
        digit="H";
        break;
    case 6:
        digit="I";
        break;
    case 102:
        digit="h";
        break;
    case 36:
        digit="r";
        break;
    case 166:
        digit="t";
        break;
    case 100:
        digit="n";
        break;
    case 32:
        digit="-";
        break;
    case 0:
        digit=" ";
        break;
    default:
        //Throw error
        throw "Unknown conversion to digit.";
    }

    return digit;
}

/*!
 * \brief RS22812::resetFlags
 * Set all the flags to false.
 */
void RS22812::resetFlags()
{
    flags.Hz=false;
    flags.Ohms=false;
    flags.k=false;
    flags.M=false;
    flags.F=false;
    flags.A=false;
    flags.V=false;
    flags.m=false;
    flags.u=false;
    flags.n=false;
    flags.dBm=false;
    flags.s=false;
    flags.percent=false;
    flags.hFE=false;
    flags.REL=false;
    flags.MIN=false;
    flags.Beep=false;
    flags.Diode=false;
    flags.continuity=false;
    flags.Bat=false;
    flags.Hold=false;
    flags.dash=false;
    flags.tilde=false;
    flags.RS232=false;
    flags.Auto=false;
    flags.MAX=false;
    flags.DP=0;
    flags.checksum=0;
}

/*!
 * \brief RS22812::newValue Reads a new packet and reformats the data.
 * \param data
 */
void RS22812::newValue(const QByteArray &data)
{
    resetFlags();
    int dataLength=data.size();
    uchar byte;
    uint checksum=0;
    if(dataLength==9)
    {
        digits.clear();
        flags.DP=0;
        for(int i=0;i<8;i++)
        {
            byte=(uint)data[i]&0xff;   //8 bits mask
            checksum+=byte;
            if(i==0)
            {
                mode=byte;
            }
            if(i==1)
            {
                flags.m=(byte&0x01);
                flags.V=((byte>>1)&0x01);
                flags.A=((byte>>2)&0x01);
                flags.F=((byte>>3)&0x01);
                flags.M=((byte>>4)&0x01);
                flags.k=((byte>>5)&0x01);
                flags.Ohms=((byte>>6)&0x01);
                flags.Hz=((byte>>7)&0x01);
            }
            if(i==2)
            {
                flags.MIN=(byte&0x01);
                flags.REL=((byte>>1)&0x01);
                flags.hFE=((byte>>2)&0x01);
                flags.percent=((byte>>3)&0x01);
                flags.s=((byte>>4)&0x01);
                flags.dBm=((byte>>5)&0x01);
                flags.n=((byte>>6)&0x01);
                flags.u=((byte>>7)&0x01);
            }
            if(i>2&&i<7)
            {
                if(i<6)
                {
                    flags.DP+=(i-2)*((byte>>3)&0x01);   //Set the position of the decimal point.
                }
                else
                    flags.MAX=((byte>>3)&0x01);
                byte=(byte&0x0f7);  //Mask the bit position 3
                try
                {
                    digits=byte2Digit(byte)+digits;
                }catch(...)
                {
                    qDebug()<<"Wrong conversion "<<QString::number(byte,16)<<" "<<((byte>>3)&0x01);
                }
            }
            if(i==7)
            {
                flags.Auto=(byte&0x01);
                flags.RS232=((byte>>1)&0x01);
                flags.tilde=((byte>>2)&0x01);
                flags.dash=((byte>>3)&0x01);
                flags.Hold=((byte>>4)&0x01);
                flags.Bat=((byte>>5)&0x01);
                flags.Diode=((byte>>6)&0x01);
                flags.Beep=((byte>>7)&0x01);
            }
        }
        flags.checksum=((data.at(8) & 0x0ff)==((checksum+57)& 0x0ff));
    }else
    {
        qDebug()<<"Wrong length "<<data;
    }
    if(flags.DP>0&&digits.size()>0) //If there is a decimal point, insert it in the appropriate position.
    {
        digits.insert(digits.size()-flags.DP,".");
    }
    if(mode==20)    flags.continuity=true;
    else    flags.continuity=false;
    //Checks if flags changed.
//    if(flags!=oldflags)
//    {
//        emit flagsChanged(flags);
//        oldflags=flags;
//    }
    emit newData();
}


