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

