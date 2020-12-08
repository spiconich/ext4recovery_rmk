#pragma once
#include <iostream>
#include <Windows.h>

class Translation
{
public:	
	virtual unsigned long long eithtBytesToULONGLONG(byte* buffer, byte* bufferHigh) = 0;
	virtual ULONGLONG sixBytesToIntx(byte* buffer) = 0;
	virtual unsigned int foursBytesToIntx(byte* buffer) = 0;
	virtual std::string UnixTimeToDaily(unsigned int time) = 0;
	virtual ~Translation() {}
};

class TranslatorNode : public  Translation
{
	unsigned long long eithtBytesToULONGLONG(byte* buffer, byte* bufferHigh)
	{
		unsigned long long resultingULONGLONG =
			unsigned long long(
				(unsigned char)(buffer[3]) << 56 |
				(unsigned char)(buffer[2]) << 48 |
				(unsigned char)(buffer[1]) << 40 |
				(unsigned char)(buffer[0]) << 32 |
				(unsigned char)(bufferHigh[3]) << 24 |
				(unsigned char)(bufferHigh[2]) << 16 |
				(unsigned char)(bufferHigh[1]) << 8 |
				(unsigned char)(bufferHigh[0])
				);
		return  resultingULONGLONG;
	}
	ULONGLONG sixBytesToIntx(byte* buffer)
	{
		ULONGLONG resultingInt = ULONGLONG(
			(unsigned char)(buffer[5]) << 40 |
			(unsigned char)(buffer[4]) << 32 |
			(unsigned char)(buffer[3]) << 24 |
			(unsigned char)(buffer[2]) << 16 |
			(unsigned char)(buffer[1]) << 8 |
			(unsigned char)(buffer[0]));
		return resultingInt;
	}
	unsigned int foursBytesToIntx(byte* buffer)
	{
		unsigned int resultingInt = unsigned int((unsigned char)(buffer[3]) << 24 |
			(unsigned char)(buffer[2]) << 16 |
			(unsigned char)(buffer[1]) << 8 |
			(unsigned char)(buffer[0]));
		return resultingInt;
	}
    std::string UnixTimeToDaily(unsigned int time)
    {
        //std::cout << "UNIX TIME:" << time << std::endl;
        int year = time / 31536000;
        year = year + 1970;
        int extraDays = (year - 1969) / 4;
        int days = time / 86400;
        int daysForLaterCalc = days;
        days = days - extraDays;
        int daysThisYear = (days % 365) + 1;
        int isCurYearLeapBonusDay = 0;
        if ((year % 4) == 0)
        {
            isCurYearLeapBonusDay = 1;
        }
        int jan = 31, mar = 31, may = 31, jul = 31, aug = 31, oct = 31, dec = 31;
        int apr = 30, jun = 30, sep = 30, nov = 30;
        int feb = 28;
        std::string month = "";

        if (daysThisYear > jan)
        {
            daysThisYear = daysThisYear - jan;
            if (daysThisYear > (feb + isCurYearLeapBonusDay))
            {
                daysThisYear = daysThisYear - (feb + isCurYearLeapBonusDay);
                if (daysThisYear > mar)
                {
                    daysThisYear = daysThisYear - mar;
                    if (daysThisYear > apr)
                    {
                        daysThisYear = daysThisYear - apr;
                        if (daysThisYear > may)
                        {
                            daysThisYear = daysThisYear - may;
                            if (daysThisYear > jun)
                            {
                                daysThisYear = daysThisYear - jun;
                                if (daysThisYear > jul)
                                {
                                    daysThisYear = daysThisYear - jul;
                                    if (daysThisYear > aug)
                                    {
                                        daysThisYear = daysThisYear - aug;
                                        if (daysThisYear > sep)
                                        {
                                            daysThisYear = daysThisYear - sep;
                                            if (daysThisYear > oct)
                                            {
                                                daysThisYear = daysThisYear - oct;
                                                if (daysThisYear > nov)
                                                {
                                                    daysThisYear = daysThisYear - nov;
                                                    month = "Dec";
                                                }
                                                else
                                                {
                                                    month = "Nov";
                                                }
                                            }
                                            else
                                            {
                                                month = "Oct";
                                            }

                                        }
                                        else
                                        {
                                            month = "Sep";
                                        }
                                    }
                                    else
                                    {
                                        month = "Aug";
                                    }
                                }
                                else
                                {
                                    month = "Jul";
                                }
                            }
                            else
                            {
                                month = "Jun";
                            }
                        }
                        else
                        {
                            month = "May";
                        }
                    }
                    else
                    {
                        month = "Apr";
                    }
                }
                else
                {
                    month = "Mar";
                }
            }
            else
            {
                month = "Feb";
            }
        }
        else
        {
            month = "Jan";
        }
        int secondsInCurDay = time - (daysForLaterCalc * 86400);
        int hours = secondsInCurDay / 3600;
        secondsInCurDay = secondsInCurDay - (hours * 3600);
        int minutes = secondsInCurDay / 60;
        int seconds = secondsInCurDay - (minutes * 60);
        std::string Answer = std::to_string(daysThisYear) + " " + month + " " + std::to_string(year) + " " + std::to_string(hours) + ":" + std::to_string(minutes) + ":" + std::to_string(seconds);

        return Answer;
    }
};

class TranslatorFactory
{
public:
    virtual Translation* createNode() = 0;
    virtual ~TranslatorFactory() {}
};

class TranslatorNodeCreate : public TranslatorFactory
{
public:
    Translation* createNode()
    {
        return new TranslatorNode;
    }
};

TranslatorNodeCreate* global_translationNode_create = new TranslatorNodeCreate;
Translation* translator = global_translationNode_create->createNode();