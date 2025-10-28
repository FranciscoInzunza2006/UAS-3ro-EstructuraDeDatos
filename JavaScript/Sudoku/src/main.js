"use strict"

/** TODO:
 * Hacer que la página se vea bien perrona
 * Qué no puedas modificar el sudoku inicial
 * El señalar de alguna manera cuando el sudoku se vuelve invalido (Señalar las celdas que tú modificaste)
 */

// HTML Elements
const SUDOKU_CONTAINER = document.getElementById("sudoku");
const DEBUG_ELEMENT = document.getElementById("temu_console");

let game = new SudokuGame(SUDOKU_CONTAINER);

window.onload = function () {
    game.start();
}