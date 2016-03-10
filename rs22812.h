/*!
  RS22812
  Decoding of the data sent by the Radio Shack 22-812.
  Part of the information was obtained from http://sigrok.org/wiki/RadioShack_22-812
  and https://code.google.com/archive/p/rs22812/

  RS 22-812 sends 9bytes packets. Each packect is a mapping of the LCD of the screen
  plus some extra information.
                                       Bit
    Byte    7       6       5       4       3       2       1       0
    0       ---------------------- Mode -----------------------------
    1       Hz      Ohms    K       M       F       A       V       m
    2       u       n       dBm     s       %       hFE     REL     MIN
    3       4D      4C      4G      4B      DP3     4E      4F      4A
    4       3D      3C      3G      3B      DP2     3E      3F      3A
    5       2D      2C      2G      2B      DP1     2E      2F      2A
    6       1D      1C      1G      1B      MAX     1E      1F      1A
    7       Beep    Diode   Bat     Hold    -       ~       RS232   Auto
    8       -------------------- Checksum ---------------------------

    The LED mapping is:
    |--A--|
    |     |
    F     B
    |     |
    |--G--|
    |     |
    E     C
    |     |
    |--D--|

    So, the equivalence between int value and digit are:
    215 : "0", 80 : "1", 181 : "2", 241 : "3", 114 : "4",
    227 : "5", 231 : "6", 81 : "7", 247 : "8", 243 : "9", 39 : "F",
    55 : "P", 167 : "E", 135 : "C", 134 : "L", 118 : "H", 6 : "I",
    102 : "h", 36 : "r", 166 : "t", 100 : "n", 32 : "-", 0 : " "

    And the possible modes are:
    0=DC V       1=AC V    2=DC uA
    3=DC mA      4=DC A    5=AC uA
    6=AC mA      7=AC A    8=OHM
    9=CAP        10=HZ     11=NET HZ
    12=AMP HZ    13=DUTY   14=NET DUTY
    15=AMP DUTY  16=WIDTH  17=NET WIDTH
    18=AMP WIDTH 19=DIODE  20=CONT
    21=HFE       22=LOGIC  23=DBM
    24=EF        25=TEMP
*/

#ifndef RS22812_H
#define RS22812_H

#include <QObject>

//Definition of custom data type.

struct Flags
{
    bool Hz;
    bool Ohms;
    bool k;
    bool M;
    bool F;
    bool A;
    bool V;
    bool m;
    bool u;
    bool n;
    bool dBm;
    bool s;
    bool percent;
    bool hFE;
    bool REL;
    bool MIN;
    bool Beep;
    bool Diode;
    bool continuity;
    bool Bat;
    bool Hold;
    bool dash;
    bool tilde;
    bool RS232;
    bool Auto;
    bool MAX;
    int DP; //Decimal point position
    bool checksum;
    /*!
 * \brief operator == Equality operator for Flags struct.
 * \param f1
 * \param f2
 * \return
 */
    bool operator==(const Flags& f2) const
    {return ((A==f2.A)&&(Auto==f2.Auto)&&(Bat==f2.Bat)&&
             (Beep==f2.Beep)&&(checksum==f2.checksum)&&(dash==f2.dash)&&
             (dBm==f2.dBm)&&(Diode==f2.Diode)&&(DP==f2.DP)&&
             (F==f2.F)&&(hFE==f2.hFE)&&(Hold==f2.Hold)&&(Hz==f2.Hz)&&
             (k==f2.k)&&(M==f2.M)&&(m==f2.m)&&(MAX==f2.MAX)&&
             (MIN==f2.MIN)&&(n==f2.n)&&(Ohms==f2.Ohms)&&
             (percent==f2.percent)&&(REL==f2.REL)&&(RS232==f2.RS232)&&
             (s==f2.s)&&(tilde==f2.tilde)&&(u==f2.u)&&(V==f2.V));
    }

    bool operator!=(const Flags& f2)
    {
        return !(*this==f2);
    }
};

class RS22812 : public QObject
{
    Q_OBJECT
public:
    explicit RS22812(QObject *parent = 0);
    float getVal() const;
    Flags getFlags() const;
    QString getDigitString() const;
    uint getMode() const;
private:
    bool modeChanged();
    uint mode;
    Flags flags,oldflags;
    QString digits;
    QString byte2Digit(uchar byte);
    void resetFlags(Flags &f);

signals:
    void newMode();
    //void flagsChanged(Flags newflags);
    void newData();

public slots:
    void newValue(const QByteArray &data);
};

#endif // RS22812_H
