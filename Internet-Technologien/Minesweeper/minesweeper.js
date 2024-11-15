const grid = document.getElementById('minesweeper');
const rows = 10;
const cols = 10;
const mineCount = 20;
let board = [];

function initGame() {
    board = generateBoard(rows, cols, mineCount);
    drawBoard(board);
}

function generateBoard(rows, cols, mineCount) {
    let board = Array(rows).fill().map(() => Array(cols).fill(0));
    let minesPlaced = 0;

    while (minesPlaced < mineCount) {
        let r = Math.floor(Math.random() * rows);
        let c = Math.floor(Math.random() * cols);

        if (board[r][c] === 0) {
            board[r][c] = 'M';
            minesPlaced++;
        }
    }

    for (let r = 0; r < rows; r++) {
        for (let c = 0; c < cols; c++) {
            if (board[r][c] === 'M') continue;
            let mines = countAdjacentMines(r, c, board);
            board[r][c] = mines;
        }
    }

    return board;
}

function drawBoard(board) {
    grid.innerHTML = '';
    board.forEach((row, r) => {
        row.forEach((cell, c) => {
            let cellElement = document.createElement('div');
            cellElement.addEventListener('click', () => revealCell(r, c));
            cellElement.classList.add('cell');
            grid.appendChild(cellElement);
        });
    });
}

function countAdjacentMines(r, c, board) {
    let count = 0;
    for (let i = -1; i <= 1; i++) {
        for (let j = -1; j <= 1; j++) {
            if (r + i < 0 || r + i >= board.length || c + j < 0 || c + j >= board[r].length) continue;
            if (board[r + i][c + j] === 'M') count++;
        }
    }
    return count;
}

function revealCell(r, c) {
    if (board[r][c] === 'M') {
        alert('Game Over!');
        initGame();
        return;
    }
    let cell = grid.children[r * cols + c];
    cell.classList.add('revealed');
    cell.textContent = board[r][c] > 0 ? board[r][c] : '';
}

initGame();
