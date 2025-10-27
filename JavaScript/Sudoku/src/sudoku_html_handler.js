class SudokuHtmlHandler {
    static REGION_CLASS = "sudoku-region"
    static CELL_CLASS = "sudoku-cell"

    static CLUE_CLASS = "clue"

    constructor(sudoku_container, on_click) {
        this.container = sudoku_container;
        this.on_click = on_click;
    }

    createElements() {
        for (let region_index = 0; region_index < SudokuGenerator.REGIONS; region_index++) {
            const region = document.createElement("div");
            region.classList.add(SudokuHtmlHandler.REGION_CLASS);

            for (let cell_index = 0; cell_index < SudokuGenerator.CELLS; cell_index++) {
                const cell = document.createElement("div");

                const [row, col] = this.#index_to_row_and_col(region_index, cell_index);
                cell.dataset.row = row.toString();
                cell.dataset.col = col.toString();

                cell.classList.add(SudokuHtmlHandler.CELL_CLASS);
                region.appendChild(cell);
            }
            this.container.appendChild(region);
        }
    }

    restart(sudoku_puzzle) {
        for (let region_index = 0; region_index < SudokuGenerator.REGIONS; region_index++) {
            const region = this.container.children[region_index];
            for (let cell_index = 0; cell_index < SudokuGenerator.CELLS; cell_index++) {
                let cell = region.children[cell_index];

                const row = Number(cell.dataset.row);
                const col = Number(cell.dataset.col);

                const value = sudoku_puzzle[row][col];
                if (this.#is_clue(value)) {
                    cell.onclick = null;

                    cell.innerText = value.toString();
                    cell.classList.add(SudokuHtmlHandler.CLUE_CLASS);
                    continue;
                }

                cell.onclick = this.on_click;
                cell.classList.remove(SudokuHtmlHandler.CLUE_CLASS);
            }
        }
    }

    #index_to_row_and_col(region_index, cell_index) {
        const region_row = Math.floor(region_index / SudokuGenerator.SUDOKU_WIDTH);
        const region_col = region_index % SudokuGenerator.SUDOKU_WIDTH;

        const row = region_row * SudokuGenerator.REGION_HEIGHT + Math.floor(cell_index / SudokuGenerator.REGION_HEIGHT);
        const col = region_col * SudokuGenerator.REGION_WIDTH + (cell_index % SudokuGenerator.REGION_WIDTH);

        return [row, col];
    }

    #is_clue(value) {
        return value !== SudokuGenerator.EMPTY_CELL;
    }
}