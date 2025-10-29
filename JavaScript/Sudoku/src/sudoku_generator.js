class SudokuGenerator {
    static SUDOKU_WIDTH = 3
    static SUDOKU_HEIGHT = 3

    static REGION_WIDTH = 3
    static REGION_HEIGHT = 3

    static REGIONS = SudokuGenerator.SUDOKU_WIDTH * SudokuGenerator.SUDOKU_HEIGHT;
    static CELLS = SudokuGenerator.REGION_WIDTH * SudokuGenerator.REGION_HEIGHT;
    static TOTAL_CELLS = SudokuGenerator.REGIONS * SudokuGenerator.CELLS;

    static ROWS = SudokuGenerator.SUDOKU_HEIGHT * SudokuGenerator.REGION_HEIGHT
    static COLUMNS = SudokuGenerator.SUDOKU_WIDTH * SudokuGenerator.REGION_WIDTH;

    static EMPTY_CELL = 0;

    generate() {
        // Empty sudoku
        let sudoku = new Array(SudokuGenerator.ROWS);
        for (let row = 0; row < SudokuGenerator.ROWS; row++) {
            sudoku[row] = new Array(SudokuGenerator.COLUMNS).fill(SudokuGenerator.EMPTY_CELL);
        }

        // Fill diagonal regions
        for (let region_index = 0; region_index < SudokuGenerator.SUDOKU_WIDTH; region_index++) {
            const nums = [1, 2, 3, 4, 5, 6, 7, 8, 9];

            this.#shuffleArray(nums);
            for (let row = 0; row < SudokuGenerator.REGION_HEIGHT; row++) {
                for (let col = 0; col < SudokuGenerator.REGION_WIDTH; col++) {
                    sudoku[region_index * SudokuGenerator.REGION_HEIGHT + row][region_index * SudokuGenerator.REGION_WIDTH + col] = nums.pop();
                }
            }
        }

        this.#solveSudoku(sudoku);

        return sudoku;
    }

    generatePuzzle(solved_sudoku, difficulty = 35) {
        let puzzle = [];
        solved_sudoku.forEach(row => {
            puzzle.push(Array.from(row));
        })

        const cells = [];
        for (let row = 0; row < SudokuGenerator.ROWS; row++) {
            for (let col = 0; col < SudokuGenerator.COLUMNS; col++) {
                cells.push([row, col]);
            }
        }
        this.#shuffleArray(cells);

        for (let removed_cells = 0; removed_cells < difficulty; removed_cells++) {
            const [row, col] = cells[removed_cells];
            puzzle[row][col] = SudokuGenerator.EMPTY_CELL;
        }

        return puzzle;
    }

    isValidCell(sudoku, row, col, num) {
        for (let x = 0; x < SudokuGenerator.COLUMNS; x++) {
            if (sudoku[row][x] === num) return false;
        }

        for (let y = 0; y < SudokuGenerator.ROWS; y++) {
            if (sudoku[y][col] === num) return false;
        }

        // Check region
        const region_start_row = Math.floor(row / 3) * 3;
        const region_start_col = Math.floor(col / 3) * 3;
        for (let i = 0; i < SudokuGenerator.REGION_HEIGHT; i++) {
            for (let j = 0; j < SudokuGenerator.REGION_WIDTH; j++) {
                if (sudoku[i + region_start_row][j + region_start_col] === num) return false;
            }
        }

        return true;
    }

    #solveSudoku(sudoku) {
        for (let row = 0; row < SudokuGenerator.ROWS; row++) {
            for (let col = 0; col < SudokuGenerator.COLUMNS; col++) {
                if (sudoku[row][col] === SudokuGenerator.EMPTY_CELL) {
                    const nums = [1, 2, 3, 4, 5, 6, 7, 8, 9];
                    this.#shuffleArray(nums);

                    for (const num of nums) {
                        if (this.isValidCell(sudoku, row, col, num)) {
                            sudoku[row][col] = num;
                            if (this.#solveSudoku(sudoku)) return true;
                            sudoku[row][col] = SudokuGenerator.EMPTY_CELL;
                        }
                    }
                    return false;
                }
            }
        }
        return true;
    }

    #shuffleArray(array) {
        let current_index = array.length - 1;

        while (current_index > 0) {
            const random_index = Math.floor(Math.random() * (current_index + 1));
            [array[current_index], array[random_index]] = [array[random_index], array[current_index]];

            current_index--;
        }
    }
}