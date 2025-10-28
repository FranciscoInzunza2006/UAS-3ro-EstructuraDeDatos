class SudokuGame {
    static STARTING_LIVES = 3;
    static BONUS_LIVES = 1;

    constructor(sudoku_container) {
        this.generator = new SudokuGenerator();
        this.drawer = new SudokuHtmlHandler(sudoku_container, (e) => this.#clickedCell(e));

        this.solution = null;
        this.puzzle = null;

        this.difficulty = 35;
        this.remaining_cells = 0;

        this.lives = SudokuGame.STARTING_LIVES;
        this.flawless = false;

        this.current_level = 0;

        this.time_taken = 0;
        this.time_in_level = 0;

        setInterval(function () {
            function format_seconds(total_seconds) {
                const minutes = Math.floor(total_seconds / 60);
                const seconds = total_seconds % 60;

                const minutes_formatted = (minutes >= 10) ? minutes : '0' + minutes;
                const seconds_formatted = (seconds >= 10) ? seconds : '0' + seconds;

                return minutes_formatted + ":" + seconds_formatted;
            }

            game.time_taken++;
            game.time_in_level++;

            document.getElementById("time-total").innerText = format_seconds(game.time_taken);
            document.getElementById("time-level").innerText = format_seconds(game.time_in_level);
        }, 1000);


    }

    start() {
        this.drawer.createElements();
        this.#load_next_level();
    }

    #load_next_level() {
        this.current_level++;

        this.solution = this.generator.generate();
        this.puzzle = this.generator.generatePuzzle(this.solution, this.difficulty); // Higher difficulty the higher the level

        this.remaining_cells = this.difficulty;

        this.lives = SudokuGame.STARTING_LIVES;
        if (this.flawless)
            this.lives += SudokuGame.BONUS_LIVES;
        this.flawless = true;

        this.drawer.restart(this.puzzle);

        this.time_in_level = 0;

        this.#updateLevel();
        this.#updateLives();

        let debug_solution = document.getElementById("solution");
        let debug_puzzle = document.getElementById("puzzle");

        debug_solution.innerText = "";
        debug_puzzle.innerText = "";
        for (let row_index = 0; row_index < SudokuGenerator.ROWS; row_index++) {
            debug_solution.innerText += this.solution[row_index].join("") + "\n";
            debug_puzzle.innerText += this.puzzle[row_index].join("").replaceAll("0", " ") + "\n";
        }
    }

    #clickedCell(event) {
        const cell = event.target;
        const row = Number(cell.dataset.row);
        const col = Number(cell.dataset.col);

        const new_value = this.#getNewCellValue();
        const cell_value = this.puzzle[row][col];

        if (new_value === null || new_value === cell_value) {
            return;
        }

        const correct_value = this.solution[row][col];
        if (new_value !== correct_value) {
            this.flawless = false;
            this.lives--;
            this.#updateLives();
            if (this.lives > 0) {
                alert("¡Esa no era la respuesta correcta!");
            } else {
                this.#gameOver();
            }

            return;
        }

        //this.puzzle[row][col] = correct_value;

        cell.onclick = null;
        cell.innerText = correct_value.toString();
        cell.classList.replace(SudokuHtmlHandler.UNSOLVED_CELL_CLASS, SudokuHtmlHandler.SOLVED_CELL_CLASS);

        this.remaining_cells -= 1;
        if (this.remaining_cells === 0) {
            if (this.current_level === 5) {
                alert("¡GG!");
                window.location.reload();
            }

            let str = `¡Nivel ${this.current_level} completado!\n`;
            if (this.flawless)
                str += "¡FELICIDADES! Completaste el nivel sin ningún error.\n";

            alert(str);
            this.#load_next_level();
        }
    }

    #gameOver() {
        alert("¡Game Over!");
        window.location.reload();
    }

    #updateLevel() {
        document.getElementById("level").innerText = this.current_level.toString();
    }

    #updateLives() {
        document.getElementById("lives").innerHTML = this.lives.toString();
    }

    #getNewCellValue() {
        // TODO: Make the input system something fancier
        const input = prompt("Ingresa un valor del 1 al 9");
        if (input == null || input.trim() === "") {
            return SudokuGenerator.EMPTY_CELL;
        }

        const entered_value = parseInt(input);
        if (isNaN(entered_value)) {
            DEBUG_ELEMENT.innerText += "¡Valor invalido ingresado!\n";
            return null;
        }

        if (entered_value < 1 || entered_value > 9) {
            DEBUG_ELEMENT.innerText += "Solo números del 1 al 9\n";
            return null;
        }

        return entered_value;
    }
}