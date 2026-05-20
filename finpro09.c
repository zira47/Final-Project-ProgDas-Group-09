#include <stdio.h>

#define MAKS 100
#define JUMLAH_PROVINSI 38

// ZIRA
// ENUM
typedef enum
{
    STAF,
    MANAJER,
    MAGANG
} Jabatan;
typedef enum
{
    TK,
    K
} StatusPerkawinan;
typedef enum
{
    TIDAK_LAYAK,      // Gaji < KHL
    LAYAK_MINIMUM,    // KHL <= Gaji < Living Wage
    LAYAK_BERMARTABAT // Gaji >= Living Wage
} StatusKelayakan;

// ZIRA
// UNION
typedef union
{
    float gajiPerBulan;
    float bonus;
} InfoGaji;

// ZIRA
// STRUCT DATA PROVINSI
// Sumber data:
/*   
- UMP 2026     : PP No.49 Tahun 2025 
- Pengeluaran  : BPS Susenas September 2024 
- Komponen KHL : Estimasi pengeluaran berdasarkan BPS (pangan 50%, papan 25%, sandang 5%, kesehatan 8%, transport 12%)
- Living Wage  : KHL + pendidikan + rekreasi + tabungan darurat (estimasi 20-25% di atas KHL, mengacu metodologi Global Living Wage Coalition)
*/

typedef struct
{
    char nama[40];        // Nama provinsi
    float ump;            // UMP 2026 (Rp/bulan) 
    float biayaPangan;    
    float biayaSandang;   
    float biayaPapan;     
    float biayaKesehatan; 
    float biayaTransport; 
    // Komponen tambahan Living Wage (di atas KHL)
    float biayaPendidikan; // Pengembangan diri
    float biayaRekreasi;   // Sosial & hiburan
    float biayaTabungan;   // Tabungan darurat minimum
} DataProvinsi;

// HILL
// DATA 38 PROVINSI
// Pengeluaran per kapita BPS Sep 2024 (Rp/bulan):
DataProvinsi dataProvinsi[JUMLAH_PROVINSI] = {
    // Format: {nama, UMP2026, pangan, sandang, papan, kesehatan, transport, pendidikan, rekreasi, tabungan}
    // Komponen KHL dihitung dari pengeluaran per kapita BPS × proporsi masing-masing
    // Living Wage tambahan 20-25% dari total KHL

    // PULAU JAWA
    {"DKI Jakarta", 5729876.0f, 1450000, 290000, 725000, 232000, 348000, 580000, 290000, 725000},
    {"Jawa Barat", 2317601.0f, 750000, 100000, 375000, 120000, 180000, 250000, 125000, 300000},
    {"Jawa Tengah", 2327386.0f, 650000, 90000, 325000, 104000, 156000, 200000, 100000, 260000},
    {"DI Yogyakarta", 2417495.0f, 750000, 100000, 375000, 120000, 180000, 250000, 150000, 300000},
    {"Jawa Timur", 2446880.0f, 700000, 95000, 350000, 112000, 168000, 230000, 115000, 280000},
    {"Banten", 3100881.0f, 895000, 125000, 447000, 143000, 215000, 350000, 179000, 450000},

    // SUMATERA 
    {"Aceh", 3932552.0f, 650000, 90000, 325000, 104000, 156000, 200000, 100000, 260000},
    {"Sumatera Utara", 3228949.0f, 725000, 98000, 362000, 116000, 174000, 240000, 120000, 290000},
    {"Sumatera Barat", 3182955.0f, 700000, 95000, 350000, 112000, 168000, 230000, 115000, 280000},
    {"Riau", 3780495.0f, 800000, 110000, 400000, 128000, 192000, 280000, 140000, 320000},
    {"Jambi", 3471497.0f, 725000, 98000, 362000, 116000, 174000, 240000, 120000, 290000},
    {"Sumatera Selatan", 3942963.0f, 650000, 90000, 325000, 104000, 156000, 200000, 100000, 260000},
    {"Bengkulu", 2827250.0f, 675000, 92000, 337000, 108000, 162000, 210000, 105000, 270000},
    {"Lampung", 3047734.0f, 610000, 85000, 305000, 98000, 146000, 190000, 95000, 244000},
    {"Kep. Bangka Belitung", 4035000.0f, 825000, 113000, 412000, 132000, 198000, 290000, 145000, 330000},
    {"Kepulauan Riau", 3879520.0f, 1105000, 154000, 552000, 177000, 265000, 440000, 220000, 550000},

    // KALIMANTAN
    {"Kalimantan Barat", 3054552.0f, 750000, 100000, 375000, 120000, 180000, 250000, 125000, 300000},
    {"Kalimantan Tengah", 3686138.0f, 850000, 115000, 425000, 136000, 204000, 300000, 150000, 340000},
    {"Kalimantan Selatan", 3725000.0f, 825000, 113000, 412000, 132000, 198000, 290000, 145000, 330000},
    {"Kalimantan Timur", 3762431.0f, 1015000, 140000, 507000, 162000, 244000, 400000, 200000, 500000},
    {"Kalimantan Utara", 3775243.0f, 910000, 126000, 455000, 146000, 218000, 360000, 180000, 455000},

    // SULAWESI 
    {"Sulawesi Utara", 3775425.0f, 775000, 105000, 387000, 124000, 186000, 260000, 130000, 310000},
    {"Sulawesi Tengah", 3194754.0f, 640000, 89000, 320000, 102000, 154000, 200000, 100000, 256000},
    {"Sulawesi Selatan", 3657527.0f, 650000, 90000, 325000, 104000, 156000, 200000, 100000, 260000},
    {"Sulawesi Tenggara", 3073551.0f, 635000, 88000, 317000, 102000, 152000, 195000, 98000, 254000},
    {"Gorontalo", 3221731.0f, 675000, 92000, 337000, 108000, 162000, 210000, 105000, 270000},
    {"Sulawesi Barat", 2736698.0f, 540000, 75000, 270000, 86000, 130000, 170000, 85000, 216000},

    // BALI & NUSA TENGGARA 
    {"Bali", 3207459.0f, 930000, 128000, 465000, 149000, 223000, 370000, 185000, 465000},
    {"Nusa Tenggara Barat", 2701985.0f, 600000, 83000, 300000, 96000, 144000, 190000, 95000, 240000},
    {"Nusa Tenggara Timur", 2328490.0f, 510000, 71000, 255000, 82000, 122000, 160000, 80000, 204000},

    // MALUKU
    {"Maluku", 3650000.0f, 665000, 91000, 332000, 106000, 160000, 205000, 103000, 266000},
    {"Maluku Utara", 3408000.0f, 750000, 100000, 375000, 120000, 180000, 250000, 125000, 300000},

    // PAPUA 
    {"Papua Barat", 4107000.0f, 910000, 126000, 455000, 146000, 218000, 360000, 180000, 455000},
    {"Papua Barat Daya", 3871000.0f, 935000, 130000, 467000, 150000, 224000, 370000, 185000, 468000},
    {"Papua", 4285848.0f, 940000, 130000, 470000, 150000, 225000, 375000, 188000, 470000},
    {"Papua Selatan", 4024270.0f, 850000, 115000, 425000, 136000, 204000, 300000, 150000, 340000},
    {"Papua Tengah", 4024270.0f, 800000, 110000, 400000, 128000, 192000, 280000, 140000, 320000},
    {"Papua Pegunungan", 4024270.0f, 945000, 131000, 472000, 151000, 226000, 378000, 189000, 472000},
};

// STRUCT KARYAWAN
typedef struct
{
    int id;
    char nama[50];
    int jam;
    float tarif;
    float gajiKotorPerBulan;
    float pajakPerBulan;
    float gajiBersihPerBulan;
    float ptkp;
    float pkp;
    Jabatan jabatan;
    StatusPerkawinan perkawinan;
    int tanggungan;
    InfoGaji info;

    // Data wilayah & kelayakan
    int indeksProvinsi;    // Index ke array dataProvinsi
    float totalKHL;        // Total KHL/bulan (disesuaikan tanggungan)
    float totalLivingWage; // Total Living Wage/bulan
    float selisihKHL;      // Gaji bersih - KHL
    float selisihLW;       // Gaji bersih - Living Wage
    float selisihUMP;      // Gaji bersih - UMP 2026
    StatusKelayakan kelayakan;
} Karyawan;

// DEKLARASI FUNGSI
void tampilkanDaftarProvinsi(); // HILL
int pilihProvinsi(); // HILL
void hitungKelayakan(Karyawan *kar); // HILL
void tampilkanAnalisisKelayakan(Karyawan *kar); // HILL


// HILL
// TAMPILKAN DAFTAR PROVINSI
// Menampilkan semua provinsi beserta UMP 2026, total KHL, dan total Living Wage
void tampilkanDaftarProvinsi()
{
    printf("\n--- DAFTAR 38 PROVINSI INDONESIA ---\n");
    printf("%-3s %-25s %12s %12s %12s\n\n", "No", "Provinsi", "UMP 2026", "KHL/bln", "Living Wage/bln");

    for (int i = 0; i < JUMLAH_PROVINSI; i++)
    {
        // Hitung KHL = jumlah 5 komponen dasar
        float khl = dataProvinsi[i].biayaPangan + dataProvinsi[i].biayaSandang + dataProvinsi[i].biayaPapan + dataProvinsi[i].biayaKesehatan + dataProvinsi[i].biayaTransport;

        // Hitung Living Wage = KHL + 3 komponen tambahan
        float lw = khl + dataProvinsi[i].biayaPendidikan + dataProvinsi[i].biayaRekreasi + dataProvinsi[i].biayaTabungan;

        printf("%-3d %-25s %12.0f %12.0f %14.0f\n",
            i + 1,
            dataProvinsi[i].nama,
            dataProvinsi[i].ump,
            khl, lw);
    }
}
