class SudokuGame {
    static STARTING_LIVES = 3;

    constructor(sudoku_container) {
        this.generator = new SudokuGenerator();
        this.drawer = new SudokuDrawer(sudoku_container);

        this.solution = null;
        this.puzzle = null;

        this.lives = SudokuGame.STARTING_LIVES;

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

        this.drawer.restart(this.puzzle);

        this.time_in_level = 0;

        let debug_solution = document.getElementById("solution");
        let debug_puzzle = document.getElementById("puzzle");

        debug_solution.innerText = "";
        debug_puzzle.innerText = "";
        for(let row_index = 0; row_index < SudokuGenerator.ROWS; row_index++) {
            debug_solution.innerText += this.solution[row_index].join("") + "\n";
            debug_puzzle.innerText += this.puzzle[row_index].join("").replaceAll("0", " ") + "\n";
        }


    }
}