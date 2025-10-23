
const EMPTY_CELL = 0;
const SUDOKU_SIZE = 9;

const REGIONS = 3;

const ROWS = 9
const COLUMNS = 9

// Sudoku puzzle
let sudoku = [[1]];

function generateSudoku() {
    // Empty sudoku
    sudoku = new Array(SUDOKU_SIZE);
    for (let row = 0; row < ROWS; row++) {
        for (let col = 0; col < COLUMNS; col++) {
            sudoku[row] = new Array(SUDOKU_SIZE).fill(EMPTY_CELL);
        }
    }

    for (let region_index = 0; region_index < REGIONS; region_index++) {
        const nums = [1, 2, 3, 4, 5, 6, 7, 8, 9];
        shuffle(nums);

        for (let row = 0; row < 3; row++) {
            for (let col = 0; col < 3; col++) {
                sudoku[region_index * 3 + row][region_index * 3 + col] = nums[row * 3 + col];
            }
        }
    }

    solveSudoku(sudoku);
}

function solveSudoku() {
    for (let row = 0; row < 9; row++) {
        for (let col = 0; col < 9; col++) {
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
    for (let x = 0; x < 9; x++) {
        if (sudoku[row][x] === num) return false;
    }

    for (let x = 0; x < 9; x++) {
        if (sudoku[x][col] === num) return false;
    }

    const startRow = Math.floor(row / 3) * 3;
    const startCol = Math.floor(col / 3) * 3;

    for (let i = 0; i < 3; i++) {
        for (let j = 0; j < 3; j++) {
            if (sudoku[i + startRow][j + startCol] === num) return false;
        }
    }

    return true;
}

function shuffle(array) {
    let current_index = array.length-1;

    while (current_index > 0) {
        const random_index = Math.floor(Math.random() * (current_index+1));
        [array[current_index], array[random_index]] = [array[random_index], array[current_index]];

        current_index--;
    }
}

function printSudoku() {
    for (let i = 0; i < ROWS; i++) {
        const row = sudoku[i];
        console.log(row.join(" "));
    }
}

generateSudoku();
printSudoku();