/******** DOS HEADER ********/
typedef struct _IMAGE_DOS_HEADER // DOS .EXE header
{
+00h  WORD  e_magic;     // Magic number,DOS可执行文件标记,值为'MZ'(4Dh 5Ah);
+02h  WORD  e_cblp;      // Bytes on last page of file
+04h  WORD  e_cp;        // Pages in file
+06h  WORD  e_crlc;      // Relocations
+08h  WORD  e_cparhdr;   // Size of header in paragraphs
+0Ah  WORD  e_minalloc;  // Minimum extra paragraphs needed
+0Ch  WORD  e_maxalloc;  // Maximum extra paragraphs needed
+0Eh  WORD  e_ss;        // Initial (relative) SS value;DOS代码的初始化堆栈SS;
+10h  WORD  e_sp;        // Initial SP value;DOS代码的初始化堆栈指针SP;
+12h  WORD  e_csum;      // Checksum
+14h  WORD  e_ip;        // Initial IP value;DOS代码的初始化指令指针IP;
+16h  WORD  e_cs;        // Initial (relative) CS value;DOS代码的初始化代码段地址;
+18h  WORD  e_lfarlc;    // File address of relocation table
+1Ah  WORD  e_ovno;      // Overlay number
+1Ch  WORD  e_res[4];    // Reserved words
+24h  WORD  e_oemid;     // OEM identifier (for e_oeminfo)
+26h  WORD  e_oeminfo;   // OEM information; e_oemid specific
+28h  WORD  e_res2[10];  // Reserved words
+3Ch  LONG  e_lfanew;    // File address of new exe header;其值是指向PE文件头的地址(相对于整个PE文件起始位置的偏移地址);
} IMAGE_DOS_HEADER, *PIMAGE_DOS_HEADER;
DOS头部结构中最重要的成员是e_lfanew,它的值是PE头部的首地址(相对于整个PE文件起始位置的偏移地址);通过e_lfanew可以直接定位PE头部的位置;
备注:字段类型前面的数字是相对于DOS Header首地址处的偏移地址;

/******** PE HEADER ********/
//PE HEADER = ImageBase + IMAGE_DOS_HEADER::e_lfanew
typedef struct _IMAGE_NT_HEADERS  //PE Header定义的开始;
{
+00h  DWORD Signature;              // 有效的PE文件标识,标记PE文件头的开始,dosHeader->e_lfanew就指向这里;值为0x00004550H,ASCII="PE",即"PE",0,0;
+04h  IMAGE_FILE_HEADER FileHeader; // IMAGE_FILE_HEADER结构,在下面有定义;
+18h  IMAGE_OPTIONAL_HEADER32 OptionalHeader; // IMAGE_OPTIONAL_HEADER32结构,在下面有定义;
} IMAGE_NT_HEADERS32, *PIMAGE_NT_HEADERS32;

typedef struct _IMAGE_NT_HEADERS64
{
+00h  DWORD Signature;              // 有效的PE文件标识,标记有效的PE文件头的开始;值为0x00004550H,ASCII="PE..";
+04h  IMAGE_FILE_HEADER FileHeader; // IMAGE_FILE_HEADER结构,在下面有定义;
+18h  IMAGE_OPTIONAL_HEADER64 OptionalHeader; // IMAGE_OPTIONAL_HEADER64结构,在下面有定义;
} IMAGE_NT_HEADERS64, *PIMAGE_NT_HEADERS64;
PE头在内存中的定位方法是:基地址(ImageBase)+DOS_Header->e_lfanew;
PE头在文件中的定位方法是:0+DOS_Header->e_lfanew;
备注:字段类型前面的数字是相对于PE Header首地址处的偏移地址;

/******** PE HEADER --> FILE HEADER ********/
//IMAGE_FILE_HEADER
typedef struct _IMAGE_FILE_HEADER
{
+04h  WORD   Machine;               // 运行平台,即:生成可执行文件的目标CPU类型;
+06h  WORD   NumberOfSections;      // 可执行文件中区块的数目;
+08h  DWORD  TimeDateStamp;         // 可执行文件的创建日期和时间;
+0Ch  DWORD  PointerToSymbolTable;  // 指向符号表的指针(主要用于调试);
+10h  DWORD  NumberOfSymbols;       // 符号表中符号的个数;
+14h  WORD   SizeOfOptionalHeader;  // IMAGE_OPTIONAL_HEADER结构的大小;
+16h  WORD   Characteristics;       // 可执行文件的属性;
} IMAGE_FILE_HEADER, *PIMAGE_FILE_HEADER;
备注:字段类型前面的数字是相对于PE Header首地址处的偏移地址;

/******** PE HEADER --> OPTIONAL HEADER ********/
//IMAGE_OPTIONAL_HEADER
typedef struct _IMAGE_OPTIONAL_HEADER
{
      //Standard fields:
+18h  WORD   Magic;                    // 标志字;ROM影像(0107h),普通可执行文件(010Bh);
+1Ah  BYTE   MajorLinkerVersion;       // 链接程序的主版本号;
+1Bh  BYTE   MinorLinkerVersion;       // 链接程序的次版本号;
+1Ch  DWORD  SizeOfCode;               // 所有包含代码的节的总大小;
+20h  DWORD  SizeOfInitializedData;    // 所有包含已初始化数据的节的总大小;
+24h  DWORD  SizeOfUninitializedData;  // 所有包含未初始化数据的节的总大小;
+28h  DWORD  AddressOfEntryPoint;      // 可执行文件被装入到内存之后,在执行时的入口地址(RVA),即:程序执行入口地址;
+2Ch  DWORD  BaseOfCode;               // 代码段所属的节在内存中的起始RVA;
+30h  DWORD  BaseOfData;               // 数据段所属的节在内存中的起始RVA;

      //NT additional fields:
+34h  DWORD  ImageBase;             // 程序被装入内存中时的首选装载地址;
+38h  DWORD  SectionAlignment;      // 可执行文件中的区块在内存中的边界对齐大小;(以CPU的对齐边界为基准,默认为1000H->4KB);
+3Ch  DWORD  FileAlignment;         // 可执行文件中的区块在磁盘文件中的边界对齐大小;(以磁盘为基准,默认为200H->512Byte);
+40h  WORD   MajorOperatingSystemVersion; // 要求操作系统最低版本号的主版本号;
+42h  WORD   MinorOperatingSystemVersion; // 要求操作系统最低版本号的次版本号;
+44h  WORD   MajorImageVersion;     // 可运行于操作系统的主版本号;
+46h  WORD   MinorImageVersion;     // 可运行于操作系统的次版本号;
+48h  WORD   MajorSubsystemVersion; // 要求最低子系统版本的主版本号;
+4Ah  WORD   MinorSubsystemVersion; // 要求最低子系统版本的次版本号;
+4Ch  DWORD  Win32VersionValue;     // 莫须有的字段,不被病毒利用的话,一般为0;
+50h  DWORD  SizeOfImage;           // 映像装入内存后的总大小;
+54h  DWORD  SizeOfHeaders;         // 所有头部大小+节表的大小;
+58h  DWORD  CheckSum;              // 映像的校验和;
+5Ch  WORD   Subsystem;             // 可执行文件期望的子系统;
+5Eh  WORD   DllCharacteristics;    // DllMain()函数被调用的时机,默认为0 ；
+60h  DWORD  SizeOfStackReserve;    // 初始化时的栈的大小;
+64h  DWORD  SizeOfStackCommit;     // 初始化时实际提交的栈的大小;
+68h  DWORD  SizeOfHeapReserve;     // 初始化时保留的堆的大小;
+6Ch  DWORD  SizeOfHeapCommit;      // 初始化时实际提交的堆的大小;
+70h  DWORD  LoaderFlags;           // 与调试有关,默认为0;
+74h  DWORD  NumberOfRvaAndSizes;   // 数据目录字段数组DataDirectory中的元素数目,一般是16;
+78h  IMAGE_DATA_DIRECTORY DataDirectory[IMAGE_NUMBEROF_DIRECTORY_ENTRIES]; // 数据目录表;
} IMAGE_OPTIONAL_HEADER32, *PIMAGE_OPTIONAL_HEADER32;

typedef struct _IMAGE_OPTIONAL_HEADER64
{
+18h  WORD       Magic;
+1Ah  BYTE       MajorLinkerVersion;
+1Bh  BYTE       MinorLinkerVersion;
+1Ch  DWORD      SizeOfCode;
+20h  DWORD      SizeOfInitializedData;
+24h  DWORD      SizeOfUninitializedData;
+28h  DWORD      AddressOfEntryPoint;
+2Ch  DWORD      BaseOfCode;
+30h  ULONGLONG  ImageBase;
+38h  DWORD      SectionAlignment;
+3Ch  DWORD      FileAlignment;
+40h  WORD       MajorOperatingSystemVersion;
+42h  WORD       MinorOperatingSystemVersion;
+44h  WORD       MajorImageVersion;
+46h  WORD       MinorImageVersion;
+48h  WORD       MajorSubsystemVersion;
+4Ah  WORD       MinorSubsystemVersion;
+4Ch  DWORD      Win32VersionValue;
+50h  DWORD      SizeOfImage;
+54h  DWORD      SizeOfHeaders;
+58h  DWORD      CheckSum;
+5Ch  WORD       Subsystem;
+5Eh  WORD       DllCharacteristics;
+60h  ULONGLONG  SizeOfStackReserve;
+68h  ULONGLONG  SizeOfStackCommit;
+70h  ULONGLONG  SizeOfHeapReserve;
+78h  ULONGLONG  SizeOfHeapCommit;
+80h  DWORD      LoaderFlags;
+84h  DWORD      NumberOfRvaAndSizes;
+88h  IMAGE_DATA_DIRECTORY DataDirectory[IMAGE_NUMBEROF_DIRECTORY_ENTRIES];
} IMAGE_OPTIONAL_HEADER64, *PIMAGE_OPTIONAL_HEADER64;
备注:字段类型前面的数字是相对于PE Header首地址处的偏移地址;

/******** DATA DIRECTORY ********/
//IMAGE_DATA_DIRECTORY定义了OPTIIMAGE_OPTIONAL_HEADER结构中的数据目录表成员DataDirectory[]中的数据元素;
typedef struct _IMAGE_DATA_DIRECTORY
{
  DWORD  VirtualAddress; // 区块在内存中的起始地址;
  DWORD  Size;           // 区块的长度;
} IMAGE_DATA_DIRECTORY, *PIMAGE_DATA_DIRECTORY;
数据目录表是按照各个节中的数据的不同用途进行分类,具有相同用途的数据存放在同一个数据目录中;按照不同用途进行分类,有:导入表、导出表、资源表、重定位表,等等不同的数据块;

/******** SECTION HEADER ********/
//节表中的元素;
typedef struct _IMAGE_SECTION_HEADER
{
  BYTE   Name[IMAGE_SIZEOF_SHORT_NAME]; // 节的名称;IMAGE_SIZEOF_SHORT_NAME=8;
  union
  {
    DWORD  PhysicalAddress;
    DWORD  VirtualSize;    // 节的大小;这是节的数据在没有进行对齐处理前的实际大小;
  } Misc;
  DWORD  VirtualAddress;   // 节装载到内存中之后的RVA地址;这个地址是按照内存页来对齐的;其值总是SectionAlignment的整数倍;
  DWORD  SizeOfRawData;    // 节在磁盘文件中所占空间的大小;在可执行文件中,该字段是已经被FileAlignment潜规则处理过的长度;
  DWORD  PointerToRawData; // 节在磁盘文件中的偏移地址;这个数值是从文件头处开始算起的偏移量;
  DWORD  PointerToRelocations;
  DWORD  PointerToLinenumbers;
  WORD   NumberOfRelocations;
  WORD   NumberOfLinenumbers;
  DWORD  Characteristics;  // 节的属性;按位来指出节的属性;
} IMAGE_SECTION_HEADER, *PIMAGE_SECTION_HEADER;
节表是按照可执行文件在内存中的不同内存页属性进行分类,具有相同内存页属性的数据存放在同一个节中;按照不同内存页属性进行分类,有:代码节(.text)、数据节(.data),等等;代码节所在的内存页具有可读、可执行、不可写的属性,数据节所在的内存页具有可读、可写、不可执行的属性;
节表就是一个元素类型为IMAGE_SECTION_HEADER结构的数组;
RVA是PE文件被装载器装载到内存中之后,某个数据的位置相对于内存中文件头的偏移量;例如:PE装载器把一个PE文件装载到内存中的地址00400000h处,而某个内存块中的某个数据被装入到地址004xxxxxh处,那么这个数据的RVA就是(004xxxxxh - 00400000h) = xxxxxh;即内存中的实际地址就是(00400000h + xxxxxh) = 004xxxxxh;
内存中的目标RVA到磁盘文件中物理偏移地址的转换:
第1步:循环扫描区块表,得出每一个区块在内存中的起始RVA(由IMAGE_SECTION_HEADER中的字段VirtualAddress的值得到),并根据该区块的大小(由IMAGE_SECTION_HEADER中的字段SizeOfrawData的值得到)计算出该区块的结束RVA(这两个字段的值相加即可),最后判断目标RVA是否落在该区块内;
      即:判断条件表达式"VirtualAddress <= 目标RVA <= (VirtualAddress + SizeOfRawData)"是否成立;如果成立,则目标RVA就在该区块内;否则就不在该区块内;
第2步:通过第1步定位了目标RVA处于具体的某个区块中之后,那么目标RVA减去该区块的起始RVA,就得到了目标RVA相对于该区块起始RVA的偏移地址(设为RVA2);
第3步:从区块表中获取该区块的起始位置在磁盘文件中的偏移地址(由IMAGE_SECTION_HEADER的字段PointerToRawData的值得到),把这个偏移地址加上第2步中得到的RVA2的值,相加的结果就是目标RVA在磁盘文件中的偏移地址;
=====================================================================================

/******** IMPORT DESCRIPTOR ********/
//导入表结构:简称IID;
typedef struct _IMAGE_IMPORT_DESCRIPTOR
{
  union
  {
    DWORD  Characteristics;    // 0 for terminating null import descriptor
    DWORD  OriginalFirstThunk; // RVA to original unbound IAT (PIMAGE_THUNK_DATA)
  } DUMMYUNIONNAME;
  DWORD  TimeDateStamp;        // 0 if not bound,
                               // -1 if bound, and real date\time stamp
                               //     in IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT (new BIND)
                               // O.W. date/time stamp of DLL bound to (Old BIND)

  DWORD  ForwarderChain;       // -1 if no forwarders
  DWORD  Name;
  DWORD  FirstThunk;           // RVA to IAT (if bound this IAT has actual addresses)
} IMAGE_IMPORT_DESCRIPTOR;
导入表就是一个元素类型为IMAGE_IMPORT_DESCRIPTOR结构的数组,即:IID数组;被可执行文件链接进来的每一个DLL文件都单独对应一个IID数组;但是在这个IID数组中并没有明确指出有多少个数组项,即:没有明确指明有多少个DLL文件被链接进来,也没有明确指明每个DLL文件中有多少个导入函数被链接进来;但是这个IID数组以一个内容全为NULL(0)的IMAGE_IMPORT_DESCRIPTOR结构元素作为结束的标志;
在可执行的PE文件中,数据目录表中的第2个元素(下标索引为1)就是导入表的信息,第13个元素(下标索引为12)是导入函数地址表(IAT);

typedef struct _IMAGE_THUNK_DATA64
{
  union
  {
    ULONGLONG ForwarderString; // PBYTE,指向一个转向者字符串的RVA;
    ULONGLONG Function;        // PDWORD,导入函数的内存地址;
    ULONGLONG Ordinal;         // 导入函数的序数值;
    ULONGLONG AddressOfData;   // PIMAGE_IMPORT_BY_NAME,指向IMAGE_IMPORT_BY_NAME结构的指针;
  } u1;
} IMAGE_THUNK_DATA64;

typedef struct _IMAGE_THUNK_DATA32
{
  union
  {
    DWORD ForwarderString; // PBYTE,指向一个转向者字符串的RVA; 
    DWORD Function;        // PDWORD,导入函数的内存地址;
    DWORD Ordinal;         // 导入函数的序数值;
    DWORD AddressOfData;   // PIMAGE_IMPORT_BY_NAME,指向IMAGE_IMPORT_BY_NAME结构的指针;
  } u1;
} IMAGE_THUNK_DATA32;

typedef struct _IMAGE_IMPORT_BY_NAME
{
  WORD  Hint;    // 导入函数的序数;
  BYTE  Name[1]; // 导入函数的名称;
} IMAGE_IMPORT_BY_NAME, *PIMAGE_IMPORT_BY_NAME;
备注:导入函数的序数是一个WORD类型的数据,占用两个字节;

/******** EXPORT DESCRIPTOR ********/
//导出表结构:简称IED;
typedef struct _IMAGE_EXPORT_DIRECTORY
{
  DWORD  Characteristics;       // 未使用,值为0;
  DWORD  TimeDateStamp;         // 文件生成时间;
  WORD   MajorVersion;          // 未使用,值为0;
  WORD   MinorVersion;          // 未使用,值为0;
  DWORD  Name;                  // 模块的真实名称;;
  DWORD  Base;                  // 导出函数的序数的起始值,再加上序数,就是函数地址数组的索引值;
  DWORD  NumberOfFunctions;     // 导出函数的总数量;
  DWORD  NumberOfNames;         // 以名称方式导出的函数的总数量;
  DWORD  AddressOfFunctions;    // 指向导出函数地址的RVA;
  DWORD  AddressOfNames;        // 指向导出函数名字的RVA;
  DWORD  AddressOfNameOrdinals; // 指向导出函数序数的RVA;
} IMAGE_EXPORT_DIRECTORY, *PIMAGE_EXPORT_DIRECTORY;
在可执行的PE文件中,数据目录表中的第1个元素(下标索引为0)就是导出表的信息;
备注:导出函数的序数是一个WORD类型的数据,占用两个字节;

/******** 基址重定位表 ********/
在可执行的PE文件中,数据目录表中的第6个元素(下标索引为5)就是基址重定位表的信息;
1、应用场合:凡是涉及到直接寻址的指令都需要进行基址重定位处理;
2、所需条件:
   A、需要修正的地址(10003000h):存在于DLL文件中的原始地址;它被统计并保存在基址重定位表中;
   B、建议装入的地址(10000000h):ImageBase字段的值;
   C、实际装入的地址(20003000h):只有在模块被装载器实际装入到内存中时才能得知,装入之前无从得知;
3、定位算法:
   新地址 = 直接寻址指令中的双字地址 + (模块的实际装入地址 - 模块建议装入地址);
4、重定位表中保存的信息:
   PE文件的基址重定位表中保存的是文件中所有需要进行基址重定位处理的代码的地址;
5、基址重定位表结构:
typedef struct _IMAGE_BASE_RELOCATION
{
  DWORD  VirtualAddress; // 基址重定位表对应的重定位数据块的起始RVA;
  DWORD  SizeOfBlock;    // 基址重定位表对应的重定位数据块的长度;
  WORD   TypeOffset[1];  // 基址重定位项的数组,存放需要进行重定位的项;
} IMAGE_BASE_RELOCATION;
成员TypeOffset是一个WORD类型的数组,用于存放需要进行重定位的项;项数 = ( SizeOfBlock - 8) / 2;每项都是一个16位的数据,由高4位和低12位组成;高4位标识重定位类型,低12位是重定位地址的偏移地址,该偏移地址值加上VirtualAddress的值,就得到了指向PE映像中需要进行修正的那个代码的地址;
6、重定位类型:
#define IMAGE_REL_BASED_ABSOLUTE              0  // 使块按照32位对齐,位置为0;
#define IMAGE_REL_BASED_HIGH                  1  // 高16位必须应用于偏移量所指高字16位;
#define IMAGE_REL_BASED_LOW                   2  // 低16位必须应用于偏移量所指低字16位;
#define IMAGE_REL_BASED_HIGHLOW               3  // 全部32位应用于所有32位;
#define IMAGE_REL_BASED_HIGHADJ               4  //
#define IMAGE_REL_BASED_MIPS_JMPADDR          5
#define IMAGE_REL_BASED_MIPS_JMPADDR16        9
#define IMAGE_REL_BASED_IA64_IMM64            9
#define IMAGE_REL_BASED_DIR64                 10
==============================================================

/******** 资源表 ********/
在可执行的PE文件中,数据目录表中的第3个元素(下标索引为2)就是基址重定位表的信息;
typedef struct _IMAGE_RESOURCE_DIRECTORY
{
  DWORD  Characteristics;      // 理论上是资源的属性,实际上总是0;
  DWORD  TimeDateStamp;        // 资源产生的时间;
  WORD   MajorVersion;         // 理论上是资源的版本,实际上总是0;
  WORD   MinorVersion;         //
  WORD   NumberOfNamedEntries; // 以名称(字符串)命名的资源目录项数量;(重要)
  WORD   NumberOfIdEntries;    // 以ID(整型数字)命名的资源目录项数量;(重要)
  //IMAGE_RESOURCE_DIRECTORY_ENTRY DirectoryEntries[];
} IMAGE_RESOURCE_DIRECTORY, *PIMAGE_RESOURCE_DIRECTORY;

#define IMAGE_RESOURCE_NAME_IS_STRING     0x80000000
#define IMAGE_RESOURCE_DATA_IS_DIRECTORY  0x80000000

typedef struct _IMAGE_RESOURCE_DIRECTORY_ENTRY
{
  union
  {
    struct
    {
      DWORD NameOffset:31;
      DWORD NameIsString:1;
    } DUMMYSTRUCTNAME;
    DWORD  Name;           // 目录项的名称字符串指针;
    WORD   Id;             // 目录项的名称ID;
  } DUMMYUNIONNAME;
  union
  {
    DWORD    OffsetToData; // 目录项的指针;
    struct
    {
      DWORD  OffsetToDirectory:31;
      DWORD  DataIsDirectory:1;
    } DUMMYSTRUCTNAME2;
  } DUMMYUNIONNAME2;
} IMAGE_RESOURCE_DIRECTORY_ENTRY, *PIMAGE_RESOURCE_DIRECTORY_ENTRY;
该结构精简之后的定义如下:
typedef struct _IMAGE_RESOURCE_DIRECTORY_ENTRY
{
  DWORD  Name;         // 目录项的名称字符串指针或ID;
  DWORD  OffsetToData; // 目录项的指针;
} IMAGE_RESOURCE_DIRECTORY_ENTRY, *PIMAGE_RESOURCE_DIRECTORY_ENTRY;

typedef struct _IMAGE_RESOURCE_DIRECTORY_STRING
{
  WORD  Length;        // 字符串长度;
  CHAR  NameString[1]; // 变长的UNICODE字符串;
} IMAGE_RESOURCE_DIRECTORY_STRING, *PIMAGE_RESOURCE_DIRECTORY_STRING;


typedef struct _IMAGE_RESOURCE_DIR_STRING_U
{
  WORD   Length;        // 字符串长度;
  WCHAR  NameString[1]; // 变长的UNICODE字符串;
} IMAGE_RESOURCE_DIR_STRING_U, *PIMAGE_RESOURCE_DIR_STRING_U;

typedef struct _IMAGE_RESOURCE_DATA_ENTRY
{
  DWORD  OffsetToData; // 资源数据的RVA;
  DWORD  Size;         // 资源数据的长度;
  DWORD  CodePage;     // 代码页,一般为0;
  DWORD  Reserved;
} IMAGE_RESOURCE_DATA_ENTRY, *PIMAGE_RESOURCE_DATA_ENTRY;


===============================================================


push ebp
mov  ebp, esp



mov eax, value
mov esp, ebp
pop ebp
