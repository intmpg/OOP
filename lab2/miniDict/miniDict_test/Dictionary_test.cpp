#include "stdafx.h"
#include "../miniDict/Dictionary.h"

using namespace std;

struct TempDict
{
	CDictionary dictionary;
	CDictionary emptyDictionary;
};

BOOST_FIXTURE_TEST_SUITE(temp, TempDict);

	BOOST_AUTO_TEST_CASE(start_dict_list_to_be_empty)
	{
		BOOST_CHECK(dictionary.IsDictionaryEmpty());
		BOOST_CHECK(emptyDictionary.IsDictionaryEmpty());
	}

	BOOST_AUTO_TEST_CASE(start_list_of_new_word_to_be_empty)
	{
		BOOST_CHECK(dictionary.IsNewWordsListEmpty());
		BOOST_CHECK(emptyDictionary.IsNewWordsListEmpty());
	}
	
	BOOST_AUTO_TEST_CASE(if_load_dictionary_from_empty_file_dict_list_to_be_empty)
	{
		std::remove("empty.txt");
		std::ofstream input("empty.txt");
		input.close();
		emptyDictionary.SetDictionaryFile("empty.txt");
		BOOST_CHECK(emptyDictionary.IsDictionaryEmpty());
		std::remove("empty.txt");
	}

	BOOST_AUTO_TEST_CASE(if_load_dictionary_from_nonempty_file_it_should_not_be_empty)
	{
		std::remove("hello.txt");
		std::ofstream input("hello.txt");
		input << "hello = privet";
		input.close();
		dictionary.SetDictionaryFile("hello.txt");
		BOOST_CHECK(!dictionary.IsDictionaryEmpty());
		std::remove("hello.txt");
	}

	BOOST_AUTO_TEST_CASE(new_word_should_be_insert_into_list_of_new_words_and_into_dictionary_list)
	{
		dictionary.AddNewWord("dog", "cobaka");
		BOOST_CHECK(!dictionary.IsNewWordsListEmpty());
		BOOST_CHECK(dictionary.FindWord("dog"));
	}

	BOOST_AUTO_TEST_CASE(cant_find_notexisting_word)
	{
		BOOST_CHECK(!dictionary.FindWord("cat"));
	}

	BOOST_AUTO_TEST_CASE(save_dictionary_into_empty_doc_it_should_not_be_empty)
	{
		std::remove("empty.txt");
		dictionary.AddNewWord("dog", "cobaka");
		dictionary.SetDictionaryFile("empty.txt");
		std::string line;
		dictionary.DictionarySave();
		std::ifstream dic("empty.txt");
		getline(dic, line);
		BOOST_CHECK(!line.empty());
		dic.close();
		std::remove("empty.txt");
	}

	BOOST_AUTO_TEST_CASE(must_return_left_and_right_parts)
	{
		BOOST_CHECK(SplitPairOfWords("dog=cat").first == "dog"
			&& SplitPairOfWords("dog=cat").second == "cat");
	}

BOOST_AUTO_TEST_SUITE_END()
