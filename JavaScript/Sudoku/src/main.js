
"use strict"

console.log("Hello World!")

function init_sudoku() {
    let sudoku_grid = document.getElementById("sudoku_grid");

    for (let region = 0; region < 9; region++) {
        let sudoku_region = document.createElement("div");
        sudoku_region.classList.add("sudoku-region");

        for (let block = 0; block < 9; block++) {
            let sudoku_block = document.createElement("div");
            sudoku_block.innerText = (block + 1).toString();

            sudoku_region.appendChild(sudoku_block);
        }

        sudoku_grid.appendChild(sudoku_region);
    }
}

window.onload = init_sudoku;