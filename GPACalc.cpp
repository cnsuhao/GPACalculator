// GPACalc.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#define SAFE_RELEASE(p) if((p))delete(p);(p)=nullptr;

using namespace std;

wchar_t const * DATA_FILE_PATH = L"data.txt";

wstring& trim(wstring &s);
vector<wstring> split(wstring str, wstring pattern);

//����γ����ƣ��ɼ���ѧ�֣�����
typedef struct
{
	float score;
	float credit;
	float gpa;
} DataItem;

int _tmain(int argc, _TCHAR* argv[])
{
	system("mode con cols=140 lines=40");

	cout << "�����򽫸��������ļ��Զ���������ƽ������(GPA)" << endl;
	cout << "Tip:�ɽ�data.txtֱ���ϵ�����ͼ���ϼ���:\n" << endl;

	wifstream *file = new wifstream;

	if (argc < 2){
		wstring path(argv[0]);
		wstring::size_type pos = path.rfind('\\');
		path = path.substr(0, pos + 1);
		file->open(path + DATA_FILE_PATH, wifstream::in);
	}
	else
		file->open(argv[1], wifstream::in);

	if (!file->is_open()){
		cout << "�ļ���ʧ�ܣ���ȷ���ļ����ں���Ȩ���ʣ�" << endl;
		SAFE_RELEASE(file);
		system("pause");
		exit(-1);
	}

	vector<DataItem> datalist;
	datalist.reserve(20);

	wcout.flags(ios::left);
	cout.flags(ios::left);

	cout << setw(30) << "�γ�����";
	cout << "���Ƽ���\n" << endl;

	int _line = 1;
	while (file->good())
	{
		wchar_t buf[256];
		file->getline(buf, 256);
		//
		wstring s(buf);
		trim(s);
		vector<wstring> items = split(buf, L" ");
		int _size = items.size();
		if (_size == 0) break;
		else if (_size != 3){
			//��������
			cout << "�Բ��������������ݸ�ʽ�д�����������ԣ�" << endl;
			wcout << "[on line " << _line << " ]:" << buf << endl;
			file->close();
			SAFE_RELEASE(file);
			system("pause");
			exit(0);
		}
		int i = 0;
		DataItem _item = {0, 0, 0};
		for (auto it = items.begin(); it != items.end(); ++it, ++i)
		{
			wstringstream wss;
			float _int;
			trim(*it);
			wstring str = it->c_str();
			wss << it->c_str();
			wss >> _int;
			switch (i)
			{
			case 1:
				_item.score = _int;
				break;
			case 2:
				_item.credit = _int;
				break;
			}
			//����γ���
			if (i == 0) wcout << setw(30) << it->c_str();
		}
		//���㵥�Ƽ���
		_item.gpa = _item.score / 10 - 5;
		//�������
		cout << setprecision(1) << setiosflags(ios::fixed) << _item.gpa << endl;
		//���뵥��
		datalist.push_back(_item);
		_line++;
	}
	file->close();
	SAFE_RELEASE(file);

	//����ƽ������
	float _a = 0.0;
	float _credit_sum = 0.0;
	for (auto it = datalist.begin(); it != datalist.end(); ++it)
	{
		_a += it->credit * it->gpa;
		_credit_sum += it->credit;
	}
	float _gpa = _a / _credit_sum;

	cout << "\n����ƽ������Ϊ��" << setprecision(2) << _gpa << endl;
	cout << "\n[ver0.1 Powered by Micooz @ Chengdu university of technology 2014/1/18] Good Luck��" << endl;
	cout << endl;

	system("pause");
	return 0;
}

wstring& trim(wstring &s)
{
	if (s.empty())
		return s;
	wchar_t _ch = L' ';
	s.erase(0, s.find_first_not_of(_ch));
	s.erase(s.find_last_not_of(_ch) + 1);
	return s;
}

//�ַ����ָ��
vector<wstring> split(wstring str, wstring pattern)
{
	wstring::size_type pos;
	vector<wstring> result;
	str += pattern;//��չ�ַ����Է������
	int size = str.size();

	for (int i = 0; i < size; i++)
	{
		pos = str.find(pattern, i);
		if (pos < size)
		{
			wstring s = str.substr(i, pos - i);
			if (s != L"")
				result.push_back(s);
			i = pos + pattern.size() - 1;
		}
	}
	return result;
}
