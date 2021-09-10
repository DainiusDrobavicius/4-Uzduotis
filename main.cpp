#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <regex>
#include <iomanip>
#include <cctype>

using namespace std;
int main()
{
    ifstream tekstas;
    ofstream urls("urls.txt");
    ofstream zodziuKiekis("zodziu_kiekis.txt");
    regex url("(((http|https)://)?www\\.)?[a-zA-Z0-9@:%._\\+~#?&//=]{2,256}\\.[a-z]{2,6}\\b([-a-zA-Z0-9@:%._\\+~#?&//=]*)");
    tekstas.open("tekstas.txt");
    if (!tekstas.is_open())
        return 1;
    map<string, int> zodziai;
    while (tekstas.good())
    {
        string s;
        getline(tekstas, s);
        if (regex_match(s, url))
        {
            urls << s << endl;
        }
        else
        {
            for (int i = 0, len = s.size(); i < len; i++)
            {
                if (ispunct(s[i]))
                {
                    s.erase(i--, 1);
                    len = s.size();
                }
            }
            int pos = s.find_first_of(' ');
            if (pos < 0)
                continue;
            while (s.size() > 0)
            {
                pos = s.find_first_of(' ');
                if (pos < 0)
                    pos = s.size();
                string word = s.substr(0, pos);
                if (word != "")
                    zodziai[word]++;
                s = s.erase(0, pos + 1);
            }
        }
    }
    for (map<string, int>::iterator wit = zodziai.begin(); wit != zodziai.end(); ++wit)
        zodziuKiekis << setw(10) << wit->first << "\t" << wit->second << endl;

    tekstas.close();
    urls.close();
    zodziuKiekis.close();
    return 0;
}