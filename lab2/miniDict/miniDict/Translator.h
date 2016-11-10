#pragma once
#include "Dictionary.h"

class CTranslator
{
public:
	CTranslator(CDictionary & dict);

	void DoDialogWithUser(std::string const& word);

private:
	CDictionary & m_dict;

};