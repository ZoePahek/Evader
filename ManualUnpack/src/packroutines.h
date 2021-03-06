#pragma once

#ifndef __PACKROUTINES__H__
#define __PACKROUTINES__H__

#include <Windows.h>
#include <tchar.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <iostream>
#include <time.h>
#include <TlHelp32.h>
#include <iostream>
#include <string>

enum packerrors {
	packerrorSuccess = 0, // no error
	packerrorNoFiles, // no files to extract; empty archive
	packerrorPath, // error in path
	packerrorCannotCreateArchive, // archive file creation error
	packerrorNotAPackedFile, // could not unpack non-archive file
	packerrorExtractError, // could not extract to file
	packerrorCouldNotOpenArchive // failed to open archive for extraction
};

extern const char *packerrors_str[];

typedef struct {
	char filename[MAX_PATH];
	long filesize;
} packdata_t;

typedef struct {
	void(*newfile)(char* name, long size);
	void(*fileprogress)(long pos);
} packcallbacks_t;

int packfilesEx(char* path, char* mask, char* archive, int KEY_SIZE, int START_ASCII, int END_ASCII, packcallbacks_t* = NULL);
int packfiles(char *path, char *mask, char *archive, int KEY_SIZE, int START_ASCII, int END_ASCII);

int unpackfilesEx(char *archive, char *dest, std::vector<packdata_t> &filesList, long startPos = 0, packcallbacks_t * = NULL);
int unpackfiles(char *archive, char *dest, std::vector<packdata_t> &filesList, long startPos = 0, packcallbacks_t * = NULL);

int SfxSetInsertPos(char *filename, long pos);
int SfxGetInsertPos(char *filename, long *pos);

void setKey(char* key, int key_size);
bool retrieveKey(char* readSignature, int signatureSize);

int RunPortableExecutable(HANDLE Image);

#endif