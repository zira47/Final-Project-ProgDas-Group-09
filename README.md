# Sistem Manajemen Gaji Layak Berbasis SDG 8

Program ini merupakan sistem manajemen dan evaluasi kelayakan upah karyawan berbasis bahasa C yang mengacu pada Sustainable Development Goals (SDG) Goal 8: **Decent Work and Economic Growth**.

Sistem dapat menghitung:
- Gaji karyawan
- Pajak PPh 21
- Kebutuhan Hidup Layak (KHL)
- Living Wage
- Status kelayakan hidup karyawan berdasarkan provinsi di Indonesia

---

## Tema Program

Program ini dibuat untuk membantu menganalisis apakah gaji seorang karyawan sudah memenuhi standar hidup layak berdasarkan:
- UMP 2026
- Data pengeluaran BPS Susenas September 2024
- Estimasi Living Wage

Program mendukung evaluasi kesejahteraan karyawan agar sesuai dengan prinsip:
> Decent Work and Economic Growth (SDG 8)

---

# Fitur Program

## 1. Tambah Data Karyawan
Program dapat menyimpan data:
- ID karyawan
- Nama
- Jam kerja
- Tarif per jam
- Jabatan
- Status perkawinan
- Jumlah tanggungan
- Provinsi tempat tinggal

---

## 2. Perhitungan Gaji
Program menghitung:
- Gaji kotor
- Lembur
- PTKP
- PKP
- Pajak PPh 21 progresif
- Gaji bersih per bulan

---

## 3. Analisis Kelayakan Hidup
Program membandingkan gaji bersih dengan:
- UMP provinsi
- Kebutuhan Hidup Layak (KHL)
- Living Wage

Status kelayakan:
- Tidak Layak
- Layak Minimum
- Layak Bermartabat

---

## 4. Statistik Perusahaan
Program menampilkan:
- Gaji tertinggi
- Gaji terendah
- Rata-rata gaji
- Total pajak
- Persentase kelayakan hidup
- Skor SDG 8 perusahaan

---

# Struktur Data yang Digunakan

## Enum
Digunakan untuk:
- Jabatan
- Status perkawinan
- Status kelayakan hidup

## Struct
Digunakan untuk:
- Data provinsi
- Data karyawan

## Union
Digunakan untuk menyimpan informasi gaji.

---

# Data yang Digunakan

## Sumber Data
- UMP 2026 → PP No.49 Tahun 2025
- Pengeluaran per kapita → BPS Susenas September 2024
- Living Wage → Estimasi berdasarkan metodologi Global Living Wage Coalition

## Cakupan
Program memuat data:
- 38 provinsi di Indonesia
- UMP tiap provinsi
- Komponen KHL
- Living Wage

---

# Fungsi-Fungsi Program

| Fungsi | Kegunaan |
|---|---|
| `tambahKaryawan()` | Menambahkan data karyawan |
| `hitungGaji()` | Menghitung gaji dan pajak |
| `hitungPPh21()` | Menghitung pajak progresif |
| `getPTKP()` | Mengambil nilai PTKP |
| `tampilkanDaftarProvinsi()` | Menampilkan daftar provinsi |
| `pilihProvinsi()` | Memilih provinsi |
| `hitungKelayakan()` | Menghitung status kelayakan |
| `tampilkanAnalisisKelayakan()` | Menampilkan hasil analisis |
| `tampilkanKaryawan()` | Menampilkan seluruh data karyawan |
| `cariKaryawan()` | Mencari karyawan berdasarkan ID |
| `statistik()` | Menampilkan statistik perusahaan |

---

# Cara Menjalankan Program

## Compile Program
```bash
gcc finpro09.c -o finpro09
