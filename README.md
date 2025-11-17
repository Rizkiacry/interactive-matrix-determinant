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
    A[Start] --> B[Initialize TUI Window & Matrix Data];
    B --> C{Main Application Loop};
    C --> D[Generate Display String from Matrix Data];
    D --> E[Calculate Determinant (Recursive)];
    E --> F[Render UI with Display String];
    F --> G[Wait for User Input];
    G -- Key Press --> H[Handle Key Press];
    H --> I{Update Matrix Data, Size, or Cursor Position};
    I --> C;
    G -- 'q' Key --> J[End Loop];
    J --> K[Close TUI Window];
    K --> L[End];
```
