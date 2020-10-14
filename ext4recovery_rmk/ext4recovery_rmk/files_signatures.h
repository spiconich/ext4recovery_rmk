#pragma once
#pragma pack(push,1)
#include <iostream>
#include <string.h>
#include <Windows.h>

struct twelve_bits
{
    BYTE first_bytes[4];//0-3
    BYTE second_bytes[4];//0-3
    BYTE third_bytes[4];//0-3
};
enum Sign_result
{
    SIGN_MICROSOFT_WORD = 1,
    SIGN_JPG = 2
};

//Microsoft WORD
enum microsoft_word:unsigned int
{
    first_4bytes = 67324752,
    second_4bytes = 134742036,
};
std::string microsoft_word_string = "docx";

//JPG


