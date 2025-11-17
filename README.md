# Interactive Matrix Determinant

This project is an interactive tool for calculating matrix determinants, utilizing the `termui-cpp` library.

**Credit:**
*   `termui-cpp`: [https://github.com/claby2/termui-cpp](https://github.com/claby2/termui-cpp)

**Kelas Aljabar Linier C31020101 Kelompok 9:**
*   Zain Akbar Rizkia (202531091)
*   Iqbal Raihan Raffianza (202531111)
*   FX. Oktabimo DwiPriabudi Sumintro (202531085)
*   Lewis Radhi Oktasamiqdad (202531107)

## Program Flow

```mermaid
graph TD
    A[Start] --> B[Init];
    B --> C{Loop};
    C --> D[Display];
    D --> E[Calc_Det];
    E --> F[Render];
    F --> G[Input];
    G --> H[Handle_Key];
    H --> C;
    G --> J[Quit];
    J --> K[End];
```

## Sequence Diagram

```mermaid
sequenceDiagram
    participant Pengguna
    participant main
    participant Jendela
    participant getDisplayString
    participant determinantOfMatrix
    participant getCofactor
    participant handleKeyPress

    Pengguna->>main: Pengguna memulai program.
    main->>Jendela: Program utama menyiapkan jendela tampilan.
    loop Loop Utama
        main->>getDisplayString: Program utama meminta teks untuk ditampilkan.
        getDisplayString->>determinantOfMatrix: Untuk menampilkan teks, perlu dihitung dulu determinannya.
        activate determinantOfMatrix
        determinantOfMatrix->>getCofactor: Perhitungan determinan butuh kofaktor.
        getCofactor-->>determinantOfMatrix: Kofaktor didapatkan dan dikembalikan.
        Note right of determinantOfMatrix: Panggilan rekursif dihilangkan untuk kejelasan.
        determinantOfMatrix-->>getDisplayString: Hasil determinan dikembalikan untuk ditampilkan.
        deactivate determinantOfMatrix
        getDisplayString-->>main: Teks final (termasuk determinan) siap ditampilkan.
        main->>Jendela: Program utama menampilkan semua teks ke jendela.
        main->>Jendela: Program menunggu input dari pengguna.
        Jendela-->>Pengguna: Jendela menampilkan antarmuka kepada pengguna.
        Pengguna->>Jendela: Pengguna menekan sebuah tombol.
        Jendela-->>main: Informasi tombol yang ditekan dikirim ke program utama.
        main->>handleKeyPress: Program utama memproses tombol yang ditekan.
        handleKeyPress-->>main: Status program diperbarui (misal: angka di matriks berubah).
    end
    main->>Jendela: Setelah siklus berhenti (pengguna keluar), program menutup jendela.
```
