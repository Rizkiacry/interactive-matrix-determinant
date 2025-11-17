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
    participant User
    participant main
    participant Window
    participant getDisplayString
    participant determinantOfMatrix
    participant getCofactor
    participant handleKeyPress

    User->>main: Starts the program
    main->>Window: new()
    loop Main Loop
        main->>getDisplayString: call
        getDisplayString->>determinantOfMatrix: call
        activate determinantOfMatrix
        determinantOfMatrix->>getCofactor: call
        getCofactor-->>determinantOfMatrix: return cofactor
        Note right of determinantOfMatrix: Recursive calls omitted for clarity
        determinantOfMatrix-->>getDisplayString: return determinant
        deactivate determinantOfMatrix
        getDisplayString-->>main: return display string
        main->>Window: render()
        main->>Window: poll_event()
        Window-->>User: Shows UI
        User->>Window: Presses a key
        Window-->>main: returns Event
        main->>handleKeyPress: call with Event
        handleKeyPress-->>main: updates state
    end
    main->>Window: close()
```