#pragma once
#include <string>
#include <map>
#include <vector>

static const std::string DIC_FILE = "dictionary.txt";

static const std::string FINISH_ADD_WORD_STRING = "new word remebered like ";
static const std::string WHETHER_ADD_WORD_STRING = "add translate or press Enter to skip";

static const std::string DELIMITER = "=";
static const std::string EXIT_LINE = "...";

typedef std::pair<std::string, std::string> Collocation;

Collocation SplitPairOfWords(std::string const& line);

class CDictionary
{
public:
	CDictionary();

	void AddNewWord(std::string const& englishWord, std::string const& russianWord);

	void SetDictionaryFile(std::string const& fileName);

	void DictionarySave() const;

	bool FindWord(std::string const& englishWord) const;

	bool IsDictionaryEmpty() const { return m_dictionaryList.empty(); }

	bool IsNewWordsListEmpty() const { return m_newCollocations.empty(); }

private:

	void LoadDictionary();

	void SaveChanges() const;

	std::vector<std::string> m_newCollocations;

	std::map<std::string, std::string> m_dictionaryList;

	std::string m_dictionaryFile;

};