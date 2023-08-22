//---------------------------------------------------------------------------

#include <vcl.h>
#include <iostream>
#include <fstream>
#include <string>
#pragma hdrstop

#include "Main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
UnicodeString inputFilename="";
//--------------------�������������� �������� � �����------------------------
void CreateTextImageFromBitmap(TBitmap *bmp, const std::string& outputFilename){
	if (bmp != NULL){
		TFileStream *outputFileStream = new TFileStream(outputFilename.c_str(), fmCreate);
		char palette[11] = {'@', '#', '8', '&', 'o', ':', '*', '.', ' ', ' ', ' '};//�������� ������
		for (int i = 0; i < bmp->Height; i++){
			for (int j = 0; j < bmp->Width; j++){
				TColor pixel = bmp->Canvas->Pixels[j][i];
				int red = GetRValue(pixel);
				int green = GetGValue(pixel);
				int blue = GetBValue(pixel);
				unsigned int brightness = (red + green + blue) / 3;//������� �������������� ���� ������ - �������
				int index = brightness * 10 / 255;//�������� ������ ������� ������� ��������� ����������
				char ch = palette[index];
				outputFileStream->WriteBuffer(&ch, sizeof(char));
			}//for int j
			char newline = '\n';
			outputFileStream->WriteBuffer(&newline, sizeof(char));
		}//for int i

		delete outputFileStream;
	}//if (bmp!=Null)
}//CreateTextImageFromBitmap

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::N2Click(TObject *Sender){
	if(OPDLG->Execute()){
        inputFilename = OPDLG->FileName;
		MainImage->Picture->LoadFromFile(inputFilename);
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender){
	UnicodeString outputFilename = "output.txt"; // ��� ����� ��� ���������� ����������� �� �������� ������
	TPicture *picture = new TPicture();
	if(inputFilename != ""){
        picture->LoadFromFile(inputFilename);
	}else{
        Application->MessageBox(L"�������� ������� �������� �� ������� �������",L"������!");
	}
	if (picture->Graphic != NULL && inputFilename!=""){
		TBitmap *bmp = new TBitmap();
		bmp->Assign(picture->Graphic);
		CreateTextImageFromBitmap(bmp, AnsiString(outputFilename).c_str());
		delete bmp;
        Application->MessageBox(L"���� �������� ������� ������������� � ��������� � ����� �������:\"Debug\\output.txt\"",L"�����!");
		}//if not empty picture
		delete picture;
}//void Button
//---------------------------------------------------------------------------

