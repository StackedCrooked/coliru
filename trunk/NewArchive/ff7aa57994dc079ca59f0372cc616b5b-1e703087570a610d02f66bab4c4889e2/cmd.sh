g++-4.8 -std=c++11 -O2 -pthread main.cpp -o sehe-json
./sehe-json <<"MORE DECENT"
{
    "Image": {
        "Width":  800,
        "Height": 600,
        "Title":  "View from 15th Floor",
        "Thumbnail": {
            "Russian":  "На берегу пустынных волн",
            "Escapes": "Ha \"\u0431\u0435\u0440\u0435\u0433\u0443\" shows up \\similar\\.\r\b\n",
            "берегу": "Russian",
            "Dummy": null,
            "Yummy": false,
            "Tummy": true,
            "Url":    "http://www.example.com/image/481989943",
            "Height": 125,
            "Width":  "100"
        },
        "IDs": [116, 943, 234, 38793]

    }
}
HERE