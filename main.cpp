#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

class Pasien0001 {
    private:
        std::string nama;
        std::string keluhan;
        double biayaKonsultasi;
    public:
        // constructor
        Pasien0001(std::string nama, std::string keluhan, double biayaKonsultasi) {
            setNama(nama);
            setKeluhan(keluhan);
            setBiayaKonsultasi(biayaKonsultasi);
        }

        // setter dan getter dari atribut nama
        std::string getNama() const {return nama;} // mengambil nilai dari nama
        void setNama(std::string nama) {
            if (nama.empty()) {
                throw std::invalid_argument("Nama tidak boleh kosong");
            }
            this->nama = nama;
        }

        // setter dan getter dari atribut keluhan
        std::string getKeluhan() const {return keluhan;} // mengambil nilai dari keluhan
        void setKeluhan(std::string keluhan) {
            if (keluhan.empty()) {
                throw std::invalid_argument("Keluhan tidak boleh kosong");
            }
            this->keluhan = keluhan;
        }

        // setter dan getter dari atribut biayaKonsultasi
        double getBiayaKonsultasi() const {return biayaKonsultasi;} // mengambiil nilai dari biayaKonsultasi
        void setBiayaKonsultasi(double biayaKonsultasi) {
            if (biayaKonsultasi <= 0) {
                throw std::invalid_argument("Biaya Konsultasi tidak valid");
            }
            this->biayaKonsultasi = biayaKonsultasi;
        }
};

class Klinik {
    private:
        std::string namaKlinik;
        std::vector<Pasien0001> daftarPasien;
    public:
        // constructor
        Klinik(std::string namaKlinik) {
            setNamaKlinik(namaKlinik);
        }

        // setter dan getter dari atribut namaKlinik
        std::string getNamaKlinik() const {return namaKlinik;} // mengambil nilai dari namaKlinik
        void setNamaKlinik(std::string namaKlinik) {
            if (namaKlinik.empty()) {
                throw std::invalid_argument("Nama klinik tidak boleh kosong");
            }
            this->namaKlinik = namaKlinik;
        }

        // method tambah pasien
        void tambahPasien(const Pasien0001& pasien) {
            daftarPasien.push_back(pasien);
        }

        // method perhitungan total biaya
        double totalBiaya() const {
            double total = 0;

            for (const Pasien0001& pasien : daftarPasien) {
                total += pasien.getBiayaKonsultasi();
            }
            return total; 
        }

        // method untuk menampilkan daftar pasien
        void cetakDaftarPasien() const {
            std::cout << "Klinik: " << namaKlinik << "\n";
            for (const Pasien0001& p : daftarPasien) {
                std::cout << "- " << p.getNama() << " | keluhan : " << p.getKeluhan() << " | Biaya: Rp" << p.getBiayaKonsultasi() << "\n";
            } 
        }
};

int main() {
    Klinik klinik("Klinik Sehat");

    Pasien0001 p1("Renal", "Pusing", 12000);
    Pasien0001 p2("Budi", "Pilek", 20000);

    klinik.tambahPasien(p1);
    klinik.tambahPasien(p2);

    klinik.cetakDaftarPasien();
    std::cout << "Total biaya: Rp" << klinik.totalBiaya() << "\n";

    std::cout << "\nUji Validasi: " << "\n";

    auto uji = [](auto aksi) {
        try {
            aksi();

            std::cout << "Gagal : validasi tidak berjalan, dan error" << "\n"; 
        } catch (const std::invalid_argument& e) {
            std::cout << "Validasi: " << e.what() << "\n";
        }
    };

    uji([&] { p2.setBiayaKonsultasi(-500); });  
    uji([&] { p2.setNama(""); });              
    uji([&] { p2.setKeluhan(""); });           
    uji([&] { klinik.setNamaKlinik(""); });     
    uji([&] { Pasien0001 x("", "Flu", 1000); }); 
    return 0;
}

