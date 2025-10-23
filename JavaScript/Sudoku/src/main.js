"use strict"

let sudoku = generateSudoku()

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
                    const col = region_x * 3 + cell_x;

                    cell.dataset.row = row.toString();
                    cell.dataset.column = col.toString();
                    cell.onclick = cellClicked;

                    const sudoku_cell_value = sudoku[row][col];
                    cell.innerText = sudoku_cell_value.toString();

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
function cellClicked(event) {
    const cell = event.target;
    const row = cell.dataset.row;
    const column = cell.dataset.column;

    DEBUG_ELEMENT.innerText += "Row: " + row + "\n";
    DEBUG_ELEMENT.innerText += "Column : " + column + "\n\n";
}

function init() {
    // HTML Page and styling
    //applySudokuStyleDimensions();
    createSudokuElements();
    printSudoku(sudoku);
}

window.onload = init;