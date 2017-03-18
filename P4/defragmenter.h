#include "DefragRunner.h"


class DiskInfo
{
public:
    int blockID;
    int curLoc;
    DiskInfo(int bID = 0, int cL = 0) : blockID(bID), curLoc(cL) {}
};

class QuadraticHashTable
{
public:
    explicit QuadraticHashTable(int siz);
    DiskInfo & find( const DiskInfo & x );
    DiskInfo & find( const int xID );
    // DiskInfo & insert ( DiskInfo & x );
    void insert( const DiskInfo & x );
    // DiskInfo & remove ( DiskInfo & x );
    void remove( const DiskInfo & x );
    
    DiskInfo *disarr;
    int size;
    int curSz;
    DiskInfo NO_RESULT;
};


class Defragmenter
{
  QuadraticHashTable hash;
    // list size 越大 disk 读写越少
//    测试 最大不超过8m 的是12102
  DiskBlock* list[12109];
  int stake[12109];
  DiskDrive *diskDrive;
  
  int listCount;
  int curPos;
  int backEmp;
  int topIndex;
  DiskBlock* getSrcBlock(int srcID);
  void movFilePart1(DirectoryEntry &entry);
   // void movFilePart2(DirectoryEntry &entry);
  void saveBlock(int blockID);
public:
  Defragmenter(DiskDrive *diskDrive);

};
