// miniDict.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Translator.h"
#include "Dictionary.h"
#include <ctype.h>
#include <windows.h>



using namespace std;

void ConvertToLowercase(string & word)
{
	for (auto &it : word)
	{
		it = char(tolower(it));
	}
}

int main(int argc, char *argv[])
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	if (argc != 1)
	{
		cout << "The command has no additional parameters" << endl;
		return 0;
	}

	string englishWord;
	CDictionary dictionary;
	CTranslator translator(dictionary);
	while (getline(cin, englishWord) && englishWord != EXIT_LINE)
	{
		if (!englishWord.empty())
		{
			ConvertToLowercase(englishWord);
			translator.DoDialogWithUser(englishWord);
		}
	}
	string answer;
	if (!dictionary.IsNewWordsListEmpty())
	{
		cout << "Do you want to save new words? YES/NO" << endl;
		while (getline(cin, answer))
		{
			if (answer == "YES")
			{
				dictionary.DictionarySave();
				break;
			}
			else if (answer == "NO")
			{
				break;
			}
			else
			{
				cout << "Try again" << endl;
			}
		}
	}
	return 0;
}

