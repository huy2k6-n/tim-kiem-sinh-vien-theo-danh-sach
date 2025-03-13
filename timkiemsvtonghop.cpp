#include <bits/stdc++.h>
using namespace std;

struct SinhVien {
    string maSV;     
    string hoTen; 
    int namSinh;    
    float diemTB;   
};

void docDuLieuTuFile(const string& filename, SinhVien sinhVien[], int& soLuong) {
    ifstream inFile(filename);
    if (!inFile) {
        cout << "Khong the mo file!" << endl;
        return;
    }

    soLuong = 0;
    while (inFile >> sinhVien[soLuong].maSV) {
        inFile.ignore(); 
        getline(inFile, sinhVien[soLuong].hoTen);
        inFile >> sinhVien[soLuong].namSinh >> sinhVien[soLuong].diemTB;
        soLuong++;
    }

    inFile.close();
}

int timKiemTuyenTinh(const SinhVien sinhVien[], int soLuong, const string& maSV) {
    for (int i = 0; i < soLuong; ++i) {
        if (sinhVien[i].maSV == maSV) {
            return i; 
        }
    }
    return -1; 
}

int timKiemNhiPhan(SinhVien sinhVien[], int soLuong, const string& maSV) {
    int trai = 0;
    int phai = soLuong - 1;

    while (trai <= phai) {
        int giua = trai + (phai - trai) / 2;
        if (sinhVien[giua].maSV == maSV) {
            return giua; 
        }
        if (sinhVien[giua].maSV < maSV) {
            trai = giua + 1;
        } else {
            phai = giua - 1;
        }
    }
    return -1;
}

int timKiemNhiPhanDeQuy(SinhVien sinhVien[], int trai, int phai, const string& maSV) {
    if (trai > phai) {
        return -1; // Không tìm thấy
    }

    int giua = trai + (phai - trai) / 2;
    if (sinhVien[giua].maSV == maSV) {
        return giua; 
    } else if (sinhVien[giua].maSV < maSV) {
        return timKiemNhiPhanDeQuy(sinhVien, giua + 1, phai, maSV);
    } else {
        return timKiemNhiPhanDeQuy(sinhVien, trai, giua - 1, maSV);
    }
}

struct Nut {
    SinhVien sinhVien;
    Nut* trai;
    Nut* phai;
};

void themNut(Nut*& goc, SinhVien sv) {
    if (goc == nullptr) {
    } else if (sv.maSV < goc->sinhVien.maSV) {
        themNut(goc->trai, sv);
    } else {
        themNut(goc->phai, sv);
    }
}

Nut* timNut(Nut* goc, const string& maSV) {
    if (goc == nullptr || goc->sinhVien.maSV == maSV) {
        return goc;
    }
    if (maSV < goc->sinhVien.maSV) {
        return timNut(goc->trai, maSV);
    }
    return timNut(goc->phai, maSV);
}

void hienThiSinhVien(const SinhVien& sv) {
    cout << "Ma SV: " << sv.maSV << ", Ho ten: " << sv.hoTen 
         << ", Nam sinh: " << sv.namSinh << ", Diem TB: " << sv.diemTB << endl;
}

void hienThiDanhSach(const SinhVien sinhVien[], int soLuong) {
    cout << "Danh sach sinh vien:" << endl;
    for (int i = 0; i < soLuong; ++i) {
        hienThiSinhVien(sinhVien[i]);
    }
}

int main() {
    SinhVien sinhVien[10]; 
    int soLuong = 0;        

    string filename = "sinhvien.txt";
    docDuLieuTuFile(filename, sinhVien, soLuong);

    int luaChon; 

    do {
        cout << "\n=== MENU ===" << endl;
        cout << "1. Tim kiem sinh vien theo ma SV (Tuyen Tinh)" << endl;
        cout << "2. Tim kiem sinh vien theo ma SV (Nhi Phan)" << endl;
        cout << "3. Tim kiem sinh vien theo ma SV (Nhi Phan De Quy)" << endl;
        cout << "4. Tim kiem sinh vien theo ma SV (Cay Nhi Phan)" << endl;
        cout << "5. Hien thi danh sach sinh vien" << endl;
        cout << "6. Thoat" << endl;
        cout << "Nhap lua chon: ";
        cin >> luaChon;

        switch (luaChon) {
            case 1: {
                string maSVTimKiem;
                cout << "Nhap ma sinh vien can tim: ";
                cin >> maSVTimKiem;
                int index = timKiemTuyenTinh(sinhVien, soLuong, maSVTimKiem);
                if (index != -1) {
                    cout << "Tim thay sinh vien (Tuyen Tinh): ";
                    hienThiSinhVien(sinhVien[index]);
                } else {
                    cout << "Khong tim thay sinh vien." << endl;
                }
                break;
            }
            case 2: {
                string maSVTimKiem;
                cout << "Nhap ma sinh vien can tim: ";
                cin >> maSVTimKiem;
                sort(sinhVien, sinhVien + soLuong, [](const SinhVien& a, const SinhVien& b) {
                    return a.maSV < b.maSV;
                });
                int index = timKiemNhiPhan(sinhVien, soLuong, maSVTimKiem);
                if (index != -1) {
                    cout << "Tim thay sinh vien (Nhi Phan): ";
                    hienThiSinhVien(sinhVien[index]);
                } else {
                    cout << "Khong tim thay sinh vien." << endl;
                }
                break;
            }
            case 3: {
                string maSVTimKiem;
                cout << "Nhap ma sinh vien can tim: ";
                cin >> maSVTimKiem;
                sort(sinhVien, sinhVien + soLuong, [](const SinhVien& a, const SinhVien& b) {
                    return a.maSV < b.maSV;
                });
                int index = timKiemNhiPhanDeQuy(sinhVien, 0, soLuong - 1, maSVTimKiem);
                if (index != -1) {
                    cout << "Tim thay sinh vien (Nhi Phan De Quy): ";
                    hienThiSinhVien(sinhVien[index]);
                } else {
                    cout << "Khong tim thay sinh vien." << endl;
                }
                break;
            }
            case 4: {
                string maSVTimKiem;
                cout << "Nhap ma sinh vien can tim: ";
                cin >> maSVTimKiem;
                Nut* goc = nullptr;
                for (int i = 0; i < soLuong; ++i) {
                    themNut(goc, sinhVien[i]);
                }
                Nut* nutTimThay = timNut(goc, maSVTimKiem);
                if (nutTimThay) {
                    cout << "Tim thay sinh vien (Cay Nhi Phan): ";
                    hienThiSinhVien(nutTimThay->sinhVien);
                } else {
                    cout << "Khong tim thay sinh vien." << endl;
                }
                break;
            }
            case 5:
                hienThiDanhSach(sinhVien, soLuong);
                break;
            case 6:
                cout << "Thoat chuong trinh." << endl;
                break;
            default:
                cout << "Lua chon khong hop le. Vui long chon lai." << endl;
        }
    } while (luaChon != 6);

    return 0;
}