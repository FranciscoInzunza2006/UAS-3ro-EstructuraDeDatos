
const SUDOKU_SIZE = 9

function shuffle(array) {
    let current_index = array.length-1;

    while (current_index > 0) {
        const random_index = Math.floor(Math.random() * current_index);
        [array[current_index], array[random_index]] = [array[random_index], array[current_index]];

        current_index--;
    }
}

// Empty sudoku
let sudoku = new Array(SUDOKU_SIZE);
for (let i = 0; i < SUDOKU_SIZE; i++) {
    sudoku[i] = new Array(SUDOKU_SIZE);
}

// Create solved sudoku
let available_digits = new Array(SUDOKU_SIZE);
for (let i = 0; i < SUDOKU_SIZE; i++) {
    available_digits[i] = new Array(SUDOKU_SIZE);
    for (let j = 0; j < SUDOKU_SIZE; j++) {
        available_digits[i][j] = j;
    }
}

function isInRows(value, col, row) {
    for (let row_check = 0; row_check < row; row_check++) {
        if (value === sudoku[row_check][col]) {
            return true;
        }
    }

    return false;
}

//shuffle(available_digits[0]);
sudoku[0] = available_digits[0];
for (let row = 1; row < SUDOKU_SIZE; row++) {
    let test_row = available_digits[row]
//    shuffle(test_row)

    for (let col = 0; col < SUDOKU_SIZE; col++) {
        for (let i = 0; i < test_row.length - 2; i++) {
            const n = test_row[i];

            if (isInRows(n, col, row))
                continue;

            sudoku[row][col] = n;
            test_row.splice(i, 1)
            break;
        }

        let last = test_row[test_row.length - 1];
        if (last)
    }
}


// Print sudoku
for (let i = 0; i < SUDOKU_SIZE; i++) {
   console.log(sudoku[i].join(" "));
}