#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/repository/include/qi_seek.hpp>
namespace qi = boost::spirit::qi;
namespace qr = boost::spirit::repository::qi;

extern std::string const sample; // below

int main() {
    auto f(sample.begin()), l(sample.end());

    std::vector<std::string> phrases;

    if (qi::parse(f,l, *qi::as_string[
                qr::seek[qi::string("KEY")] >> *(qi::char_ - "END")
            ], phrases)) {
        for (size_t i = 0; i < phrases.size(); ++i) 
            std::cout << "keyphrase: #" << i << ": '" << phrases[i] << "'\n";
    }
}

std::string const sample = 
    "mhf5SVgPTOsNfuof9x2r7/UpEr12577U4tElsRZawRwJEc879LJJedvk/g4a+Uz/ktf+WSzoPRUq3q2T1uCgLoHKCuWXYVDAPiPWXfbm44CLNHqwFR0YTzGN"
    "VxlCX1YekdeAEsyxMJB3x1xXetaqeNHGKv5v6M1S4x8HQGUvT/lo2kuFQbrDM8CsI0Hm91oHGBkfuMAJq//U54QHYJVRyvsum+F1qMbXuC3a9BKkyI4qvAji"
    "ZgZTZ0wN71AVnSDolLafDr7TdAYwGqK1pXU+mlSinTLDKXeXgM99nWog3x5wUdBCd7/k1P4tWZgngLshZf6BkBzTlFHAeRo44tDHvecHWhpexFJdycUMqiqU"
    "uYV3lStC/in7DKfYvOlPKhQj+c4dN6k1GgVmESJ9YT2rwLZUrA/0fchwiGD62voMzoG+GK3tTswuPDxmPOWX2iPdolKvMfqw/y1yS/EynaeaqAkeChxrIyIz"
    "MXHFDWpl5P9X8c5JjT4CZ7NXbYa0pBZ/Qv72UetaXvwCCobxdcwR949ZiIobvIuMkYHpPjkATApkWTtfKYYpGPsfN7J3XwL/6qj/ltEuEbiP58cAZYZwv2+b"
    "ItLW4RpQgiwGXKkaQKdgGzh9ENoSy/JFfmdgedJldKUCC0FVVTmlKtCnzD5FMVa6NKcrkF7YIgZPqjAfqSIf80cDCrVlpEIHnNNMOT+Az9hOGK1eU/Mox+yE"
    "qAILFOujg7z05lrbwUuEE/Y9d3sE1L159AwNrjDVKxXRQmR5cS3D/udaWcQa044+StzOICwCGi0mbyiLG/yLt1uptcMWkYAAGPcU8ZdVT3nFSNDy1Kyw3srV"
    "9qxzVim4Wg5P+Y5vgqeUlCaHeigZOpw9gXchxCgCTcBYJhqHXuNm1o9QXK4IWf+GU81pgz08TH6SsiZac/bnJJuGzD4OJn5Q36Js1e9lhTfdtUk1UsztT4Yv"
    "NVMjhDNmVizVqm4CDy2rm5IJvBO/6qEZIdruTI5oDMSGpEn91GGc6H5Uz3+qpjdI7PuAz1Dj9jmQ12b70YDw2uLhHWUJo+5YYdA4kTCPa897rJX3vzdVOV70"
    "PA8FdUZ6uOOEelJ6L49q7rKhORjYFSlljUXfFCfTlrg2r4pJyPBGOQjH+wGH+KYfacyzhNEIdB/1hi9h8eXIPUgRQ7QSPyXHh6msra3NvKKAUhtfG+k5TZs/"
    "qGVlfZee2UEvKEY@v/0qwJTjgFQwNmose7LiEmAmKpIdK3TPmkCs@ENDTDEkyfE/QOPH0EUe1IaZn4p8NO1j9miE8VxLN4sIUSitxxkOtQSen+QEzlGqpset"
    "tGXwD7cKAT4yhMDUWGeRTgLsJKuANg+lDn9EStHokG1oP6JLp0yhx5SdJ+DcwLyxPp2IdLd7ntkGMpRVciqbz4DGQtgU/Yyd5X9KBWttG6kfqSeTXxuRgwlb"
    "su0V9PhEzB+YYAk18dMLiXHTgEINIjJ2DmyTu+akzg09Aq4BykMTgtE3AKcImUP8YMHtrITScGCCXH+bDNOxhxteAtREMN1/MpzXdAssNBWnoT82z0agSMLh"
    "AyHG7QG/5S6qGp7qP3mdLFqqcz8CegLV6jTaTlb5xjK2zCZDLgShc9p7oFG1kdXxBOC30/3gBTHG4Ng3iE5nHin51Nd2l57WKNiu+lncTMS/tK4JaYBqZFWF"
    "aoGyaMtEz8pRZ3wRKMzHRivZ+n7ASoEIlDq33+CAtfMnqSw0VjJYyJNxwPjmKVsNJHODmbwaA7xDmpSHTYTM1edaoTD3XmZPZKc5yc/96kitfoioy9ZWAiPI"
    "9gncGYfQl9NqXx6uHY1HPbqZWcj8KQhrpWEQAFsebOBRZ/jPzuQDN4UmKEY@G1TErN1QSSKi17BSnwBKML@END@OHEUrazNI5OvQCc09B5mhGMsfrZF6DKzC"
    "8ty2OqULTTnfDH9lOTXFO2VD9zWUZO1Uk47wGDNfw+r9XmWDnQ8kGkkO3jIEDqoQCkenBE8dqwhAhWa2B6XOujIY2Pr4xJtKWZ/vKgbSj7Ksx6h0t34BvcI+"
    "LPB7FuXRnPdzMx41MxDjBVGNrTrPNTd5JjS3m/WyxRuGlBN61t/hBwzNstnTDGXNGydA7KX7VhtV7djwZgAwchkUnPz+lsKGBizKX3qNcO43Od6L6XoWmPQo"
    "5Wga+n0lzn9ciPgG8dfiX66x4kU8NRyxEqmz4dBbB7kc32176JWMAL4LIB+mNt+0AzrRaKTx6eatxN+42UdHznZfRn0+rn9e5hvxmSFZA4rLp/+ANPVKcjHs"
    "V+mThNKxCAYYab7e4TP4Zs8hafDsSSaQxDp/5UE1r8pvgw8GPzE7GrkTtoK6i7zXuRuqBdpV2lcoUasWIeyWFKPDY0Ggsd/ld4AAw8s3647sVKFjHoqJE5uf"
    "U7IBbaotnKOeR95XgB/w1oIwoFFOsqbzKPRMJ0he/RadU0/Dbxy07Z0ZaQTgsURDlL9E2YOMjGgHm6J8Kti47JFws5AkMbGkbuXYw5qC8AXZyrvMlo8iTofk"
    "CrvNw+ID2sRSSKZfVsmdsNUSo1fAozFC2KHTOhhTZt+3mgZL93Je6Zu9vAibafNC7NYYs4jp1eXkgUXUs2fhar9bP17xwzBPfpchM3iNOCF1s0bLz8M+Ft6C"
    "v9X6Ac5l2Gx64hWZAWdQapLZnh5bfBsjaRnygQKvd2x5Qe2RrHL41AYLPLQKygiYOl7VB2k4q28rnN3nuhONGTJYdUlP/fq9tB5njHdW9GvPw00pfDx/2H/s"
    "qLvV3c2gjjfZGrDp+cb/6LTgE5B+iRAKSbMT/ERkTqQBDhv5PnaP8qCqHkBnVKzCT3nK0r0caOXDiAp27unoNZesI3UUeXd2+oq50+YHhZtQXo7Ct+5WNADT"
    "oq2N8cAA61k5r6/@KEY@pWhBKmc0sD+o@END@W7GxTIrXiEh1c63u4NKq3feyfO6zd8Pb6UwxtKqKLLUelZwrOYEmg1ShnHz4gTHHrDANuxInMWfSMHJ3kwo"
    "5vtJIVvyH3BvpK7oreNg9Nkr9csd/GkQuhtXgkjIOKObyMvrrKhPd88Ex/RIz1KzVdzoZZMoLbDu7h35zSaizp2jcVXAVvaSR2oq4L/qQXOrr1qIj5wEBkjw"
    "QEhSnTwFFzXbHQuhOyDgFNX8R2YgnQV6nEOadzN8IizxyIr9uIghz9jSS1pH3OfCIfBnYv4ZaxQW4oDWM/6uWDUyqg9HkOkaWzMwHYLMJjFgxyB7O7SuG5do"
    "z8ET41FkZEh6txDHHKjy2wfTHDU6AbXy0hTuaq7FKUm3X8R3pwHqYAc7U4/mSu+aqB/xEWKn7CmviIB8ul/1UlK2FLcmYmN+cvfSkXrrOgsDoqW7qWIRK6jR"
    "07cUpP2WG6WnIjQvRgG2nj6nbx72EBMG4T27FmZfavC1xPDS+@KEY@pwgjNJ0FvWGRezwi74QdIQdmUuKVyquWuvXz4tBOXqMMqco@END@tZ/t60n9pDZfLt"
    "1rO8oeHvGLyZ1oFCVU9h/aMvNHL5unThRz5+NbSnE0FjVrJbGfZFo4Ty1GWHzum1cgNc8WEDLw1WNraAC3Oliu8tByfuPVUlbcTvaZjgICd8l0/3AgRcOFfi"
    "Hreu72W+kfaYof1HrWqoEIXbsphs334iWOglnvEA91ZqN430/DFfXwPEG7IQ5dxYhlXRvjjcYt8BSFg2ZiUW1sQt/kTmxazV8pg6zpRy4PR1Wi7EL4ZqzCu8"
    "3KrzbO/xqjCGKQPd0DZJBC7Iucjjb9xWCZO9X+o2L+0JwloOwucrBTqbDPwewXlDVXjDSDaBS2J3a4h3eGQG3BCKyJwelpk3EFrMa8JyST9o3r6NcgTJD8ht"
    "wTmnAY6vemwbSVlNzoQkJ0WDx82OxLTFTacuHDvbOoFD7y++mH1x8@KEY@aJ3QUfLh3AqfKyxcUSiDbanZmCNGza6jb6pZ@END@9/7hvRkODnXFaFPv9uQpw"
    "h4VcLc6vojJenZwkc404kB+dWF/iMAyQSijzdrY3MByUnXdwQhBbjsl8QmOFZkj2a4txQZRr4+pZkWQKtXxLm9eLdVCzyAwWredXm2NI/OD1ieyNI5MjT3am"
    "JVyuvq6NvVLfTd8uPTm6WDbYnUv1305AxPd2pdeEvbIrghrITb/GvVL5+6WY2/7aWt/gORt4Fds91zpXtcjKiuOe0xzlwb6SANoCdnaUBpxp7O/8R0M2vFRd"
    "QWKgrWVU5HXqylzTQzvMv7vEmBrjBmFZyJvre9K+gJvc2GsY1YymPEgWCG/DlQlvONcpLjN12YNvLD24lHOSl83Cv33wMPLRypIc1WBkpRiFaeqLzgr7OqzH"
    "VuQhF4@KEY@bYJzitZUyXlgPA009qBpleHIJ9uJUSdJO78iisUgHkoqUpf+oXZQF9X/7v2fikgemCD@END@y+RXr8aN3D4GhTtjRIqrvaT6vkJ/lcK/SOmEH"
    "uzsb9F8HKpAyveQ6vPcXH4BOz/oCq5P3ndvfom2lnRKP83fxftOWe0LTvjQpmVKuKj6OrRkkdBKph1R9QjI/1U4krJ25Gb0r2qZvDQFkNx5B7VnYEsJGOT/A"
    "bAELSqoQOz8R2nHaIGnERw0f/DchUZQAQKLRc6/O59eVeNtQHbTjdmKz8+PrVNfynvlN2i3hu3h9s2tH63sQ/QUWETewhfKw6GTXA4JUtIuFC5GMkSoV8WZU"
    "oXUOpbDk43E3SqCWD1V55QOfwlYiC2eTUPZ7jTxJ54uJ5jpBaZWSQHhzzFtAaOca8Y2SlIlv1h0dBcL7eHFZ+r/rIGulPEZQ+CeNuvx9OfvcSJWMQEWEZlYR"
;
