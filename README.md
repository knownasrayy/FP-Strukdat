# Final Project Struktur Data - Kelompok 1

## Nama Kelompok:

| NRP         | Nama                                 |
|-------------|--------------------------------------|
| 5027241056  | Theodorus Aaron Ugraha               |
| 5027241102  | Rayhan Agnan Kusuma                  |
| 5027241071  | Fika Arka Nuriyah                    |
| 5027241118  | Naufal Ardhana                       |
| 5027241105  | Naruna Vicranthyo Putra Gangga       |
| 5027241065  | Dina Rahmadani                       |

## Deskripsi Proyek
Implementasi sistem pencarian rute dengan mempertimbangkan preferensi pengguna menggunakan algoritma A* dan Dijkstra.

## Struktur Proyek
```
.
├── asset/              # Dokumentasi proyek
├── data/              # File data (CSV dan JSON)
│   ├── location.csv
│   ├── preference.json
│   └── route.csv
├── include/           # Header files (.hpp)
│   ├── algorithm/     # Implementasi algoritma
│   ├── graph/        # Struktur data graph
│   ├── io/           # File handlers
│   ├── preference/   # Pengolahan preferensi
│   └── utils/        # Utilitas
├── src/              # Source files (.cpp)
├── test/             # Unit tests
└── main.cpp          # Entry point
```

## Fitur
- Implementasi algoritma A* dan Dijkstra untuk pencarian rute
- Penanganan preferensi pengguna
- Pembacaan data dari file CSV dan JSON
- Unit testing untuk validasi algoritma

## Cara Kompilasi
```bash
make
```

## Cara Menjalankan
```bash
./main
```

## Cara Menjalankan Tests
```bash
make test
```