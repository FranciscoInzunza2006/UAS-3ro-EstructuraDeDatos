
const EMPTY_CELL = 0;

// SUDOKU DIMENSIONS
const ROWS = 9;
const COLUMNS = 9; // TODO: Test for rectangles

// Sudoku puzzle
let sudoku = [[1]];

function shuffle(array) {
    let current_index = array.length-1;

    while (current_index > 0) {
        const random_index = Math.floor(Math.random() * (current_index+1));
        [array[current_index], array[random_index]] = [array[random_index], array[current_index]];

        current_index--;
    }
}

function generateSudoku() {
    // Empty sudoku
    sudoku = new Array(ROWS);
    for (let row = 0; row < ROWS; row++) {
        sudoku[row] = new Array(COLUMNS).fill(EMPTY_CELL);
    }

    // Fill diagonal regions
    for (let region_index = 0; region_index < 3; region_index++) {
        const nums = [1, 2, 3, 4, 5, 6, 7, 8, 9];
        shuffle(nums);

        for (let row = 0; row < 3; row++) {
            for (let col = 0; col < 3; col++) {
                sudoku[region_index * 3 + row][region_index * 3 + col] = nums.pop();
            }
        }
    }

    solveSudoku(sudoku);
}

function solveSudoku() {
    for (let row = 0; row < ROWS; row++) {
        for (let col = 0; col < COLUMNS; col++) {
            if (sudoku[row][col] === EMPTY_CELL) {
                const nums = [1, 2, 3, 4, 5, 6, 7, 8, 9];
                shuffle(nums);

                for (const num of nums) {
                    if (isValidCell(row, col, num)) {
                        sudoku[row][col] = num;
                        if (solveSudoku()) return true;
                        sudoku[row][col] = EMPTY_CELL;
                    }
                }
                return false;
            }
        }
    }
    return true;
}

function isValidCell(row, col, num) {
    for (let x = 0; x < COLUMNS; x++) {
        if (sudoku[row][x] === num) return false;
    }

    for (let y = 0; y < ROWS; y++) {
        if (sudoku[y][col] === num) return false;
    }

    // Check region
    const start_row = Math.floor(row / 3) * 3;
    const start_col = Math.floor(col / 3) * 3;
    for (let i = 0; i < 3; i++) {
        for (let j = 0; j < 3; j++) {
            if (sudoku[i + start_row][j + start_col] === num) return false;
        }
    }

    return true;
}

function printSudoku() {
    for (let i = 0; i < ROWS; i++) {
        const row = sudoku[i];
        console.log(row.join(" "));
    }
}

// generateSudoku()
// printSudoku()