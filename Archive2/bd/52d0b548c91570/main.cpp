/*
  Cryo HNM 1 Dumper v.0.2 by VAG, ARR.  vagsoft@mail.ru
  Feel free to use this code for any purposes as long as the above line is kept

  2006/07  vag     initial version
  2009/10  vag     cleanup, sound extraction
  2009/10  rymoah  console based version
*/

#include <stdio.h>
#include <string.h>
#pragma comment(lib, "user32")
#pragma comment(lib, "comdlg32")

#define LZCHECKCRC

#pragma pack(push, 1)
typedef struct _LZHEADER {
unsigned short    ulen;
unsigned char	zero;	// must be zero
unsigned short	plen;   // including this header
unsigned char	salt;
} LZHEADER, *PLZHEADER;
#pragma pack(pop)

int LZUnpack(void *input, void *output)
{
printf("pack\n");
	unsigned char* inp = (unsigned char*)input;
	unsigned char* out = (unsigned char*)output;
#ifdef LZCHECKCRC
	unsigned char crc = 0;
	for(int i = 0;i < sizeof(LZHEADER);i++)
		crc += inp[i];
	if((crc != 171) || (((LZHEADER*)inp)->zero != 0))
	{
printf("LZ: BAD CRC\n");
		return 0;
	}
#endif

	inp += sizeof(LZHEADER);

	unsigned long queue = 0;
#define GetBit() (((queue > 0x20000) ? (queue >>= 1) : queue = 0xFFFF0000 | *(unsigned short*)((inp += 2)-2)) & 1)

	for(;;)
	{
		if(GetBit())
			*out++ = *inp++;
		else
		{
			int len;
			int ofs;
			if(GetBit())
			{
				len = *inp & 7;
				ofs = (-1l << 13) + (*(unsigned short*)inp >> 3); inp += 2;
				if(len == 0)
				{
					len = *inp++;
					if(!len)
						break;
				}
			}
			else
			{
				len = 0;
				len = (len << 1) | GetBit();
				len = (len << 1) | GetBit();
				ofs = (-1l << 8) + (*(unsigned char*)inp >> 0); inp += 1;
			}
			len += 2;
			while(len--) *out++ = out[ofs];
		}
	}
	return out - (unsigned char*)output;
}

#pragma pack(push, 1)
struct _TGAH {
char	IDFieldLength;
char	ColorMapType;
char	ImageType;
short	CMapOrigin;
short	CMapLength;
char	CMapSize;
short	XOrigin;
short	YOrigin;
short	Width;
short	Height;
char	ImagePixSize;
char	ImageDescriptor;
}		TGAHeader = {0, 1, 1, 0, 256, 24, 0, 0, 0, 0, 8, 0x20};
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct _RGB {
char	r, g, b;
} RGB, *PRGB;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct _BGR {
unsigned char b;
unsigned char g;
unsigned char r;
} BGR, *PBGR;
#pragma pack(pop)

void SaveTGA(char *fn, struct _TGAH *tga, int width, int height, void *pal, void *pix)
{
	FILE *f = fopen(fn, "wb+");
	if(f)
	{
		tga->Width = width;
		tga->Height = height;
		fwrite(tga, sizeof(_TGAH), 1, f);
		if(tga->ColorMapType == 1)
		{
			BGR palet[256];
			RGB	*dacpal = (RGB*)pal;
			for(int k = 0;k < tga->CMapLength;k++)
			{
				palet[k].r = (dacpal[k].r << 2) | (dacpal[k].r >> 4);
				palet[k].g = (dacpal[k].g << 2) | (dacpal[k].r >> 4);
				palet[k].b = (dacpal[k].b << 2) | (dacpal[k].r >> 4);
			}
			fwrite(palet, sizeof(palet[0]), 256, f);
		}
		fwrite(pix, (tga->ImagePixSize + 7) / 8, tga->Width * tga->Height, f);
		fclose(f);
	}
}

unsigned char temp[65536];
unsigned char buff[65536];
unsigned char back[65536];

int UnpackCodebook(unsigned char* input, unsigned char* output, int outputlen, unsigned char colorbase)
{
	unsigned char* inp = input;
	unsigned char* outend = output + outputlen;
	int	flip = 0;
	unsigned char o;
	for(;output < outend;)
	{
		unsigned char tag = *input++;
		if(tag & 0x80)
		{
			unsigned char len;
			if(!flip)
			{
				o = *input++;
				len = o >> 4;
			}
			else
			{
				len = o & 0xF;
			}
			flip ^= 1;
			unsigned char ofs = (tag << 1) | (len & 1);
			len = (len >> 1) + 2;
			while(len--) *output++ = output[-ofs-1];
		}
		else
		{
			if(tag)	tag += colorbase;
			*output++ = tag;
		}
	}
	return input - inp;
}

void ADUnpack(unsigned char* input, unsigned char* output, int* x, int* y)
{
#pragma pack(push, 1)
	typedef struct _ADHDR {
	unsigned short	framesize;
	unsigned short	codebooksize;
	unsigned char	flags;
	unsigned char	salt;
	} ADHDR;
#pragma pack(pop)

	ADHDR* hdr = (ADHDR*)input; input += 6;
	if(!(hdr->flags & 0x4))
	{
printf("EXTRA 4\n");
		*x = *(unsigned short*)input; input += 2;
		*y = *(unsigned short*)input; input += 2;
	}
	else
	{
		*x = 0;
		*y = 0;
	}
	unsigned char* inp = input;
	unsigned char* outend = output + hdr->framesize;
	unsigned char* temp = outend - hdr->codebooksize;
	inp += UnpackCodebook(input, temp, hdr->codebooksize, (hdr->flags & 0x40) ? 0x80 : 0);

	unsigned short queue = 0x8000;
#ifdef GetBit
#undef GetBit
#endif
#define GetBit() (((queue == 0x8000) ? ((queue = (*(unsigned short*)((inp += 2)-2) << 1) | 1) & 0) | *(unsigned short*)((inp)-2) : (queue & 0x8000) ? (queue <<= 1) | 0x8000 : (queue <<= 1) & 0x7FFF ) >> 15)

	int len, o, flip = 0;
	if(!(hdr->flags & 0x80))
	{
		for(;;)
		{
			while(!GetBit()) *output++ = *temp++;
			unsigned char c = *temp++;
			if(!GetBit())
			{
				*output++ = c;
				*output++ = c;
			}
			else
			{
				if(!GetBit())
				{
					*output++ = c;
					*output++ = c;
					*output++ = c;
				}
				else
				{
					if(!GetBit())
					{
						*output++ = c;
						*output++ = c;
						*output++ = c;
						*output++ = c;
					}
					else
					{
						if(output >= outend)
							break;

						if(!flip)
						{
							o = *inp++;
							len = o >> 4;
						}
						else
						{
							len = o & 0xF;
						}
						flip ^= 1;

						if(!len)
							len = *inp++ + 16;

						for(len += 4;len;len--)
							*output++ = c;
					}
				}
			}
		}
	}
	else
	{
		for(;;)
		{
			while(!GetBit()) *output++ = *temp++;
			unsigned char c = *temp++;
			if(!GetBit())
			{
				if(!flip)
				{
					o = *inp++;
					len = o >> 4;
				}
				else
				{
					len = o & 0xF;
				}
				flip ^= 1;

				if(!len)
					len = *inp++ + 16;

				for(len += 4;len;len--)
					*output++ = c;
			}
			else
			{

				if(!GetBit())
				{
					*output++ = c;
					*output++ = c;
				}
				else
				{
					if(!GetBit())
					{
						*output++ = c;
						*output++ = c;
						*output++ = c;
					}
					else
					{
						if(output >= outend)
							break;
						
						*output++ = c;
						*output++ = c;
						*output++ = c;
						*output++ = c;
					}
				}
			}
		}
	}
}

void DecodeFrame(unsigned char* input, unsigned char* output, int* x, int* y)
{
	*x = -1;
	*y = -1;
	unsigned char* inp = (unsigned char*)input + 4; // flags1+flags2
	unsigned char* out = (unsigned char*)output;
	unsigned char crc = 0;
	for(int i = 0;i < sizeof(LZHEADER);i++)
		crc += inp[i];
	if(crc == 171)
	{
printf("UNPQ - 171\n");
		LZUnpack(inp, output);
	}
	else if(crc == 172)
	{
printf("UNPQ - 172\n");
//MessageBox(NULL, "172", "172", 0);
	}
	else if(crc == 173)	// 0xAD
	{
printf("UNPQ - 173\n");
		ADUnpack(inp, output, x, y);
	}
	else
	{
		printf("UNPQ - Bad Mode (%d)\n", crc);
		//MessageBox(NULL, "UNK", "UNK", 0);
	}
	
}

int ProcessPalette(unsigned char* input, RGB* palet)
{
	unsigned char* inp = input;
	while(*(unsigned short*)input != 0xFFFF)
	{
		int beg = *input++;
		int cnt = *input++; if(cnt == 0) cnt = 256;
		if((cnt == 1) && (beg == 0))
		{
			input += 3;
			continue;
		}
		unsigned char* pal = (unsigned char*)&palet[beg];
		for(int i = 0;i < cnt * sizeof(palet[0]);i++)
		{
			pal[i] = *input++;
		}
	}
	return (input + 2) - inp;
}

void RenderOver(unsigned char* input, unsigned char* out, int x, int y, int w, int h, unsigned char mode, int width, int height)
{
	if(x == -1) x = 0;
	if(y == -1) y = 0;
	for(int yy = 0;yy < h;yy++)
		for(int xx = 0;xx < w;xx++)
			if((mode != 0xFF) || input[yy * w + xx])
				out[(y + yy) * width + x + xx] = input[yy * w + xx];
}

RGB	dacpal[256];

void test(char* fn)
{
	unsigned short	chunklen;
	FILE* f = fopen(fn, "rb");
	if(f)
	{
		int frmno = 0;
		unsigned long index = 0;
		int	gotsound = 0;
		while(!feof(f))
		{
			long o = ftell(f);
			if(fread(&chunklen, sizeof(chunklen), 1, f) != 1) break;
			if(chunklen == 0)
				break;

			unsigned char* chunk = new unsigned char[chunklen - 1];
			fread(chunk, 1, chunklen - 2, f);
			unsigned char* chk = chunk;
			printf("Chunk @ %6X\n", o);

			if(index == 0)
			{
				chk += ProcessPalette(chk, dacpal);

				// offsets table, don't care	
			}
			else
			{
				for(;;chk += *(unsigned short*)&chk[2])
				{
					unsigned short tag = *(unsigned short*)chk;
					printf("%c%c : %d\n", chk[0], chk[1], index);
					if(tag == 'tp')
					{
//	MessageBox(NULL, "PT", "PT", 0);
					}
					else if(tag == 'lk')
					{
//	MessageBox(NULL, "KL", "KL", 0);
					}
					else if(tag == 'ds')
					{
					// sound
						FILE* vocf = fopen("sound.voc", gotsound ? "ab+" : "wb+");
						gotsound |= 1;
						if(vocf)
						{
							int sndlen = *(unsigned short*)&chk[2] - 4;
							if (sndlen > 0)
								fwrite(chk + 4, 1, sndlen, vocf);
							fclose(vocf);
						}

					}
					else if(tag == 'lp')
					{
					// palette
						ProcessPalette(chk + 4, dacpal);
					}
					else
					{
					// frame
printf("FLAGS %X %X\n", ~0x1FF & *(unsigned short*)&chk[0], ~0xFF & *(unsigned short*)&chk[2]);
						int w = 0x1FF & *(unsigned short*)&chk[0];
						int h = 0xFF & *(unsigned short*)&chk[2];
						unsigned char mode = chk[3];
printf("%dx%d\n", w, h);

						unsigned short flags = tag;
						int x, y;

						if(h != 0)
						{
							DecodeFrame(chk, temp, &x, &y);
//							for(int i = 0;i < 320 * 200;i++) buff[i] = back[i];
							RenderOver(temp, buff, x, y, w, h, mode, 640, 400);
						}
						char tgan[32];
						sprintf(tgan, "frame_%04d.tga", frmno++);
						SaveTGA(tgan, &TGAHeader, 640, 400, dacpal, buff);
						break;
					}
				}
			}

			delete [] chunk;
			index++;

			fseek(f, o + chunklen, SEEK_SET);
		}
		fclose(f);
		printf("%s %s %s \n", "File" , fn, "dumped");
	}
	else
		printf("Unable to open file\n");
}

int main(int argc, char** argv)
{
	printf("\nCryo HNM 1 Dumper v.0.2 by VAG, ARR. \n\n");

	if(argc != 2) {
		printf("Usage: hnm1dump input_hnm_file\n\n");
		return 1;
	}

	else {
		test(argv[1]);
		return 0;
	}
}

