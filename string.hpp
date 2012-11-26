/**@file include/string.hpp
 * @author Nosov Yuri <hoxnox@gmail.com>
 * @date 2012-04-29
 * @copyright (c) 2012 Nosov Yuri <hoxnox@gmail.com>
 * @licence Querier licence
 *
 * @brief Yet another String class.
 *
 * STL std::string based*/

#ifndef __NX_STRING_H__
#define __NX_STRING_H__

// hoxnox codecvt facets to from... functions
#include <codecvt/codecvt_cp1251.hpp>
#include <codecvt/codecvt_cp866.hpp>
#include <codecvt/mbwcvt.hpp>
#include <ctype/ctype_unicode.hpp>


// STL
#include <algorithm>
#include <cassert>
#include <cstring>
#include <locale>
#include <limits>
#include <sstream>
#include <iterator>
#include <vector>


namespace nx{

/**@brief Replacement for L"".*/
#define dT(x) CONCAT(L, x)

/**@typedef Byte
 * @brief Byte*/
typedef char Byte;

/**@typedef ByteArray
 * @brief Byte sequence.*/
typedef std::vector<unsigned char> ByteArray;

inline char uch2ch(unsigned char c)
{
	return static_cast<char>(c);
}

inline std::vector<char> barr2charr(const ByteArray& barr)
{
	std::vector<char> proxy;
	proxy.reserve(barr.size());
	std::transform(barr.begin(), barr.end(), std::back_inserter(proxy), uch2ch);
	return proxy;
}

class String : public std::basic_string<wchar_t>
{
public:

	/**@name ctors and dtors
	 * @{*/
	String();
	String(const String& str);
	String(const std::wstring& str);
	String(const std::wstring& str, size_t pos, size_t n = npos);
	String(const wchar_t * s, size_t n);
	String(const wchar_t * s);
	String(size_t n, wchar_t c);
	template<class InputIterator>
		String (InputIterator begin, InputIterator end);
	~String();
	/**@}*/

	/**@name assigment operators
	 * @{ */
	String& operator=(const String str);
	/**@} */

	/**@name "from" constructors
	 * @{ */
	static String fromUTF8(const char* str);
	static String fromUTF8(const std::string& str);
	static String fromCP1251(const char* str);
	static String fromCP1251(const std::string& str);
	static String fromCP866(const char* str);
	static String fromCP866(const std::string& str);
	static String fromASCII(const char* str);
	static String fromASCII(const std::string& str);
	static String fromNumber(long number);
	static String fromByteArray(const ByteArray& bytes, std::locale loc);
	static String fromByteArray(const ByteArray& bytes);
	/**@} */

	/**@name converting to std string
	 * @{*/
	std::string toUTF8() const;
	std::string toCP1251() const;
	std::string toCP866() const;
	std::string toASCII() const;
	unsigned long toNumber(unsigned char base = 10) const;
	/**@}*/

	bool operator==(const std::string& str) const;
	bool operator==(const char *str) const;

	String substr(size_t pos = 0, size_t n = npos) const;
	String field(const String separator, const size_t n) const;
	String trim();
	String toUpper();
	String toLower();
};

std::ostream& operator<<(std::ostream& os, const String& str);

//////////////////////////////////////////////////////////////////////////////
// inlines

inline String String::fromASCII(const std::string& str)
{
	return fromASCII(str.c_str());
}

inline String String::fromCP866(const std::string& str)
{
	return fromCP866(str.c_str());
}

inline String String::fromCP1251(const std::string& str)
{
	return fromCP1251(str.c_str());
}

inline String String::fromUTF8(const std::string& str)
{
	return fromUTF8(str.c_str());
}

inline String String::substr(size_t pos, size_t n) const
{
	return std::basic_string<wchar_t>::substr(pos, n);
}

/**@brief Construct String from data between begin and end iterators.*/
template<class InputIterator>
	String::String (InputIterator begin, InputIterator end)
		: std::basic_string<wchar_t>(begin, end)
{
}

} // namespace nx

#endif // __NX_STRING_H__

