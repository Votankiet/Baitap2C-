#include <iostream>
#include <vector>

using namespace std;

class DonThuc
{
public:
    double heSo;
    int soMu;
public:
    DonThuc(double heSo, double soMu) {
        this->heSo = heSo;
        this->soMu = soMu;
    }

    //Định nghĩa toán tử *
    DonThuc operator*(const DonThuc &other) {
        return DonThuc(this->heSo * other.heSo, this->soMu + other.soMu);
    }

    DonThuc tinhDaoHam() {
        return DonThuc(this->heSo * this->soMu, (this->soMu - 1) < 0 ? 0 : (this->soMu - 1));
    }

    DonThuc tinhDaoHamCapK(int k) {
        DonThuc temp = DonThuc(heSo, soMu);

        for(int i = 1; i <= k; i++) temp = temp.tinhDaoHam();

        return temp;
    }

    //định nghĩa toán tử /
    DonThuc operator/(const DonThuc &other) {
        return DonThuc(this->heSo / other.heSo, this->soMu - other.soMu);
    }

    double tinhGiaTriTaix0(double x0) {
        double res = 1;
        for(int i = 1; i <= soMu; i++) {
            res *= x0;
        }
        return heSo * res;
    }
};

class DaThuc
{
private:
    vector<DonThuc> daThuc;
public:
    DaThuc(vector<DonThuc> &daThuc) {
        vector<DonThuc> temp(daThuc.begin(), daThuc.end());
        this->daThuc = temp;
    }
    void inDaThuc() {
        for(DonThuc e : daThuc) {
            cout<< e.heSo << "x^" << e.soMu << " ";
        }
        cout << endl;
    }
    // định nghĩa toán tử +
    DaThuc operator+(const DaThuc &other) {
        vector<DonThuc> res;
        int asize = daThuc.size();
        int bsize = other.daThuc.size();
        int i = asize - 1, j = bsize - 1;
        
        while(i >= 0 && j >= 0) {
            if(daThuc[i].soMu == other.daThuc[j].soMu) {
                res.push_back(DonThuc(daThuc[i].heSo + other.daThuc[j].heSo, daThuc[i].soMu));
            }
            i--;
            j--;
        }

        while(i >= 0) {
            res.push_back(DonThuc(daThuc[i].heSo, daThuc[i].soMu));
            i--;
        }
        while(j >= 0) {
            res.push_back(DonThuc(other.daThuc[j].heSo, other.daThuc[j].soMu));
            j--;
        }
        return DaThuc(res);
    }
    //Định nghĩa toán tử -
    DaThuc operator-(const DaThuc &other) {
        vector<DonThuc> res;
        int asize = daThuc.size();
        int bsize = other.daThuc.size();
        int i = asize - 1, j = bsize - 1;
        
        while(i >= 0 && j >= 0) {
            if(daThuc[i].soMu == other.daThuc[j].soMu) {
                res.push_back(DonThuc(daThuc[i].heSo - other.daThuc[j].heSo, daThuc[i].soMu));
            }
            i--;
            j--;
        }

        while(i >= 0) {
            res.push_back(DonThuc(daThuc[i].heSo, daThuc[i].soMu));
            i--;
        }
        while(j >= 0) {
            res.push_back(DonThuc(other.daThuc[j].heSo, other.daThuc[j].soMu));
            j--;
        }
        return DaThuc(res);
    }
    //Định nghĩa toán tử *
    DaThuc operator*(const DaThuc &other) {
        vector<DonThuc> res;
        int asize = daThuc.size();
        int bsize = other.daThuc.size();

        for(int i = 0; i < asize; i++) {
            for(int j = 0; j < bsize; j++) {
                res.push_back(daThuc[i] * other.daThuc[j]);
            }
        }
        return DaThuc(res);
    }
    //tính đạo hàm cấp 1
    DaThuc tinhDaoHam() {
        vector<DonThuc> res;
        for(DonThuc e : daThuc) {
            res.push_back(e.tinhDaoHam());
        }
        return DaThuc(res);
    }

    DaThuc tinhDaoHamBacK(int k) {
        DaThuc temp = DaThuc(daThuc);

        for(int i = 0; i < k; i++) temp = temp.tinhDaoHam();
        return temp;
    }
    double tinhGiaTriTaix0(double x0) {
        double temp = 0;
        for(DonThuc e : daThuc) {
            temp += e.tinhGiaTriTaix0(x0);
        }
        return temp;
    }

    double nghiemTrongKhoang(double a, double b) {
        DaThuc f = DaThuc(daThuc);
        DaThuc d = f.tinhDaoHam();
        DaThuc d2 = d.tinhDaoHam();
        double res;

        if(f.tinhGiaTriTaix0(a) * d2.tinhGiaTriTaix0(a) > 0) res = a;
        else res = b;
        for(int i = 0; i < 10; i++) res = (res - f.tinhGiaTriTaix0(res) / d.tinhGiaTriTaix0(res));

        return res;
    }
};


int main() {
    vector<DonThuc> d1{DonThuc(1, 2), DonThuc(2, 1), DonThuc(-1, 0)};
    vector<DonThuc> d2{DonThuc(2, 1), DonThuc(2, 0)};

    //Tạo 2 đa thức a và b
    DaThuc a = DaThuc(d1);
    DaThuc b = DaThuc(d2);

    //Tính tổng 2 đa thức
    DaThuc res = a + b;
    res.inDaThuc();

    //Tính hiệu 2 đa thức
    res = a - b;
    res.inDaThuc();

    //Tính tích 2 đa thức
    res = a * b;
    res.inDaThuc();

    //Tính đạo hàm bậc 1;
    res = res.tinhDaoHam();
    res.inDaThuc();

    //tính đạo hàm bậc k;
    res = a.tinhDaoHamBacK(2);
    res.inDaThuc();

    //tính giá trị tại x0;
    res = a;
    cout << res.tinhGiaTriTaix0(2) << endl;
    //tính nghiệm trong khoảng a b băng công thức Newton
    cout << res.nghiemTrongKhoang(0, 1);
    return 0;
}