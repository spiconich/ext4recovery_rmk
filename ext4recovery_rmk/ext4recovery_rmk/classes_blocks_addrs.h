#pragma once
#include <iostream>
#include <Windows.h>
#include <string>
#include "files_signatures.h"

unsigned int blocksaddr[256];//refr 0..255 ->> áûëî [255] 0..254, îøèáñÿ...
unsigned long infoFromOffsets[256];//refr 0..255
unsigned int nOfRecoveredFile = 1000000;
bool EightBytes[8];


unsigned int foursBytesToIntx(byte* buffer)
{
    unsigned int resultingInt = unsigned int((unsigned char)(buffer[3]) << 24 |
        (unsigned char)(buffer[2]) << 16 |
        (unsigned char)(buffer[1]) << 8 |
        (unsigned char)(buffer[0]));
    return resultingInt;
}
void tellIfFound()
{
    std::cout << std::endl;
    std::cout << "  Block maps founded, saving offsets to group blocks...  " << std::endl;
};
void ByteToEightBits(int one_byte)
{
    EightBytes[0] = one_byte % 2;
    one_byte = one_byte / 2;
    EightBytes[1] = one_byte % 2;
    one_byte = one_byte / 2;
    EightBytes[2] = one_byte % 2;
    one_byte = one_byte / 2;
    EightBytes[3] = one_byte % 2;
    one_byte = one_byte / 2;
    EightBytes[4] = one_byte % 2;
    one_byte = one_byte / 2;
    EightBytes[5] = one_byte % 2;
    one_byte = one_byte / 2;
    EightBytes[6] = one_byte % 2;
    one_byte = one_byte / 2;
    EightBytes[7] = one_byte % 2;
}
BYTE signDetect(unsigned int first_byte, unsigned int second_byte, unsigned int third_byte)
{   //microsoft_word_docx
    if ((first_byte == microsoft_word::first_4bytes) && (second_byte == microsoft_word::second_4bytes))
    {
        return SIGN_MICROSOFT_WORD;
    }
    else
    {
        return NULL;
    }
}

class SearchType
{
public:
    typedef struct Block_map_offsets
    {
        BYTE GroupBlock[4];
        BYTE GroupInode[4];
        BYTE noMatter[56];
    };
    typedef struct zeroBytes
    {
        BYTE hopeZeroOne[4];
        BYTE hopeZeroTwo[4];
    };
    void searchingSignaturesShow()
    {
        std::cout << std::endl;
        std::cout << "  Going to search signatures in file...  " << std::endl;
    }
    virtual void info() = 0;
    virtual void recoveringFile(unsigned long long sbOffset, unsigned long long foundedSignAddr, std::string fullPath,BYTE WhatsSign) = 0;
    virtual void searchigFiles(unsigned long long sbOffset, std::string fullPath) = 0;
    virtual bool discoveringIfBlockSetUsDeleted(unsigned long long sbOffset, unsigned long long foundedSignAddr, std::string fullPath) = 0;
    virtual void blockMapRead(unsigned long long sbOffset, std::string fullPath) = 0;
    virtual ~SearchType() {}

};

class BlockMap4096 : public SearchType
{
    void info()
    {
        std::cout << std::endl;
        std::cout << "  Going to look for block map, using 4kb block size us detected" << std::endl;
    }
    bool discoveringIfBlockSetUsDeleted(unsigned long long sbOffset, unsigned long long foundedSignAddr, std::string fullPath)
    {   //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        const unsigned char MAX_GROUP_NUM = 255;
        const int BLOCKSIZEX = 4096;
        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        bool whatToReturn = false;
        unsigned long long sbOffsetButReal = 0;
        while ((sbOffsetButReal + BLOCKSIZEX) < sbOffset)
        {
            sbOffsetButReal = sbOffsetButReal + BLOCKSIZEX; // ukazivaet na nachalo bloka a ne na nachalo superbloka kak ran'we.
        }
        //std::cout << foundedSignAddr << std::endl;
        unsigned long long thisBlockGroupNumber = (foundedSignAddr - sbOffsetButReal) / BLOCKSIZEX;
        thisBlockGroupNumber = thisBlockGroupNumber / BLOCKSIZEX;
        thisBlockGroupNumber = thisBlockGroupNumber / 8;
        if (thisBlockGroupNumber <= MAX_GROUP_NUM)
        {
            // std::cout <<"  N group"<< blocksaddr[thisBlockGroupNumber] << std::endl;
            unsigned long long offsetToReadBinary = blocksaddr[thisBlockGroupNumber];
            offsetToReadBinary = offsetToReadBinary * BLOCKSIZEX;
            HANDLE fileHandlex = CreateFileA(
                fullPath.c_str(),
                GENERIC_READ,
                FILE_SHARE_READ | FILE_SHARE_WRITE,
                NULL,
                OPEN_EXISTING,
                FILE_ATTRIBUTE_NORMAL,
                NULL);
            if (fileHandlex != INVALID_HANDLE_VALUE)
            {
                ULONGLONG startOffset = 0;
                BYTE buffer[BLOCKSIZEX];
                DWORD bytesToRead = BLOCKSIZEX;
                DWORD bytesRead;
                LARGE_INTEGER sectorOffset;
                sectorOffset.QuadPart = 0;
                sectorOffset.LowPart = BLOCKSIZEX;
                Block_map_offsets* map = reinterpret_cast <Block_map_offsets*> (buffer);
                unsigned long long currentPosition = 0;
                currentPosition = SetFilePointer(fileHandlex, offsetToReadBinary, NULL, FILE_BEGIN);
                //std::cout << " test: " << currentPosition << " = " << offsetToReadBinary << std::endl;
               // std::cout << " blocksaddr[" << thisBlockGroupNumber << "]:" << blocksaddr[thisBlockGroupNumber] << std::endl;
                BYTE buffer_no_array[1];
                unsigned long long firstByteOffset = (thisBlockGroupNumber * BLOCKSIZEX * 8 * BLOCKSIZEX) + sbOffsetButReal;  // ïåðâûé áàéò â íóæíîé ãðóïïå â êàðòå çàíÿòîñòè áëîêîâ
                unsigned int bitOnMapWeRInterestedIn = (foundedSignAddr - firstByteOffset) / BLOCKSIZEX;
                unsigned int ByteWeNeed = bitOnMapWeRInterestedIn / 8;
                sectorOffset.LowPart = ByteWeNeed;// byteOnMapWeRInterestedIn
                unsigned int bitOnMapWeRInterestedInOneOfEight = bitOnMapWeRInterestedIn - (ByteWeNeed * 8);
                currentPosition = SetFilePointer(fileHandlex, sectorOffset.LowPart, NULL, FILE_CURRENT);
                if (currentPosition != INVALID_SET_FILE_POINTER)
                {
                    bytesToRead = 1;
                    bool readResult = ReadFile(fileHandlex, buffer_no_array, bytesToRead, &bytesRead, NULL);
                    if (readResult && bytesRead == bytesToRead)
                    {
                        ByteToEightBits(int(buffer_no_array[0]));

                        if (EightBytes[bitOnMapWeRInterestedInOneOfEight] == false)
                        {
                            whatToReturn = true;
                        }

                    }
                }
            }

            CloseHandle(fileHandlex);

        }
        else
        {
            std::cout << "  Error: some problems accured with group blocks count..." << std::endl;
        }
        return whatToReturn;
    }
    void recoveringFile(unsigned long long sbOffset, unsigned long long foundedSignAddr, std::string fullPath,BYTE WhatsSign)
    {   //~~~~~~~~~~~~~~~~~~~~~~~~~~~
        const int BLOCKSIZE = 4096;
        //~~~~~~~~~~~~~~~~~~~~~~~~~~~
        const unsigned short BYTESTOREADLOOP = 8;

        HANDLE fileHandleRecoveryRead = CreateFileA(
            fullPath.c_str(),
            GENERIC_READ,
            FILE_SHARE_READ | FILE_SHARE_WRITE,
            NULL,
            OPEN_EXISTING,
            FILE_ATTRIBUTE_NORMAL,
            NULL);
        if (fileHandleRecoveryRead != INVALID_HANDLE_VALUE)
        {   
            //Creating file
            std::string createdFileName;
            if (WhatsSign == SIGN_MICROSOFT_WORD)
            {
                createdFileName = std::to_string(nOfRecoveredFile) + "." + microsoft_word_string;
            }
            HANDLE fileHandleRecoveryWrite = CreateFileA(
                createdFileName.c_str(),
                GENERIC_READ,
                FILE_SHARE_READ | FILE_SHARE_WRITE,
                NULL,
                CREATE_NEW,
                FILE_ATTRIBUTE_NORMAL,
                NULL
            );
            if (fileHandleRecoveryRead != INVALID_HANDLE_VALUE)
            {
                nOfRecoveredFile++;
            }
            else
            {
                std::cout << "ERROR WHILE CREATING FILE" << std::endl;
            }
            ULONGLONG startOffset = 0;
            BYTE buffer[BLOCKSIZE];
            BYTE bufferForLoop[BYTESTOREADLOOP];
            DWORD bytesToRead = BLOCKSIZE;
            DWORD bytesRead;
            LARGE_INTEGER sectorOffset;
            sectorOffset.QuadPart = 0;
            sectorOffset.LowPart = BLOCKSIZE;
            unsigned long long currentPosition = 0;
            currentPosition = SetFilePointer(fileHandleRecoveryRead, foundedSignAddr, NULL, FILE_BEGIN);//bil FILE_CURRENT
            //std::cout << " naw test: " << currentPosition << " = " << foundedSignAddr << std::endl;
            std::cout << currentPosition << std::endl;
            bool ReadError = false;
            bool endOfFile = false; // ne zavisimo ot togo kakim sposobom, no vsegda doljen stat' true inache vse zaciklitsya
            bool readResult;
            bool zeroByteFound;
            unsigned int walker = 0;
            unsigned long long startPos = 0;
            unsigned long long eightBytesFromTheEndReaden = 1;//starts from 1 // dlya loop
            unsigned long long LastRecoveryByteOffset = 0;
            unsigned long long firstLoopByte = 0;
            unsigned long long secondLoopByte = 0;         
            zeroBytes* strucForLoop = reinterpret_cast <zeroBytes*> (bufferForLoop);
            // at this moment currentPosition in fileHandleRecoveryRead == foundedSignAddr      
            startPos = foundedSignAddr;

            while ((currentPosition != INVALID_SET_FILE_POINTER) && (endOfFile == false)) // starting from this moment non-stop reading, no pos return
            {   
                std::cout << " ----------------------------------------------------" << std::endl;
                std::cout << "     StartPos: " << startPos << std::endl;
                //checking last 8 bytes of  the first file block
                currentPosition = SetFilePointer(fileHandleRecoveryRead, startPos + BLOCKSIZE - (eightBytesFromTheEndReaden * BYTESTOREADLOOP), NULL, FILE_BEGIN); // nado budet kajdiy raz uchitivat' smewenie ot READ
                std::cout << "PosBeforeRead:" << currentPosition << std::endl;
                readResult = ReadFile(fileHandleRecoveryRead, bufferForLoop, BYTESTOREADLOOP, &bytesRead, NULL);
                currentPosition = SetFilePointer(fileHandleRecoveryRead, startPos + BLOCKSIZE - (eightBytesFromTheEndReaden * BYTESTOREADLOOP), NULL, FILE_BEGIN);
                firstLoopByte = foursBytesToIntx(strucForLoop->hopeZeroOne);
                secondLoopByte = foursBytesToIntx(strucForLoop->hopeZeroTwo);
                std::cout <<"f: "<<firstLoopByte << ", s:"<< secondLoopByte << std::endl;
                if ((firstLoopByte == 0) && (secondLoopByte) == 0)//zero found at the end last 8 bytes
                {
                    // prodoljaem idti s nachala v konec
                    endOfFile = true; 
                    /* the EOF detected, caz last 8 bytes was not zero...
                     prodoljaem idti s nachala v konec*/
                    const short BYTESTOREADSMALLLOOP = 1;
                    unsigned int oneByteFromTheEndReadenCount = 0;//after four bytes
                    unsigned short thisByteRez=0;
                    BYTE bufferForSmallLoop[BYTESTOREADSMALLLOOP];
                    while ((startPos<=currentPosition)&&(thisByteRez==0))
                    {
                        oneByteFromTheEndReadenCount++;
                        currentPosition = SetFilePointer(fileHandleRecoveryRead, startPos + BLOCKSIZE - (eightBytesFromTheEndReaden * BYTESTOREADLOOP)-(oneByteFromTheEndReadenCount * BYTESTOREADSMALLLOOP), NULL, FILE_BEGIN);
                        readResult = ReadFile(fileHandleRecoveryRead, bufferForSmallLoop, BYTESTOREADSMALLLOOP, &bytesRead, NULL);
                        currentPosition = SetFilePointer(fileHandleRecoveryRead, startPos + BLOCKSIZE - (eightBytesFromTheEndReaden * BYTESTOREADLOOP)-(oneByteFromTheEndReadenCount * BYTESTOREADSMALLLOOP), NULL, FILE_BEGIN); // nado budet kajdiy raz uchitivat' smewenie ot READ
                        thisByteRez = (unsigned char)(bufferForSmallLoop[0]);
                        LastRecoveryByteOffset = currentPosition;
                    }
                }
                else
                {                  
                    startPos = startPos + BLOCKSIZE;
                    //checking bitmap , zdes' nujno ewe proveryat', probably bug there
                    endOfFile = !discoveringIfBlockSetUsDeleted(sbOffset, startPos, fullPath);
                    if (endOfFile == true)
                    {
                        LastRecoveryByteOffset = startPos - 1;
                    }
                }
            }
            std::cout << "LastRecoveryByteOffset: "<< LastRecoveryByteOffset << std::endl;
            //there are curpos== invalid or eof==true
            //recovery file there if curpos!=invalid

            CloseHandle(fileHandleRecoveryWrite);
           // std::cout << currentPosition << " " << foundedSignAddr << std::endl;
        }
        else
        {
            std::cout << "  Error: fake file handle" << std::endl;
        }
        CloseHandle(fileHandleRecoveryRead);
    }

    void blockMapRead(unsigned long long sbOffset, std::string fullPath)
    {
        const int BLOCKSIZE = 4096;
        const int SCRUCT_SIZE = 64;
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
            BYTE buffer[SCRUCT_SIZE];
            DWORD bytesToRead = SCRUCT_SIZE;
            DWORD bytesRead;
            LARGE_INTEGER sectorOffset;
            sectorOffset.QuadPart = 0;
            sectorOffset.LowPart = BLOCKSIZE;
            Block_map_offsets* map = reinterpret_cast <Block_map_offsets*> (buffer);
            unsigned long long currentPosition = 0;
            unsigned long long sbOffsetButReal = 0;
            while ((sbOffsetButReal + BLOCKSIZE) < sbOffset)
            {
                sbOffsetButReal = sbOffsetButReal + BLOCKSIZE; // ukazivaet na nachalo bloka a ne na nachalo superbloka kak ran'we.
            }
            currentPosition = SetFilePointer(fileHandle, sbOffsetButReal+BLOCKSIZE, NULL, FILE_BEGIN);//NEXT BLOCK AFTER SUPERBLOCK
            
            //std::cout << "test sb: " << currentPosition << " = " << sbOffsetButReal << std::endl;
            if (currentPosition != INVALID_SET_FILE_POINTER)
            {
                int obv_size = 0;
                bool readResult;
                bool noFail = true;
                while ((obv_size < 256) && (noFail==true))
                {
                    readResult = ReadFile(fileHandle, buffer, bytesToRead, &bytesRead, NULL);
                    if (readResult && bytesRead == bytesToRead)
                    {
                        blocksaddr[obv_size] = foursBytesToIntx(map->GroupBlock);//zapolnyaem massiv s nomerami blokov dlya vosstanovleniya
                        //std::cout << "group num: " << obv_size << " " << blocksaddr[obv_size] << std::endl;
                        obv_size++;
                    }
                    else
                    {
                        noFail = false;
                    }
                }
                if (noFail == true)
                {
                    tellIfFound();
                }
                else
                {
                    std::cout << "  Error: reading error" << std::endl;
                }
            }
            else
            {
                std::cout << "  Error: invalid set file pointer" << std::endl;
            }
        }
        else
        {
            std::cout << "  Error: fake file handle" << std::endl;
        }
        CloseHandle(fileHandle);

    }
    void searchigFiles(unsigned long long sbOffset, std::string fullPath)
    { //~~~~~~~~~~~~~~~~~~~~~~~~~~~

        const int BLOCKSIZE = 4096;
        const int SIGNATURESIZE = 12;

        //~~~~~~~~~~~~~~~~~~~~~~~~~~~


        unsigned long first_bytes_rez = 0;
        unsigned long second_bytes_rez = 0;
        unsigned long third_bytes_rez = 0;
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
            BYTE buffer[SIGNATURESIZE];
            DWORD bytesToRead = SIGNATURESIZE;
            DWORD bytesRead;
            LARGE_INTEGER sectorOffset;
            sectorOffset.QuadPart = 0;
            sectorOffset.LowPart = BLOCKSIZE;
            twelve_bits* map = reinterpret_cast <twelve_bits*> (buffer);
            unsigned long long currentPosition = 0;
            unsigned long long sbOffsetButReal = 0;
            while ((sbOffsetButReal + BLOCKSIZE) < sbOffset)
            {
                sbOffsetButReal = sbOffsetButReal + BLOCKSIZE; // ukazivaet na nachalo bloka a ne na nachalo superbloka kak ran'we.
            }
            currentPosition = SetFilePointer(fileHandle, sbOffsetButReal + BLOCKSIZE+BLOCKSIZE, NULL, FILE_CURRENT);//VTOROY BLOCK POSLE SUPERBLOCKA
            
            //std::cout << "XXX:"<< currentPosition << " = " << sbOffset + BLOCKSIZE;
            bool ReadError = false;
            while (currentPosition != INVALID_SET_FILE_POINTER && (ReadError == false))
            {
                bool readResult = ReadFile(fileHandle, buffer, bytesToRead, &bytesRead, NULL);
                if (readResult && bytesRead == bytesToRead)
                {   //--------------------------------------------------       
                    first_bytes_rez = foursBytesToIntx(map->first_bytes);
                    second_bytes_rez = foursBytesToIntx(map->second_bytes);
                    third_bytes_rez = foursBytesToIntx(map->third_bytes);
                    BYTE SignResult = signDetect(first_bytes_rez, second_bytes_rez, third_bytes_rez);
                    if (SignResult != NULL)
                    {
                        bool ifNeedToRecover = discoveringIfBlockSetUsDeleted(sbOffset, currentPosition, fullPath);
                        if (ifNeedToRecover == true)
                        {
                            std::cout << "  Signature found at " << currentPosition << " going to recover..." << std::endl;
                            recoveringFile(sbOffset,currentPosition,fullPath, SignResult);
                        }
                    }
                }
                else
                {
                    ReadError = true;
                }
                currentPosition = SetFilePointer(fileHandle, sectorOffset.LowPart - SIGNATURESIZE, NULL, FILE_CURRENT);
            }
            std::cout << "  File fully read..." << std::endl;
        }
        else
        {
            std::cout << "  Error: fake file handle" << std::endl;
        }
        CloseHandle(fileHandle);

    }
};

class Factory
{
public:
    virtual SearchType* createSystemType() = 0;
    virtual ~Factory() {}
};

class Factory4096 : public Factory
{
public:
    SearchType* createSystemType()
    {
        return new BlockMap4096;
    }
};

SearchType* desicionWhatToCreate(int blockSize)
{
    if (blockSize == 4096)
    {
        //if+4096
        Factory4096* factory4096 = new Factory4096;
        return factory4096->createSystemType();
    }
    else
    {
        return NULL;
    }
}
