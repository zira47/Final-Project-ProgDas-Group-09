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
void tambahKaryawan(Karyawan *kar, int *jumlah); // ZIRA
float getPTKP(StatusPerkawinan perkawinan, int tanggungan); //ZIRA
float hitungPPh21(float pkp); // ZIRA
void hitungGaji(Karyawan *kar); // ZIRA
void tampilkanKaryawan(Karyawan *kar, int jumlah); // LEA
void cariKaryawan(Karyawan *kar, int jumlah); // LEA
void statistik(Karyawan *kar, int jumlah); // LEA

// LEA
// MAIN PROGRAM
int main()
{
    Karyawan *karyawan = (Karyawan *)malloc(MAKS * sizeof(Karyawan));
    int jumlah = 0;
    int pilihan;

    do
    {   printf("\n============================================\n");
        printf("    SISTEM MANAJEMEN GAJI LAYAK (SDG 8)    \n");
        printf("     Decent Work & Economic Growth        \n");
        printf("   Data: UMP 2026 + BPS Susenas Sep 2024  \n");
        printf("============================================\n");
        printf("1. Tambah Karyawan\n");
        printf("2. Tampilkan Semua Karyawan\n");
        printf("3. Cari Karyawan\n");
        printf("4. Statistik Gaji & Kelayakan\n");
        printf("5. Keluar\n");
        printf("Pilih Menu: ");

        if (scanf("%d", &pilihan) != 1)
        {
            printf("\nInput Tidak Valid\n");
            return 0;
        }

        switch (pilihan)
        {
        case 1:
            tambahKaryawan(karyawan, &jumlah);
            break;
        case 2:
            tampilkanKaryawan(karyawan, jumlah);
            break;
        case 3:
            cariKaryawan(karyawan, jumlah);
            break;
        case 4:
            statistik(karyawan, jumlah);
            break;
        case 5:
            printf("\nProgram Selesai\n");
            break;
        default:
            printf("\nMenu Tidak Valid\n");
        }

    } while (pilihan != 5);

    free(karyawan);
    return 0;
}


// HILL
// TAMPILKAN DAFTAR PROVINSI
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

    // Setiap tanggungan menambah 40% dari biaya pangan + kesehatan
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

// ZIRA
// GET PTKP 
float getPTKP(StatusPerkawinan perkawinan, int tanggungan)
{
    float ptkpDasar = (perkawinan == TK) ? 54000000.0f : 58500000.0f;
    return ptkpDasar + (tanggungan * 4500000.0f);
}

// ZIRA
// HITUNG PPh 21 PROGRESIF 
float hitungPPh21(float pkp)
{
    if (pkp <= 0)
        return 0;
    float pajak = 0;
    if (pkp <= 60000000)
        pajak = pkp * 0.05f;
    else if (pkp <= 250000000)
    {
        pajak = 60000000 * 0.05f;
        pajak += (pkp - 60000000) * 0.15f;
    }
    else if (pkp <= 500000000)
    {
        pajak = 60000000 * 0.05f;
        pajak += (250000000 - 60000000) * 0.15f;
        pajak += (pkp - 250000000) * 0.25f;
    }
    else if (pkp <= 5000000000.0f)
    {
        pajak = 60000000 * 0.05f;
        pajak += (250000000 - 60000000) * 0.15f;
        pajak += (500000000 - 250000000) * 0.25f;
        pajak += (pkp - 500000000) * 0.30f;
    }
    else
    {
        pajak = 60000000 * 0.05f;
        pajak += (250000000 - 60000000) * 0.15f;
        pajak += (500000000 - 250000000) * 0.25f;
        pajak += (5000000000.0f - 500000000) * 0.30f;
        pajak += (pkp - 5000000000.0f) * 0.35f;
    }
    return pajak;
}

// ZIRA
// HITUNG GAJI 
void hitungGaji(Karyawan *kar)
{
    float lembur = 0;
    if (kar->jam > 40)
        lembur = (kar->jam - 40) * (kar->tarif * 1.5f);
    kar->gajiKotorPerBulan = (kar->jam * kar->tarif) + lembur;

    float gajiSetahun = kar->gajiKotorPerBulan * 12;
    kar->ptkp = getPTKP(kar->perkawinan, kar->tanggungan);
    kar->pkp = gajiSetahun - kar->ptkp;
    if (kar->pkp < 0)
        kar->pkp = 0;

    float pajakSetahun = hitungPPh21(kar->pkp);
    kar->pajakPerBulan = pajakSetahun / 12;
    kar->gajiBersihPerBulan = kar->gajiKotorPerBulan - kar->pajakPerBulan;
    kar->info.gajiPerBulan = kar->gajiBersihPerBulan;
}

// LEA
// TAMPILKAN SEMUA KARYAWAN
void tampilkanKaryawan(Karyawan *kar, int jumlah)
{
    if (jumlah == 0)
    {
        printf("Tidak Ada Data Karyawan\n");
        return;
    }

    for (int i = 0; i < jumlah; i++)
    {
        printf("\n===== KARYAWAN %d =====\n", i + 1);
        printf("ID                : %d\n", kar[i].id);
        printf("Nama              : %s\n", kar[i].nama);
        printf("Provinsi          : %s\n", dataProvinsi[kar[i].indeksProvinsi].nama);
        printf("Jam/Bulan         : %d\n", kar[i].jam);
        printf("Tarif Per Jam     : Rp%.2f\n", kar[i].tarif);

        if (kar[i].jam >= 200)
            printf("Produktivitas     : Sangat Tinggi\n");
        else if (kar[i].jam >= 160)
            printf("Produktivitas     : Tinggi\n");
        else
            printf("Produktivitas     : Normal\n");

        switch (kar[i].jabatan)
        {
        case STAF:
            printf("Jabatan           : Staf\n");
            break;
        case MANAJER:
            printf("Jabatan           : Manajer\n");
            break;
        case MAGANG:
            printf("Jabatan           : Magang\n");
            break;
        }

        printf("Status Perkawinan : %s\n",
            kar[i].perkawinan == TK ? "Tidak Kawin (TK)" : "Kawin (K)");
        printf("Tanggungan        : %d\n", kar[i].tanggungan);

        printf("--- Perhitungan PPh 21 ---\n");
        printf("Gaji Kotor/bln    : Rp%.2f\n", kar[i].gajiKotorPerBulan);
        printf("Gaji Kotor/thn    : Rp%.2f\n", kar[i].gajiKotorPerBulan * 12);
        printf("PTKP              : Rp%.2f\n", kar[i].ptkp);
        printf("PKP (setahun)     : Rp%.2f\n", kar[i].pkp);
        printf("PPh 21/bulan      : Rp%.2f\n", kar[i].pajakPerBulan);
        printf("Gaji Bersih/bln   : Rp%.2f\n", kar[i].gajiBersihPerBulan);

        tampilkanAnalisisKelayakan(&kar[i]);
    }
}

// LEA  
// CARI KARYAWAN
void cariKaryawan(Karyawan *kar, int jumlah)
{
    int id, ditemukan = 0;
    printf("\nMasukkan ID Karyawan: ");
    scanf("%d", &id);

    for (int i = 0; i < jumlah; i++)
    {
        if (kar[i].id == id)
        {
            printf("\nKaryawan Ditemukan\n");
            printf("Nama              : %s\n", kar[i].nama);
            printf("Provinsi          : %s\n", dataProvinsi[kar[i].indeksProvinsi].nama);
            printf("Gaji Bersih/bln   : Rp%.2f\n", kar[i].gajiBersihPerBulan);
            tampilkanAnalisisKelayakan(&kar[i]);
            ditemukan = 1;
        }
    }
    if (!ditemukan)
        printf("Karyawan Tidak Ditemukan\n");
}

// LEA
// STATISTIK + REKAPITULASI SDG 8
void statistik(Karyawan *kar, int jumlah)
{
    if (jumlah == 0)
    {
        printf("Tidak Ada Data Tersedia\n");
        return;
    }

    float tertinggi = kar[0].gajiBersihPerBulan;
    float terendah = kar[0].gajiBersihPerBulan;
    float totalBersih = 0, totalPajak = 0;

    int jmlTidakLayak = 0, jmlLayakMin = 0, jmlLayakBermartabat = 0;
    int jmlDiBawahUMP = 0;
    float totalDefisitKHL = 0, totalDefisitLW = 0;

    for (int i = 0; i < jumlah; i++)
    {
        if (kar[i].gajiBersihPerBulan > tertinggi)
            tertinggi = kar[i].gajiBersihPerBulan;
        if (kar[i].gajiBersihPerBulan < terendah)
            terendah = kar[i].gajiBersihPerBulan;
        totalBersih += kar[i].gajiBersihPerBulan;
        totalPajak += kar[i].pajakPerBulan;

        if (kar[i].selisihUMP < 0)
            jmlDiBawahUMP++;

        switch (kar[i].kelayakan)
        {
        case TIDAK_LAYAK:
            jmlTidakLayak++;
            totalDefisitKHL += -kar[i].selisihKHL;
            totalDefisitLW += -kar[i].selisihLW;
            break;
        case LAYAK_MINIMUM:
            jmlLayakMin++;
            totalDefisitLW += -kar[i].selisihLW;
            break;
        case LAYAK_BERMARTABAT:
            jmlLayakBermartabat++;
            break;
        }
    }

    printf("\n   STATISTIK GAJI & KELAYAKAN HIDUP (SDG 8)  \n");

    printf("\n[1] STATISTIK GAJI\n");
    printf("    Gaji Bersih Tertinggi : Rp%.2f\n", tertinggi);
    printf("    Gaji Bersih Terendah  : Rp%.2f\n", terendah);
    printf("    Rata-rata Gaji Bersih : Rp%.2f\n", totalBersih / jumlah);
    printf("    Total PPh 21/bulan    : Rp%.2f\n", totalPajak);

    printf("\n[2] KEPATUHAN HUKUM — UMP 2026\n");
    printf("    Di bawah UMP (ilegal) : %d orang (%.1f%%)\n",
           jmlDiBawahUMP, (float)jmlDiBawahUMP / jumlah * 100);
    printf("    Di atas / sesuai UMP  : %d orang (%.1f%%)\n",
        jumlah - jmlDiBawahUMP,
           (float)(jumlah - jmlDiBawahUMP) / jumlah * 100);

    printf("\n[3] REKAPITULASI KELAYAKAN HIDUP\n");
    printf("    Total Karyawan        : %d orang\n", jumlah);
    printf("    ---------------------------------─────\n");
    printf("    Tidak Layak (< KHL): %d orang (%.1f%%)\n",
           jmlTidakLayak, (float)jmlTidakLayak / jumlah * 100);
    printf("    Layak Minimum      : %d orang (%.1f%%)\n",
           jmlLayakMin, (float)jmlLayakMin / jumlah * 100);
    printf("    Layak Bermartabat  : %d orang (%.1f%%)\n",
           jmlLayakBermartabat, (float)jmlLayakBermartabat / jumlah * 100);

    printf("\n[4] ANALISIS DEFISIT UPAH\n");
    if (totalDefisitKHL > 0)
        printf("    Total defisit vs KHL  : Rp%.0f/bulan\n", totalDefisitKHL);
    else
        printf("    Semua karyawan memenuhi standar KHL.\n");
    if (totalDefisitLW > 0)
        printf("    Total defisit vs LW   : Rp%.0f/bulan\n", totalDefisitLW);
    else
        printf("    Semua karyawan memenuhi standar Living Wage.\n");

    // Skor SDG 8:
    float skorSDG8 = (float)jmlLayakBermartabat / jumlah * 100;
    printf("\n[5] SKOR SDG 8 PERUSAHAAN\n");
    printf("    %.1f%% karyawan hidup layak bermartabat\n", skorSDG8);
    if (skorSDG8 >= 80)
        printf("    BAIK - Perusahaan mendukung Decent Work dengan baik.\n");
    else if (skorSDG8 >= 50)
        printf("    CUKUP - Masih perlu peningkatan kesejahteraan karyawan.\n");
    else
        printf("    KRITIS - Perlu perhatian serius terhadap kelayakan upah.\n");

    printf("\n    Sumber data: UMP 2026 (PP No.49 Th.2025) BPS Susenas September 2024\n");
}
