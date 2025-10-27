class SudokuGame {
    static STARTING_LIVES = 3;
    static BONUS_LIVES = 1;
    constructor(sudoku_container) {
        this.generator = new SudokuGenerator();
        this.drawer = new SudokuHtmlHandler(sudoku_container, (e) => this.#clickedCell(e));

        this.solution = null;
        this.puzzle = null;

        this.lives = SudokuGame.STARTING_LIVES;
        this.flawless = false;

        this.current_level = 0;

        this.time_taken = 0;
        this.time_in_level = 0;
    }

    start() {
        this.drawer.createElements();
        this.#next_level();
    }

    #next_level() {
        this.current_level++;

        this.solution = this.generator.generate();
        this.puzzle = this.generator.generatePuzzle(this.solution);

        this.lives = SudokuGame.STARTING_LIVES;
        if (this.flawless)
            this.lives += SudokuGame.BONUS_LIVES;
        this.flawless = true;

        this.drawer.restart(this.puzzle);

        this.time_in_level = 0;

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
            DEBUG_ELEMENT.innerText = "¡Esa no era la respuesta correcta!";

            // TODO: Game Over

            return;
        }

        this.puzzle[row][col] = correct_value;
        cell.innerText = correct_value.toString();
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