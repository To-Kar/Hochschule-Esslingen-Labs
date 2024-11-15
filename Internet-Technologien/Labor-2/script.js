document.addEventListener("DOMContentLoaded", (event) => {
  // Create necessary HTML elements
  const content = document.createElement("div");
  content.className = "content";

  const header = document.createElement("header");
  const headerDiv = document.createElement("div");
  const h1 = document.createElement("h1");
  h1.textContent = "Minesweeper";
  headerDiv.appendChild(h1);
  headerDiv.appendChild(document.createTextNode("by Tom Karaqi"));
  header.appendChild(headerDiv);
  content.appendChild(header);

  const playfield = document.createElement("div");
  playfield.className = "playfield";
  playfield.id = "playfield";
  content.appendChild(playfield);

  const overlay = document.createElement("div");
  overlay.className = "overlay";
  overlay.id = "overlay";
  content.appendChild(overlay);

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
  content.appendChild(buttons);

  const endGameContainer = document.createElement("div");
  endGameContainer.id = "endGameContainer";
  const restartButton = document.createElement("button");
  restartButton.id = "restartButton";
  restartButton.textContent = "Restart";
  endGameContainer.appendChild(restartButton);
  content.appendChild(endGameContainer);

  const footer = document.createElement("footer");
  const footerDiv = document.createElement("div");
  const footerP = document.createElement("p");
  footerP.innerHTML = "&copy; 2024 by Tom Karaqi";
  footerDiv.appendChild(footerP);
  footer.appendChild(footerDiv);
  content.appendChild(footer);

  document.body.appendChild(content);

  // Existing JavaScript code with slight modifications
  let rows = 9;
  let cols = 9;
  let minesCount = 10;
  let gameEnded = false;
  let cells = [];
  let mines = [];
  let flags = [];

  function init() {
    playfield.style.gridTemplateRows = `repeat(${rows}, 1fr)`;
    playfield.style.gridTemplateColumns = `repeat(${cols}, 1fr)`;
    playfield.innerHTML = "";

    cells = Array(rows * cols)
      .fill(null)
      .map((_, index) => {
        const cell = document.createElement("div");
        cell.classList.add("cell");
        cell.dataset.index = index;
        cell.addEventListener("click", onCellClick);
        cell.addEventListener("contextmenu", onRightClick);
        return cell;
      });

    cells.forEach((cell) => playfield.appendChild(cell));

    mines = generateMines();
    flags = Array(rows * cols).fill(false);

    gameEnded = false;
    overlay.style.display = "none";
    restartButton.style.display = "none";
  }

  function generateMines() {
    const minesArray = Array(rows * cols).fill(false);
    let count = 0;
    while (count < minesCount) {
      const index = Math.floor(Math.random() * minesArray.length);
      if (!minesArray[index]) {
        minesArray[index] = true;
        count++;
      }
    }
    return minesArray;
  }

  function onCellClick(event) {
    if (gameEnded) return;
    const index = event.target.dataset.index;
    if (mines[index]) {
      revealMines();
      endGame(false);
    } else {
      revealCell(index);
      checkWin();
    }
    event.target.classList.add("cell_shadow");
  }

  function onRightClick(event) {
    event.preventDefault();
    if (gameEnded) return;
    const index = event.target.dataset.index;
    if (flags[index]) {
      event.target.classList.remove("cell_symbol9");
      flags[index] = false;
    } else {
      event.target.classList.add("cell_symbol9");
      flags[index] = true;
    }
  }

  function revealCell(index) {
    const cell = cells[index];
    if (!cell.classList.contains("revealed")) {
      cell.classList.add("revealed", "cell_shadow");
      const minesCount = countMinesAround(index);
      if (minesCount > 0) {
        cell.classList.add("cell_symbol" + minesCount);
      } else {
        revealAdjacentCells(index);
      }
    }
  }

  function revealAdjacentCells(index) {
    const adjacentIndices = getAdjacentIndices(index);
    for (let i = 0; i < adjacentIndices.length; i++) {
      const adjacentIndex = adjacentIndices[i];
      if (!cells[adjacentIndex].classList.contains("revealed")) {
        revealCell(adjacentIndex);
      }
    }
  }

  function getAdjacentIndices(index) {
    const indices = [];
    const row = Math.floor(index / cols);
    const col = index % cols;

    for (let r = row - 1; r <= row + 1; r++) {
      for (let c = col - 1; c <= col + 1; c++) {
        if (
          r >= 0 &&
          r < rows &&
          c >= 0 &&
          c < cols &&
          !(r === row && c === col)
        ) {
          indices.push(r * cols + c);
        }
      }
    }
    return indices;
  }

  function countMinesAround(index) {
    return getAdjacentIndices(index).filter((i) => mines[i]).length;
  }

  function revealMines() {
    mines.forEach((mine, index) => {
      if (mine) {
        cells[index].classList.add("mine", "cell_symbol10");
      }
    });
  }

  function checkWin() {
    const revealedCellsCount = cells.filter((cell) =>
      cell.classList.contains("revealed")
    ).length;
    if (revealedCellsCount === rows * cols - minesCount) {
      endGame(true);
    }
  }

  function endGame(win) {
    gameEnded = true;
    overlay.textContent = win ? "You Win!" : "You Lose!";
    overlay.className = ""; // Reset the class name
    overlay.classList.add(win ? "message-win" : "message-lose");
    overlay.style.display = "block";
    restartButton.style.display = "block";
  }

  restartButton.addEventListener("click", init);

  buttons.addEventListener("click", (event) => {
    if (event.target.tagName === "BUTTON") {
      switch (event.target.className) {
        case "small":
          rows = 9;
          cols = 9;
          minesCount = 10;
          init();
          break;
        case "medium":
          rows = 16;
          cols = 16;
          minesCount = 40;
          init();
          break;
        case "large":
          rows = 24;
          cols = 24;
          minesCount = 99;
          init();
          break;
      }
    }
  });
  init();
});
