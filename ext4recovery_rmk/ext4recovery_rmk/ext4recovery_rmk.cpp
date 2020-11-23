#include <iostream>
#include <Windows.h>
#include <string>

#include "console_colors.h"
#include "superblock_offsets.h"
#include "classes_blocks_addrs.h"  

//signatures output to sqlite
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
        SQL = "CREATE TABLE IF NOT EXISTS signatures(Format,Bytes_0to3 VARCHAR(20),Bytes_4to7 VARCHAR(20) ,Bytes_8to11 VARCHAR(20));";
        //create table
        if (sqlite3_exec(db, SQL, 0, 0, &err))
        {
            std::cout << "  SQL Table create error: " << err << std::endl;
            sqlite3_free(err);
        }

        //microsoft_word_0 sql responce
        SQL = "INSERT INTO signatures (Format, Bytes_0to3, Bytes_4to7,Bytes_8to11) VALUES ('microsoft_word_0','50 4B 03 04','14 00 08 08','NULL')";
        if (sqlite3_exec(db, SQL, 0, 0, &err))
        {
            std::cout << "  SQL microsoft_word_0 sign error: " << err << std::endl;
            sqlite3_free(err);
        }

        //picture_jpg_0 sql responce
        SQL = "INSERT INTO signatures (Format, Bytes_0to3, Bytes_4to7,Bytes_8to11) VALUES ('picture_jpg_0','FF D8 FF E0','NULL','NULL')";
        if (sqlite3_exec(db, SQL, 0, 0, &err))
        {
            std::cout << "  SQL microsoft_word_0 sign error: " << err << std::endl;
            sqlite3_free(err);
        }

        
    }
    // closing connection
    sqlite3_close(db);
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
    int daysThisYear = (days % 365)+1;
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
unsigned int foursBytesToInt(byte* buffer)
{
    unsigned int resultingInt = unsigned int((unsigned char)(buffer[3]) << 24 |
        (unsigned char)(buffer[2]) << 16 |
        (unsigned char)(buffer[1]) << 8 |
        (unsigned char)(buffer[0]));
    return resultingInt;
}
void showMe()
{
    std::cout << "\n" << "  Insert anykey to exit programm:   ";
    std::string x;
    std::cin >> x;
}
char backSlashForCPP()
{
    int backSlashInt = 92;
    char backSlashChar = backSlashInt;
    return backSlashChar;
}
std::string ExePath() {
    char buffer[MAX_PATH];
    GetModuleFileName(NULL, buffer, MAX_PATH);
    std::string::size_type pos = std::string(buffer).find_last_of("\\/");
    return std::string(buffer).substr(0, pos);
}
bool letsTryToOpenFile(std::string fullPath)
{
    bool rez = false;
    HANDLE fileHandle = CreateFileA(
        fullPath.c_str(),
        GENERIC_READ,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL);
    if (fileHandle != INVALID_HANDLE_VALUE)
    {
        rez = true;
    }
    CloseHandle(fileHandle);
    return rez;
}
void superBlockShow(superblock_offests strucToShow, unsigned long long offset)
{
    std::cout << "                                                                       " << std::endl;
    std::cout << "  ______________________S_U_P_E_R__B_L_O_C_K__F_O_U_N_D______________________ " << std::endl;
    std::cout << "" << std::endl;;
    std::cout << "  Super block offset (dec):  " << offset << std::endl;;
    std::cout << "  Inodes count:              " << foursBytesToInt(strucToShow.nInodeinSystem) << std::endl;
    GLOBAL_num_of_groups = foursBytesToInt(strucToShow.nBlocksinSystem);
    std::cout << "  Blocks count:              " << foursBytesToInt(strucToShow.nBlocksinSystem) << std::endl;
    std::cout << "  Reserved block count:      " << foursBytesToInt(strucToShow.nBlocksReserved) << std::endl;
    std::cout << "  Free blocks:               " << foursBytesToInt(strucToShow.nBlocksFree) << std::endl;
    std::cout << "  Free inodes:               " << foursBytesToInt(strucToShow.nInodesFree) << std::endl;
    std::cout << "  First block:               " << foursBytesToInt(strucToShow.ZeroGroupBlock) << std::endl;
    unsigned int blockSizeMult = foursBytesToInt(strucToShow.BlockSize);
    int blockSize = 1024;
    unsigned int scale = 0;
    while (scale < blockSizeMult)
    {
        blockSize = blockSize * 2;
        scale++;
    }
    std::cout << "  Block size:                " << blockSize << std::endl;
    GLOBAL_num_of_groups = GLOBAL_num_of_groups / blockSize;
    GLOBAL_num_of_groups = GLOBAL_num_of_groups / 8;
    GLOBAL_num_of_groups++;
    std::cout << "  Groups count:              " << GLOBAL_num_of_groups << std::endl;
    unsigned int FragSizeMult = foursBytesToInt(strucToShow.FragmentSize);
    int FragSize = 1024;
    scale = 0;
    while (scale < FragSizeMult)
    {
        FragSize = FragSize * 2;
        scale++;
    }
    std::cout << "  Fragment size:             " << FragSize << std::endl;
    std::cout << "  Blocks per group:          " << foursBytesToInt(strucToShow.nBlocksPerGroup) << std::endl;
    std::cout << "  Fragments per group:       " << foursBytesToInt(strucToShow.nFragmentsPerGroup) << std::endl;
    std::cout << "  Inodes per group:          " << foursBytesToInt(strucToShow.nInodesPerGroup) << std::endl;
    unsigned int UnixTime = foursBytesToInt(strucToShow.fs_mk_time);
    std::string DailyTimeFormat = UnixTimeToDaily(UnixTime);
    std::cout << "  FS create time:            " << DailyTimeFormat << std::endl;
    UnixTime = foursBytesToInt(strucToShow.LastTimeMounted);
    DailyTimeFormat = UnixTimeToDaily(UnixTime);

    std::cout << "  Last mount time:           " << DailyTimeFormat << std::endl;
    UnixTime = foursBytesToInt(strucToShow.LastWriteTime);
    DailyTimeFormat = UnixTimeToDaily(UnixTime);
    std::cout << "  Last write time:           " << DailyTimeFormat << std::endl;
    std::cout << "  Mount count:               " << strucToShow.CurnOfMounts << std::endl;
    std::cout << "  Max mounts count:          " << strucToShow.MaxnOfMounts << std::endl;
    int signint = strucToShow.Signature;
    std::string sign = "";
    if (signint == 61267)
    {
        sign = "0xef53";
    }
    else
    {
        sign = std::to_string(signint);
    }
    std::cout << "  Signature:                 " << sign << std::endl;
    std::cout << "  Current system status:     " << strucToShow.CurSysStatus << std::endl;
    std::cout << "  Error correct metod:       " << strucToShow.ErrorCorrectsMetod << std::endl;
    std::cout << "  Additional version:        " << strucToShow.AdditionalVersion << std::endl;
    UnixTime = foursBytesToInt(strucToShow.LastIntegretyCheckTime);
    DailyTimeFormat = UnixTimeToDaily(UnixTime);
    std::cout << "  Last integrety check time: " << DailyTimeFormat << std::endl;
    std::cout << "  Interval for force check:  " << foursBytesToInt(strucToShow.IntervalForIntegretyForceCheck) << std::endl;
    std::cout << "  OS created FS name:        " << foursBytesToInt(strucToShow.OSCreatedFSName) << std::endl;
    std::cout << "  Main version:              " << foursBytesToInt(strucToShow.MainVersion) << std::endl;
    std::cout << "  UID whch can use rsvd blcks: " << strucToShow.UIDWhichCanUseReservedBlocks << std::endl;
    std::cout << "  GID whch can use rsvd blcks: " << strucToShow.GIDWhichCanUseReservedBlocks << std::endl;
    std::cout << "  First not reserved inode:  " << foursBytesToInt(strucToShow.FirstNotReservedInod) << std::endl;
    std::cout << "  Inode structure size:      " << strucToShow.InodeStructSize << std::endl;
    //std::cout << "  Grp num for this sprblck:  " << strucToShow.nGroupForThisSuperblock << std::endl;
    std::cout << "  Volume identificator:      " << foursBytesToInt(strucToShow.VolumeIdentificator) << std::endl;
    std::cout << "  Last mount path:           " << strucToShow.LastMountPath << std::endl;
    std::cout << "  ___________________________________________________________________________ " << std::endl;
    // ???? std::cout << "  Journal inode:             " << std::to_string(foursBytesToInt(strucToShow.JournalInode)) << std::endl;


}
bool letsTryToFindSuperBlock(std::string fullPath, HANDLE hConsoleHandle, unsigned int* blockSizeCalculated, unsigned int* BlockGroupSize, unsigned long long* superBlockOffsetDec)
{
    std::cout << "  File ";
    SetConsoleTextAttribute(hConsoleHandle, Blue | Black);
    std::cout << "exist";
    SetConsoleTextAttribute(hConsoleHandle, White | Black);
    std::cout << ", trying to find ";
    SetConsoleTextAttribute(hConsoleHandle, Green | Black);
    std::cout << "superblock";
    SetConsoleTextAttribute(hConsoleHandle, White | Black);
    std::cout << "..." << std::endl;;

    bool pointerRez = false;
    bool readRez = false;
    bool isItSuperBlock = false;
    const int SuperBlockSignature = 61267;
    HANDLE fileHandle = CreateFileA(
        fullPath.c_str(),
        GENERIC_READ,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL);
    if (fileHandle != INVALID_HANDLE_VALUE)
    {
        ULONGLONG startOffset = 0;
        BYTE buffer[512];
        DWORD bytesToRead = 512;
        DWORD bytesRead;
        LARGE_INTEGER sectorOffset;
        sectorOffset.QuadPart = 0;
        sectorOffset.LowPart = 512;
        superblock_offests* superblock_for_magic = reinterpret_cast <superblock_offests*> (buffer);

        unsigned long long currentPosition = SetFilePointer(fileHandle, NULL, NULL, FILE_BEGIN);
        if (currentPosition != INVALID_SET_FILE_POINTER)
        {

            pointerRez = true;
            bool readResult = ReadFile(fileHandle, buffer, bytesToRead, &bytesRead, NULL);
            if (readResult && bytesRead == bytesToRead)
            {
                readRez = true;
                if (((superblock_for_magic->Signature) == (SuperBlockSignature)) && ((superblock_for_magic->ErrorCorrectsMetod) > 0) && ((superblock_for_magic->ErrorCorrectsMetod) < 4) && ((int)(foursBytesToInt(superblock_for_magic->OSCreatedFSName)) > -1) && ((int)(foursBytesToInt(superblock_for_magic->OSCreatedFSName)) < 5) && ((int)(foursBytesToInt(superblock_for_magic->MainVersion)) > -1) && ((int)(foursBytesToInt(superblock_for_magic->MainVersion)) < 2))
                {
                    // std::cout << " This block offset (dec):  " << kbRead * 1024 << std::endl;
                    superBlockShow(*superblock_for_magic, currentPosition);
                    isItSuperBlock = true;
                    unsigned int blockSizeMult = foursBytesToInt(superblock_for_magic->BlockSize);
                    unsigned int blockSize = 1024;
                    unsigned int scale = 0;
                    while (scale < blockSizeMult)
                    {
                        blockSize = blockSize * 2;
                        scale++;
                    }
                    *BlockGroupSize = foursBytesToInt(superblock_for_magic->nBlocksPerGroup);
                    *blockSizeCalculated = blockSize;
                    *superBlockOffsetDec = currentPosition;
                    //del
                   //rabochaya std::cout << " cur pos 1 " << currentPosition << std::endl;
                }
                else
                {
                    while ((pointerRez == true) && (isItSuperBlock == false) && (readRez == true))
                    {
                        currentPosition = SetFilePointer(fileHandle, sectorOffset.LowPart, NULL, FILE_CURRENT);
                        if (currentPosition != INVALID_SET_FILE_POINTER)
                        {
                            pointerRez = true;
                            readResult = ReadFile(fileHandle, buffer, bytesToRead, &bytesRead, NULL);
                            if (readResult && bytesRead == bytesToRead)
                            {
                                readRez = true;
                                // std::cout << "  Kilobytes read: " << kbRead << std::endl;
                                if (((superblock_for_magic->Signature) == (SuperBlockSignature)) && ((superblock_for_magic->ErrorCorrectsMetod) > 0) && ((superblock_for_magic->ErrorCorrectsMetod) < 4) && ((int)(foursBytesToInt(superblock_for_magic->OSCreatedFSName)) > -1) && ((int)(foursBytesToInt(superblock_for_magic->OSCreatedFSName)) < 5) && ((int)(foursBytesToInt(superblock_for_magic->MainVersion)) > -1) && ((int)(foursBytesToInt(superblock_for_magic->MainVersion)) < 2))
                                {   //обнулять буффер?обновлять bytesRead?
                                   // std::cout << " This block offset (dec):  " << kbRead*1024 << std::endl;
                                    superBlockShow(*superblock_for_magic, currentPosition);
                                    isItSuperBlock = true;
                                    unsigned int blockSizeMult = foursBytesToInt(superblock_for_magic->BlockSize);
                                    unsigned int blockSize = 1024;
                                    unsigned int scale = 0;
                                    while (scale < blockSizeMult)
                                    {
                                        blockSize = blockSize * 2;
                                        scale++;
                                    }
                                    *blockSizeCalculated = blockSize;
                                    *BlockGroupSize = foursBytesToInt(superblock_for_magic->nBlocksPerGroup);
                                    *superBlockOffsetDec = currentPosition;
                                    //rabochaya std::cout << " cur pos 1 " << currentPosition << std::endl;
                                }
                            }
                            else
                            {
                                readRez = false;
                            }
                        }
                        else
                        {
                            pointerRez = false;
                        }
                    }
                }
            };
        };
    }

    CloseHandle(fileHandle);
    return isItSuperBlock;

}


int main()
{   
    HANDLE hConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    std::string pathToDir = ExePath();
    SetConsoleTextAttribute(hConsoleHandle, Green | Black);
    std::cout << "  ###########   ext4_file_recovery  ###########" << std::endl;
    SetConsoleTextAttribute(hConsoleHandle, White | Black);
    std::cout << "  At first, select the way to detect the drive image" << std::endl;
    std::cout << "  Manual control involves specifying the full path to the drive image  " << std::endl;
    std::cout << "  Automatic way require only file name, but drive image should be placed the same folder as exe file " << std::endl;
    std::cout << "  With either choice, you must ensure that ";
    SetConsoleTextAttribute(hConsoleHandle, Red | Black);
    std::cout << "there are no spaces";
    SetConsoleTextAttribute(hConsoleHandle, White | Black);
    std::cout << " in the file path. " << std::endl;
    std::cout << "  Enter '";
    SetConsoleTextAttribute(hConsoleHandle, Blue | Black);
    std::cout << "m";
    SetConsoleTextAttribute(hConsoleHandle, White | Black);
    std::cout << "' for manual or '";
    SetConsoleTextAttribute(hConsoleHandle, Blue | Black);
    std::cout << "a";
    SetConsoleTextAttribute(hConsoleHandle, White | Black);
    std::cout << "' for automatic search:   ";
    std::string ChoosedWay = "";
    std::cin >> ChoosedWay;
    bool noErrorWhileChoosingWay = false;
    if (ChoosedWay == "m" || ChoosedWay == "a")
    {
        noErrorWhileChoosingWay = true;
    }

    while (noErrorWhileChoosingWay == false)
    {
        std::cout << "  You set an incorrect detect way, try again:   ";
        std::cin >> ChoosedWay;
        if (ChoosedWay == "m" || ChoosedWay == "a")
        {
            noErrorWhileChoosingWay = true;
        }
    }
    std::string fileName = "";
    std::string fullPath = "";
    std::cout << "           Please, follow next steps:" << std::endl;
    if (ChoosedWay == "m")
    {
        std::cout << "  1.Enter the fullpath to the drive image or directly to the drive" << std::endl;
        std::cout << "  Example: \\\\.\\\\C:\\Users\\Anakim\\source\\example.img or \\\\.\\\\G:" << std::endl;
        std::cout << "  Full path:   ";
        std::cin >> fullPath;
        while (letsTryToOpenFile(fullPath) == false)
        {
            SetConsoleTextAttribute(hConsoleHandle, Red | Black);
            std::cout << "  Error:  Path to file or file name are incorrect." << std::endl;
            SetConsoleTextAttribute(hConsoleHandle, White | Black);
            std::cout << "  Also this error may occure if programm has not enought permitions to read it" << std::endl;
            std::cout << "  Just restart it with administrator permissions if so." << std::endl;
            std::cout << "  or try to insert full path again:   ";
            std::cin >> fullPath;
        }
    }

    if (ChoosedWay == "a")
    {
        std::cout << "  1.Place the drive image next to the exe file. Current folder:  " << pathToDir << std::endl;
        std::cout << "  2.Enter its name and format, f.e. file.img :  ";
        std::cin >> fileName;
        char longLifebackSlashChar = backSlashForCPP();
        std::string longLifebackSlashString(1, longLifebackSlashChar);
        fullPath = longLifebackSlashString + longLifebackSlashString + "." + longLifebackSlashString + pathToDir + longLifebackSlashString + fileName;
        while (letsTryToOpenFile(fullPath) == false)
        {

            SetConsoleTextAttribute(hConsoleHandle, Red | Black);
            std::cout << "  Error:  Path to file or file name are incorrect." << std::endl;
            SetConsoleTextAttribute(hConsoleHandle, White | Black);
            std::cout << "  Also this error may occure if programm has not enought permitions to read it." << std::endl;
            std::cout << "  Just restart it with administrator permissions if so." << std::endl;
            std::cout << "  or try to insert full path again:   ";
            std::cin >> fileName;
            fullPath = longLifebackSlashString + longLifebackSlashString + "." + longLifebackSlashString + pathToDir + longLifebackSlashString + fileName;
        }
    }
    sqlShow();
    unsigned int BlockSize = 0;
    unsigned int GroupSize = 0;
    unsigned long long sblockOffsetDec = 0;
    bool isSuperBlockExist = letsTryToFindSuperBlock(fullPath, hConsoleHandle, &BlockSize, &GroupSize, &sblockOffsetDec);
    if (isSuperBlockExist == false)
    {
        SetConsoleTextAttribute(hConsoleHandle, Red | Black);
        std::cout << "  Error: the file was checked but the superblock was not found. " << std::endl;
        SetConsoleTextAttribute(hConsoleHandle, White | Black);
    }
    else
    {
        SearchType* block_map = desicionWhatToCreate(BlockSize);
        if (block_map == NULL)
        {
            SetConsoleTextAttribute(hConsoleHandle, Red | Black);
            std::cout << "  Error: this block size is incorrect or unsupported yet. " << std::endl;
            SetConsoleTextAttribute(hConsoleHandle, White | Black);
        }
        else
        {
            block_map->info();
            block_map->blockMapRead(sblockOffsetDec, fullPath);
            block_map->searchingSignaturesShow();
            block_map->searchigFiles(sblockOffsetDec, fullPath);
        }
    }
    showMe();
}
