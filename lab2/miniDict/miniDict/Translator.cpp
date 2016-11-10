#include "stdafx.h"
#include "Translator.h"

CTranslator::CTranslator(CDictionary & dict)
	:m_dict(dict)
{

}

void CTranslator::DoDialogWithUser(std::string const& word)
{
	enum State
	{
		FIND_WORD, ADD_WORD, FINISH
	};

	State state = FIND_WORD;

	while (state != FINISH)
	{
		switch (state)
		{
		case FIND_WORD:
			if (m_dict.FindWord(word))
			{
				state = FINISH;
			}
			else
			{
				state = ADD_WORD;
			}
			break;
		case ADD_WORD:
			std::cout << WHETHER_ADD_WORD_STRING << std::endl;
			std::string translate;
			std::getline(std::cin, translate);
			if (!translate.empty())
			{
				m_dict.AddNewWord(word, translate);
			}

			state = FINISH;
			break;
		}

	}
	state = FIND_WORD;
}

