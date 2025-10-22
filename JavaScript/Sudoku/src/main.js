
"use strict"

// HTML Elements
const SUDOKU_ELEMENT = document.getElementById("sudoku");
const DEBUG_ELEMENT = document.getElementById("debug_output");

// Size of the sudoku board
const REGIONS_PER_ROW = 3;
const BLOCKS_PER_ROW = 3;

const TOTAL_REGIONS = REGIONS_PER_ROW ** 2;
const BLOCKS_PER_REGION = BLOCKS_PER_ROW ** 2;

let sudoku = new Array(TOTAL_REGIONS);
for (let i = 0; i < sudoku.length; i++) {
    sudoku[i] = new Array(BLOCKS_PER_REGION);
}

function block_position(event) {
    let block_element = event.target;
    DEBUG_ELEMENT.innerText += "Block index: " + block_element.dataset.index + "\n";
    DEBUG_ELEMENT.innerText += "Region index: " + block_element.parentElement.dataset.index + "\n";
}

function applySudokuStyleDimensions() {
    document.documentElement.style.setProperty("--sudoku-regions-per-row", REGIONS_PER_ROW.toString());
    document.documentElement.style.setProperty("--sudoku-blocks-per-row", BLOCKS_PER_ROW.toString());
}

// function createSudokuBlocks(region_index, sudoku_region_element) {
//     for (let block_index = 0; block_index < BLOCKS_PER_ROW ** 2; block_index++) {
//         const sudoku_block = document.createElement("div");
//         sudoku_block.dataset.index = block_index.toString();
//         sudoku_block.onclick = block_position;
//
//         sudoku_block.innerText = (block_index + 1).toString();
//
//         sudoku_region_element.appendChild(sudoku_block);
//     }
// }

// function createSudokuRegions() {
//     for (let region_index = 0; region_index < REGIONS_PER_ROW ** 2; region_index++) {
//         const sudoku_region = document.createElement("div");
//         sudoku_region.dataset.index = region_index.toString();
//         sudoku_region.classList.add("sudoku-region");
//
//         createSudokuBlocks(sudoku_region);
//         SUDOKU_ELEMENT.appendChild(sudoku_region);
//     }
// }

function init_sudoku() {
    // Internal sudoku
    let sudoku_digits = new Array(BLOCKS_PER_ROW ** 2);
    for (let i = 0; i < sudoku_digits.length; i++) {
        sudoku_digits[i] = i+1;
    }

    // What values are still available in each row and column
    let columns = new Array(REGIONS_PER_ROW ** 2);
    let rows = new Array(REGIONS_PER_ROW ** 2);
    for (let i = 0; i < columns.length; i++) {
        columns[i] = Array.from(sudoku_digits);
        rows[i] = Array.from(sudoku_digits);
    }

    for (let region_row = 0; region_row < REGIONS_PER_ROW; region_row++) {
        for (let region_col = 0; region_col < REGIONS_PER_ROW; region_col++) {
            const region_index = region_row * REGIONS_PER_ROW + region_col;
            for (let block_row = 0; block_row < BLOCKS_PER_ROW; block_row++) {
                for (let block_col = 0; block_col < BLOCKS_PER_ROW; block_col++) {
                    const cell_index = block_row * REGIONS_PER_ROW + block_col;

                    sudoku[region_index][cell_index] = region_index * BLOCKS_PER_REGION + cell_index + 1;
                }
            }
        }
    }

    // HTML Page and styling
    applySudokuStyleDimensions();

    createSudokuRegions();
}

window.onload = init_sudoku;