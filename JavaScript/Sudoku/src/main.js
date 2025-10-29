"use strict"

/** TODO:
 * Hacer que la página se vea bien perrona
 * Qué no puedas modificar el sudoku inicial
 * El señalar de alguna manera cuando el sudoku se vuelve invalido (Señalar las celdas que tú modificaste)
 */

// HTML Elements
const SUDOKU_CONTAINER = document.getElementById("sudoku");
const DEBUG_ELEMENT = document.getElementById("temu_console");

let audio = new Audio('assets/audio/background_music.mp3');
audio.volume = 0.25;
audio.loop = true;

let game = new SudokuGame(SUDOKU_CONTAINER);

let scores = sessionStorage.getItem("scores");
if (scores == null) {
    scores = [];
    // scores[0] = [0, 100];
    // scores[1] = [1, 400];
    // scores[2] = [1, 200];
} else {
    scores = JSON.parse(scores);
}

document.body.style.visibility = false;
window.onload = function () {
    game.start();    
    document.body.style.visibility = true;
}

window.onclick = function () {
    audio.play();
    window.onclick = null;
}

window.onclose = function () {
    console.log("Hello");
}