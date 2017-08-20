#pragma once
#include <globals.h>

typedef struct LogonDataNode LogonDataNode;
typedef struct LogonDataList LogonDataList;
typedef struct LogonData LogonData;

// Global list of LogonDatas
LogonDataList* s_list;

struct LogonDataNode
{
	LogonData* data;
	LogonDataNode* next;
};

struct LogonDataList
{
	size_t length;
	LogonDataNode* first;
	LogonDataNode* last;
};

// Represents a username and its known credentials.
struct LogonData
{
	WCHAR username[WINDOWS_MAX_USERNAME_PASS_LENGTH];
	WCHAR password[WINDOWS_MAX_USERNAME_PASS_LENGTH];
	BYTE lmHash[LM_NTLM_HASH_LENGTH];
	BYTE ntlmHash[LM_NTLM_HASH_LENGTH];
};

/* LogonDataNode functions */
LogonDataNode* Node_create(LogonData* item);
void Node_delete(LogonDataNode* node);

/* LogonDataList functions */
LogonDataList* List_create();
void List_delete(LogonDataList* list);
void List_addItem(LogonDataList* list, LogonData* item);
LogonData List_pop(LogonDataList* list);
size_t List_getLength(LogonDataList* list);

/* LogonData functions */
LogonData* LogonData_create(WCHAR* username, size_t username_size, WCHAR* password, size_t password_size, BYTE* lmHash, BYTE* ntlmHash);
void LogonData_delete(LogonData* logonData);
LogonData LogonData_generateEmpty();
