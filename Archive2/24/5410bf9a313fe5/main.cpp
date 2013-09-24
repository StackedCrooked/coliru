#include <QtCore/QString>

QString toBin(bool isneg, QString num)
{
    QString buffer;
    bool boolBuffer;
    int intBuffer;
    int bitNum;
    if(isneg)
    {
        boolBuffer = true;
        intBuffer = 0;
        QString out;
        while(boolBuffer)
        {
            if(pow(2, (double)intBuffer) >= num.toDouble())
            {
                boolBuffer = false;
            }
            else
            {
                intBuffer++;
            }
        }
        bitNum = intBuffer;
        intBuffer = num.toInt();
        buffer = "1";
        intBuffer = intBuffer - pow(2, bitNum);
        bitNum--;
        for(int i=bitNum; i>=0; i--)
        {
            if(intBuffer - pow(2, i) >= 0)
            {
                intBuffer = intBuffer - pow(2, i);
                buffer.append("1");
            }
            else
            {
                buffer.append("0");
            }
        }
        for(int i=0; i<buffer.length(); i++)
        {
            if(buffer.at(i)=='1')
            {
                out.append("0");
            }
            else
            {
                out.append("1");
            }
        }
        out.append(" + 1");
        return out;
    }
    else
    {
        boolBuffer = true;
        intBuffer = 0;
        while(boolBuffer)
        {
            if(pow(2, (double)intBuffer) >= num.toDouble())
            {
                boolBuffer = false;
            }
            else
            {
                intBuffer++;
            }
        }
        bitNum = intBuffer;
        intBuffer = num.toInt();
        buffer = "1";
        intBuffer = intBuffer - pow(2, bitNum);
        bitNum--;
        for(int i=bitNum; i>=0; i--)
        {
            if(intBuffer - pow(2, i) >= 0)
            {
                intBuffer = intBuffer - pow(2, i);
                buffer.append("1");
            }
            else
            {
                buffer.append("0");
            }
        }
        return buffer;
    }
}

QString toDec(bool isneg, QString num)
{
    QString buffer;
    int intBuffer;
    if(isneg)
    {
        buffer = num;
        intBuffer = 0;
        for(int i=0; i<buffer.length(); i++)
        {
            if(buffer.at(i)=='1')
            {
                intBuffer = intBuffer + pow(2, abs(buffer.length()-i-1));
            }
        }
        buffer = QString::number(-1*intBuffer);
        return buffer;
    }
    else
    {
        buffer = num;
        intBuffer = 0;
        for(int i=0; i<buffer.length(); i++)
        {
            if(buffer.at(i)=='1')
            {
                intBuffer = intBuffer + pow(2, abs(buffer.length()-i-1));
            }
        }
        buffer = QString::number(intBuffer);
        //ui->textBrowser->append(buffer);
        return buffer;
    }
}

#include <iostream>

int main()
{
    QString s = "10";
    std::cout << s.toStdString() << "\n";
    auto other = toDec(false, s);
    std::cout << other.toStdString() << "\n";
}
