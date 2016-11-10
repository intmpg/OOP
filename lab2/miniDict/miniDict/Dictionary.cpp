#include "stdafx.h"
#include "Dictionary.h"

CDictionary::CDictionary()
{
	m_dictionaryFile = DIC_FILE;
	LoadDictionary();
}

void CDictionary::AddNewWord(std::string const& englishWord, std::string const& russianWord)
{
	m_dictionaryList.insert({ englishWord, russianWord });

	m_newCollocations.push_back(englishWord + "=" + russianWord);

	std::cout << FINISH_ADD_WORD_STRING << russianWord << std::endl;
}

bool CDictionary::FindWord(std::string const& englishWord) const
{
	auto word = m_dictionaryList.find(englishWord);
	if (word == m_dictionaryList.end())
	{
		return false;
	}

	std::cout << word->second << std::endl;
	return true;
}

Collocation SplitPairOfWords(std::string const& line)
{
	std::vector<std::string> words;
	boost::split(words, line, boost::is_any_of(DELIMITER));

	std::string rusWord;
	std::string engWord;
	if (words.size() >= 2)
	{
		rusWord = words[1];
		engWord = words[0];
	}

	return Collocation(engWord, rusWord);
}

void CDictionary::LoadDictionary()
{
	std::string line;

	std::ifstream dictInputFile(m_dictionaryFile);
	while (std::getline(dictInputFile, line))
	{

		m_dictionaryList.insert(SplitPairOfWords(line));
	}
	dictInputFile.close();
}

void CDictionary::SaveChanges() const
{
	std::ofstream dictFile(m_dictionaryFile, std::ios_base::app);
	for (auto &it : m_newCollocations)
	{
		dictFile << it << std::endl;
	}
	dictFile.close();
}

void CDictionary::DictionarySave() const
{
	if (!m_newCollocations.empty())
	{
		SaveChanges();
	}
}

void CDictionary::SetDictionaryFile(std::string const& fileName)
{
	m_dictionaryFile = fileName;
	LoadDictionary();
}