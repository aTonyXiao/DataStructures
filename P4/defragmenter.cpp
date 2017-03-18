#include "defragmenter.h"
#include "DefragRunner.h"

QuadraticHashTable::QuadraticHashTable(int sz)
: size(sz), curSz(0)
{
    disarr = new DiskInfo[size];
}

void QuadraticHashTable::insert( const DiskInfo & x )
{    
    int curPos;
    curPos = x.blockID % size;
    int curID = disarr[ curPos ].blockID;
    int xID = x.blockID;
    while (curID > 1 && curID != xID)
    {
        curPos++;
        curID = disarr[ curPos ].blockID;
    }
    if (curID == 0)
        curSz++;
    
    disarr[ curPos ] = x;
}


void QuadraticHashTable::remove( const DiskInfo & x )
{
    int curPos = x.blockID % size;
    
    int curID = disarr[ curPos ].blockID;
    int xID = x.blockID;
    
    while(curID!=0&&curID!=xID)
    {
        curPos++;
        curID = disarr[ curPos ].blockID;
    }
   
    
    if(curID == xID)
        disarr[ curPos ].blockID = 1;
}

DiskInfo & QuadraticHashTable::find( const DiskInfo & x )
{
    int curPos = x.blockID % size;
    int curID = disarr[ curPos ].blockID;
    int xID = x.blockID;
    while(curID!=0 && curID!=xID)
    {
        curPos++;
        curID = disarr[ curPos ].blockID;
    }
    
    if (curID == xID)
        return disarr[curPos];
    else
        return NO_RESULT;
}

DiskInfo & QuadraticHashTable::find( const int xID )
{
    int curPos = xID % size;
    int curID = disarr[ curPos ].blockID;
    while(curID!=0 && curID!=xID)
    {
        curPos++;
        curID = disarr[ curPos ].blockID;
    }
    
    if (curID != xID)
        return NO_RESULT;
    
    else
        return disarr[curPos];
//    返回未找到
}


 Defragmenter::Defragmenter(DiskDrive *diskDriv) : hash(179550), // 初始化整理方程
// 190000 可以 1700000 需要rehase 180000 不需要rehase 选择180000
// list size 越大 disk 读写越少
   diskDrive(diskDriv), listCount(1),curPos(2), topIndex(0)
 {
     backEmp = diskDrive->getCapacity() - 1;
     
     for(backEmp; backEmp >=0 ; backEmp--)
     {
         if(!diskDrive->FAT[backEmp])
             break;
     }
     int i = 0;
//     按照每个目录开始排序 block 直到遍历每个目录
      while (i< diskDrive->getNumFiles())
      {
        movFilePart1(diskDrive->directory[i]);
        i++;
      }
 }  // Defragmenter


void Defragmenter::saveBlock(int blockID)
{
    DiskBlock *tmp = diskDrive->readDiskBlock(blockID);
    diskDrive->FAT[blockID] = 0;
    //储存block
    int listIndex;
    //   初始化 list 设定数列下标
    if(listCount < 12109  || topIndex > 0)
    {   // 小于12101 上标大于0 表示在数组内
        if(topIndex > 0)
            listIndex = stake[--topIndex];
        else
            listIndex = listCount++;
        //   重复移动
        list[listIndex] = tmp;
        hash.insert(DiskInfo(blockID, -listIndex));
    }
    else
    {
        diskDrive->writeDiskBlock(tmp, backEmp);
        //     DiskBlock *tmp = diskDrive->readDiskBlock(blockID);
        //       delete tmp;
        diskDrive->FAT[backEmp] = 1;
        hash.insert(DiskInfo(blockID,backEmp));
        delete tmp;
        //       删除 临时变量
        for(; diskDrive->FAT[backEmp]; backEmp--);
        //   更新最后空位
    }
    
} 


 void Defragmenter::movFilePart1(DirectoryEntry &entry)
 {
   int srcID = entry.getFirstBlockID(), nextID;
   entry.setFirstBlockID(curPos);
   while(srcID != 1)//只要不是第一位的Disk
   {
     DiskBlock *tmp = getSrcBlock(srcID);
     nextID = tmp->getNext();
     
       if(srcID == curPos)
       {
           if(nextID != curPos + 1)
           {
               tmp->setNext(curPos + 1);
               diskDrive->writeDiskBlock(tmp, curPos);
               diskDrive->FAT[curPos] = 1;
           }  // if next pointer is not pointing at the next block position
           
       }  // if source and destination not the same.
       else  // from the same position
       {
           
           if(diskDrive->FAT[curPos]) // if not empty
               saveBlock(curPos);
           
           tmp->setNext(curPos + 1);
           diskDrive->writeDiskBlock(tmp, curPos);
           diskDrive->FAT[curPos] = 1;
           
//        移动文件完成
           
       }
     
     delete tmp; //删除临时block
     srcID = nextID;
     curPos++;
   }
     //call part2
   
 }



//
//void Defragmenter::movFilePart2(DirectoryEntry &entry)
//{
//    setFirstBlockID(curPos);
//    while(srcID != 1)//只要不是第一位的Disk
//    {
//        DiskBlock *tmp = getSrcBlock(srcID);
//        nextID = tmp->getNext();
//        
//        if(srcID == curPos)
//        {
//            if(nextID != curPos + 1)
//            {
//                skBlock(tmp, curPos);
//                diskDrive->FAT[curPos] = 1;
//            }  // if next pointer is not pointing at the next block position
//            
//        }  // if source and destination not the same.
//        else  // from the same position
//        {
//            //            //        移动文件完成
//            
//        }
//        
//        delete tmp; //删除临时block
//
//    }
//    
//}
//
// 

 DiskBlock* Defragmenter::getSrcBlock(int srcID)
 {
   DiskBlock *tmp;
   DiskInfo diskInfo2, diskInfo = hash.find(srcID);
     int disloc = diskInfo.curLoc;
   if(disloc == 0)
   {
     tmp = diskDrive->readDiskBlock(srcID);
     diskDrive->FAT[srcID] = 0;
     if(srcID > backEmp)
       backEmp = srcID;
   }
   else
   {
     while(disloc > 0
       && (hash.find(disloc).curLoc != 0))
     {
       hash.remove(diskInfo);
       diskInfo = hash.find(disloc);
         disloc = diskInfo.curLoc;
         
     }
     
     hash.remove(diskInfo);
//      从hashtable 中剔除 已找到disk
     if(disloc < 0) // if in list
     {
       tmp = list[-disloc];
       stake[topIndex++] = -disloc;
     }
     else
     {
       tmp = diskDrive->readDiskBlock(disloc);
      diskDrive->FAT[disloc] = 0;
       
      if(disloc > backEmp)
        backEmp = disloc;
     }
    }  // in HashTable

   return tmp;
 } // getSrcBlock()
   
 

//需要修改
//void Defragmenter::findEmpty()
//{
//    backEmp = diskDrive->getCapacity() - 1;
//    
//    for(backEmp; backEmp >=0 ; backEmp--)
//    {
//        if(!diskDrive->FAT[backEmp])
//            break;
//    }
//    
//    cout << backEmp << endl;
//
//}

 
