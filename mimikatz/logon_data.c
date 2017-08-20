#include "logon_data.h"

LogonDataNode* Node_create(LogonData* item)
{
	LogonDataNode* newNode = malloc(sizeof(LogonDataNode));
	newNode->data = item;
	newNode->next = NULL;
	return newNode;
}

void Node_delete(LogonDataNode* node)
{
	if (node != NULL)
	{
		free(node);
	}
}

LogonDataList* List_create()
{
	LogonDataList* list = malloc(sizeof(LogonDataList));
	list->length = 0;
	list->first = NULL;
	list->last = NULL;
	return list;
}

void List_delete(LogonDataList* list)
{
	LogonDataNode* node = list->first;
	
	while (node != NULL)
	{
		LogonDataNode* toDelete = node;
		node = node->next;

		LogonData_delete(toDelete->data);
		Node_delete(toDelete);
	}

	free(list);
}

void List_addItem(LogonDataList* list, LogonData* item)
{
	list->length++;
	LogonDataNode* newNode = Node_create(item);

	if (list->first == NULL)
	{
		list->first = newNode;
		list->last = newNode;
	}
	else
	{
		list->last->next = newNode;
		list->last = newNode;
	}
}

LogonData List_pop(LogonDataList* list)
{
	if ((list == NULL) || (list->length == 0))
	{
		return LogonData_generateEmpty();
	}

	list->length--;
	LogonData logonData = *(list->first->data);
	LogonData_delete(list->first->data);
	LogonDataNode* firstNode = list->first;
	list->first = list->first->next;

	return logonData;
}

size_t List_getLength(LogonDataList* list)
{
	return list->length;
}

LogonData* LogonData_create(WCHAR* username, size_t username_size, WCHAR* password, size_t password_size, BYTE* lmHash, BYTE* ntlmHash)
{
	LogonData* logonData = malloc(sizeof(LogonData));

	wcscpy_s(logonData->username, WINDOWS_MAX_USERNAME_PASS_LENGTH, username);
	
	if (password == NULL)
	{
		wmemset(logonData->password, L'\0', WINDOWS_MAX_USERNAME_PASS_LENGTH);
	}
	else
	{
		wcscpy_s(logonData->password, WINDOWS_MAX_USERNAME_PASS_LENGTH, password);
	}

	if (lmHash == NULL)
	{
		memset(logonData->lmHash, 0, LM_NTLM_HASH_LENGTH);
	}
	else
	{
		memcpy_s(logonData->lmHash, LM_NTLM_HASH_LENGTH, lmHash, LM_NTLM_HASH_LENGTH);
	}

	if (ntlmHash == NULL)
	{
		memset(logonData->ntlmHash, 0, LM_NTLM_HASH_LENGTH);
	}
	else
	{
		memcpy_s(logonData->ntlmHash, LM_NTLM_HASH_LENGTH, ntlmHash, LM_NTLM_HASH_LENGTH);
	}

	return logonData;
}

LogonData LogonData_generateEmpty()
{
	LogonData logonData;
	logonData.username[0] = L'\0';
	logonData.password[0] = L'\0';
	return logonData;
}

void LogonData_delete(LogonData* logonData)
{
	if (logonData != NULL)
	{
		free(logonData);
	}
}