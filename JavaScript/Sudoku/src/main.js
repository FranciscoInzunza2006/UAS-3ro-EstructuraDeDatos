
"use strict"

console.log("Hello World!")

const debug = document.getElementById("debug_output");

function block_position(event) {
    let block_element = event.target;
    debug.innerText += "Block index: " + block_element.dataset.index + "\n";
    debug.innerText += "Region index: " + block_element.parentElement.dataset.index + "\n";
}

function init_sudoku() {
    let sudoku_grid = document.getElementById("sudoku_grid");

    for (let region_index = 0; region_index < 9; region_index++) {
        let sudoku_region = document.createElement("div");
        sudoku_region.dataset.index = region_index.toString();
        sudoku_region.classList.add("sudoku-region");

        for (let block_index = 0; block_index < 9; block_index++) {
            let sudoku_block = document.createElement("div");
            sudoku_block.dataset.index = block_index.toString();
            sudoku_block.onclick = block_position;

            sudoku_block.innerText = (block_index + 1).toString();

            sudoku_region.appendChild(sudoku_block);
        }

        sudoku_grid.appendChild(sudoku_region);
    }
}

window.onload = init_sudoku;