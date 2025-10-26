class SudokuDrawer {
    static REGION_CLASS = "sudoku-region"
    static CELL_CLASS = "sudoku-cell"

    static CLUE_CLASS = "clue"

    constructor(sudoku_container) {
        this.container = sudoku_container;
    }

    createElements() {
        for (let region_index = 0; region_index < SudokuGenerator.REGIONS; region_index++) {
            const region = document.createElement("div");
            region.classList.add(SudokuDrawer.REGION_CLASS);

            for (let cell_index = 0; cell_index < SudokuGenerator.CELLS; cell_index++) {
                const cell = document.createElement("div");
                cell.classList.add(SudokuDrawer.CELL_CLASS);
                region.appendChild(cell);
            }
            this.container.appendChild(region);
        }
    }

    restart(sudoku_puzzle) {
        for (let region_index = 0; region_index < SudokuGenerator.REGIONS; region_index++) {
            const region_row = Math.floor(region_index / SudokuGenerator.SUDOKU_WIDTH);
            const region_col = region_index % SudokuGenerator.SUDOKU_WIDTH;

            const region = this.container.children[region_index];
            for (let cell_index = 0; cell_index < SudokuGenerator.CELLS; cell_index++) {
                const row = region_row * SudokuGenerator.REGION_HEIGHT + Math.floor(cell_index / SudokuGenerator.REGION_HEIGHT);
                const col = region_col * SudokuGenerator.REGION_WIDTH + (cell_index % SudokuGenerator.REGION_WIDTH);

                let cell = region.children[cell_index];
                const value = sudoku_puzzle[row][col];
                if (this.#is_clue(value)) {
                    cell.onclick = null;

                    cell.innerText = value.toString();
                    cell.classList.add(SudokuDrawer.CLUE_CLASS);
                    continue;
                }


                cell.classList.remove(SudokuDrawer.CLUE_CLASS);
            }
        }
    }

    #is_clue(value) {
        return value !== SudokuGenerator.EMPTY_CELL;
    }
}