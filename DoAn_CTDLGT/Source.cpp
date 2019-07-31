#include <iostream>
#include <string>
#include <time.h>
#include <fstream>
#include <map>
#include <algorithm>
#include <iterator>

#define SOLUONGDAUSACH 1000
#define THOIGIANMUONSACHTOIDA 15
#define SOLUONGDOCGIA 1000
#define SOLUONGSACHMUONTOIDA 3
#define TRANGTHAITHE_HOATDONG 1
#define TRANGTHAITHE_KHOA 0
#define TRANGTHAISACH_DUOCMUON 0
#define TRANGTHAISACH_KHONGDUOCMUON 1
#define TRANGTHAISACH_DATHANHLY 2
#define TRANGTHAIMUONTRA_DANGMUON 0
#define TRANGTHAIMUONTRA_DATRA 1
#define TRANGTHAIMUONTRA_MATSACH 2
#define FILEPATH_DATABE_DOCGIA "DocGia.txt"
#define FILEPATH_DATABE_DAUSACH "DauSach.txt"
using namespace std;




struct DanhMucSach		
{						
	int MaSach;			
	int TrangThai;		
	string ViTri;		
};

struct SachNode
{
	DanhMucSach sach;
	SachNode *next;
};
struct ListSach
{
	SachNode *head;
	SachNode *tail;
};
struct DauSach
{
	int ISBN;
	string TenSach;
	int SoTrang;
	string TacGia;
	int NamXuatBan;
	string TheLoai;
	ListSach *ListSach;
};


struct Date
{
	int d;
	int m;
	int y;
};



struct MuonTra
{
	int MaSach;
	int TrangThai;
	Date NgayMuon;
	Date NgayTra;
};
struct MuonTraNode
{
	MuonTra mt;
	MuonTraNode *next;
};
struct ListMuonTra
{
	MuonTraNode *head;
	MuonTraNode *tail;
};
struct DocGia
{
	int MaDocGia;
	string Ho;
	string Ten;
	string Phai;
	int TrangThaiThe;
	ListMuonTra *ListMuonTra;
};
struct TreeNode
{
	TreeNode *left;
	TreeNode *right;
	DocGia dg;
};
typedef struct TreeNode Tnode;
typedef Tnode* Tree;





void inputdocgia(Tree t, DocGia &dg);
void inittree(Tree &t);
void searchstandfor(Tree &p, Tree &t);
Tnode *CreateTnode(DocGia dg);
void inputdocgiafromfile(Tree &t, string file, ListMuonTra *lmt);
void LNR(Tree t);
int removedocgia(Tree &t, int MaDocGia);
void outputdocgia(DocGia dg);
int InsertTree(Tree &t, DocGia dg);
int updatedocgia(Tree &t, int x, Tree p);
DocGia *searchdocgia(Tree t, int MaDocGia);
void outputmuontra(ListMuonTra *lmt);
void outputsachmuon(MuonTra mt);
void outputdate(Date date);
MuonTraNode * getNodeMuonTra(MuonTra mt);
void loadsachmuonfromfile(ListMuonTra *lmt, string file);
void addheadlistmuontra(ListMuonTra *lmt, MuonTraNode *p);
int SachDocGiaMuon(Tree t, int MaDocGia);
void initlistsachmuon(ListMuonTra *lmt);
void outputlistsachtratre(ListMuonTra *lmt);
void listsachtratre(Tree t);
void outputsachtratre(MuonTra mt);
void sortedInsert(MuonTraNode** head_ref, MuonTraNode* new_node);
int menu();
int menu_1();
int menu_2();
void writefiledocgia(DocGia dg, string file);
void removedocgiafromfile(int MaDocGia, string file);
void inputdocgiafromfiletoarray(DocGia ldg[], string file, int &element);
void sortdocgia(DocGia ldg[], int soluongdocgia);
void outputdocgiaarr(DocGia ldg[], int soluongdocgia);
void inputdausachfromfile(DauSach lds[], string file, int &element,ListSach *listsach_thuvien);
void initlistsach(ListSach *ls);
void loadlistsachfromfile(ListSach *ls, string file,ListSach *listsach_thuvien);
void outputdausach(DauSach ds);
SachNode * getNodeSach(DanhMucSach dms);
void addheadlistsach(ListSach *ls, SachNode *p);
void outputlistdausach(DauSach lds[], int length);
void sortlistdausachtheoten(DauSach lds[], int length);
void inputdausach(DauSach lds[], DauSach &ds, int &soluongdausach, ListSach *ls);
void inputsach(DanhMucSach &dms, ListSach *ls);
DanhMucSach *searchsach(ListSach *ls, int MaSach);
void sortlistdausachtheoma(DauSach lds[], int length);
void writefiledausach(DauSach ds, string file);
void outputsach(DanhMucSach dms);
DauSach *searchdausach(string tensach, DauSach lds[], int soluongsach);
int getDifference(Date dt1, Date dt2);
bool checksachnhap(int soluongsach);
bool checksachmuon(int soluongsach);
bool checkdate(Date date);
void updatetrangthaisachformfile(DanhMucSach *dms, string file);
bool checksachtra(int soluongsachtra, int soluongsachdangmuon);
MuonTra * searchsachmuon(ListMuonTra *lmt, int MaSach);
void updatemuontrafromfile(MuonTra *mt, string file);
void initlistsachmuon(ListMuonTra *lmt);
void getall(Tree t, ListMuonTra *lmt);
void addtaillistmuontra(ListMuonTra *lmt, MuonTraNode *p);
void inputsachmuon(MuonTra &mt, ListSach*ls,ListMuonTra * listmuontra,int madocgia,DauSach ds[],int soluongdausach,ListMuonTra *listmuontratatca);
const int monthDays[12] = { 31, 29, 31, 30, 31, 30,
						   31, 31, 30, 31, 30, 31 };
template <typename A, typename B>
pair <B, A> flip_pair(const pair<A, B> &p)
{
	return pair<B, A>(p.second, p.first);
}
template <typename A,typename B>
multimap<B, A> flip_map(const map<A, B> &src)
{
	multimap<B, A> dst;
	transform(src.begin(), src.end(), inserter(dst, dst.begin()),flip_pair<A,B>);
	return dst;
}

Date today;
ListSach *ls_thuvien = new ListSach;
ListMuonTra *lmt = new ListMuonTra;

int main()
{
	system("color 0a");
	Tree t;
	DocGia ldg[SOLUONGDOCGIA];
	DauSach lds[SOLUONGDAUSACH];
	DauSach *timsach;
	DocGia *docgia;
	MuonTra * muontra;
	MuonTra * muontra1;
	DanhMucSach *danhmucsach = NULL;
	map<int, int> sach_soluong;
	multimap<int, int> dst;
	initlistsach(ls_thuvien);
	inittree(t);
	srand(time(0));
	time_t time1 = time(0);
	tm*now = localtime(&time1);
	today.d = now->tm_mday;
	today.m = now->tm_mon + 1;
	today.y = now->tm_year + 1900;
	bool flag = true;
	bool flag_1 = true;
	bool flag_2 = true;
	int choice;
	int choice_1;
	int choice_2;
	int soluongdocgianhap;
	int soluongdausachnhap;
	int soluongdocgia = 0;
	int soluongdausach = 0;
	int soluongsachcanmuon;
	int soluongsachcantra;
	int soluongsachquahan;
	int madocgia;
	int soluongsachdangmuon;
	int ISBN;
	int count;
	string tensach;
	initlistsachmuon(lmt);
	inputdocgiafromfile(t, "DocGia.txt",lmt);
	inputdausachfromfile(lds, "DauSach.txt", soluongdausach, ls_thuvien);
	while (flag)
	{
		choice = menu();
		switch (choice)
		{
		case 1:
			flag_1 = true;
			while (flag_1)
			{
				choice_1 = menu_1();
				switch (choice_1)
				{
				case 1:
					cout << "So luong doc gia can them: ";
					cin >> soluongdocgianhap;
					for (int i = 0; i < soluongdocgianhap; i++)
					{
						DocGia dg;
						inputdocgia(t, dg);
						InsertTree(t, dg);
						writefiledocgia(dg, "DocGia.txt");
					}	
					break;
				case 2:
					cout << "Nhap ma doc gia can xoa: ";
					cin >> madocgia;
					if (removedocgia(t, madocgia) == 1)
						removedocgiafromfile(madocgia,"DocGia.txt");
					break;
				case 3:
					cout << "Nhap ma doc gia can hieu chinh: ";
					cin >> madocgia;
					updatedocgia(t, madocgia, t);
					break;
				default:
					flag_1 = false;
					break;
				}
			}
				break;
		case 2:
			flag_2 = true;
			while (flag_2)
			{
				choice_2 = menu_2();
				switch (choice_2)
				{
				case 1:
					LNR(t);
					break;
				case 2:
					soluongdocgia = 0;
					inputdocgiafromfiletoarray(ldg, "DocGia.txt",soluongdocgia);
					sortdocgia(ldg, soluongdocgia);
					outputdocgiaarr(ldg, soluongdocgia);
					break;
				default:
					flag_2 = false;
					break;
				}
			}
			break;
		case 3:
			cout << "So luong dau sach can nhap: ";
			cin >> soluongdausachnhap;
			for (int i = 0; i < soluongdausachnhap; i++)
			{
				sortlistdausachtheoma(lds, soluongdausach);
				DauSach ds;
				inputdausach(lds, ds, soluongdausach,ls_thuvien);
			}
			break;
		case 4:
			sortlistdausachtheoten(lds, soluongdausach);
			outputlistdausach(lds, soluongdausach);
			break;
		case 5:
			cout << "Nhap ten sach can tim: ";
			cin >> tensach;
			sortlistdausachtheoten(lds, soluongdausach);
			timsach = searchdausach(tensach, lds,soluongdausach);
			if (timsach == NULL)
				cout << "Khong tim thay sach" << endl;
			else
			{
				outputdausach(*timsach);
				for (SachNode *p = timsach->ListSach->head; p != NULL; p = p->next)
					if (p->sach.TrangThai == 0)
						outputsach(p->sach);
			}
			break;
		case 6:
			soluongsachquahan = 0;
			cout << "Nhap ma doc gia: ";
			cin >> madocgia;
			docgia = searchdocgia(t, madocgia);
			if (docgia != NULL)
			{
				for (MuonTraNode *p = docgia->ListMuonTra->head; p != NULL; p = p->next)
					if (p->mt.TrangThai == 0 && getDifference(p->mt.NgayMuon, today) > THOIGIANMUONSACHTOIDA)
						soluongsachquahan++;
				if (docgia->TrangThaiThe == 0)
					cout << "The da bi khoa" << endl;
				else
				if (soluongsachquahan > 0)
					cout << "Co sach muon qua han" << endl;
				else
				{
					soluongsachdangmuon = SachDocGiaMuon(t, madocgia);
					if (soluongsachdangmuon == 3)
						cout << "Da muon toi da 3 quyen sach vui long tra sach truoc khi muon" << endl;
					else
					{
						cout << "So luong sach can muon: ";
						cin >> soluongsachcanmuon;
						while (!(checksachnhap(soluongsachcanmuon) && checksachmuon(soluongsachdangmuon + soluongsachcanmuon)))
						{
							cout << "Vui long nhap dung thong tin" << endl;
							cout << "So luong sach can muon: ";
							cin >> soluongsachcanmuon;
						}
						for (int i = 0; i < soluongsachcanmuon; i++)
						{
							MuonTra mts;
							inputsachmuon(mts, ls_thuvien, docgia->ListMuonTra, docgia->MaDocGia, lds, soluongdausach,lmt);
						}
					}
				}
			}
			else
				cout << "Khong ton tai doc gia" << endl;
			break;
		case 7:
			soluongsachquahan = 0;
			cout << "Nhap ma doc gia: ";
			cin >> madocgia;
			docgia = searchdocgia(t, madocgia);
			if (docgia != NULL)
			{
				{
					soluongsachdangmuon = SachDocGiaMuon(t, madocgia);
					if (soluongsachdangmuon == 0)
						cout << "Doc gia khong muon sach nao" << endl;
					else
					{
						cout << "So luong sach can tra: ";
						cin >> soluongsachcantra;
						while (!(checksachnhap(soluongsachcantra) && checksachtra(soluongsachcantra,soluongsachdangmuon)))
						{
							cout << "Vui long nhap dung thong tin" << endl;
							cout << "So luong sach can tra: ";
							cin >> soluongsachcantra;
						}
						for (int i = 0; i < soluongsachcantra; i++)
						{
							int masach;
							cout << "Nhap ma sach tra: ";
							cin >> masach;
							while ((muontra = searchsachmuon(docgia->ListMuonTra, masach)) == NULL)
							{
								cout << "Doc gia khong muon sach nay" << endl;
								cout << "Nhap ma sach tra: ";
								cin >> masach;
							}
							cout << "Nhap ngay tra sach";
							cin >> muontra->NgayTra.d >> muontra->NgayTra.m >> muontra->NgayTra.y;
							while (checkdate(muontra->NgayTra) && getDifference(muontra->NgayMuon, muontra->NgayTra) < 0 && getDifference(muontra->NgayTra, today) < 0)
							{
								cout << "Ngay tra sach khong hop le" << endl;
								cout << "Nhap ngay tra sach";
								cin >> muontra->NgayTra.d >> muontra->NgayTra.m >> muontra->NgayTra.y;
							}
							muontra->TrangThai = 1;
							string file = "SachMuon_DG" + to_string(docgia->MaDocGia) + ".txt";
							updatemuontrafromfile(muontra, file);
							muontra1 = searchsachmuon(lmt, masach);
							muontra1->TrangThai = 1;
							muontra1->NgayTra = muontra->NgayTra;
							for (int i = 0; i < soluongdausach; i++)
							{
								ISBN = lds[i].ISBN;
								danhmucsach = searchsach(lds[i].ListSach,masach);
								if (danhmucsach != NULL)
									break;
							}
							if (danhmucsach != NULL)
							{
								danhmucsach->TrangThai = 0;
								string filename;
								filename = "Sach_DS" + to_string(ISBN) + ".txt";
								updatetrangthaisachformfile(danhmucsach, filename);
							}
							danhmucsach = searchsach(ls_thuvien, masach);
							danhmucsach->TrangThai = 0;
						}
					}
				}
			}
			else
				cout << "Khong ton tai doc gia" << endl;
			break;
		case 8:
			cout << "Nhap ma doc gia: ";
			cin >> madocgia;
			SachDocGiaMuon(t, madocgia);
			break;
		case 9:
			listsachtratre(t);
			break;
		case 10:
			for (MuonTraNode *p = lmt->head; p != NULL; p = p->next)
			{
				if (sach_soluong.count(p->mt.MaSach) > 0)
				{
					std::map<int, int>::iterator it = sach_soluong.find(p->mt.MaSach);
					it->second++;
				}
				else
					sach_soluong[p->mt.MaSach] = 1;
			}
			dst = flip_map(sach_soluong);
			count = 0;
			for (multimap<int, int>::const_reverse_iterator it = dst.rbegin(); it!=dst.rend(); ++it)
			{
				if (count == 10)
					break;
				cout << "Ma sach: "<<it->second << " " << it->first << endl;
				count++;
			}
			break;
		default:
			break;
		}
	}
	system("pause");
}

int menu()
{
	cout << "1.Quan ly doc gia" << endl;
	cout << "2.Danh sach doc gia" << endl;
	cout << "3.Nhap dau sach va ma sach" << endl;
	cout << "4.Danh sach dau sach" << endl;
	cout << "5.Tra cuu sach" << endl;
	cout << "6.Muon sach" << endl;
	cout << "7.Tra sach" << endl;
	cout << "8.Sach doc gia dang muon" << endl;
	cout << "9.Danh sach sach qua han" << endl;
	cout << "10.Muoi sach co so luot muon nhieu nhat" << endl;
	cout << "Lua chon: ";
	int choice;
	cin >> choice;
	return choice;
}
int menu_1()
{
	cout << "1.Them doc gia" << endl;
	cout << "2.Xoa doc gia" << endl;
	cout << "3.Hieu chinh doc gia" << endl;
	cout << "Lua chon: ";
	int choice;
	cin >> choice;
	return choice;
}
int menu_2()
{
	cout << "1.Ma doc gia tang dan" << endl;
	cout << "2.Ten doc gia tang dan" << endl;
	cout << "Lua chon: ";
	int choice;
	cin >> choice;
	return choice;
}

bool checksachnhap(int soluongsach)
{
	if (soluongsach > 3 || soluongsach < 0)
	{
		return false;

	}
	else
		return true;
}
bool checksachtra(int soluongsachtra, int soluongsachdangmuon)
{
	if (soluongsachtra > soluongsachdangmuon)
	{
		return false;
	}
	else
		return true;
}
bool checksachmuon(int soluongsach)
{
	if (soluongsach > 3)
	{
		return false;
	}
	else
		return true;
}
 void getall(Tree t,ListMuonTra *lmt)
{
	if (t != NULL)
	{
		getall(t->left,lmt);
		if (t->dg.ListMuonTra->head != NULL)
		{
			addtaillistmuontra(lmt, t->dg.ListMuonTra->head);
			lmt->tail = t->dg.ListMuonTra->tail;
		}
		getall(t->right, lmt);
	}
}
void outputsach(DanhMucSach dms)
{
	cout << "Ma Sach: " << dms.MaSach << endl;
	string trangthai;
	cout << "Trang thai: ";
	if (dms.TrangThai == 0)
		trangthai = "Muon duoc";
	else if (dms.TrangThai == 1)
		trangthai = "Sach da duoc muon";
	else
		trangthai = "Da thanh ly";
	cout << trangthai << endl;
	cout << "Vi tri: " << dms.ViTri << endl;
}
DauSach *searchdausach(string tensach, DauSach lds[], int soluongsach)
{
	int l = 0;
	int r = soluongsach - 1;
	while (l <= r)
	{
		int m = (l + r) / 2;
		if (lds[m].TenSach == tensach)
			return &lds[m];
		if (lds[m].TenSach > tensach)
			r = m - 1;
		else
			l = m + 1;
	}
	return NULL;
}
void inputdausachfromfile(DauSach lds[], string file,int &element,ListSach * ls_thuvien)
{
	fstream f;
	f.open(file, ios::in);
	string checkEnd;
	while (f >> checkEnd)
	{
		DauSach ds;
		ds.ISBN = stoi(checkEnd.c_str());
		f >> ds.TenSach >> ds.SoTrang >> ds.TacGia >> ds.NamXuatBan >> ds.TheLoai;
		string str = "Sach_DS" + to_string(ds.ISBN) + ".txt";
		ds.ListSach = new ListSach;
		initlistsach(ds.ListSach);
		loadlistsachfromfile(ds.ListSach, str, ls_thuvien);
		lds[element] = ds;
		element++;
	}
	f.close();
}

void sortlistdausachtheoma(DauSach lds[], int length)
{
	for (int i = 0; i < length - 1; i++)
		for (int j = i + 1; j < length; j++)
			if (lds[i].ISBN > lds[j].ISBN)
				swap(lds[i], lds[j]);
}
void sortlistdausachtheoten(DauSach lds[], int length)
{
	for (int i = 0; i < length - 1; i++)
		for (int j = i + 1; j < length; j++)
			if (lds[i].TenSach > lds[j].TenSach)
				swap(lds[i], lds[j]);
}

void outputlistdausach(DauSach lds[], int length)
{
	for (int i = 0; i < length; i++)
	{
		outputdausach(lds[i]);
	}
}
void outputdausach(DauSach ds)
{
	cout << "ISBN: " << ds.ISBN << endl;
	cout << "Ten Sach: " << ds.TenSach << endl;
	cout << "So Trang: " << ds.SoTrang << endl;
	cout << "Tac Gia: " << ds.TacGia << endl;
	cout << "Nam Xuat Ban: " << ds.NamXuatBan << endl;
	cout << "The Loai: " << ds.TheLoai << endl;
}
void sortdocgia(DocGia ldg[], int soluongdocgia)
{
	for (int i = 0; i < soluongdocgia - 1; i++)
		for (int j = i + 1; j < soluongdocgia; j++)
			if ((ldg[i].Ho + ldg[i].Ten) > (ldg[j].Ho + ldg[j].Ten))
				swap(ldg[i], ldg[j]);
}
void outputdocgiaarr(DocGia ldg[], int soluongdocgia)
{
	for (int i = 0; i < soluongdocgia; i++)
		outputdocgia(ldg[i]);
}
void swap(DocGia &a, DocGia &b)
{
	DocGia temp = a;
	a = b;
	b = temp;
}
void removedocgiafromfile(int MaDocGia, string file)
{
	fstream f;
	f.open(file, ios::in | ios::out | ios ::app);
	fstream rem;
	rem.open("temp.txt", ios::in | ios::out | ios::app);
	string checkEnd;
	string madocgia;
	string ho;
	string ten;
	string phai;
	string trangthaithe;
	string line;
	string delline;
	while (!f.eof())
	{
		f >> madocgia;
		if (madocgia == to_string(MaDocGia))
		{
			f >> ho >> ten >> phai >> trangthaithe;
			delline += madocgia + " " + ho + " " + ten + " " + phai + " " + trangthaithe;
			break;
		}
		else
			f >> ho >> ten >> phai >> trangthaithe;
	}
	f.close();
	f.open(file, ios::in | ios::out | ios::app);
	while (!f.eof())
	{
		getline(f, line);
		if (line != delline)
		{
			rem << line << endl;
		}
	}
	f.close();
	rem.close();
	remove("DocGia.txt");
	rename("temp.txt", "DocGia.txt");
}

int countLeapYears(Date d)
{
	int years = d.y;
	if (d.m <= 2)
		years--;

	return years / 4 - years / 100 + years / 400;
}


int getDifference(Date dt1, Date dt2)
{
	long int n1 = dt1.y * 365 + dt1.d;
	for (int i = 0; i < dt1.m - 1; i++)
		n1 += monthDays[i];
	n1 += countLeapYears(dt1);
	long int n2 = dt2.y * 365 + dt2.d;
	for (int i = 0; i < dt2.m - 1; i++)
		n2 += monthDays[i];
	n2 += countLeapYears(dt2);
	return (n2 - n1);
}
void insertionSort(MuonTraNode **head_ref)
{
	// Initialize sorted linked list 
	MuonTraNode *sorted = NULL;

	// Traverse the given linked list and insert every 
	// node to sorted 
	struct MuonTraNode *current = *head_ref;
	while (current != NULL)
	{
		// Store next for next iteration 
		 MuonTraNode *next = current->next;

		// insert current in sorted linked list 
		sortedInsert(&sorted, current);

		// Update current 
		current = next;
	}

	// Update head_ref to point to sorted linked list 
	*head_ref = sorted;
}

void sortedInsert(MuonTraNode** head_ref, MuonTraNode* new_node)
{
	 MuonTraNode* current;
	/* Special case for the head end */
	if (*head_ref == NULL || getDifference((*head_ref)->mt.NgayMuon, (*head_ref)->mt.NgayTra)
		<= getDifference(  new_node->mt.NgayMuon, new_node->mt.NgayTra))
	{
		new_node->next = *head_ref;
		*head_ref = new_node;
	}
	else
	{
		/* Locate the node before the point of insertion */
		current = *head_ref;
		while (current->next != NULL &&
			getDifference(current->next->mt.NgayMuon,current->next->mt.NgayTra) 
			> getDifference(new_node->mt.NgayMuon, new_node->mt.NgayTra))
		{
			current = current->next;
		}
		new_node->next = current->next;
		current->next = new_node;
	}
}
void listsachtratre(Tree t)
{
	if (t != NULL)
	{
		listsachtratre(t->left);
		if (t->dg.ListMuonTra->head != NULL)
		{
			
			insertionSort(&t->dg.ListMuonTra->head);
			for (MuonTraNode *p = t->dg.ListMuonTra->head; p != NULL; p = p->next)
			{
				double diffdate = getDifference(p->mt.NgayMuon, p->mt.NgayTra);
				if (p->mt.TrangThai == 1 && diffdate > THOIGIANMUONSACHTOIDA)
				{
					cout << "Ho ten Doc Gia: " << t->dg.Ho << " " << t->dg.Ten << endl;
					cout << "Danh Sach sach tra tre: " << endl;
					break;
				}
			}
			outputlistsachtratre(t->dg.ListMuonTra);
		}
		listsachtratre(t->right);
	}
}
void outputlistsachtratre(ListMuonTra *lmt)
{

	for (MuonTraNode *p = lmt->head; p != NULL; p = p->next)
	{
		double diffdate = getDifference(p->mt.NgayMuon, p->mt.NgayTra);
		if (p->mt.TrangThai == 1 && diffdate > THOIGIANMUONSACHTOIDA)
		{
			outputsachtratre(p->mt);
			cout << "So ngay tre: " << diffdate << endl;
		}
	}
}

MuonTra * searchsachmuon(ListMuonTra *lmt, int MaSach)
{
	for (MuonTraNode *p = lmt->head; p != NULL; p = p->next)
	{
		if (p->mt.MaSach == MaSach && p->mt.TrangThai == 0)
			return &p->mt;
	}
	return NULL;
}
int SachDocGiaMuon(Tree t, int MaDocGia)
{
	int count = 0;
	DocGia *dg = searchdocgia(t, MaDocGia);
	if ( dg == NULL)
		cout << "Khong ton tai ma doc gia" << endl;
	else
	{
		if (dg->ListMuonTra->head == NULL)
			cout << "Doc gia chua muon sach nao" << endl;
		else

		{
			for (MuonTraNode *p = dg->ListMuonTra->head; p != NULL; p = p->next)
				if (p->mt.TrangThai == 0)
				{
					outputsachmuon(p->mt);
					count++;
				}
		}
	}
	return count;
}
void outputmuontra(ListMuonTra *lmt)
{
	for (MuonTraNode *p = lmt->head; p != NULL; p = p->next)
	{
			outputsachmuon(p->mt);
	}
}
void outputsachtratre(MuonTra mt)
{
	cout << "Ma Sach: " << mt.MaSach << endl;
	cout << "Ngay Muon: ";
	outputdate(mt.NgayMuon);
	cout << "Ngay Tra: ";
	outputdate(mt.NgayTra);

}
void outputsachmuon(MuonTra mt)
{
	cout << "Ma Sach: " << mt.MaSach << endl;
	cout << "Ngay Muon: ";
	outputdate(mt.NgayMuon);
}
void outputdate(Date date)
{
	cout << date.d << "/" << date.m << "/" << date.y << endl;
}


void LNR(Tree t)
{
	if (t != NULL)
	{
		LNR(t->left);
		outputdocgia(t->dg);
		LNR(t->right);
	}

}
void outputdocgia(DocGia dg)
{
	cout << "Ma doc gia: " << dg.MaDocGia << endl;
	cout << "Ho ten doc gia: " << dg.Ho << " " << dg.Ten << endl;
	cout << "Phai doc gia: " << dg.Phai << endl;
	cout << "Trang thai the doc gia: " << dg.TrangThaiThe << endl;
	cout << "========================" << endl;
}
void inittree(Tree &t)
{
	t = NULL;
}
DauSach *searchISBN(DauSach lds[], int ISBN,int soluongdausach)
{
	int l = 0;
	int r = soluongdausach - 1;
	while (l <= r)
	{
		int m = (l + r) / 2;
		if (lds[m].ISBN == ISBN)
			return &lds[m];
		if (lds[m].ISBN > ISBN)
			r = m - 1;
		else
			l = m + 1;
	}
	return NULL;
}
DocGia *searchdocgia(Tree t, int MaDocGia)
{
	if (t != NULL) {
		if (t->dg.MaDocGia == MaDocGia)
		{
			return &t->dg;
		}
		else
		{
			if (MaDocGia > t->dg.MaDocGia)
				searchdocgia(t->right, MaDocGia);
			else
				searchdocgia(t->left, MaDocGia);
		}
	}
	else
	return NULL;
}
void inputdocgiafromfiletoarray(DocGia ldg[], string file,int &element)
{
	fstream f;
	f.open(file, ios::in);
	string checkEnd;
	while (f >> checkEnd)
	{
		DocGia dg;
		dg.MaDocGia = stoi(checkEnd.c_str());
		f >> dg.Ho >> dg.Ten >> dg.Phai >> dg.TrangThaiThe;
		string str = "SachMuon_DG" + to_string(dg.MaDocGia) + ".txt";
		dg.ListMuonTra = new ListMuonTra;
		initlistsachmuon(dg.ListMuonTra);
		loadsachmuonfromfile(dg.ListMuonTra, str);
		ldg[element] = dg;
		element++;
	}
	f.close();
}
void inputdocgiafromfile(Tree &t, string file,ListMuonTra *lmt)
{
	fstream f;
	f.open(file, ios::in);
	string checkEnd;
	while (f >> checkEnd)
	{
		DocGia dg;
		dg.MaDocGia = stoi(checkEnd.c_str());
		f >> dg.Ho>> dg.Ten >> dg.Phai >> dg.TrangThaiThe;
		string str = "SachMuon_DG" + to_string(dg.MaDocGia)+".txt";
		dg.ListMuonTra = new ListMuonTra;
		initlistsachmuon(dg.ListMuonTra);
		loadsachmuonfromfile(lmt, str);
		loadsachmuonfromfile(dg.ListMuonTra, str);
		InsertTree(t, dg);
	}
	f.close();
}
void writefilesachdausach(DanhMucSach dms, string file)
{
	fstream f;
	f.open(file, ios::app);
	f << endl << dms.MaSach << " " << dms.TrangThai << " " << dms.ViTri;
	f.close();
}
void writefiledausach(DauSach ds, string file)
{
	fstream f;
	f.open(file, ios::app);
	f << endl << ds.ISBN << " " << ds.TenSach << " " << ds.SoTrang << " " << ds.TacGia << " " << ds.NamXuatBan << " " << ds.TheLoai;
	f.close();
}
void writefilemuontra(MuonTra mt, string file)
{
	fstream f;
	f.open(file, ios::app);
	f << endl << mt.MaSach << " " << mt.NgayMuon.d << " " << mt.NgayMuon.m << " " << mt.NgayMuon.y << " "
		<< mt.NgayTra.d << " " << mt.NgayTra.m << " " << mt.NgayTra.y << " "  << mt.TrangThai;
	f.close();
}
void writefiledocgia(DocGia dg, string file)
{
	fstream f;
	f.open(file, ios::app);
	f << endl<< dg.MaDocGia << " " << dg.Ho << " " << dg.Ten << " " << dg.Phai << " "
		<< dg.TrangThaiThe;
	f.close();
}
void loadlistsachfromfile(ListSach *ls, string file,ListSach *ls_thuvien)
{
	fstream f;
	f.open(file, ios::in);
	string checkEnd;
	while (f >> checkEnd)
	{
		DanhMucSach dms;
		dms.MaSach = stoi(checkEnd.c_str());
		f >> dms.TrangThai >> dms.ViTri;
		SachNode *p = getNodeSach(dms);
		SachNode *t = getNodeSach(dms);
		addheadlistsach(ls, p);
		addheadlistsach(ls_thuvien, t);
	}
	f.close();
}
void loadsachmuonfromfile(ListMuonTra *lmt,string file)
{
	fstream f;
	f.open(file, ios::in);
	string checkEnd;
	while (f >> checkEnd)
	{
		MuonTra mt;
		mt.MaSach = stoi(checkEnd.c_str());
		f >> mt.NgayMuon.d >> mt.NgayMuon.m>> mt.NgayMuon.y;
		f >> mt.NgayTra.d >> mt.NgayTra.m >> mt.NgayTra.y;
		f >> mt.TrangThai;
		MuonTraNode *p = getNodeMuonTra(mt);
		addheadlistmuontra(lmt, p);
	}
	f.close();
}
void initlistsach(ListSach *ls)
{
	ls->head = NULL;
	ls->tail = NULL;
}
void initlistsachmuon(ListMuonTra *lmt)
{
	lmt->head = NULL;
	lmt->tail = NULL;
}
SachNode * getNodeSach(DanhMucSach dms)
{
	SachNode *p = new SachNode;
	if (p == NULL)
		return NULL;
	p->sach.MaSach = dms.MaSach;
	p->sach.TrangThai = dms.TrangThai;
	p->sach.ViTri = dms.ViTri;
	p->next = NULL;
	return p;
}
MuonTraNode * getNodeMuonTra(MuonTra mt)
{
	MuonTraNode *p = new MuonTraNode;
	if (p == NULL)
		return NULL;
	p->mt.MaSach = mt.MaSach;
	p->mt.NgayMuon = mt.NgayMuon;
	p->mt.NgayTra = mt.NgayTra;
	p->mt.TrangThai = mt.TrangThai;
	p->next = NULL;
	return p;
}
void addheadlistsach(ListSach *ls, SachNode *p)
{
	if (ls->head == NULL)
	{
		ls->head = ls->tail = p;
	}
	else
	{
		p->next = ls->head;
		ls->head = p;
	}
}
void addtaillistmuontra(ListMuonTra *lmt, MuonTraNode *p)
{
	if (lmt->head == NULL)
	{
		lmt->head = lmt->tail = p;
	}
	else
	{
		lmt->tail->next = p;
		lmt->tail = p;
	}
}
void addheadlistmuontra(ListMuonTra *lmt, MuonTraNode *p)
{
	if (lmt->head == NULL)
	{
		lmt->head = lmt->tail = p;
	}
	else
	{
		p->next = lmt->head;
		lmt->head = p;
	}
}
void inputlistsach(ListSach *ls_dausach,ListSach *ls_thuvien,int ISBN)
{
	cout << "So luong sach can them: ";
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		DanhMucSach dms;
		inputsach(dms, ls_thuvien);
		SachNode *p = getNodeSach(dms);
		SachNode *t = getNodeSach(dms);
		addheadlistsach(ls_dausach, p);
		addheadlistsach(ls_thuvien, t);
		string DauSach_Sach;
		DauSach_Sach = "Sach_DS" + to_string(ISBN) + ".txt";
		writefilesachdausach(dms, DauSach_Sach);
	}
}
void inputsach(DanhMucSach &dms, ListSach *ls)
{
	do
	{
		cout << "Ma sach: ";
		dms.MaSach = rand() % 1000000;
	} while (searchsach(ls,dms.MaSach ) != NULL);
	cout << dms.MaSach << endl;
	dms.TrangThai = 0;
	cout << "Trang thai: " << dms.TrangThai << endl;
	cout << "Nhap vi tri: ";
	cin >> dms.ViTri;
}
DanhMucSach *searchsach(ListSach *ls, int MaSach)
{
	for (SachNode*p = ls->head; p != NULL; p = p->next)
		if (p->sach.MaSach == MaSach)
			return &p->sach;
	return NULL;
}
void inputdausach(DauSach lds[], DauSach &ds, int &soluongdausach, ListSach *ls)
{
	do
	{
		cout << "Nhap ISBN: ";
		cin >> ds.ISBN;
		DauSach*p;
		if (( p = searchISBN(lds, ds.ISBN, soluongdausach)) != NULL)
		{
			cout << "ISBN da ton tai" << endl;
			cout << "1.Nhap ISBN moi" << endl;
			cout << "2.Them sach" << endl;
			cout << "Lua chon: ";
			int choice;
			cin >> choice;
			if (choice == 2)
			{
				inputlistsach(p->ListSach, ls,ds.ISBN);
				return;
			}
		}
	} while(searchISBN(lds, ds.ISBN, soluongdausach) != NULL);

	cout << "Nhap ten sach: ";
	cin >> ds.TenSach;
	cout << "Nhap ten tac gia: ";
	cin >> ds.TacGia;
	cout << "Nhap so trang: ";
	cin >> ds.SoTrang;
	cout << "Nhap nam xuat ban: ";
	cin >> ds.NamXuatBan;
	cout << "Nhap the loai: ";
	cin >> ds.TheLoai;
	ds.ListSach = new ListSach;
	initlistsach(ds.ListSach);
	inputlistsach(ds.ListSach,ls,ds.ISBN);
	writefiledausach(ds, "DauSach.txt");
	lds[soluongdausach++] = ds;
}
void inputsachmuon(MuonTra &mt, ListSach*ls, ListMuonTra *lmt,int MaDocGia,DauSach ds[],int soluongdausach,ListMuonTra * lmt_tatca)
{
	DanhMucSach *dms;
	DanhMucSach * dms_ds = NULL;
	int ISBN;
	do
	{
		cout << "Nhap ma sach: ";
		cin >> mt.MaSach;
		if (((dms = searchsach(ls, mt.MaSach)) == NULL))
			cout << "Khong ton tai sach" << endl;
		else if (dms->TrangThai == 1 || dms->TrangThai == 2)
		{
			cout << "Sach da duoc muon hoac thanh ly" << endl;
			dms = NULL;
		}
	} while (dms  == NULL);

	{
		cout << "Nhap ngay muon: ";
		cin >> mt.NgayMuon.d >> mt.NgayMuon.m >> mt.NgayMuon.y;
		while (!checkdate(mt.NgayMuon) && getDifference(today, mt.NgayMuon) < 0)
		{
			cout << "Ngay khong hop le" << endl;
			cout << "Nhap ngay muon: ";
			cin >> mt.NgayMuon.d >> mt.NgayMuon.m >> mt.NgayMuon.y;
		}
		mt.TrangThai = 0;
		mt.NgayTra.d = mt.NgayMuon.d - 1;
		mt.NgayTra.m = mt.NgayMuon.m;
		mt.NgayTra.y = mt.NgayMuon.y;
		MuonTraNode *p = getNodeMuonTra(mt);
		addheadlistmuontra(lmt, p);
		MuonTraNode *t = getNodeMuonTra(mt);
		addheadlistmuontra(lmt_tatca, t);
		dms->TrangThai = 1;
		for (int i = 0; i < soluongdausach;i++)
		{
			ISBN = ds[i].ISBN;
			dms_ds =searchsach(ds[i].ListSach, mt.MaSach);
			if (dms_ds != NULL)
				break;
		}
		if (dms_ds != NULL)
		{
			dms_ds->TrangThai = 1;
			string filename;
			filename = "Sach_DS" + to_string(ISBN) + ".txt";
			updatetrangthaisachformfile(dms_ds, filename);
		}
		string filename;
		filename = "SachMuon_DG" + to_string(MaDocGia) + ".txt";
		writefilemuontra(mt, filename);
	}

}
void updatemuontrafromfile(MuonTra *mt, string file)
{
	fstream f;
	fstream rem;
	f.open(file, ios::in | ios::out | ios::app);
	rem.open("temp.txt", ios::in | ios::out | ios::app);
	string masach;
	string line;
	string delline;
	Date muon;
	Date tra;
	string trangthai;
	while (!f.eof())
	{
		f >> masach >> muon.d >> muon.m >> muon.y >> tra.d >> tra.m >> tra.y >> trangthai;
		if (masach == to_string(mt->MaSach) && getDifference(mt->NgayMuon, muon) == 0)
		{
			delline = masach + " " + to_string(muon.d) + " " + to_string(muon.m) + " "
				+ to_string(muon.y) + " " + to_string(tra.d) + " " + to_string(tra.m) + " "
				+ to_string(tra.y) + " " + trangthai;
			break;
		}
	}
	f.close();
	f.open(file, ios::in | ios::out | ios::app);
	while (!f.eof())
	{
		getline(f, line);
		if (line != delline)
		{
			rem << line << endl;
		}
	}
	rem << mt->MaSach << " " << mt->NgayMuon.d << " " << mt->NgayMuon.m <<
		" " << mt->NgayMuon.y << " " << mt->NgayTra.d << " " << mt->NgayTra.m <<
		" " << mt->NgayTra.y << " " << mt->TrangThai;
	f.close();
	rem.close();
	int csize = file.size() + 1;
	char * carr = new char[csize];
	file.copy(carr, csize);
	carr[csize - 1] = '\0';
	remove(carr);
	rename("temp.txt", carr);


}
void updatetrangthaisachformfile(DanhMucSach *dms, string file)
{
	fstream f;
	fstream rem;
	f.open(file, ios::in | ios::out | ios::app);
	rem.open("temp.txt", ios::in | ios::out | ios::app);
	string masach;
	string trangthai;
	string vitri;
	string line;
	string delline;
	while (!f.eof())
	{
		f >> masach >> trangthai >> vitri;
		if (masach == to_string(dms->MaSach))
		{
			delline = masach + " " + trangthai + " " + vitri;
			break;
		}
	}
	f.close();
	f.open(file, ios::in | ios::out | ios::app);
	while (!f.eof())
	{
		getline(f, line);
		if (line != delline)
		{
			rem << line << endl;
		}
	}
	rem << dms->MaSach << " " << dms->TrangThai << " " << dms->ViTri << endl;
	f.close();
	rem.close();
	int csize = file.size() + 1;
	char * carr = new char[csize];
	file.copy(carr, csize);
	carr[csize - 1] = '\0';
	remove(carr);
	rename("temp.txt", carr);


}
bool checkdate(Date date)
{
	if (date.d > monthDays[date.m + 1] || date.d < 0)
		return false;
	else
	if (date.y % 4 != 0 && date.d == 29 && date.m == 2)
		return false;
	else return true;

}
void inputdocgia2(Tree t, DocGia &dg)
{
	DocGia docgia = dg;
	cout << "Ma doc gia: ";
	cout << dg.MaDocGia << endl;
	cout << "Nhap ho doc gia: ";
	cin.ignore();
	getline(cin, dg.Ho);
	cout << "Nhap ten doc gia: ";
	getline(cin, dg.Ten);
	do
	{
		cout << "Nhap phai doc gia: ";
		getline(cin, dg.Phai);
	} while (dg.Phai != "Nam" && dg.Phai != "Nu" &&dg.Phai != "");

	do
	{
		cout << "Nhap trang thai the doc gia: ";
		cin >> dg.TrangThaiThe;
	} while (dg.TrangThaiThe > 1 || dg.TrangThaiThe < 0);
	if (dg.Ho == "");
	dg.Ho = docgia.Ho;
	if (dg.Ten == "")
		dg.Ten = docgia.Ten;
	if (dg.Phai == "")
		dg.Phai = docgia.Phai;
	//if (dg.TrangThaiThe == "")
	//	dg.TrangThaiThe = docgia.TrangThaiThe;
}
void inputdocgia(Tree t,DocGia &dg)
{	
	do
	{
		cout << "Ma doc gia: ";
		dg.MaDocGia = rand() % 1000000;
	} while (searchdocgia(t, dg.MaDocGia) != NULL);
	cout << dg.MaDocGia << endl;
	cout << "Nhap ho doc gia: ";
	cin.ignore();
	getline(cin, dg.Ho);
	cout << "Nhap ten doc gia: ";
	getline(cin, dg.Ten);
	do
	{
		cout << "Nhap phai doc gia: ";
		getline(cin, dg.Phai);
	} while (dg.Phai != "Nam" && dg.Phai != "Nu");
	
	do
	{
		cout << "Nhap trang thai the doc gia: ";
		cin >> dg.TrangThaiThe;
	} while (dg.TrangThaiThe > 1 || dg.TrangThaiThe < 0);
	dg.ListMuonTra = new ListMuonTra;
	initlistsachmuon(dg.ListMuonTra);
}
int updatedocgia(Tree &t,  int x,Tree p)
{
	if (t != NULL) {
		if (t->dg.MaDocGia == x)
		{
			removedocgiafromfile(x, "DocGia.txt");
			inputdocgia2(p, t->dg);
			writefiledocgia(t->dg, "DocGia.txt");
			cout << "Hieu chinh doc gia thanh cong" << endl;
			return 1;
		}
		else
		{
			if (x > t->dg.MaDocGia)
				updatedocgia(t->right, x, p);
			else
				updatedocgia(t->left, x, p);
		}
	}
	else
	{
		cout << "Hieu chinh doc gia khong thanh cong" << endl;
		return 0;
	}
}
int removedocgia(Tree &t, int MaDocGia)
{
	if (t != NULL) {
		if (t->dg.MaDocGia == MaDocGia)
		{
			Tnode *p = t;
			if (t->left == NULL)
				t = t->right;
			else if (t->right == NULL)
				t = t->left;
			else searchstandfor(p, t->right);
			delete p;
			cout << "Xoa thanh cong" << endl;
			return 1;
		}
		else
		{
			if (MaDocGia > t->dg.MaDocGia)
				removedocgia(t->right, MaDocGia);
			else
				removedocgia(t->left, MaDocGia);
		}
	}
	else
	{
		cout << "Khong ton tai ma doc gia" << endl;
		return 0;
	}
}
void searchstandfor(Tree &p, Tree &t)
{
	if (t->left != NULL)
		searchstandfor(p, t->left);
	else
	{
		p->dg = t->dg;
		p = t;
		t = t->right;
	}
}
int InsertTree(Tree &t, DocGia dg)
{
	if (t != NULL)
	{
		if (dg.MaDocGia == t->dg.MaDocGia)
			return 0;
		else
			if (dg.MaDocGia > t->dg.MaDocGia)
				InsertTree(t->right, dg);
			else
				InsertTree(t->left, dg);
	}
	else
	{
		t = CreateTnode(dg);
		if (t == NULL)
			return -1;
		return 1;
	}
}
Tnode *CreateTnode(DocGia dg)
{
	Tnode *p = new Tnode;
	if (p == NULL)
		return NULL;
	p->left = NULL;
	p->right = NULL;
	p->dg = dg;
	return p;
}
