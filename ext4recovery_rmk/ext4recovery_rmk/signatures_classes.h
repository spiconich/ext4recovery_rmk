#pragma once
#pragma pack(push,1)
#include <iostream>
#include <string.h>
#include <Windows.h>
#include "sqlite3.h"
#include "translation.h"


struct twelve_bits
{
	BYTE first_bytes[4];//0-3
	BYTE second_bytes[4];//0-3
	BYTE third_bytes[4];//0-3
};

const size_t signatures_count = 46;


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
Signature(2,3791640831,0,2017831719,0,"png",true), //10
Signature(2,912808514,0,912808514,0,"tar.bz2",true), //1 643383601
Signature(2,912808514,0,643383601,0,"tar.bz2",true),
Signature(1,559903,0,0,0,"gz",false), //14
Signature(2,3689851885,0,3,0,"rpm",true), //1
Signature(2,963140162,0,643383601,0,"bz2",true), //1
Signature(3,67324752,0,134217748,2376728576,"odp",true), //1
Signature(3,67324752,0,134217748,2374828032,"odp",true),
Signature(3,67324752,0,134217748,1999372288,"odp",true),//1 
Signature(3,67324752,0,134217748,2953445376,"odt",true), //1
Signature(3,67324752,0,134217748,2953379840,"odt",true),
Signature(2,67324752,0,393236,0,"docx",true),
Signature(2,67324752,0,134742036,0,"docx",true), //1 393236
Signature(1,3791640831,0,0,0,"jpg",true), //2
Signature(1,3774863615,0,0,0,"jpg",true), //2 
Signature(1,3774863615,0,0,0,"jpeg",true), //2
Signature(1,1178882085,0,0,0,"pdf",true), //3
Signature(1,2948364855,0,0,0,"7z",true), //4      %%%% ПЕРЕТЕСТ
Signature(3,1766609235,0,1713399156,1634562671,"dblite",true), //5
Signature(1,4262637007,0,0,0,"dbx",true), //6
Signature(2,3759263696,0,3776623009,0,"doc",true), //7
Signature(1,34498581873,0,0,0,"iso",true), //8     %%%% ТРЭШ
Signature(1,1129333590,0,0,0,"pch",true), //9
Signature(2,1196314761,0,169478669,0,"png",true), //10
Signature(2,3759263696,0,3776623009,0,"ppt",true), //11
Signature(1,561144146,0,0,0,"rar",true), //12       % ПЕРЕТЕСТ
Signature(1,1953651835,0,0,0,"rtf",true), //13
Signature(1,1147694772,0,0,0,"tib",true), //14
Signature(1,1480934229,0,0,0,"uce",true), //15
Signature(1,1448299867,0,0,0,"vcw",true), //16
Signature(1,1179011410,0,0,0,"avi",true), //17
Signature(2,3759263696,0,3776623009,0,"xls",true), //18
Signature(1,1684558925,0,0,0,"midi",true), //19
Signature(2,2749318426,0,2290238099,0,"mkv",true), //20
Signature(2,2749318426,0,2173059747,0,"mkv",true),
Signature(1,1179011410,0,0,0,"wav",true), //21
Signature(2,1974609456,0,298804878,0,"wmv",true), //22
Signature(3,256,0,1851880531,1685217636,"accdb",true), //23
Signature(1,1179011410,0,0,0,"cdr",true), //24
Signature(2,3759263696,0,3776623009,0,"pub",true), //25
Signature(2,1631205476,0,1970237038,0,"torrent",true), //26
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

class SignaturesInteract
{
public:
	virtual void addingUserSign() = 0;
	virtual void sqlShow() = 0;
	virtual ~SignaturesInteract() {}
};
class SignaturesInteractNode : public SignaturesInteract
{
    void addingUserSign()
    {
        unsigned char _action_type = 0;
        unsigned int _four_bytes = 0;
        ULONGLONG _six_bytes = 0;
        unsigned int _eight_bytes = 0;
        unsigned int _twelwe_bytes = 0;
        std::string _file_format = "NOT USED";
        bool _restore_required = false;
        std::cout << "  You wanna to add optional signature? y/n: ";
        std::string ynRez;
        std::cin >> ynRez;
        bool isErrorExist = true;
        if ((ynRez == "y") || (ynRez == "Y"))
        {
            std::cout << "  Choose your signature action type: " << std::endl;
            std::cout << "  1- using bytes 0-3, 2- using bytes 0-7, 3- using bytes 0-11, 4-using bytes 0-5: ";
            std::cin >> _action_type;

            switch (_action_type)
            {
            case '1':
                _action_type = 1;
                isErrorExist = false;
                break;
            case '2':
                _action_type = 2;
                isErrorExist = false;
                break;
            case '3':
                _action_type = 3;
                isErrorExist = false;
                break;
            case '4':
                _action_type = 4;
                isErrorExist = false;
                break;
            default:
                isErrorExist = true;
            }
            if (!isErrorExist)
            {
                if (_action_type == 1)
                {
                    std::cout << "  Enter bytes 0-3 (demical, BE): ";
                    std::cin >> _four_bytes;
                    std::cout << "  Enter Extension: ";
                    std::cin >> _file_format;
                }
                else
                {
                    if (_action_type == 2)
                    {
                        std::cout << "  Enter bytes 0-3 (demical, BE): ";
                        std::cin >> _four_bytes;
                        std::cout << "  Enter bytes 4-7 (demical, BE): ";
                        std::cin >> _eight_bytes;
                        std::cout << "  Enter Extension: ";
                        std::cin >> _file_format;
                    }
                    else
                    {
                        if (_action_type == 3)
                        {
                            std::cout << "  Enter bytes 0-3 (demical, BE): ";
                            std::cin >> _four_bytes;
                            std::cout << "  Enter bytes 4-7 (demical, BE): ";
                            std::cin >> _eight_bytes;
                            std::cout << "  Enter bytes 8-11 (demical, BE): ";
                            std::cin >> _twelwe_bytes;
                            std::cout << "  Enter Extension: ";
                            std::cin >> _file_format;
                        }
                        else
                        {
                            if (_action_type == 4)
                            {
                                std::cout << "  Enter bytes 0-5 (demical, BE): ";
                                std::cin >> _six_bytes;
                                std::cout << "  Enter Extension: ";
                                std::cin >> _file_format;
                            }
                        }
                    }
                }
            }
            else
            {
                std::cout << "  Incorrect action type, scipping..." << std::endl;
            }
        }
        _restore_required = !isErrorExist;
        if (_restore_required)
        {
            signature_arr[signatures_count - 1] = Signature(_action_type, _four_bytes, _six_bytes, _eight_bytes, _twelwe_bytes, _file_format, _restore_required);
        }
    }
    void sqlShow()
    {
        std::cout << "  Creating sqlite3 file with humanreadable signatures" << std::endl;
        sqlite3* db = 0; // sql object handle
        char* err = 0;
        //const char* SQL = "CREATE TABLE IF NOT EXISTS signatures(Format,Bytes_0to3 VARCHAR(20),Bytes_4to7 VARCHAR(20) ,Bytes_8to11 VARCHAR(20));"; 
        const char* SQL = "DROP TABLE signatures;";
        if (sqlite3_open("signatures.dblite", &db))
        {
            std::cout << "  Error: got some troubles with open/creating DB " << sqlite3_errmsg(db) << std::endl;
        }
        // doing sql code
        else
        {   //drop table if no exit
            if (sqlite3_exec(db, SQL, 0, 0, &err))
            {
                // std::cout << "  SQL Table drop error: " << err << std::endl;
                sqlite3_free(err);
            }
            SQL = "CREATE TABLE IF NOT EXISTS signatures(Extension VARCHAR(20), action_type VARCHAR(20),bytes0to3 VARCHAR(20), bytes4to7 VARCHAR(20),bytes8to11 VARCHAR(20),bytes0to5 VARCHAR(20));";
            //create table
            if (sqlite3_exec(db, SQL, 0, 0, &err))
            {
                std::cout << "  SQL Table create error: " << err << std::endl;
                sqlite3_free(err);
            }
            std::string SQL_string;
            unsigned int sql_counter = 0;
            std::string temporary_data;
            std::string long_life_temp;
            ULONGLONG test;
            for (sql_counter = 0; sql_counter < signatures_count; sql_counter++)
            {

                SQL_string = "INSERT INTO signatures(bytes0to5, Extension) VALUES ('";
                test = signature_arr[sql_counter].get_six_bytes();
                temporary_data = std::to_string(test);
                if (temporary_data == "0" || temporary_data == " " || temporary_data == "" || temporary_data.length() == 0) { temporary_data = "NOT USED"; };
                SQL_string = SQL_string + temporary_data + "','";
                temporary_data = signature_arr[sql_counter].get_file_format();
                if (temporary_data == "0" || temporary_data == " " || temporary_data == "" || temporary_data.length() == 0) { temporary_data = "NOT USED"; };
                long_life_temp = temporary_data;
                SQL_string = SQL_string + temporary_data + "');";
                SQL = SQL_string.c_str();
                if (sqlite3_exec(db, SQL, 0, 0, &err))
                {
                    std::cout << "  SQL error: " << err << std::endl;
                    sqlite3_free(err);
                }


                SQL_string = "UPDATE signatures SET action_type='";
                test = signature_arr[sql_counter].get_action_type();
                switch (test)
                {
                case 1:
                    temporary_data = "Using first 4 bytes";
                    break;
                case 2:
                    temporary_data = "Using first 8 bytes";
                    break;
                case 3:
                    temporary_data = "Using first 12 bytes";
                    break;
                case 4:
                    temporary_data = "Using first 6 bytes";
                    break;
                default:
                    temporary_data = std::to_string(test);
                    break;
                }
                if (temporary_data == "0" || temporary_data == " " || temporary_data == "" || temporary_data.length() == 0) { temporary_data = "NOT USED"; };
                SQL_string = SQL_string + temporary_data + "',bytes0to3='";

                test = signature_arr[sql_counter].get_four_bytes();
                temporary_data = std::to_string(test);
                if (temporary_data == "0" || temporary_data == " " || temporary_data == "" || temporary_data.length() == 0) { temporary_data = "NOT USED"; };
                SQL_string = SQL_string + temporary_data + "' WHERE Extension='" + long_life_temp + "';";

                SQL = SQL_string.c_str();
                if (sqlite3_exec(db, SQL, 0, 0, &err))
                {
                    std::cout << "  SQL error: " << err << std::endl;
                    sqlite3_free(err);
                }

                SQL_string = "UPDATE signatures SET bytes4to7='";
                test = signature_arr[sql_counter].get_eight_bytes();
                temporary_data = std::to_string(test);
                if (temporary_data == "0" || temporary_data == " " || temporary_data == "" || temporary_data.length() == 0) { temporary_data = "NOT USED"; };
                SQL_string = SQL_string + temporary_data + "',bytes8to11='";
                test = signature_arr[sql_counter].get_twelwe_bytes();
                temporary_data = std::to_string(test);
                if (temporary_data == "0" || temporary_data == " " || temporary_data == "" || temporary_data.length() == 0) { temporary_data = "NOT USED"; };
                SQL_string = SQL_string + temporary_data + "' WHERE Extension='" + long_life_temp + "';";
                SQL = SQL_string.c_str();
                if (sqlite3_exec(db, SQL, 0, 0, &err))
                {
                    std::cout << "  SQL error: " << err << std::endl;
                    sqlite3_free(err);
                }
            }
        }
        // closing connection
        sqlite3_close(db);
    }
};
class SignaturesInteractFactory
{
public:
	virtual SignaturesInteract* createNode() = 0;
	virtual ~SignaturesInteractFactory() {}
};
class SignaturesInteractFactoryCreate : public SignaturesInteractFactory
{
public:
	SignaturesInteract* createNode()
	{
		return new SignaturesInteractNode;
	}
}; 
SignaturesInteractFactoryCreate* global_sign_int_create = new SignaturesInteractFactoryCreate;
SignaturesInteract* signature_interact = global_sign_int_create->createNode();