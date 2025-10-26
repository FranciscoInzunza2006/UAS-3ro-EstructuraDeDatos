"use strict"

/** TODO:
 * Hacer que la página se vea bien perrona
 * Qué no puedas modificar el sudoku inicial
 * El señalar de alguna manera cuando el sudoku se vuelve invalido (Señalar las celdas que tú modificaste)
 */

let solution = generateSudoku();
let puzzle = generateSudokuPuzzle(solution);

// HTML Elements
const SUDOKU_ELEMENT = document.getElementById("sudoku");
const DEBUG_ELEMENT = document.getElementById("debug_output");

function createSudokuElements() {
    for (let region_y = 0; region_y < 3; region_y++) {
        for (let region_x = 0; region_x < 3; region_x++) {
            const region = document.createElement("div");
            region.classList.add("sudoku-region");

            for (let cell_y = 0; cell_y < 3; cell_y++) {
                const row = region_y * 3 + cell_y;
                for (let cell_x = 0; cell_x < 3; cell_x++) {
                    const cell = document.createElement("div");
                    cell.classList.add("sudoku-cell");

                    const col = region_x * 3 + cell_x;
                    cell.dataset.row = row.toString();
                    cell.dataset.column = col.toString();

                    const sudoku_cell_value = puzzle[row][col];
                    const is_clue = sudoku_cell_value !== EMPTY_CELL;
                    if (is_clue) {
                        cell.innerText = sudoku_cell_value.toString();
                        cell.classList.add("clue");
                    } else {
                        cell.onclick = cellClicked;
                    }

                    region.appendChild(cell);
                }
            }
            SUDOKU_ELEMENT.appendChild(region);
        }
    }
}

// Styling
function applySudokuStyleDimensions() {
    document.documentElement.style.setProperty("--sudoku-regions-per-row", REGIONS_PER_ROW.toString());
    document.documentElement.style.setProperty("--sudoku-blocks-per-row", BLOCKS_PER_ROW.toString());
}

// Functionality
function changeCellValue(row, col) {
    // TODO: Make the input system something fancier
    const input = prompt("Ingresa un valor del 1 al 9");
    if (input == null || input.trim() === "") {
        puzzle[row][col] = EMPTY_CELL;
    }

    const entered_value = parseInt(input);
    if (isNaN(entered_value)) {
        DEBUG_ELEMENT.innerText += "¡Valor invalido ingresado!\n";
        return;
    }

    if (entered_value < 1 || entered_value > 9) {
        DEBUG_ELEMENT.innerText += "Solo números del 1 al 9\n";
        return;
    }

    puzzle[row][col] = entered_value;
}

function markInvalidCells(sudoku, row, col, num) {
    for (let x = 0; x < COLUMNS; x++) {
        if (sudoku[row][x] === num) return false;
    }

    for (let y = 0; y < ROWS; y++) {
        if (sudoku[y][col] === num) return false;
    }

    // Check region
    const start_row = Math.floor(row / 3) * 3;
    const start_col = Math.floor(col / 3) * 3;
    for (let i = 0; i < 3; i++) {
        for (let j = 0; j < 3; j++) {
            if (sudoku[i + start_row][j + start_col] === num) return false;
        }
    }

    return true;
}

function cellClicked(event) {
    const cell = event.target;
    const row = cell.dataset.row;
    const column = cell.dataset.column;

    changeCellValue(row, column);

    const cell_value = puzzle[row][column];
    cell.innerText = (cell_value !== EMPTY_CELL) ? puzzle[row][column].toString() : "";

    DEBUG_ELEMENT.innerText += "Row: " + row + "\n";
    DEBUG_ELEMENT.innerText += "Column : " + column + "\n\n";
}

// Driver code
function init() {
    // HTML Page and styling
    //applySudokuStyleDimensions();
    createSudokuElements();
    printSudoku(solution);
}

window.onload = init;