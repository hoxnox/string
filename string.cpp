/**@file src/string.cpp
 * @author Nosov Yuri <hoxnox@gmail.com>
 * @date 2012-04-29
 * @copyright (c) 2011 Nosov Yuri <hoxnox@gmail.com>
 * @licence ENTY licence
 *
 * @brief String implementation*/

#include "string.hpp"

namespace nx{

/**@class String
 * @brief Yet another string class
 *
 * To construct String class from cstring you must use dT() macro, or one
 * of 4 constructors:
 * fromUTF8(), fromCP1251(), fromCP866(), fromASCII() like this:
 * @code
 * String hello_world = dT("Привет, мир!");
 * String::fromUTF8("Привет, мир!");
 * @endcode
 * */

String::String()
{
}

/**@brief Copy constructor.*/
String::String(const String& str)
	: std::basic_string<wchar_t>(str)
{
}

/**@brief Construct String from std::wstring.*/
String::String(const std::wstring& str)
	: std::basic_string<wchar_t>(str)
{
}

/**@brief Construct String from substring of std::wstring.*/
String::String(const std::wstring& str, size_t pos, size_t n /* = npos*/)
	: std::basic_string<wchar_t>(str, pos, npos)
{
}

/**@brief Construct String from const wchar_t*.*/
String::String(const wchar_t * s, size_t n)
	: std::basic_string<wchar_t>(s, n)
{
}

/**@brief Construct String from const wchar_t*.*/
String::String(const wchar_t * s)
	: std::basic_string<wchar_t>(s)
{
}

/**@brief Construct String from repeating wchar_t symbol.*/
String::String(size_t n, wchar_t c)
	: std::basic_string<wchar_t>(n, c)
{
}

String::~String()
{
}

/**@brief Constructs String from UTF-8 byte sequence.*/
String String::fromUTF8(const char* str)
{
	size_t str_l = strlen(str);
	if(str_l == 0)
		return String();
	std::basic_string<wchar_t> wstr;
	if(mbstowcs(str, str + str_l, std::back_inserter(wstr))
		== str + str_l)
		assert(true);
	return wstr;
}

/**@brief Constructs String from cp1251 byte sequence.*/
String String::fromCP1251(const char* str)
{
	size_t str_l = strlen(str);
	if(str_l == 0)
		return String();

	// converting, using codecvt facets
	const std::locale cp1251_loc(std::locale(), new codecvt_cp1251);
	mbstate_t tmp;
	const char * cnext;
	wchar_t * wnext;
	wchar_t *wstr = new wchar_t[str_l + 1];
	std::uninitialized_fill(wstr, wstr + str_l + 1, 0);
	typedef std::codecvt<wchar_t, char, mbstate_t> cvt;
	cvt::result res =
	    std::use_facet<cvt>(cp1251_loc).in(tmp, str, str + str_l, cnext,
	                                                 wstr, wstr + str_l, wnext);
	assert(res == cvt::ok);
	String result(wstr);
	delete [] wstr;

	return result;
}

/**@brief Constructs String from cp866 byte sequence.*/
String String::fromCP866(const char* str)
{
	size_t str_l = strlen(str);
	if(str_l == 0)
		return String();

	// converting, using codecvt facets
	const std::locale cp866_loc(std::locale(), new codecvt_cp866);
	mbstate_t tmp;
	const char * cnext;
	wchar_t * wnext;
	wchar_t *wstr = new wchar_t[str_l + 1];
	std::uninitialized_fill(wstr, wstr + str_l + 1, 0);
	typedef std::codecvt<wchar_t, char, mbstate_t> cvt;
	cvt::result res =
	    std::use_facet<cvt>(cp866_loc).in(tmp, str, str + str_l, cnext,
	                                           wstr, wstr + str_l, wnext);
	assert(res == cvt::ok);
	String result(wstr);
	delete [] wstr;

	return result;
}

/**@brief Constructs String from ascii byte sequence.
 *
 * Note that each non-ASCII symbol turns into ? symbol.*/
String String::fromASCII(const char* str)
{
	size_t str_l = strlen(str);
	if(str_l == 0)
		return String();
	std::basic_string<wchar_t> wstr;
	for(size_t i = 0; i < str_l; ++i)
	{
		if(str[i] < 0 || str[i] > 127)
		{
			assert(false); // ONLY ASCII allowed
			wstr += L'?';
		}
		else
		{
			wstr += static_cast<wchar_t>(str[i]);
		}
	}
	return wstr;
}

/**@brief Constructs String from number .*/
String String::fromNumber(long num)
{
	std::basic_stringstream<wchar_t> wss;
	wss << num;
	return wss.str();
}

/**@brief Constructs String from byte sequence, using the locale codecvt
 * facet.*/
String String::fromByteArray(const ByteArray& bytes, std::locale loc)
{
	if(bytes.empty())
		return String();

	// converting, using codecvt facets
	size_t bsize = bytes.size();
	mbstate_t tmp;
	const char * cnext;
	wchar_t * wnext;
	wchar_t *wstr = new wchar_t[bsize + 1];
	std::uninitialized_fill(wstr, wstr + bsize + 1, 0);
	typedef std::codecvt<wchar_t, char, mbstate_t> cvt;
	std::vector<char> charr = barr2charr(bytes);
	cvt::result res =
	    std::use_facet<cvt>(loc).in(tmp, &charr[0], &charr[0] + bsize, cnext,
	                                     wstr, wstr + bsize, wnext);
	assert(res == cvt::ok);
	String result(wstr);
	delete [] wstr;
	return result;
}

char hex2char(Byte n)
{
	if(0 <= n && n <= 9)
		return n + 48;
	if(0xA <= n && n <= 0xF)
		return n - 0xA + 65;
	return -1;
}

/**@brief Constructs String as string representation of byte sequence in hex form.
 * e.g 234F11A1...*/
String String::fromByteArray(const ByteArray& bytes)
{
	if(bytes.empty())
		return String();
	String result;
	for(ByteArray::const_iterator i = bytes.begin(); i != bytes.end(); ++i)
	{
		result += hex2char(((*i)/0x10)%0x10);
		result += hex2char((*i)%0x10);
	}
	return result;
}

/**@brief Converts String into UTF8 byte sequence.
 *
 * By default this method is used to handle with std::ostream.*/
std::string String::toUTF8() const
{
	if(std::basic_string<wchar_t>::empty())
		return std::string();
	std::string str;
	if(wcstombs(std::basic_string<wchar_t>::begin(),
	                std::basic_string<wchar_t>::end(),
	                std::back_inserter(str))
	       == std::basic_string<wchar_t>::end())
		assert(true);
	return str;
}

/**@brief Converts String into cp1251 byte sequence.*/
std::string String::toCP1251() const
{
	if(std::basic_string<wchar_t>::empty())
		return std::string();
	// converting, using codecvt facets
	const std::locale cp1251_loc(std::locale(), new codecvt_cp1251);
	const wchar_t *wstr = std::basic_string<wchar_t>::c_str();
	const size_t wstr_l = std::basic_string<wchar_t>::length();
	mbstate_t tmp;
	char * cnext;
	const wchar_t * wnext;
	// wchar_t symol extends maximum to 4 char
	char *str = new char[wstr_l*4 + 1];
	std::uninitialized_fill(str, str + wstr_l*4 + 1, 0);
	typedef std::codecvt<wchar_t, char, mbstate_t> cvt;
	cvt::result res =
	    std::use_facet<cvt>(cp1251_loc).out(tmp, wstr, wstr + wstr_l, wnext,
	                                             str, str + wstr_l*4, cnext);
	assert(res == cvt::ok);
	std::string result(str);
	delete [] str;

	return result;
}

/**@brief Converts String into cp866 byte sequence.*/
std::string String::toCP866() const
{
	if(std::basic_string<wchar_t>::empty())
		return std::string();
	// converting, using codecvt facets
	const std::locale cp866_loc(std::locale(), new codecvt_cp866);
	const wchar_t *wstr = std::basic_string<wchar_t>::c_str();
	const size_t wstr_l = std::basic_string<wchar_t>::length();
	mbstate_t tmp;
	char * cnext;
	const wchar_t * wnext;
	// wchar_t symol extends maximum to 4 char
	char *str = new char[wstr_l*4 + 1];
	std::uninitialized_fill(str, str + wstr_l*4 + 1, 0);
	typedef std::codecvt<wchar_t, char, mbstate_t> cvt;
	cvt::result res =
	    std::use_facet<cvt>(cp866_loc).out(tmp, wstr, wstr + wstr_l, wnext,
	                                            str, str + wstr_l*4, cnext);
	assert(res == cvt::ok);
	std::string result(str);
	delete [] str;

	return result;
}

/**@brief Converts String into ascii byte sequence.
 *
 * Note that each non-ascii symbol turns into ? symbol.*/
std::string String::toASCII() const
{
	if(std::basic_string<wchar_t>::empty())
		return std::string();
	std::string result;
	for(size_t i = 0; i < std::basic_string<wchar_t>::length(); ++i)
	{
		if(std::basic_string<wchar_t>::at(i) > 127
			|| std::basic_string<wchar_t>::at(i) < 0)
		{
			assert(std::basic_string<wchar_t>::at(i) > 127);
			result += '?';
		}
		else
			result += static_cast<char>(std::basic_string<wchar_t>::at(i));
	}
	return result;
}

/**@brief Compares with ASCII string.
 * @warning Only ASCII symbols are compared. Use T() macro or toUTF8(),
 * fromUTF8() functions.*/
bool String::operator==(const std::string& str) const
{
	if(std::basic_string<wchar_t>::empty() && str.length() == 0)
		return true;
	if(std::basic_string<wchar_t>::empty())
		return false;
	if(str.empty())
		return false;
	if(std::basic_string<wchar_t>::length() != str.length())
		return false;
	for(size_t i = 0; i < std::basic_string<wchar_t>::length(); ++i)
	{
		if(std::basic_string<wchar_t>::at(i) > 127)
			return false;
		if(static_cast<char>(std::basic_string<wchar_t>::at(i)) != str[i])
			return false;
	}
	return true;
}

/**@brief Compares with ASCII string
 * @param str is null terminated const char string
 * @warning Only ASCII symbols are compared. Use T() macro or toUTF8(),
 * fromUTF8() functions.*/
bool String::operator==(const char *str) const
{
	if(std::basic_string<wchar_t>::empty() && strlen(str) == 0)
		return true;
	if(std::basic_string<wchar_t>::empty())
		return false;
	if(strlen(str) == 0)
		return false;
	if(std::basic_string<wchar_t>::length() != strlen(str))
		return false;
	for(size_t i = 0; i < std::basic_string<wchar_t>::length(); ++i)
	{
		if(std::basic_string<wchar_t>::at(i) > 127)
			return false;
		if(static_cast<char>(std::basic_string<wchar_t>::at(i)) != str[i])
			return false;
	}
	return true;
}

/**@brief HowTo print String.*/
std::ostream& operator<<(std::ostream& os, const String& str)
{
	return os << str.toUTF8();
}

/**@brief Оперетор присваивания.*/
String& String::operator=(const String str)
{
	std::basic_string<wchar_t>::assign(str);
	return *this;
}

/**@brief Преобразует строку в число, считая основание base.
 * @base может принимать значения 2-16
 * Если строка не является числом с заданным основанием, возвращает 0.*/
unsigned long String::toNumber(unsigned char base /*=10*/) const
{
	if(16 < base || base < 2)
		return 0;
	unsigned long result = 0;
	size_t counter = 0;
	std::basic_string<wchar_t>::const_reverse_iterator i = rbegin();
	while(i != rend())
	{
		unsigned long pw = 1;
		for(size_t k = 0; k < counter; ++k)
		{
			// контроль переполнения
			if(std::numeric_limits<unsigned long>::max() / pw < base)
				return 0;
			pw *= base;
		}
		wchar_t d = *i;
		if(48 <= d && d <= 57)
		{
			if(d - 48 < base)
			{
				// контроль переполнения
				if(std::numeric_limits<unsigned long>::max() - result < (d-55)*pw)
					return 0;
				result += (d - 48)*pw;
			}
			else
			{
				return 0;
			}
		}
		if(65 <= d && d <=70 )
		{
			if(d - 55 < base)
			{
				// контроль переполнения
				if(std::numeric_limits<unsigned long>::max() - result < (d-55)*pw)
					return 0;
				result += (d - 55)*pw;
			}
			else
			{
				return 0;
			}
		}
		++i;
		++counter;
	}
	return result;
}

/**@fn String::substr(size_t pos, size_t n) const
 * @brief Переопределение substring.
 * 
 * Переопределение необходимо, чтобы substring возвращал правильный тип 
 * данных.*/

/**@brief Возвращает часть строки (подстроку) с заданным номером.
 * @param separator последовательность символов, служащая для разделения подстрок в исходной строке.
 * @param n Номер (индекс) заданного вхождения подстроки.
 *
 * Возвращает часть строки (подстроку) с указанным номером. Если подстрока с указанным номером
 * отсутствует, функция возвращает пустую строку. Если ни один разделитель в исходной строке не
 * найден, первой подстрокой считается вся строка. Нулевой подстрокой всегда является вся строка.
 *
 * @code
 * String str = L"Иванов Иван Иванович";
 * str.field(L" ", 2); // возвращает строку L"Иван" 
 * str = L"Иванов##Иван##Иванович";
 * str.field(L"##", 1); // возвращает строку L"Иванов"
 * str.field(L"##", 0); // возвращает строку L"Иванов##Иван##Иванович"
 * str = L"Иванов Иван Иванович";
 * str.field(L"##", 1); // возвращает строку L"Иванов Иван Иванович"
 * @endcode*/
String String::field(const String separator, const size_t n) const
{
	String str(*this);
	if(n == 0 || str.length() < separator.length())
		return str;
	size_t counter = 1;
	String::iterator prev = str.begin(), i = std::search(prev, str.end(), separator.begin(), separator.end());
	if(i == str.end())
	{
		if(n == 1)
			return str;
		else
			return String();
	}
	
	while( i != str.end() && counter < n)
	{
		if(str.end() - i < static_cast<String::iterator::difference_type>(separator.length()))
			break;
		prev = i + separator.length();
		i = std::search(prev, str.end(), separator.begin(), separator.end());
		++counter;
	}

	if(counter < n)
		return String();
	return String(prev, i);
}

/**@brief trim the string*/
String String::trim()
{
	size_t begin = 0, end = size() - 1;
	while( begin < size() && (operator[](begin) == L' ' || operator[](begin) == L'\t') )
		++begin;
	while( end != 0 && (operator[](end) == L' ' || operator[](end) == L'\t') )
	{
		--end;
	}
	if(end - begin > 0)
		return String(substr(begin, end - begin + 1));
	else
		return String();
}

/**@brief Convert to upper*/
String String::toUpper()
{
	String result;
	const std::locale ctype_loc(std::locale(), new ctype_unicode);
	for(size_t i = 0; i < length(); ++i)
		result += toupper(operator[](i), ctype_loc);
	return result;
}

/**@brief Convert to lower*/
String String::toLower()
{
	String result;
	const std::locale ctype_loc(std::locale(), new ctype_unicode);
	for(size_t i = 0; i < length(); ++i)
		result += tolower(operator[](i), ctype_loc);
	return result;
}

} //namespace nx

