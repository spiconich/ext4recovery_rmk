#pragma once
#pragma pack(push,1)
#include <iostream>
#include <string.h>
#include <Windows.h>
#include "sqlite3.h"
#include "byte_to_dem.h"


struct twelve_bits
{
	BYTE first_bytes[4];//0-3
	BYTE second_bytes[4];//0-3
	BYTE third_bytes[4];//0-3
};

const size_t signatures_count = 31;


class Signature {
	unsigned char action_type;
	unsigned int four_bytes;
	ULONGLONG six_bytes;
	unsigned int eight_bytes;
	unsigned int twelwe_bytes;
	std::string file_format;
	bool restore_required;

public:
	//Signature(const unsigned char action_type = 0 , const unsigned int four_bytes = 0, const ULONGLONG six_bytes = 0, const unsigned int eight_bytes = 0, const unsigned int twelwe_bytes=0, const std::string file_format="unknown", const bool restore_required=false);
	Signature(unsigned char,unsigned int, ULONGLONG, unsigned int, const unsigned int, std::string, bool); // Конструктор со всеми параметрами

	const unsigned char get_action_type() const { return action_type; }    //метод, тип взаимодействия
	const unsigned int get_four_bytes() const { return four_bytes; }    //метод, отдающий первые четыре байта
	const ULONGLONG get_six_bytes() const { return six_bytes; }    //метод, отдающий первые шесть байт
	const unsigned int get_eight_bytes() const { return eight_bytes; }    //метод, вторые четыре байта
	const unsigned int get_twelwe_bytes() const { return twelwe_bytes; }    //метод, отдающий третьи четыре байта
	const std::string get_file_format() const { return file_format; }    //метод, отдающий формат файла
	const bool get_restore_required() const { return restore_required; }    //метод, отдающий флаг восстановления файла
};

Signature::Signature(const unsigned char action_type_, const unsigned int four_bytes_, const ULONGLONG six_bytes_, const unsigned int eight_bytes_, const unsigned int twelwe_bytes_, const std::string file_format_, const bool restore_required_) 
{
	action_type = action_type_;//записываем пришедшее значение в данное класса
	four_bytes = four_bytes_;
	six_bytes = six_bytes_;
	eight_bytes = eight_bytes_;
	twelwe_bytes = twelwe_bytes_;
	file_format = file_format_;
	restore_required = restore_required_;
}

/*
|||||||||||||||||||||||||||||||||||||||||||||||||||||||||
|||||||       Type 0=sleep,1=4b,2=8b,3=12,4=6b      |||||||
|||||||||||||||||||||||||||||||||||||||||||||||| b |||||||||
*/

unsigned char g_user_action_type = 0;
unsigned int g_user_four_bytes = 0;
ULONGLONG g_user_six_bytes = 0;
unsigned int g_user_eight_bytes = 0;
unsigned int g_user_twelwe_bytes = 0;
bool g_user_restore_required = false;
std::string g_user_file_format = "NOT ENABLED";

Signature signature_arr[signatures_count] = {
Signature(2,67324752,0,134742036,0,"docx",true), //1
Signature(1,3774863615,0,0,0,"jpg",true), //2
Signature(1,1178882085,0,0,0,"pdf",true), //3
Signature(1,2948364855,0,0,0,"7z",true), //4
Signature(3,1766609235,0,1713399156,1634562671,"dblite",true), //5
Signature(1,4262637007,0,0,0,"dbx",true), //6
Signature(2,3759263696,0,3776623009,0,"doc",true), //7
Signature(1,34498581873,0,0,0,"iso",true), //8
Signature(1,1129333590,0,0,0,"pch",true), //9
Signature(2,1196314761,0,169478669,0,"png",true), //10
Signature(2,3759263696,0,3776623009,0,"ppt",true), //11
Signature(1,21726152,0,0,0,"rar",true), //12
Signature(1,1953651835,0,0,0,"rtf",true), //13
Signature(1,1147694772,0,0,0,"tib",true), //14
Signature(1,1480934229,0,0,0,"uce",true), //15
Signature(1,1448299867,0,0,0,"vcw",true), //16
Signature(1,1179011410,0,0,0,"wav",true), //17
Signature(2,3759263696,0,3776623009,0,"xls",true), //18
Signature(1,1684558925,0,0,0,"midi",true), //19
Signature(2,2749318426,0,2290238099,0,"mkv",true), //20
Signature(1,1179011410,0,0,0,"avi",true), //21
Signature(2,1974609456,0,298804878,0,"wmv",true), //22
Signature(3,256,0,1851880531,1685217636,"accdb",true), //23
Signature(1,1179011410,0,0,0,"cdr",true), //24
Signature(2,3759263696,0,3776623009,0,"pub",true), //25
Signature(3,1631205476,0,1970237038,845505390,"torrent",true), //26
Signature(2,1411798081,0,1297239878,0,"djvu",true), //27
Signature(3,1836597052,0,1702240364,1869181810,"fb2",true), //28
Signature(1,168627466,0,0,0,"pcapng",true), //29
Signature(1,402653184,0,1887007846,842297453,"mp4",true), //30
Signature(g_user_action_type,g_user_four_bytes,g_user_six_bytes,g_user_eight_bytes,g_user_twelwe_bytes, g_user_file_format,g_user_restore_required)
};




std::string desicionWhatExtensionToCreate(unsigned int four_bytes, unsigned int eight_bytes, unsigned int twelwe_bytes, ULONGLONG six_bytes)
{
	unsigned int desicion_counter=0;
	signed int desicion_result= -1;
	while ((desicion_counter < signatures_count) && (desicion_result == -1))
	{
		if (signature_arr[desicion_counter].get_restore_required() == true)
		{
			if (signature_arr[desicion_counter].get_action_type() == 1)
			{
				if (signature_arr[desicion_counter].get_four_bytes() == four_bytes)
				{
					desicion_result = desicion_counter;
				}
			}
			else
			{
				if (signature_arr[desicion_counter].get_action_type() == 2)
				{
					if ((signature_arr[desicion_counter].get_four_bytes() == four_bytes) && (signature_arr[desicion_counter].get_eight_bytes() == eight_bytes))
					{
						desicion_result = desicion_counter;
					}
				}
				else
				{
					if (signature_arr[desicion_counter].get_action_type() == 3)
					{
						if ((signature_arr[desicion_counter].get_four_bytes() == four_bytes) && (signature_arr[desicion_counter].get_eight_bytes() == eight_bytes) && (signature_arr[desicion_counter].get_twelwe_bytes() == twelwe_bytes))
						{
							desicion_result = desicion_counter;
						}
					}
					else
					{
						if (signature_arr[desicion_counter].get_action_type() == 4)
						{
							if (signature_arr[desicion_counter].get_six_bytes() == six_bytes)
							{
								desicion_result = desicion_counter;
							}
						}
					}
				}
			}
		}
		desicion_counter++;
	} 
	if (desicion_result == -1)
	{
		return  "";
	}
	else
	{
		return signature_arr[desicion_result].get_file_format();
	}
}

