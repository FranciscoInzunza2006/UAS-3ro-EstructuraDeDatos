
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

shuffle(available_digits[0]);
sudoku[0] = available_digits[0];
for (let row = 1; row < SUDOKU_SIZE; row++) {
    let test_row = available_digits[row]
    shuffle(test_row)

    // Make that the number isn't already in the column
    let try_again;
    do {
        try_again = false;
        for (let col = 0; col < SUDOKU_SIZE; col++) {
            for (let row_check = 0; row_check < row; row_check++) {
                if (test_row[col] === sudoku[row_check][col]) {
                    try_again = true;

                    // FIXME: This causes and infinite loop, get another way to get a valid digit
                    // Swap with next value and keep trying till we get a valid combination
                    const next = (col+1) % SUDOKU_SIZE;
                    const next_val = test_row[next]
                    test_row[next] = test_row[col];
                    test_row[col] = next_val;

                    break;
                }
            }
        }
    } while(try_again)

    console.log(test_row.join(" "))
    sudoku[row] = test_row;
}


// Print sudoku
for (let i = 0; i < SUDOKU_SIZE; i++) {
   console.log(sudoku[i].join(" "));
}