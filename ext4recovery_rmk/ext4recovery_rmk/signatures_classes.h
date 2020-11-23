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

const size_t signatures_count = 3;
//const size_t sign_arr_max = signatures_count + 10;

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
|||||||||||||||||||||||||||||||||||||||||||||||||||||||||
*/
Signature signature_arr[signatures_count] = {
	Signature(2,67324752,0,134742036,0,"docx",true),
	Signature(1,3774863615,0,0,0,"jpg",true),
	Signature(0,0,0,0,0,"",false)
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

