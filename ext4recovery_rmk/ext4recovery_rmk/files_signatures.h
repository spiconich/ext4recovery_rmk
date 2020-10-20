#pragma once
#pragma pack(push,1)
#include <iostream>
#include <string.h>
#include <Windows.h>
#include "sqlite3.h"

//twelve BYTES for future sign find 
unsigned int foursBytesToIntx(byte* buffer)
{
    unsigned int resultingInt = unsigned int((unsigned char)(buffer[3]) << 24 |
        (unsigned char)(buffer[2]) << 16 |
        (unsigned char)(buffer[1]) << 8 |
        (unsigned char)(buffer[0]));
    return resultingInt;
}
struct twelve_bits
{
    BYTE first_bytes[4];//0-3
    BYTE second_bytes[4];//0-3
    BYTE third_bytes[4];//0-3
};

//signatures_bytes
enum microsoft_word: unsigned int
{
    // 50 4B 03 04 14 00 08 08 Little endian
    first_4bytes_microsoft_word_0 = 67324752,  //04 03 4B 50 Big endian
    second_4bytes_microsoft_word_0 = 134742036,//08 08 00 14 Big endian
};

enum first_jpg: unsigned int
{   // FF D8 FF E0 Little endian
    first_4bytes_jpg_0 = 3774863615, //E0 FF D8 FF Big endian
};
//signatures_classes
class Signatures
{
    public:
        virtual std::string give_format() = 0;
        virtual ~Signatures() {}
};

class Microsoft_word_0 : public Signatures
{
    std::string give_format()
    {
        std::string format = "docx";
        return format;
    }
};

class Picture_jpg_0 : public Signatures
{
    std::string give_format()
    {
        std::string format = "jpg";
        return format;
    }
};

class Signatures_Factory
{
public:
    virtual Signatures* createSignType() = 0;
    virtual ~Signatures_Factory() {}
};

class Microsoft_word_0_factory : public Signatures_Factory
{
public:
    Signatures* createSignType()
    {
        return new Microsoft_word_0;
    }
};

class Picture_jpg_0_factory : public Signatures_Factory
{
public:
    Signatures* createSignType()
    {
        return new Picture_jpg_0;
    }
};

Signatures* desicionWhatSignToCreate(unsigned int first_byte, unsigned int second_byte, unsigned int third_byte)
{
    
    if ((first_byte == microsoft_word::first_4bytes_microsoft_word_0) && (second_byte == microsoft_word::second_4bytes_microsoft_word_0))
    {
        Microsoft_word_0_factory* microsoft_word_0 = new Microsoft_word_0_factory;
        return microsoft_word_0->createSignType();
    }
    else
    {
        if (first_byte == first_jpg::first_4bytes_jpg_0)
        {
            Picture_jpg_0_factory* picture_jpg_0 = new Picture_jpg_0_factory;
            return picture_jpg_0->createSignType();
        }
        else
        {
            return NULL;
        }
    }
}
