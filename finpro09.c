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

// HILL
// PILIH PROVINSI
int pilihProvinsi()
{
    tampilkanDaftarProvinsi();

    int pilihan;
    printf("\nPilih nomor provinsi (1-%d): ", JUMLAH_PROVINSI);
    scanf("%d", &pilihan);

    if (pilihan < 1 || pilihan > JUMLAH_PROVINSI)
    {
        printf("Pilihan tidak valid, menggunakan DKI Jakarta sebagai default.\n");
        return 0; // Default index 0 = DKI Jakarta
    }

    return pilihan - 1; // Konversi ke index 0-based
}

// HILL
// HITUNG KELAYAKAN
// Membandingkan gaji bersih vs KHL, Living Wage, dan UMP 2026 provinsi karyawan
void hitungKelayakan(Karyawan *kar)
{
    int p = kar->indeksProvinsi;

    // Hitung Total KHL (5 komponen dasar) 
    kar->totalKHL = dataProvinsi[p].biayaPangan + dataProvinsi[p].biayaSandang + dataProvinsi[p].biayaPapan + dataProvinsi[p].biayaKesehatan + dataProvinsi[p].biayaTransport;

    // Hitung Total Living Wage (KHL + 3 komponen martabat) 
    kar->totalLivingWage = kar->totalKHL + dataProvinsi[p].biayaPendidikan + dataProvinsi[p].biayaRekreasi + dataProvinsi[p].biayaTabungan;

    // Sesuaikan dengan Tanggungan
    // Setiap tanggungan menambah 40% dari biaya pangan + kesehatan
    // (karena papan & transport relatif tidak berubah signifikan)
    if (kar->tanggungan > 0)
    {
        float tambahanPerOrang =
            (dataProvinsi[p].biayaPangan + dataProvinsi[p].biayaKesehatan) * 0.40f;
        float totalTambahan = tambahanPerOrang * kar->tanggungan;
        kar->totalKHL += totalTambahan;
        kar->totalLivingWage += totalTambahan;
    }

    // Hitung Selisih
    kar->selisihKHL = kar->gajiBersihPerBulan - kar->totalKHL;
    kar->selisihLW = kar->gajiBersihPerBulan - kar->totalLivingWage;
    kar->selisihUMP = kar->gajiBersihPerBulan - dataProvinsi[p].ump;

    // Tentukan Status Kelayakan
    if (kar->selisihKHL < 0)
        kar->kelayakan = TIDAK_LAYAK;
    else if (kar->selisihLW < 0)
        kar->kelayakan = LAYAK_MINIMUM;
    else
        kar->kelayakan = LAYAK_BERMARTABAT;
}

// HILL
// TAMPILKAN ANALISIS KELAYAKAN
void tampilkanAnalisisKelayakan(Karyawan *kar)
{
    int p = kar->indeksProvinsi;
    printf("\n==============================================\n");
    printf("      ANALISIS KELAYAKAN HIDUP (SDG 8)        \n");
    printf("  Decent Work & Economic Growth - Goal 8     \n");
    printf("==============================================\n");
    printf("Karyawan   : %s\n", kar->nama);
    printf("Provinsi   : %s\n", dataProvinsi[p].nama);
    printf("Tanggungan : %d orang\n", kar->tanggungan);
    printf("UMP 2026   : Rp%.0f\n", dataProvinsi[p].ump);

    // Blok A: Rincian KHL 
    printf("\n[A] KEBUTUHAN HIDUP LAYAK / KHL\n");
    printf("    (Sumber: BPS Susenas Sep 2024 - proporsi pengeluaran per kapita)\n");
    printf("    Pangan       : Rp %10.0f\n", dataProvinsi[p].biayaPangan);
    printf("    Sandang      : Rp %10.0f\n", dataProvinsi[p].biayaSandang);
    printf("    Papan (sewa) : Rp %10.0f\n", dataProvinsi[p].biayaPapan);
    printf("    Kesehatan    : Rp %10.0f\n", dataProvinsi[p].biayaKesehatan);
    printf("    Transport    : Rp %10.0f\n", dataProvinsi[p].biayaTransport);

    if (kar->tanggungan > 0)
    {
        float tambahanPerOrang =
            (dataProvinsi[p].biayaPangan + dataProvinsi[p].biayaKesehatan) * 0.40f;
        printf("    Tanggungan(%dx): Rp %7.0f\n",
            kar->tanggungan,
               tambahanPerOrang * kar->tanggungan);
    }
    printf("    ---------------------------------\n");
    printf("    TOTAL KHL    : Rp %10.0f\n", kar->totalKHL);

    // Blok B: Rincian Living Wage
    printf("\n[B] LIVING WAGE - Upah Hidup Bermartabat\n");
    printf("    (Metodologi: Global Living Wage Coalition + BPS 2024)\n");
    printf("    KHL (di atas): Rp %10.0f\n", kar->totalKHL);
    printf("    Pendidikan   : Rp %10.0f\n", dataProvinsi[p].biayaPendidikan);
    printf("    Rekreasi     : Rp %10.0f\n", dataProvinsi[p].biayaRekreasi);
    printf("    Tabungan     : Rp %10.0f\n", dataProvinsi[p].biayaTabungan);
    printf("    ---------------------------------\n");
    printf("    TOTAL LW     : Rp %10.0f\n", kar->totalLivingWage);

    // Blok C: Perbandingan
    printf("\n[C] PERBANDINGAN DENGAN GAJI BERSIH\n");
    printf("    Gaji Bersih/bln  : Rp %10.0f\n", kar->gajiBersihPerBulan);
    printf("    ---------------------------------\n");

    // Perbandingan vs UMP
    if (kar->selisihUMP >= 0)
        printf("    vs UMP 2026      : Rp %10.0f   DI ATAS UMP\n", kar->selisihUMP);
    else
        printf("    vs UMP 2026      : Rp %10.0f   DI BAWAH UMP (melanggar hukum!)\n",
            kar->selisihUMP);

    // Perbandingan vs KHL
    if (kar->selisihKHL >= 0)
        printf("    vs KHL           : Rp %10.0f   SURPLUS\n", kar->selisihKHL);
    else
        printf("    vs KHL           : Rp %10.0f   DEFISIT\n", kar->selisihKHL);

    // Perbandingan vs Living Wage
    if (kar->selisihLW >= 0)
        printf("    vs Living Wage   : Rp %10.0f   SURPLUS\n", kar->selisihLW);
    else
        printf("    vs Living Wage   : Rp %10.0f   DEFISIT\n", kar->selisihLW);

    // Blok D: Vonis Status
    printf("\n[D] STATUS KELAYAKAN HIDUP\n");
    switch (kar->kelayakan)
    {
    case TIDAK_LAYAK:
        printf("    TIDAK LAYAK \n");
        printf("    Gaji belum mencukupi kebutuhan hidup dasar (KHL).\n");
        printf("    Karyawan ini berisiko mengalami kemiskinan dan\n");
        printf("    tidak dapat memenuhi kebutuhan dasar keluarganya.\n");
        printf("    Butuh kenaikan gaji minimal: Rp %.0f/bulan\n",
            -kar->selisihKHL);
        printf("    Untuk mencapai Living Wage butuh: Rp %.0f/bulan\n",
            -kar->selisihLW);
        break;
    case LAYAK_MINIMUM:
        printf("    LAYAK MINIMUM \n");
        printf("    Gaji cukup untuk kebutuhan dasar (KHL),\n");
        printf("    namun belum memenuhi standar hidup bermartabat.\n");
        printf("    Karyawan tidak punya ruang untuk menabung atau\n");
        printf("    mengembangkan diri secara optimal.\n");
        printf("    Butuh tambahan Rp %.0f/bulan untuk Living Wage.\n",
            -kar->selisihLW);
        break;
    case LAYAK_BERMARTABAT:
        printf("    LAYAK BERMARTABAT \n");
        printf("    Gaji mencukupi untuk hidup layak dan bermartabat.\n");
        printf("    Karyawan dapat memenuhi KHL, menabung, berekreasi, dan terus mengembangkan diri.\n");
        printf("    Surplus di atas Living Wage: Rp %.0f/bulan\n",
            kar->selisihLW);
        break;
    }
}

// ZIRA
// TAMBAH KARYAWAN
void tambahKaryawan(Karyawan *kar, int *jumlah)
{
    printf("\nID Karyawan: ");
    scanf("%d", &kar[*jumlah].id);

    printf("Nama Karyawan: ");
    scanf("%s", kar[*jumlah].nama);

    printf("Jam Kerja (per bulan): ");
    scanf("%d", &kar[*jumlah].jam);

    printf("Tarif Per Jam (Rp): ");
    scanf("%f", &kar[*jumlah].tarif);

    int pilihanJabatan;
    printf("\nJabatan\n0. Staf\n1. Manajer\n2. Magang\nPilih: ");
    scanf("%d", &pilihanJabatan);
    kar[*jumlah].jabatan = (Jabatan)pilihanJabatan;

    int pilihanPerkawinan;
    printf("\nStatus Perkawinan\n0. Tidak Kawin (TK)\n1. Kawin (K)\nPilih: ");
    scanf("%d", &pilihanPerkawinan);
    kar[*jumlah].perkawinan = (StatusPerkawinan)pilihanPerkawinan;

    printf("Jumlah Tanggungan (0-3): ");
    scanf("%d", &kar[*jumlah].tanggungan);
    if (kar[*jumlah].tanggungan < 0)
        kar[*jumlah].tanggungan = 0;
    if (kar[*jumlah].tanggungan > 3)
        kar[*jumlah].tanggungan = 3;

    printf("\nProvinsi Tempat Tinggal Karyawan:\n");
    kar[*jumlah].indeksProvinsi = pilihProvinsi();

    hitungGaji(&kar[*jumlah]);
    hitungKelayakan(&kar[*jumlah]);

    (*jumlah)++;
    printf("\nKaryawan Berhasil Ditambahkan!\n");

    // Langsung tampilkan analisis kelayakan setelah input
    tampilkanAnalisisKelayakan(&kar[*jumlah - 1]);
}
