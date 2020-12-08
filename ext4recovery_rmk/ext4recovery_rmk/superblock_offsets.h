#pragma pack(push,1)
#include <Windows.h>
struct superblock_offests
{
    BYTE nInodeinSystem[4];//0-3
    BYTE nBlocksinSystem[4];//4-7
    BYTE nBlocksReserved[4];//8-11
    BYTE nBlocksFree[4];//12-15
    BYTE nInodesFree[4];//16-19
    BYTE ZeroGroupBlock[4];//20-23
    BYTE BlockSize[4];//24-27
    BYTE FragmentSize[4];//28-31
    BYTE nBlocksPerGroup[4];//32-35
    BYTE nFragmentsPerGroup[4];//36-39
    BYTE nInodesPerGroup[4];//40-43
    BYTE LastTimeMounted[4];//44-47
    BYTE LastWriteTime[4];//48-51
    WORD CurnOfMounts;//52-53
    WORD MaxnOfMounts;//54-55
    WORD Signature;//56-57 0xef53
    WORD CurSysStatus;//58-59
    WORD ErrorCorrectsMetod;//60-61
    WORD AdditionalVersion;//62-63
    BYTE LastIntegretyCheckTime[4];//64-67
    BYTE IntervalForIntegretyForceCheck[4];//68-71
    BYTE OSCreatedFSName[4];//72-75
    BYTE MainVersion[4];//76-79
    WORD UIDWhichCanUseReservedBlocks;//80-81
    WORD GIDWhichCanUseReservedBlocks;//82-83
    BYTE FirstNotReservedInod[4];//84-87
    DWORD InodeStructSize;//88-89
    DWORD nGroupForThisSuperblock;//90-91
    BYTE CompatibilityFlag[4];//92-95
    BYTE UnCompatibilityFlag[4];//96-99
    BYTE FlagsOnlyForRead[4];//100-103
    BYTE FSidentificator[16];//104-119
    BYTE VolumeIdentificator[12];//120-135 34
    BYTE LastMountPath[68];//136-199 50
    BYTE AlghoritmBitmap[4];//200-203 51
    BYTE nBlocksPrealocatedForFile;//204-204 
    BYTE nBlocksPrealocatedForDir;//205-205
    DWORD notUsed0;//206-207 52
    BYTE JournalIdentificator[16];//208-223  56
    BYTE JournalInode[4];//224-227 57
    BYTE JournalDevice[4];//228-231 58
    BYTE FreezedInodesCount[4];//232-235 59
    BYTE NotUsed1[22]; //236-255
    BYTE fs_mk_time[4];//264-267
    BYTE NotUsed2[244];//236-1023

};
