#include "stdafx.h"
#include "../UrlParser/HttpUrl.h"

BOOST_AUTO_TEST_SUITE(testing_parser_with_giving_string);

	BOOST_AUTO_TEST_CASE(can_return_parts_of_url_and_all_url)
	{
		CHttpUrl parser("http://jjons.com:444/doc.txt");
		BOOST_CHECK_EQUAL(parser.GetURL(), "http://jjons.com:444/doc.txt");
		BOOST_CHECK_EQUAL(parser.GetDocument(), "/doc.txt");
		BOOST_CHECK_EQUAL(parser.GetDomain(), "jjons.com");
		BOOST_CHECK_EQUAL(parser.GetPort(), 444);
		BOOST_CHECK_EQUAL(parser.GetProtocol(), HTTP);
	}

	BOOST_AUTO_TEST_CASE(when_doc_is_empty)
	{
		CHttpUrl parser("http://jjons.com:444");
		BOOST_CHECK_EQUAL(parser.GetURL(), "http://jjons.com:444/");
		BOOST_CHECK_EQUAL(parser.GetDocument(), "/");
		BOOST_CHECK_EQUAL(parser.GetDomain(), "jjons.com");
		BOOST_CHECK_EQUAL(parser.GetPort(), 444);
		BOOST_CHECK_EQUAL(parser.GetProtocol(), HTTP);
	}

	BOOST_AUTO_TEST_CASE(if_protocol_incorrect_then_class_throw_exception)
	{
		BOOST_REQUIRE_THROW(CHttpUrl("httpt://github.com/document.txt"), CUrlParsingError);
	}

	BOOST_AUTO_TEST_CASE(if_port_incorrect_then_class_throw_exception)
	{
		BOOST_REQUIRE_THROW(CHttpUrl("httpt://github.com:76t/document.txt"), CUrlParsingError);
	}

	BOOST_AUTO_TEST_CASE(if_domain_incorrect_then_class_throw_exception)
	{
		BOOST_REQUIRE_THROW(CHttpUrl("httpt://git hub.com:76t/document.txt"), CUrlParsingError);
	}

	BOOST_AUTO_TEST_CASE(if_all_correct_then_class_not_throw_exception)
	{
		BOOST_REQUIRE_NO_THROW(CHttpUrl("http://github.com:76/document.txt"));
	}
BOOST_AUTO_TEST_SUITE_END();



BOOST_AUTO_TEST_SUITE(testing_parser_with_giving_param_list);

	BOOST_AUTO_TEST_CASE(can_return_parts_of_url_and_all_url)
	{
		CHttpUrl parser("jjons.com", "/doc.txt", HTTP, 444);
		BOOST_CHECK_EQUAL(parser.GetURL(), "http://jjons.com:444/doc.txt");
		BOOST_CHECK_EQUAL(parser.GetDocument(), "/doc.txt");
		BOOST_CHECK_EQUAL(parser.GetDomain(), "jjons.com");
		BOOST_CHECK_EQUAL(parser.GetPort(), 444);
		BOOST_CHECK_EQUAL(parser.GetProtocol(), HTTP);
	}

	BOOST_AUTO_TEST_CASE(if_domain_incorrect_then_class_throw_exception)
	{
		BOOST_REQUIRE_THROW(CHttpUrl("jjon s.com", "/doc.txt", HTTP, 444), CUrlParsingError);
	}
BOOST_AUTO_TEST_SUITE_END();