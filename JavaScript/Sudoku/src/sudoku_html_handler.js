class SudokuHtmlHandler {
    static REGION_CLASS = "sudoku-region"
    static CELL_CLASS = "sudoku-cell"

    static UNSOLVED_CELL_CLASS = "unsolved"
    static SOLVED_CELL_CLASS = "solved"
    static CLUE_CELL_CLASS = "clue"
    static FLAGGED_CELL_CLASS = "flagged"

    constructor(sudoku_container) {
        this.container = sudoku_container;
        this.on_click = (e) => {game.setCellValue(e);}
        this.on_context_menu = (e) => {game.flagCell(e); return false;}
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

                cell.classList.remove(SudokuHtmlHandler.UNSOLVED_CELL_CLASS);
                cell.classList.remove(SudokuHtmlHandler.SOLVED_CELL_CLASS);
                cell.classList.remove(SudokuHtmlHandler.CLUE_CELL_CLASS);
                cell.classList.remove(SudokuHtmlHandler.FLAGGED_CELL_CLASS);

                cell.onclick = null;
                cell.oncontextmenu = null;

                if (this.#is_clue(value)) {
                    cell.innerText = value.toString();
                    cell.classList.add(SudokuHtmlHandler.CLUE_CELL_CLASS);
                    continue;
                }

                cell.onclick = this.on_click;
                cell.oncontextmenu = this.on_context_menu;
                cell.innerText = "";
                cell.classList.add(SudokuHtmlHandler.UNSOLVED_CELL_CLASS);
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