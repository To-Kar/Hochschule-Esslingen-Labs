document.addEventListener("DOMContentLoaded", (event) => {
  const container = document.createElement("div");
  container.className = "container";

  const header = document.createElement("header");
  const headerDiv = document.createElement("div");
  const h1 = document.createElement("h1");
  h1.textContent = "Minesweeper";
  headerDiv.appendChild(h1);
  headerDiv.appendChild(document.createTextNode("by Tom K"));
  header.appendChild(headerDiv);
  container.appendChild(header);

  const playfield = document.createElement("div");
  playfield.className = "playfield";
  playfield.id = "playfield";
  container.appendChild(playfield);

  const overlay = document.createElement("div");
  overlay.className = "overlay";
  overlay.id = "overlay";
  container.appendChild(overlay);

  const buttons = document.createElement("div");
  buttons.className = "buttons";
  buttons.id = "buttons";
  const smallButton = document.createElement("button");
  smallButton.className = "small";
  smallButton.textContent = "Small";
  const mediumButton = document.createElement("button");
  mediumButton.className = "medium";
  mediumButton.textContent = "Medium";
  const largeButton = document.createElement("button");
  largeButton.className = "large";
  largeButton.textContent = "Large";
  buttons.appendChild(smallButton);
  buttons.appendChild(mediumButton);
  buttons.appendChild(largeButton);
  container.appendChild(buttons);

  const endGameContainer = document.createElement("div");
  endGameContainer.id = "endGameContainer";
  container.appendChild(endGameContainer);

  const footer = document.createElement("footer");
  const footerDiv = document.createElement("div");
  const footerP = document.createElement("p");
  footerP.innerHTML = "&copy; 2024 by Tom K";
  footerDiv.appendChild(footerP);
  footer.appendChild(footerDiv);
  container.appendChild(footer);

  document.body.appendChild(container);

  let token = null;
  const baseUrl = '';//Hier war ein Link mit dem man ein Token bekommen hat für das Spiel
  let gameEnded = false;
  let numRows = 0;
  let numCols = 0;
  let cells = [];

  async function initGame(userId, size, mines) {
    try {
      const response = await fetch(`${baseUrl}?request=init&userid=${userId}&size=${size}&mines=${mines}`, {
        method: 'GET',
      });
      const data = await response.json();
      console.log(data); // Ausgabe des Token-Objekts
      if (data.status === 'ok') {
        token = data.token;
      } else {
        console.error('Failed to initialize game:', data);
      }
      return data;
    } catch (error) {
      console.error('Error initializing game:', error);
      return { status: 'error', message: error.message };
    }
  }

  async function sweep(x, y) {
    if (!token) {
      console.error('Token is not initialized.');
      return { status: 'error', message: 'Token is not initialized.' };
    }

    try {
      const response = await fetch(`${baseUrl}?request=sweep&token=${token}&x=${x}&y=${y}`, {
        method: 'GET',
      });
      if (!response.ok) {
        const errorData = await response.json();
        console.error('Error sweeping cell:', errorData.message || response.statusText);
        return { status: 'error', message: errorData.message || response.statusText };
      }
      const data = await response.json();
      console.log(data); // Ausgabe des Sweep-Response-Objekts
      return data;
    } catch (error) {
      console.error('Error sweeping cell:', error);
      return { status: 'error', message: error.message };
    }
  }

  async function init(difficulty = 'small') {
    const userId = "tokait01"; // Replace with your actual user ID
    numRows = numCols = difficulty === 'small' ? 9 : difficulty === 'medium' ? 16 : 24;
    const mines = difficulty === 'small' ? 10 : difficulty === 'medium' ? 40 : difficulty === 'large' ? 99 : 10;

    const data = await initGame(userId, numCols, mines);
    if (data.status === 'ok') {
      createBoard(numRows, numCols);
      gameEnded = false;
      overlay.style.display = "none";
    } else {
      overlay.textContent = "Error initializing game. Please try again.";
      overlay.style.display = "block";
    }
  }

  function createBoard(rows, cols) {
    playfield.style.gridTemplateRows = `repeat(${rows}, 1fr)`;
    playfield.style.gridTemplateColumns = `repeat(${cols}, 1fr)`;
    playfield.innerHTML = "";
    cells = []; // Initialize cells array

    for (let i = 0; i < rows * cols; i++) {
      const cell = document.createElement("div");
      cell.classList.add("cell");
      cell.dataset.index = i;
      cell.dataset.mine = 'false'; // Default value for all cells
      cell.addEventListener("click", (e) => onCellClick(e, i));
      cell.addEventListener("contextmenu", (e) => {
        e.preventDefault();
        onRightClick(e, i);
      });
      cells.push(cell);
      playfield.appendChild(cell);
    }
  }

  async function onCellClick(event, index) {
    if (gameEnded) return;
    const x = index % numCols;
    const y = Math.floor(index / numCols);

    const data = await sweep(x, y);
    if (data.status === 'ok') {
      console.log(`Cell clicked at (${x}, ${y}):`, data); // Debug-Ausgabe
      revealCell(index, data);
      if (data.minehit || data.userwins) {
        console.log("Game end condition met"); // Debug-Ausgabe
        revealAllMines(data.mines || []); // Hier wird `revealAllMines` aufgerufen, sicherstellen, dass es immer ein Array ist
        endGame(data.userwins);
      }
    } else {
      overlay.textContent = "An error occurred. Please try again.";
    }

    event.target.classList.add("cell_shadow");
  }

  function onRightClick(event, index) {
    if (gameEnded) return;
    const cell = event.target;
    if (cell.classList.contains('revealed')) return;

    cell.classList.toggle('flagged');
    cell.classList.toggle('cell_symbol9');
  }

  function revealCell(index, data) {
    const cell = cells[index];
    cell.className = 'cell';
    cell.classList.add("revealed", "cell_shadow");

    if (data.minehit) {
      cell.classList.add("cell_symbol10");
    } else if (data.minesAround > 0) {
      cell.classList.add("cell_symbol" + data.minesAround);
    } else {
      cell.classList.add("cell_symbol0");
      revealAdjacentCells(data.emptyCells);
    }
  }

  function revealAdjacentCells(emptyCells) {
    emptyCells.forEach(cellData => {
      const index = cellData.y * numCols + cellData.x;
      const cell = cells[index];
      if (!cell.classList.contains('revealed')) {
        revealCell(index, { minesAround: cellData.minesAround, minehit: false, emptyCells: [] });
      }
    });
  }

  function revealAllMines(mines) {
    if (!mines) return; // Sicherstellen, dass `mines` definiert ist
    mines.forEach(mine => {
      const index = mine.y * numCols + mine.x;
      const cell = cells[index];
      cell.classList.add('cell_symbol10');
    });
  }

  function endGame(win) {
    gameEnded = true;
    console.log("Endgame reached"); // Debug-Ausgabe
    console.log("Win status:", win); // Debug-Ausgabe
    overlay.textContent = win ? "You Win!" : "You Lose!";
    overlay.className = "overlay"; // Reset the class name
    overlay.classList.add(win ? "message-win" : "message-lose");
    overlay.style.display = "block";
  }

  buttons.addEventListener("click", (event) => {
    if (event.target.tagName === "BUTTON") {
      gameEnded = false;
      switch (event.target.className) {
        case "small":
          init('small');
          break;
        case "medium":
          init('medium');
          break;
        case "large":
          init('large');
          break;
      }
    }
  });

  init(); // Initialize the game with default difficulty
});
