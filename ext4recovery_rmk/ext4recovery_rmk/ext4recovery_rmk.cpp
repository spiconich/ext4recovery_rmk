#include <iostream>
#include <Windows.h>
#include <string>
#include "console_colors.h"
#include "superblock_offsets.h"
#include "classes_blocks_addrs.h" 
class Superblock
{
public:
    virtual void superBlockShow(superblock_offests strucToShow, unsigned long long offset) = 0;
    virtual bool letsTryToFindSuperBlock(std::string fullPath, HANDLE hConsoleHandle, unsigned int* blockSizeCalculated, unsigned int* BlockGroupSize, unsigned long long* superBlockOffsetDec) = 0;
    virtual ~Superblock() {}
};
class SuperblockNode : public Superblock
{
    void superBlockShow(superblock_offests strucToShow, unsigned long long offset)
    {
        std::cout << "                                                                       " << std::endl;
        std::cout << "  ______________________S_U_P_E_R__B_L_O_C_K__F_O_U_N_D______________________ " << std::endl;
        std::cout << "" << std::endl;;
        std::cout << "  Super block offset (dec):  " << offset << std::endl;;
        std::cout << "  Inodes count:              " << translator->foursBytesToIntx(strucToShow.nInodeinSystem) << std::endl;
        GLOBAL_num_of_groups = translator->foursBytesToIntx(strucToShow.nBlocksinSystem);
        std::cout << "  Blocks count:              " << translator->foursBytesToIntx(strucToShow.nBlocksinSystem) << std::endl;
        std::cout << "  Reserved block count:      " << translator->foursBytesToIntx(strucToShow.nBlocksReserved) << std::endl;
        std::cout << "  Free blocks:               " << translator->foursBytesToIntx(strucToShow.nBlocksFree) << std::endl;
        std::cout << "  Free inodes:               " << translator->foursBytesToIntx(strucToShow.nInodesFree) << std::endl;
        std::cout << "  First block:               " << translator->foursBytesToIntx(strucToShow.ZeroGroupBlock) << std::endl;
        unsigned int blockSizeMult = translator->foursBytesToIntx(strucToShow.BlockSize);
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
        unsigned int FragSizeMult = translator->foursBytesToIntx(strucToShow.FragmentSize);
        int FragSize = 1024;
        scale = 0;
        while (scale < FragSizeMult)
        {
            FragSize = FragSize * 2;
            scale++;
        }
        std::cout << "  Fragment size:             " << FragSize << std::endl;
        std::cout << "  Blocks per group:          " << translator->foursBytesToIntx(strucToShow.nBlocksPerGroup) << std::endl;
        std::cout << "  Fragments per group:       " << translator->foursBytesToIntx(strucToShow.nFragmentsPerGroup) << std::endl;
        std::cout << "  Inodes per group:          " << translator->foursBytesToIntx(strucToShow.nInodesPerGroup) << std::endl;
        unsigned int UnixTime = translator->foursBytesToIntx(strucToShow.fs_mk_time);
        std::string DailyTimeFormat = translator->UnixTimeToDaily(UnixTime);
        std::cout << "  FS create time:            " << DailyTimeFormat << std::endl;
        UnixTime = translator->foursBytesToIntx(strucToShow.LastTimeMounted);
        DailyTimeFormat = translator->UnixTimeToDaily(UnixTime);

        std::cout << "  Last mount time:           " << DailyTimeFormat << std::endl;
        UnixTime = translator->foursBytesToIntx(strucToShow.LastWriteTime);
        DailyTimeFormat = translator->UnixTimeToDaily(UnixTime);
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
        UnixTime = translator->foursBytesToIntx(strucToShow.LastIntegretyCheckTime);
        DailyTimeFormat = translator->UnixTimeToDaily(UnixTime);
        std::cout << "  Last integrety check time: " << DailyTimeFormat << std::endl;
        std::cout << "  Interval for force check:  " << translator->foursBytesToIntx(strucToShow.IntervalForIntegretyForceCheck) << std::endl;
        std::cout << "  OS created FS name:        " << translator->foursBytesToIntx(strucToShow.OSCreatedFSName) << std::endl;
        std::cout << "  Main version:              " << translator->foursBytesToIntx(strucToShow.MainVersion) << std::endl;
        std::cout << "  UID whch can use rsvd blcks: " << strucToShow.UIDWhichCanUseReservedBlocks << std::endl;
        std::cout << "  GID whch can use rsvd blcks: " << strucToShow.GIDWhichCanUseReservedBlocks << std::endl;
        std::cout << "  First not reserved inode:  " << translator->foursBytesToIntx(strucToShow.FirstNotReservedInod) << std::endl;
        std::cout << "  Inode structure size:      " << strucToShow.InodeStructSize << std::endl;
        //std::cout << "  Grp num for this sprblck:  " << strucToShow.nGroupForThisSuperblock << std::endl;
        std::cout << "  Volume identificator:      " << translator->foursBytesToIntx(strucToShow.VolumeIdentificator) << std::endl;
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
                    if (((superblock_for_magic->Signature) == (SuperBlockSignature)) && ((superblock_for_magic->ErrorCorrectsMetod) > 0) && ((superblock_for_magic->ErrorCorrectsMetod) < 4) && ((int)(translator->foursBytesToIntx(superblock_for_magic->OSCreatedFSName)) > -1) && ((int)(translator->foursBytesToIntx(superblock_for_magic->OSCreatedFSName)) < 5) && ((int)(translator->foursBytesToIntx(superblock_for_magic->MainVersion)) > -1) && ((int)(translator->foursBytesToIntx(superblock_for_magic->MainVersion)) < 2))
                    {
                        // std::cout << " This block offset (dec):  " << kbRead * 1024 << std::endl;
                        superBlockShow(*superblock_for_magic, currentPosition);
                        isItSuperBlock = true;
                        unsigned int blockSizeMult = translator->foursBytesToIntx(superblock_for_magic->BlockSize);
                        unsigned int blockSize = 1024;
                        unsigned int scale = 0;
                        while (scale < blockSizeMult)
                        {
                            blockSize = blockSize * 2;
                            scale++;
                        }
                        *BlockGroupSize = translator->foursBytesToIntx(superblock_for_magic->nBlocksPerGroup);
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
                                    if (((superblock_for_magic->Signature) == (SuperBlockSignature)) && ((superblock_for_magic->ErrorCorrectsMetod) > 0) && ((superblock_for_magic->ErrorCorrectsMetod) < 4) && ((int)(translator->foursBytesToIntx(superblock_for_magic->OSCreatedFSName)) > -1) && ((int)(translator->foursBytesToIntx(superblock_for_magic->OSCreatedFSName)) < 5) && ((int)(translator->foursBytesToIntx(superblock_for_magic->MainVersion)) > -1) && ((int)(translator->foursBytesToIntx(superblock_for_magic->MainVersion)) < 2))
                                    {   //обнулять буффер?обновлять bytesRead?
                                       // std::cout << " This block offset (dec):  " << kbRead*1024 << std::endl;
                                        superBlockShow(*superblock_for_magic, currentPosition);
                                        isItSuperBlock = true;
                                        unsigned int blockSizeMult = translator->foursBytesToIntx(superblock_for_magic->BlockSize);
                                        unsigned int blockSize = 1024;
                                        unsigned int scale = 0;
                                        while (scale < blockSizeMult)
                                        {
                                            blockSize = blockSize * 2;
                                            scale++;
                                        }
                                        *blockSizeCalculated = blockSize;
                                        *BlockGroupSize = translator->foursBytesToIntx(superblock_for_magic->nBlocksPerGroup);
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
};
class SuperblockFactory
{
public:
    virtual Superblock* createNode() = 0;
    virtual ~SuperblockFactory() {}
};
class SuperblockFactoryCreate : public SuperblockFactory
{
public:
    Superblock* createNode()
    {
        return new SuperblockNode;
    }
};

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

int main()
{
    HANDLE hConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    std::string pathToDir = ExePath();
    SetConsoleTextAttribute(hConsoleHandle, Green | Black);
    std::cout << "  ###########   ext4_file_recovery  ###########" << std::endl;
    SetConsoleTextAttribute(hConsoleHandle, White | Black);
    signature_interact->addingUserSign();
    signature_interact->sqlShow();
    SuperblockFactoryCreate* superblock_create = new SuperblockFactoryCreate;
    Superblock* superblock = superblock_create->createNode();
    std::cout << "  As next, select the way to detect the drive image" << std::endl;
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
    unsigned int BlockSize = 0;
    unsigned int GroupSize = 0;
    unsigned long long sblockOffsetDec = 0;
    bool isSuperBlockExist = superblock->letsTryToFindSuperBlock(fullPath, hConsoleHandle, &BlockSize, &GroupSize, &sblockOffsetDec);
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
            block_map->setRecoveryConfiguration();            
            block_map->blockMapRead(sblockOffsetDec, fullPath);
            block_map->searchingSignaturesShow();
            block_map->searchigFiles(sblockOffsetDec, fullPath);
        }
    }
    showMe();
}
