 public String GetInfo(Int32 Param)
        {
            System.Globalization.CultureInfo CInfo;
            Double divi = 1000.0;
            String fmt = "000";
            String txt = String.Empty;
            byte[] textfeld = {0x43, 0x61, 0x63, 0x68, 0x65, 0x20, 0x66, 
                               0x69, 0x6e, 0x64, 0x65, 0x74, 0x20};
            String test = "Fritz jagt im komplett verwahrlosten Taxi quer durch Bayern";
            Int32 vA = 0x05, vB = 0x6AF, vC = 0x02, vD = 0x145;
            Int32 B1 = 'D', D1 = 's', pNum = D1 + test.Length + vD + Param;

            CInfo = System.Globalization.CultureInfo.InvariantCulture; 
            txt += Convert.ToChar('A' + 'Q' - 'N').ToString() + test.Substring(34, 3);
            txt = String.Concat(txt, test.Substring(test.IndexOf('w') + 2, 2), " in");
            txt = txt.Insert(4, System.Text.Encoding.GetEncoding(1251).GetString(textfeld));
            txt = String.Concat(txt, test.Substring(test.LastIndexOf(' ')), " bei ");
            txt = txt.Insert(0x11, "i");
            txt += test.Substring(test.Length - 1, 1).ToUpper() + txt[ 8 ].ToString().ToUpper();
            txt = txt.Insert(txt.Length - 1, ('§' - 'w').ToString());
            txt += ('§' - 0x25a6 / Param + vC).ToString(fmt) + ((char)0xb0).ToString();
            txt += Convert.ToChar('A' - 0x49 + Param).ToString() + ('-' - '+').ToString();
            txt = txt.Insert(txt.IndexOf((char)0x45), ((char)0xb0).ToString()
                + Convert.ToChar(49).ToString() + (0x11 - 0x0e + vA).ToString() 
                + ((char)0x2e).ToString());
            txt = txt.Insert(txt.IndexOf('E'), (B1 - 1280 + vB).ToString(fmt + " "));
            txt += (pNum / divi).ToString("." + fmt, CInfo);

            return txt;
        }