/**@author hoxnox <hoxnox@gmail.com>
 * @copyright (c) 2018 hoxnox <hoxnox@gmail.com>
 * @license LGPL
 * @brief Codecvt KOI-8R facet implementation.
 * 
 * This file is a part of hoxnox's facets project*/

#ifndef __CODECVT_KO8R_HPP__
#define __CODECVT_KO8R_HPP__

#include <locale>
#include <map>

/**@brief Facet is used to convert cyrillic char strings in koi8-r
 * encoding into UNICODE*/
class codecvt_koi8r : public std::codecvt<wchar_t, char, mbstate_t>
{
  public:

    typedef std::codecvt_base::result result;
    const result ok, partial, error, noconv;

    explicit codecvt_koi8r(size_t r=0)
      : std::codecvt<wchar_t, char, mbstate_t>(r),
        ok(std::codecvt_base::ok),
        partial(std::codecvt_base::partial),
        error(std::codecvt_base::error),
        noconv(std::codecvt_base::noconv)
    {
      // UNICODE -> KOI8R tab, extended part without alpha
      out_tab[0x2500] = 128; in_tab[128] = 0x2500;// ─
      out_tab[0x2502] = 129; in_tab[129] = 0x2502;// │
      out_tab[0x250C] = 130; in_tab[130] = 0x250C;// ┌
      out_tab[0x2510] = 131; in_tab[131] = 0x2510;// ┐
      out_tab[0x2514] = 132; in_tab[132] = 0x2514;// └
      out_tab[0x2518] = 133; in_tab[133] = 0x2518;// ┘
      out_tab[0x251C] = 134; in_tab[134] = 0x251C;// ├
      out_tab[0x2524] = 135; in_tab[135] = 0x2524;// ┤
      out_tab[0x252C] = 136; in_tab[136] = 0x252C;// ┬
      out_tab[0x2534] = 137; in_tab[137] = 0x2534;// ┴
      out_tab[0x253C] = 138; in_tab[138] = 0x253C;// ┼
      out_tab[0x2580] = 139; in_tab[139] = 0x2580;// ▀
      out_tab[0x2584] = 140; in_tab[140] = 0x2584;// ▄
      out_tab[0x2588] = 141; in_tab[141] = 0x2588;// █
      out_tab[0x258C] = 142; in_tab[142] = 0x258C;// ▌
      out_tab[0x2590] = 143; in_tab[143] = 0x2590;// ▐
      out_tab[0x2591] = 144; in_tab[144] = 0x2591;// ░
      out_tab[0x2592] = 145; in_tab[145] = 0x2592;// ▒
      out_tab[0x2593] = 146; in_tab[146] = 0x2593;// ▓
      out_tab[0x2320] = 147; in_tab[147] = 0x2320;// ⌠
      out_tab[0x25A0] = 148; in_tab[148] = 0x25A0;// ■
      out_tab[0x2219] = 149; in_tab[149] = 0x2219;// ∙
      out_tab[0x221A] = 150; in_tab[150] = 0x221A;// √
      out_tab[0x2248] = 151; in_tab[151] = 0x2248;// ≈
      out_tab[0x2264] = 152; in_tab[152] = 0x2264;// ≤
      out_tab[0x2265] = 153; in_tab[153] = 0x2265;// ≥
      out_tab[0x00A0] = 154; in_tab[154] = 0x00A0;// N
      out_tab[0x2321] = 155; in_tab[155] = 0x2321;// ⌡
      out_tab[0x00B0] = 156; in_tab[156] = 0x00B0;// °
      out_tab[0x00B2] = 157; in_tab[157] = 0x00B2;// ²
      out_tab[0x00B7] = 158; in_tab[158] = 0x00B7;// ·
      out_tab[0x00F7] = 159; in_tab[159] = 0x00F7;// ÷
      out_tab[0x2550] = 160; in_tab[160] = 0x2550;// ═
      out_tab[0x2551] = 161; in_tab[161] = 0x2551;// ║
      out_tab[0x2552] = 162; in_tab[162] = 0x2552;// ╒
      out_tab[0x0451] = 163; in_tab[163] = 0x0451;// ё
      out_tab[0x2553] = 164; in_tab[164] = 0x2553;// ╓
      out_tab[0x2554] = 165; in_tab[165] = 0x2554;// ╔
      out_tab[0x2555] = 166; in_tab[166] = 0x2555;// ╕
      out_tab[0x2556] = 167; in_tab[167] = 0x2556;// ╖
      out_tab[0x2557] = 168; in_tab[168] = 0x2557;// ╗
      out_tab[0x2558] = 169; in_tab[169] = 0x2558;// ╘
      out_tab[0x2559] = 170; in_tab[170] = 0x2559;// ╙
      out_tab[0x255A] = 171; in_tab[171] = 0x255A;// ╚
      out_tab[0x255B] = 172; in_tab[172] = 0x255B;// ╛
      out_tab[0x255C] = 173; in_tab[173] = 0x255C;// ╜
      out_tab[0x255D] = 174; in_tab[174] = 0x255D;// ╝
      out_tab[0x255E] = 175; in_tab[175] = 0x255E;// ╞
      out_tab[0x255F] = 176; in_tab[176] = 0x255F;// ╟
      out_tab[0x2560] = 177; in_tab[177] = 0x2560;// ╠
      out_tab[0x2561] = 178; in_tab[178] = 0x2561;// ╡
      out_tab[0x0401] = 179; in_tab[179] = 0x0401;// Ё
      out_tab[0x2562] = 180; in_tab[180] = 0x2562;// ╢
      out_tab[0x2563] = 181; in_tab[181] = 0x2563;// ╣
      out_tab[0x2564] = 182; in_tab[182] = 0x2564;// ╤
      out_tab[0x2565] = 183; in_tab[183] = 0x2565;// ╥
      out_tab[0x2566] = 184; in_tab[184] = 0x2566;// ╦
      out_tab[0x2567] = 185; in_tab[185] = 0x2567;// ╧
      out_tab[0x2568] = 186; in_tab[186] = 0x2568;// ╨
      out_tab[0x2569] = 187; in_tab[187] = 0x2569;// ╩
      out_tab[0x256A] = 188; in_tab[188] = 0x256A;// ╪
      out_tab[0x256B] = 189; in_tab[189] = 0x256B;// ╫
      out_tab[0x256C] = 190; in_tab[190] = 0x256C;// ╬
      out_tab[0x00A9] = 191; in_tab[191] = 0x00A9;// ©
      out_tab[0x044E] = 192; in_tab[192] = 0x044E;// ю
      out_tab[0x0430] = 193; in_tab[193] = 0x0430;// а
      out_tab[0x0431] = 194; in_tab[194] = 0x0431;// б
      out_tab[0x0446] = 195; in_tab[195] = 0x0446;// ц
      out_tab[0x0434] = 196; in_tab[196] = 0x0434;// д
      out_tab[0x0435] = 197; in_tab[197] = 0x0435;// е
      out_tab[0x0444] = 198; in_tab[198] = 0x0444;// ф
      out_tab[0x0433] = 199; in_tab[199] = 0x0433;// г
      out_tab[0x0445] = 200; in_tab[200] = 0x0445;// х
      out_tab[0x0438] = 201; in_tab[201] = 0x0438;// и
      out_tab[0x0439] = 202; in_tab[202] = 0x0439;// й
      out_tab[0x043A] = 203; in_tab[203] = 0x043A;// к
      out_tab[0x043B] = 204; in_tab[204] = 0x043B;// л
      out_tab[0x043C] = 205; in_tab[205] = 0x043C;// м
      out_tab[0x043D] = 206; in_tab[206] = 0x043D;// н
      out_tab[0x043E] = 207; in_tab[207] = 0x043E;// о
      out_tab[0x043F] = 208; in_tab[208] = 0x043F;// п
      out_tab[0x044F] = 209; in_tab[209] = 0x044F;// я
      out_tab[0x0440] = 210; in_tab[210] = 0x0440;// р
      out_tab[0x0441] = 211; in_tab[211] = 0x0441;// с
      out_tab[0x0442] = 212; in_tab[212] = 0x0442;// т
      out_tab[0x0443] = 213; in_tab[213] = 0x0443;// у
      out_tab[0x0436] = 214; in_tab[214] = 0x0436;// ж
      out_tab[0x0432] = 215; in_tab[215] = 0x0432;// в
      out_tab[0x044C] = 216; in_tab[216] = 0x044C;// ь
      out_tab[0x044B] = 217; in_tab[217] = 0x044B;// ы
      out_tab[0x0437] = 218; in_tab[218] = 0x0437;// з
      out_tab[0x0448] = 219; in_tab[219] = 0x0448;// ш
      out_tab[0x044D] = 220; in_tab[220] = 0x044D;// э
      out_tab[0x0449] = 221; in_tab[221] = 0x0449;// щ
      out_tab[0x0447] = 222; in_tab[222] = 0x0447;// ч
      out_tab[0x044A] = 223; in_tab[223] = 0x044A;// ъ
      out_tab[0x042E] = 224; in_tab[224] = 0x042E;// Ю
      out_tab[0x0410] = 225; in_tab[225] = 0x0410;// А
      out_tab[0x0411] = 226; in_tab[226] = 0x0411;// Б
      out_tab[0x0426] = 227; in_tab[227] = 0x0426;// Ц
      out_tab[0x0414] = 228; in_tab[228] = 0x0414;// Д
      out_tab[0x0415] = 229; in_tab[229] = 0x0415;// Е
      out_tab[0x0424] = 230; in_tab[230] = 0x0424;// Ф
      out_tab[0x0413] = 231; in_tab[231] = 0x0413;// Г
      out_tab[0x0425] = 232; in_tab[232] = 0x0425;// Х
      out_tab[0x0418] = 233; in_tab[233] = 0x0418;// И
      out_tab[0x0419] = 234; in_tab[234] = 0x0419;// Й
      out_tab[0x041A] = 235; in_tab[235] = 0x041A;// К
      out_tab[0x041B] = 236; in_tab[236] = 0x041B;// Л
      out_tab[0x041C] = 237; in_tab[237] = 0x041C;// М
      out_tab[0x041D] = 238; in_tab[238] = 0x041D;// Н
      out_tab[0x041E] = 239; in_tab[239] = 0x041E;// О
      out_tab[0x041F] = 240; in_tab[240] = 0x041F;// П
      out_tab[0x042F] = 241; in_tab[241] = 0x042F;// Я
      out_tab[0x0420] = 242; in_tab[242] = 0x0420;// Р
      out_tab[0x0421] = 243; in_tab[243] = 0x0421;// С
      out_tab[0x0422] = 244; in_tab[244] = 0x0422;// Т
      out_tab[0x0423] = 245; in_tab[245] = 0x0423;// У
      out_tab[0x0416] = 246; in_tab[246] = 0x0416;// Ж
      out_tab[0x0412] = 247; in_tab[247] = 0x0412;// В
      out_tab[0x042C] = 248; in_tab[248] = 0x042C;// Ь
      out_tab[0x042B] = 249; in_tab[249] = 0x042B;// Ы
      out_tab[0x0417] = 250; in_tab[250] = 0x0417;// З
      out_tab[0x0428] = 251; in_tab[251] = 0x0428;// Ш
      out_tab[0x042D] = 252; in_tab[252] = 0x042D;// Э
      out_tab[0x0429] = 253; in_tab[253] = 0x0429;// Щ
      out_tab[0x0427] = 254; in_tab[254] = 0x0427;// Ч
      out_tab[0x042A] = 255; in_tab[255] = 0x042A;// Ъ
    }

    ~codecvt_koi8r()
    {
    }


protected:


  virtual result do_in(mbstate_t&,
                       const char* from,
                       const char* from_end,
                       const char* &from_next,
                       wchar_t* to,
                       wchar_t* to_end,
                       wchar_t* &to_next)
    const
  {
    while(from != from_end)
    {
      if(to == to_end)
      {
        from_next = from;
        to_next = to;
        return partial;
      }
      const unsigned char ufrom = static_cast<unsigned char>(*from);
      // ASCII
      if(ufrom <= 0x7F)
        *to = static_cast<wchar_t>(*from);
      else
      {
        std::map<unsigned char, wchar_t>::const_iterator s;
        s = in_tab.lower_bound(ufrom);
        if(s->first != ufrom || s == in_tab.end())
        {
          from_next = ++from;
          to_next = ++to;
          return error;
        }
        *to = s->second;
      }
      ++to;
      ++from;
    }
    from_next = from_end;
    to_next = to;
    return ok;
  }


  virtual result do_out(mbstate_t&,
                        const wchar_t* from,
                        const wchar_t* from_end,
                        const wchar_t* &from_next,
                        char* to,
                        char* to_end,
                        char* &to_next)
    const
  {
    while(from != from_end)
    {
      if(to == to_end)
      {
        from_next = from;
        to_next = to;
        return partial;
      }
      if(0 <= *from && *from <= 0x7F)
        *to = static_cast<unsigned char>(*from);
      else
      {
        std::map<wchar_t, unsigned char>::const_iterator s;
        s = out_tab.lower_bound(*from);
        if( s->first != *from || s == out_tab.end())
        {
          // ok from and to is not endings
          from_next = ++from;
          to_next = ++to;
          return error;
        }
        *to = s->second;
      }
      ++to;
      ++from;
    }
    from_next = from_end;
    to_next = to;
    return ok;
  }

  virtual int do_encoding() const throw()
  {
    return 1;
  }

  virtual bool do_always_noconv() const throw()
  {
    return false;
  }
      /*
  virtual int do_length(State& s, const E* from, const E* from_end, size_t max) const
  {
    return codecvt<I, E, State>::do_length(s, from, from_end, max);
  }

  virtual int do_max_length() const throw()
  {
    return codecvt<I, E, State>::do_max_length();
  }
     */
private:
  std::map<unsigned char, wchar_t> in_tab;
  std::map<wchar_t, unsigned char> out_tab;

};

#endif // __CODECVT_KOI8R__

