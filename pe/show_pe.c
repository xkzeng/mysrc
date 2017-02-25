/*********************************************************

      PE File Format
  ------------------------------- <--+
  |     MZ  MS-DOS Header       |    |
  -------------------------------    |  Dos Headers
  |     MS DOS Stub             |    |
  ------------------------------- <--+
  |        PE00                 |    |
  -------------------------------    |
  |                             |    |
  |  IMAGE_FILE_HEADER          |    | IMAGE_NT_HEADERS32
  -------------------------------    |
  |                             |    |
  |  IMAGE_OPTIONAL_HEADER32    |    |
  |                             |    |
  ------------------------------- <--+    
  |   Section Header 1          |    |
  |-----------------------------|    |
  |   Section Header 2          |    |
  -------------------------------    |  Section Headers
  |     ..............          |    |
  |-----------------------------|    |
  |   Section Header N          |    |
  ------------------------------- <--+
  |   Section Data 1            |    |
  |-----------------------------|    |
  |   Section Data 2            |    |
  -------------------------------    |  Section Datas
  |     ...............         |    |
  -------------------------------    |
  |   Section Data N            |    |
  ------------------------------- <--+

**********************************************************/

#include <stdio.h>
#include <windows.h>
#include <time.h>

// Data Directory Description

char szDataDirectory[16][64] = {
    "Export Directory",
    "Import Directory",
    "Resource Directory",
    "Exception Directory",
    "Security Directory",
    "Base Relocation Table",
    "Debug Directory",
    "Architecture Specific Data",
    "RVA of GP",
    "TLS Directory",
    "Load Configuration Directory",
    "Bound Import Directory in headers",
    "Import Address Table",
    "Delay Load Import Descriptors",
    "COM Runtime descriptor"
};

HANDLE hFile = NULL;
HANDLE hFileMapping = NULL;
void* pFileBase = NULL;
IMAGE_DOS_HEADER *pDosHeader = NULL;
IMAGE_NT_HEADERS *pNTHeader = NULL;
IMAGE_SECTION_HEADER *pSectionHeader = NULL;


DWORD RVA2FileOffset(DWORD dwRVA);

int main(int argc, char **argv)
{
    struct tm* ptm;
    DWORD dwIndex;

    IMAGE_IMPORT_DESCRIPTOR *pImportDescriptor = NULL;
    IMAGE_THUNK_DATA *pThunkData = NULL;
    IMAGE_IMPORT_BY_NAME *pImportByName = NULL;

    IMAGE_EXPORT_DIRECTORY *pExportDirectory = NULL;

    DWORD *pdw;
    WORD *pw;

    if ( argc != 2 )
    {
        printf("Usage:\n\t%s PEFile\n", argv[0]);
        return -1;
    }


    /*********************** Map the file to memory *************************/
    hFile = CreateFile(argv[1], GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_ARCHIVE, NULL);
    if ( hFile == INVALID_HANDLE_VALUE )
    {
        printf("Open File Error.\n");
        return -1;
    }
    hFileMapping = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, 0, NULL);
    if ( !hFileMapping )
    {
        CloseHandle(hFile);
        printf("Create File Mapping Error.\n");
        return -1;
    }

    pFileBase = MapViewOfFile(hFileMapping, FILE_MAP_READ, 0, 0, 0);
    if ( !pFileBase )
    {
        CloseHandle(hFileMapping);
        CloseHandle(hFile);
        printf("Map View Of File Error.\n");
        return -1;
    }
    /*********************** Map end *****************************************/

    // get the dos heaader pointer

    pDosHeader = (IMAGE_DOS_HEADER*)pFileBase;
    if ( pDosHeader->e_magic != IMAGE_DOS_SIGNATURE )
    {
        printf("Unknow File Format.\n");
        goto End;
    }
    printf("%-35s%s\n\n", "FileName:", argv[1]);
    printf("%-35s%#010x\n", "Dos Stub Size:", pDosHeader->e_lfanew - sizeof(IMAGE_DOS_HEADER));
    printf("%-35s%#010x\n", "NT File RVA:", pDosHeader->e_lfanew);

    // get the nt header pointer

    pNTHeader = (IMAGE_NT_HEADERS*)((char*)pFileBase + pDosHeader->e_lfanew);
    if ( pNTHeader->Signature != IMAGE_NT_SIGNATURE )
    {
        printf("Not NT File.\n");
        goto End;
    }

    // get the section header pointer

    pSectionHeader = (IMAGE_SECTION_HEADER*)((char*)pNTHeader + sizeof(IMAGE_NT_HEADERS));

    printf("\n%-35s%s\n", "nRun Platform:", (pNTHeader->FileHeader.Machine == IMAGE_FILE_MACHINE_I386) ? "Intel 386" : "Other" );
    printf("%-35s%d\n", "NumOfSections:", pNTHeader->FileHeader.NumberOfSections);
    ptm = localtime(&pNTHeader->FileHeader.TimeDateStamp);

    printf("%-35s%02d/%02d/%04d %02d:%02d:%02d\n", "FileCreateTime:", ptm->tm_mon + 1, ptm->tm_mday, ptm->tm_year + 1900,
         ptm->tm_hour, ptm->tm_min, ptm->tm_sec);
    //printf("%.19s\n", asctime(ptm));

    printf("%-35s%#010x\n", "SizeofOptionHdr:", pNTHeader->FileHeader.SizeOfOptionalHeader);
    printf("%-35s%s\n", "File Type:", (pNTHeader->FileHeader.Characteristics & IMAGE_FILE_DLL) ? "DLL" : "EXE");


    printf("\n%-35s%s\n", "Image Type:", (pNTHeader->OptionalHeader.Magic == 0x10B) ? "Exe Image" : "Other");
    printf("%-35s%d.%d\n", "Linker Version:", pNTHeader->OptionalHeader.MajorLinkerVersion, pNTHeader->OptionalHeader.MinorLinkerVersion);
    printf("%-35s%#010x\n", "SizeofCode:", pNTHeader->OptionalHeader.SizeOfCode);
    printf("%-35s%#010x\n", "AddressOfEntryPoint:", pNTHeader->OptionalHeader.AddressOfEntryPoint);
    printf("%-35s%#010x\n", "DefaultLoadAddress:", pNTHeader->OptionalHeader.ImageBase);
    printf("%-35s%#010x\n", "SectionAlignment:", pNTHeader->OptionalHeader.SectionAlignment);
    printf("%-35s%#010x\n", "FileAlignment:", pNTHeader->OptionalHeader.FileAlignment);
    printf("%-35s%d.%d\n", "OS SystemVersion:", pNTHeader->OptionalHeader.MajorOperatingSystemVersion, 
         pNTHeader->OptionalHeader.MinorOperatingSystemVersion);
    printf("%-35s%d.%d\n", "ImageVersion:", pNTHeader->OptionalHeader.MajorImageVersion, 
         pNTHeader->OptionalHeader.MinorImageVersion);
    printf("%-35s%d.%d\n", "SubSystemVersion:", pNTHeader->OptionalHeader.MajorSubsystemVersion,
         pNTHeader->OptionalHeader.MinorSubsystemVersion);
    printf("%-35s%#010d\n", "SizeOfIamge:", pNTHeader->OptionalHeader.SizeOfImage);
    printf("%-35s%#010d\n", "SizeOfHeaders:", pNTHeader->OptionalHeader.SizeOfHeaders);
    if ( pNTHeader->OptionalHeader.Subsystem == IMAGE_SUBSYSTEM_WINDOWS_GUI )
        printf("%-35s%s\n", "GUI System:", "Windows GUI");
    else if ( pNTHeader->OptionalHeader.Subsystem == IMAGE_SUBSYSTEM_WINDOWS_CUI)
        printf("%-35s%s\n", "GUI System:", "Windows Console");
    else
        printf("%-35s%s\n", "GUI System:", "Other");

    printf("\n-----------------------------Data Directory----------------------------------\n");
    printf("#Index\t#Virtual Address\t#Size\t\t#%-32s\n", "Directory Name");
    for (dwIndex = 0; dwIndex < IMAGE_NUMBEROF_DIRECTORY_ENTRIES; dwIndex++ )
    {
        printf("0x%02x\t0x%08x\t0x%08x\t%-50s\n", dwIndex, 
            pNTHeader->OptionalHeader.DataDirectory[dwIndex].VirtualAddress,
            pNTHeader->OptionalHeader.DataDirectory[dwIndex].Size, szDataDirectory[dwIndex]);
    }
    printf("\n\n-----------------------------Section Headers----------------------------------\n");
    printf("#VirtualAddress\t#VirtualSize\t#PointerToRawData\t#SizeOfRawData\t#Name\n");
    for ( dwIndex = 0; dwIndex < pNTHeader->FileHeader.NumberOfSections; dwIndex++ )
    {
        printf("0x%08x\t0x%08x\t0x%08x\t\t0x%08x\t%-10s\n", pSectionHeader[dwIndex].VirtualAddress,
            pSectionHeader[dwIndex].Misc.VirtualSize, pSectionHeader[dwIndex].PointerToRawData, 
            pSectionHeader[dwIndex].SizeOfRawData, pSectionHeader[dwIndex].Name);
    }

    // Import Table

    printf("\n\n-------------------------Import Table-------------------------------------\n");
    pImportDescriptor = (IMAGE_IMPORT_DESCRIPTOR*)((char*)pFileBase + RVA2FileOffset(pNTHeader->OptionalHeader.DataDirectory[1].VirtualAddress));
    for ( ; *(char*)pImportDescriptor ; pImportDescriptor++ )
    {
        printf("Import Lib: %s\n", (char*)(RVA2FileOffset(pImportDescriptor->Name) + (char*)pFileBase));
        pThunkData = (IMAGE_THUNK_DATA*)(RVA2FileOffset(pImportDescriptor->OriginalFirstThunk) + (char*)pFileBase);
        for ( ; pThunkData->u1.AddressOfData; pThunkData++ )
        {
            if ( pThunkData->u1.Ordinal & IMAGE_ORDINAL_FLAG32 ) // import by index

            {
                printf("\t0x%04x\n", pThunkData->u1.Ordinal & 0xffff);
            }
            else // import by name

            {
                pImportByName = (IMAGE_IMPORT_BY_NAME*)(RVA2FileOffset(pThunkData->u1.Ordinal) + (char*)pFileBase);
                printf("\t0x%04x\t%s\n", pImportByName->Hint, pImportByName->Name);
            }
        }
        printf("\n");
    }

    if ( pNTHeader->OptionalHeader.DataDirectory[0].Size == 0 ) // Export Table Not Exist

        goto End;

    // Export Table 

    printf("\n\n------------------------Export Table---------------------------------\n");
    
    pExportDirectory = (IMAGE_EXPORT_DIRECTORY*)(RVA2FileOffset(pNTHeader->OptionalHeader.DataDirectory[0].VirtualAddress) + (char*)pFileBase);
    printf("Export Lib: \t%s\n", (char*)(RVA2FileOffset(pExportDirectory->Name) + (char*)pFileBase));
    printf("\tIndex\tName\t\t\n");
    printf("\t------------------------------\n");
    for ( dwIndex = 0; dwIndex < pExportDirectory->NumberOfNames; dwIndex++ )
    {
        pdw = (DWORD*)(RVA2FileOffset(pExportDirectory->AddressOfNames) + (char*)pFileBase);
        pw = (WORD*)(RVA2FileOffset(pExportDirectory->AddressOfFunctions) + (char*)pFileBase);
        printf("\t0x%04x\t%-20s\n", dwIndex, (char*)(RVA2FileOffset(pdw[dwIndex]) + (char*)pFileBase), pw[dwIndex]);
    }


End:
    UnmapViewOfFile(pFileBase);
    CloseHandle(hFileMapping);
    CloseHandle(hFile);

    return 0;
}

/*
   Convert RVA To File Offset
*/
DWORD RVA2FileOffset(DWORD dwRVA)
{
    DWORD dwNum, dwIndex;

    if ( pNTHeader == NULL )
        return 0;
    if ( pSectionHeader == NULL )
        return 0;
    dwNum = pNTHeader->FileHeader.NumberOfSections;
    for ( dwIndex = 0; dwIndex < dwNum; dwIndex++ )
    {
        if ( dwRVA >= pSectionHeader[dwIndex].VirtualAddress &&
             dwRVA <= pSectionHeader[dwIndex].VirtualAddress + pSectionHeader[dwIndex].SizeOfRawData)
        {
            return dwRVA - pSectionHeader[dwIndex].VirtualAddress + pSectionHeader[dwIndex].PointerToRawData;
        }
    }
    return 0;
}