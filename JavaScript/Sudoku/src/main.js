
"use strict"

// HTML Elements
const SUDOKU_ELEMENT = document.getElementById("sudoku");
const DEBUG_ELEMENT = document.getElementById("debug_output");

// Size of the sudoku board
const REGIONS_ROW_LENGTH = 4;
const BLOCKS_ROW_LENGTH = 3;

let sudoku = new Array(REGIONS_ROW_LENGTH ** 2);
sudoku.fill(new Array(BLOCKS_ROW_LENGTH ** 2));

function block_position(event) {
    let block_element = event.target;
    DEBUG_ELEMENT.innerText += "Block index: " + block_element.dataset.index + "\n";
    DEBUG_ELEMENT.innerText += "Region index: " + block_element.parentElement.dataset.index + "\n";
}

function applySudokuStyleDimensions() {
    document.documentElement.style.setProperty("--sudoku-regions-per-row", REGIONS_ROW_LENGTH.toString());
    document.documentElement.style.setProperty("--sudoku-blocks-per-row", BLOCKS_ROW_LENGTH.toString());
}

function createSudokuBlocks(sudoku_region) {
    for (let block_index = 0; block_index < BLOCKS_ROW_LENGTH ** 2; block_index++) {
        const sudoku_block = document.createElement("div");
        sudoku_block.dataset.index = block_index.toString();
        sudoku_block.onclick = block_position;

        sudoku_block.innerText = (block_index + 1).toString();

        sudoku_region.appendChild(sudoku_block);
    }
}

function createSudokuRegions() {
    for (let region_index = 0; region_index < REGIONS_ROW_LENGTH ** 2; region_index++) {
        const sudoku_region = document.createElement("div");
        sudoku_region.dataset.index = region_index.toString();
        sudoku_region.classList.add("sudoku-region");

        createSudokuBlocks(sudoku_region);
        SUDOKU_ELEMENT.appendChild(sudoku_region);
    }
}

function init_sudoku() {
    applySudokuStyleDimensions();

    createSudokuRegions();
}

window.onload = init_sudoku;