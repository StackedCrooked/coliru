# include <Siv3D.hpp>

/* puzzle.txt (空行なし）
wce
hogehoge
11111
10000
11111
00001
11111
*/

void Main()
{
    TextReader reader(L"puzzle.txt");

	if (!reader)
	{
		// ロード失敗
		return;
	}

	/////////////////////////////
	// 追加

	String author;
	String pass;

	if (const auto line = reader.readLine())
	{
		author = line.get();
	}
	else
	{
		return;
	}

	if (const auto line = reader.readLine())
	{
		pass = line.get();
	}
	else
	{
		return;
	}
	                           //
	/////////////////////////////

	std::vector<int> data;

	optional<int> lineWidth;

	while (auto line = reader.readLine())
	{
		const int length = line.get().length;

		if (!lineWidth)
		{
			if (length == 0)
			{
				// 1 行目が空行
				return;
			}

			lineWidth = length;
		}

		if (length != lineWidth.get())
		{
			// 現在の列の要素数が 1 行目と違う
			return;
		}

		for (const auto elem : line.get())
		{
			data.push_back(elem == L'0' ? 0 : 1);
		}
	}

	if (!lineWidth)
	{
		// テキストファイルに何も書かれていなかった
		return;
	}

	const int sheetWidth = lineWidth.get();
	const int sheetHeight = data.size() / sheetWidth;
}